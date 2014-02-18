/*******************************************************************************
 *  @file      CurlWrapperConfig.h 2013\5\3 3:41:39 $
 *  @author    Wang Xiaotao<wangxiaotao1980@gmail.com>(中文编码测试)
 
 ******************************************************************************/

#ifndef CURLWRAPPERCONFIG_C8E8C47E_7518_4620_9681_8FCD85C7623A_H__
#define CURLWRAPPERCONFIG_C8E8C47E_7518_4620_9681_8FCD85C7623A_H__

#include "Config/Config.h"
/******************************************************************************/


// 空指针设定，对于C++11 和 C++98 都支持
#if defined(CPS_NO_CXX11_NULLPTR)
    #define CPS_HTTPACCESS_NULL_PTR  0
#else
    #define CPS_HTTPACCESS_NULL_PTR  nullptr
#endif

//http(s)超时默认值，无超时限制

#define HTTP_NO_TIMEOUT 0U

//http(s)没有速度限制 

#define HTTP_NO_SPEED_LIMITED 0U  


/******************************************************************************/
#endif// CURLWRAPPERCONFIG_C8E8C47E_7518_4620_9681_8FCD85C7623A_H__
