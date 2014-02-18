/*******************************************************************************
 *  @file      IQiniuUploadFile.h 2013\12\31 11:01:24 $
 *  @author    Wang Xiaotao<wangxiaotao1980@gmail.com>
 *
 ******************************************************************************/

#ifndef IQINIUUPLOADFILE_30F2A772_6F30_402A_AB0C_230A3576E3BE_H__
#define IQINIUUPLOADFILE_30F2A772_6F30_402A_AB0C_230A3576E3BE_H__

#include "QiniuConfig.h"
#include "QiniuError.h"

#include "IHttpSetting.h"


#include <string>

/******************************************************************************/

QINIU_NAMESPACE_BEGIN

struct QiniuToken;
struct QiniuPutPolicy;
struct QiniuIoPutExtra;
struct IUpLoadProgress; 

/**
 * The class <code>IQiniuUploadFile</code>
 *
 */
struct QINIU_API_DECL IQiniuUploadFile : public IHttpSetting
{
public:
    /**
     * 上传文件到七牛云端(使用http form）
     *
     * @param   [in] const QiniuToken & token            用户token信息
     * @param   [in] const QiniuPutPolicy & putPolicy    上传文件基本信息，具体参见QiniuPutPolicy结构体
     * @param   [in] const QiniuIoPutExtra & ioPutExtra  上传文件的附加信息 具体参见QiniuIoPutExtra结构体
     * @param   [in] const bool  isReplaceOldFile        如果服务器上存在同名文件是否覆盖，
     *                                                   注意，如果此参数选择false，当本次上传文件和服务器存在的文件二进制一致的情况下，返回成功。不一致
     *                                                   报错，
     * @param   [in] const char * localFilePath          要上传的本地文件路径（utf-8编码）
     * @param   [in] IUpLoadProgress * pUploadProcess    回调接口，在文件上传中发送上传信息，可以设置为空， 表明不发送上传信息
     * @param   [out] std::string & jsonstr              返回值，json字符串，当 函数返回 QINIU_OK 其有意义 指明上传成功后file的信息
     * @return  QiniuCode                                错误码，当值为QINIU_OK时候，表示正确返回，否则可查询
     *                                                   IQiniuRemoteFile::getLastErrorInfo()得到提示信息  
     * @exception <code>无异常抛出</code>
     */
    virtual QiniuCode uploadFile( IN  const QiniuToken& token,
                                  IN  const QiniuPutPolicy&   putPolicy,
                                  IN  const QiniuIoPutExtra&  ioPutExtra,
                                  IN  const bool  isReplaceOldFile,
                                  IN  const char* localFilePath,
                                  IN  IUpLoadProgress* pUploadProcess,
                                  OUT std::string& jsonstr)                  = 0;

    /**
     * 上传文件到七牛云端(使用分片上传）
     * 具体参数和   uploadFile 类似
     */
    virtual QiniuCode uploadFileByChunk ( IN  const QiniuToken& token,
                                          IN  const QiniuPutPolicy&   putPolicy,
                                          IN  const QiniuIoPutExtra&  ioPutExtra,
                                          IN  const bool  isReplaceOldFile,
                                          IN  const char* localFilePath,
                                          IN  IUpLoadProgress* pUploadProcess,
                                          OUT std::string& jsonstr)           = 0;

    /**
     * 当上方接口返回非QINIU_OK错误码时候，其给出辅助信息
     *
     * @return  const char*辅助信息，仅仅指出最后一次出错的信息
     * @exception <code>无异常抛出</code>
     */
    
    virtual const char* getLastErrorInfo()                                    = 0;


    ~ IQiniuUploadFile() = 0;
};


QINIU_NAMESPACE_END

/******************************************************************************/
#endif// IQINIUUPLOADFILE_30F2A772_6F30_402A_AB0C_230A3576E3BE_H__