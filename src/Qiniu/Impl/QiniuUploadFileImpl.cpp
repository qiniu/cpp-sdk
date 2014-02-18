/******************************************************************************* 
 *  @file      QiniuUploadFileImpl.cpp 2013\12\31 11:20:09 $
 *  @author    Wang Xiaotao<wangxiaotao1980@gmail.com>
 ******************************************************************************/

#include "QiniuUploadFileImpl.h"
#include "Qiniu/QiniuUtils.h"
#include "Qiniu/QiniuStrcut.h"
#include "Qiniu/IUpLoadProgress.h"
#include "QiniuMisc.h"

#include "Misc/Misc.h"
#include "../Json/json.h"
#include "IUpLoadProgressDecoration.h"


#include "boost/smart_ptr.hpp"

#include <time.h>
#include <sstream>
// 
// -----------------------------------------------------------------------------

#ifdef  blockBits
#undef  blockBits
#endif

#ifdef blockMask
#undef blockMask
#endif

#ifdef  sliceBits
#undef sliceBits
#endif


#ifdef  sliceMask
#undef sliceMask
#endif

#define	blockBits			22
#define blockMask			((1 << blockBits) - 1)

#define  sliceBits          19
#define  sliceMask          ((1 << sliceBits) - 1)


namespace 
{
    const std::string URL_RS_HOST_HTTPS(QINIU_NAMESPACE::HTTPS_QINIU_RS_HOST);
    const std::string URL_RS_HOST_HTTP(QINIU_NAMESPACE::HTTP_QINIU_RS_HOST);

    const std::string URL_UP_HOST_HTTPS(QINIU_NAMESPACE::HTTPS_QINIU_UP_HOST);
    const std::string URL_UP_HOST_HTTP(QINIU_NAMESPACE::HTTP_QINIU_UP_HOST);

    const std::string URL_MAKE_BLOCK_HTTPS(QINIU_NAMESPACE::HTTPS_QINIU_UP_HOST + "/mkblk/");
    const std::string URL_MAKE_BLOCK_HTTP (QINIU_NAMESPACE::HTTP_QINIU_UP_HOST  + "/mkblk/");


    const int REPEATCOUNT = 6;      // 分片上传重复次数
}


QINIU_NAMESPACE_BEGIN
// -----------------------------------------------------------------------------
// class :  inherit from :    public  
QiniuUploadFileImpl::QiniuUploadFileImpl()
    : m_CurlPost()
    , m_CurlPostForm()
    , m_isUsingHttps(false)
    , m_lastErrorInfo()
{

}

// -----------------------------------------------------------------------------
// class :  inherit from :    public  
QiniuUploadFileImpl::~QiniuUploadFileImpl()
{

}

// -----------------------------------------------------------------------------
// class :  inherit from :    public  
void QiniuUploadFileImpl::setUsingHttps( bool isUsingHttps )
{
    m_isUsingHttps = isUsingHttps;
}
// -----------------------------------------------------------------------------
// class :  inherit from :    public  
bool QiniuUploadFileImpl::getUsingHttps()
{
    return m_isUsingHttps;
}
// -----------------------------------------------------------------------------
// class :  inherit from :    public  
void QiniuUploadFileImpl::setProxyInfo( const ProxyInfo& proxyInfo )
{
    m_CurlPost.setProxyInfo((CPS_HTTPACCESS_NAMESPACE::ProxyInfo&)proxyInfo);
    m_CurlPostForm.setProxyInfo((CPS_HTTPACCESS_NAMESPACE::ProxyInfo&)proxyInfo);;
}
// -----------------------------------------------------------------------------
// class :  inherit from :    public  
const ProxyInfo& QiniuUploadFileImpl::getProxyInfo()
{
    return (const ProxyInfo&)(m_CurlPost.getProxyInfo());
}
// -----------------------------------------------------------------------------
// class :  inherit from :    public  
void QiniuUploadFileImpl::setTimeout( UInt32 timeout )
{
    m_CurlPost.setTimeout(timeout);
    m_CurlPostForm.setTimeout(timeout);
}
// -----------------------------------------------------------------------------
// class :  inherit from :    public  
UInt32 QiniuUploadFileImpl::getTimeout()
{
    return m_CurlPost.getTimeout();
}

