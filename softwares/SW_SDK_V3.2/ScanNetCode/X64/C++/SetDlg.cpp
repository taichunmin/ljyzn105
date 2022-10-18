// SetDlg.cpp
//

#include "stdafx.h"
#include "ScanDevice.h"
#include "SetDlg.h"
#include "ScanDeviceDlg.h"
#include "NetUdpApi.h"

// CSetDlg

IMPLEMENT_DYNAMIC(CSetDlg, CDialog)

CSetDlg::CSetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetDlg::IDD, pParent)
	, m_strMac(_T(""))
	, m_strLocalPort(_T(""))
	, m_strDistinPort(_T(""))
	, m_bDHCP(FALSE)
	, m_bDNS(FALSE)
	, m_strDNSName(_T(""))
	, m_strHeartTime(_T(""))
	, m_strSSID(_T(""))
	, m_strSN(_T(""))
{

}

CSetDlg::~CSetDlg()
{
}

void CSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_MACADDR, m_strMac);
	DDV_MaxChars(pDX, m_strMac, 12);
	DDX_Control(pDX, IDC_IPADDRESS1, m_ctlLocalIP);
	DDX_Control(pDX, IDC_IPADDRESS2, m_ctlSubMask);
	DDX_Control(pDX, IDC_IPADDRESS3, m_ctlGate);
	DDX_Control(pDX, IDC_IPADDRESS4, m_ctlDistinIP);
	DDX_Text(pDX, IDC_EDIT3, m_strLocalPort);
	DDV_MaxChars(pDX, m_strLocalPort, 5);
	DDX_Text(pDX, IDC_EDIT4, m_strDistinPort);
	DDV_MaxChars(pDX, m_strDistinPort, 5);
	DDX_Check(pDX, IDC_CHECK1, m_bDHCP);
	DDX_Check(pDX, IDC_CHECK2, m_bDNS);
	DDX_Text(pDX, IDC_EDIT5, m_strDNSName);
	DDV_MaxChars(pDX, m_strDNSName, 31);
	DDX_Text(pDX, IDC_EDIT6, m_strHeartTime);
	DDV_MaxChars(pDX, m_strHeartTime, 3);
	DDX_Text(pDX, IDC_EDIT_SN, m_strSN);
}


BEGIN_MESSAGE_MAP(CSetDlg, CDialog)
	ON_WM_INITMENU()
	ON_WM_INITMENUPOPUP()
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BUTTON3, &CSetDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDOK, &CSetDlg::OnBnClickedOk)
END_MESSAGE_MAP()


unsigned char g_arrDeviceSN[8];

void CSetDlg::CStringToChar(CString strSource, unsigned char *pDest)
{
	int iLength = strSource.GetLength();
	int i = 0;
	BYTE ucTemp = 0;
	for(i= 0; i<iLength/2 - 1; i++)
	{
		ucTemp = strSource.GetAt(i*2 + 2);
		if(ucTemp >= '0' && ucTemp <= '9') pDest[i] = ucTemp - '0';
		else if(ucTemp >= 'A' && ucTemp <= 'F') pDest[i] = ucTemp - 'A' + 10;
		else if(ucTemp >= 'a' && ucTemp <= 'f') pDest[i] = ucTemp - 'a' + 10;
		else  pDest[i] = 0;
		ucTemp = strSource.GetAt(i*2+1 + 2);
		if(ucTemp >= '0' && ucTemp <= '9') pDest[i] = pDest[i]*16 + ucTemp - '0';
		else if(ucTemp >= 'A' && ucTemp <= 'F') pDest[i] = pDest[i]*16 + ucTemp - 'A' + 10;
		else if(ucTemp >= 'a' && ucTemp <= 'f') pDest[i] = pDest[i]*16 + ucTemp - 'a' + 10;
		else  pDest[i] = 0;
	}
}

BOOL CSetDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	CScanDeviceDlg *parent = (CScanDeviceDlg*)(GetParent());

	m_strSN = parent->m_strSN;
	CStringToChar(m_strSN,g_arrDeviceSN);
	UpdateData(FALSE);
	OnBnClickedButton3();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CSetDlg::OnBnClickedButton3()
{
	unsigned char pParam[256]={0};
	unsigned short iLength = 0;
	unsigned char *ucBuffer;
	if(NetUdp_ReadDeviceNetParam(g_arrDeviceSN, pParam, &iLength))
	{
		ucBuffer = &pParam[2];
		m_strMac.Format("%.2X%.2X%.2X%.2X%.2X%.2X", ucBuffer[0],ucBuffer[1],ucBuffer[2],ucBuffer[3],ucBuffer[4],ucBuffer[5]);		
		DWORD dwIP = 0; 
		dwIP = ((ucBuffer[6]<<24)|(ucBuffer[7]<<16)|(ucBuffer[8]<<8)|ucBuffer[9]);
		m_ctlLocalIP.SetAddress(dwIP);
		dwIP = ((ucBuffer[10]<<24)|(ucBuffer[11]<<16)|(ucBuffer[12]<<8)|ucBuffer[13]);
		m_ctlSubMask.SetAddress(dwIP);
		dwIP = ((ucBuffer[14]<<24)|(ucBuffer[15]<<16)|(ucBuffer[16]<<8)|ucBuffer[17]);
		m_ctlGate.SetAddress(dwIP);
		dwIP = ((ucBuffer[18]<<24)|(ucBuffer[19]<<16)|(ucBuffer[20]<<8)|ucBuffer[21]);
		m_ctlDistinIP.SetAddress(dwIP);

		m_strLocalPort.Format("%d", ucBuffer[23]*256 + ucBuffer[22]);
		m_strDistinPort.Format("%d", ucBuffer[25]*256 + ucBuffer[24]);

		m_bDHCP = ucBuffer[26];
		m_bDNS = ucBuffer[27];
		m_strHeartTime.Format("%d", ucBuffer[28]);

		m_strDNSName.Format("%s", &ucBuffer[29]);
		m_strSSID.Format("%s", &ucBuffer[29+32]);
		m_strWifiPass.Format("%s", &ucBuffer[29+64]);

		m_strHttpHead.Format("%s", &ucBuffer[29+96]);

		UpdateData(FALSE);
	}
	else
	{
		MessageBoxEx(NULL,"Operation Failed.","Info",MB_OK,MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US));
	}
}

