
// SVLauncher_MFCDlg.h: 头文件
//

#pragma once


// CSVLauncherMFCDlg 对话框
class CSVLauncherMFCDlg : public CDialogEx
{
// 构造
public:
	CSVLauncherMFCDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SVLAUNCHER_MFC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
private:
	CString cstrRootStorage;
	CString cstrConfDir;
	CString cstrCluster;
	CString cstrSteamID64;
	CString cstrSteamID3;
	CString cstrLogBackup;
	CString cstrMaxPlayers;
	CString cstrTR;
	CString cstrShard;
	BOOL bFO;
	BOOL bLocal;
};
