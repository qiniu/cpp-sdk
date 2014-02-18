/******************************************************************************* 
 *  @file      QiniuMisc.cpp 2013\11\21 15:10:27 $
 *  @author    Wang Xiaotao<wangxiaotao1980@gmail.com> (中文编码测试)
 ******************************************************************************/

#include "QiniuMisc.h"
#include "Qiniu/QiniuStrcut.h"

#include "b64/urlsafe_b64.h"

#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "openssl/hmac.h"
#include "openssl/engine.h"


QINIU_NAMESPACE_BEGIN


std::string getAuthStr( const QiniuToken& token, const unsigned char* contentstr, size_t len )
{

    unsigned char digest[EVP_MAX_MD_SIZE + 1] = {0};
    unsigned int dgtlen = sizeof(digest);
    ::HMAC_CTX ctx;

    ::HMAC_CTX_init(&ctx);
    ::HMAC_Init_ex(&ctx, token.m_secret_key.c_str(), token.m_secret_key.size(), EVP_sha1(), NULL);
    ::HMAC_Update(&ctx, contentstr, len);
    unsigned char endchar[2]  = {'\n', 0};
    ::HMAC_Update(&ctx, endchar, 1);

    ::HMAC_Final(&ctx, digest, &dgtlen);
    digest[dgtlen] = 0;
    ::HMAC_CTX_cleanup(&ctx);

    unsigned char* ptemp = digest;
    return std::string((char*)ptemp, (char*)ptemp + dgtlen);

}
// -----------------------------------------------------------------------------
// class :  inherit from : 
//   public  

std::string getAuthStr( const QiniuToken& token, 
                        const unsigned char* contentstr, size_t len, 
                        const unsigned char* otherStr, size_t otherLen )
{
    unsigned char digest[EVP_MAX_MD_SIZE + 1] = {0};
    unsigned int dgtlen = sizeof(digest);
    ::HMAC_CTX ctx;

    ::HMAC_CTX_init(&ctx);
    ::HMAC_Init_ex(&ctx, token.m_secret_key.c_str(), token.m_secret_key.size(), EVP_sha1(), NULL);
    ::HMAC_Update(&ctx, contentstr, len);
    unsigned char endchar[2]  = {'\n', 0};
    ::HMAC_Update(&ctx, endchar, 1);
    ::HMAC_Update(&ctx, otherStr, otherLen);

    ::HMAC_Final(&ctx, digest, &dgtlen);
    digest[dgtlen] = 0;
    ::HMAC_CTX_cleanup(&ctx);

    unsigned char* ptemp = digest;
    return std::string((char*)ptemp, (char*)ptemp + dgtlen);
}    
    
    
// -----------------------------------------------------------------------------
//   public  
void Base64_Encode( const char* buf, std::string& resultStr )
{
    const size_t cb = strlen(buf);
    const size_t cbDest = ::urlsafe_b64_encode(buf, cb, NULL, 0);
    char* dest = (char*)malloc(cbDest + 1);
    const size_t cbReal = ::urlsafe_b64_encode(buf, cb, dest, cbDest);
    dest[cbReal] = '\0';

    resultStr = dest;

    free(dest);
}
// -----------------------------------------------------------------------------
// class :  inherit from : 
//   public  

void Base64_Encode( const char* buf,const size_t len, std::string& resultStr )
{

    const size_t cbDest = urlsafe_b64_encode(buf, len, NULL, 0);
    char* dest = (char*)malloc(cbDest + 1);
    const size_t cbReal = urlsafe_b64_encode(buf, len, dest, cbDest);
    dest[cbReal] = '\0';
    
    resultStr = dest;

    free(dest);
}
// -----------------------------------------------------------------------------
// class :  inherit from : 
//   public  

std::string getMacAuthStr( const QiniuToken& token, const unsigned char* contentstr, size_t len )
{

    unsigned char digest[EVP_MAX_MD_SIZE + 1] = {0};
    unsigned int dgtlen = sizeof(digest);
    ::HMAC_CTX ctx;

    ::HMAC_CTX_init(&ctx);
    ::HMAC_Init_ex(&ctx, token.m_secret_key.c_str(), token.m_secret_key.size(), EVP_sha1(), NULL);
    ::HMAC_Update(&ctx, contentstr, len);

    ::HMAC_Final(&ctx, digest, &dgtlen);
    digest[dgtlen] = 0;
    ::HMAC_CTX_cleanup(&ctx);

    unsigned char* ptemp = digest;
    return std::string((char*)ptemp, (char*)ptemp + dgtlen);
}
QINIU_NAMESPACE_END
// 
// -----------------------------------------------------------------------------
