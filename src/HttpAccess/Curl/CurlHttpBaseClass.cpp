/******************************************************************************* 
 *  @file      CurlHttpBaseClass.cpp 2013\3\8 13:10:59 $
 *  @author    Wang Xiaotao<wangxiaotao1980@gmail.com>
 ******************************************************************************/

#include "CurlHttpBaseClass.h"
#include "HttpAccess/HttpAccessUtils.h"


#include <cassert>
#include <algorithm>
#include <string>

#include "boost/algorithm/string.hpp"

/******************************************************************************/
CPS_HTTPACCESS_NAMESPACE_BEGIN
// -----------------------------------------------------------------------------
//  CurlHttpBaseClass: Public, Constructor

CurlHttpBaseClass::CurlHttpBaseClass()
    : CurlWrapperClass()
    , m_pcurl_list(CPS_HTTPACCESS_NULL_PTR)
    , m_isSettingurlstr(false)
    , m_isSettingRequestHeaderStrs(false)
    , m_isSettingcurltimeOut(false)
    , m_isSettingProxyInfo(false)
    , m_isSettingUploadBandWidth(false)
    , m_isSettingDownloadBandWidth(false)
    , m_isSettingUserAgent(false)
    , m_urlstr()
    , m_RequestHeaderStrs()                       //存储htpp(s)请求头信息
    , m_curltimeOut(HTTP_NO_TIMEOUT)              //超时设定,单位:秒,为设定存在默认值 0 , 不限速
    , m_userAgent()
    , m_pSmartProxyInfo(new ProxyInfo)            //代理信息
    , m_uploadBandWidth ( HTTP_NO_SPEED_LIMITED )   //上传速率限制  0 代表无限制
    , m_downloadBandWidth( HTTP_NO_SPEED_LIMITED )  //下载速率限制  0 代表无限制
    , m_ResponeHeaderStr()
{}
// -----------------------------------------------------------------------------
//  CurlHttpBaseClass: Public, Destructor

CurlHttpBaseClass::~CurlHttpBaseClass()
{
    // 释放可能需要释放的资源
    ::curl_slist_free_all(m_pcurl_list);
}

// -----------------------------------------------------------------------------
// public   
void CurlHttpBaseClass::setURL( const char* pUrl )
{
    assert(pUrl);
    m_isSettingurlstr = true;
    m_urlstr = pUrl;

}

// -----------------------------------------------------------------------------
// public   
void CurlHttpBaseClass::setHttpRequestHeaders( const char** ppHeader )
{
    assert(ppHeader);

    //清空以前的设置
    m_RequestHeaderStrs.clear();

    m_isSettingRequestHeaderStrs = true;
    while(0 != (*ppHeader))
    {
        m_RequestHeaderStrs.push_back(std::string(*ppHeader));
        ++ppHeader;
    }

    ::curl_slist_free_all(m_pcurl_list);
    m_pcurl_list = CPS_HTTPACCESS_NULL_PTR;

    for (std::vector<std::string>::const_iterator 
        itor = m_RequestHeaderStrs.begin(); itor != m_RequestHeaderStrs.end(); ++itor)
    {
        m_pcurl_list = curl_slist_append(m_pcurl_list, itor->c_str());
    }

}

// -----------------------------------------------------------------------------
// public   
void CurlHttpBaseClass::setHttpRequestHeaders( const std::vector<std::string> headers )
{
    m_isSettingRequestHeaderStrs = true;
    m_RequestHeaderStrs = headers;
    
    ::curl_slist_free_all(m_pcurl_list);

    m_pcurl_list = CPS_HTTPACCESS_NULL_PTR;

    for (std::vector<std::string>::const_iterator 
        itor = m_RequestHeaderStrs.begin(); itor != m_RequestHeaderStrs.end(); ++itor)
    {
        m_pcurl_list = curl_slist_append(m_pcurl_list, itor->c_str());
    }
}

// -----------------------------------------------------------------------------
// public   
void CurlHttpBaseClass::setTimeout( UInt32 timeout )
{
    m_isSettingcurltimeOut = true;
    m_curltimeOut = timeout;
}

