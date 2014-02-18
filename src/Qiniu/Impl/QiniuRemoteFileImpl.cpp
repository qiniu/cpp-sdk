/******************************************************************************* 
 *  @file      QiniuRemoteFileImpl.cpp 2013\11\21 14:00:35 $
 *  @author    Wang Xiaotao<wangxiaotao1980@gmail.com> (中文编码测试)
 ******************************************************************************/

#include "QiniuRemoteFileImpl.h"
#include "../QiniuInternalConfig.h"

#include "Qiniu/QiniuUtils.h"
#include "Qiniu/QiniuStrcut.h"
#include "Qiniu/IUpLoadProgress.h"
#include "QiniuMisc.h"

#include "Misc/Misc.h"
#include "../Json/json.h"

#include "boost/smart_ptr.hpp"

#include <time.h>
#include <sstream>
#include <string.h>
namespace 
{
    const std::string URL_FILE_INFO("/stat/");
    const std::string URL_FILE_MOVE("/move/");
    const std::string URL_FILE_COPY("/copy/");
    const std::string URL_FILE_DELETE("/delete/");

    const std::string URL_RS_HOST_HTTPS(QINIU_NAMESPACE::HTTPS_QINIU_RS_HOST);
    const std::string URL_RS_HOST_HTTP(QINIU_NAMESPACE::HTTP_QINIU_RS_HOST);
                                                                
    const std::string URL_RSF_HOST_HTTPS(QINIU_NAMESPACE::HTTPS_QINIU_RSF_HOST);
    const std::string URL_RSF_HOST_HTTP(QINIU_NAMESPACE::HTTP_QINIU_RSF_HOST);

    const std::string URL_UP_HOST_HTTPS(QINIU_NAMESPACE::HTTPS_QINIU_UP_HOST);
    const std::string URL_UP_HOST_HTTP(QINIU_NAMESPACE::HTTP_QINIU_UP_HOST);

    const std::string URL_MAKE_BLOCK_HTTPS(QINIU_NAMESPACE::HTTPS_QINIU_UP_HOST + "/mkblk/");
    const std::string URL_MAKE_BLOCK_HTTP (QINIU_NAMESPACE::HTTP_QINIU_UP_HOST  + "/mkblk/");


    const int REPEATCOUNT = 6;      // 分片上传重复次数
}

QINIU_NAMESPACE_BEGIN

// -----------------------------------------------------------------------------
//  QiniuRemoteFileImpl: Public, Constructor

QiniuRemoteFileImpl::QiniuRemoteFileImpl()
: m_CurlPost()
//, m_CurlPostForm()
, m_isUsingHttps(false)
, m_lastErrorInfo()
{
    m_CurlPost.setUserAgent(QiniuUtils::getUserAgent());
}

// -----------------------------------------------------------------------------
//  QiniuRemoteFileImpl: Public, Destructor

QiniuRemoteFileImpl::~QiniuRemoteFileImpl()
{}

// -----------------------------------------------------------------------------
//  virtual  public  
void QiniuRemoteFileImpl::setUsingHttps( bool isUsingHttps )
{
    m_isUsingHttps = isUsingHttps;
}
// -----------------------------------------------------------------------------
// class : QiniuRemoteFileImpl inherit from : IQiniuRemoteFile
//  virtual  public  

bool QiniuRemoteFileImpl::getUsingHttps()
{
    return m_isUsingHttps;
}
// -----------------------------------------------------------------------------
//  virtual  public  

void QiniuRemoteFileImpl::setProxyInfo( const ProxyInfo& proxyInfo )
{
    m_CurlPost.setProxyInfo((CPS_HTTPACCESS_NAMESPACE::ProxyInfo&)proxyInfo);
}

// -----------------------------------------------------------------------------
//  virtual  public  

const ProxyInfo& QiniuRemoteFileImpl::getProxyInfo()
{
    return (const ProxyInfo&)(m_CurlPost.getProxyInfo());
}

// -----------------------------------------------------------------------------
//  virtual  public  
void QiniuRemoteFileImpl::setTimeout( UInt32 timeout )
{
    m_CurlPost.setTimeout(timeout);
}

