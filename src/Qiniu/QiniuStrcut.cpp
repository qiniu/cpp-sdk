/******************************************************************************* 
 *  @file      QiniuStrcut.cpp 2013\11\21 10:29:24 $
 *  @author    Wang Xiaotao<wangxiaotao1980@gmail.com> (中文编码测试)
 ******************************************************************************/

#include "Qiniu/QiniuStrcut.h"
#include "QiniuInternalConfig.h"
QINIU_NAMESPACE_BEGIN

// -----------------------------------------------------------------------------
// class :  inherit from : 
//   public  

QiniuToken::QiniuToken()
: m_access_key()
, m_secret_key()
{}
// -----------------------------------------------------------------------------
// class : ProxyInfo inherit from : QINIU_API_DECL
//   public  

QiniuToken::QiniuToken( const QiniuToken& rValue )
    : m_access_key(rValue.m_access_key)
    , m_secret_key(rValue.m_secret_key)
{

}
// -----------------------------------------------------------------------------
// class : QiniuToken inherit from : QINIU_API_DECL
//   public  

const QiniuToken& QiniuToken::operator=( const QiniuToken& rValue )
{
    m_access_key = rValue.m_access_key;
    m_secret_key = rValue.m_secret_key;

    return *this;
}


// -----------------------------------------------------------------------------
// class :  inherit from : 
//   public  

QiniuPutPolicy::QiniuPutPolicy()
    : m_bucketName(QINIU_NULL_PTR)      ///< 要上传的bucket的名称(必须设置）
    , m_keyName(QINIU_NULL_PTR)         ///< 上传后的文件名称（必须设置）
    , m_callbackUrl(QINIU_NULL_PTR)     ///< 回调url（可以为空）
    , m_callbackBody(QINIU_NULL_PTR)          ///< 回调body（可以为空)
    , m_returnUrl(QINIU_NULL_PTR)             ///< 什么意思？等待增加（可以为空)
    , m_returnBody(QINIU_NULL_PTR)            ///< 什么意思？等待增加（可以为空)
    , m_endUser(QINIU_NULL_PTR)               ///< 什么意思？等待增加（可以为空)
    , m_asyncOps(QINIU_NULL_PTR)              ///< 什么意思？等待增加（可以为空)
    , m_expires(0)      ///< 上传超时时间还是token失效时间？（值为0的话，为一个小时）
{}


// -----------------------------------------------------------------------------
// public   
ProxyInfo::ProxyInfo()
: m_proxyMode(NoProxy)        //代理模式，noproxy, http, sock4，sock5
, m_ip()                      //代理IP地址
, m_port(0)                   //端口号
, m_isUsingPwd(false)         //是否密码登陆代理，如果设定下面两项有效，否则无效。
, m_user()                    //用户名
, m_passwd()                  //密码
{}

// -----------------------------------------------------------------------------
// public   
ProxyInfo::ProxyInfo( const ProxyInfo& rValue )
    : m_proxyMode(rValue.m_proxyMode)        //代理模式，noproxy, http, sock4，sock5
    , m_ip(rValue.m_ip)                      //代理IP地址
    , m_port(rValue.m_port)                  //端口号
    , m_isUsingPwd(rValue.m_isUsingPwd)      //是否密码登陆代理，如果设定下面两项有效，否则无效。
    , m_user(rValue.m_user)                  //用户名
    , m_passwd(rValue.m_passwd)              //密码
{}

// -----------------------------------------------------------------------------
// public   
const ProxyInfo& ProxyInfo::operator=( const ProxyInfo& rValue )
{
    m_proxyMode  = rValue.m_proxyMode;        //代理模式，noproxy, http, sock4，sock5
    m_ip         = rValue.m_ip;               //代理IP地址
    m_port       = rValue.m_port;             //端口号
    m_isUsingPwd = rValue.m_isUsingPwd;       //是否密码登陆代理，如果设定下面两项有效，否则无效。
    m_user       = rValue.m_user;             //用户名
    m_passwd     = rValue.m_passwd;           //密码

    return *this;
}



// -----------------------------------------------------------------------------
// class : QiniuPutPolicy inherit from : QINIU_API_DECL
//   public  

QiniuIoPutExtraParam::QiniuIoPutExtraParam()
    : m_key(QINIU_NULL_PTR)
    , m_value(QINIU_NULL_PTR)
    , m_pNext(QINIU_NULL_PTR)

{}





// -----------------------------------------------------------------------------
// class :  inherit from : 
//   public  

QiniuIoPutExtra::QiniuIoPutExtra()
    : m_params(QINIU_NULL_PTR)
    , m_mimeType(QINIU_NULL_PTR)
    , m_crc32(0U)
    , m_checkCrc32(0)
{}


QINIU_NAMESPACE_END
// 
// -----------------------------------------------------------------------------
