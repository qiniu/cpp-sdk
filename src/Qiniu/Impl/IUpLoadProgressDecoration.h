/*******************************************************************************
 *  @file      IUpLoadProgressDecoration.h 2013\12\31 14:43:40 $
 *  @author    Wang Xiaotao<wangxiaotao1980@gmail.com>
 *
 ******************************************************************************/

#ifndef IUPLOADPROGRESSDECORATION_5F38C929_88E1_49C5_9D64_D9892E4FD04D_H__
#define IUPLOADPROGRESSDECORATION_5F38C929_88E1_49C5_9D64_D9892E4FD04D_H__

#include "Qiniu/QiniuConfig.h"
#include "Qiniu/IUpLoadProgress.h"
/******************************************************************************/


QINIU_NAMESPACE_BEGIN

/**
 * The class <code>IUpLoadProgressDecoration</code>
 *
 */
class IUpLoadProgressDecoration : public IUpLoadProgress
{
public:
    /** @name Constructors and Destructor*/

    //@{
    /**
     * No Parameter Constructor 
     */
    IUpLoadProgressDecoration(IUpLoadProgress* pUpLoadProgress, double fileSize);
    /**
     * Destructor
     */
    ~IUpLoadProgressDecoration();

    virtual void OnBeginUploadFile( time_t theTime, double totalsize, const char* pname );

    virtual void OnProcessUploadFile( time_t theTime, double totalsize, double nowsize );

    virtual void OnEndUploadFile( time_t theTime, double totalsize, const char* pName );

    virtual void OnFailUploadFile( time_t theTime, const char* pName );

    void setBaseFileSize(double baseFiles);
    //@}

public:

private:
    double            m_theFileSize;
    double            m_baseFileSize;
    IUpLoadProgress*  m_pIUpLoadProgress;
};


QINIU_NAMESPACE_END

/******************************************************************************/
#endif// IUPLOADPROGRESSDECORATION_5F38C929_88E1_49C5_9D64_D9892E4FD04D_H__