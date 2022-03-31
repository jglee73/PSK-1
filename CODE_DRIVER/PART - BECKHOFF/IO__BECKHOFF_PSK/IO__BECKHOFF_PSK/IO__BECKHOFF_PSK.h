// IO__BECKHOFF_PSK.h : main header file for the IO__BECKHOFF_PSK DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CIO__BECKHOFF_PSKApp
// See IO__BECKHOFF_PSK.cpp for the implementation of this class
//

class CIO__BECKHOFF_PSKApp : public CWinApp
{
public:
	CIO__BECKHOFF_PSKApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
