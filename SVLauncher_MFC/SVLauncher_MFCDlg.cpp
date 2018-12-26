
// SVLauncher_MFCDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "SVLauncher_MFC.h"
#include "SVLauncher_MFCDlg.h"
#include "afxdialogex.h"
#include "..\SVlaunchDLL\SVlaunchDLL.hpp"
#include <iostream>
#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSVLauncherMFCDlg 对话框



CSVLauncherMFCDlg::CSVLauncherMFCDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SVLAUNCHER_MFC_DIALOG, pParent)
	, cstrRootStorage(_T(""))
	, cstrConfDir(_T(""))
	, cstrSteamID64(_T(""))
	, cstrSteamID3(_T(""))
	, cstrLogBackup(_T(""))
	, cstrMaxPlayers(_T(""))
	, cstrTR(_T(""))
	, bFO(FALSE)
	, bLocal(TRUE)
	, cstrShard(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSVLauncherMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_RS, cstrRootStorage);
	DDX_Text(pDX, IDC_CONFDIR, cstrConfDir);
	DDX_Text(pDX, IDC_CLUSTER, cstrCluster);
	DDX_Text(pDX, IDC_S_ID64, cstrSteamID64);
	DDX_Text(pDX, IDC_S_ID3, cstrSteamID3);
	DDX_Text(pDX, IDC_LOG, cstrLogBackup);
	DDX_Text(pDX, IDC_MAXPLYR, cstrMaxPlayers);
	DDX_Text(pDX, IDC_TR, cstrTR);
	DDX_Check(pDX, IDC_FO, bFO);
	DDX_Check(pDX, IDC_LOCALSV, bLocal);
	DDX_Text(pDX, IDC_SHARD, cstrShard);
}

BEGIN_MESSAGE_MAP(CSVLauncherMFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CSVLauncherMFCDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CSVLauncherMFCDlg 消息处理程序

BOOL CSVLauncherMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadStringW(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenuW(MF_SEPARATOR);
			pSysMenu->AppendMenuW(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	ShowWindow(SW_NORMAL);

	//ShowWindow(SW_MINIMIZE);

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CSVLauncherMFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSVLauncherMFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CSVLauncherMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CSVLauncherMFCDlg::OnBnClickedOk()
{
	using namespace SVLaunchDLL;
	using std::wcout;
	using std::endl;//控制台输出
	using std::wstring;
	// TODO: 在此添加控件通知处理程序代码
	SVPARAM* p_param = new SVPARAM;

	p_param->cluster = cstrCluster.GetBuffer();
	p_param->confdir = cstrConfDir.GetBuffer();
	p_param->fo = bFO;
	p_param->logbackup = cstrLogBackup.GetBuffer();
	p_param->maxplayers = cstrMaxPlayers.GetBuffer();
	p_param->offline = bLocal;
	p_param->shard = cstrShard.GetBuffer();
	p_param->SteamID3 = cstrSteamID3.GetBuffer();
	p_param->SteamID64 = cstrSteamID64.GetBuffer();
	p_param->storage_root = cstrRootStorage.GetBuffer();
	p_param->tickrate = cstrTR.GetBuffer();
	
	SVManage* p_svman1 = new SVManage;
	BOOL ret = p_svman1->CallSv(*p_param,L"K:\\SteamLibrary\\steamapps\\common\\Don't Starve Together\\bin\\");
}
