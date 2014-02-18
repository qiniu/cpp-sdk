/*******************************************************************************
 *  @file      CurlWrapperClass.h 2013\3\7 17:14:57 $
 *  @author    Wang Xiaotao<wangxiaotao1980@snda.com> 中文编码测试
 *  this file defines ... ...
 ******************************************************************************/

#ifndef CURLWRAPPERCLASS_1FE7F0C2_9F3E_4EFA_BDFE_8394849BEC4A_H__
#define CURLWRAPPERCLASS_1FE7F0C2_9F3E_4EFA_BDFE_8394849BEC4A_H__

#include "HttpAccess/HttpAccess.h"
#include "CurlWrapperConfig.h"

#include <string>

#include "curl/curl.h"
/******************************************************************************/

CPS_HTTPACCESS_NAMESPACE_BEGIN

/**
 * The class <code>CurlWrapperClass</code>
 *
 */
class CurlWrapperClass
{
public:
    /** @name Constructors and Destructor*/

    //@{
    /**
     * No Parameter Constructor 
     */
    CurlWrapperClass();
    /**
     * Destructor
     */
    ~CurlWrapperClass();
    //@}

public:
    /** @name Setter Methods*/
    //@{

    virtual HttpAccessCode InitCurl();
    //@}
public:
    /** @name Getter Methods*/
    //@{

    //@}
public:
    /** @name Access Methods*/
    //@{
    const char* getLastErrorMessage() const;
    //@}   
protected:
    CURL*                    m_pCURL;                  //   CURL 句柄,本类最重要的封装
    std::string              m_errorMessage;           //   错误信息字符串

};

CPS_HTTPACCESS_NAMESPACE_END

/******************************************************************************/
#endif// CURLWRAPPERCLASS_1FE7F0C2_9F3E_4EFA_BDFE_8394849BEC4A_H__
