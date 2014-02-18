/*******************************************************************************
 *  @file      ClangConfig.h 2013\1\9 18:14:36 $
 *  @author    Wang Xiaotao<wangxiaotao1980@gmail.com>
 *  Clang（LLVM项目前端）编译器的设置
 ******************************************************************************/

#ifndef CLANGCONFIG_6E06FB9D_5BA8_4485_BDE8_FC639B8007EB_H__
#define CLANGCONFIG_6E06FB9D_5BA8_4485_BDE8_FC639B8007EB_H__

#include "../FunctionMacro.h"
/******************************************************************************/

#define CPS_COMPILER_NAME "Clang C++"

#define CPS_COMPILER_VERSION \
    CPS_STRINGIZE(__clang_major__) "."\
    CPS_STRINGIZE(__clang_minor__) "."\
    CPS_STRINGIZE(__clang_patchlevel__)

#define  CPS_COMPILER_FULL_NAME CPS_COMPILER_NAME " " \
    CPS_COMPILER_VERSION

// clange 编译器仅支持3和以上版本
#if (__clang_major__ < 3)
    #error "Compiler not supported"
#endif


// C++ 是否支持异常
#if !__has_feature(cxx_exceptions) && !defined(CPS_NO_EXCEPTIONS)
    #define CPS_NO_EXCEPTIONS
#endif

// C++ 是否支持 RTTI（一般情况编程不开启这项）
#if !__has_feature(cxx_rtti) && !defined(CPS_NO_RTTI)
    #define CPS_NO_RTTI
#endif


// C++ 是否支持 typeid（一般情况编程不开启这项）
#if !__has_feature(cxx_rtti) && !defined(CPS_NO_TYPEID)
    #define CPS_NO_TYPEID
#endif

#if defined(__int64)
    #define CPS_HAS_MS_INT64
#endif


// Clang 在所有的兼容模式支持 "long long"
#define CPS_HAS_LONG_LONG


// 判断是否支持C++11标准
#if defined(__GXX_EXPERIMENTAL_CXX0X__) && !defined(CPS_SUPPORT_CXX11)
    #define CPS_CXX_SUPPORT_CXX11
#endif

// C++ 11 标准支持测试，clang使用__has_feature 函数测试
#if !__has_feature(cxx_auto_type)
    #define CPS_NO_CXX11_AUTO_DECLARATIONS
    #define CPS_NO_CXX11_AUTO_MULTIDECLARATIONS
#endif

#if !(defined(__GXX_EXPERIMENTAL_CXX0X__) || __cplusplus >= 201103L)
    #define CPS_NO_CXX11_CHAR16_T
    #define CPS_NO_CXX11_CHAR32_T
#endif

#if !__has_feature(cxx_constexpr)
    #define CPS_NO_CXX11_CONSTEXPR
#endif

#if !__has_feature(cxx_decltype)
    #define CPS_NO_CXX11_DECLTYPE
#endif

#if !__has_feature(cxx_decltype_incomplete_return_types)
    #define CPS_NO_CXX11_DECLTYPE_N3276
#endif

#if !__has_feature(cxx_defaulted_functions)
    #define CPS_NO_CXX11_DEFAULTED_FUNCTIONS
#endif

#if !__has_feature(cxx_deleted_functions)
    #define CPS_NO_CXX11_DELETED_FUNCTIONS
#endif

#if !__has_feature(cxx_explicit_conversions)
    #define CPS_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS
#endif

#if !__has_feature(cxx_default_function_template_args)
    #define CPS_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS
#endif

#if !__has_feature(cxx_generalized_initializers)
    #define CPS_NO_CXX11_HEADER_INITIALIZER_LIST
#endif

#if !__has_feature(cxx_lambdas)
    #define CPS_NO_CXX11_LAMBDAS
#endif

#if !__has_feature(cxx_local_type_template_args) && !__has_extension(cxx_local_type_template_args)
    #define CPS_NO_CXX11_LOCAL_CLASS_TEMPLATE_PARAMETERS
#endif

#if !__has_feature(cxx_noexcept)
    #define CPS_NO_CXX11_NOEXCEPT
#endif

#if !__has_feature(cxx_nullptr)
    #define CPS_NO_CXX11_NULLPTR
#endif

#if !__has_feature(cxx_range_for)
    #define CPS_NO_CXX11_RANGE_BASED_FOR
#endif

#if !__has_feature(cxx_raw_string_literals)
    #define CPS_NO_CXX11_RAW_LITERALS
#endif

#if !__has_feature(cxx_generalized_initializers)
    #define CPS_NO_CXX11_UNIFIED_INITIALIZATION_SYNTAX
#endif

#if !__has_feature(cxx_rvalue_references)
    #define CPS_NO_CXX11_RVALUE_REFERENCES
#endif

#if !__has_feature(cxx_strong_enums)
    #define CPS_NO_CXX11_SCOPED_ENUMS
#endif

#if !__has_feature(cxx_static_assert)
    #define CPS_NO_CXX11_STATIC_ASSERT
#endif

#if !__has_feature(cxx_alias_templates)
    #define CPS_NO_CXX11_TEMPLATE_ALIASES
#endif

#if !__has_feature(cxx_unicode_literals)
    #define CPS_NO_CXX11_UNICODE_LITERALS
#endif

// C++11 variadic templates 支持与否（可变模板参数）
#if !__has_feature(cxx_variadic_templates)
    #define CPS_NO_CXX11_VARIADIC_TEMPLATES
#endif

// 本文以下没有设定
//CPS_NO_CXX11_EXTERN_TEMPLATE

//CPS_NO_CXX11_VARIADIC_MACROS

/******************************************************************************/
#endif// CLANGCONFIG_6E06FB9D_5BA8_4485_BDE8_FC639B8007EB_H__
