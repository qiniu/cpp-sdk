/*******************************************************************************
 *  @file      MacOS.h 2013\1\9 16:19:00 $
 *  @author    Wang Xiaotao<wangxiaotao1980@gmail.com>
 *  本文件定义Mac OS 操作系统特性
 ******************************************************************************/

#ifndef MACOS_6163CED6_5C8B_474B_8788_C12099697743_H__
#define MACOS_6163CED6_5C8B_474B_8788_C12099697743_H__

/******************************************************************************/

#define CPS_OS_NAME "MacOS"

// 暂时不支持 Metrowerks MSL 运行时

#ifndef CPS_HAS_POSIX_UNISTD_H
    #define CPS_HAS_POSIX_UNISTD_H
#endif

// POSIX特性的包含
#include "POSIXConfig.h"


#ifndef CPS_HAS_STDINT_H
    #define CPS_HAS_STDINT_H
#endif

// BSD 运行时存在
#define CPS_HAS_SCHED_YIELD
#define CPS_HAS_GETTIMEOFDAY
#define CPS_HAS_SIGACTION


#  if (__GNUC__ >= 4)
    #define CPS_HAS_PTHREAD_MUTEXATTR_SETTYPE
    #define CPS_HAS_POSIX_NANOSLEEP_FUNCTION
#  endif


/******************************************************************************/
#endif// MACOS_6163CED6_5C8B_474B_8788_C12099697743_H__
