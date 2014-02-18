/*******************************************************************************
 *  @file      QiniuConfig.h 2013\11\20 17:42:21 $
 *  @author    Wang Xiaotao<wangxiaotao1980@gmail.com>
 *
 ******************************************************************************/

#ifndef QINIUCONFIG_E97E1D20_33BF_4B01_9FD9_F38CD13F5331_H__
#define QINIUCONFIG_E97E1D20_33BF_4B01_9FD9_F38CD13F5331_H__

#include "../Config/Config.h"
/******************************************************************************/

#define  QINIU_NAMESPACE qiniu
#if defined(__cplusplus)
#define  QINIU_NAMESPACE_BEGIN \
    namespace QINIU_NAMESPACE\
            {

#define  QINIU_NAMESPACE_END \
            }

#endif

#if defined(CPS_ALL_DYNAMIC_LINK) || defined(QINIU_DYNAMIC_LINK)
    #if defined(CPS_ALL_SOURCE) || defined(QINIU_SOURCE) 
        #define QINIU_API_DECL CPS_SYMBOL_EXPORT
    #else
        #define QINIU_API_DECL CPS_SYMBOL_IMPORT
    #endif
#else
    #define QINIU_API_DECL
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
#endif// QINIUCONFIG_E97E1D20_33BF_4B01_9FD9_F38CD13F5331_H__