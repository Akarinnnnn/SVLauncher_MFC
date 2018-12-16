#pragma once
#ifdef SVLAUNCHDLL_EXPORTS
#define SVLAUNCHERDLL_API extern "C" __declspec(dllexport)
#else
#defineSVLAUNCHERDLL_API extern "C" __declspec(dllimport)
#endif

namespace SVLauncherDLL
{
	SVLAUNCHERDLL_API bool CallSV(wchar_t* arg);
	SVLAUNCHERDLL_API STARTUPINFOW siSv = {
		sizeof(siSv),NULL,NULL
	};
	SVLAUNCHERDLL_API PROCESS_INFORMATION piSv;
	using std::wstring;
	SVLAUNCHERDLL_API struct svarg
	{
		wstring cluster = L"Cluster_1";
		wstring shard = L"Master";
		wstring logbackup;
		wstring storage_root;
		wstring confdir;
		wstring tickrate;
		wstring maxplayers;
		wstring SteamID3;
		wstring SteamID64;
		bool offline;
		bool fo;
	};
}