/*******************************************************************************
 *  @file      UploadCallBack.h 2013\11\27 15:55:14 $
 *  @author    Wang Xiaotao<wangxiaotao1980@gmail.com> (÷–Œƒ±‡¬Î≤‚ ‘)
 *
 ******************************************************************************/

#ifndef UPLOADCALLBACK_8E9D26C6_0F02_4936_BE29_33DEDD5B91CC_H__
#define UPLOADCALLBACK_8E9D26C6_0F02_4936_BE29_33DEDD5B91CC_H__

#include "Qiniu/Qiniu.h"
/******************************************************************************/

/**
 * The class <code>UploadCallBack</code>
 *
 */
class UploadCallBack : public QINIU_NAMESPACE::IUpLoadProgress
{
public:
    /** @name Constructors and Destructor*/

    //@{
    /**
     * No Parameter Constructor 
     */
    UploadCallBack();
    /**
     * Destructor
     */
    ~UploadCallBack();

    virtual void OnBeginUploadFile( time_t theTime, double totalsize, const char* pname );

    virtual void OnProcessUploadFile( time_t theTime, double totalsize, double nowsize );

    virtual void OnEndUploadFile( time_t theTime, double totalsize, const char* pName );

    virtual void OnFailUploadFile( time_t theTime, const char* pName );

    //@}
public:




public:
    /** @name Setter Methods*/
    //@{

    //@}
public:
    /** @name Getter Methods*/
    //@{

    //@}
public:
    /** @name Access Methods*/
    //@{

    //@}   
protected:

private:

};

/******************************************************************************/
#endif// UPLOADCALLBACK_8E9D26C6_0F02_4936_BE29_33DEDD5B91CC_H__