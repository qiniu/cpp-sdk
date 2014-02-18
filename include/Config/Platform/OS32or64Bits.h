/*******************************************************************************
 *  @file      OS32or64Bits.h 2013\1\8 18:40:49 $
 *  @author    Wang Xiaotao<wangxiaotao1980@gmail.com>
 *  判定此库是32位还是64位
 ******************************************************************************/

#ifndef OS32OR64BITS_252938B5_7EFE_4625_A192_F2019128D22B_H__
#define OS32OR64BITS_252938B5_7EFE_4625_A192_F2019128D22B_H__

template<int N>
struct OSBits
{
    const static int s_bits = N*8;
};

// 判定应用程序是32位还是64位
#define CPS_OS_BITS    OSBits<sizeof(void*)>::s_bits;

/******************************************************************************/
#endif// OS32OR64BITS_252938B5_7EFE_4625_A192_F2019128D22B_H__
