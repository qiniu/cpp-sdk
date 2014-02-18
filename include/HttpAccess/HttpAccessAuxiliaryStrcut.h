/*******************************************************************************
 *  @file      HttpAccessAuxiliaryStrcut.h 2013\3\8 15:54:49 $
 *  @author    Wang Xiaotao<wangxiaotao1980@gmail.com> 中文编码测试
 *  @
 ******************************************************************************/

#ifndef HTTPACCESSAUXILIARYSTRCUT_92C9D786_80FA_4C3D_B4C8_E78D144D15F7_H__
#define HTTPACCESSAUXILIARYSTRCUT_92C9D786_80FA_4C3D_B4C8_E78D144D15F7_H__

#include"HttpAccessConfig.h"
#include <string>
/******************************************************************************/
CPS_HTTPACCESS_NAMESPACE_BEGIN

/**
 * the enum  http访问代理模式
 */
typedef enum  CPS_HTTPACCESS_API_DECL tagEnumProxyMode
{
    NoProxy              = 0,          // No Using Proxy
    ProxyHTTP            = 1,          // Using the HTTP Proxy
    ProxySock4           = 2,          // Using the Socks 4 Proxy
    ProxySock5           = 3           // Using the Socks 5 Proxy
} EnumProxyMode;

/**
 * The struct <code>ProxyInfo</code> 代理信息
 *
 */
struct CPS_HTTPACCESS_API_DECL ProxyInfo
{
    ProxyInfo();
    ProxyInfo(const ProxyInfo& rValue);

    const ProxyInfo& operator = (const ProxyInfo& rValue);

    EnumProxyMode   m_proxyMode;   //代理模式，noproxy, http, sock4，sock5
    std::string     m_ip;          //代理IP地址
    UInt32          m_port;        //端口号

    bool            m_isUsingPwd;  //是否密码登陆代理，如果设定下面两项有效，否则无效。

    std::string     m_user;        //用户名
    std::string     m_passwd;      //密码
};

CPS_HTTPACCESS_NAMESPACE_END
/******************************************************************************/
#endif// HTTPACCESSAUXILIARYSTRCUT_92C9D786_80FA_4C3D_B4C8_E78D144D15F7_H__