// -----------------------------------------------------------------------------
//  virtual  public  
UInt32 QiniuRemoteFileImpl::getTimeout()
{
    return m_CurlPost.getTimeout();
}

QiniuCode QiniuRemoteFileImpl::ListFileNames( IN  const QiniuToken& token,
                                   IN  const char* bucketName,
                                   IN  const char* marker,
                                   IN  const int   sum,
                                   IN  const char* prefix,
                                   OUT std::string& jsonStr)
{
    QiniuCode returnCode = QINIU_OK;
    //清除上次的错误信息
    m_lastErrorInfo.clear();

    std::string markStr;

    std::string hosturl = m_isUsingHttps ? URL_RSF_HOST_HTTPS
                                         : URL_RSF_HOST_HTTP;

    std::string  urlparam = "/list?bucket=";
    urlparam += CPS_MISC_NAMESPACE::utf8urlEncode(bucketName);
    {
        std::stringstream  sstrem;
        sstrem << "&limit=" << sum;
        urlparam += sstrem.str();
    }

    if (marker && (0 != strlen(marker)))
    {
        urlparam += "&marker=";
        urlparam += CPS_MISC_NAMESPACE::utf8urlEncode(marker);
    }
    if (prefix && (0 != strlen(prefix)))
    {
        urlparam += "&prefix=";
        urlparam += CPS_MISC_NAMESPACE::utf8urlEncode(prefix);
    }

    std::string url = hosturl + urlparam;

                                                             

    m_CurlPost.setURL(url.c_str());

    std::string authStr = getAuthStr(token, (unsigned char*)urlparam.c_str(), urlparam.size());
    std::string authStrBase64;                     
    Base64_Encode(authStr.c_str(), authStr.size(), authStrBase64);

    std::vector<std::string> headerVect;
    // 增加签名
    headerVect.push_back(std::string("Authorization: QBox ") + token.m_access_key + ":" + authStrBase64);
    headerVect.push_back("Content-Type: application/x-www-form-urlencoded");


    m_CurlPost.setHttpRequestHeaders(headerVect);

    returnCode = m_CurlPost.processCurlHttp();

    // 此时证明Http已经和服务器交互完毕
    if (CPS_HTTPACCESS_NAMESPACE::HTTPACCESS_OK != returnCode)
    {
        m_lastErrorInfo = m_CurlPost.getLastErrorMessage();
        return returnCode;
    }
    else
    {
        returnCode = m_CurlPost.getResponseHttpCode();
        // 没有解析出 HTTP 返回码
        if (returnCode == CPS_HTTPACCESS_NAMESPACE::HTPPACCESS_NO_HTTP_RETURN_CODE)
        {
            // 错误码信息已经解析完毕
            m_lastErrorInfo = m_CurlPost.getLastErrorMessage();
            return returnCode;
        }
        else
        {   // 正确返回分支 http 状态码为 200
            if (returnCode == (CPS_HTTPACCESS_NAMESPACE::HTTP_STANDARD_FLAG | 200U))
            {
                jsonStr = m_CurlPost.getResponeBody();
                returnCode = QINIU_OK;
            }
            else
            {
                m_lastErrorInfo = m_CurlPost.getResponeBody();
            }
        }
    }

    return returnCode;
}


