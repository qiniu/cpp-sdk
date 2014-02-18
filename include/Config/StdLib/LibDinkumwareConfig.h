/*******************************************************************************
 *  @file      LibDinkumwareConfig.h 2013\1\14 19:02:47 $
 *  @author    Wang Xiaotao<wangxiaotao1980@gmail.com>
 *  Dinkumware(Visual C++) 标准库设定
 ******************************************************************************/

#ifndef LIBDINKUMWARECONFIG_7A6B13B0_3503_4085_B26E_F48F3D77A592_H__
#define LIBDINKUMWARECONFIG_7A6B13B0_3503_4085_B26E_F48F3D77A592_H__

#include "../FunctionMacro.h"

/******************************************************************************/

// 使用标准库名称
#define CPS_STDLIB_NAME "Dinkumware c++"

// 使用标准库版本
#define CPS_STDLIB_VERSION CPS_STRINGIZE(_CPPLIB_VER)

// 使用标准库版本全名 名称 + 版本
#define CPS_STDLIB_FULL_NAME CPS_STDLIB_NAME " " \
    CPS_STRINGIZE(_CPPLIB_VER)



//   在Dinkumware的标准库中 C++11 头文件 520版本中实现的头文件

#if !defined(_CPPLIB_VER) || _CPPLIB_VER < 520
    #define CPS_NO_CXX11_HEADER_ARRAY
    #define CPS_NO_CXX11_HEADER_CODECVT
    #define CPS_NO_CXX11_HEADER_FORWARD_LIST
    #define CPS_NO_CXX11_HEADER_INITIALIZER_LIST
    #define CPS_NO_CXX11_HEADER_RANDOM
    #define CPS_NO_CXX11_HEADER_REGEX
    #define CPS_NO_CXX11_HEADER_SYSTEM_ERROR
    #define CPS_NO_CXX11_HEADER_UNORDERED_MAP
    #define CPS_NO_CXX11_HEADER_UNORDERED_SET
    #define CPS_NO_CXX11_HEADER_TUPLE
    #define CPS_NO_CXX11_HEADER_TYPEINDEX
    #define CPS_NO_CXX11_HEADER_FUNCTIONAL
    //#define CPS_NO_CXX11_NUMERIC_LIMITS
    #define CPS_NO_CXX11_SMART_PTR
#endif

#if (!defined(_HAS_TR1_IMPORTS) || (_HAS_TR1_IMPORTS+0 == 0)) && !defined(CPS_NO_CXX11_HDR_TUPLE)
#  define CPS_NO_CXX11_HDR_TUPLE
#endif


//  在Dinkumware的标准库中 C++11标准中仍旧未实现/完全实现的头文件

    #define CPS_NO_CXX11_HEADER_TYPE_TRAITS
    #define CPS_NO_CXX11_HEADER_CHRONO
    #define CPS_NO_CXX11_HEADER_CONDITION_VARIABLE
    #define CPS_NO_CXX11_HEADER_FUTURE
    #define CPS_NO_CXX11_HEADER_MUTEX
    #define CPS_NO_CXX11_HEADER_RATIO
    #define CPS_NO_CXX11_HEADER_THREAD

    //#define CPS_NO_CXX11_ALLOCATOR
    //#  define CPS_NO_CXX11_ATOMIC_SMART_PTR
/******************************************************************************/
#endif// LIBDINKUMWARECONFIG_7A6B13B0_3503_4085_B26E_F48F3D77A592_H__
