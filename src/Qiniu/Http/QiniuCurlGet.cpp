/******************************************************************************* 
 *  @file      QiniuCurlGet.cpp 2013\11\20 18:34:06 $
 *  @author    Wang Xiaotao<wangxiaotao1980@gmail.com>
 ******************************************************************************/

#include "QiniuCurlGet.h"

/******************************************************************************/

QINIU_NAMESPACE_BEGIN

    // -----------------------------------------------------------------------------
    //  QiniuCurlGet : Public, Constructor

    QiniuCurlGet ::QiniuCurlGet ()
    : CurlHttpBaseClass()
    , m_respone_data()
{

}

// -----------------------------------------------------------------------------
//  QiniuCurlGet : Public, Destructor

QiniuCurlGet ::~QiniuCurlGet ()
{

}

// -----------------------------------------------------------------------------
// public   
const std::string& QiniuCurlGet::getResponeBody() const
{
    return m_respone_data;
}

// -----------------------------------------------------------------------------
// protected   virtual 
void QiniuCurlGet::clear_up_before_setting()
{
    m_respone_data.clear();
    CurlHttpBaseClass::clear_up_before_setting();
}


// -----------------------------------------------------------------------------
// protected   virtual
void QiniuCurlGet::curl_set_http_put_body_function()
{
    // HTTP PUT 方法使用，这里不设定
}

// -----------------------------------------------------------------------------
// protected   virtual 
void QiniuCurlGet::curl_set_http_post_body_function()
{
    // HTTP POST 方法这里不设定
}

// -----------------------------------------------------------------------------
// protected   virtual 
void QiniuCurlGet::curl_set_progress_function()
{
    // 过程回调函数 不设定
}

// -----------------------------------------------------------------------------
// protected   virtual 
void QiniuCurlGet::curl_set_write_response_body_function()
{
    ::curl_easy_setopt(m_pCURL, CURLOPT_WRITEFUNCTION, &(QiniuCurlGet::write_respone_body_data));
    ::curl_easy_setopt(m_pCURL, CURLOPT_WRITEDATA, this);

}

// -----------------------------------------------------------------------------
// private  static  
size_t QiniuCurlGet::write_respone_body_data( void*ptr,
                                             size_t msize, 
                                             size_t n, 
                                             QiniuCurlGet* stream )
{
    stream->m_respone_data.append(static_cast<const char*>(ptr), msize * n);

    return msize * n;
}


QINIU_NAMESPACE_END

    // 
    // -----------------------------------------------------------------------------