// -----------------------------------------------------------------------------
// public   
void CurlHttpBaseClass::setProxyInfo( const ProxyInfo& proxyInfo )
{
    m_isSettingProxyInfo = true;

    m_pSmartProxyInfo->m_proxyMode  = proxyInfo.m_proxyMode;
    m_pSmartProxyInfo->m_ip         = proxyInfo.m_ip;
    m_pSmartProxyInfo->m_port       = proxyInfo.m_port;
    m_pSmartProxyInfo->m_isUsingPwd = proxyInfo.m_isUsingPwd;
    m_pSmartProxyInfo->m_passwd     = proxyInfo.m_passwd;
    m_pSmartProxyInfo->m_user       = proxyInfo.m_user;
}

// -----------------------------------------------------------------------------
// public   
void CurlHttpBaseClass::setUploadBandWidth( UInt32 unBandWidth )
{
    m_isSettingUploadBandWidth = true;
    m_uploadBandWidth = unBandWidth;
}

// -----------------------------------------------------------------------------
// public   
void CurlHttpBaseClass::setDownLoadBandWidth( UInt32 unBandWidth )
{
    m_isSettingDownloadBandWidth = true;
    m_downloadBandWidth = unBandWidth;
}


// -----------------------------------------------------------------------------
// public   
void CurlHttpBaseClass::setUserAgent( const char* pUserAgent )
{
    m_isSettingUserAgent = true;
    m_userAgent = pUserAgent;
}

// -----------------------------------------------------------------------------
// public   
const char* CurlHttpBaseClass::getURL() const
{
    return m_urlstr.c_str();
}

// -----------------------------------------------------------------------------
// public   
const std::vector<std::string>& CurlHttpBaseClass::getHttpRequestHeaders() const
{
    return m_RequestHeaderStrs;
}

// -----------------------------------------------------------------------------
// public   
const UInt32 CurlHttpBaseClass::getTimeout() const
{
    return m_curltimeOut;
}

// -----------------------------------------------------------------------------
// public   
const ProxyInfo& CurlHttpBaseClass::getProxyInfo() const
{
    return *m_pSmartProxyInfo;
}

// -----------------------------------------------------------------------------
// public   
UInt32 CurlHttpBaseClass::getUploadBandWidth() const
{
    return m_uploadBandWidth;
}

// -----------------------------------------------------------------------------
// public   
UInt32 CurlHttpBaseClass::getDownLoadBandWidth() const
{
    return m_downloadBandWidth;
}

// -----------------------------------------------------------------------------
// public   
const char* CurlHttpBaseClass::getUserAgent() const
{
    return m_userAgent.c_str();
}


// -----------------------------------------------------------------------------
// public   
HttpAccessCode CurlHttpBaseClass::getResponseHttpCode()
{
    HttpAccessCode resultCode = HTPPACCESS_NO_HTTP_RETURN_CODE;

    UInt32 httpcode = 0U;

    CURLcode curlresult = ::curl_easy_getinfo(m_pCURL, CURLINFO_RESPONSE_CODE , &httpcode);   

    if ( curlresult == CURLE_OK )
    {
        resultCode = httpcode | HTTP_STANDARD_FLAG;
    }
    else
    {
        m_errorMessage = getErrorCodeInfo(curlresult);
    }

    return resultCode;
}

// -----------------------------------------------------------------------------
// public   
const std::string& CurlHttpBaseClass::getResponeHeader() const
{
    return m_ResponeHeaderStr;
}


// -----------------------------------------------------------------------------
// public   
HttpAccessCode CurlHttpBaseClass::processCurlHttp()
{

    HttpAccessCode resultCode = HTTPACCESS_OK;


    clear_up_before_setting();

    // 设定 curl
    resultCode = InitCurl();
    if (HTTPACCESS_OK != resultCode)
    {
        return resultCode;
    }


    curl_set_url_address();                       // 设定   CURLOPT_URL

    curl_set_upload_speed();                      // 设定   CURLOPT_MAX_SEND_SPEED_LARGE
    curl_set_download_speed();                    // 设定   CURLOPT_MAX_RECV_SPEED_LARGE
    curl_set_timeout();                           // 设定   CURLOPT_TIMEOUT
    curl_set_http_request_header();               // 设定   CURLOPT_HTTPHEADER
    curl_set_proxy();                             // 设定   代理规则
    curl_set_protocol_https();                    // 设定   http协议
    curl_set_User_Agent();                        // 设定   User Agent

    curl_set_write_respone_header_function();     // 设定   头函数 
    curl_set_write_response_body_function();      // http 请求返回body的函数，有可能是写入文件
    curl_set_http_put_body_function();            // http put 请求的body数据
    curl_set_http_post_body_function();           // http post 请求的body数据
    curl_set_progress_function();                 // 进度　设定

    curl_set_DIY();                               // 自定义设置

    resultCode  = perform_curl_http();

    clear_up_resource();

    return resultCode;
}


