/*******************************************************************************
 *  @file      WorkThreadConfig.h 2013\6\19 14:05:04 $
 *  @author    Wang Xiaotao<wangxiaotao1980@gmail.com>(中文编码测试)
 
 ******************************************************************************/

#ifndef WORKTHREADCONFIG_C4C26BCC_26F1_46C5_A0E2_9212D444C7EC_H__
#define WORKTHREADCONFIG_C4C26BCC_26F1_46C5_A0E2_9212D444C7EC_H__

#include "../Config/Config.h"
/******************************************************************************/
/**
 * @def CPS_QINIU_NAMESPACE
 * 定义麦库API命名空间
 */

#define  CPS_WORK_THREAD_NAMESPACE CPS_work_thread

#if defined(__cplusplus)

    #define  CPS_WORK_THREAD_NAMESPACE_BEGIN \
        namespace CPS_WORK_THREAD_NAMESPACE \
            {

    #define  CPS_WORK_THREAD_NAMESPACE_END \
            }
#endif


#if defined(CPS_ALL_DYNAMIC_LINK) || defined(CPS_WORK_THREAD_DYNAMIC_LINK)
    #if defined(CPS_ALL_SOURCE) || defined(CPS_WORK_THREAD_SOURCE) 
        #define CPS_WORK_THREAD_DECL CPS_SYMBOL_EXPORT
    #else
        #define CPS_WORK_THREAD_DECL CPS_SYMBOL_IMPORT
    #endif
#else
    #define CPS_WORK_THREAD_DECL
#endif

/******************************************************************************/
#endif// WORKTHREADCONFIG_C4C26BCC_26F1_46C5_A0E2_9212D444C7EC_H__
