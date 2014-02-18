/*******************************************************************************
 *  @file      GccConfig.h 2013\1\9 18:11:18 $
 *  @author    Wang Xiaotao<wangxiaotao1980@gmail.com>
 *  GNU GCC 编译器设置
 ******************************************************************************/

#ifndef GCCCONFIG_6211070A_B84B_499E_8D59_DD77E51E228B_H__
#define GCCCONFIG_6211070A_B84B_499E_8D59_DD77E51E228B_H__

#include "../FunctionMacro.h"
/******************************************************************************/

#define CPS_COMPILER_NAME "GNU C++"

#define CPS_COMPILER_VERSION \
            CPS_STRINGIZE(__GNUC__) "."\
            CPS_STRINGIZE(__GNUC_MINOR__) "."\
            CPS_STRINGIZE(__GNUC_PATCHLEVEL__)

#define  CPS_COMPILER_FULL_NAME CPS_COMPILER_NAME " " \
            CPS_COMPILER_VERSION

// gcc 编译器仅支持4和以上版本
#if (__GNUC__ < 4)
    #error "Compiler not supported"
#endif

#if !defined(__EXCEPTIONS) && !defined(CPS_NO_EXCEPTIONS)
    # define CPS_NO_EXCEPTIONS
#endif



//
// gcc implements the named return value optimization since version 3.1
//
#if __GNUC__ > 3 || ( __GNUC__ == 3 && __GNUC_MINOR__ >= 1 )
#define BOOST_HAS_NRVO
#endif

//
// Dynamic shared object (DSO) and dynamic-link library (DLL) support
//
#if __GNUC__ >= 4
    #if (defined(_WIN32) || defined(__WIN32__) || defined(WIN32)) && !defined(__CYGWIN__)
    // All Win32 development environments, including 64-bit Windows and MinGW, define 
    // _WIN32 or one of its variant spellings. Note that Cygwin is a POSIX environment,
    // so does not define _WIN32 or its variants.
        #define CPS_HAS_DECLSPEC
        #define CPS_SYMBOL_EXPORT __attribute__((dllexport))
        #define CPS_SYMBOL_IMPORT __attribute__((dllimport))
    #else
        #define CPS_SYMBOL_EXPORT __attribute__((visibility("default")))
        #define CPS_SYMBOL_IMPORT
    #endif

    #define CPS_SYMBOL_VISIBLE __attribute__((visibility("default")))
#else
    // 不是GCC编译器，CPS_SYMBOL_EXPORT
    // Config/Platform/Win32Config.h will define CPS_SYMBOL_EXPORT, etc., unless already defined  
    #define CPS_SYMBOL_EXPORT
#endif


// gcc-4.3 存在__GXX_RTTI 宏可以侦测，typeid 和 rtti 的设定
#if ((__GNUC__*10000 + __GNUC_MINOR__*100) >= 40300)
    #ifndef __GXX_RTTI
        #ifndef CPS_NO_TYPEID
            #define CPS_NO_TYPEID
        #endif
        #ifndef CPS_NO_RTTI
            #define CPS_NO_RTTI
        #endif
    #endif
#endif


// 判断是否支持C++11标准, 根据文档GNU从4.3版本开始支持C++0x(C++11)
#if defined(__GXX_EXPERIMENTAL_CXX0X__) && !defined(CPS_SUPPORT_CXX11)
    #define CPS_CXX_SUPPORT_CXX11
#endif

// GNU 4.3 C++ 11 标准
 #if ((__GNUC__*10000 + __GNUC_MINOR__*100) < 40300) || !defined(__GXX_EXPERIMENTAL_CXX0X__)
    #define CPS_NO_CXX11_DECLTYPE
    #define CPS_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS
    #define CPS_NO_CXX11_RVALUE_REFERENCES
    #define CPS_NO_CXX11_STATIC_ASSERT
#endif


// GNU 4.4 C++ 　标准
#if ((__GNUC__*10000 + __GNUC_MINOR__*100) < 40400) || !defined(__GXX_EXPERIMENTAL_CXX0X__)
    #define CPS_NO_CXX11_AUTO_DECLARATIONS
    #define CPS_NO_CXX11_AUTO_MULTIDECLARATIONS
    #define CPS_NO_CXX11_CHAR16_T
    #define CPS_NO_CXX11_CHAR32_T
    #define CPS_NO_CXX11_HEADER_INITIALIZER_LIST
    #define CPS_NO_CXX11_DEFAULTED_FUNCTIONS
    #define CPS_NO_CXX11_DELETED_FUNCTIONS
    #define CPS_NO_CXX11_VARIADIC_TEMPLATES
#endif

// GNU 4.5 C++ 标准

#if ((__GNUC__*10000 + __GNUC_MINOR__*100) < 40500) || !defined(__GXX_EXPERIMENTAL_CXX0X__)
    #define CPS_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS
    #define CPS_NO_CXX11_LAMBDAS
    #define CPS_NO_CXX11_LOCAL_CLASS_TEMPLATE_PARAMETERS
    #define CPS_NO_CXX11_RAW_LITERALS
    #define CPS_NO_CXX11_UNICODE_LITERALS
#endif

// GNU 4.4 对C++标准  scoped enums  存在严重bug ，在4.5.1开始修复，
#if (__GNUC__*10000 + __GNUC_MINOR__*100 + __GNUC_PATCHLEVEL__ < 40501) || !defined(__GXX_EXPERIMENTAL_CXX0X__)
    #define CPS_NO_CXX11_SCOPED_ENUMS
#endif

// GNU 4.6 C++ 标准
#if ((__GNUC__*10000 + __GNUC_MINOR__*100) < 40600) || !defined(__GXX_EXPERIMENTAL_CXX0X__)
    #define CPS_NO_CXX11_CONSTEXPR
    #define CPS_NO_CXX11_NOEXCEPT
    #define CPS_NO_CXX11_NULLPTR
    #define CPS_NO_CXX11_RANGE_BASED_FOR
    #define CPS_NO_CXX11_UNIFIED_INITIALIZATION_SYNTAX
#endif


// GNU 4.7 C++ 标准
#if ((__GNUC__*10000 + __GNUC_MINOR__*100) < 40700) || !defined(__GXX_EXPERIMENTAL_CXX0X__)
    #define CPS_NO_CXX11_TEMPLATE_ALIASES
#endif


// 到目前为止 GCC 仍旧不支持的 C++特性
#define CPS_NO_CXX11_DECLTYPE_N3276


/******************************************************************************/
#endif// GCCCONFIG_6211070A_B84B_499E_8D59_DD77E51E228B_H__
