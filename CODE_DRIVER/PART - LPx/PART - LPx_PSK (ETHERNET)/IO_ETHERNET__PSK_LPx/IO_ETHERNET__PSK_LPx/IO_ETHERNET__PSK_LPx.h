// IO_ETHERNET__PSK_LPx.h : main header file for the IO_ETHERNET__PSK_LPx DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CIO_ETHERNET__PSK_LPxApp
// See IO_ETHERNET__PSK_LPx.cpp for the implementation of this class
//

class CIO_ETHERNET__PSK_LPxApp : public CWinApp
{
public:
	CIO_ETHERNET__PSK_LPxApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
