/*******************************************************************************
 *  @file      QiniuFactory.h 2013\11\21 11:16:06 $
 *  @author    Wang Xiaotao<wangxiaotao1980@gmail.com> (中文编码测试)
 *
 ******************************************************************************/

#ifndef QINIUFACTORY_F60D4D91_D492_4B16_A4A8_FA4C8A5A614E_H__
#define QINIUFACTORY_F60D4D91_D492_4B16_A4A8_FA4C8A5A614E_H__

#include "QiniuConfig.h"
#include "WorkThread/WorkThreadConfig.h"
/******************************************************************************/
CPS_WORK_THREAD_NAMESPACE_BEGIN

struct IThreadControl;

CPS_WORK_THREAD_NAMESPACE_END


QINIU_NAMESPACE_BEGIN

struct IQiniuRemoteFile;
struct IQiniuRemoteBatchFiles;
struct IQiniuUploadFile;
struct QiniuToken;

/**
 * The class <code>QiniuFactory</code> 七牛类工厂
 *
 */
class QINIU_API_DECL QiniuFactory
{
public:
    /**
     * 创建IQiniuRemoteFile接口对象
     *
     * @return  IQiniuRemoteFile*          返回IQiniuRemoteFile接口对象
     * @exception <code>无异常抛出</code>
     */

    static IQiniuRemoteFile* CreateIQiniuRemoteFileObj();

    /**
     * 销毁由QiniuFactory::CreateIQiniuRemoteFileObj() 创建的 IQiniuRemoteFile接口对象
     *
     * @param   IQiniuRemoteFile * qiniuRemoteObj   要销毁的对象指针
     * @return  void
     * @exception <code>无异常抛出</code>
     */
    static void              DestoryIQiniuRemoteFileObj(IQiniuRemoteFile* qiniuRemoteObj);

    /**
     * 创建IQiniuRemoteBatchFiles接口对象
     *
     * @return  IQiniuRemoteBatchFiles* 返回IQiniuRemoteBatchFiles接口对象
     * @exception <code>无异常抛出</code>
     */
    
    static IQiniuRemoteBatchFiles* CreateIQiniuRemoteBatchFilesObj();


    /**
     * 销毁由QiniuFactory::CreateIQiniuRemoteBatchFilesObj() 创建的IQiniuRemoteBatchFiles接口对象
     *
     * @param   IQiniuRemoteBatchFiles * QiniuRemoteBatchFilesObj  要销毁的对象指针
     * @return  void
     * @exception <code>无异常抛出</code>
     */
    static void  DestoryIQiniuRemoteBatchFilesObj(IQiniuRemoteBatchFiles* QiniuRemoteBatchFilesObj);


    /**
     * 创建IQiniuUploadFile接口对象
     *
     * @return  IQiniuUploadFile*  返回IQiniuUploadFile接口对象指针
     * @exception <code>无异常抛出</code>
     */
    
    static IQiniuUploadFile* CreateIQiniuUploadFileObj();

    /**
     * 销毁由QiniuFactory::CreateIQiniuUploadFileObj() 创建的IQiniuUploadFile接口对象
     *
     * @param   IQiniuUploadFile * qiniuUploadFileObj  要销毁的对象指针
     * @return  void
     * @exception <code>无异常抛出</code>
     */
    static void DestoryIQiniuUploadFileObj(IQiniuUploadFile* qiniuUploadFileObj);

};


QINIU_NAMESPACE_END
/******************************************************************************/
#endif// QINIUFACTORY_F60D4D91_D492_4B16_A4A8_FA4C8A5A614E_H__