// -----------------------------------------------------------------------------
// class :  inherit from :   virtual  public  
QiniuCode QiniuRemoteFileImpl::ListAllFileNames( IN const QiniuToken& token, 
                                                 IN const char* bucketName, 
                                                 IN const char* prefix, 
                                                 OUT std::string& jsonStr )
{
    QiniuCode returnCode = QINIU_OK;
    //清除上次的错误信息
    m_lastErrorInfo.clear(); 

    std::string markstr;

    Json::Value root;
    root["items"] = Json::arrayValue;

    do 
    {
        const char* pmark = 0;
        std::string theResultJson;
        if (!markstr.empty())
        {
            pmark = markstr.c_str();
        }
        returnCode = this->ListFileNames(token, bucketName, pmark, 1000, prefix, theResultJson);

        if (returnCode != 0)
        {
            return returnCode;
        }


        Json::Reader reader;
        Json::Value subroot;
        if (!reader.parse(theResultJson, subroot, false))
        {
            return QINIU_JSON_PARSE_ERROR;
        }

        if (subroot.isMember("marker"))
        {   if (subroot["marker"].isString())
            {
                markstr = subroot["marker"].asString();
            }
            else
            {
                markstr.clear();
            }
        }
        else
        {
            markstr.clear();
        }

        if (subroot.isMember("items"))
        {
            if (subroot["items"].isArray())
            {
                for (Json::Value::iterator it = subroot["items"].begin(); it != subroot["items"].end(); ++it)
                {
                       root["items"].append(*it);
                }
            }
        }
    } while (!markstr.empty());

    Json::FastWriter writer;  
    jsonStr = writer.write(root);  

    return returnCode;
}




// ----------------------------------------------------------------------------- 
//  virtual  public  
QiniuCode QiniuRemoteFileImpl::getRemoteFileInfo( IN const QiniuToken&  token,  
                                                  IN const char* bucketName, 
                                                  IN const char* keyName, 
                                                  OUT std::string& jsonstr )
{

    QiniuCode returnCode = QINIU_OK;
    //清除上次的错误信息
    m_lastErrorInfo.clear(); 

    std::string url = m_isUsingHttps ? URL_RS_HOST_HTTPS
                                     : URL_RS_HOST_HTTP;

    std::string urlparam(std::string(bucketName) + ":" + keyName);

    std::string urlparamBase64;
    Base64_Encode(urlparam.c_str(), urlparam.size(), urlparamBase64);

    urlparamBase64 = URL_FILE_INFO + urlparamBase64;

    url += urlparamBase64;

    m_CurlPost.setURL(url.c_str());

    std::string authStr = getAuthStr(token, (unsigned char*)urlparamBase64.c_str(), urlparamBase64.size());
    std::string authStrBase64;
    Base64_Encode(authStr.c_str(), authStr.size(), authStrBase64);

    std::vector<std::string> headerVect;
    // 增加签名
    headerVect.push_back(std::string("Authorization: QBox ") + token.m_access_key + ":" + authStrBase64);

    m_CurlPost.setHttpRequestHeaders(headerVect);


    returnCode = m_CurlPost.processCurlHttp();

    // 此时证明Http已经和服务器交互完毕
    if (CPS_HTTPACCESS_NAMESPACE::HTTPACCESS_OK != returnCode)
    {
        m_lastErrorInfo = m_CurlPost.getLastErrorMessage();
        return returnCode;
    }
    else
    {
        returnCode = m_CurlPost.getResponseHttpCode();
        // 没有解析出 HTTP 返回码
        if (returnCode == CPS_HTTPACCESS_NAMESPACE::HTPPACCESS_NO_HTTP_RETURN_CODE)
        {
            // 错误码信息已经解析完毕
            m_lastErrorInfo = m_CurlPost.getLastErrorMessage();
            return returnCode;
        }
        else
        {   // 正确返回分支 http 状态码为 200
            if (returnCode == (CPS_HTTPACCESS_NAMESPACE::HTTP_STANDARD_FLAG | 200U))
            {
                jsonstr = m_CurlPost.getResponeBody();
                returnCode = QINIU_OK;
            }
            else
            {
                m_lastErrorInfo = m_CurlPost.getResponeBody();
            }
        }
    }

    return returnCode;
}

// -----------------------------------------------------------------------------
// class :  inherit from : 
//  virtual  public  

