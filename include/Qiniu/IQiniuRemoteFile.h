/*******************************************************************************
 *  @file      IQiniuRemoteFile.h 2013\11\21 11:08:32 $
 *  @author    Wang Xiaotao<wangxiaotao1980@gmail.com> (中文编码测试)
 *
 ******************************************************************************/

#ifndef IQINIUREMOTEFILE_1749BE1D_2FB7_4F09_85DD_35C46B9888F6_H__
#define IQINIUREMOTEFILE_1749BE1D_2FB7_4F09_85DD_35C46B9888F6_H__

#include "QiniuConfig.h"
#include "QiniuError.h"

#include "IHttpSetting.h"


#include <string>

/******************************************************************************/

QINIU_NAMESPACE_BEGIN

struct QiniuToken;
struct IUpLoadProgress;
struct QiniuPutPolicy;
struct QiniuIoPutExtra;

/**
 * The class <code>IQiniuRemoteFile</code>七牛云存储文件操作接口
 *
 */
struct QINIU_API_DECL IQiniuRemoteFile : public IHttpSetting
{
public:

    virtual QiniuCode ListFileNames( IN  const QiniuToken& token,
                                        IN  const char* bucketName,
                                        IN  const char* marker,
                                        IN  const int   sum,
                                        IN  const char* prefix,
                                        OUT std::string& jsonStr)               = 0;

    virtual QiniuCode ListAllFileNames( IN  const QiniuToken& token,
                                        IN  const char* bucketName,
                                        IN  const char* prefix,
                                        OUT std::string& jsonStr)               = 0;



   /**
     * 得到七牛云端的具体文件信息
     *
     * @param [in] const QiniuToken & token       用户token信息
     * @param [in] const char * bucketName        文件所在bucket名称
     * @param [in] const char * keyName           文件的名称
     * @param [out] std::string & jsonstr         返回值，json字符串，当 QiniuCode QINIU_OK 其有意义 指明查询file的信息
     * @return  QINIU_NAMESPACE::QiniuCode        错误码，当值为QINIU_OK时候，表示正确返回，否则可查询
     *                                            IQiniuRemoteFile::getLastErrorInfo()得到提示信息
     * @exception <code>无异常抛出</code>
     */
    
    virtual QiniuCode getRemoteFileInfo( IN const QiniuToken&  token, 
                                         IN const char* bucketName, 
                                         IN const char* keyName,
                                         OUT std::string& jsonstr)             = 0;

    /**
     *  移动七牛云端的具体文件，如果 bucketSrc 和 bucketDest 相同，其效果等同与改名
     *
     * @param   [in] const QiniuToken & token  用户token信息
     * @param   [in] const char * bucketSrc    源文件所在bucket名称
     * @param   [in] const char * keySrc       源文件名称
     * @param   [in] const char * bucketDest   目标文件所在bucket名称
     * @param   [in] const char * keyDest      目标文件名称
     * @return  QINIU_NAMESPACE::QiniuCode     错误码，当值为QINIU_OK时候，表示正确返回，否则可查询
     *                                            IQiniuRemoteFile::getLastErrorInfo()得到提示信息
     * @exception <code>无异常抛出</code>
     */
    
    virtual QiniuCode moveRemoteFile( IN const QiniuToken& token,
                                      IN const char*       bucketSrc,
                                      IN const char*       keySrc,
                                      IN const char*       bucketDest,
                                      IN const char*       keyDest)           = 0;

    /**
     * 复制七牛云端的具体文件
     *
     * @param   [in] const QiniuToken & token  用户token信息
     * @param   [in] const char * bucketSrc    源文件所在bucket名称
     * @param   [in] const char * keySrc       源文件名称
     * @param   [in] const char * bucketDest   目标文件所在bucket名称
     * @param   [in] const char * keyDest      目标文件名称
     * @return  QiniuCode                      错误码，当值为QINIU_OK时候，表示正确返回，否则可查询
     *                                            IQiniuRemoteFile::getLastErrorInfo()得到提示信息
     * @exception <code>无异常抛出</code>
     */
    
    virtual QiniuCode copyRemoteFile( IN const QiniuToken& token,
                                      IN const char*       bucketSrc,
                                      IN const char*       keySrc,
                                      IN const char*       bucketDest,
                                      IN const char*       keyDest)           = 0;

    /**
     *  删除七牛云端的具体文件
     *
     * @param   [in] const QiniuToken & token    用户token信息
     * @param   [in] const char * bucketName     文件所在bucket名称
     * @param   [in] const char * keyName        文件名称
     * @return  QiniuCode                         错误码，当值为QINIU_OK时候，表示正确返回，否则可查询
     *                                            IQiniuRemoteFile::getLastErrorInfo()得到提示信息
     * @exception <code>无异常抛出</code>
     */
    
    virtual QiniuCode deleteRemoteFile( IN  const QiniuToken&  token, 
                                        IN  const char* bucketName, 
                                        IN  const char* keyName)             = 0;

    /**
     * 当上方接口返回非QINIU_OK错误码时候，其给出辅助信息
     *
     * @return  const char*辅助信息，仅仅指出最后一次出错的信息
     * @exception <code>无异常抛出</code>
     */
    
    virtual const char* getLastErrorInfo()                                    = 0;

    ~IQiniuRemoteFile()                                                       = 0;
};

QINIU_NAMESPACE_END

/******************************************************************************/
#endif// IQINIUREMOTEFILE_1749BE1D_2FB7_4F09_85DD_35C46B9888F6_H__