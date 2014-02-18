/******************************************************************************* 
 *  @file      QiniuRemoteBatchFilesImpl.cpp 2013\11\25 17:27:31 $
 *  @author    Wang Xiaotao<wangxiaotao1980@gmail.com> (中文编码测试)
 ******************************************************************************/

#include "QiniuRemoteBatchFilesImpl.h"
#include "../QiniuInternalConfig.h"

#include "Qiniu/QiniuUtils.h"
#include "Qiniu/QiniuStrcut.h"
#include "QiniuMisc.h"


namespace 
{
    const std::string URL_FILE_INFO("/stat/");
    const std::string URL_FILE_MOVE("/move/");
    const std::string URL_FILE_COPY("/copy/");
    const std::string URL_FILE_DELETE("/delete/");

    const std::string URL_FILE_BATCH("/batch");

    const std::string URL_RS_BATCH_HTTPS(QINIU_NAMESPACE::HTTPS_QINIU_RS_HOST + URL_FILE_BATCH);
    const std::string URL_RS_BATCH_HTTP(QINIU_NAMESPACE::HTTP_QINIU_RS_HOST   + URL_FILE_BATCH);
}


QINIU_NAMESPACE_BEGIN

// -----------------------------------------------------------------------------
//  QiniuRemoteBatchFilesImpl: Public, Constructor

QiniuRemoteBatchFilesImpl::QiniuRemoteBatchFilesImpl()
: m_CurlPost()
, m_isUsingHttps(false)
, m_lastErrorInfo()
{
    m_CurlPost.setUserAgent(QiniuUtils::getUserAgent());
}
// -----------------------------------------------------------------------------
//  QiniuRemoteBatchFilesImpl: Public, Destructor

QiniuRemoteBatchFilesImpl::~QiniuRemoteBatchFilesImpl()
{}


// -----------------------------------------------------------------------------
//  virtual  public  
void QiniuRemoteBatchFilesImpl::setUsingHttps( bool isUsingHttps )
{
    m_isUsingHttps = isUsingHttps;
}
// -----------------------------------------------------------------------------
// class : QiniuRemoteBatchFilesImpl inherit from : IQiniuRemoteFile
//  virtual  public  

bool QiniuRemoteBatchFilesImpl::getUsingHttps()
{
    return m_isUsingHttps;
}
// -----------------------------------------------------------------------------
//  virtual  public  

void QiniuRemoteBatchFilesImpl::setProxyInfo( const ProxyInfo& proxyInfo )
{
    m_CurlPost.setProxyInfo((CPS_HTTPACCESS_NAMESPACE::ProxyInfo&)proxyInfo);
}

// -----------------------------------------------------------------------------
//  virtual  public  

const ProxyInfo& QiniuRemoteBatchFilesImpl::getProxyInfo()
{
    return (const ProxyInfo&)(m_CurlPost.getProxyInfo());
}

// -----------------------------------------------------------------------------
//  virtual  public  
void QiniuRemoteBatchFilesImpl::setTimeout( UInt32 timeout )
{
    m_CurlPost.setTimeout(timeout);
}