QINIU_NAMESPACE::QiniuCode QiniuRemoteFileImpl::moveRemoteFile( IN const QiniuToken& token, 
                                                                IN const char* bucketSrc, 
                                                                IN const char* keySrc, 
                                                                IN const char* bucketDest, 
                                                                IN const char* keyDest )
{
    QiniuCode returnCode = QINIU_OK;

    m_lastErrorInfo.clear(); 

    std::string url = m_isUsingHttps ? URL_RS_HOST_HTTPS
        : URL_RS_HOST_HTTP;

    std::string entryURISrc  = std::string(bucketSrc)  + ":" + keySrc;
    std::string entryURISrcBase64;
    Base64_Encode(entryURISrc.c_str(), entryURISrc.size(), entryURISrcBase64);

    std::string entryURIDest = std::string(bucketDest) + ":" + keyDest;
    std::string entryURIDestBase64;
    Base64_Encode(entryURIDest.c_str(), entryURIDest.size(), entryURIDestBase64);

    std::string urlparamBase64(entryURISrcBase64 + "/" + entryURIDestBase64);

    urlparamBase64 = URL_FILE_MOVE + urlparamBase64;

    url += urlparamBase64;

    m_CurlPost.setURL(url.c_str());

    std::string authStr = getAuthStr(token, (unsigned char*)urlparamBase64.c_str(), urlparamBase64.size());
    std::string authStrBase64;
    Base64_Encode(authStr.c_str(), authStr.size(), authStrBase64);

    std::vector<std::string> headerVect;
    // 增加签名
    headerVect.push_back(std::string("Authorization: QBox ") + token.m_access_key + ":" + authStrBase64);

    m_CurlPost.setHttpRequestHeaders(headerVect);


    returnCode = m_CurlPost.processCurlHttp();

    // 此时证明Http已经和服务器交互完毕
    if (CPS_HTTPACCESS_NAMESPACE::HTTPACCESS_OK != returnCode)
    {
        m_lastErrorInfo = m_CurlPost.getLastErrorMessage();
        return returnCode;
    }
    else
    {
        returnCode = m_CurlPost.getResponseHttpCode();
        // 没有解析出 HTTP 返回码
        if (returnCode == CPS_HTTPACCESS_NAMESPACE::HTPPACCESS_NO_HTTP_RETURN_CODE)
        {
            // 错误码信息已经解析完毕
            m_lastErrorInfo = m_CurlPost.getLastErrorMessage();
            return returnCode;
        }
        else
        {   // 正确返回分支 http 状态码为 200
            if (returnCode == (CPS_HTTPACCESS_NAMESPACE::HTTP_STANDARD_FLAG | 200U))
            {
                returnCode = QINIU_OK;
            }
            else
            {
                m_lastErrorInfo = m_CurlPost.getResponeBody();
            }
        }
    }

    return returnCode;
}

// -----------------------------------------------------------------------------
// class : QiniuRemoteFileImpl inherit from : IQiniuRemoteFile
//  virtual  public  

QINIU_NAMESPACE::QiniuCode QiniuRemoteFileImpl::copyRemoteFile( IN const QiniuToken& token, 
                                                                IN const char* bucketSrc, 
                                                                IN const char* keySrc, 
                                                                IN const char* bucketDest, 
                                                                IN const char* keyDest )
{
    QiniuCode returnCode = QINIU_OK;

    m_lastErrorInfo.clear(); 

    std::string url = m_isUsingHttps ? URL_RS_HOST_HTTPS
        : URL_RS_HOST_HTTP;

    std::string entryURISrc  = std::string(bucketSrc)  + ":" + keySrc;
    std::string entryURISrcBase64;
    Base64_Encode(entryURISrc.c_str(), entryURISrc.size(), entryURISrcBase64);

    std::string entryURIDest = std::string(bucketDest) + ":" + keyDest;
    std::string entryURIDestBase64;
    Base64_Encode(entryURIDest.c_str(), entryURIDest.size(), entryURIDestBase64);

    std::string urlparamBase64(entryURISrcBase64 + "/" + entryURIDestBase64);


    urlparamBase64 = URL_FILE_COPY + urlparamBase64;

    url += urlparamBase64;

    m_CurlPost.setURL(url.c_str());

    std::string authStr = getAuthStr(token, (unsigned char*)urlparamBase64.c_str(), urlparamBase64.size());
    std::string authStrBase64;
    Base64_Encode(authStr.c_str(), authStr.size(), authStrBase64);

    std::vector<std::string> headerVect;
    // 增加签名
    headerVect.push_back(std::string("Authorization: QBox ") + token.m_access_key + ":" + authStrBase64);

    m_CurlPost.setHttpRequestHeaders(headerVect);


    returnCode = m_CurlPost.processCurlHttp();

    // 此时证明Http已经和服务器交互完毕
    if (CPS_HTTPACCESS_NAMESPACE::HTTPACCESS_OK != returnCode)
    {
        m_lastErrorInfo = m_CurlPost.getLastErrorMessage();
        return returnCode;
    }
    else
    {
        returnCode = m_CurlPost.getResponseHttpCode();
        // 没有解析出 HTTP 返回码
        if (returnCode == CPS_HTTPACCESS_NAMESPACE::HTPPACCESS_NO_HTTP_RETURN_CODE)
        {
            // 错误码信息已经解析完毕
            m_lastErrorInfo = m_CurlPost.getLastErrorMessage();
            return returnCode;
        }
        else
        {   // 正确返回分支 http 状态码为 200
            if (returnCode == (CPS_HTTPACCESS_NAMESPACE::HTTP_STANDARD_FLAG | 200U))
            {
                returnCode = QINIU_OK;
            }
            else
            {
                m_lastErrorInfo = m_CurlPost.getResponeBody();
            }
        }
    }

    return returnCode;
}
// -----------------------------------------------------------------------------
// class : QiniuRemoteFileImpl inherit from : IQiniuRemoteFile
//  virtual  public  

