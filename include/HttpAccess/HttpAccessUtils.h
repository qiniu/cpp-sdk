/*******************************************************************************
 *  @file      HttpAccessUtils.h 2013\3\8 11:25:16 $
 *  @author    Wang Xiaotao<wangxiaotao1980@gmail.com> 中文编码测试
 
 ******************************************************************************/

#ifndef HTTPACCESSUTILS_739CAED9_7DF7_414A_B74E_8A5BD89C4C41_H__
#define HTTPACCESSUTILS_739CAED9_7DF7_414A_B74E_8A5BD89C4C41_H__

#include"HttpAccessConfig.h"
#include "HttpAccessError.h"
/******************************************************************************/

CPS_HTTPACCESS_NAMESPACE_BEGIN

/**
 * 初始化HttpAccess模块
 *
 * @return HttpAccessCode 返回 HTTPACCESS_OK 代表 初始化成功
                          返回 HTTPACCESS_MODEL_INIT_FAIL 代表 初始化不成功
 */
CPS_HTTPACCESS_API_DECL HttpAccessCode Initialize();

/**
 * 反初始化HttpAccess模块
 *
 * @return  void
 *
 */
CPS_HTTPACCESS_API_DECL void Terminate();

CPS_HTTPACCESS_API_DECL const char* getErrorCodeInfo(HttpAccessCode code);

CPS_HTTPACCESS_NAMESPACE_END
/******************************************************************************/
#endif// HTTPACCESSUTILS_739CAED9_7DF7_414A_B74E_8A5BD89C4C41_H__
