/*******************************************************************************
 *  @file      Win32Config.h 2012\12\25 16:10:56 $
 *  @author    Wang Xiaotao<wangxiaotao1980@gmail.com>
 *  文件设定了关于Windows平台的特有特性
 ******************************************************************************/

#ifndef WIN32CONFIG_8FA3AB1C_EB8D_45B7_BA92_B13E31DB7ED1_H__
#define WIN32CONFIG_8FA3AB1C_EB8D_45B7_BA92_B13E31DB7ED1_H__
/******************************************************************************/

#define CPS_OS_NAME "Win32"

//  MinGW runtime 运行时信息 譬如 ： __MINGW32_*VERSION.
#if defined(__MINGW32__)
    #include <_mingw.h>
#endif

#ifndef CPS_SYMBOL_EXPORT
    #define CPS_HAS_DECLSPEC
    #define CPS_SYMBOL_EXPORT __declspec(dllexport)
    #define CPS_SYMBOL_IMPORT __declspec(dllimport)
#endif


#if defined(__MINGW32__) && ((__MINGW32_MAJOR_VERSION > 2) || ((__MINGW32_MAJOR_VERSION == 2) && (__MINGW32_MINOR_VERSION >= 0)))
    #define CPS_HAS_STDINT_H
    #define CPS_HAS_POSIX_UNISTD_H
#endif



#ifndef CPS_HAS_POSIX_PTHREAD_H
    #define CPS_HAS_WINTHREADS
#endif

/******************************************************************************/
#endif// WIN32CONFIG_8FA3AB1C_EB8D_45B7_BA92_B13E31DB7ED1_H__