QINIU_NAMESPACE::QiniuCode QiniuRemoteFileImpl::deleteRemoteFile( IN const QiniuToken& token, 
                                                                  IN const char* bucketName, 
                                                                  IN const char* keyName )
{
    QiniuCode returnCode = QINIU_OK;
    //清除上次的错误信息
    m_lastErrorInfo.clear(); 

    std::string url = m_isUsingHttps ? URL_RS_HOST_HTTPS
                                     : URL_RS_HOST_HTTP;

    std::string urlparam(std::string(bucketName) + ":" + keyName);

    std::string urlparamBase64;
    Base64_Encode(urlparam.c_str(), urlparam.size(), urlparamBase64);

    urlparamBase64 = URL_FILE_DELETE + urlparamBase64;

    url += urlparamBase64;

    m_CurlPost.setURL(url.c_str());

    std::string authStr = getAuthStr(token, (unsigned char*)urlparamBase64.c_str(), urlparamBase64.size());
    std::string authStrBase64;
    Base64_Encode(authStr.c_str(), authStr.size(), authStrBase64);

    std::vector<std::string> headerVect;
    // 增加签名
    headerVect.push_back(std::string("Authorization: QBox ") + token.m_access_key + ":" + authStrBase64);

    m_CurlPost.setHttpRequestHeaders(headerVect);


    returnCode = m_CurlPost.processCurlHttp();

    // 此时证明Http已经和服务器交互完毕
    if (CPS_HTTPACCESS_NAMESPACE::HTTPACCESS_OK != returnCode)
    {
        m_lastErrorInfo = m_CurlPost.getLastErrorMessage();
        return returnCode;
    }
    else
    {
        returnCode = m_CurlPost.getResponseHttpCode();
        // 没有解析出 HTTP 返回码
        if (returnCode == CPS_HTTPACCESS_NAMESPACE::HTPPACCESS_NO_HTTP_RETURN_CODE)
        {
            // 错误码信息已经解析完毕
            m_lastErrorInfo = m_CurlPost.getLastErrorMessage();
            return returnCode;
        }
        else
        {   // 正确返回分支 http 状态码为 200
            if (returnCode == (CPS_HTTPACCESS_NAMESPACE::HTTP_STANDARD_FLAG | 200U))
            {
                returnCode = QINIU_OK;
            }
            else
            {
                m_lastErrorInfo = m_CurlPost.getResponeBody();
            }
        }
    }

    return returnCode;
}


// -----------------------------------------------------------------------------
//  virtual  public  
const char* QiniuRemoteFileImpl::getLastErrorInfo()
{
    return m_lastErrorInfo.c_str();
}


QINIU_NAMESPACE_END
// 
// -----------------------------------------------------------------------------