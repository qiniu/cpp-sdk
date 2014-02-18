/*******************************************************************************
 *  @file      QiniuInternalConfig.h 2013\11\20 18:05:52 $
 *  @author    Wang Xiaotao<wangxiaotao1980@gmail.com>
 *
 ******************************************************************************/

#ifndef QINIUINTERNALCONFIG_F9BBB923_E77A_437C_B7E3_95BE72CB0BCD_H__
#define QINIUINTERNALCONFIG_F9BBB923_E77A_437C_B7E3_95BE72CB0BCD_H__

#include "Qiniu/QiniuConfig.h"
#include <string>

/******************************************************************************/

#if defined(CPS_NO_CXX11_SMART_PTR)

#include "boost/scoped_ptr.hpp"
#define QINIU_UNIQUE_PTR   boost::scoped_ptr

#else

#include <memory>
#define QINIU_UNIQUE_PTR   std::unique_ptr

#endif

// 空指针设定，对于C++11 和 C++98 都支持
#if defined(CPS_NO_CXX11_NULLPTR)
    #define QINIU_NULL_PTR  0
#else
    #define QINIU_NULL_PTR  nullptr
#endif

QINIU_NAMESPACE_BEGIN

// 内部测试 url
#if defined(INTERNAL_VERSION)

    const std::string HTTP_QINIU_RS_HOST    ("http://");
    const std::string HTTPS_QINIU_RS_HOST   ("https://");

    const std::string HTTP_QINIU_UP_HOST    ("http://");
    const std::string HTTPS_QINIU_UP_HOST   ("http://");

// 正式url
#else

    const std::string HTTP_QINIU_RS_HOST    ("http://rs.qbox.me");
    const std::string HTTPS_QINIU_RS_HOST   ("https://rs.qbox.me");

    const std::string HTTP_QINIU_RSF_HOST    ("http://rsf.qbox.me");
    const std::string HTTPS_QINIU_RSF_HOST   ("https://rsf.qbox.me");

    const std::string HTTP_QINIU_UP_HOST    ("http://up.qiniu.com");
    const std::string HTTPS_QINIU_UP_HOST   ("https://up.qiniu.com");

#endif
QINIU_NAMESPACE_END
/******************************************************************************/
#endif// QINIUINTERNALCONFIG_F9BBB923_E77A_437C_B7E3_95BE72CB0BCD_H__