// -----------------------------------------------------------------------------
// protected   
void CurlHttpBaseClass::curl_set_url_address()
{
    assert(0 != m_pCURL);
    assert(!m_urlstr.empty());
    if (true == m_isSettingurlstr)
    {
        ::curl_easy_setopt(m_pCURL, CURLOPT_URL, m_urlstr.c_str());
        m_isSettingurlstr = false;
    }
}

// -----------------------------------------------------------------------------
// protected   
void CurlHttpBaseClass::curl_set_upload_speed()
{
    assert( 0 != m_pCURL);
    if (true == m_isSettingUploadBandWidth)
    {
        ::curl_easy_setopt(m_pCURL, CURLOPT_MAX_SEND_SPEED_LARGE, m_uploadBandWidth* 1024);
        m_isSettingUploadBandWidth = false;
    }
}

// -----------------------------------------------------------------------------
// protected   
void CurlHttpBaseClass::curl_set_download_speed()
{
    assert(0 != m_pCURL);
     if (true == m_isSettingDownloadBandWidth)
     {
         ::curl_easy_setopt(m_pCURL, CURLOPT_MAX_RECV_SPEED_LARGE, m_downloadBandWidth * 1024);
         m_isSettingDownloadBandWidth = false;
     }
}

// -----------------------------------------------------------------------------
// protected   
void CurlHttpBaseClass::curl_set_timeout()
{
    assert(0 != m_pCURL);
    if (true == m_isSettingcurltimeOut)
    {
        ::curl_easy_setopt(m_pCURL, CURLOPT_TIMEOUT, m_curltimeOut);
        m_isSettingcurltimeOut = false;
    }
}

// -----------------------------------------------------------------------------
// protected   
void CurlHttpBaseClass::curl_set_http_request_header()
{
    assert(0 != m_pCURL);
    if (true == m_isSettingRequestHeaderStrs)
    {
        ::curl_easy_setopt(m_pCURL, CURLOPT_HTTPHEADER, m_pcurl_list);
        m_isSettingRequestHeaderStrs = false;
    }
}


// -----------------------------------------------------------------------------
// protected   
void CurlHttpBaseClass::curl_set_proxy()
{
    //CURLOPT_PROXY
    //CURLOPT_RETURNTRANSFER

    assert(m_pCURL);
    // 设定代理模式，
    switch (m_pSmartProxyInfo->m_proxyMode)
    {
    case NoProxy:// No Using Proxy
        // 设定 IP地址和端口号
        ::curl_easy_setopt(m_pCURL, CURLOPT_PROXY, "");
        ::curl_easy_setopt(m_pCURL, CURLOPT_PROXYPORT, 1080L);
        return;
        break;
    case ProxyHTTP:             // Using the HTTP Proxy
        ::curl_easy_setopt(m_pCURL, CURLOPT_PROXYTYPE, CURLPROXY_HTTP);
        break;
    case ProxySock4:           // Using the Scok4
        ::curl_easy_setopt(m_pCURL, CURLOPT_PROXYTYPE, CURLPROXY_SOCKS4);
        break;
    case ProxySock5:           // Using the Scok5
        ::curl_easy_setopt(m_pCURL, CURLOPT_PROXYTYPE, CURLPROXY_SOCKS5);
        break;
    default: //
        ::curl_easy_setopt(m_pCURL, CURLOPT_PROXYTYPE, CURLPROXY_HTTP);
        break;
    }
    // 设定 IP地址和端口号
    ::curl_easy_setopt(m_pCURL, CURLOPT_PROXY, m_pSmartProxyInfo->m_ip.c_str());
    ::curl_easy_setopt(m_pCURL, CURLOPT_PROXYPORT, m_pSmartProxyInfo->m_port);

    // 设定代理密码
    if (m_pSmartProxyInfo->m_isUsingPwd)
    {
        ::curl_easy_setopt(m_pCURL, CURLOPT_PROXYUSERNAME, m_pSmartProxyInfo->m_user.c_str());
         ::curl_easy_setopt(m_pCURL, CURLOPT_PROXYPASSWORD, m_pSmartProxyInfo->m_passwd.c_str());
    }
    else
    {
        ::curl_easy_setopt(m_pCURL, CURLOPT_PROXYUSERNAME, "");
        ::curl_easy_setopt(m_pCURL, CURLOPT_PROXYPASSWORD, "");
    }

    // 对 https 协议的设定

    if (is_curl_using_https())
    {
        ::curl_easy_setopt(m_pCURL, CURLOPT_HTTPPROXYTUNNEL, 1);
    }
    else
    {
        ::curl_easy_setopt(m_pCURL, CURLOPT_HTTPPROXYTUNNEL, 0);
    }
}


