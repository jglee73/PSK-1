// IO__PUMP_PFEIFFIER.h : main header file for the IO__PUMP_PFEIFFIER DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CIO__PUMP_PFEIFFIERApp
// See IO__PUMP_PFEIFFIER.cpp for the implementation of this class
//

class CIO__PUMP_PFEIFFIERApp : public CWinApp
{
public:
	CIO__PUMP_PFEIFFIERApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
