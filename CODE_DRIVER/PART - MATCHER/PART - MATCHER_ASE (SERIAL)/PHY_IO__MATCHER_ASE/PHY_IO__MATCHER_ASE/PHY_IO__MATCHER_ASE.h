// PHY_IO__MATCHER_ASE.h : main header file for the PHY_IO__MATCHER_ASE DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CPHY_IO__MATCHER_ASEApp
// See PHY_IO__MATCHER_ASE.cpp for the implementation of this class
//

class CPHY_IO__MATCHER_ASEApp : public CWinApp
{
public:
	CPHY_IO__MATCHER_ASEApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
