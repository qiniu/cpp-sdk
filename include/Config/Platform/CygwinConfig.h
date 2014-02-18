/*******************************************************************************
 *  @file      CygwinConfig.h 2012\12\28 14:19:15 $
 *  @author    Wang Xiaotao<wangxiaotao1980@gmail.com>
 *  此文件定义Cygwin特性
 ******************************************************************************/

#ifndef CYGWINCONFIG_FF030940_4CBA_4710_A8B1_57568CDBF549_H__
#define CYGWINCONFIG_FF030940_4CBA_4710_A8B1_57568CDBF549_H__

/******************************************************************************/

#define CPS_OS_NAME "Cygwin"

//Cygwin 存在<dirent.h>头文件
#define CPS_HAS_POSIX_DIRENT_H

#if !defined(CPS_HAS_POSIX_UNISTD_H) 
    #define CPS_HAS_POSIX_UNISTD_H
#endif

#include <unistd.h>


#if defined(_POSIX_THREADS) && (_POSIX_THREADS+0 >= 0) && !defined(CPS_HAS_WINTHREADS)
    #define CPS_HAS_POSIX_PTHREAD_H
#else
    #if !defined(CPS_HAS_WINTHREADS)
        #define CPS_HAS_WINTHREADS
    #endif
#endif

//Cygwin 存在<sys/types.h>头文件
#include <sys/types.h>
#ifdef _STDINT_H
    #define CPS_HAS_STDINT_H
#endif

// Cygwin 不存在<fenv.h>头文件
#define CPS_NO_FENV_H

// Cygwin 为POSIX 标准兼容 OS，引入POSIX的特性
#include "POSIXConfig.h"


// Cygwin 不存在POSIX定义的XSI扩展头文件<nl_type.h>
#ifdef CPS_HAS_NL_TYPES_H
    #undef CPS_HAS_NL_TYPES_H
#endif


/******************************************************************************/
#endif// CYGWINCONFIG_FF030940_4CBA_4710_A8B1_57568CDBF549_H__
