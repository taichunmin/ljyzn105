#pragma once
#include "afxcmn.h"


// CSetDlg �Ի���

class CSetDlg : public CDialog
{
	DECLARE_DYNAMIC(CSetDlg)

public:
	void CStringToChar(CString strSource, unsigned char *pDest);
	CSetDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSetDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_SET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CString m_strMac;
	CIPAddressCtrl m_ctlLocalIP;
	CIPAddressCtrl m_ctlSubMask;
	CIPAddressCtrl m_ctlGate;
	CIPAddressCtrl m_ctlDistinIP;
	CString m_strLocalPort;
	CString m_strDistinPort;
	BOOL m_bDHCP;
	BOOL m_bDNS;
	CString m_strDNSName;
	CString m_strHeartTime;
	CString m_strSSID;
	CString m_strWifiPass;
	CString m_strHttpHead;
	CString m_strSetTime;
	CString m_strSN;
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedOk();
};
