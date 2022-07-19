// Phy_IO__ROBOT_PERSIMMON_PSK.h : main header file for the Phy_IO__ROBOT_PERSIMMON_PSK DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CPhy_IO__ROBOT_PERSIMMON_PSKApp
// See Phy_IO__ROBOT_PERSIMMON_PSK.cpp for the implementation of this class
//

class CPhy_IO__ROBOT_PERSIMMON_PSKApp : public CWinApp
{
public:
	CPhy_IO__ROBOT_PERSIMMON_PSKApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
