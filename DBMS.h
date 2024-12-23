
// DBMS.h : main header file for the DBMS application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CDBMSApp:
// See DBMS.cpp for the implementation of this class
//

class CDBMSApp : public CWinApp
{
public:
	CDBMSApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CDBMSApp theApp;
