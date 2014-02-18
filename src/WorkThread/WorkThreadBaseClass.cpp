/******************************************************************************* 
 *  @file      WorkThreadBaseClass.cpp 2013\6\24 10:44:54 $
 *  @author    Wang Xiaotao<wangxiaotao1980@gmail.com> (中文编码测试)
 ******************************************************************************/

#include "WorkThread/WorkThreadBaseClass.h"
/******************************************************************************/

CPS_WORK_THREAD_NAMESPACE_BEGIN
// -----------------------------------------------------------------------------
//  WorkThreadBaseClass: Public, Constructor

WorkThreadBaseClass::WorkThreadBaseClass()
    : m_pMainThread(0)
    , m_isThreadStart(false)
    , m_isThreadCanPause(false)
{}

// -----------------------------------------------------------------------------
//  WorkThreadBaseClass: Public, Destructor

WorkThreadBaseClass::~WorkThreadBaseClass()
{
    if (0 != m_pMainThread)
    {
        delete m_pMainThread;
        m_pMainThread = 0;
    }
}

// -----------------------------------------------------------------------------
// public   
void WorkThreadBaseClass::setThreadCanPause( bool isPause )
{
    m_isThreadCanPause = isPause;
}

// -----------------------------------------------------------------------------
// public   
void WorkThreadBaseClass::ThreadPausePoint()
{
    boost::mutex::scoped_lock tempScopeLock(m_mutexPause);

    if (m_isThreadCanPause)
    {
        m_condPause.wait(tempScopeLock);
    }
}

// -----------------------------------------------------------------------------
// public   
void WorkThreadBaseClass::ThreadInterruptPoint()
{
    boost::this_thread::interruption_point();
}

// -----------------------------------------------------------------------------
// public   
WorkThreadCode WorkThreadBaseClass::startThread()
{
    WorkThreadCode resultCode = THREAD_OK;

    if (true == m_isThreadStart)
    {
        resultCode = THREAD_HAS_STARTED;
        return resultCode;
    }

    if (0 != m_pMainThread)
    {
        delete m_pMainThread;
        m_pMainThread = 0;
    }

    if (THREAD_OK == resultCode)
    {
        m_pMainThread = new boost::thread(WorkThreadBaseClass::threadFunction, this);
        m_isThreadStart = true;
    }

    return resultCode;

}

// -----------------------------------------------------------------------------
// public   
WorkThreadCode WorkThreadBaseClass::endThread()
{
    WorkThreadCode resultCode = THREAD_OK;

    if  (false == m_isThreadStart)
    {
        resultCode = THREAD_HAS_ENDED;
        return resultCode;
    }

    // 发出中断的消息，其中断将在ThreadInterruptPoint 和 ThreadPausePoint 点相应中断消息
    m_pMainThread->interrupt();
    m_pMainThread->join();
    delete m_pMainThread;
    m_pMainThread = 0;

    return resultCode;
}
// -----------------------------------------------------------------------------
// public   
WorkThreadCode WorkThreadBaseClass::pauseThread()
{
    WorkThreadCode resultCode = THREAD_OK;

    if  (false == m_isThreadStart)
    {
        resultCode = THREAD_HAS_ENDED;
        return resultCode;
    }

    setThreadCanPause(true);

    return resultCode;
}
// -----------------------------------------------------------------------------
// public   
WorkThreadCode WorkThreadBaseClass::resumeThread()
{
    WorkThreadCode resultCode = THREAD_OK;

    if  (false == m_isThreadStart)
    {
        resultCode = THREAD_HAS_ENDED;
        return resultCode;
    }

    setThreadCanPause(false);
    m_condPause.notify_all();

    return resultCode;
}

// -----------------------------------------------------------------------------
// protected  static  
void WorkThreadBaseClass::threadFunction( WorkThreadBaseClass* pThis )
{
    pThis->processWorkThread();
}
// -----------------------------------------------------------------------------
// class : WorkThreadBaseClass inherit from : IThreadResponsePoints
//  virtual  protected  

void WorkThreadBaseClass::processWorkThread()
{
    m_isThreadStart = false;
}

CPS_WORK_THREAD_NAMESPACE_END
// 
// -----------------------------------------------------------------------------
