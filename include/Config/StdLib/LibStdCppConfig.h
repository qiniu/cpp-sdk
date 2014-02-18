/*******************************************************************************
 *  @file      LibStdCppConfig.h 2013\1\9 17:49:42 $
 *  @author    Wang Xiaotao<wangxiaotao1980@gmail.com>
 *  定义GNU 使用的 libstdC++ 特性
 ******************************************************************************/

#ifndef LIBSTDCPPCONFIG_894965D5_820A_4B94_B0A6_94BA7BB7D732_H__
#define LIBSTDCPPCONFIG_894965D5_820A_4B94_B0A6_94BA7BB7D732_H__

#include "../FunctionMacro.h"

/******************************************************************************/

// 使用标准库名称
#define  CPS_STDLIB_NAME "GNU libstdc++"

// 使用标准库版本
//#if defined(__GLIBCXX__)
//    #define CPS_STDLIB_VERSION CPS_STRINGIZE(__GLIBCXX__)
//#else
//    #define CPS_STDLIB_VERSION CPS_STRINGIZE(__GLIBCPP__)
//#endif


#define CPS_STDLIB_VERSION \
    CPS_STRINGIZE(__GNUC__) "."\
    CPS_STRINGIZE(__GNUC_MINOR__) "."\
    CPS_STRINGIZE(__GNUC_PATCHLEVEL__)


// 使用标准库版本全名 名称 + 版本
#define  CPS_STDLIB_FULL_NAME CPS_STDLIB_NAME " " \
            CPS_STDLIB_VERSION

//  C++11 头文件特性实现情况在 GCC 4.3.0 以及以后版本
#if ((__GNUC__*10000 + __GNUC_MINOR__*100) < 40300) || !defined(__GXX_EXPERIMENTAL_CXX0X__)
    #define CPS_NO_CXX11_HEADER_ARRAY
    #define CPS_NO_CXX11_HEADER_REGEX
    #define CPS_NO_CXX11_HEADER_TUPLE
    #define CPS_NO_CXX11_HEADER_UNORDERED_MAP
    #define CPS_NO_CXX11_HEADER_UNORDERED_SET
    #define CPS_NO_CXX11_HEADER_FUNCTIONAL
#endif

//  C++11 头文件特性实现情况在 GCC 4.4.0 以及以后版本
#if ((__GNUC__*10000 + __GNUC_MINOR__*100) < 40400) || !defined(__GXX_EXPERIMENTAL_CXX0X__)
    #define CPS_NO_CXX11_HEADER_CONDITION_VARIABLE
    #define CPS_NO_CXX11_HEADER_FORWARD_LIST
    #define CPS_NO_CXX11_HEADER_INITIALIZER_LIST
    #define CPS_NO_CXX11_HEADER_MUTEX
    #define CPS_NO_CXX11_HEADER_RATIO
    #define CPS_NO_CXX11_HEADER_SYSTEM_ERROR
    #define CPS_NO_CXX11_SMART_PTR
#endif

//　以下好像有问题，暂时屏蔽，　此引起linux + clang3.2 + libstdc++ 4.6.3 condition_variable编译不过
#if (!defined(_GLIBCXX_HAS_GTHREADS) || !defined(_GLIBCXX_USE_C99_STDINT_TR1)) && (!defined(CPS_NO_CXX11_HEADER_CONDITION_VARIABLE) || !defined(CPS_NO_CXX11_HEADER_MUTEX))
    #define CPS_NO_CXX11_HEADER_CONDITION_VARIABLE
    #define CPS_NO_CXX11_HEADER_MUTEX
#endif


// C++11 头文件特性实现情况在 GCC 4.5.0  以及以后版本
#if ((__GNUC__*10000 + __GNUC_MINOR__*100) < 40500) || !defined(__GXX_EXPERIMENTAL_CXX0X__)
   //#define CPS_NO_CXX11_NUMERIC_LIMITS
    #define CPS_NO_CXX11_HEADER_FUTURE
    #define CPS_NO_CXX11_HEADER_RANDOM
#endif

//  C++11 头文件特性实现情况在 GCC 4.6.0 以及以后版本
#if ((__GNUC__*10000 + __GNUC_MINOR__*100) < 40600) || !defined(__GXX_EXPERIMENTAL_CXX0X__)
    #define CPS_NO_CXX11_HEADER_TYPEINDEX
#endif


//  C++11 头文件特性实现情况在 GCC 4.7.0 and later
#if ((__GNUC__*10000 + __GNUC_MINOR__*100) < 40700) || !defined(__GXX_EXPERIMENTAL_CXX0X__)
    //在4.6版本中存在<chrono>头文件但是缺少 std::chrono::steady_clock实现
    #define CPS_NO_CXX11_HEADER_CHRONO
#endif

// 以下是C++11标准中定义但 GCC根本未实现的或完全实现的头文件

#define CPS_NO_CXX11_HEADER_THREAD
#define CPS_NO_CXX11_HEADER_TYPE_TRAITS
#define CPS_NO_CXX11_HEADER_CODECVT

/******************************************************************************/
#endif// LIBSTDCPPCONFIG_894965D5_820A_4B94_B0A6_94BA7BB7D732_H__
