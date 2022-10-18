#include "stdafx.h"
#include "ReaderDemo.h"
#include "ReaderDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CReaderDemoDlg *g_pIdentifyTag;
// CReaderDemoDlg 
CReaderDemoDlg::CReaderDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CReaderDemoDlg::IDD, pParent)
	, m_strHostName(_T(""))
	, m_strPort(_T("60000"))
	, m_strSock(_T("0"))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CReaderDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, m_strHostName);
	DDX_Text(pDX, IDC_EDIT3, m_strPort);
	DDV_MaxChars(pDX, m_strPort, 5);
	DDX_Control(pDX, IDC_EDIT1, m_ctlEdit);
	DDX_Control(pDX, IDC_COMBO2, m_ctlRF);
	DDX_Text(pDX, IDC_EDIT4, m_strSock);
	DDV_MaxChars(pDX, m_strSock, 5);
}

BEGIN_MESSAGE_MAP(CReaderDemoDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CReaderDemoDlg::OnBnClickedButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CReaderDemoDlg::OnBnClickedButtonClose)
	ON_BN_CLICKED(IDC_BUTTON1, &CReaderDemoDlg::OnBnClickedButton1)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON14, &CReaderDemoDlg::OnBnClickedButton14)
	ON_BN_CLICKED(IDC_BUTTON2, &CReaderDemoDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CReaderDemoDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CReaderDemoDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CReaderDemoDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CReaderDemoDlg::OnBnClickedButton6)
END_MESSAGE_MAP()


// CReaderDemoDlg 
int g_iSock = 0;
BOOL CReaderDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			
	SetIcon(m_hIcon, FALSE);	

	m_strShow = "";
	g_pIdentifyTag = this;

	SWNet_GetLocalHostIPName((unsigned char *)m_strHostName.GetBuffer(20));
	m_strHostName.ReleaseBuffer();
	UpdateData(FALSE);

	return TRUE;  
}

void CReaderDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); 

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CReaderDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CReaderDemoDlg::OnBnClickedButtonOpen()
{
	unsigned char arrBuffer[256] = {0};
	unsigned short iPort = 1000;
	UpdateData(TRUE);
	iPort = atoi(m_strPort.GetBuffer(5));
	m_strPort.ReleaseBuffer();
	if(SWNet_Listening(iPort)  == FALSE) 
	{	
		ShowString("Failed!\r\n");
		return;
	}
	m_bOpenFlag = TRUE;
	SWNet_SetCallback(Dev_Callback);
	(CButton*)GetDlgItem(IDC_BUTTON_OPEN)->EnableWindow(FALSE);
	(CButton*)GetDlgItem(IDC_BUTTON_CLOSE)->EnableWindow(TRUE);
}

void CReaderDemoDlg::OnBnClickedButtonClose()
{
	m_bOpenFlag = FALSE;
	SWNet_CloseAllSocket();  //close all running socket, if not close first, will memory crash
	Sleep(1000); //the delay time need bigger if many clients connect  

	SWNet_SetCallback(NULL);
	SWNet_CloseDevice();
	(CButton*)GetDlgItem(IDC_BUTTON_OPEN)->EnableWindow(TRUE);
	(CButton*)GetDlgItem(IDC_BUTTON_CLOSE)->EnableWindow(FALSE);
	ShowString("Close\r\n");
}

void CReaderDemoDlg::ShowString(CString strTemp)
{
	GetDlgItem(IDC_EDIT1)->GetWindowText(m_strShow);
	if(m_strShow.GetLength() >= 1000)
	{
		m_strShow = "";
	}
    GetDlgItem(IDC_EDIT1)->SetWindowText(m_strShow + strTemp);
	m_ctlEdit.LineScroll(m_ctlEdit.GetLineCount());
}

