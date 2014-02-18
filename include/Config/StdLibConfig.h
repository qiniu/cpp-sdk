/*******************************************************************************
 *  @file      StdLibConfig.h 2012\12\25 15:03:06 $
 *  @author    Wang Xiaotao<wangxiaotao1980@gmail.com>
 *  对使用不同的标准库的设定（谨慎开发，了解甚少）
 ******************************************************************************/

#ifndef STDLIBCONFIG_AC66E29A_8DF0_4284_AE7F_AD98FDDAD6E8_H__
#define STDLIBCONFIG_AC66E29A_8DF0_4284_AE7F_AD98FDDAD6E8_H__

/******************************************************************************/

#ifdef __cplusplus
    #include <cstddef>
#else
    #include <stddef.h>
#endif

#if defined(__SGI_STL_PORT) || defined(_STLPORT_VERSION)
    // STLPort 标准库。 此分类务必最先出现，因为STLport 典型的依赖与其他的C++基础标准库
    #include "StdLib/STLPortConfig.h"

#else

    #if defined(_LIBCPP_VERSION)
        #define  CPS_STDLIB_LIBCPP
        #include "StdLib/LibCppConfig.h"

    #elif defined(__GLIBCPP__) || defined(__GLIBCXX__)
        #define  CPS_STDLIB_LIBSTDCPP
        #include "StdLib/LibStdCppConfig.h"

    #elif defined(_CPPLIB_VER)
        #define  CPS_STDLIB_DINKUMWARE
        #include "StdLib/LibDinkumwareConfig.h"

    #endif

#endif

/******************************************************************************/
#endif// STDLIBCONFIG_AC66E29A_8DF0_4284_AE7F_AD98FDDAD6E8_H__
