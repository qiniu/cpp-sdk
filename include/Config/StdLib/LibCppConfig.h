/*******************************************************************************
 *  @file      LibCppConfig.h 2013\1\9 17:48:06 $
 *  @author    Wang Xiaotao<wangxiaotao1980@gmail.com>
 *  定义LLVM使用的libc++标准库特性
 ******************************************************************************/

#ifndef LIBCPPCONFIG_667D1586_D71C_4C85_972C_BFBD87A98920_H__
#define LIBCPPCONFIG_667D1586_D71C_4C85_972C_BFBD87A98920_H__

#include "../FunctionMacro.h"
/******************************************************************************/

#if !defined(_LIBCPP_VERSION)
    #include <ciso646>
    #if !defined(_LIBCPP_VERSION)
        #error "This is not libc++!"
    #endif
#endif

// 使用标准库名称
#define CPS_STDLIB_NAME "libc++"

// 使用标准库版本
#define CPS_STDLIB_VERSION CPS_STRINGIZE(_LIBCPP_VERSION)

// 使用标准库版本全名 名称 + 版本
#define CPS_STDLIB_FULL_NAME CPS_STDLIB_NAME " " \
            CPS_STRINGIZE(_LIBCPP_VERSION)


#ifdef _LIBCPP_HAS_NO_VARIADICS
    #define CPS_NO_CXX11_HEADER_TUPLE
#endif

//
// 目前为止libc++ 仍旧没有实现(或者完全实现的)的头文件
// <chrono>在libc++上已经经过测试，但相对权威的人士(boost.org)说其实现不稳定
#define CPS_NO_CXX11_HEADER_CHRONO
#define CPS_NO_CXX11_HEADER_FUTURE
#define CPS_NO_CXX11_HEADER_TYPE_TRAITS

// 等待确认
//#define CPS_NO_CXX11_ATOMIC_SMART_PTR


/******************************************************************************/
#endif// LIBCPPCONFIG_667D1586_D71C_4C85_972C_BFBD87A98920_H__
