
//

#include "stdafx.h"
#include "ScanDevice.h"
#include "ScanDeviceDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CScanDeviceApp

BEGIN_MESSAGE_MAP(CScanDeviceApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()



CScanDeviceApp::CScanDeviceApp()
{
}



CScanDeviceApp theApp;



BOOL CScanDeviceApp::InitInstance()
{
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);

	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	SetRegistryKey(_T("Application"));

	CScanDeviceDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{

	}
	else if (nResponse == IDCANCEL)
	{
	}
	return FALSE;
}
