/******************************************************************************* 
 *  @file      QiniuCurlPostForm.cpp 2013\11\20 18:57:37 $
 *  @author    Wang Xiaotao<wangxiaotao1980@gmail.com>
 ******************************************************************************/

#include "QiniuCurlPostForm.h"
#include "Qiniu/IUpLoadProgress.h"
#include "Qiniu/QiniuStrcut.h"

#include <time.h>
/******************************************************************************/

QINIU_NAMESPACE_BEGIN
// -----------------------------------------------------------------------------
//  MaiKuCurlPostForm: Public, Constructor

QiniuCurlPostForm::QiniuCurlPostForm()
: CurlHttpBaseClass()
, m_pPost(QINIU_NULL_PTR)
, m_pLast(QINIU_NULL_PTR)
, m_respone_data()
, m_tokenStr()
, m_keyName()
, m_pIoPutExtra(QINIU_NULL_PTR)
, m_pUploadFileInfo(QINIU_NULL_PTR)
, m_pUpLoadProcess(QINIU_NULL_PTR)
{
}

// -----------------------------------------------------------------------------
//  MaiKuCurlPostForm: Public, Destructor

QiniuCurlPostForm::~QiniuCurlPostForm()
{
}

// -----------------------------------------------------------------------------
// public   
void QiniuCurlPostForm::setToken( const std::string& tokenStr )
{
    m_tokenStr = tokenStr;
}

// -----------------------------------------------------------------------------
// class : QiniuCurlPostForm inherit from : CurlHttpBaseClass
//   public  

void QiniuCurlPostForm::setKeyName( const char*keyname )
{
    m_keyName = keyname;
}


// -----------------------------------------------------------------------------
// class :  inherit from : 
//   public  

void QiniuCurlPostForm::setIoPutExtra( const QiniuIoPutExtra* ioPutExtra )
{
    m_pIoPutExtra = ioPutExtra;
}



// -----------------------------------------------------------------------------
// public   
void QiniuCurlPostForm::setUploadFileInfo(UploadInfo* uploadInfo)
{
    m_pUploadFileInfo = uploadInfo;
}

// -----------------------------------------------------------------------------
// public   
void QiniuCurlPostForm::setUpLoadProcessCallBack( IUpLoadProgress* pUpLoadProcess )
{
    m_pUpLoadProcess = pUpLoadProcess;
}

// -----------------------------------------------------------------------------
// public   
const std::string& QiniuCurlPostForm::getResponeBody() const
{
    return m_respone_data;
}

// -----------------------------------------------------------------------------
// protected   virtual 
void QiniuCurlPostForm::clear_up_resource()
{
    ::curl_formfree(m_pPost);

    m_pPost = QINIU_NULL_PTR;
    m_pLast = QINIU_NULL_PTR;

    m_tokenStr.clear();
    m_keyName.clear();
    //　清空数据
    m_pIoPutExtra     = QINIU_NULL_PTR;
    m_pUploadFileInfo = QINIU_NULL_PTR;
    m_pUpLoadProcess  = QINIU_NULL_PTR;

    CurlHttpBaseClass::clear_up_resource();
}

// -----------------------------------------------------------------------------
// protected   virtual 
void QiniuCurlPostForm::clear_up_before_setting()
{
    m_respone_data.clear();
    CurlHttpBaseClass::clear_up_before_setting();
}

// -----------------------------------------------------------------------------
// protected   virtual 
void QiniuCurlPostForm::curl_set_DIY()
{

    ::curl_easy_setopt(m_pCURL, CURLOPT_POST, 1L);


    ::curl_formadd( &m_pPost,                 &m_pLast,
        CURLFORM_COPYNAME,        "token",
        CURLFORM_COPYCONTENTS,    m_tokenStr.c_str(),
        CURLFORM_END);
    
    ::curl_formadd( &m_pPost,     &m_pLast,
        CURLFORM_COPYNAME,        "file",
        CURLFORM_FILENAME,        "fileName",                    //随意的名字，不重要
        CURLFORM_STREAM,            m_pUploadFileInfo,
        CURLFORM_CONTENTSLENGTH,    m_pUploadFileInfo->m_fileSize,
        CURLFORM_END);
    

    ::curl_formadd( &m_pPost,     &m_pLast,
        CURLFORM_COPYNAME,        "key",
        CURLFORM_COPYCONTENTS,    m_keyName.c_str(),
        CURLFORM_END);
    
    for (QiniuIoPutExtraParam* param = m_pIoPutExtra->m_params; param != NULL; param = param->m_pNext) 
    {
        ::curl_formadd( &m_pPost, &m_pLast, 
            CURLFORM_COPYNAME, param->m_key, 
            CURLFORM_COPYCONTENTS, param->m_value, 
        CURLFORM_END);
    }

    ::curl_easy_setopt(m_pCURL, CURLOPT_HTTPPOST, m_pPost);

    CurlHttpBaseClass::curl_set_DIY();
}

