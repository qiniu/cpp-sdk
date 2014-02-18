/*******************************************************************************
 *  @file      QiniuStrcut.h 2013\11\21 10:26:48 $
 *  @author    Wang Xiaotao<wangxiaotao1980@gmail.com> (中文编码测试)
 *
 ******************************************************************************/

#ifndef QINIUSTRCUT_A881227D_F042_49FA_B122_23166F9D9C68_H__
#define QINIUSTRCUT_A881227D_F042_49FA_B122_23166F9D9C68_H__

#include "QiniuConfig.h"

#include <string>

/******************************************************************************/

QINIU_NAMESPACE_BEGIN

/** 
 * @enum EnumProxyMode 
 * 枚举了代理模式
 */
typedef enum  QINIU_API_DECL tagEnumProxyMode
{
    NoProxy              = 0,          ///< No Using Proxy
    ProxyHTTP            = 1,          ///< Using the HTTP Proxy
    ProxySock4           = 2,          ///< Using the Socks 4 Proxy
    ProxySock5           = 3           ///< Using the Socks 5 Proxy
} EnumProxyMode;



struct QINIU_API_DECL QiniuToken
{
public:
    QiniuToken();

    QiniuToken(const QiniuToken& rValue);

    const QiniuToken& operator = (const QiniuToken& rValue);
public:
    std::string m_access_key;
    std::string m_secret_key;
};


struct QINIU_API_DECL QiniuBucketKey
{
public:
    const char* m_pBucketName;
    const char* m_pKeyName;
};


struct QINIU_API_DECL QiniuSrcAndDestBucketKey
{
public:
    const char* m_pBucketNameSrc;               ///< 源   bucketName
    const char* m_pKeyNameSrc;                  ///< 源   keyName
    const char* m_pBucketNameDest;              ///< 目标 bucketName
    const char* m_pKeyNameDest;                 ///< 目标 keyName
};


struct QINIU_API_DECL QiniuIoPutExtraParam 
{
public:
    QiniuIoPutExtraParam();
public:
    const char* m_key;
    const char* m_value;
    struct QiniuIoPutExtraParam* m_pNext;
};

struct QINIU_API_DECL QiniuIoPutExtra
{
public:
    QiniuIoPutExtra();
public:
    QiniuIoPutExtraParam* m_params;

    const char* m_mimeType;
    UInt32      m_crc32;
    UInt32      m_checkCrc32;
};


struct QINIU_API_DECL QiniuPutPolicy 
{
public:
    QiniuPutPolicy();

public:
    const char* m_bucketName;   ///< 要上传的bucket的名称(必须设置）
    const char* m_keyName;      ///< 上传后的文件名称（必须设置）

    const char* m_callbackUrl;  ///< 回调url（可以为空）
    const char* m_callbackBody; ///< 回调body（可以为空)
    const char* m_returnUrl;    ///< 什么意思？等待增加（可以为空)
    const char* m_returnBody;   ///< 什么意思？等待增加（可以为空)
    const char* m_endUser;      ///< 什么意思？等待增加（可以为空)
    const char* m_asyncOps;     ///< 什么意思？等待增加（可以为空)
    UInt32      m_expires;      ///< 上传超时时间还是token失效时间？（值为0的话，为一个小时）
};



/**
 * The struct <code>ProxyInfo</code> 代理信息结构体
 */
struct QINIU_API_DECL ProxyInfo
{
    ProxyInfo();
    ProxyInfo(const ProxyInfo& rValue);

    const ProxyInfo& operator = (const ProxyInfo& rValue);

    EnumProxyMode   m_proxyMode;   ///<代理模式，noproxy, http, sock4，sock5
    std::string     m_ip;          ///<代理IP地址
    UInt32          m_port;        ///<端口号

    bool            m_isUsingPwd;  ///<是否密码登陆代理，如果设定下面两项有效，否则无效。

    std::string     m_user;        ///<用户名
    std::string     m_passwd;      ///<密码
};



QINIU_NAMESPACE_END
/******************************************************************************/
#endif// QINIUSTRCUT_A881227D_F042_49FA_B122_23166F9D9C68_H__