// -----------------------------------------------------------------------------
// protected   
void CurlHttpBaseClass::curl_set_User_Agent()
{
    if (true == m_isSettingUserAgent)
    {
        ::curl_easy_setopt(m_pCURL, CURLOPT_USERAGENT, m_userAgent.c_str());
        m_isSettingUserAgent = false;
    }
}


// -----------------------------------------------------------------------------
// protected   virtual 不设定任何值，等待子类完成
void CurlHttpBaseClass::curl_set_DIY()
{
    #ifdef _DEBUG
        ::curl_easy_setopt(m_pCURL, CURLOPT_VERBOSE, 1);
        //::curl_easy_setopt(m_pCURL, CURLOPT_HEADER, 1L);
    #endif
}


// -----------------------------------------------------------------------------
// protected   
HttpAccessCode CurlHttpBaseClass::perform_curl_http()
{

    HttpAccessCode resultCode = HTTPACCESS_OK;

    CURLcode curlresult = ::curl_easy_perform(m_pCURL);
    if (CURLE_OK != curlresult)
    {
        resultCode = CURL_FLAG | curlresult;
        m_errorMessage = getErrorCodeInfo(resultCode);
    }

    return resultCode;
}


// -----------------------------------------------------------------------------
// protected
void CurlHttpBaseClass::curl_set_protocol_https()
{
    if (is_curl_using_https())
    {
        curl_easy_setopt(m_pCURL, CURLOPT_PROTOCOLS, CURLPROTO_HTTPS);
        // 下面这个需要设定与否，需要测试
        curl_easy_setopt(m_pCURL, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(m_pCURL, CURLOPT_SSL_VERIFYHOST, 0L);
    }
    else
    {  
        curl_easy_setopt(m_pCURL, CURLOPT_PROTOCOLS, CURLPROTO_HTTP); 
    }
}


// -----------------------------------------------------------------------------
// protected   
void CurlHttpBaseClass::curl_set_write_respone_header_function()
{
    assert(m_pCURL != 0);
    curl_easy_setopt(m_pCURL, CURLOPT_HEADERFUNCTION, CurlHttpBaseClass::write_respone_header_data);
    curl_easy_setopt(m_pCURL, CURLOPT_HEADERDATA, &m_ResponeHeaderStr);
}

// -----------------------------------------------------------------------------
// protected   
bool CurlHttpBaseClass::is_curl_using_https() const
{
    assert(!m_urlstr.empty());

    return boost::algorithm::istarts_with(m_urlstr, std::string("https://"));
}

// -----------------------------------------------------------------------------
// protected   virtual 
void CurlHttpBaseClass::clear_up_resource()
{}

// -----------------------------------------------------------------------------
// protected   virtual 
void CurlHttpBaseClass::clear_up_before_setting()
{

    m_ResponeHeaderStr.clear();
    // 清空错误信息
    m_errorMessage.clear();
}

// -----------------------------------------------------------------------------
// private  static  
size_t CurlHttpBaseClass::write_respone_header_data( void* ptr
                                                   , size_t msize
                                                   , size_t n 
                                                   , std::string* pStr )
{
    assert(0 != pStr);
    std::string* strStream = pStr;
    try 
    {
        strStream->append(static_cast<const char*>(ptr), msize * n);
    }
    catch(...) 
    {
        return 0;
    }

    return msize * n;
}


CPS_HTTPACCESS_NAMESPACE_END
// 
// -----------------------------------------------------------------------------
