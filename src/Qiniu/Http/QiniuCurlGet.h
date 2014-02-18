/*******************************************************************************
 *  @file      QiniuCurlGet.h 2013\11\20 18:30:57 $
 *  @author    Wang Xiaotao<wangxiaotao1980@gmail.com>
 *
 ******************************************************************************/

#ifndef QINIUCURLGET_88385CE1_754A_4956_8804_66CCDE599398_H__
#define QINIUCURLGET_88385CE1_754A_4956_8804_66CCDE599398_H__

#include "../QiniuInternalConfig.h"

#include "../../HttpAccess/Curl/CurlHttpBaseClass.h"

#include "Qiniu/QiniuConfig.h"

#include "HttpAccess/HttpAccessConfig.h"

#include <string>
/******************************************************************************/

QINIU_NAMESPACE_BEGIN
/**
 * The class <code>QiniuCurlGet</code>
 *
 */
class QiniuCurlGet : public CPS_HTTPACCESS_NAMESPACE::CurlHttpBaseClass
{
public:
    /** @name Constructors and Destructor*/

    //@{
    /**
     * No Parameter Constructor 
     */
    QiniuCurlGet();
    /**
     * Destructor
     */
    ~QiniuCurlGet();
    //@}

public:
    /** @name Setter Methods*/
    //@{

    const std::string& getResponeBody() const;

    //@}
public:
    /** @name Getter Methods*/
    //@{

    //@}
public:
    /** @name Access Methods*/
    //@{

    //@}   
protected:
    virtual void clear_up_before_setting();           // 在curl设定之前再给个清理的机会
protected:
    virtual void curl_set_write_response_body_function(); // http 请求返回body的函数，有可能是写入文件
    virtual void curl_set_http_put_body_function();      // http put 请求的body数据
    virtual void curl_set_http_post_body_function();     // http post 请求的body数据
    virtual void curl_set_progress_function();           // 进程 设定
private:

    static size_t write_respone_body_data( void*ptr, size_t msize
                                         , size_t n, QiniuCurlGet* stream);

private:

    std::string  m_respone_data;
};

QINIU_NAMESPACE_END
/******************************************************************************/
#endif// QINIUCURLGET_88385CE1_754A_4956_8804_66CCDE599398_H__