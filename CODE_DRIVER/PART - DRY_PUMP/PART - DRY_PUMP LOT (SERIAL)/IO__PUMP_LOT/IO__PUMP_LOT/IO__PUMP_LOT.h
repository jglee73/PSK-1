// IO__PUMP_LOT.h : main header file for the IO__PUMP_LOT DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CIO__PUMP_LOTApp
// See IO__PUMP_LOT.cpp for the implementation of this class
//

class CIO__PUMP_LOTApp : public CWinApp
{
public:
	CIO__PUMP_LOTApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
