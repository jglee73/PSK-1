// IO__ROBOT_PERSIMMON.h : main header file for the IO__ROBOT_PERSIMMON DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CIO__ROBOT_PERSIMMONApp
// See IO__ROBOT_PERSIMMON.cpp for the implementation of this class
//

class CIO__ROBOT_PERSIMMONApp : public CWinApp
{
public:
	CIO__ROBOT_PERSIMMONApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
