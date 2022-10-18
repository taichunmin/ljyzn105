
// ReaderDemoDlg.h : 
//

#pragma once

#include "SWNetServerApi.h"
#include "afxwin.h"
#pragma comment(lib,"SWNetServerApi.lib")

// CReaderDemoDlg 
class CReaderDemoDlg : public CDialog
{

public:
	CReaderDemoDlg(CWnd* pParent = NULL);	

	unsigned char m_bDevType;

    static void Dev_Callback(int msg, unsigned char *param1, int param2, int param3,unsigned char *param4,int param5,unsigned char *param6);
	void ShowString(CString strTemp);

	enum { IDD = IDD_READERDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	

	BOOL m_bOpenFlag;

protected:
	HICON m_hIcon;

	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	CString m_strShow;
	afx_msg void OnBnClickedButtonOpen();
	afx_msg void OnBnClickedButtonClose();
	CString m_strHostName;
	CString m_strPort;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnClose();
	afx_msg void OnBnClickedButton14();
	CEdit m_ctlEdit;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	CComboBox m_ctlRF;
	CString m_strSock;
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
};
