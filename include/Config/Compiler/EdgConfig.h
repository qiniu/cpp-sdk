/*******************************************************************************
 *  @file      EdgConfig.h 2013\2\21 12:01:46 $
 *  @author    Wang Xiaotao<wangxiaotao1980@gmail.com>
 *  this file defines ... ...
 ******************************************************************************/

#ifndef EDGCONFIG_19C3A10A_3CEA_4918_AC84_4DBCE66A809A_H__
#define EDGCONFIG_19C3A10A_3CEA_4918_AC84_4DBCE66A809A_H__
/******************************************************************************/

    //编译器使用 edg 前端 所以包含edg宏判断
    #ifndef  __EDG_VERSION__
    #  error "This file requires that __EDG_VERSION__ be defined."
    #endif

    #if (__EDG_VERSION__ <= 238)
    #   define CPS_NO_INTEGRAL_INT64_T
    #   define CPS_NO_SFINAE
    #endif

    #if (__EDG_VERSION__ <= 240)
    #   define CPS_NO_VOID_RETURNS
    #endif


    # if !defined(__NO_LONG_LONG)
    #define CPS_HAS_LONG_LONG
    # else
    #define CPS_NO_LONG_LONG
    # endif

    //
    // C++0x features
    //
    #if (__EDG_VERSION__ < 310)
    #define CPS_NO_CXX11_EXTERN_TEMPLATE
    #endif

    #if (__EDG_VERSION__ <= 310)
    // No support for initializer lists
    #define CPS_NO_CXX11_HEADER_INITIALIZER_LIST
    #endif

    #if(__EDG_VERSION__ < 400)
    #define CPS_NO_CXX11_VARIADIC_MACROS
    #endif


    // C++ 标准暂时完全不支持
    #define CPS_NO_CXX11_AUTO_DECLARATIONS
    #define CPS_NO_CXX11_AUTO_MULTIDECLARATIONS
    #define CPS_NO_CXX11_CHAR16_T
    #define CPS_NO_CXX11_CHAR32_T
    #define CPS_NO_CXX11_CONSTEXPR
    #define CPS_NO_CXX11_DECLTYPE
    #define CPS_NO_CXX11_DECLTYPE_N3276
    #define CPS_NO_CXX11_DEFAULTED_FUNCTIONS
    #define CPS_NO_CXX11_DELETED_FUNCTIONS
    #define CPS_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS
    #define CPS_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS
    #define CPS_NO_CXX11_LAMBDAS
    #define CPS_NO_CXX11_LOCAL_CLASS_TEMPLATE_PARAMETERS
    #define CPS_NO_CXX11_NOEXCEPT
    #define CPS_NO_CXX11_NULLPTR
    #define CPS_NO_CXX11_RANGE_BASED_FOR
    #define CPS_NO_CXX11_RAW_LITERALS
    #define CPS_NO_CXX11_RVALUE_REFERENCES
    #define CPS_NO_CXX11_SCOPED_ENUMS
    #define CPS_NO_CXX11_STATIC_ASSERT
    #define CPS_NO_CXX11_TEMPLATE_ALIASES
    #define CPS_NO_CXX11_UNICODE_LITERALS
    #define CPS_NO_CXX11_VARIADIC_TEMPLATES
    #define CPS_NO_CXX11_UNIFIED_INITIALIZATION_SYNTAX

/******************************************************************************/
#endif// EDGCONFIG_19C3A10A_3CEA_4918_AC84_4DBCE66A809A_H__
