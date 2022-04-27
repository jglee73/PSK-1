// PHY_IO__OES_VERITY.h : main header file for the PHY_IO__OES_VERITY DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CPHY_IO__OES_VERITYApp
// See PHY_IO__OES_VERITY.cpp for the implementation of this class
//

class CPHY_IO__OES_VERITYApp : public CWinApp
{
public:
	CPHY_IO__OES_VERITYApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
