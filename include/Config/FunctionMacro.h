/*******************************************************************************
 *  @file      FunctionMacro.h 2013\1\10 13:59:00 $
 *  @author    Wang Xiaotao<wangxiaotao1980@gmail.com>
 *  C/C++辅助宏定义
 ******************************************************************************/

#ifndef FUNCTIONMACRO_C4D3F4ED_CABF_4974_A47A_D3966452DF92_H__
#define FUNCTIONMACRO_C4D3F4ED_CABF_4974_A47A_D3966452DF92_H__

/******************************************************************************/

//转换宏为一个字符串
#define CPS_STRINGIZE(X) CPS_DO_STRINGIZE(X)
#define CPS_DO_STRINGIZE(X) #X

//宏拼接
#define CPS_JOIN( X, Y ) CPS_DO_JOIN( X, Y )
#define CPS_DO_JOIN( X, Y ) CPS_DO_JOIN2(X,Y)
#define CPS_DO_JOIN2( X, Y ) X##Y
/******************************************************************************/
#endif// FUNCTIONMACRO_C4D3F4ED_CABF_4974_A47A_D3966452DF92_H__
