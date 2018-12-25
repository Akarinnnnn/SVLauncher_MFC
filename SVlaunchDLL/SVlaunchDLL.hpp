//wide strings only,no ANSI string version
//CodePage:936(GBK)
//字符串全是wstring/wchar_t注意一下

#pragma once
#ifdef SVLAUNCHDLL_EXPORTS
#define SVLAUNCHERDLL_API __declspec(dllexport)
#else
#define SVLAUNCHERDLL_API __declspec(dllimport)
#endif

#include <vector>
#include <iostream>
#include <memory>



namespace SVLaunchDLL 
{

	//数据
	SVLAUNCHERDLL_API PROCESS_INFORMATION def_piSv;//请不要修改这个结构体，修改它会导致CallSv默认行为改变
	SVLAUNCHERDLL_API STARTUPINFOW def_siSv;//请不要修改这个结构体，修改它会导致CallSv默认行为改变
	

	//类型
	SVLAUNCHERDLL_API struct SVPARAM
	{
		std::wstring cluster = L"Cluster_1";
		std::wstring shard = L"Master";
		std::wstring logbackup;
		std::wstring storage_root;
		std::wstring confdir;
		std::wstring tickrate;
		std::wstring maxplayers;
		std::wstring SteamID3;
		std::wstring SteamID64;
		bool offline;
		bool fo;
	}defsvparam;

	class SVManage
	{
	public:
		
		SVLAUNCHERDLL_API BOOL CallSv(
			SVPARAM param = SVLaunchDLL::defsvparam,
			const wchar_t* SvDir = L".\\",
			PROCESS_INFORMATION * p_piSv = &SVLaunchDLL::def_piSv,
			STARTUPINFOW * p_siSv = &SVLaunchDLL::def_siSv);

		SVLAUNCHERDLL_API SVManage();
		SVLAUNCHERDLL_API ~SVManage();
	private:
		
	};

	//函数
	unsigned short BuildArg(SVLaunchDLL::SVPARAM &a, wchar_t* target);

};
