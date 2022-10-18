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
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CReaderDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_ctlCom);
	DDX_Control(pDX, IDC_EDIT1, m_ctlEdit);
	DDX_Control(pDX, IDC_COMBO2, m_ctlRF);
}

BEGIN_MESSAGE_MAP(CReaderDemoDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CReaderDemoDlg::OnBnClickedButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CReaderDemoDlg::OnBnClickedButtonClose)
	ON_BN_CLICKED(IDC_BUTTON10, &CReaderDemoDlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON11, &CReaderDemoDlg::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON12, &CReaderDemoDlg::OnBnClickedButton12)
	ON_BN_CLICKED(IDC_BUTTON1, &CReaderDemoDlg::OnBnClickedButton1)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON14, &CReaderDemoDlg::OnBnClickedButton14)
	ON_BN_CLICKED(IDC_BUTTON2, &CReaderDemoDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CReaderDemoDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CReaderDemoDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CReaderDemoDlg 

BOOL CReaderDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			
	SetIcon(m_hIcon, FALSE);	

	m_strShow = "";
	((CComboBox*)GetDlgItem(IDC_COMBO1))->SetCurSel(0);
	g_pIdentifyTag = this;

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
	CString strComPort;

	((CComboBox*)GetDlgItem(IDC_COMBO1))->GetLBText(((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel(), strComPort);
	if( SWCom_OpenDevice(strComPort.GetBuffer(10), 115200) == FALSE)
	{
		m_strShow = m_strShow + "Com not exist\r\n";
		UpdateData(FALSE);
		return;
	}
	if (SWCom_GetDeviceSystemInfo(0xFF,arrBuffer) == false) //failed
	{
		//ShowString("Device is out!\r\n");
		//SWCom_CloseDevice();
		//return;
	}

	CString str = "",str1="";
	str.Format("SoftVer:%.2d.%.2d\r\n", arrBuffer[0] >> 4, arrBuffer[0] & 0x0F);
	ShowString(str);
	str.Format("HardVer:%.2d.%.2d\r\n", arrBuffer[1] >> 4, arrBuffer[1] & 0x0F);
	ShowString(str);
	str = "SN:";
	for (int i = 0; i < 7; i++)
	{
		str1.Format("%.2X", arrBuffer[2 + i]);
		str = str + str1;
	}
	str = str + "\r\n";
	ShowString(str);

	(CButton*)GetDlgItem(IDC_BUTTON_OPEN)->EnableWindow(FALSE);
	(CButton*)GetDlgItem(IDC_BUTTON_CLOSE)->EnableWindow(TRUE);
}

void CReaderDemoDlg::OnBnClickedButtonClose()
{
	SWCom_SetCallback(NULL);
	SWCom_CloseDevice();
	(CButton*)GetDlgItem(IDC_BUTTON_OPEN)->EnableWindow(TRUE);
	(CButton*)GetDlgItem(IDC_BUTTON_CLOSE)->EnableWindow(FALSE);
	ShowString("Close\r\n");
	(CButton*)GetDlgItem(IDC_BUTTON10)->EnableWindow(TRUE);
	(CButton*)GetDlgItem(IDC_BUTTON11)->EnableWindow(FALSE);
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

void CReaderDemoDlg::Dev_Callback(int msg, int param1, unsigned char *param2, int param3,unsigned char *param4)
{
	if (msg == 2)  //Data
	{
		unsigned short iTagLength = 0;
		unsigned short iTagNumber = 0;
		iTagLength = param3;  //
		iTagNumber = param1;  //
		unsigned char *pBuffer = NULL;
		pBuffer = (unsigned char *)param2;  
		//param4 

		if(iTagNumber== 0) return;  
		int iIndex = 0;
		int iLength = 0;
		unsigned char *pID;
		unsigned char bPackLength = 0;
		int iIDLen = 0;

		for(iIndex = 0; iIndex < iTagNumber; iIndex++)
		{
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

			g_pIdentifyTag->ShowString(str2+"\r\n"); 
			iLength = iLength + bPackLength + 1;
		}
	}
	else if(msg == 1) //Device Out
	{
		g_pIdentifyTag->ShowString("No Device\r\n");
	}
	else if(msg == 0) //Device Insert
	{
		g_pIdentifyTag->ShowString("Device Insert\r\n");
	}
}

void CReaderDemoDlg::OnBnClickedButton10()
{
	BOOL bReturn = FALSE;
	ShowString("ActiveMode\r\n"); 
	SWCom_SetCallback(Dev_Callback); //Callback with Json output
	ShowString("Success\r\n"); 
	(CButton*)GetDlgItem(IDC_BUTTON10)->EnableWindow(FALSE);
	(CButton*)GetDlgItem(IDC_BUTTON11)->EnableWindow(TRUE);
}

void CReaderDemoDlg::OnBnClickedButton11()
{
	SWCom_SetCallback(NULL);
	(CButton*)GetDlgItem(IDC_BUTTON10)->EnableWindow(TRUE);
	(CButton*)GetDlgItem(IDC_BUTTON11)->EnableWindow(FALSE);
}

void CReaderDemoDlg::OnBnClickedButton12()
{
	unsigned char arrBuffer[2048] = {0};
	unsigned short iTagLength = 0;
	unsigned short iTagNumber = 0;
	ShowString("AnswerMode\r\n"); 
	if (SWCom_InventoryG2(0xFF,arrBuffer,&iTagLength,&iTagNumber) == false)
	{
		ShowString("Failed\r\n"); 
		return;
	}
	if (iTagNumber == 0)
	{
		ShowString("NoData\r\n");
		return;
	}
	int iIndex = 0;
	int iLength = 0;
	unsigned char *pID;
	unsigned char bPackLength = 0;
	unsigned char bIDLength = 0;
	int iIDLen = 0;

	for(iIndex = 0; iIndex < iTagNumber; iIndex++)
	{
		bPackLength = arrBuffer[iLength];                           
		pID = (unsigned char *)&arrBuffer[1 + iLength];             
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
		ShowString(str2+"\r\n"); 

		iLength = iLength + bPackLength + 1;
	}
}

void CReaderDemoDlg::OnClose()
{
	SWCom_SetCallback(NULL);
	SWCom_CloseDevice();
	CDialog::OnClose();
}

void CReaderDemoDlg::OnBnClickedButton14()
{
	unsigned char Password[4] = {0x00,0x00,0x00,0x00};
	unsigned char Mem = 1;  //EPC   3:USER
	unsigned char WordPtr = 2;  //EPC First Address
	unsigned char WriteLen = 6; //6 Words, 12 bytes data
	unsigned char Writedata[12]= {0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xAA,0xBB};

	if (SWCom_WriteCardG2(0xFF,Password,Mem,WordPtr,WriteLen,Writedata) == false)
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
	if (SWCom_ReadDeviceOneParam(0xFF,bParamAddr, &bValue) == false)
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
	if (SWCom_SetDeviceOneParam(0xFF,bParamAddr, bValue) == false)
	{
		ShowString("Failed\r\n"); 
		return;
	}
	ShowString("Success\r\n");
}

void CReaderDemoDlg::OnBnClickedButton3()
{
	if (SWCom_RelayOn(0xFF) == false)
	{
		ShowString("Failed\r\n"); 
		return;
	}
	ShowString("Success\r\n");
}

void CReaderDemoDlg::OnBnClickedButton4()
{
	if (SWCom_RelayOff(0xFF) == false)
	{
		ShowString("Failed\r\n"); 
		return;
	}
	ShowString("Success\r\n");
}