// -----------------------------------------------------------------------------
// class :  inherit from :    public  
QiniuCode QiniuUploadFileImpl::uploadFile( IN const QiniuToken& token, 
                                           IN const QiniuPutPolicy& putPolicy, 
                                           IN const QiniuIoPutExtra& ioPutExtra, 
                                           IN const bool isReplaceOldFile, 
                                           IN const char* localFilePath, 
                                           IN IUpLoadProgress* pUploadProcess, 
                                           OUT std::string& jsonstr )
{
    QiniuCode returnCode = QINIU_OK;

    std::string jsonParamStr;
    QiniuUploadFileImpl::setJsonString(putPolicy, isReplaceOldFile, jsonParamStr);
    std::string jsonParamStrBase64;
    Base64_Encode(jsonParamStr.c_str(), jsonParamStr.size(), jsonParamStrBase64);

    std::string authStr = getMacAuthStr(token, (unsigned char*)jsonParamStrBase64.c_str(), jsonParamStrBase64.size());
    std::string authStrBase64;
    Base64_Encode(authStr.c_str(), authStr.size(), authStrBase64);
    authStrBase64 = token.m_access_key + ":" + authStrBase64;


    std::string tokenStr(authStrBase64 + ":" + jsonParamStrBase64);


    FILE* pUploadFile = CPS_MISC_NAMESPACE::fopen_(localFilePath, std::string("rb"));
    // 文件打开失败。
    if (0 == pUploadFile)
    {
        return QINIU_READ_FILE_ERROR;
    }

    struct stat_ st;
    CPS_MISC_NAMESPACE::stat64_(localFilePath, &st);
    UploadInfo info;
    info.m_pFile = pUploadFile;
    info.m_fileSize = static_cast<size_t>(st.st_size); // 这里确认文件大小不会变化
    info.m_fileOff = 0;


    m_CurlPostForm.setURL(m_isUsingHttps ? URL_UP_HOST_HTTPS.c_str() : URL_UP_HOST_HTTP.c_str());
    m_CurlPostForm.setKeyName(putPolicy.m_keyName);
    m_CurlPostForm.setToken(tokenStr);
    m_CurlPostForm.setUploadFileInfo(&info);
    m_CurlPostForm.setIoPutExtra(&ioPutExtra);
    m_CurlPostForm.setUpLoadProcessCallBack(pUploadProcess);

    if (QINIU_NULL_PTR != pUploadProcess)
    {
        time_t timeNow = ::time(0);
        pUploadProcess->OnBeginUploadFile(timeNow, (double)info.m_fileSize, localFilePath);
    }


    returnCode = m_CurlPostForm.processCurlHttp();
    fclose(pUploadFile);

    // 此时证明Http已经和服务器交互完毕
    if (CPS_HTTPACCESS_NAMESPACE::HTTPACCESS_OK != returnCode)
    {
        m_lastErrorInfo = m_CurlPostForm.getLastErrorMessage();
        // 上传文件失败
        if (QINIU_NULL_PTR != pUploadProcess)
        {
            time_t timeNow = ::time(0);
            pUploadProcess->OnFailUploadFile(timeNow, localFilePath);
        }
        return returnCode;
    }
    else
    {
        returnCode = m_CurlPostForm.getResponseHttpCode();
        // 没有解析出 HTTP 返回码
        if (returnCode == CPS_HTTPACCESS_NAMESPACE::HTPPACCESS_NO_HTTP_RETURN_CODE)
        {
            // 错误码信息已经解析完毕
            m_lastErrorInfo = m_CurlPostForm.getLastErrorMessage();
            // 上传文件失败
            if (QINIU_NULL_PTR != pUploadProcess)
            {
                time_t timeNow = ::time(0);
                pUploadProcess->OnFailUploadFile(timeNow,localFilePath);
            }
            return returnCode;
        }
        else
        {
            if (returnCode == (CPS_HTTPACCESS_NAMESPACE::HTTP_STANDARD_FLAG | 200U))
            {
                jsonstr = m_CurlPostForm.getResponeBody();
                returnCode = QINIU_OK;
                // 上传成功
                if (QINIU_NULL_PTR != pUploadProcess)
                {
                    time_t timeNow = ::time(0);
                    pUploadProcess->OnEndUploadFile(timeNow, (double)info.m_fileSize, localFilePath);
                }
            }
            else
            {
                m_lastErrorInfo = m_CurlPostForm.getResponeBody();
                // 上传文件失败
                if (QINIU_NULL_PTR != pUploadProcess)
                {
                    time_t timeNow = ::time(0);
                    pUploadProcess->OnFailUploadFile(timeNow, localFilePath);
                }
            }
        }
    }
    return returnCode;
}
// -----------------------------------------------------------------------------
// class :  inherit from :    public  
QiniuCode QiniuUploadFileImpl::uploadFileByChunk( IN const QiniuToken& token, 
                                                  IN const QiniuPutPolicy& putPolicy, 
                                                  IN const QiniuIoPutExtra& ioPutExtra, 
                                                  IN const bool isReplaceOldFile, 
                                                  IN const char* localFilePath, 
                                                  IN IUpLoadProgress* pUploadProcess, 
                                                  OUT std::string& jsonstr )
{
    QiniuCode returnCode = QINIU_OK;
    //清除上次的错误信息
    m_lastErrorInfo.clear(); 
    std::string jsonParamStr;
    QiniuUploadFileImpl::setJsonString(putPolicy, isReplaceOldFile, jsonParamStr);
    std::string jsonParamStrBase64;
    Base64_Encode(jsonParamStr.c_str(), jsonParamStr.size(), jsonParamStrBase64);

    std::string authStr = getMacAuthStr(token, (unsigned char*)jsonParamStrBase64.c_str(), jsonParamStrBase64.size());
    std::string authStrBase64;
    Base64_Encode(authStr.c_str(), authStr.size(), authStrBase64);
    authStrBase64 = token.m_access_key + ":" + authStrBase64;
    std::string tokenStr(authStrBase64 + ":" + jsonParamStrBase64);


    FILE* pUploadFile = CPS_MISC_NAMESPACE::fopen_(localFilePath, std::string("rb"));


    // 文件打开失败。
    if (0 == pUploadFile)
    {
        return QINIU_READ_FILE_ERROR;
    }



    struct stat_ st;
    CPS_MISC_NAMESPACE::stat64_(localFilePath, &st);
    UploadInfo info;
    info.m_fileSize = static_cast<size_t>(st.st_size); // 这里确认文件大小不会变化

    int filecount = (int)((info.m_fileSize + blockMask) >> blockBits);
    boost::scoped_array<unsigned char> pFileBlock(new unsigned char[1 << blockBits]);

    std::vector<std::string> ctxs;
    std::string url;

    IUpLoadProgressDecoration  tempProgress(pUploadProcess, static_cast<double>(info.m_fileSize));
    {
        time_t timeNow = ::time(0);
        tempProgress.OnBeginUploadFile(timeNow, static_cast<double>(info.m_fileSize), localFilePath);
    }

    for (int i = 0; i < filecount; ++i)
    {
        // 设定文件块的大小，注意整个文件的最后一块大小的处理
        size_t blocksize =  1 << blockBits;
        size_t offbase = ((size_t)(i) << blockBits);
        if ((filecount - 1) == i)
        {
            blocksize = info.m_fileSize - offbase;
        }

        // 读取文件的数据块
        size_t readblocksize = fread(static_cast<void*>(pFileBlock.get()), sizeof(unsigned char), blocksize, pUploadFile);
        if (readblocksize != blocksize)
        {
            returnCode = QINIU_READ_FILE_ERROR;
            m_lastErrorInfo = "Read File Error";
            fclose(pUploadFile);
            {
            time_t timeNow = ::time(0);
            tempProgress.OnFailUploadFile(timeNow, localFilePath);
            }
            return returnCode;
        }

        Int64 offset = 0;
        std::string ctx;

        int sliceCount = (int)((blocksize + sliceMask) >> sliceBits);
        for (int j = 0; j < sliceCount; ++j)
        {
            size_t sliceSize = 1 << sliceBits;
            size_t sliceOffBase = ((size_t)(j) << sliceBits);
            if ((sliceCount - 1) == j)
            {
                sliceSize = blocksize - sliceOffBase;
            }

            if (0 == j)
            {
                // 每次都准备重复尝试3次以用来保证上传成功
                for (int repeat = 0; repeat < REPEATCOUNT; ++repeat)
                {
                    tempProgress.setBaseFileSize(static_cast<double>(offbase));
                    returnCode = this->makeBlock(tokenStr, 
                                                 blocksize, 
                                                 static_cast<void*>(pFileBlock.get() + sliceOffBase), 
                                                 sliceSize,
                                                 &tempProgress,
                                                 jsonstr);
                    if (returnCode != 0) // 表名此次makeblock失败，
                    {
                        if (repeat == (REPEATCOUNT - 1))    // 已经连续尝试上传了3次了，退出
                        {
                            fclose(pUploadFile);
                            {
                                time_t timeNow = ::time(0);
                                tempProgress.OnFailUploadFile(timeNow, localFilePath);
                            }
                            return returnCode;
                        }
                        else
                        {
                            continue;
                        }
                    }
                    else
                    {
                        QiniuUploadFileImpl::parseUploadFileByChunkJson(jsonstr,ctx, url, offset);
                        jsonstr.clear();
                        break;
                    }
                }
            }
            else
            {
                // 每次都准备重复尝试3次以用来保证上传成功
                for (int repeat = 0; repeat < REPEATCOUNT; ++repeat)
                {
                    tempProgress.setBaseFileSize(static_cast<double>(offbase + sliceOffBase));
                    returnCode = this->bput( tokenStr, 
                                             url, 
                                             ctx, 
                                             offset, 
                                             static_cast<void*>(pFileBlock.get() + sliceOffBase), 
                                             sliceSize,
                                             &tempProgress,
                                             jsonstr);
                    if (returnCode != 0)
                    {
                        if (repeat == (REPEATCOUNT - 1))    // 已经连续尝试上传了3次了，退出
                        {
                            fclose(pUploadFile);
                            {
                                time_t timeNow = ::time(0);
                                tempProgress.OnFailUploadFile(timeNow, localFilePath);
                            }
                            return returnCode;
                        }
                        else                               // 继续尝试上传
                        {
                            continue;
                        }
                    }
                    else
                    {
                        QiniuUploadFileImpl::parseUploadFileByChunkJson(jsonstr,ctx, url, offset);
                        jsonstr.clear();
                        break;
                    }
                }
            }

        }
        ctxs.push_back(ctx);
    }

    for (int repeatcount = 0;  repeatcount < REPEATCOUNT; ++repeatcount)
    {
        returnCode = this->makefile(tokenStr, url, putPolicy.m_keyName, ctxs, info.m_fileSize, jsonstr);
        if  (returnCode != 0)
        {
            if (repeatcount == (REPEATCOUNT - 1))
            {
                {
                    fclose(pUploadFile);
                    {
                        time_t timeNow = ::time(0);
                        tempProgress.OnFailUploadFile(timeNow, localFilePath);
                    }
                    return returnCode;
                } 
            }
            else
            {
                continue;
            }
        }
        else
        {
            break;
        }
    }

    fclose(pUploadFile);
    {
        time_t timeNow = ::time(0);
        tempProgress.OnEndUploadFile(timeNow, static_cast<double>(info.m_fileSize), localFilePath);
    }

    return returnCode;
}


