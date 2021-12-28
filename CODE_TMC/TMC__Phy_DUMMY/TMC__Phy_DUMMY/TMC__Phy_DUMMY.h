// TMC__Phy_DUMMY.h : main header file for the TMC__Phy_DUMMY DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CTMC__Phy_DUMMYApp
// See TMC__Phy_DUMMY.cpp for the implementation of this class
//

class CTMC__Phy_DUMMYApp : public CWinApp
{
public:
	CTMC__Phy_DUMMYApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
