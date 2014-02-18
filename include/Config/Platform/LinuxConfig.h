/*******************************************************************************
 *  @file      Linux.h 2013\1\9 15:42:16 $
 *  @author    Wang Xiaotao<wangxiaotao1980@gmail.com>
 *  本文件定义linux操作系统特性
 ******************************************************************************/

#ifndef LINUX_73B28821_6F68_40CB_AE5F_45CA2EE7CDA9_H__
#define LINUX_73B28821_6F68_40CB_AE5F_45CA2EE7CDA9_H__

/******************************************************************************/

#define CPS_OS_NAME "linux"

// 确认 __GLIBC_PREREQ 宏是否可用
#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

//
// <stdint.h> 头文件在 glibc 2.1.1 版本后可用
// 这里确认其版本
//
#if defined(__GLIBC__) && ((__GLIBC__ > 2) || ((__GLIBC__ == 2) && (__GLIBC_MINOR__ >= 1)))
// <stdint.h> 肯定定义了 int64_t , 然而在 <sys/types.h> 内仅仅在定义__GNUC__下才定义int64_t
// 因此仅仅当使用GCC编译器的时候我们才确认<stdint.h>可用
#  if defined __GNUC__
#    define CPS_HAS_STDINT_H
#  endif
#endif


// 当glibc的版本为2或者以上时候，定义了函数gettimeofday
// 早期版本不确定

#if defined(__GLIBC__) && (__GLIBC__ >= 2)
    #define CPS_HAS_GETTIMEOFDAY
#endif

// nanosleep 函数是否可用
#ifdef __USE_POSIX199309
    #define CPS_HAS_POSIX_NANOSLEEP_FUNCTION
#endif

#if defined(__GLIBC__) && defined(__GLIBC_PREREQ)
// __GLIBC_PREREQ宏自 glibc 2.1.2开始定义

    // swprintf 函数自 glibc 2.2.0开始定义
    #if !__GLIBC_PREREQ(2,2) || (!defined(__USE_ISOC99) && !defined(__USE_UNIX98))
        #define CPS_NO_SWPRINTF
    #endif
#else
    #define CPS_NO_SWPRINTF
#endif


// linux 虽然没有同过 posix 标准官方认证，但是的确是符合posix标准的操作系统
// 引入posix 标准设定代码
#if !defined(CPS_HAS_POSIX_UNISTD_H)
    #define CPS_HAS_POSIX_UNISTD_H
#endif

#include "POSIXConfig.h"

#define CPS_HAS_PTHREAD_YIELD



#ifndef __GNUC__
// 虽然编译器并不是gcc 我们仍然要解析GNU的头文件(主要在 <stdint.h>文件中)
// 以下是GNU系统指定的扩展
    #ifndef __extension__
        #define __extension__
    #endif

    #ifndef __const__
        #define __const__ const
    #endif

    #ifndef __volatile__
        #define __volatile__ volatile
    #endif

    #ifndef __signed__
        #define __signed__ signed
    #endif
    #ifndef __typeof__
        #define __typeof__ typeof
    #endif

    #ifndef __inline__
        #define __inline__ inline
    #endif

#endif // __GNU__
/******************************************************************************/
#endif// LINUX_73B28821_6F68_40CB_AE5F_45CA2EE7CDA9_H__
