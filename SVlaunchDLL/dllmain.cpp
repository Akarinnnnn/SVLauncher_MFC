// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"
#include <cstring>
#include <stdio.h>

using namespace std;
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
		printf("%s", "[SVlauncherDLL]process attached\n");
		
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
		printf("%s", "[SVlauncherDLL]process detached\n");
        break;
    }
    return TRUE;
}