void CReaderDemoDlg::Dev_Callback(int msg, unsigned char *param1, int param2, int param3,unsigned char *param4,int param5,unsigned char *param6)
{
	if(g_pIdentifyTag->m_bOpenFlag == FALSE) return;
	CString IP;
	IP = param1;
	CString strSock;
	strSock.Format("%d",param2);
	CString strSN="";
	if(msg == 2)
		strSN.Format("SN:%.2X%.2X%.2X%.2X%.2X%.2X%.2X",param6[0],param6[1],param6[2],param6[3],param6[4],param6[5],param6[6]);
	CString strInfo;
	strInfo = IP + ":"+strSock+" "+strSN+" ";
	g_iSock = param2;
	g_pIdentifyTag->m_strSock = strSock;

	g_pIdentifyTag->SetDlgItemText(IDC_EDIT4,g_pIdentifyTag->m_strSock);

	if (msg == 2)  //Data
	{
		unsigned short iTagLength = 0;
		unsigned short iTagNumber = 0;
		iTagLength = param3;  //
		iTagNumber = param5;  //
		unsigned char *pBuffer = NULL;
		pBuffer = (unsigned char *)param4;  
		//param4 

		if(iTagNumber== 0) return;  
		int iIndex = 0;
		int iLength = 0;
		unsigned char *pID;
		unsigned char bPackLength = 0;
		int iIDLen = 0;

		for(iIndex = 0; iIndex < iTagNumber; iIndex++)
		{
			if(g_pIdentifyTag->m_bOpenFlag == FALSE) return;
			bPackLength = pBuffer[iLength];                            
			pID = (unsigned char *)&pBuffer[1 + iLength]; 

			CString str1="", str2="", strTemp="";

			strTemp.Format("Type:%.2X ", pID[0]);
			if((pID[0] & 0x80) == 0x80)  // with TimeStamp , last 6 bytes is time
			{
				iIDLen = bPackLength - 7;
			}
			else iIDLen = bPackLength - 1;
			str2 = str2 + strTemp;  //Tag Type
			strTemp.Format("Ant:%.2X Tag:", pID[1]);
			str2 = str2 + strTemp;  //Ant
			for (int i = 2; i < iIDLen; i++)
			{
				str1.Format("%.2X ", pID[i]); 
				str2 = str2 + str1;
			}
			strTemp.Format("RSSI:%.2X", pID[iIDLen]);
			str2 = str2 + strTemp;  //RSSI

			g_pIdentifyTag->ShowString(strInfo + str2+"\r\n"); 
			iLength = iLength + bPackLength + 1;
		}
	}
	else if(msg == 1) //Device Out
	{
		g_pIdentifyTag->ShowString(strInfo + "Disconnect\r\n");
	}
	else if(msg == 0) //Device Insert
	{
		g_pIdentifyTag->ShowString(strInfo + "Connect\r\n");
	}
}

void CReaderDemoDlg::OnClose()
{
	OnBnClickedButtonClose();
	CDialog::OnClose();
}

void CReaderDemoDlg::OnBnClickedButton14()
{
	unsigned char Password[4] = {0x00,0x00,0x00,0x00};
	unsigned char Mem = 1;  //EPC   3:USER
	unsigned char WordPtr = 2;  //EPC First Address
	unsigned char WriteLen = 6; //6 Words, 12 bytes data
	unsigned char Writedata[12]= {0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xAA,0xBB};

	if (SWNet_WriteCardG2(g_iSock,Password,Mem,WordPtr,WriteLen,Writedata) == false)
	{
		ShowString("Failed\r\n"); 
		return;
	}
	ShowString("Success\r\n");
}

void CReaderDemoDlg::OnBnClickedButton1()
{
	unsigned char bValue = 0;
	unsigned char bParamAddr = 0;

	    /*01: Transport
		02: WorkMode
		03: DeviceAddr
		04: FilterTime
		05: RFPower
		06: BeepEnable
		07: UartBaudRate*/

	bParamAddr = 0x05;
	if (SWNet_ReadDeviceOneParam(g_iSock,bParamAddr, &bValue) == false)
	{
		ShowString("Failed\r\n"); 
		return;
	}
	CString strRF;
	strRF.Format("RFPower: %d\r\n",bValue);
	ShowString(strRF);
	m_ctlRF.SetCurSel(bValue);
}

void CReaderDemoDlg::OnBnClickedButton2()
{
	unsigned char bValue = 0;
	unsigned char bParamAddr = 0;

	    /*01: Transport
		02: WorkMode
		03: DeviceAddr
		04: FilterTime
		05: RFPower
		06: BeepEnable
		07: UartBaudRate*/

	bParamAddr = 0x05;  //05: RFPower
	//bValue = 26;  //RF 26dBm
	UpdateData(TRUE);
	bValue = m_ctlRF.GetCurSel();
	if (SWNet_SetDeviceOneParam(g_iSock,bParamAddr, bValue) == false)
	{
		ShowString("Failed\r\n"); 
		return;
	}
	ShowString("Success\r\n");
}

void CReaderDemoDlg::OnBnClickedButton3()
{
	if (SWNet_RelayOn(g_iSock) == false)
	{
		ShowString("Failed\r\n"); 
		return;
	}
	ShowString("Success\r\n");
}

void CReaderDemoDlg::OnBnClickedButton4()
{
	if (SWNet_RelayOff(g_iSock) == false)
	{
		ShowString("Failed\r\n"); 
		return;
	}
	ShowString("Success\r\n");
}

void CReaderDemoDlg::OnBnClickedButton5()
{
	if (SWNet_StopRead(g_iSock) == false)
	{
		ShowString("Failed\r\n"); 
		return;
	}
	ShowString("Success\r\n");
}

void CReaderDemoDlg::OnBnClickedButton6()
{
	if (SWNet_StartRead(g_iSock) == false)
	{
		ShowString("Failed\r\n"); 
		return;
	}
	ShowString("Success\r\n");
}
