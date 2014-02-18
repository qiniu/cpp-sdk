/******************************************************************************* 
 *  @file      QiniuCurlPost.cpp 2013\11\20 18:18:19 $
 *  @author    Wang Xiaotao<wangxiaotao1980@gmail.com>
 ******************************************************************************/

#include "QiniuCurlPost.h"
#include "Qiniu/IUpLoadProgress.h"

QINIU_NAMESPACE_BEGIN
// -----------------------------------------------------------------------------
//  QiniuCurlPost: Public, Constructor

QiniuCurlPost::QiniuCurlPost()
: CurlHttpBaseClass()
, m_post_body_data(0)
, m_postDataLength(0)
, m_respone_data()
, m_pUpLoadProcess(0)
{

}

// -----------------------------------------------------------------------------
//  QiniuCurlPost: Public, Destructor

QiniuCurlPost::~QiniuCurlPost()
{

}

// -----------------------------------------------------------------------------
// public   
void QiniuCurlPost::setPostBody( const void* postBody, const size_t datalen )
{
    m_post_body_data = postBody;
    m_postDataLength = datalen;
}


// -----------------------------------------------------------------------------
// class : QiniuCurlPost inherit from : CurlHttpBaseClass   public  
void QiniuCurlPost::setUpLoadProcessCallBack( IUpLoadProgress* pUpLoadProcess )
{
    m_pUpLoadProcess = pUpLoadProcess;
}

// -----------------------------------------------------------------------------
// public   
const std::string& QiniuCurlPost::getResponeBody() const
{
    return m_respone_data;
}


// -----------------------------------------------------------------------------
// protected   virtual 
void QiniuCurlPost::clear_up_before_setting()
{
    m_respone_data.clear();
    CurlHttpBaseClass::clear_up_before_setting();
}

// -----------------------------------------------------------------------------
// protected   virtual 
void QiniuCurlPost::curl_set_write_response_body_function()
{
    ::curl_easy_setopt(m_pCURL, CURLOPT_WRITEFUNCTION, &(QiniuCurlPost::write_respone_body_data));
    ::curl_easy_setopt(m_pCURL, CURLOPT_WRITEDATA, this);
}

// -----------------------------------------------------------------------------
// protected   virtual 
void QiniuCurlPost::curl_set_http_put_body_function()
{
    // 不设定
}

// -----------------------------------------------------------------------------
// protected   virtual 
void QiniuCurlPost::curl_set_http_post_body_function()
{
    ::curl_easy_setopt(m_pCURL, CURLOPT_POST, 1);
    if ((m_post_body_data != 0) && (m_postDataLength != 0))
    {
        ::curl_easy_setopt(m_pCURL, CURLOPT_POSTFIELDS, m_post_body_data);
        ::curl_easy_setopt(m_pCURL, CURLOPT_POSTFIELDSIZE, m_postDataLength);
    }
    else
    {
        ::curl_easy_setopt(m_pCURL, CURLOPT_POSTFIELDS, 0);
        ::curl_easy_setopt(m_pCURL, CURLOPT_POSTFIELDSIZE, 0);
    }

}

// -----------------------------------------------------------------------------
// protected   virtual 
void QiniuCurlPost::curl_set_progress_function()
{
    if (QINIU_NULL_PTR != m_pUpLoadProcess)
    {
        ::curl_easy_setopt( m_pCURL, CURLOPT_NOPROGRESS, 0L);
        ::curl_easy_setopt( m_pCURL, 
            CURLOPT_PROGRESSFUNCTION, 
            &(QiniuCurlPost::progress_call_backFun));

        ::curl_easy_setopt(m_pCURL, CURLOPT_PROGRESSDATA, m_pUpLoadProcess);
    }
    else
    {
        ::curl_easy_setopt( m_pCURL, CURLOPT_NOPROGRESS, 1L);
    } 
}

// -----------------------------------------------------------------------------
// private  static  
size_t QiniuCurlPost::write_respone_body_data( void*ptr, size_t msize, size_t n, QiniuCurlPost* stream )
{
    stream->m_respone_data.append(static_cast<const char*>(ptr), msize * n);

    return msize * n;
}

// -----------------------------------------------------------------------------
// public   
void QiniuCurlPost::clear_up_resource()
{
    m_post_body_data = 0;
    m_postDataLength = 0;
    m_pUpLoadProcess = 0;
    CurlHttpBaseClass::clear_up_resource();
}
// -----------------------------------------------------------------------------
// class : QiniuCurlPost inherit from : CurlHttpBaseClass static   private  
size_t QiniuCurlPost::progress_call_backFun( IUpLoadProgress *buffer, 
                                             double dltotal, 
                                             double dlnow, 
                                             double ultotal, 
                                             double ulnow )
{
    time_t theNowTime = ::time(0);
    buffer->OnProcessUploadFile( theNowTime, ultotal, ulnow);
    return 0;
}

QINIU_NAMESPACE_END

// 
// -----------------------------------------------------------------------------