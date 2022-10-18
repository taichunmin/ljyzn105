
//

#include "stdafx.h"
#include "ReaderDemo.h"
#include "ReaderDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CReaderDemoApp

BEGIN_MESSAGE_MAP(CReaderDemoApp, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()



CReaderDemoApp::CReaderDemoApp()
{
}



CReaderDemoApp theApp;



BOOL CReaderDemoApp::InitInstance()
{
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);

	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	AfxEnableControlContainer();

	SetRegistryKey(_T("Application"));

	CReaderDemoDlg dlg;
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
