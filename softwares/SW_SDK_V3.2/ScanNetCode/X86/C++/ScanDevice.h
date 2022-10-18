
// ScanDeviceApp.h : PROJECT_NAME 
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		


// CScanDeviceApp:
//

class CScanDeviceApp : public CWinAppEx
{
public:
	CScanDeviceApp();

public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

extern CScanDeviceApp theApp;
