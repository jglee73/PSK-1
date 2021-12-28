// Phy_IO__PUMP.h : main header file for the Phy_IO__PUMP DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CPhy_IO__PUMPApp
// See Phy_IO__PUMP.cpp for the implementation of this class
//

class CPhy_IO__PUMPApp : public CWinApp
{
public:
	CPhy_IO__PUMPApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
