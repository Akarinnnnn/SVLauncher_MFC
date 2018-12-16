// SVlaunchDLL.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "SVlaunchDLL.hpp"
#include <string>
#include <sstream>
#include <iostream>
#include "winnt.h"

wchar_t* operator+= (wchar_t* _Left, wstring _Right)
{
	wistringstream stream(_Left + _Right);
	
	stream >> _Left;
}

using namespace std;
using namespace SVLauncherDLL;
wchar_t* BuildArg(svarg a)
{
	static wchar_t* Arg;
	std::wstringstream sstream_buff;
	wstring* p_arg = &(a.cluster);
	std::wstring paramitters[11] = {
		L"-cluster",L"-Shard " , L"-backup_logs ",
		L"-persistent_storage_root " ,
		L"-conf_dir ",L"-tickrate " , L"-maxplayers " ,
		L"-ownernetid ",L"-ownerdir " ,L"-offline ",L"-fo " };
	for (char i = 0; i <= 8; i++)
	{
		if (*p_arg != L"")
		{
			sstream_buff << paramitters[i] << *(p_arg + i) << L" ";//极其不规范的指针用法，慎用
		}
	}
	if (a.offline) sstream_buff << paramitters[9];
	if (a.fo)
	{
		sstream_buff << paramitters[10] << paramitters[7] << a.SteamID64 << paramitters[8] << a.SteamID3;
	}
	sstream_buff >> Arg;
	return Arg;
}




SVLAUNCHERDLL_API bool SVLauncherDLL::CallSV(wchar_t* arg)
{
	const DWORD SVCreationFlags = CREATE_NEW_CONSOLE | CREATE_UNICODE_ENVIRONMENT;
	wchar_t CurDir[MAX_PATH];
	wchar_t CmdLine[500];
	
	return CreateProcessW(nullptr, CmdLine, nullptr, nullptr, false,
						SVCreationFlags, NULL, CurDir, &siSv, &piSv);
	
}
