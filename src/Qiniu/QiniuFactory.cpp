/******************************************************************************* 
 *  @file      QiniuFactory.cpp 2013\11\21 11:31:27 $
 *  @author    Wang Xiaotao<wangxiaotao1980@gmail.com> (中文编码测试)
 ******************************************************************************/

#include "Qiniu/QiniuFactory.h"
#include "Impl/QiniuRemoteFileImpl.h"
#include "Impl/QiniuRemoteBatchFilesImpl.h"
#include "Impl/QiniuUploadFileImpl.h"

/******************************************************************************/

QINIU_NAMESPACE_BEGIN

// -----------------------------------------------------------------------------
// class :  inherit from : 
// static   public  

IQiniuRemoteFile* QiniuFactory::CreateIQiniuRemoteFileObj()
{
    return new QiniuRemoteFileImpl();
}


// -----------------------------------------------------------------------------
// class :  inherit from : 
// static   public  

void QiniuFactory::DestoryIQiniuRemoteFileObj( IQiniuRemoteFile* qiniuRemoteObj )
{
    delete qiniuRemoteObj;
}
// -----------------------------------------------------------------------------
// class :  inherit from : 
// static   public  

IQiniuRemoteBatchFiles* QiniuFactory::CreateIQiniuRemoteBatchFilesObj()
{
    return new QiniuRemoteBatchFilesImpl();
}
// -----------------------------------------------------------------------------
// class :  inherit from : 
// static   public  

void QiniuFactory::DestoryIQiniuRemoteBatchFilesObj( IQiniuRemoteBatchFiles* QiniuRemoteBatchFilesObj )
{
    delete QiniuRemoteBatchFilesObj;
}


// -----------------------------------------------------------------------------
// class :  inherit from :  static   public  
IQiniuUploadFile* QiniuFactory::CreateIQiniuUploadFileObj()
{
    return new QiniuUploadFileImpl();
}
// -----------------------------------------------------------------------------
// class :  inherit from :  static   public  
void QiniuFactory::DestoryIQiniuUploadFileObj( IQiniuUploadFile* qiniuUploadFileObj )
{
     delete qiniuUploadFileObj;
}

QINIU_NAMESPACE_END
// 
// ---------------------------------------------------------------------------