/*******************************************************************************
 *  @file      IUpLoadProgress.h 2013\6\5 10:54:20 $
 *  @author    Wang Xiaotao<wangxiaotao1980@gmail.com>(中文编码测试)
 
 ******************************************************************************/

#ifndef IUPLOADPROCESS_0AE519D8_3D5F_4072_9983_4F0062BD6A8A_H__
#define IUPLOADPROCESS_0AE519D8_3D5F_4072_9983_4F0062BD6A8A_H__

#include "QiniuConfig.h"
#include <ctime>
/******************************************************************************/
QINIU_NAMESPACE_BEGIN

/**
 * The struct <code>IUpLoadProgress</code>定义上传文件回调接口
 *
 */
struct QINIU_API_DECL IUpLoadProgress
{
public:
    /**
     * 开始上传文件通知
     *
     * @param   time_t theTime               发出通知时间
     * @return  void
     * @exception  无异常抛出
     */
    virtual void OnBeginUploadFile(time_t theTime, 
                                   double totalsize,
                                   const char* pname) = 0;
    /**
     * 文件上传进程通知 
     *
     * @param   time_t theTime               发出通知时间
     * @param   double totalsize             上传信息总大小
     * @param   double nowsize               现在上传的大小
     * @return  void
     * @exception 
     */
    virtual void OnProcessUploadFile(time_t theTime, double totalsize, double nowsize) = 0;
    /**
     * 上传文件结束通知
     *
     * @param   time_t theTime               发出通知时间
     * @return  void
     * @exception 
     */
    virtual void OnEndUploadFile(time_t theTime, double totalsize, const char* pName) = 0;
    /**
     * 文件上传失败通知
     *
     * @param   time_t theTime              发出通知时间
     * @return  void
     * @exception 
     */
    virtual void OnFailUploadFile(time_t theTime, const char* pName) = 0;


    virtual ~IUpLoadProgress()                    =  0;

};

QINIU_NAMESPACE_END

/******************************************************************************/
#endif// IUPLOADPROCESS_0AE519D8_3D5F_4072_9983_4F0062BD6A8A_H__
