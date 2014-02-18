/******************************************************************************* 
 *  @file      CurlWrapperClass.cpp 2013\3\7 17:16:15 $
 *  @author    Wang Xiaotao<wangxiaotao1980@gmail.com> 中文编码测试
 ******************************************************************************/

#include "CurlWrapperClass.h"

CPS_HTTPACCESS_NAMESPACE_BEGIN
// -----------------------------------------------------------------------------
//  CurlWrapperClass: Public, Constructor
// -----------------------------------------------------------------------------

CurlWrapperClass::CurlWrapperClass()
: m_pCURL(CPS_HTTPACCESS_NULL_PTR)
{}

// -----------------------------------------------------------------------------
//  CurlWrapperClass: Public, Destructor
// -----------------------------------------------------------------------------

CurlWrapperClass::~CurlWrapperClass()
{
    if (m_pCURL != CPS_HTTPACCESS_NULL_PTR)
    {
        ::curl_easy_cleanup(m_pCURL);
    }

    m_pCURL = CPS_HTTPACCESS_NULL_PTR;
}
// -----------------------------------------------------------------------------
// class : CurlWrapperClass inherit form : 
//   public  
// -----------------------------------------------------------------------------
HttpAccessCode CurlWrapperClass::InitCurl()
{

    if (m_pCURL == 0)
    {
        m_pCURL = ::curl_easy_init();
        if (m_pCURL == 0)
        {
            m_pCURL = CPS_HTTPACCESS_NULL_PTR;

            m_errorMessage = getErrorCodeInfo(HTTPACCESS_INIT_CURL_ERROR);
            return HTTPACCESS_INIT_CURL_ERROR;
        }
        else 
        {
            return HTTPACCESS_OK;
        }
    }
    else
    {
        return HTTPACCESS_OK;
    }

}
// -----------------------------------------------------------------------------
// class :  inherit form : 
//   public  
// -----------------------------------------------------------------------------
const char* CurlWrapperClass::getLastErrorMessage() const
{
    return m_errorMessage.c_str();
}

CPS_HTTPACCESS_NAMESPACE_END
// 
// -----------------------------------------------------------------------------