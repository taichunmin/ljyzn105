
// ScanDeviceDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ScanDevice.h"
#include "ScanDeviceDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CScanDeviceDlg *g_parent;
// CScanDeviceDlg dialog

CScanDeviceDlg::CScanDeviceDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CScanDeviceDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CScanDeviceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_READERS, m_LC_IPSCANED);
}

BEGIN_MESSAGE_MAP(CScanDeviceDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CScanDeviceDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_START, &CScanDeviceDlg::OnBnClickedBtnStart)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_READERS, &CScanDeviceDlg::OnNMDblclkListReaders)
	ON_BN_CLICKED(IDC_BTN_SET, &CScanDeviceDlg::OnBnClickedBtnSet)
END_MESSAGE_MAP()


// CScanDeviceDlg message handlers
CArray<LPSCAN_PARAM> g_arr_Reader;
BOOL g_bStart = FALSE;

BOOL CScanDeviceDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	InitListControl();
	g_arr_Reader.SetSize(256);

	if(NetUdp_OpenDevice() == FALSE)
	{
		MessageBox("Socket Error");
	}
	g_parent = this;
	NetUdp_SetCallbackAddr(Dev_Callback);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CScanDeviceDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CScanDeviceDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CScanDeviceDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	 OnOK();
}

int CScanDeviceDlg::InitListControl(void)
{
	CRect rect;
	CListCtrl *pListView = (CListCtrl*)GetDlgItem(IDC_LIST_READERS);
	pListView->GetClientRect(&rect);
	pListView->SetExtendedStyle(pListView->GetExtendedStyle()|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	m_LC_IPSCANED.InsertColumn(0, "Index", LVCFMT_CENTER, rect.Width()/9-40);
	m_LC_IPSCANED.InsertColumn(1, "IP",   LVCFMT_CENTER, rect.Width()/9+15);
	m_LC_IPSCANED.InsertColumn(2, "Mask", LVCFMT_CENTER, rect.Width()/9+15);
	m_LC_IPSCANED.InsertColumn(3, "Gate", LVCFMT_CENTER, rect.Width()/9+15);
	m_LC_IPSCANED.InsertColumn(4, "TCP Port", LVCFMT_CENTER, rect.Width()/9-20);
	m_LC_IPSCANED.InsertColumn(5, "MAC",  LVCFMT_CENTER, rect.Width()/9+30);
	m_LC_IPSCANED.InsertColumn(6, "DevSN", LVCFMT_CENTER, rect.Width()/9+30);
	m_LC_IPSCANED.InsertColumn(7, "SoftVer", LVCFMT_CENTER, rect.Width()/9-25);
	m_LC_IPSCANED.InsertColumn(8, "HardVer", LVCFMT_CENTER, rect.Width()/9-20);
	pListView->SetExtendedStyle(pListView->GetExtendedStyle()|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

unsigned int g_SendCnt = 0;

void CScanDeviceDlg::OnBnClickedBtnStart()
{
	// TODO: Add your control notification handler code here
	if (g_bStart == FALSE)
	{
		g_arr_Reader.RemoveAll();
		m_LC_IPSCANED.DeleteAllItems();
		g_SendCnt = 0;

		SetTimer(0, 500, NULL);
		g_bStart = TRUE;
		SetDlgItemText(IDC_BTN_START, _T("Stop"));
	}
	else
	{
		KillTimer(0);
		g_bStart = FALSE;
		SetDlgItemText(IDC_BTN_START, _T("Start"));
	}
}

void CScanDeviceDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	UpdateListShow();
	if(NetUdp_ScanDevice() == TRUE) g_SendCnt++;
	KillTimer(0);
	SetTimer(0, 5000, NULL);
	CDialog::OnTimer(nIDEvent);
}

int CScanDeviceDlg::UpdateListShow()
{
	int j = 0;

	m_LC_IPSCANED.DeleteAllItems();
	int arr_cnt = g_arr_Reader.GetSize();
	for (int i = 0; i < arr_cnt; i++, j++)
	{
		if (g_SendCnt - g_arr_Reader[i]->cnt >= 3)
		{
			continue;
		}
		CString sNo;
		sNo.Format(_T("%d"), j + 1);
		m_LC_IPSCANED.InsertItem(j, sNo);
		m_LC_IPSCANED.SetItemText(j, 1, g_arr_Reader[i]->strIP);
		m_LC_IPSCANED.SetItemText(j, 2, g_arr_Reader[i]->strSubMask);
		m_LC_IPSCANED.SetItemText(j, 3, g_arr_Reader[i]->strGate);
		m_LC_IPSCANED.SetItemText(j, 4, g_arr_Reader[i]->strTCPPort);
		m_LC_IPSCANED.SetItemText(j, 5, g_arr_Reader[i]->strMac);
		m_LC_IPSCANED.SetItemText(j, 6, g_arr_Reader[i]->strDevSN);
		m_LC_IPSCANED.SetItemText(j, 7, g_arr_Reader[i]->strSoftVer);
		m_LC_IPSCANED.SetItemText(j, 8, g_arr_Reader[i]->strHardVer);
		m_LC_IPSCANED.EnsureVisible(m_LC_IPSCANED.GetItemCount() - 1, true);
	}
	return 0;
}

void CScanDeviceDlg::OnDestroy()
{
	CDialog::OnDestroy();
}


void CScanDeviceDlg::OnNMDblclkListReaders(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	NM_LISTVIEW* pNMListView=(NM_LISTVIEW*)pNMHDR; 
	CRect rc;  
	int m_Row = pNMListView->iItem; 
	int m_Col = pNMListView->iSubItem;
	CString strTemp ="";
	if(pNMListView->iSubItem != 0)
	{   
		KillTimer(0);
		g_bStart = FALSE;
		SetDlgItemText(IDC_BTN_START, _T("Start"));
		strTemp = m_LC_IPSCANED.GetItemText(m_Row,6);
		if(strTemp != "")
		{
			m_strSN = strTemp;
			CSetDlg dlgSet;
			dlgSet.DoModal();
		}
	} 
	*pResult = 0;
	
}

void CScanDeviceDlg::AddDeviceList(unsigned char *pSN, unsigned char *pBuffer, unsigned short iLength)
{
	CString strIP;
	CString strSubMask;
	CString strGate;
	CString strTCPPort;
	CString strMac;
	CString strDevSN;
	CString strSoftVer;
	CString strHardVer;

	strDevSN.Format("%.2X%.2X%.2X%.2X%.2X%.2X%.2X", pSN[0],pSN[1],pSN[2],pSN[3],pSN[4],pSN[5],pSN[6]);
	strSoftVer.Format("%d.%d", pBuffer[0] /16 , pBuffer[0]%16);
	strHardVer.Format("%d.%d", pBuffer[1] /16 , pBuffer[1]%16);
	strMac.Format("%.2X%.2X%.2X%.2X%.2X%.2X", pBuffer[2],pBuffer[3],pBuffer[4],pBuffer[5],pBuffer[6],pBuffer[7]);
	strIP.Format("%d.%d.%d.%d",      pBuffer[8],pBuffer[9],pBuffer[10],pBuffer[11]);
	strSubMask.Format("%d.%d.%d.%d", pBuffer[12],pBuffer[13],pBuffer[14],pBuffer[15]);
	strGate.Format("%d.%d.%d.%d",    pBuffer[16],pBuffer[17],pBuffer[18],pBuffer[19]);
	strTCPPort.Format("%d",pBuffer[20]*256 + pBuffer[21]);
	int arr_cnt = g_arr_Reader.GetSize();
	int j = 0;
	for (j = 0; j < arr_cnt; j++)
	{
		if (g_arr_Reader[j]->strDevSN == strDevSN)
		{
			g_arr_Reader[j]->cnt = g_SendCnt;
			break;
		}
	}
	if (j == arr_cnt)
	{
		LPSCAN_PARAM sr = new SCAN_PARAM;
		sr->strIP = strIP;
		sr->strSubMask = strSubMask;
		sr->strGate = strGate;
		sr->strTCPPort = strTCPPort;
		sr->strMac = strMac;
		sr->strDevSN = strDevSN;
		sr->strSoftVer = strSoftVer;
		sr->strHardVer = strHardVer;
		sr->cnt = g_SendCnt;
		g_arr_Reader.Add(sr);
		UpdateListShow();
	}
}

void CScanDeviceDlg::Dev_Callback(int msg, int param1, void * param2, void * param3, unsigned short param4)
{
	if (msg == 2) 
	{
		if(param1 == 1)
		{
			g_parent->AddDeviceList((unsigned char *)param2, (unsigned char *)param3, param4);
		}
	}
}

void CScanDeviceDlg::OnBnClickedBtnSet()
{
	POSITION pos = m_LC_IPSCANED.GetFirstSelectedItemPosition(); 
	if(pos)
	{
		int nItem = m_LC_IPSCANED.GetNextSelectedItem(pos);
		KillTimer(0);
		g_bStart = FALSE;
		CString strTemp;
		SetDlgItemText(IDC_BTN_START, _T("Start"));
		strTemp = m_LC_IPSCANED.GetItemText(nItem,6);
		if(strTemp != "")
		{
			m_strSN = strTemp;
			CSetDlg dlgSet;
			dlgSet.DoModal();
		}
	}
}
