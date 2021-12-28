// PHY_RS232__FFU_SYSWORK.h : main header file for the PHY_RS232__FFU_SYSWORK DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CPHY_RS232__FFU_SYSWORKApp
// See PHY_RS232__FFU_SYSWORK.cpp for the implementation of this class
//

class CPHY_RS232__FFU_SYSWORKApp : public CWinApp
{
public:
	CPHY_RS232__FFU_SYSWORKApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
