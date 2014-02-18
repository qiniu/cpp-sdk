/*******************************************************************************
 *  @file      IHttpSetting.h 2013\11\21 10:53:36 $
 *  @author    Wang Xiaotao<wangxiaotao1980@gmail.com> (中文编码测试)
 *
 ******************************************************************************/

#ifndef IHTTPSETTING_108003FA_D92A_475C_AC10_BA46A15B0B0B_H__
#define IHTTPSETTING_108003FA_D92A_475C_AC10_BA46A15B0B0B_H__

#include "QiniuConfig.h"
/******************************************************************************/

QINIU_NAMESPACE_BEGIN

struct ProxyInfo;

/**
 * The class <code>IHttpSetting</code>网络Http(s)请求的设定接口
 *
 */
struct QINIU_API_DECL IHttpSetting
{
public:

    /**
     * 设定是对象否使用Https协议
     *
     * @param   bool isUsingHttps   是否使用https协议， false 不使用， true 使用
     * @return  void
     * @exception 无异常抛出
     */
    virtual void setUsingHttps(bool isUsingHttps) = 0;
    /**
     * 对象现在是不是使用https协议
     *
     * @return  bool
     * @retval   true  使用http协议
       @retval   false 不使用https协议，使用http协议
     * @exception 无异常抛出
     */
    virtual bool getUsingHttps()                  = 0;


    /**
     * 设定是对象通信使用代理信息
     *
     * @param   const ProxyInfo & proxyInfo 要设定的代理信息。
     * @return  void
     * @exception 无异常抛出
     */
    virtual void setProxyInfo(const ProxyInfo& proxyInfo) = 0;
    /**
     * 得到对象通信使用的代理信息
     *
     * @return  const ProxyInfo& 代理信息对象
     * @exception 无异常抛出
     */
    virtual const ProxyInfo& getProxyInfo()               = 0;

    /**
     * 设定一次通信的超时时间，单位 秒
     *
     * @param   UInt32 timeout   超时时间， 0值，表示未设定超时时间，即无限制超时
     * @return  void
     * @exception 无异常抛出
     */
    virtual void setTimeout(UInt32 timeout) = 0;
    /**
     * 得到一次通信的超时时间，单位 秒
     *
     * @return  UInt32 超时通信时间， 如果为0，表示未设定超时时间，
     * @exception 
     */
    virtual UInt32 getTimeout()             = 0;

    virtual ~IHttpSetting()                 = 0;
};

QINIU_NAMESPACE_END
/******************************************************************************/
#endif// IHTTPSETTING_108003FA_D92A_475C_AC10_BA46A15B0B0B_H__