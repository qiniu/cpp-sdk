/******************************************************************************* 
 *  @file      HttpAccessAuxiliaryStrcut.cpp 2013\3\8 18:33:16 $
 *  @author    Wang Xiaotao<wangxiaotao1980@gmail.com>
 ******************************************************************************/

#include "HttpAccess/HttpAccessAuxiliaryStrcut.h"
/******************************************************************************/
CPS_HTTPACCESS_NAMESPACE_BEGIN
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



CPS_HTTPACCESS_NAMESPACE_END
// 
// -----------------------------------------------------------------------------
