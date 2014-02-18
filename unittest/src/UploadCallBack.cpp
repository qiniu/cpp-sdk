/******************************************************************************* 
 *  @file      UploadCallBack.cpp 2013\11\27 15:55:18 $
 *  @author    Wang Xiaotao<wangxiaotao1980@gmail.com> (÷–Œƒ±‡¬Î≤‚ ‘)
 ******************************************************************************/

#include "UploadCallBack.h"
#include <iostream>
// -----------------------------------------------------------------------------
//  UploadCallBack: Public, Constructor

UploadCallBack::UploadCallBack()
{

}

// -----------------------------------------------------------------------------
//  UploadCallBack: Public, Destructor

UploadCallBack::~UploadCallBack()
{

}
// -----------------------------------------------------------------------------
// class :  inherit from : 
//   public  

void UploadCallBack::OnBeginUploadFile( time_t theTime, double totalsize, const char* pname )
{
}
// -----------------------------------------------------------------------------
// class :  inherit from : 
//   public  

void UploadCallBack::OnProcessUploadFile( time_t theTime, double totalsize, double nowsize )
{
}
// -----------------------------------------------------------------------------
// class :  inherit from : 
//   public  

void UploadCallBack::OnEndUploadFile( time_t theTime, double totalsize, const char* pName )
{
}
// -----------------------------------------------------------------------------
// class :  inherit from : 
//   public  

void UploadCallBack::OnFailUploadFile( time_t theTime, const char* pName )
{
}