// -----------------------------------------------------------------------------
//  virtual  public  
UInt32 QiniuRemoteBatchFilesImpl::getTimeout()
{
    return m_CurlPost.getTimeout();
}
// -----------------------------------------------------------------------------
// class :  inherit from : 
//  virtual  public  
QiniuCode QiniuRemoteBatchFilesImpl::getRemoteBatchFilesInfo( IN const QiniuToken& token, 
                                                              IN const QiniuBucketKey* bucketKeys, 
                                                              IN const int bucketKeysLen, 
                                                              OUT std::string& jsonstr )
{
    QiniuCode returnCode = QINIU_OK;

    const std::string& url = m_isUsingHttps ? URL_RS_BATCH_HTTPS
                                            : URL_RS_BATCH_HTTP;
    m_CurlPost.setURL(url.c_str());

    std::string body;
    for (int i = 0; i < bucketKeysLen; ++i)
    {
        std::string bucketKeyName(std::string(bucketKeys[i].m_pBucketName) + ":" + bucketKeys[i].m_pKeyName);
        std::string bucketKeyNameBase64;
        Base64_Encode(bucketKeyName.c_str(), bucketKeyName.size(), bucketKeyNameBase64);
        if (0 == i)
        {
            body += (std::string("op=/stat/") + bucketKeyNameBase64);
        }
        else 
        {
            body += (std::string("&op=/stat/") + bucketKeyNameBase64);
        }
    }

    m_CurlPost.setPostBody(static_cast<const void*>(body.c_str()), body.size());

    std::string authStr = getAuthStr(token, (unsigned char*)URL_FILE_BATCH.c_str(), URL_FILE_BATCH.size(),
                                            (unsigned char*)body.c_str(), body.size());
    std::string authStrBase64;
    Base64_Encode(authStr.c_str(), authStr.size(), authStrBase64);



    std::vector<std::string> vectorHeader;
    vectorHeader.push_back(std::string("application/x-www-form-urlencoded"));
    vectorHeader.push_back(std::string("Authorization: QBox ") + token.m_access_key + ":" + authStrBase64);
    m_CurlPost.setHttpRequestHeaders(vectorHeader);

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
// class : QiniuRemoteBatchFilesImpl inherit from : IQiniuRemoteBatchFiles
//  virtual  public  
QiniuCode QiniuRemoteBatchFilesImpl::moveRemoteBatchFiles( IN  const QiniuToken& token, 
                                                           IN  const QiniuSrcAndDestBucketKey* bucketKeys, 
                                                           IN  const int bucketKeysLen, 
                                                           OUT std::string& jsonstr )
{
    QiniuCode returnCode = QINIU_OK;

    const std::string& url = m_isUsingHttps ? URL_RS_BATCH_HTTPS
                                            : URL_RS_BATCH_HTTP;
    m_CurlPost.setURL(url.c_str());

    std::string body;

    for (int i = 0; i < bucketKeysLen; ++i)
    {
        std::string bucketKeyNameSrc(std::string(bucketKeys[i].m_pBucketNameSrc) + ":" + bucketKeys[i].m_pKeyNameSrc);
        std::string bucketKeyNameSrcBase64;
        Base64_Encode(bucketKeyNameSrc.c_str(), bucketKeyNameSrc.size(), bucketKeyNameSrcBase64);

        std::string bucketKeyNameDest(std::string(bucketKeys[i].m_pBucketNameDest) + ":" + bucketKeys[i].m_pKeyNameDest);
        std::string bucketKeyNameDestBase64;
        Base64_Encode(bucketKeyNameDest.c_str(), bucketKeyNameDest.size(), bucketKeyNameDestBase64);


        if (0 == i)
        {
            body += (std::string("op=/move/") + bucketKeyNameSrcBase64 + "/" + bucketKeyNameDestBase64);
        }
        else 
        {
            body += (std::string("&op=/move/") + bucketKeyNameSrcBase64 + "/" + bucketKeyNameDestBase64);
        }
    }

    m_CurlPost.setPostBody(static_cast<const void*>(body.c_str()), body.size());

    std::string authStr = getAuthStr(token, (unsigned char*)URL_FILE_BATCH.c_str(), URL_FILE_BATCH.size(),
        (unsigned char*)body.c_str(), body.size());
    std::string authStrBase64;
    Base64_Encode(authStr.c_str(), authStr.size(), authStrBase64);



    std::vector<std::string> vectorHeader;
    vectorHeader.push_back(std::string("application/x-www-form-urlencoded"));
    vectorHeader.push_back(std::string("Authorization: QBox ") + token.m_access_key + ":" + authStrBase64);
    m_CurlPost.setHttpRequestHeaders(vectorHeader);

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
// class : QiniuRemoteBatchFilesImpl inherit from : IQiniuRemoteBatchFiles
//  virtual  public  

QINIU_NAMESPACE::QiniuCode QiniuRemoteBatchFilesImpl::copyRemoteBatchFiles( IN const QiniuToken& token, 
                                                                            IN const QiniuSrcAndDestBucketKey* bucketKeys, 
                                                                            IN const int bucketKeysLen, 
                                                                            OUT std::string& jsonstr )
{
    QiniuCode returnCode = QINIU_OK;

    const std::string& url = m_isUsingHttps ? URL_RS_BATCH_HTTPS
        : URL_RS_BATCH_HTTP;
    m_CurlPost.setURL(url.c_str());

    std::string body;

    for (int i = 0; i < bucketKeysLen; ++i)
    {
        std::string bucketKeyNameSrc(std::string(bucketKeys[i].m_pBucketNameSrc) + ":" + bucketKeys[i].m_pKeyNameSrc);
        std::string bucketKeyNameSrcBase64;
        Base64_Encode(bucketKeyNameSrc.c_str(), bucketKeyNameSrc.size(), bucketKeyNameSrcBase64);

        std::string bucketKeyNameDest(std::string(bucketKeys[i].m_pBucketNameDest) + ":" + bucketKeys[i].m_pKeyNameDest);
        std::string bucketKeyNameDestBase64;
        Base64_Encode(bucketKeyNameDest.c_str(), bucketKeyNameDest.size(), bucketKeyNameDestBase64);


        if (0 == i)
        {
            body += (std::string("op=/copy/") + bucketKeyNameSrcBase64 + "/" + bucketKeyNameDestBase64);
        }
        else 
        {
            body += (std::string("&op=/copy/") + bucketKeyNameSrcBase64 + "/" + bucketKeyNameDestBase64);
        }
    }

    m_CurlPost.setPostBody(static_cast<const void*>(body.c_str()), body.size());

    std::string authStr = getAuthStr(token, (unsigned char*)URL_FILE_BATCH.c_str(), URL_FILE_BATCH.size(),
        (unsigned char*)body.c_str(), body.size());
    std::string authStrBase64;
    Base64_Encode(authStr.c_str(), authStr.size(), authStrBase64);



    std::vector<std::string> vectorHeader;
    vectorHeader.push_back(std::string("application/x-www-form-urlencoded"));
    vectorHeader.push_back(std::string("Authorization: QBox ") + token.m_access_key + ":" + authStrBase64);
    m_CurlPost.setHttpRequestHeaders(vectorHeader);

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

QINIU_NAMESPACE::QiniuCode QiniuRemoteBatchFilesImpl::deleteRemoteBatchFiles( IN const QiniuToken& token, 
                                                                              IN const QiniuBucketKey* bucketKeys,
                                                                              IN const int bucketKeysLen,
                                                                              OUT std::string& jsonstr )
{
    QiniuCode returnCode = QINIU_OK;

    const std::string& url = m_isUsingHttps ? URL_RS_BATCH_HTTPS
        : URL_RS_BATCH_HTTP;
    m_CurlPost.setURL(url.c_str());

    std::string body;
    for (int i = 0; i < bucketKeysLen; ++i)
    {
        std::string bucketKeyName(std::string(bucketKeys[i].m_pBucketName) + ":" + bucketKeys[i].m_pKeyName);
        std::string bucketKeyNameBase64;
        Base64_Encode(bucketKeyName.c_str(), bucketKeyName.size(), bucketKeyNameBase64);
        if (0 == i)
        {
            body += (std::string("op=/delete/") + bucketKeyNameBase64);
        }
        else 
        {
            body += (std::string("&op=/delete/") + bucketKeyNameBase64);
        }
    }

    m_CurlPost.setPostBody(body.data(), body.size());

    std::string authStr = getAuthStr(token, (unsigned char*)URL_FILE_BATCH.c_str(), URL_FILE_BATCH.size(),
        (unsigned char*)body.c_str(), body.size());
    std::string authStrBase64;
    Base64_Encode(authStr.c_str(), authStr.size(), authStrBase64);



    std::vector<std::string> vectorHeader;
    vectorHeader.push_back(std::string("application/x-www-form-urlencoded"));
    vectorHeader.push_back(std::string("Authorization: QBox ") + token.m_access_key + ":" + authStrBase64);
    m_CurlPost.setHttpRequestHeaders(vectorHeader);

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
const char* QiniuRemoteBatchFilesImpl::getLastErrorInfo()
{
    return m_lastErrorInfo.c_str();
}
QINIU_NAMESPACE_END
// 
// -----------------------------------------------------------------------------