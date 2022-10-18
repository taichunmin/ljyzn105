
// ReaderDemoDlg.h : 
//

#pragma once

#include "SWNetApi.h"
#include "afxwin.h"
#pragma comment(lib,"SWNetApi.lib")

// CReaderDemoDlg 
class CReaderDemoDlg : public CDialog
{

public:
	CReaderDemoDlg(CWnd* pParent = NULL);	

	unsigned char m_bDevType;

    static void Dev_Callback(int msg, int param1, unsigned char *param2, int param3,unsigned char *param4);
	void ShowString(CString strTemp);

	enum { IDD = IDD_READERDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	



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
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton12();
	CString m_strIP;
	CString m_strPort;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnClose();
	afx_msg void OnBnClickedButton14();
	CEdit m_ctlEdit;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	CComboBox m_ctlRF;
};
