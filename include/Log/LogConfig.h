/*******************************************************************************
 *  @file      LogConfig.h 2013\12\12 10:01:16 $
 *  @author    Wang Xiaotao<wangxiaotao1980@gmail.com> (中文编码测试)
 *
 ******************************************************************************/

#ifndef LOGCONFIG_514C642C_0065_41E4_AAF0_2F1E1342D341_H__
#define LOGCONFIG_514C642C_0065_41E4_AAF0_2F1E1342D341_H__

#include "../Config/Config.h"
/******************************************************************************/

#define  CPS_LOG_NAMESPACE CPS_LOG
#if defined(__cplusplus)
    #define  CPS_LOG_NAMESPACE_BEGIN \
        namespace CPS_LOG_NAMESPACE\
            {

    #define  CPS_LOG_NAMESPACE_END \
            }

#endif

#if defined(CPS_ALL_DYNAMIC_LINK) || defined(CPS_LOG_DYNAMIC_LINK)
    #if defined(CPS_ALL_SOURCE) || defined(CPS_LOG_SOURCE) 
        #define CPS_LOG_API_DECL CPS_SYMBOL_EXPORT
    #else
        #define CPS_LOG_API_DECL CPS_SYMBOL_IMPORT
    #endif
#else
    #define CPS_LOG_API_DECL
#endif


typedef char Utf8Char;

/******************************************************************************/
#endif// LOGCONFIG_514C642C_0065_41E4_AAF0_2F1E1342D341_H__