unsigned char ChangeASCIIToHex(unsigned char uDataH, unsigned char uDataL)  
{
	unsigned char arrTemp[2];
	if( uDataH >= '0' && uDataH <= '9')  arrTemp[0] = uDataH - '0';
	else if( uDataH >= 'a' && uDataH <= 'f')  arrTemp[0] = uDataH - 'a' + 10;
	else if( uDataH >= 'A' && uDataH <= 'F')  arrTemp[0] = uDataH - 'A' + 10;
	else arrTemp[0] = '0';

	if( uDataL >= '0' && uDataL <= '9')  arrTemp[1] = uDataL - '0';
	else if( uDataL >= 'a' && uDataL <= 'f')  arrTemp[1] = uDataL - 'a' + 10;
	else if( uDataL >= 'A' && uDataL <= 'F')  arrTemp[1] = uDataL - 'A' + 10;
	else arrTemp[1] = '0';

	return (arrTemp[0] *16 + arrTemp[1]);
}

void StringToHex(unsigned char *pDest, unsigned char *pSource, unsigned int iLength)
{
	unsigned int i=0;
	for(i=0; i<iLength; i++)
	{
		pDest[i] = ChangeASCIIToHex( pSource[i*2], pSource[i*2+1]);
	}
	pDest[i] = 0;
}

void CSetDlg::OnBnClickedOk()
{
	UpdateData(TRUE);
	unsigned char ucBuffer[256] = {0};
	memset(ucBuffer ,0 , 256);
	StringToHex(ucBuffer, (unsigned char *)m_strMac.GetBuffer(20), 6);
	m_strMac.ReleaseBuffer();

	DWORD dwIP = 0; 
	m_ctlLocalIP.GetAddress(dwIP);
	ucBuffer[6] = (unsigned char)(dwIP >> 24);
	ucBuffer[7] = (unsigned char)((dwIP & 0xFF0000) >> 16);
	ucBuffer[8] = (unsigned char)((dwIP & 0xFF00) >> 8);
	ucBuffer[9] = (unsigned char)(dwIP & 0xff);

	m_ctlSubMask.GetAddress(dwIP);
	ucBuffer[10] = (unsigned char)(dwIP >> 24);
	ucBuffer[11] = (unsigned char)((dwIP & 0xFF0000) >> 16);
	ucBuffer[12] = (unsigned char)((dwIP & 0xFF00) >> 8);
	ucBuffer[13] = (unsigned char)(dwIP & 0xff);

	m_ctlGate.GetAddress(dwIP);
	ucBuffer[14] = (unsigned char)(dwIP >> 24);
	ucBuffer[15] = (unsigned char)((dwIP & 0xFF0000) >> 16);
	ucBuffer[16] = (unsigned char)((dwIP & 0xFF00) >> 8);
	ucBuffer[17] = (unsigned char)((dwIP & 0xff));

	m_ctlDistinIP.GetAddress(dwIP);
	ucBuffer[18] = (unsigned char)(dwIP >> 24);
	ucBuffer[19] = (unsigned char)((dwIP & 0xFF0000) >> 16);
	ucBuffer[20] = (unsigned char)((dwIP & 0xFF00) >> 8);
	ucBuffer[21] = (unsigned char)(dwIP & 0xff);

	ucBuffer[22] = atoi(m_strLocalPort) % 256;
	ucBuffer[23] = atoi(m_strLocalPort) / 256;

	ucBuffer[24] = atoi(m_strDistinPort) % 256;
	ucBuffer[25] = atoi(m_strDistinPort) / 256;

	ucBuffer[26] = m_bDHCP;
	ucBuffer[27] = m_bDNS;
	ucBuffer[28] =atoi( m_strHeartTime);

	strcpy_s((char *)&ucBuffer[29],   32, (char *)m_strDNSName.GetBuffer(32));
	m_strDNSName.ReleaseBuffer();
	strcpy_s((char *)&ucBuffer[29+32],32, (char *)m_strSSID.GetBuffer(32));
	m_strSSID.ReleaseBuffer();
	strcpy_s((char *)&ucBuffer[29+64],32, (char *)m_strWifiPass.GetBuffer(32));
	m_strWifiPass.ReleaseBuffer();
	strcpy_s((char *)&ucBuffer[29+96],80, (char *)m_strHttpHead.GetBuffer(64));
	m_strHttpHead.ReleaseBuffer();

	if(NetUdp_SetDeviceNetParam(g_arrDeviceSN,ucBuffer,29+96+80) == TRUE)
	{
		MessageBoxEx(NULL,"Set Param Success.","Info",MB_OK,MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US));
	}
	else
	{
		MessageBoxEx(NULL,"Set Param Failed.","Info",MB_OK,MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US));
	}
}
