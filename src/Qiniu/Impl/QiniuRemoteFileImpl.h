/*******************************************************************************
 *  @file      QiniuRemoteFileImpl.h 2013\11\21 14:00:16 $
 *  @author    Wang Xiaotao<wangxiaotao1980@gmail.com> (中文编码测试)
 *
 ******************************************************************************/

#ifndef QINIUREMOTEFILEIMPL_A1846704_C3AB_4C23_BF23_95607FBE8096_H__
#define QINIUREMOTEFILEIMPL_A1846704_C3AB_4C23_BF23_95607FBE8096_H__

#include "Qiniu/QiniuConfig.h"
#include "Qiniu/IQiniuRemoteFile.h"

#include "../QiniuInternalConfig.h"
#include "../Http/QiniuCurlPost.h"
#include "../Http/QiniuCurlPostForm.h"

#include <string>

/******************************************************************************/
QINIU_NAMESPACE_BEGIN

/**
 * The class <code>QiniuRemoteFileImpl</code>
 *
 */
class QiniuRemoteFileImpl : public IQiniuRemoteFile
{
public:
    /** @name Constructors and Destructor*/

    //@{
    /**
     * No Parameter Constructor 
     */
    QiniuRemoteFileImpl();
    /**
     * Destructor
     */
    ~QiniuRemoteFileImpl();
    //@}

public:
    /** @name IHttpSetting Methods*/
    //@{
    virtual void setUsingHttps( bool isUsingHttps );

    virtual bool getUsingHttps();

    virtual void setProxyInfo( const ProxyInfo& proxyInfo );

    virtual const ProxyInfo& getProxyInfo();

    virtual void setTimeout( UInt32 timeout );

    virtual UInt32 getTimeout();
    //@}
public:
    /** @name IQiniuRemoteFile Methods*/
    //@{

    virtual QiniuCode ListFileNames( IN  const QiniuToken& token,
                                        IN  const char* bucketName,
                                        IN  const char* marker,
                                        IN  const int   sum,
                                        IN  const char* prefix,
                                        OUT std::string& jsonStr);


    virtual QiniuCode ListAllFileNames( IN  const QiniuToken& token,
                                        IN  const char* bucketName,
                                        IN  const char* prefix,
                                        OUT std::string& jsonStr);


    virtual QiniuCode getRemoteFileInfo( IN  const QiniuToken&  token, 
                                         IN  const char*        bucketName, 
                                         IN  const char*        keyName,
                                         OUT std::string& jsonstr);

    virtual QiniuCode moveRemoteFile( IN const QiniuToken& token,
                                      IN const char*       bucketSrc,
                                      IN const char*       keySrc,
                                      IN const char*       bucketDest,
                                      IN const char*       keyDest );

    virtual QiniuCode copyRemoteFile( IN const QiniuToken& token,
                                      IN const char*       bucketSrc,
                                      IN const char*       keySrc,
                                      IN const char*       bucketDest,
                                      IN const char*       keyDest);

    virtual QiniuCode deleteRemoteFile( IN  const QiniuToken&  token, 
                                        IN  const char* bucketName, 
                                        IN  const char* keyName);

    virtual const char* getLastErrorInfo();
    //@}

private:

    QiniuCurlPost                            m_CurlPost;
    bool                                     m_isUsingHttps;
    std::string                              m_lastErrorInfo;
};


QINIU_NAMESPACE_END
/******************************************************************************/
#endif// QINIUREMOTEFILEIMPL_A1846704_C3AB_4C23_BF23_95607FBE8096_H__