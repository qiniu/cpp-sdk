/*******************************************************************************
 *  @file      QiniuMisc.h 2013\11\21 15:10:14 $
 *  @author    Wang Xiaotao<wangxiaotao1980@gmail.com> (÷–Œƒ±‡¬Î≤‚ ‘)
 *
 ******************************************************************************/

#ifndef SECRETAUTH_7BA5CF81_5E0A_4351_9AEC_2FDD8A1A3DF7_H__
#define SECRETAUTH_7BA5CF81_5E0A_4351_9AEC_2FDD8A1A3DF7_H__

#include "Qiniu/QiniuConfig.h"

#include <string>

/******************************************************************************/
QINIU_NAMESPACE_BEGIN

struct QiniuToken;

std::string getAuthStr(const QiniuToken& token, const unsigned char* contentstr, size_t len);
std::string getAuthStr(const QiniuToken& token, const unsigned char* contentstr, size_t len,
                                                const unsigned char* otherStr, size_t otherLen);

std::string getMacAuthStr(const QiniuToken& token, const unsigned char* contentstr, size_t len);

void Base64_Encode(const char* buf, std::string& resultStr);

void Base64_Encode(const char* buf, size_t len, std::string& resultStr);

QINIU_NAMESPACE_END
/******************************************************************************/
#endif// SECRETAUTH_7BA5CF81_5E0A_4351_9AEC_2FDD8A1A3DF7_H__