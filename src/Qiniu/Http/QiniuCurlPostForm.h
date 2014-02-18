/*******************************************************************************
 *  @file      QiniuCurlPostForm.h 2013\11\20 18:55:38 $
 *  @author    Wang Xiaotao<wangxiaotao1980@gmail.com>
 *
 ******************************************************************************/

#ifndef QINIUCURLPOSTFORM_82803EC1_8BCF_4461_812F_F3F742FDAE1C_H__
#define QINIUCURLPOSTFORM_82803EC1_8BCF_4461_812F_F3F742FDAE1C_H__

#include "../QiniuInternalConfig.h"
#include "../../HttpAccess/Curl/CurlHttpBaseClass.h"

#include "Qiniu/QiniuConfig.h"
#include "HttpAccess/HttpAccessConfig.h"

#include <string>
#include <stdio.h>
/******************************************************************************/

QINIU_NAMESPACE_BEGIN

struct IUpLoadProgress;
struct QiniuIoPutExtra;

struct UploadInfo
{
    FILE*               m_pFile;          ///< 要上传的文件句柄
    size_t              m_fileSize;       ///< 文件总大小
    size_t              m_fileOff;        ///< 文件上传偏移量
};

/**
 * The class <code>QiniuCurlPostForm</code>
 *
 */
class QiniuCurlPostForm : public CPS_HTTPACCESS_NAMESPACE::CurlHttpBaseClass
{
public:
    /** @name Constructors and Destructor*/

    //@{
    /**
     * No Parameter Constructor 
     */
    QiniuCurlPostForm();
    /**
     * Destructor
     */
    ~QiniuCurlPostForm();
    //@}

public:
    /** @name Setter Methods*/
    //@{
    void setToken(const std::string& tokenStr);
    void setKeyName(const char*keyname);
    void setIoPutExtra(const QiniuIoPutExtra* ioPutExtra);
    void setUploadFileInfo(UploadInfo* uploadInfo);
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
    virtual void clear_up_resource();                    //执行完curl之后的资源
    virtual void clear_up_before_setting();              //在curl设定之前再给个清理的机会

    virtual void curl_set_DIY();                          //
protected:
    virtual void curl_set_write_response_body_function(); // http 请求返回body的函数，有可能是写入文件
    virtual void curl_set_http_put_body_function();       // http put 请求的body数据
    virtual void curl_set_http_post_body_function();      // http post 请求的body数据
    virtual void curl_set_progress_function();            // 进程 设定
private:
    static size_t write_respone_body_data( void*ptr, 
                                           size_t msize,
                                           size_t n, 
                                           QiniuCurlPostForm* stream);


    static size_t progress_call_backFun(IUpLoadProgress *buffer, 
                                        double dltotal, 
                                        double dlnow, 
                                        double ultotal, 
                                        double ulnow);

    static size_t read_post_data( void *ptr, 
                                  size_t size, 
                                  size_t nmemb, 
                                  UploadInfo* pUploadInfo);
private:

    curl_httppost*                              m_pPost;
    curl_httppost*                              m_pLast;

    std::string                                 m_respone_data;
    std::string                                 m_tokenStr;
    std::string                                 m_keyName;
    const QiniuIoPutExtra*                            m_pIoPutExtra;
    UploadInfo*                                 m_pUploadFileInfo;  ///< 上传信息
    IUpLoadProgress*                             m_pUpLoadProcess;   ///< 上传进程接口指针
};


QINIU_NAMESPACE_END

/******************************************************************************/
#endif// QINIUCURLPOSTFORM_82803EC1_8BCF_4461_812F_F3F742FDAE1C_H__