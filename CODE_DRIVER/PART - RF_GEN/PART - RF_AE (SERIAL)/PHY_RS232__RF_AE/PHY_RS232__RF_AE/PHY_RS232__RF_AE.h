// PHY_RS232__RF_AE.h : main header file for the PHY_RS232__RF_AE DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CPHY_RS232__RF_AEApp
// See PHY_RS232__RF_AE.cpp for the implementation of this class
//

class CPHY_RS232__RF_AEApp : public CWinApp
{
public:
	CPHY_RS232__RF_AEApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
