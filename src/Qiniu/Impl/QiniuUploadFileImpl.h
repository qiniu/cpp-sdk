/*******************************************************************************
 *  @file      QiniuUploadFileImpl.h 2013\12\31 11:20:02 $
 *  @author    Wang Xiaotao<wangxiaotao1980@gmail.com>
 *
 ******************************************************************************/

#ifndef QINIUUPLOADFILEIMPL_78A2E169_071B_4B33_821F_4A3F3EC3F506_H__
#define QINIUUPLOADFILEIMPL_78A2E169_071B_4B33_821F_4A3F3EC3F506_H__

#include "Qiniu/QiniuConfig.h"
#include "Qiniu/IQiniuUploadFile.h"

#include "../QiniuInternalConfig.h"
#include "../Http/QiniuCurlPost.h"
#include "../Http/QiniuCurlPostForm.h"

#include <string>
/******************************************************************************/
QINIU_NAMESPACE_BEGIN
/**
 * The class <code>QiniuUploadFileImpl</code>
 *
 */
class QiniuUploadFileImpl : public IQiniuUploadFile
{
public:
    /** @name Constructors and Destructor*/

    //@{
    /**
     * No Parameter Constructor 
     */
    QiniuUploadFileImpl();
    /**
     * Destructor
     */
    ~QiniuUploadFileImpl();




    //@}

public:
    /** @name Setter Methods*/
    //@{
    virtual void setUsingHttps( bool isUsingHttps );
    virtual bool getUsingHttps();

    virtual void setProxyInfo( const ProxyInfo& proxyInfo );
    virtual const ProxyInfo& getProxyInfo();

    virtual void setTimeout( UInt32 timeout );
    virtual UInt32 getTimeout();
    //@}
public:
    /** @name IQiniuUploadFile Methods*/
    //@{
    virtual QiniuCode uploadFile( IN const QiniuToken& token, 
                                  IN const QiniuPutPolicy& putPolicy, 
                                  IN const QiniuIoPutExtra& ioPutExtra, 
                                  IN const bool isReplaceOldFile, 
                                  IN const char* localFilePath, 
                                  IN IUpLoadProgress* pUploadProcess, 
                                  OUT std::string& jsonstr );

    virtual QiniuCode uploadFileByChunk( IN const QiniuToken& token, 
                                         IN const QiniuPutPolicy& putPolicy, 
                                         IN const QiniuIoPutExtra& ioPutExtra, 
                                         IN const bool isReplaceOldFile, 
                                         IN const char* localFilePath, 
                                         IN IUpLoadProgress* pUploadProcess, 
                                         OUT std::string& jsonstr );

    virtual const char* getLastErrorInfo();

    //@}
public:
    /** @name Access Methods*/
    //@{

    //@}   
protected:
protected:
    // 创建块
    QiniuCode makeBlock( IN const std::string& tokenStr,
                         IN const int blockSize, 
                         IN const void* theFirstChunkdata,
                         IN const int theFirstChunkSize,
                         IN IUpLoadProgress* pUploadProcess, 
                         OUT std::string& jsonStr );
    // 上传片      
    QiniuCode     bput( IN const std::string& tokenStr,
                        IN const std::string& url,
                        IN const std::string& ctx,
                        IN const Int64  baseAddress,
                        IN const void* pChunkData,
                        IN const int   chunkSize,
                        IN IUpLoadProgress* pUploadProcess, 
                        OUT std::string& jsonStr );
    // 创建文件
    QiniuCode makefile( IN const std::string& tokenStr,
                        IN const std::string&  url,
                        IN const std::string&  keyName,
                        IN const std::vector<std::string>& ctxs,
                        IN const Int64  fileSize,
                        OUT std::string& jsonStr );


    static void setJsonString( IN const QiniuPutPolicy&   putPolicy,
                               IN const bool  isReplaceOldFile,
                               OUT std::string& jsonStr);

    QiniuCode  parseUploadFileByChunkJson( IN  const std::string& jsonStr,
                                           OUT std::string&  ctx,
                                           OUT  std::string&  nextUrl,
                                           OUT  Int64&        offset);
private:
private:

    QiniuCurlPost                            m_CurlPost;
    QiniuCurlPostForm                        m_CurlPostForm;
    bool                                     m_isUsingHttps;
    std::string                              m_lastErrorInfo;
};

QINIU_NAMESPACE_END

/******************************************************************************/
#endif// QINIUUPLOADFILEIMPL_78A2E169_071B_4B33_821F_4A3F3EC3F506_H__