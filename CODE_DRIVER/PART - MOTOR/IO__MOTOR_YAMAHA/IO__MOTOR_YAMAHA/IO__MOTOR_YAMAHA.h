// IO__MOTOR_YAMAHA.h : main header file for the IO__MOTOR_YAMAHA DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CIO__MOTOR_YAMAHAApp
// See IO__MOTOR_YAMAHA.cpp for the implementation of this class
//

class CIO__MOTOR_YAMAHAApp : public CWinApp
{
public:
	CIO__MOTOR_YAMAHAApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
