/*******************************************************************************
 *  @file      MiscConfig.h 2013\4\25 14:53:39 $
 *  @author    Wang Xiaotao<wangxiaotao1980@gmail.com>(中文编码测试)
 
 ******************************************************************************/

#ifndef MISCCONFIG_ABE90963_C0DB_4B63_8EA2_8BA096A13299_H__
#define MISCCONFIG_ABE90963_C0DB_4B63_8EA2_8BA096A13299_H__

#include "../Config/Config.h"
/******************************************************************************/

#define  CPS_MISC_NAMESPACE CPS_misc
#if defined(__cplusplus)
    #define  CPS_MISC_NAMESPACE_BEGIN \
        namespace CPS_MISC_NAMESPACE\
            {

    #define  CPS_MISC_NAMESPACE_END \
            }

#endif

#if defined(CPS_ALL_DYNAMIC_LINK) || defined(CPS_MISC_DYNAMIC_LINK)
    #if defined(CPS_ALL_SOURCE) || defined(CPS_MISC_SOURCE) 
        #define CPS_MISC_API_DECL CPS_SYMBOL_EXPORT
    #else
        #define CPS_MISC_API_DECL CPS_SYMBOL_IMPORT
    #endif
#else
    #define CPS_MISC_API_DECL
#endif

/**
 * @def IN
 * 定义参数为输入或者的标识符
 */

#if defined(IN)
    #undef IN
#endif

#define IN


/**
 * @def OUT
 * 定义参数为输出或者说返回值的标识符
 */
#if defined(OUT)
    #undef OUT
#endif

#define OUT

/******************************************************************************/
#endif// MISCCONFIG_ABE90963_C0DB_4B63_8EA2_8BA096A13299_H__
