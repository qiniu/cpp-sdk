/*******************************************************************************
 *  @file      WorkThreadBaseClass.h 2013\6\19 11:09:50 $
 *  @author    Wang Xiaotao<wangxiaotao1980@gmail.com>(中文编码测试)
 
 ******************************************************************************/

#ifndef WORKTHREADBASECLASS_A777EC05_5D45_4881_86A6_CFF9EE16FC47_H__
#define WORKTHREADBASECLASS_A777EC05_5D45_4881_86A6_CFF9EE16FC47_H__

#include "IThreadControl.h"
#include "IThreadResponsePoints.h"

#include "boost/thread.hpp"

/******************************************************************************/
CPS_WORK_THREAD_NAMESPACE_BEGIN

/**
 * The class <code>WorkThreadBaseClass</code>
 *
 */
class WorkThreadBaseClass : public IThreadResponsePoints
                          , public IThreadControl
{
public:
    /** @name Constructors and Destructor*/

    //@{
    /**
     * No Parameter Constructor 
     */
    WorkThreadBaseClass();
    /**
     * Destructor
     */
    virtual ~WorkThreadBaseClass();

    virtual void setThreadCanPause( bool isPause );
    virtual void ThreadPausePoint();
    virtual void ThreadInterruptPoint();


    virtual WorkThreadCode startThread();
    virtual WorkThreadCode endThread();
    virtual WorkThreadCode pauseThread();
    virtual WorkThreadCode resumeThread();

    //@}

public:
    /** @name Setter Methods*/
    //@{

    //@}
public:
    /** @name Getter Methods*/
    //@{

    //@}
public:
    /** @name Access Methods*/
    //@{

    //@}  

protected:

    static void threadFunction(WorkThreadBaseClass* pThis);

protected:
    virtual void processWorkThread();
protected:

    boost::thread*                  m_pMainThread;    ///< 主线程的boost对象
    bool                            m_isThreadStart;  ///< 判断线程是否开始
    // 以下三个变量用于 配合完成线程中的暂停、恢复控制
    bool                            m_isThreadCanPause;  ///< 线程是否暂停
    // 以下两个线程配合使用
    boost::condition_variable_any   m_condPause;      ///<
    boost::mutex                    m_mutexPause;     ///<
};

CPS_WORK_THREAD_NAMESPACE_END
/******************************************************************************/
#endif// WORKTHREADBASECLASS_A777EC05_5D45_4881_86A6_CFF9EE16FC47_H__
