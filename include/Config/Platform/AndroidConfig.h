/*******************************************************************************
 *  @file      AndroidConfig.h 2013\2\20 16:29:49 $
 *  @author    Wang Xiaotao<wangxiaotao1980@gmail.com>
 *  this file defines ... ...
 ******************************************************************************/

#ifndef ANDROIDCONFIG_F4D019E8_B0A6_479D_A852_5078E1580694_H__
#define ANDROIDCONFIG_F4D019E8_B0A6_479D_A852_5078E1580694_H__
/******************************************************************************/

#define CPS_OS_NAME "Android"


// 确认 __GLIBC_PREREQ 宏是否可用
#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#if defined(__BIONIC__)
    #if defined( __ANDROID_API__) && (__ANDROID_API__ >= 3)
        #define CPS_HAS_STDINT_H
    #endif
#endif
// android 更改自linux支持posix 
#if !defined(CPS_HAS_POSIX_UNISTD_H)
    #define CPS_HAS_POSIX_UNISTD_H
#endif

#include "POSIXConfig.h"

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

#endif // __GNUC__

/******************************************************************************/
#endif// ANDROIDCONFIG_F4D019E8_B0A6_479D_A852_5078E1580694_H__
