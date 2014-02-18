/*******************************************************************************
 *  @file      HttpAccessError.h 2013\3\7 17:32:47 $
 *  @author    Wang Xiaotao<wangxiaotao1980@snda.com> 中文编码测试 
 *  this file defines ... ...
 ******************************************************************************/

#ifndef HTTPACCESSERROR_83855864_50F0_4585_9130_2AB387940E0B_H__
#define HTTPACCESSERROR_83855864_50F0_4585_9130_2AB387940E0B_H__

#include "HttpAccessConfig.h"
/******************************************************************************/

CPS_HTTPACCESS_NAMESPACE_BEGIN

typedef UInt32 HttpAccessCode;

//错误掩码，error code flag
const HttpAccessCode  HTTPACCESS_FLAG    = 0x00000U; //自定义错误码
const HttpAccessCode  CURL_FLAG          = 0x10000U; //错误掩码，代表Curl产生的错误
const HttpAccessCode  HTTP_STANDARD_FLAG = 0x20000U; //Http标准掩码表示，表示其是Http定义的代码

const HttpAccessCode  HTTPACCESS_OK                  = HTTPACCESS_FLAG | 0;
const HttpAccessCode  HTTPACCESS_MODEL_INIT_FAIL     = HTTPACCESS_FLAG | 1;
const HttpAccessCode  HTTPACCESS_INIT_CURL_ERROR     = HTTPACCESS_FLAG | 2;
const HttpAccessCode  HTPPACCESS_NO_HTTP_RETURN_CODE = HTTPACCESS_FLAG | 3;


CPS_HTTPACCESS_NAMESPACE_END
/******************************************************************************/
#endif// HTTPACCESSERROR_83855864_50F0_4585_9130_2AB387940E0B_H__
