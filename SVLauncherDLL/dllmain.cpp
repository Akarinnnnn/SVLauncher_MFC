// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
	
	
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
		wsprintfW((wchar_t*)L"%s", L"已附加到进程");
    case DLL_THREAD_ATTACH:
		wsprintfW((wchar_t*)L"%s", L"已附加到线程");
    case DLL_THREAD_DETACH:
		wsprintfW((wchar_t*)L"%s", L"已脱离线程");
    case DLL_PROCESS_DETACH:
		wsprintfW((wchar_t*)L"%s", L"已脱离线程");
        break;
    }
    return TRUE;
}

