/*******************************************************************************
 *  @file      PlatformConfig.h 2012\12\25 13:34:07 $
 *  @author    Wang Xiaotao<wangxiaotao1980@gmail.com>
 *  此文件主要定义了代表运行操作系统的宏 配置不同的操作系统
 ******************************************************************************/

#ifndef PLATFORMCONFIG_FFE22E16_A47B_46E6_B60D_3C4479FE1F19_H__
#define PLATFORMCONFIG_FFE22E16_A47B_46E6_B60D_3C4479FE1F19_H__

#include "Platform/OS32or64Bits.h"
/******************************************************************************/

#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
    //win32操作系统
    #define  CPS_OS_WINDOWS
    #include "Platform/Win32Config.h"

#elif defined(linux) || defined(__linux__) || defined(__linux)
// linux 和 android 操作系统
    #if defined(__ANDROID__)

        #define  CPS_OS_ANDROID
        #include "Platform/AndroidConfig.h"

    #else
        // linux操作系统
        #define  CPS_OS_LINUX
        #include "Platform/LinuxConfig.h"

    #endif

#elif defined(__APPLE__) || defined(macintosh) || defined(__APPLE_CC__)
// MAC OS X 和 IOS 操作系统
    #include <TargetConditionals.h>
    #if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR

        #define CPS_OS_IOS

    #elif TARGET_OS_MAC
        //mac os x 操作系统
        #define CPS_OS_MAC
        #include "Platform/MacOSConfig.h"

    #endif
#elif defined(__CYGWIN__)
    // cygwin 操作系统
    #define CPS_OS_CYGWIN
    #include "Platform/CygwinConfig.h"

#else
    // 等待增加 操作系统
    #error "Unknown Platform"
#endif



/******************************************************************************/
#endif// PLATFORMCONFIG_FFE22E16_A47B_46E6_B60D_3C4479FE1F19_H__
