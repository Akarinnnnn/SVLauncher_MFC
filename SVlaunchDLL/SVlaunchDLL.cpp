// SVlaunchDLL.cpp : 定义 DLL 应用程序的导出函数。
//

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

//wchar_t* operator+= (wchar_t* _Left, wstring _Right)
//{
//	wistringstream stream(_Left + _Right);
//	static wchar_t* buffier;
//	stream >> buffier;
//	return buffier;
//}

wchar_t* SVLaunchDLL::BuildArg(SVLaunchDLL::SVPARAM a)
{
	
	const unsigned short paramlen = 500;
	static wchar_t Arg[paramlen];
	std::wstring buffier;
	
	wstring* p_arg = &(a.cluster);
	std::wstring paramitters[11] = 
	{
		L"-cluster ",L"-Shard " , L"-backup_logs ",
		L"-persistent_storage_root " ,
		L"-conf_dir ",L"-tickrate " , L"-maxplayers " ,
		L"-ownernetid ",L"-ownerdir " ,L"-offline ",L"-fo " 
	};


	for (char i = 0; i <= 6; i++)
	{
		if (*p_arg != L"")
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
	std::wistringstream sbuff(buffier);
	if (buffier.size() < paramlen)
	{
		buffier.copy(Arg, buffier.size());
		return Arg;
	}
	else	
		throw std::out_of_range("[SVLaunchDLL.cpp] Arg(wchar_t) out of range");

}

BOOL SVLaunchDLL::SVManage::CallSv(SVPARAM param)
{
	const DWORD SVCreationFlags = CREATE_NEW_CONSOLE | CREATE_UNICODE_ENVIRONMENT;
	wchar_t CmdLine[500];
	PROCESS_INFORMATION* p_piSv = &this->def_piSv;
	STARTUPINFOW* p_siSv = &this->def_siSv;
	return CreateProcessW(nullptr, CmdLine, nullptr, nullptr, false,
						SVCreationFlags, NULL, L".\\", p_siSv, p_piSv);
	
}

BOOL SVLaunchDLL::SVManage::CallSv()
{
	const DWORD SVCreationFlags = CREATE_NEW_CONSOLE | CREATE_UNICODE_ENVIRONMENT;
	wchar_t CmdLine[500];
	return CreateProcessW(nullptr, CmdLine, nullptr, nullptr, false,
		SVCreationFlags, NULL, L".\\", &def_siSv, &def_piSv);
}

BOOL SVLaunchDLL::SVManage::CallSv(SVPARAM param, wchar_t * SvDir, STARTUPINFOW * siSv, PROCESS_INFORMATION * piSv)
{
	const DWORD SVCreationFlags = CREATE_NEW_CONSOLE | CREATE_UNICODE_ENVIRONMENT;
	wchar_t CmdLine[500];

	return CreateProcessW(nullptr, CmdLine, nullptr, nullptr, false,
		SVCreationFlags, NULL, SvDir, &def_siSv, &def_piSv);
}

BOOL SVLaunchDLL::SVManage::CallSv(SVPARAM param, wchar_t * SvDir, PROCESS_INFORMATION * piSv)
{
	const DWORD SVCreationFlags = CREATE_NEW_CONSOLE | CREATE_UNICODE_ENVIRONMENT;
	wchar_t CmdLine[500];

	return CreateProcessW(nullptr, CmdLine, nullptr, nullptr, false,
		SVCreationFlags, NULL, SvDir, &def_siSv, &def_piSv);
}

BOOL SVLaunchDLL::SVManage::CallSv(SVPARAM param, wchar_t * SvDir)
{
	const DWORD SVCreationFlags = CREATE_NEW_CONSOLE | CREATE_UNICODE_ENVIRONMENT;

	wchar_t CmdLine[500];

	return CreateProcessW(nullptr, CmdLine, nullptr, nullptr, false,
		SVCreationFlags, NULL, SvDir, &def_siSv, &def_piSv);
}

BOOL SVLaunchDLL::SVManage::CallSv(SVPARAM param, STARTUPINFOW* p_siSv, PROCESS_INFORMATION* p_piSv)
{
	const DWORD SVCreationFlags = CREATE_NEW_CONSOLE | CREATE_UNICODE_ENVIRONMENT;


	wchar_t CmdLine[500];

	return CreateProcessW(nullptr, CmdLine, nullptr, nullptr, false,
		SVCreationFlags, NULL, L".\\", p_siSv, p_piSv);

}

BOOL SVLaunchDLL::SVManage::CallSv(wchar_t * SvDir)
{
	const DWORD SVCreationFlags = CREATE_NEW_CONSOLE | CREATE_UNICODE_ENVIRONMENT;
	wchar_t CmdLine[500];

	return CreateProcessW(nullptr, CmdLine, nullptr, nullptr, false,
		SVCreationFlags, NULL, SvDir, &def_siSv, &def_piSv);
}

SVLaunchDLL::SVManage::SVManage()
{
	def_siSv = { sizeof(STARTUPINFOW),NULL,NULL,NULL };
}

SVLaunchDLL::SVManage::~SVManage()
{
	delete &defsvparam;
}