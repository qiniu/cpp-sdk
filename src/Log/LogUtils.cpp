/******************************************************************************* 
 *  @file      LogUtils.cpp 2013\12\12 10:30:49 $
 *  @author    Wang Xiaotao<wangxiaotao1980@gmail.com> (中文编码测试)
 ******************************************************************************/

#include "Log/LogUtils.h"
#include "Log/LogError.h"


#include <string>
#include <fstream>
#include <iostream>

#include "Misc/EncodeAndDecode.h"

#include "boost/thread.hpp"
#include "boost/filesystem.hpp"

/******************************************************************************/

namespace
{
    std::ofstream*  s_pLogFile       = 0;
    std::streambuf* s_std_clogbuf    = 0;

    boost::mutex    s_readLogMutex;
}



CPS_LOG_NAMESPACE_BEGIN

 
LogCode Initialize(const Utf8Char* pFilepath)
{
    LogCode resultCode = LOG_OK;

    //USING_STD_CLOG : 使用 std::clog作为输出
# if !defined(USING_STD_CLOG)
    #if defined(CPS_OS_WINDOWS)  
        #if defined(CPS_STDLIB_DINKUMWARE)
            std::string pathName(pFilepath);
            std::wstring pathNameStr;
            CPS_MISC_NAMESPACE::UTF8ToUCS2(pathNameStr, pathName.c_str(), pathName.size());
        #else

            // windows :: 非 dinkumware C++ stdlib， 
            std::string pathNameStr(pFilepath);
        #endif //(CPS_STDLIB_DINKUMWARE)

    #else
        std::string pathNameStr(pFilepath);
    #endif //CPS_OS_WINDOW

        boost::filesystem::path thePath(pathNameStr);
        if (!boost::filesystem::exists(thePath.parent_path()))
        {
            boost::filesystem::create_directories(thePath.parent_path());
        }


        s_pLogFile = new std::ofstream(pathNameStr.c_str(), std::ios::ate|std::ios::out);    

        if  (!(s_pLogFile->is_open()))
        {
            delete s_pLogFile;
            s_pLogFile = 0;
            resultCode = LOG_OPEN_LOG_FILE_FAIL;
            return resultCode;
        }

        s_std_clogbuf = std::clog.rdbuf(s_pLogFile->rdbuf()); // redirection std::clog to the log file
        // write the utf-8 bom for windows
        #if defined(CPS_OS_WINDOWS)
            char bom[] = {0xEF, 0xBB, 0xBF};
            std::clog.write(bom, 3);
        #endif
#endif


    return resultCode;
}


void Terminate()
{

# if !defined(USING_STD_CLOG)
    std::clog.rdbuf(s_std_clogbuf);   // redircition    std::clog 
    s_std_clogbuf = 0;
    s_pLogFile->close();
    delete s_pLogFile;
    s_pLogFile = 0;
#endif
}
// -----------------------------------------------------------------------------
// class :  inherit from : 
//   public  

void LogLock()
{
    s_readLogMutex.lock();
}


void LogUnLock()
{
    s_readLogMutex.unlock();
}

CPS_LOG_NAMESPACE_END
// 
// -----------------------------------------------------------------------------