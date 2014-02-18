/*******************************************************************************
 *  @file      Suffix.h 2012\12\25 16:25:54 $
 *  @author    Wang Xiaotao<wangxiaotao1980@gmail.com>
 *  文件用于屏蔽各种不同系统环境、编译器下函数、类的前后缀。
 ******************************************************************************/

#ifndef SUFFIX_D914265B_3025_474C_AC97_36F1ED2361E4_H__
#define SUFFIX_D914265B_3025_474C_AC97_36F1ED2361E4_H__
/******************************************************************************/

// 函数导出宏
#ifndef CPS_SYMBOL_EXPORT
    #define CPS_SYMBOL_EXPORT
#endif

#ifndef CPS_SYMBOL_IMPORT
    #define CPS_SYMBOL_IMPORT
#endif

#ifndef CPS_SYMBOL_VISIBLE
    #define CPS_SYMBOL_VISIBLE
#endif

#ifdef CPS_HAS_STDINT_H
    #include <stdint.h>
#endif


#if defined(CPS_NO_TYPEID) && !defined(CPS_NO_RTTI)
    #define CPS_NO_RTTI
#endif


#if defined(CPS_HAS_STDINT_H)
    // 对IOS 好像 typedef 无法通过
    #if defined(CPS_OS_IOS)
        #define Int16             int16_t
        #define UInt16            uint16_t
        #define Int32             int32_t
        #define UInt32            uint32_t
        #define Int64             int64_t
        #define UInt64            uint64_t
    #else
        typedef int16_t     Int16;
        typedef uint16_t    UInt16;
        typedef int32_t     Int32;
        typedef uint32_t    UInt32;
        typedef int64_t     Int64;
        typedef uint64_t    UInt64;
    #endif
#else
    #include <basetsd.h>
    typedef INT16  Int16;
    typedef UINT16 UInt16;
    typedef INT32  Int32;
    typedef UINT32 UInt32;
    typedef INT64  Int64;
    typedef UINT64 UInt64;
#endif



/******************************************************************************/
#endif// SUFFIX_D914265B_3025_474C_AC97_36F1ED2361E4_H__
