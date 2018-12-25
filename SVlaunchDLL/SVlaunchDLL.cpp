// SVlaunchDLL.cpp : 定义 DLL 应用程序的导出函数。
//wide strings only,no ANSI string version
//CodePage:936(GBK)
//字符串全是wstring/wchar_t注意一下

#include "stdafx.h"
#include "SVlaunchDLL.hpp"
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <stdexcept>
#include <exception>
#include <iostream>
#include "winnt.h"
using std::wstring;
using std::wistringstream;
using std::map;
using std::vector;
constexpr unsigned short buffiersize = 1024;


//合成参数，返回参数的字数，用了STL
unsigned short SVLaunchDLL::BuildArg(SVLaunchDLL::SVPARAM &a,wchar_t* target)
{
	std::wstring buffier;
	buffier.reserve(buffiersize);
	wstring* p_arg = &(a.cluster);
	std::wstring paramitters[11] = 
	{
		L"-cluster ",L"-Shard " , L"-backup_logs ",
		L"-persistent_storage_root " ,
		L"-conf_dir ",L"-tickrate " , L"-maxplayers " ,
		L"-ownerdir ",L"-ownernetid " ,L"-offline ",L"-fo " 
	};
	for (char i = 0; i <= 6; i++)
	{
		if (! ((p_arg + i)->empty()) )
		{
			buffier += paramitters[i] + *(p_arg + i) + L" ";
		}
	}
	if (a.fo)
	{
		for (char i = 7; i <= 8; i++)
		{
			buffier += paramitters[i] + *(p_arg + i) + L" ";
		}
	}
	if (a.offline)
		buffier += paramitters[9];
	if (buffier.size() <= buffiersize)
	{
		buffier.copy(target, buffier.size());
		return buffier.size();
	}
	else
	{ 
		MessageBoxW(GetActiveWindow(), L"参数过长(超过1024字)", L"畜生，你输了什么？", 0);
		return 0;
	}
}

SVLAUNCHERDLL_API BOOL SVLaunchDLL::SVManage::CallSv(SVPARAM param, const wchar_t* SvDir, PROCESS_INFORMATION * p_piSv, STARTUPINFOW * p_siSv)
{
	const DWORD SVCreationFlags = CREATE_NEW_CONSOLE | CREATE_UNICODE_ENVIRONMENT;
	wchar_t CmdLine[buffiersize + MAX_PATH + 3]{0};
	wchar_t Arg[1024]{ 0 };
	BuildArg(param, Arg);
	lstrcpyW(CmdLine, SvDir);//别问，问就文体两开花
	lstrcatW(CmdLine, L"dontstarve_dedicated_server_nullrenderer.exe");
	lstrcatW(CmdLine, L" ");
	lstrcatW(CmdLine, Arg);
	
	return CreateProcessW(nullptr, CmdLine, nullptr, nullptr, false,
		SVCreationFlags, NULL, SvDir, &def_siSv, &def_piSv);
}

SVLAUNCHERDLL_API SVLaunchDLL::SVManage::SVManage()
{
	def_siSv =
	{
		sizeof(STARTUPINFOW),NULL,NULL,nullptr,0,0,0,0,
		0,0,NULL,NULL,SW_SHOW,NULL,NULL,NULL,NULL,NULL
	};
}

SVLAUNCHERDLL_API SVLaunchDLL::SVManage::~SVManage()
{
	
}