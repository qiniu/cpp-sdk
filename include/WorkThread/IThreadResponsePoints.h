/*******************************************************************************
 *  @file      IThreadResponsePoints.h 2013\6\18 18:32:04 $
 *  @author    Wang Xiaotao<wangxiaotao1980@gmail.com>(中文编码测试)
 
 ******************************************************************************/

#ifndef ITHREADRESPONSEPOINTS_7D9A1FF3_81DD_4F18_9D2C_8FE3CEAC5EDE_H__
#define ITHREADRESPONSEPOINTS_7D9A1FF3_81DD_4F18_9D2C_8FE3CEAC5EDE_H__

#include "WorkThread/WorkThreadConfig.h"
/******************************************************************************/

CPS_WORK_THREAD_NAMESPACE_BEGIN

/**
 * The class <code>IThreadResponsePoints</code>
 * 夸平台线程控制实现接口，相应随时结束和暂停
 *
 */
struct CPS_WORK_THREAD_DECL IThreadResponsePoints
{
public:

    /**
     * 设定线程是否暂停
     *
     * @param   bool isPause    ture代表暂停 false代表不暂停
     * @return void
     */
    virtual void setThreadCanPause(bool isPause) = 0;

protected:

    /**
     * 线程暂停点，线程运行到此的时候可以相应暂停命令
     *
     * @return  void
     */
    virtual void ThreadPausePoint() = 0;

    /**
     * 线程终止点，线程运行到此的时候可以相应终止命令
     *
     * @return  void
     * @exception 
     */
    virtual void ThreadInterruptPoint() = 0;

public:

    virtual ~IThreadResponsePoints() = 0;
};

CPS_WORK_THREAD_NAMESPACE_END
/******************************************************************************/
#endif// ITHREADRESPONSEPOINTS_7D9A1FF3_81DD_4F18_9D2C_8FE3CEAC5EDE_H__
