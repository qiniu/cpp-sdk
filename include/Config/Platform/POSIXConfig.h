/*******************************************************************************
 *  @file      POSIXConfig.h 2013\1\6 13:33:56 $
 *  @author    Wang Xiaotao<wangxiaotao1980@gmail.com>
 *  本文件主要设定符合POSIX规范操作系统特性
 ******************************************************************************/

#ifndef POSIXCONFIG_75D20667_139E_49BC_AA62_9C2E40BF6718_H__
#define POSIXCONFIG_75D20667_139E_49BC_AA62_9C2E40BF6718_H__
/******************************************************************************/

#if defined(CPS_HAS_POSIX_UNISTD_H)
    #include <unistd.h>

// POSIX 标准版本 6 需要 <stdint.h> 头文件
    #if defined(_POSIX_VERSION) && (_POSIX_VERSION >= 200100)
        #define CPS_HAS_STDINT_H
    #endif


// POSIX 标准版本 2 需要 <dirent.h> 头文件
    #if defined(_POSIX_VERSION) && (_POSIX_VERSION >= 199009L)
        #define CPS_HAS_POSIX_DIRENT_H
    #endif

// POSIX 标准版本 3 需要 <signal.h> 中存在函数 sigaction
    #if defined(_POSIX_VERSION) && (_POSIX_VERSION >= 199506L)
        #define CPS_HAS_SIGACTION
    #endif

// 如果pthread在POSIX中被支持，POSIX 定义 _POSIX_THREADS > 0 
// 然而有些平台仅仅定义 _POSIX_THREADS 而没有值存在
// 因此使用 (_POSIX_THREADS+0 >= 0) 检测
    #if defined(_POSIX_THREADS) && (_POSIX_THREADS+0 >= 0) && !defined(CPS_HAS_WINTHREADS)
        #define CPS_HAS_POSIX_PTHREAD_H
    #endif

// CPS_HAS_POSIX_NANOSLEEP_FUNCTION:
// This is predicated on _POSIX_TIMERS or _XOPEN_REALTIME:
    #if (defined(_POSIX_TIMERS) && (_POSIX_TIMERS+0 >= 0)) \
    || (defined(_XOPEN_REALTIME) && (_XOPEN_REALTIME+0 >= 0))
        #define CPS_HAS_POSIX_NANOSLEEP_FUNCTION
    #endif

// CPS_HAS_GETTIMEOFDAY:
// CPS_HAS_PTHREAD_MUTEXATTR_SETTYPE:
// These are predicated on _XOPEN_VERSION, and appears to be first released
// in issue 4, version 2 (_XOPEN_VERSION > 500).
// Likewise for the functions log1p and expm1.
    #if defined(_XOPEN_VERSION) && (_XOPEN_VERSION+0 >= 500)
        #define CPS_HAS_GETTIMEOFDAY
        #if defined(_XOPEN_SOURCE) && (_XOPEN_SOURCE+0 >= 500)
            #define CPS_HAS_PTHREAD_MUTEXATTR_SETTYPE
        #endif

        #ifndef CPS_HAS_C99_LOG1P_FUNCTION
            #define CPS_HAS_C99_LOG1P_FUNCTION
        #endif

        #ifndef CPS_HAS_C99_EXPM1_FUNCTION
            #define CPS_HAS_C99_EXPM1_FUNCTION
        #endif

    #endif



#endif


/******************************************************************************/
#endif// POSIXCONFIG_75D20667_139E_49BC_AA62_9C2E40BF6718_H__