// -----------------------------------------------------------------------------
// class :  inherit from :    public  
const char* QiniuUploadFileImpl::getLastErrorInfo()
{
    return m_lastErrorInfo.c_str();
}


// -----------------------------------------------------------------------------
// class : QiniuUploadFileImpl inherit from : IQiniuUploadFile   protected  
QiniuCode QiniuUploadFileImpl::makeBlock( IN const std::string& tokenStr, 
                                          IN const int blockSize, 
                                          IN const void* theFirstChunkdata, 
                                          IN const int theFirstChunkSize,
                                          IN IUpLoadProgress* pUploadProcess,
                                          OUT std::string& jsonStr )
{
    QiniuCode returnCode = QINIU_OK;
    //清除上次的错误信息
    m_lastErrorInfo.clear(); 

    std::stringstream url;
    url << (m_isUsingHttps ? URL_MAKE_BLOCK_HTTPS: URL_MAKE_BLOCK_HTTP);
    url << blockSize;
    // 设定url
    m_CurlPost.setURL(url.str().c_str());
    // 设定header
    std::vector<std::string> header;


    header.push_back("Content-Type: application/octet-stream");

    std::string authStr("Authorization:  UpToken ");
    authStr += tokenStr;
    header.push_back(authStr);

    m_CurlPost.setHttpRequestHeaders(header);

    m_CurlPost.setPostBody(static_cast<const void*>(theFirstChunkdata), theFirstChunkSize);

    m_CurlPost.setUpLoadProcessCallBack(pUploadProcess);

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
// class :  inherit from :    protected  
QiniuCode QiniuUploadFileImpl::bput( IN const std::string& tokenStr,
                                     IN const std::string& url,
                                     IN const std::string& ctx, 
                                     IN const Int64 baseAddress, 
                                     IN const void* pChunkData, 
                                     IN const int chunkSize,
                                     IN IUpLoadProgress* pUploadProcess, 
                                     OUT std::string& jsonStr )
{
    QiniuCode returnCode = QINIU_OK;

    m_lastErrorInfo.clear(); 

    std::stringstream theCompleteUrl;
    theCompleteUrl << url <<"/bput" << "/" << ctx << "/" << baseAddress;
    m_CurlPost.setURL(theCompleteUrl.str().c_str());

    std::vector<std::string> headers;
    headers.push_back("Content-Type: application/octet-stream");

    std::string authStr("Authorization: UpToken ");
    authStr += tokenStr;
    headers.push_back(authStr);

    m_CurlPost.setHttpRequestHeaders(headers);

    m_CurlPost.setPostBody(pChunkData, chunkSize);

    m_CurlPost.setUpLoadProcessCallBack(pUploadProcess);

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
// class : QiniuUploadFileImpl inherit from : IQiniuUploadFile   protected  
QiniuCode QiniuUploadFileImpl::makefile( IN const std::string& tokenStr, 
                                         IN const std::string& url, 
                                         IN const std::string& keyName,
                                         IN const std::vector<std::string>& ctxs,
                                         IN const Int64 fileSize, 
                                         OUT std::string& jsonStr )
{
    QiniuCode returnCode = QINIU_OK;
    m_lastErrorInfo.clear(); 

    std::stringstream theCompleteUrl;
    theCompleteUrl << url <<"/mkfile/" << fileSize << "/key/";
    std::string keyNameBase64;
    Base64_Encode(keyName.c_str(), keyName.size(), keyNameBase64);
    theCompleteUrl << keyNameBase64;

    m_CurlPost.setURL(theCompleteUrl.str().c_str());     //Content-Type:   text/plain

    std::vector<std::string> headers;
    headers.push_back("Content-Type: text/plain");
    std::string authStr("Authorization: UpToken ");
    authStr += tokenStr;
    headers.push_back(authStr);
    m_CurlPost.setHttpRequestHeaders(headers);

    std::string content;
    for(std::vector<std::string>::const_iterator cit = ctxs.begin(); cit != ctxs.end(); ++cit)
    {
        if (cit != ctxs.begin())
        {
            content += ",";
        }
        content += *cit;

    }
    m_CurlPost.setPostBody(static_cast<const void*>(content.data()), content.size());


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
// class : QiniuUploadFileImpl inherit from : IQiniuUploadFile static   protected  
void QiniuUploadFileImpl::setJsonString( IN const QiniuPutPolicy& putPolicy, 
                                         IN const bool isReplaceOldFile, 
                                         OUT std::string& jsonStr )
{
    Json::Value root;

    std::string scopeValue = putPolicy.m_bucketName;
    if (isReplaceOldFile)
    {
        scopeValue += ":";
        scopeValue += putPolicy.m_keyName;
    }
    root["scope"] = scopeValue;

    if (QINIU_NULL_PTR != putPolicy.m_callbackUrl)
    {
        root["callbackUrl"]  = putPolicy.m_callbackUrl;

    }

    if (QINIU_NULL_PTR != putPolicy.m_callbackBody)
    {
        root["callbackBody"] = putPolicy.m_callbackBody;

    }

    if (QINIU_NULL_PTR != putPolicy.m_asyncOps)
    {
        root["asyncOps"]     = putPolicy.m_asyncOps;
    }


    if (QINIU_NULL_PTR != putPolicy.m_returnUrl)
    {
        root["returnUrl"]    = putPolicy.m_returnUrl;
    }

    if (QINIU_NULL_PTR != putPolicy.m_returnBody)
    {
        root["returnBody"] = putPolicy.m_returnBody;
    }

    if (QINIU_NULL_PTR != putPolicy.m_endUser)
    {
        root["endUser"] = putPolicy.m_endUser;
    }

    int expires;
    time_t deadline;

    if (putPolicy.m_expires) 
    {
        expires = putPolicy.m_expires;
    } else 
    {
        expires = 3600; // 1小时
    }

    ::time(&deadline);
    deadline += expires;
    root["deadline"]  = static_cast<int>(deadline);

    Json::FastWriter writer;  
    jsonStr = writer.write(root);  
}
// -----------------------------------------------------------------------------
// class : QiniuUploadFileImpl inherit from : IQiniuUploadFile   protected  
QiniuCode QiniuUploadFileImpl::parseUploadFileByChunkJson( IN const std::string& jsonStr, 
                                                           OUT std::string& ctx, 
                                                           OUT std::string& nextUrl, 
                                                           OUT Int64& offset )
{
    QiniuCode returnCode = QINIU_OK;

    Json::Reader reader;
    Json::Value root;
    if (!reader.parse(jsonStr, root, false))
    {
        return QINIU_JSON_PARSE_ERROR;
    }

    if (root.isMember("ctx"))
    {
        ctx = root["ctx"].asCString();
    }

    if (root.isMember("host"))
    {
        nextUrl = root["host"].asCString();
    }

    if (root.isMember("offset"))
    {
        offset = root["offset"].asInt64();
    }

    return returnCode;
}

QINIU_NAMESPACE_END
