/*******************************************************************************
 *  @file      CurlHttpBaseClass.h 2013\3\8 13:07:47 $
 *  @author    Wang Xiaotao<wangxiaotao1980@gmail.com>
 
 ******************************************************************************/

#ifndef CURLHTTPBASECLASS_2A999A14_4790_4104_9C6F_349FF631F40D_H__
#define CURLHTTPBASECLASS_2A999A14_4790_4104_9C6F_349FF631F40D_H__

#include "CurlWrapperClass.h"

#include <string>
#include <vector>

// 设定使用C++ 智能指针
#if defined (CPS_NO_CXX11_SMART_PTR)
    #include "boost/scoped_ptr.hpp"
#else
    #include <memory>
    #include <functional>
#endif

/******************************************************************************/

CPS_HTTPACCESS_NAMESPACE_BEGIN

/**
 * The class <code>CurlHttpBaseClass</code>
 *
 */
class CurlHttpBaseClass 
    : public CurlWrapperClass
{
public:
    /** @name Constructors and Destructor*/

    //@{
    /**
     * No Parameter Constructor 
     */
    CurlHttpBaseClass();
    /**
     * Destructor
     */
    ~CurlHttpBaseClass();
    //@}

public:
    /** @name Setter Methods*/
    //@{
    /**
     * 设定要访问的url
     *
     * @param   const char * pUrl 字符串
     * @return  void
     */
    void setURL(const char* pUrl);

    /**
     * 设定Http(s)请求头
     *
     * @param  const char ** ppHeader           http 头列表 C形式
     * @return  void
     * @exception
     */
    void setHttpRequestHeaders(const char** ppHeader);

    /**
     *  设定Http(s)请求头
     *
     * @param   const std::vector<std::string> headers http 头列表 C++ STL容器形式
     * @return  void
     * @exception
     */
    void setHttpRequestHeaders(const std::vector<std::string> headers);

    /**
     * 设定Http请求超时时间
     *
     * @param   UInt32 timeout               超时时间，单位为秒
     * @return  void
     * @exception <code></code>
     */
    void setTimeout(UInt32 timeout);
    /**
     * 设定代理访问信息
     *
     * @param   const ProxyInfo & proxyInfo       要设定的代理信息
     * @return  void
     * @exception <code></code>
     */
    void setProxyInfo(const ProxyInfo& proxyInfo);

    /**
     * 设定curl最大上传速率
     *
     * @param   UInt32 unBandWidth 上传速率 单位 k/s
     * @return  void
     * @exception there is no any exception to throw.
     */
    void setUploadBandWidth(UInt32 unBandWidth);

    /**
     * 设定curl最大下载速率
     *
     * @param   UInt32 unBandWidth  下载速率 单位 k/s
     * @return  void
     * @exception there is no any exception to throw.
     */
    void setDownLoadBandWidth(UInt32 unBandWidth);


    void setUserAgent(const char* pUserAgent);

    //@}
public:
    /** @name Getter Methods*/
    //@{
    /**
     * 得到访问的url
     *
     * @return  const char* 访问Url字字符串
     * @exception <code></code>
     */
    const char* getURL()                                    const;
    const std::vector<std::string>& getHttpRequestHeaders() const;
    const UInt32  getTimeout()                              const;
    const ProxyInfo&  getProxyInfo()                        const;
    UInt32 getUploadBandWidth()                             const;
    UInt32 getDownLoadBandWidth()                           const;
    const char* getUserAgent()                              const;
   /**
     * 解析Http请求的返回码值
     *
     * @return  HttpAccessCode  http请求返回码，譬如(200，401， 502) | HTTP_STANDARD_FLAG
     *                          如果没有值返回 HTPPACCESS_NO_HTTP_RETURN_CODE
     *                             
     */
    HttpAccessCode getResponseHttpCode();

    /**
     * 得到http请求响应的头数据
     *
     * @return  std::string& http请求返回的头数据
     */
    const std::string& getResponeHeader() const;
    //@}
public:
    /** @name Access Methods*/
    //@{
    /**
     * 执行Http请求
     * 
     * @return HttpAccessCode
     *
     */
    HttpAccessCode processCurlHttp();
    //@}
protected:
    void curl_set_url_address();                       ///< 设定   CURLOPT_URL
    void curl_set_upload_speed();                      ///< 设定   CURLOPT_MAX_SEND_SPEED_LARGE
    void curl_set_download_speed();                    ///< 设定   CURLOPT_MAX_RECV_SPEED_LARGE
    void curl_set_timeout();                           ///< 设定   CURLOPT_TIMEOUT
    void curl_set_http_request_header();               ///< 设定   CURLOPT_HTTPHEADER
    void curl_set_proxy();                             ///< 设定   代理规则
    void curl_set_User_Agent();                        ///< 设定   UserAgent
    void curl_set_protocol_https();                    ///< 设定   http协议


    void curl_set_write_respone_header_function();     // 设定   CURLOPT_HEADERFUNCTION,CURLOPT_HEADERDATA

    virtual void curl_set_write_response_body_function() = 0; // http 请求返回body的函数，有可能是写入文件
    virtual void curl_set_http_put_body_function()       = 0; // http put 请求的body数据
    virtual void curl_set_http_post_body_function()      = 0; // http post 请求的body数据
    virtual void curl_set_progress_function()            = 0; // 进程 设定

    virtual void curl_set_DIY();                       // 自定义设定
    virtual HttpAccessCode perform_curl_http();        // 发出请求 ::curl_easy_perform(m_pCURL)



protected: // 辅助函数
    bool is_curl_using_https() const;                 // 判断 m_urlstr 是不是 https 协议

    virtual void clear_up_resource();                 // 清空curl资源
    virtual void clear_up_before_setting();           // 在curl设定之前再给个清理的机会

private:
    // 回调函数，http(s)请求响应的头信息通过此写入变量
    static size_t write_respone_header_data( void* ptr
                                           , size_t msize
                                           , size_t n
                                           , std::string* pStr);

private: // 存储辅助的变量
    curl_slist*                  m_pcurl_list;        // 用于转化写入m_RequestHeaderStrs 到 curl
    bool                         m_isSettingurlstr;
    bool                         m_isSettingRequestHeaderStrs;
    bool                         m_isSettingcurltimeOut;
    bool                         m_isSettingProxyInfo;
    bool                         m_isSettingUploadBandWidth;
    bool                         m_isSettingDownloadBandWidth;
    bool                         m_isSettingUserAgent;

private: // 存储http请求信息变量
    std::string                  m_urlstr;            ///<http(s)要访问的url地址
    std::vector<std::string>     m_RequestHeaderStrs; ///<存储htpp(s)请求头信息
    UInt32                       m_curltimeOut;       ///<超时设定,单位:秒,为设定存在默认值0s，表示不限速
    std::string                  m_userAgent;         ///<User Agent
    // 设定使用C++ 智能指针,不支持C++11标准，使用boost
#if defined (CPS_NO_CXX11_SMART_PTR)
    boost::scoped_ptr<ProxyInfo>   m_pSmartProxyInfo;
#else
    std::unique_ptr<ProxyInfo>     m_pSmartProxyInfo;
#endif
    UInt32                   m_uploadBandWidth;        ///<   上传速率限制  0 代表无限制
    UInt32                   m_downloadBandWidth;      ///<   下载速率限制  0 代表无限制
private://存储http请求返回信息

    std::string                  m_ResponeHeaderStr;   ///< 存储http(s)请求返回头信息

};

CPS_HTTPACCESS_NAMESPACE_END

/******************************************************************************/
#endif// CURLHTTPBASECLASS_2A999A14_4790_4104_9C6F_349FF631F40D_H__
