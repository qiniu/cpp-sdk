/*******************************************************************************
 *  @file      MSVCConfig.h 2012\12\25 17:17:07 $
 *  @author    Wang Xiaotao<wangxiaotao1980@gmail.com>
 *  此文件定义微软C++编译器的特性（开发中）
 ******************************************************************************/

#ifndef MSVCCONFIG_EBD693FC_7364_4E71_BC4C_66CEF69C4ED2_H__
#define MSVCCONFIG_EBD693FC_7364_4E71_BC4C_66CEF69C4ED2_H__
/******************************************************************************/

#define CPS_COMPILER_NAME "Microsoft Visual C++"

#define CPS_COMPILER_VERSION \
    CPS_STRINGIZE(_MSC_VER)

#define  CPS_COMPILER_FULL_NAME CPS_COMPILER_NAME " " \
    CPS_COMPILER_VERSION


// 现行库不支持 vc 2008 以下下版本，现在仅仅支持到vc2008
#if (_MSC_VER < 1500)  // 150X == VC++ 9.0
    #error "Compiler not supported"
#endif


#if !defined(_CPPUNWIND) && !defined(CPS_NO_EXCEPTIONS)
    #define CPS_NO_EXCEPTIONS
#endif 


#if !defined(_CPPRTTI) && !defined(CPS_NO_RTTI)
    #define CPS_NO_RTTI
#endif


// Visual studio 不支持<fenv.h> C99 文件
#define CPS_NO_FENV_H

#define CPS_HAS_MS_INT64


// vc 2010 以上版本开始支持C++11标准, vc编译器没有一个宏说明它是否正在支持 C++11
#if (_MSC_VER >= 1600)  // 150X == VC++ 9.0
    #define CPS_CXX_SUPPORT_CXX11
#endif


// 从 visual studio studio 2010（_MSC_VER=1600） 开始有对 stdint.h（cstdint)的支持了,
// 但是以前的版本没有这个支持。 (stdint.h 在C99标准中出现，但是CXX98标准没定义，CXX11标准出现cstdint
#if _MSC_VER >= 1600
    #define CPS_HAS_STDINT_H
#endif

// 从visual studio 2010 开始部分支持 C++11标准
#if _MSC_VER < 1600
    #define CPS_NO_CXX11_AUTO_DECLARATIONS
    #define CPS_NO_CXX11_AUTO_MULTIDECLARATIONS
    #define CPS_NO_CXX11_LAMBDAS
    #define CPS_NO_CXX11_RVALUE_REFERENCES
    #define CPS_NO_CXX11_STATIC_ASSERT
    #define CPS_NO_CXX11_NULLPTR
    #define CPS_NO_CXX11_DECLTYPE
#endif // _MSC_VER < 1600

// vc 2012 开始支持的C++11标准特性
#if _MSC_VER < 1700
    #define CPS_NO_CXX11_RANGE_BASED_FOR
    #define CPS_NO_CXX11_SCOPED_ENUMS
    #define CPS_NO_CXX11_HEADER_CSTDINT
#endif // _MSC_VER < 1700


// vc 仍旧不被支持的 C++11特性

#define CPS_NO_CXX11_CONSTEXPR
#define CPS_NO_CXX11_CHAR16_T
#define CPS_NO_CXX11_CHAR32_T
#define CPS_NO_CXX11_DECLTYPE_N3276
#define CPS_NO_CXX11_DEFAULTED_FUNCTIONS
#define CPS_NO_CXX11_DELETED_FUNCTIONS
#define CPS_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS
#define CPS_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS
#define CPS_NO_CXX11_NOEXCEPT
#define CPS_NO_CXX11_RAW_LITERALS
#define CPS_NO_CXX11_TEMPLATE_ALIASES
#define CPS_NO_CXX11_UNICODE_LITERALS
#define CPS_NO_CXX11_VARIADIC_TEMPLATES
#define CPS_NO_CXX11_UNIFIED_INITIALIZATION_SYNTAX

// 以下由语法和一个头文件联合实现，vc现在还没有实现
#define CPS_NO_CXX11_HEADER_INITIALIZER_LIST


// CPS_NO_CXX11_LOCAL_CLASS_TEMPLATE_PARAMETERS 好像支持， 等待判断
#define  CPS_NO_CXX11_LOCAL_CLASS_TEMPLATE_PARAMETERS






// 本文以下没有设定
// extern template (确认支持)
//CPS_NO_CXX11_EXTERN_TEMPLATE

/******************************************************************************/
#endif// MSVCCONFIG_EBD693FC_7364_4E71_BC4C_66CEF69C4ED2_H__
