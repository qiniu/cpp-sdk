/******************************************************************************* 
 *  @file      FileDefine.cpp 2013\6\5 17:37:07 $
 *  @author    Wang Xiaotao<wangxiaotao1980@gmail.com> (中文编码测试)
 ******************************************************************************/

#include "Misc/FileDefine.h"

#if defined(CPS_COMILER_MSVC_CPP)
    #include "Misc/EncodeAndDecode.h"
#endif
/******************************************************************************/

CPS_MISC_NAMESPACE_BEGIN

// -----------------------------------------------------------------------------
// public   
#if defined(CPS_COMILER_MSVC_CPP)
FILE* fopen_(const std::string& filename, const std::string& mode)
{
    std::wstring wfilename;
    std::wstring wfileMode;
    UTF8ToUCS2(wfilename, filename.c_str(), filename.size());
    UTF8ToUCS2(wfileMode, mode.c_str(), mode.size());
    FILE* tempFile  = 0;
    errno_t err = _wfopen_s(&tempFile, wfilename.c_str(), wfileMode.c_str());
    if (err != 0)
    {
        tempFile = 0;
    }
    return tempFile;
}
#else

FILE* fopen_(const std::string& filename, const std::string& mode)
{
    return fopen(filename.c_str(), mode.c_str());
}
#endif //


#if defined(CPS_COMILER_MSVC_CPP)
// -----------------------------------------------------------------------------
// public   
int stat64_( const std::string& filename, struct stat_* buf )
{
    std::wstring wfilename;
    UTF8ToUCS2(wfilename, filename.c_str(), filename.size());
    return _wstati64(wfilename.c_str(), buf);
}
#elif defined(CPS_OS_APPLE)

int stat64_( const std::string& filename, struct stat_* buf )
{
    return stat(filename.c_str(), buf);
}

#else

int stat64_( const std::string& filename, struct stat_* buf )
{
    return stat64(filename.c_str(), buf);
}
#endif // CPS_COMILER_MSVC_CPP)

CPS_MISC_NAMESPACE_END


// 
// -----------------------------------------------------------------------------