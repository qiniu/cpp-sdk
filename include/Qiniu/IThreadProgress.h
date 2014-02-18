/*******************************************************************************
 *  @file      IThreadProgress.h 2013\12\6 14:41:35 $
 *  @author    Wang Xiaotao<wangxiaotao1980@gmail.com> (÷–Œƒ±‡¬Î≤‚ ‘)
 *
 ******************************************************************************/

#ifndef ITHREADPRGRESS_6A0067C5_396A_4C9C_876D_47D287292FED_H__
#define ITHREADPRGRESS_6A0067C5_396A_4C9C_876D_47D287292FED_H__

#include "QiniuConfig.h"
/******************************************************************************/

QINIU_NAMESPACE_BEGIN

/**
 * The class <code>IThreadProgress</code>
 *
 */
struct QINIU_API_DECL IThreadProgress
{
public:
    virtual void startThread()                                   = 0;
    virtual void uploadFileNumber(int count)                     = 0;
    virtual void progressThread(int count, int n)                = 0;
    virtual void fileConflict(const char* scr, const char* dest) = 0;
    virtual void endThread()                                     = 0;
    virtual void pauseThread()                                   = 0;
    virtual void resumeThread()                                  = 0;

    virtual ~IThreadProgress()                                   = 0;
};


QINIU_NAMESPACE_END
/******************************************************************************/
#endif// ITHREADPRGRESS_6A0067C5_396A_4C9C_876D_47D287292FED_H__