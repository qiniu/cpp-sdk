/*******************************************************************************
 *  @file      QiniuError.h 2013\11\20 19:11:41 $
 *  @author    Wang Xiaotao<wangxiaotao1980@gmail.com>
 *
 ******************************************************************************/

#ifndef QINIUERROR_B98A9E61_AF77_4387_8EA7_A08442A15744_H__
#define QINIUERROR_B98A9E61_AF77_4387_8EA7_A08442A15744_H__

#include "QiniuConfig.h"
/******************************************************************************/
QINIU_NAMESPACE_BEGIN

/**
 * @typedef UInt32 QiniuCode;
 * @brief 七牛API错误码 Qiniu API error code
 */
typedef UInt32 QiniuCode;

//错误码

//错误掩码，error code flag
const QiniuCode  QINIU_FLAG         = 0x00000U; ///< 自定义错误码
const QiniuCode  CURL_FLAG          = 0x10000U; ///< 错误掩码，代表Curl产生的错误
const QiniuCode  HTTP_STANDARD_FLAG = 0x20000U; ///< Http标准掩码表示，表示其是Http定义的代码
const QiniuCode  JSON_PARSE_FLAG    = 0x40000U; ///< json解析错误



const QiniuCode  QINIU_OK                  = (QINIU_FLAG | 0); ///< 一切OK


const QiniuCode  QINIU_MODEL_INIT_FAIL     = (QINIU_FLAG | 1);  ///< 模块初始化错误
const QiniuCode  QINIU_INIT_CURL_ERROR     = (QINIU_FLAG | 2);  ///< curl初始化错误
const QiniuCode  QINIU_NO_HTTP_RETURN_CODE = (QINIU_FLAG | 3);  ///< HTTP请求未返回http代码
// 以上掩码继承自HttpAccess
const QiniuCode  QINIU_READ_FILE_ERROR     = (QINIU_FLAG | 4);  ///< 读文件错误
const QiniuCode  QINIU_WRITE_FILE_ERROR    = (QINIU_FLAG | 5);  ///< 写文件错误

const QiniuCode  THREAD_HAS_STARTED        = (QINIU_FLAG | 6);  ///< 线程已经开始
const QiniuCode  THREAD_HAS_ENDED          = (QINIU_FLAG | 7);  ///< 线程已经结束

// 本模块自定义

const QiniuCode QINIU_JSON_PARSE_ERROR     = (JSON_PARSE_FLAG | 1); ///< json解析错误
const QiniuCode QINIU_JSON_NO_ITEM         = (JSON_PARSE_FLAG | 2); ///< json无此条目

QINIU_NAMESPACE_END

/******************************************************************************/
#endif// QINIUERROR_B98A9E61_AF77_4387_8EA7_A08442A15744_H__
