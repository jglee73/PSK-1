// IO_RS232__ROBOT_SANKYO.h : main header file for the IO_RS232__ROBOT_SANKYO DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CIO_RS232__ROBOT_SANKYOApp
// See IO_RS232__ROBOT_SANKYO.cpp for the implementation of this class
//

class CIO_RS232__ROBOT_SANKYOApp : public CWinApp
{
public:
	CIO_RS232__ROBOT_SANKYOApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
