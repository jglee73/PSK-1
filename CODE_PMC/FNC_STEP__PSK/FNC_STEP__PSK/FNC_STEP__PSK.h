// FNC_STEP__PSK.h : main header file for the FNC_STEP__PSK DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CFNC_STEP__PSKApp
// See FNC_STEP__PSK.cpp for the implementation of this class
//

class CFNC_STEP__PSKApp : public CWinApp
{
public:
	CFNC_STEP__PSKApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
