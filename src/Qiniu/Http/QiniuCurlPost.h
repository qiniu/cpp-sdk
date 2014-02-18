/*******************************************************************************
 *  @file      QiniuCurlPost.h 2013\11\20 18:17:39 $
 *  @author    Wang Xiaotao<wangxiaotao1980@gmail.com>
 *
 ******************************************************************************/

#ifndef QINIUCURLPOST_A7D084CD_0395_45C2_9E85_E5BA63DBEFE3_H__
#define QINIUCURLPOST_A7D084CD_0395_45C2_9E85_E5BA63DBEFE3_H__

#include "../QiniuInternalConfig.h"
#include "../../HttpAccess/Curl/CurlHttpBaseClass.h"
#include "Qiniu/QiniuConfig.h"
#include "HttpAccess/HttpAccessConfig.h"

#include <string>
/******************************************************************************/

QINIU_NAMESPACE_BEGIN

struct IUpLoadProgress;

/**
 * The class <code>QiniuCurlPost</code>
 *
 */
class QiniuCurlPost : public CPS_HTTPACCESS_NAMESPACE::CurlHttpBaseClass
{
public:
    /** @name Constructors and Destructor*/

    //@{
    /**
     * No Parameter Constructor 
     */
    QiniuCurlPost();
    /**
     * Destructor
     */
    ~QiniuCurlPost();
    //@}

public:
    /** @name Setter Methods*/
    //@{
    void setPostBody( const void* postBody, const size_t datalen );
    void setUpLoadProcessCallBack(IUpLoadProgress* pUpLoadProcess);
    //@}
public:
    /** @name Getter Methods*/
    //@{
    const std::string& getResponeBody() const;
    //@}
public:
    /** @name Access Methods*/
    //@{

    //@}   
protected:
    virtual void clear_up_before_setting();           // 在curl设定之前再给个清理的机会
    virtual void clear_up_resource();
protected:
    virtual void curl_set_write_response_body_function(); // http 请求返回body的函数，有可能是写入文件
    virtual void curl_set_http_put_body_function();       // http put 请求的body数据
    virtual void curl_set_http_post_body_function();      // http post 请求的body数据
    virtual void curl_set_progress_function();            // 进程 设定
private:

    static size_t write_respone_body_data( void*ptr, 
                                           size_t msize,
                                           size_t n, 
                                           QiniuCurlPost* stream);

    static size_t progress_call_backFun(IUpLoadProgress *buffer, 
                                        double dltotal, 
                                        double dlnow, 
                                        double ultotal, 
                                        double ulnow);


private:

    const void*                                  m_post_body_data;
    size_t                                       m_postDataLength;
    std::string                                  m_respone_data;
    IUpLoadProgress*                             m_pUpLoadProcess;   ///< 上传进程接口指针
};

QINIU_NAMESPACE_END
/******************************************************************************/
#endif// QINIUCURLPOST_A7D084CD_0395_45C2_9E85_E5BA63DBEFE3_H__