/******************************************************************************* 
 *  @file      QiniuDestoryFunction.cpp 2013\4\26 14:13:23 $
 *  @author    Wang Xiaotao<wangxiaotao1980@gmail.com> (中文编码测试)
 *  @summary   接口的析构函数
 ******************************************************************************/


#include "Qiniu/IUpLoadProgress.h"
#include "Qiniu/IHttpSetting.h"
#include "Qiniu/IQiniuRemoteFile.h"
#include "Qiniu/IQiniuRemoteBatchFiles.h"
#include "Qiniu/IThreadProgress.h"
#include "Qiniu/IQiniuUploadFile.h"

/******************************************************************************/
QINIU_NAMESPACE_BEGIN

IUpLoadProgress::~IUpLoadProgress(){}

IHttpSetting::~IHttpSetting(){}

IQiniuRemoteFile::~IQiniuRemoteFile(){}

IQiniuRemoteBatchFiles::~IQiniuRemoteBatchFiles(){}

IThreadProgress::~IThreadProgress(){}

IQiniuUploadFile::~IQiniuUploadFile(){}

QINIU_NAMESPACE_END
// 
// -----------------------------------------------------------------------------
