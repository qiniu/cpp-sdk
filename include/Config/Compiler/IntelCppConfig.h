/*******************************************************************************
 *  @file      IntelCppConfig.h 2013\1\9 18:12:14 $
 *  @author    Wang Xiaotao<wangxiaotao1980@gmail.com>
 *  Intel Cpp 编译器特性设置
 ******************************************************************************/

#ifndef INTELCPPCONFIG_51F45AD2_7010_4810_BAD2_111734585889_H__
#define INTELCPPCONFIG_51F45AD2_7010_4810_BAD2_111734585889_H__

// intel编译器使用EDG的前端 
#include "EdgConfig.h"
/******************************************************************************/
// 编译器名称
#define  CPS_COMPILER_NAME "Intel C++"

// 版本号
#if defined(__INTEL_COMPILER)
    #define CPS_COMPILER_VERSION CPS_STRINGIZE(__INTEL_COMPILER)
#elif defined(__ICL)
    #define CPS_COMPILER_VERSION CPS_STRINGIZE(__ICL)
#elif defined(__ICC)
    #define CPS_COMPILER_VERSION CPS_STRINGIZE(__ICC)
#elif defined(__ECC)
    #define CPS_COMPILER_VERSION CPS_STRINGIZE(__ECC)
#endif

// 编译器全称
#define  CPS_COMPILER_FULL_NAME CPS_COMPILER_NAME " " \
    CPS_COMPILER_VERSION


// 版本号，内部辅助宏
#if defined(__INTEL_COMPILER)
    #define CPS_LOCAL_INTEL_CPP_VER __INTEL_COMPILER
#elif defined(__ICL)
    #define CPS_LOCAL_INTEL_CPP_VER __ICL
#elif defined(__ICC)
    #define CPS_LOCAL_INTEL_CPP_VER __ICC
#elif defined(__ECC)
    #define CPS_LOCAL_INTEL_CPP_VER __ECC
#endif

// Intel C++ 2011 XE 是现在支持的最低版本。
#if (CPS_LOCAL_INTEL_CPP_VER < 1100)
#  error "Compiler not supported"
#endif

//
// Dynamic shared object (DSO) and dynamic-link library (DLL) support
// 表明这个intel编译器不是在Windows下运行的，设定导出函数
#if defined(__GNUC__) && (__GNUC__ >= 4)
    #define CPS_SYMBOL_EXPORT __attribute__((visibility("default")))
    #define CPS_SYMBOL_IMPORT
    #define CPS_SYMBOL_VISIBLE __attribute__((visibility("default")))
#endif


// 判断是否支持C++11标准(非Windows系统)
#if (!(defined(_WIN32) || defined(_WIN64)) \
    && defined(__STDC_HOSTED__) \
    && (__STDC_HOSTED__ && (CPS_LOCAL_INTEL_CPP_VER <= 1200))) \
    || defined(__GXX_EXPERIMENTAL_CPP0X__) \
    || defined(__GXX_EXPERIMENTAL_CXX0X__)

    #define CPS_LOCAL_INTEL_STDCXX11

#endif

// 判断是否支持C++11标准(Windows系统)
#if defined(_MSC_VER) && (_MSC_VER >= 1600)
    #define CPS_LOCAL_INTEL_STDCXX11
#endif

#if defined(_WIN32) || defined(_WIN64)
    #define CPS_INTEL_COMPILER_ON_WINDOWS  1
#else
    #define CPS_INTEL_COMPILER_ON_WINDOWS  0
#endif

#if defined(CPS_LOCAL_INTEL_STDCXX11)
    #define CPS_CXX_SUPPORT_CXX11
#endif


#if defined(CPS_LOCAL_INTEL_STDCXX11)
    #undef  CPS_NO_CXX11_STATIC_ASSERT
//
// 虽然以下可以通过测试案例, 但官方不支持，具体信息参见:
// http://software.intel.com/en-us/articles/c0x-features-supported-by-intel-c-compiler/
//
//  #undef  CPS_NO_CXX11_LAMBDAS
//  #undef  CPS_NO_CXX11_LOCAL_CLASS_TEMPLATE_PARAMETERS
//  #undef  CPS_NO_CXX11_DECLTYPE
//  #undef  CPS_NO_CXX11_AUTO_DECLARATIONS
//  #undef  CPS_NO_CXX11_AUTO_MULTIDECLARATIONS
#endif


#if defined(CPS_LOCAL_INTEL_STDCXX11) && (CPS_LOCAL_INTEL_CPP_VER >= 1200)
//  #undef  CPS_NO_CXX11_RVALUE_REFERENCES // Enabling this breaks Filesystem and Exception libraries
//  #undef  CPS_NO_CXX11_SCOPED_ENUMS  // doesn't really work!!
    #undef  CPS_NO_CXX11_DELETED_FUNCTIONS
    #undef  CPS_NO_CXX11_DEFAULTED_FUNCTIONS
    #undef  CPS_NO_CXX11_LAMBDAS
    #undef  CPS_NO_CXX11_LOCAL_CLASS_TEMPLATE_PARAMETERS
    #undef  CPS_NO_CXX11_DECLTYPE
    #undef  CPS_NO_CXX11_AUTO_DECLARATIONS
    #undef  CPS_NO_CXX11_AUTO_MULTIDECLARATIONS
#endif

// icl Version 12.1.0.233 Build 20110811 and possibly some other builds
// had an incorrect __INTEL_COMPILER value of 9999. Intel say this has been fixed. 
#if defined(CPS_LOCAL_INTEL_STDCXX11) && (CPS_LOCAL_INTEL_CPP_VER > 1200)
    #undef  CPS_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS
    #undef  CPS_NO_CXX11_NULLPTR
    #undef  CPS_NO_CXX11_RVALUE_REFERENCES
    //#undef  CPS_NO_SFINAE_EXPR
    #undef  CPS_NO_CXX11_TEMPLATE_ALIASES
    #undef  CPS_NO_CXX11_VARIADIC_TEMPLATES
// scoped enum 部分实现，
// http://software.intel.com/en-us/articles/c0x-features-supported-by-intel-c-compiler/
//  #undef  CPS_NO_CXX11_SCOPED_ENUMS 
#endif


#if defined(_MSC_VER) && (_MSC_VER <= 1700)
//
// 虽然 Intel 编译器支持如下C++11标准, 但在再MSVC兼容模式下是不支持的
//
    #define  CPS_NO_CXX11_HEADER_INITIALIZER_LIST
    #define  CPS_NO_CXX11_VARIADIC_TEMPLATES
    #define  CPS_NO_CXX11_DELETED_FUNCTIONS
    #define  CPS_NO_CXX11_DEFAULTED_FUNCTIONS
    #define  CPS_NO_CXX11_TEMPLATE_ALIASES
#endif



// 删除内部使用的宏，防止污染
#if defined(CPS_LOCAL_INTEL_STDCXX11)
    #undef  CPS_LOCAL_INTEL_STDCXX11
#endif

// 删除内部使用的宏，防止污染
#if defined(CPS_LOCAL_INTEL_CPP_VER)
    #undef  CPS_LOCAL_INTEL_CPP_VER
#endif

/******************************************************************************/
#endif// INTELCPPCONFIG_51F45AD2_7010_4810_BAD2_111734585889_H__
