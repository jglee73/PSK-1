// PHY_RS232__ESC_CHUNGJIN.h : main header file for the PHY_RS232__ESC_CHUNGJIN DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CPHY_RS232__ESC_CHUNGJINApp
// See PHY_RS232__ESC_CHUNGJIN.cpp for the implementation of this class
//

class CPHY_RS232__ESC_CHUNGJINApp : public CWinApp
{
public:
	CPHY_RS232__ESC_CHUNGJINApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
