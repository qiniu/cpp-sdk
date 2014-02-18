/*******************************************************************************
 *  @file      CompilerConfig.h 2012\12\25 14:11:26 $
 *  @author    Wang Xiaotao<wangxiaotao1980@gmail.com>
 *  此文件主要定义了代表编译器的宏，配置不同编译器
 ******************************************************************************/

#ifndef COMPILERCONFIG_950673B2_9779_4DFC_8DEB_E9769E1CFAC7_H__
#define COMPILERCONFIG_950673B2_9779_4DFC_8DEB_E9769E1CFAC7_H__

/******************************************************************************/

#if defined(__clang__)
// clang 编译器模拟并兼容 gcc 编译器，因此其必须出现在gcc编译器之前
    #define CPS_COMPILER_CLANG_CPP
    #include "Compiler/ClangConfig.h"
#elif defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC) || defined(__ECC)
// intel 编译器
    #define  CPS_COMILER_INTEL_CPP
    #include "Compiler/IntelCppConfig.h"
#elif defined(__GNUC__)
// GUN C++ 编译器
    #define  CPS_COMILER_GCC_CPP
    #include "Compiler/GccConfig.h"
#elif defined(__BORLANDC__)
// Borland C++ Build 编译器
    #define CPS_COMPILER_BORLAND_CPP
#elif defined(_MSC_VER)
// Microsoft C++ 编译器
    #define CPS_COMILER_MSVC_CPP
    #include "Compiler/MSVCConfig.h"
#else
    #error "Unknown compiler"
#endif // __clang__


/******************************************************************************/
#endif// COMPILERCONFIG_950673B2_9779_4DFC_8DEB_E9769E1CFAC7_H__
