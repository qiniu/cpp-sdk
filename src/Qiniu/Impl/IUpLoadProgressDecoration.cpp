/******************************************************************************* 
 *  @file      IUpLoadProgressDecoration.cpp 2013\12\31 14:43:44 $
 *  @author    Wang Xiaotao<wangxiaotao1980@gmail.com>
 ******************************************************************************/

#include "IUpLoadProgressDecoration.h"


QINIU_NAMESPACE_BEGIN
// -----------------------------------------------------------------------------
//  IUpLoadProgressDecoration: Public, Constructor

IUpLoadProgressDecoration::IUpLoadProgressDecoration(IUpLoadProgress* pUpLoadProgress, double fileSize)
    : m_theFileSize(fileSize)
    , m_baseFileSize(0)
    , m_pIUpLoadProgress(pUpLoadProgress)
{
}

// -----------------------------------------------------------------------------
//  IUpLoadProgressDecoration: Public, Destructor
IUpLoadProgressDecoration::~IUpLoadProgressDecoration()
{
}
// -----------------------------------------------------------------------------
// class :  inherit from :    public  
void IUpLoadProgressDecoration::OnBeginUploadFile( time_t theTime, double totalsize, const char* pname )
{
    if (m_pIUpLoadProgress)
    {
        m_pIUpLoadProgress->OnBeginUploadFile(theTime, m_theFileSize, pname);
    }
}
// -----------------------------------------------------------------------------
// class :  inherit from :    public  
void IUpLoadProgressDecoration::OnProcessUploadFile( time_t theTime, double totalsize, double nowsize )
{
    if (m_pIUpLoadProgress)
    {
        m_pIUpLoadProgress->OnProcessUploadFile(theTime, m_theFileSize, m_baseFileSize + nowsize);
    }
}
// -----------------------------------------------------------------------------
// class :  inherit from :    public  
void IUpLoadProgressDecoration::OnEndUploadFile( time_t theTime, double totalsize, const char* pName )
{
    if (m_pIUpLoadProgress)
    {
        m_pIUpLoadProgress->OnEndUploadFile(theTime, m_theFileSize, pName);
    }
}
// -----------------------------------------------------------------------------
// class :  inherit from :    public  
void IUpLoadProgressDecoration::OnFailUploadFile( time_t theTime, const char* pName )
{
    if (m_pIUpLoadProgress)
    {
        m_pIUpLoadProgress->OnFailUploadFile(theTime, pName);
    }
}
// -----------------------------------------------------------------------------
// class : IUpLoadProgressDecoration inherit from : IUpLoadProgress   public  
void IUpLoadProgressDecoration::setBaseFileSize( double baseFiles )
{
       m_baseFileSize = baseFiles ;
}

QINIU_NAMESPACE_END
// 
// -----------------------------------------------------------------------------