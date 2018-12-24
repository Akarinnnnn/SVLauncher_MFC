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

	//类型
	struct SVPARAM
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
	};

	class SVManage
	{
	public:
		BOOL CallSv(SVPARAM param, wchar_t* SvDir, STARTUPINFOW* p_siSv, PROCESS_INFORMATION* p_piSv);
		BOOL CallSv(SVPARAM param, wchar_t* SvDir,  PROCESS_INFORMATION* p_piSv);
		BOOL CallSv(SVPARAM param, wchar_t* SvDir);
		BOOL CallSv(SVPARAM param, STARTUPINFOW* p_siSv, PROCESS_INFORMATION* p_piSv);
		BOOL CallSv(wchar_t* SvDir);
		BOOL CallSv(SVPARAM param);
		BOOL CallSv();
		PROCESS_INFORMATION def_piSv;
		STARTUPINFOW def_siSv;
		SVPARAM defsvparam;
		SVManage();
		~SVManage();
	private:
		friend wchar_t* BuildArg(SVPARAM a);

	};

	//变量
	//SVManage defsvman;

	//函数
	wchar_t* BuildArg(SVPARAM a);

};
