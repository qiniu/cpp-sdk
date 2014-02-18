/******************************************************************************* 
 *  @file      WindowsDllMain.cpp 2013\1\8 16:39:48 $
 *  @author    Wang Xiaotao<wangxiaotao1980@gmail.com>
 *  Windows动态链接库DllMain函数
 ******************************************************************************/

#include "Config/Config.h"

#if defined(CPS_OS_WINDOWS) && defined(CPS_ALL_DYNAMIC_LINK)
// Exclude rarely-used stuff from Windows headers
#define WIN32_LEAN_AND_MEAN 
// at here you add you need Windows Header Files:
#include <windows.h>


BOOL APIENTRY DllMain( HMODULE /*hModule*/
                     , DWORD  ul_reason_for_call
                     , LPVOID /*lpReserved*/)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        break;
    case DLL_THREAD_ATTACH:
        break;
    case DLL_THREAD_DETACH:
        break;
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

#endif //CPS_OS_WIN32

// 
// -----------------------------------------------------------------------------
