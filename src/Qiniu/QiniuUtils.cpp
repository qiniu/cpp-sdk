/******************************************************************************* 
 *  @file      QiniuUtils.cpp 2013\11\20 19:20:43 $
 *  @author    Wang Xiaotao<wangxiaotao1980@gmail.com> (中文编码测试)
 ******************************************************************************/


#include "Qiniu/QiniuUtils.h"
#include "HttpAccess/HttpAccessUtils.h"


#include "openssl/hmac.h"
#include "openssl/engine.h"



/******************************************************************************/

namespace
{
    static std::string s_UserAgentStr;
}


QINIU_NAMESPACE_BEGIN

// -----------------------------------------------------------------------------
// public   static
QiniuCode QiniuUtils::Initialize()
{
    QiniuCode resultCode  = 0U;
    resultCode = CPS_HTTPACCESS_NAMESPACE::Initialize();

    //::ENGINE_load_builtin_engines();
    //::ENGINE_register_all_complete();

    return resultCode;
}

// -----------------------------------------------------------------------------
// public   static
void QiniuUtils::Terminate()
{   

    CPS_HTTPACCESS_NAMESPACE::Terminate();

}

// -----------------------------------------------------------------------------
// public  static  
void QiniuUtils::setUserAgent( const char* pUserAgent )
{
    s_UserAgentStr = pUserAgent;
}

// -----------------------------------------------------------------------------
// public  static  
const char* QiniuUtils::getUserAgent()
{
    return s_UserAgentStr.c_str();
}

QINIU_NAMESPACE_END

// 
// -----------------------------------------------------------------------------
