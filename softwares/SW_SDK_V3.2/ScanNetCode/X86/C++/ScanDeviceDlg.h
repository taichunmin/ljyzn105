
// ScanDeviceDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "SetDlg.h"

#include "NetUdpApi.h"
#pragma comment(lib,"NetUdpApi.lib")

typedef struct stScanThreadParam
{
	CString strIP;
	CString strSubMask;
	CString strGate;
	CString strTCPPort;
	CString strMac;
	CString strDevSN;
	CString strSoftVer;
	CString strHardVer;
	unsigned int cnt;
}SCAN_PARAM, *LPSCAN_PARAM;

class CScanDeviceDlg : public CDialog
{
public:
	CScanDeviceDlg(CWnd* pParent = NULL);

	HANDLE g_hMapMutex;
	CString m_strSN;
	int UpdateListShow();
	void AddDeviceList(unsigned char *pSN, unsigned char *pBuffer, unsigned short iLength);
	static void Dev_Callback(int msg, int param1, void * param2, void *param3,unsigned short param4);

	enum { IDD = IDD_SCANDEVICE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
protected:
	HICON m_hIcon;

	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	int InitListControl(void);
	CListCtrl m_LC_IPSCANED;
	SOCKET InitRecvSocket(void);
	SOCKET InitSendSocket(void);
	afx_msg void OnBnClickedBtnStart();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnNMDblclkListReaders(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnSet();
};
