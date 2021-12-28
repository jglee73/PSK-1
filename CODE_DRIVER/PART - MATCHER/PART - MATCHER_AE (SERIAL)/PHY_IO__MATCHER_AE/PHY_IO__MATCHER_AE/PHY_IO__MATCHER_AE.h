// PHY_IO__MATCHER_AE.h : main header file for the PHY_IO__MATCHER_AE DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CPHY_IO__MATCHER_AEApp
// See PHY_IO__MATCHER_AE.cpp for the implementation of this class
//

class CPHY_IO__MATCHER_AEApp : public CWinApp
{
public:
	CPHY_IO__MATCHER_AEApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
