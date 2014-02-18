/*******************************************************************************
 *  @file      IQiniuRemoteBatchFiles.h 2013\11\25 17:10:59 $
 *  @author    Wang Xiaotao<wangxiaotao1980@gmail.com> (中文编码测试)
 *
 ******************************************************************************/

#ifndef IQINIUREMOTEBATCHFILES_6D902195_7AB3_4F5C_8CF4_EE662C8A1D10_H__
#define IQINIUREMOTEBATCHFILES_6D902195_7AB3_4F5C_8CF4_EE662C8A1D10_H__

#include "QiniuConfig.h"
#include "QiniuError.h"

#include "IHttpSetting.h"


#include <string>
/******************************************************************************/


QINIU_NAMESPACE_BEGIN

struct QiniuToken;
struct QiniuBucketKey;
struct QiniuSrcAndDestBucketKey;


/**
 * The class <code>IQiniuRemoteBatchFile</code>远程文件批量操作接口
 *
 */
struct QINIU_API_DECL IQiniuRemoteBatchFiles : public IHttpSetting
{
public:

    /**
     * 批量得到文件信息
     *
     * @param   [in] const QiniuToken & token           用户token信息
     * @param   [in] const QiniuBucketKey * bucketKeys  QiniuBucketKey数组头指针，里面是要批量得到的文件名称，
     * @param   [in] const int bucketKeysLen            上个参数bucketKeys数组的长度，
     * @param   [out] std::string & jsonstr             返回值，json字符串，当 QiniuCode QINIU_OK 其有意义 指明查询files的信息
     * @return  QiniuCode                               错误码，当值为QINIU_OK时候，表示正确返回，否则可查询
     *                                                  IQiniuRemoteFile::getLastErrorInfo()得到提示信息
     * @exception <code>无异常抛出</code>
     */
    
    virtual QiniuCode getRemoteBatchFilesInfo( IN const QiniuToken&     token,
                                               IN const QiniuBucketKey* bucketKeys,
                                               IN const int             bucketKeysLen,
                                               OUT std::string&         jsonstr)             = 0;

    /**
     * 批量移动远程文件
     *
     * @param   IN const QiniuToken & token                        用户token信息
     * @param   IN const QiniuSrcAndDestBucketKey * bucketKeys     QiniuSrcAndDestBucketKey数组头指针，里面是要批量移动的文件的源与目标名称
     * @param   IN const int bucketKeysLen                         bucketKeys数组长度
     * @param   OUT std::string & jsonstr                          返回值，json字符串，当 QiniuCode QINIU_OK 其有意义 指明移动files操作的信息
     * @return  QINIU_NAMESPACE::QiniuCode                         错误码，当值为QINIU_OK时候，表示正确返回，否则可查询
     *                                                             IQiniuRemoteFile::getLastErrorInfo()得到提示信息
     * @exception <code>无异常抛出</code>
     */
    
    virtual QiniuCode moveRemoteBatchFiles( IN const QiniuToken&     token,
                                            IN const QiniuSrcAndDestBucketKey* bucketKeys,
                                            IN const int             bucketKeysLen,
                                            OUT std::string&         jsonstr)             = 0;

    
    /**
     * 批量拷贝远程文件
     *
     * @param   [in]  const QiniuToken & token                       用户token信息
     * @param   [in]  const QiniuSrcAndDestBucketKey * bucketKeys    QiniuSrcAndDestBucketKey数组头指针，里面是要批量移动的文件的源与目标名称
     * @param   [in]  const int bucketKeysLen                        bucketKeys数组长度 
     * @param   [out] std::string & jsonstr                          返回值，json字符串，当 QiniuCode QINIU_OK 其有意义 指明拷贝files操作的信息
     * @return  QINIU_NAMESPACE::QiniuCode                           错误码，当值为QINIU_OK时候，表示正确返回，否则可查询
     *                                                               IQiniuRemoteFile::getLastErrorInfo()得到提示信息
     * @exception <code>无异常抛出</code>
     */
    
    virtual QiniuCode copyRemoteBatchFiles( IN const QiniuToken&               token,
                                            IN const QiniuSrcAndDestBucketKey* bucketKeys,
                                            IN const int                       bucketKeysLen,
                                            OUT std::string&                   jsonstr)     = 0;
    
    /**
     * 批量删除远程文件
     *
     * @param   [in]  const QiniuToken & token                   用户token信息
     * @param   [in]  const QiniuBucketKey * bucketKeys          QiniuBucketKey数组头指针，里面是要批量删除的文件名称，
     * @param   [in]  const int bucketKeysLen                    bucketKeys数组长度
     * @param   [out] std::string & jsonstr                      返回值，json字符串，当 QiniuCode QINIU_OK 其有意义 指明删除files操作的信息
     * @return  QINIU_NAMESPACE::QiniuCode                       错误码，当值为QINIU_OK时候，表示正确返回，否则可查询
     *                                                               IQiniuRemoteFile::getLastErrorInfo()得到提示信息
     * @exception <code>无异常抛出</code>
     */
    
    virtual QiniuCode deleteRemoteBatchFiles( IN  const QiniuToken&     token,
                                              IN  const QiniuBucketKey* bucketKeys,
                                              IN  const int             bucketKeysLen,
                                              OUT std::string&         jsonstr)             = 0;
    

    /**
     * 当上方接口返回非QINIU_OK错误码时候，其给出辅助信息
     *
     * @return  const char*辅助信息，仅仅指出最后一次出错的信息
     * @exception <code>无异常抛出</code>
     */
    virtual const char* getLastErrorInfo()                                                  = 0;


    ~IQiniuRemoteBatchFiles() = 0;
};

QINIU_NAMESPACE_END

/******************************************************************************/
#endif// IQINIUREMOTEBATCHFILES_6D902195_7AB3_4F5C_8CF4_EE662C8A1D10_H__