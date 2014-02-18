/*******************************************************************************
 *  @file      LogError.h 2013\12\12 10:18:38 $
 *  @author    Wang Xiaotao<wangxiaotao1980@gmail.com> (中文编码测试)
 *
 ******************************************************************************/

#ifndef LOGERROR_60897703_2F9A_4BC7_85CC_4CAFAE6E792F_H__
#define LOGERROR_60897703_2F9A_4BC7_85CC_4CAFAE6E792F_H__

#include "LogConfig.h"
/******************************************************************************/
CPS_LOG_NAMESPACE_BEGIN


typedef UInt32 LogCode; // log的错误码


//错误掩码，error code flag


const LogCode  LOG_FLAG    = 0x00000U; //自定义错误码


const LogCode  LOG_OK                  = LOG_FLAG | 0;
const LogCode  LOG_OPEN_LOG_FILE_FAIL  = LOG_FLAG | 1;


CPS_LOG_NAMESPACE_END
/******************************************************************************/
#endif// LOGERROR_60897703_2F9A_4BC7_85CC_4CAFAE6E792F_H__