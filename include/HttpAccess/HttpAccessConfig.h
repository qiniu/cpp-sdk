/*******************************************************************************
 *  @file      HttpAccessConfig.h 2013\3\6 22:52:51 $
 *  @author    Wang Xiaotao<wangxiaotao1980@gmail.com> 中文编码测试
 
 ******************************************************************************/

#ifndef HTTPACCESSCONFIG_4EC5F521_D16D_4ACB_93D7_9EC05CE86CE9_H__
#define HTTPACCESSCONFIG_4EC5F521_D16D_4ACB_93D7_9EC05CE86CE9_H__

#include "../Config/Config.h"
/******************************************************************************/


    #define  CPS_HTTPACCESS_NAMESPACE CPS_http_access

    #define  CPS_HTTPACCESS_NAMESPACE_BEGIN \
        namespace CPS_HTTPACCESS_NAMESPACE \
        {

    #define  CPS_HTTPACCESS_NAMESPACE_END \
        }


#if defined(CPS_ALL_DYNAMIC_LINK) || defined(CPS_HTTPACCESS_DYNAMIC_LINK)
    #if defined(CPS_ALL_SOURCE) || defined(CPS_HTTPACCESS_SOURCE) 
        #define CPS_HTTPACCESS_API_DECL CPS_SYMBOL_EXPORT
    #else
        #define CPS_HTTPACCESS_API_DECL CPS_SYMBOL_IMPORT
    #endif
#else
    #define CPS_HTTPACCESS_API_DECL
#endif

/******************************************************************************/
#endif// HTTPACCESSCONFIG_4EC5F521_D16D_4ACB_93D7_9EC05CE86CE9_H__
