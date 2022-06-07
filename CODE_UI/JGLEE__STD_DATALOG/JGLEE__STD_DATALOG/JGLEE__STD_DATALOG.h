// JGLEE__STD_DATALOG.h : main header file for the JGLEE__STD_DATALOG DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CJGLEE__STD_DATALOGApp
// See JGLEE__STD_DATALOG.cpp for the implementation of this class
//

class CJGLEE__STD_DATALOGApp : public CWinApp
{
public:
	CJGLEE__STD_DATALOGApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