// -----------------------------------------------------------------------------
// protected   virtual 
void QiniuCurlPostForm::curl_set_write_response_body_function()
{
    ::curl_easy_setopt(m_pCURL, CURLOPT_WRITEFUNCTION, &(QiniuCurlPostForm::write_respone_body_data));
    ::curl_easy_setopt(m_pCURL, CURLOPT_WRITEDATA, this);

}


// -----------------------------------------------------------------------------
// protected   virtual 
void QiniuCurlPostForm::curl_set_http_put_body_function()
{
}

// -----------------------------------------------------------------------------
// protected   virtual 
void QiniuCurlPostForm::curl_set_http_post_body_function()
{
    ::curl_easy_setopt( m_pCURL, CURLOPT_READFUNCTION,
        &(QiniuCurlPostForm::read_post_data));
    // CURLOPT_READDATA 不需要设定，在CURLFORM_STREAM中传入。
}    

// -----------------------------------------------------------------------------
// protected   virtual 
void QiniuCurlPostForm::curl_set_progress_function()
{

    if (QINIU_NULL_PTR != m_pUpLoadProcess)
    {
        ::curl_easy_setopt( m_pCURL, CURLOPT_NOPROGRESS, 0L);
        ::curl_easy_setopt( m_pCURL, 
            CURLOPT_PROGRESSFUNCTION, 
            &(QiniuCurlPostForm::progress_call_backFun));

        ::curl_easy_setopt(m_pCURL, CURLOPT_PROGRESSDATA, m_pUpLoadProcess);
    }
    else
    {
        ::curl_easy_setopt( m_pCURL, CURLOPT_NOPROGRESS, 1L);
    }

}

// -----------------------------------------------------------------------------
// private  static  
size_t QiniuCurlPostForm::write_respone_body_data( void*ptr, 
                                                  size_t msize,
                                                  size_t n, 
                                                  QiniuCurlPostForm* stream )
{
    stream->m_respone_data.append(static_cast<const char*>(ptr), msize * n);
    return msize * n;
}

// -----------------------------------------------------------------------------
// private  static  
size_t QiniuCurlPostForm::progress_call_backFun( IUpLoadProgress* buffer, 
                                                double  dltotal, 
                                                double  dlnow, 
                                                double  ultotal, 
                                                double  ulnow )
{
    time_t theNowTime = ::time(0);
    buffer->OnProcessUploadFile( theNowTime, ultotal, ulnow);

    return 0;
}

// -----------------------------------------------------------------------------
// private  static  
size_t QiniuCurlPostForm::read_post_data( void *ptr, 
                                         size_t size, 
                                         size_t nmemb, 
                                         UploadInfo* pUploadInfo)
{
    size_t fileHasNoUpLent = pUploadInfo->m_fileSize - pUploadInfo->m_fileOff;
    size_t upblock = 0;

    if (fileHasNoUpLent >= size * nmemb)
    {
        upblock = fread(ptr, nmemb, size, pUploadInfo->m_pFile);
        pUploadInfo->m_fileOff += (nmemb * upblock);

        return nmemb * upblock;
    }

    else

    {
        upblock = fread(ptr, fileHasNoUpLent, 1, pUploadInfo->m_pFile);
        pUploadInfo ->m_fileOff += fileHasNoUpLent * upblock;

        return fileHasNoUpLent * upblock;
    }

}

QINIU_NAMESPACE_END

    // 
    // -----------------------------------------------------------------------------


