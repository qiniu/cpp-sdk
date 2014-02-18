/*******************************************************************************
 *  @file      QiniuRemoteBatchFilesImpl.h 2013\11\25 17:25:40 $
 *  @author    Wang Xiaotao<wangxiaotao1980@gmail.com> (中文编码测试)
 *
 ******************************************************************************/

#ifndef QINIUREMOTEBATCHFILESIMPL_54BCCD7C_9188_4F67_ADDB_FC90F701AD59_H__
#define QINIUREMOTEBATCHFILESIMPL_54BCCD7C_9188_4F67_ADDB_FC90F701AD59_H__

#include "Qiniu/QiniuConfig.h"
#include "Qiniu/IQiniuRemoteBatchFiles.h"

#include "../QiniuInternalConfig.h"
#include "../Http/QiniuCurlPost.h"


#include <string>
/******************************************************************************/

QINIU_NAMESPACE_BEGIN

/**
 * The class <code>QiniuRemoteBatchFilesImpl</code>
 *
 */
class QiniuRemoteBatchFilesImpl : public IQiniuRemoteBatchFiles
{
public:
    /** @name Constructors and Destructor*/

    //@{
    /**
     * No Parameter Constructor 
     */
    QiniuRemoteBatchFilesImpl();
    /**
     * Destructor
     */
    ~QiniuRemoteBatchFilesImpl();
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
    /** @name IQiniuRemoteBatchFiles Methods*/
    //@{
    virtual QiniuCode getRemoteBatchFilesInfo( IN  const QiniuToken&  token,
                                               IN  const QiniuBucketKey* bucketKeys,
                                               IN  const int             bucketKeysLen,
                                               OUT std::string& jsonstr); 

    virtual QiniuCode moveRemoteBatchFiles( IN const QiniuToken&     token,
                                            IN const QiniuSrcAndDestBucketKey* bucketKeys,
                                            IN const int             bucketKeysLen,
                                            OUT std::string&         jsonstr);

    virtual QiniuCode copyRemoteBatchFiles( IN const QiniuToken&               token,
                                            IN const QiniuSrcAndDestBucketKey* bucketKeys,
                                            IN const int                       bucketKeysLen,
                                            OUT std::string&                   jsonstr);


    virtual QiniuCode deleteRemoteBatchFiles( IN  const QiniuToken&     token,
                                              IN  const QiniuBucketKey* bucketKeys,
                                              IN  const int             bucketKeysLen,
                                              OUT std::string&         jsonstr);


    virtual const char* getLastErrorInfo();
    //@}

private:

    QiniuCurlPost                            m_CurlPost;
    bool                                     m_isUsingHttps;
    std::string                              m_lastErrorInfo;

};


QINIU_NAMESPACE_END
/******************************************************************************/
#endif// QINIUREMOTEBATCHFILESIMPL_54BCCD7C_9188_4F67_ADDB_FC90F701AD59_H__