/*******************************************************************************
 *  @file      IThreadControl.h 2013\6\19 11:24:56 $
 *  @author    Wang Xiaotao<wangxiaotao1980@gmail.com>(中文编码测试)
 
 ******************************************************************************/

#ifndef ITHREADCONTROL_7A8663B2_2094_4755_A4E1_8CED9C16A24C_H__
#define ITHREADCONTROL_7A8663B2_2094_4755_A4E1_8CED9C16A24C_H__

#include "WorkThreadConfig.h"
#include "WorkThreadError.h"
/******************************************************************************/

CPS_WORK_THREAD_NAMESPACE_BEGIN
/**
 * The struct <code>IThreadControl</code>
 *
 */
struct CPS_WORK_THREAD_DECL IThreadControl
{
public:
    /**
     * 开始线程
     *
     * @return  WorkThreadCode
     * @retval  THREAD_OK           代表成功开始
     * @retval  THREAD_HAS_STARTED  代表线程已经开始了
     */
    virtual WorkThreadCode startThread()  = 0;
    /**
     * 终止线程
     *
     * @return  WorkThreadCode
     * @retval  THREAD_OK           代表成功结束
     * @retval  THREAD_HAS_ENDED    代表线程已经结束了
     */
    virtual WorkThreadCode endThread()    = 0;
    /**
     * 暂停线程
     *
     * @return  WorkThreadCode      
     * @retval  THREAD_OK           代表成功发出暂停消息 
     *                              如果线程已经在暂停状态，没有任何影响。直接返回THREAD_OK
     *                              ，也就是说这是个消息的发送, 什么时候暂停，线程代码运行到暂停点相应。
     * @retval  THREAD_HAS_ENDED    代表线程已经结束了或则尚未开始，无法暂停
     */
    virtual WorkThreadCode pauseThread()  = 0;

    /**
     * 唤醒暂停运行的线程
     *
     * @return  WorkThreadCode      
     * @retval  THREAD_OK           代表成功发出恢复运行消息
     *                              如果线程已经在运行，没有任何影响。直接返回THREAD_OK
     * @retval  THREAD_HAS_ENDED    代表线程已经结束了或者尚未开始，无法暂停
     */
    virtual WorkThreadCode resumeThread() = 0;

    virtual ~IThreadControl() = 0;
};

CPS_WORK_THREAD_NAMESPACE_END
/******************************************************************************/
#endif// ITHREADCONTROL_7A8663B2_2094_4755_A4E1_8CED9C16A24C_H__
