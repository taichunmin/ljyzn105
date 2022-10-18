
// ReaderDemo.h : PROJECT_NAME 
//

#pragma once

#ifndef __AFXWIN_H__
	#error "¡°stdafx.h¡±"
#endif

#include "resource.h"		


// CReaderDemoApp:
//

class CReaderDemoApp : public CWinApp
{
public:
	CReaderDemoApp();

	public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

extern CReaderDemoApp theApp;