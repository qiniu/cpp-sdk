/*******************************************************************************
 *  @file      LogUtils.h 2013\12\12 10:14:05 $
 *  @author    Wang Xiaotao<wangxiaotao1980@gmail.com> (中文编码测试)
 *
 ******************************************************************************/

#ifndef LOGUTILS_A941E8B7_2EB0_44E5_8D99_62BB7B01227A_H__
#define LOGUTILS_A941E8B7_2EB0_44E5_8D99_62BB7B01227A_H__

#include "LogConfig.h"
#include "LogError.h"

#include <fstream>

/******************************************************************************/

CPS_LOG_NAMESPACE_BEGIN


    CPS_LOG_API_DECL LogCode  Initialize(const Utf8Char* pFilepath);


    CPS_LOG_API_DECL void LogLock();
    CPS_LOG_API_DECL void LogUnLock();

    CPS_LOG_API_DECL void Terminate();

CPS_LOG_NAMESPACE_END
/******************************************************************************/
#endif// LOGUTILS_A941E8B7_2EB0_44E5_8D99_62BB7B01227A_H__