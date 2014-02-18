/*******************************************************************************
 *  @file      QiniuUtils.h 2013\4\26 10:35:34 $
 *  @author    Wang Xiaotao<wangxiaotao1980@gmail.com>(中文编码测试)
 
 ******************************************************************************/

#ifndef MAIKUAPIUTILS_8F3CF3BF_5857_4B6F_8E65_52D367C4A76C_H__
#define MAIKUAPIUTILS_8F3CF3BF_5857_4B6F_8E65_52D367C4A76C_H__

#include "QiniuConfig.h"
#include "QiniuError.h"

#include <string>

/******************************************************************************/
QINIU_NAMESPACE_BEGIN

class QINIU_API_DECL QiniuUtils
{
    public:
    /**
     * 初始化Qiniu模块
     *
     * @return QiniuCode
     * @retval 返回 QINIU_OK 代表 初始化成功
     * @retval 返回 QINIU_MODEL_INIT_FAIL 代表 初始化不成功
     */
    static QiniuCode Initialize();

    /**
     * 设定通信协议的User Agent
     *
     * @param   const char * pUserAgent 设定的字符串
     * @return  void
     * @exception 无任何异常抛出
     */
    static void setUserAgent(const char* pUserAgent);

    /**
     *  得到通信协议的User Agent
     *
     * @return  const char* User angent 的字符串
     * @exception 
     */
    static const char* getUserAgent();
    /**
     * 反初始化Qiniu模块
     *
     * @return  void
     *
     */
    static void Terminate();
};


QINIU_NAMESPACE_END
/******************************************************************************/
#endif// MAIKUAPIUTILS_8F3CF3BF_5857_4B6F_8E65_52D367C4A76C_H__
