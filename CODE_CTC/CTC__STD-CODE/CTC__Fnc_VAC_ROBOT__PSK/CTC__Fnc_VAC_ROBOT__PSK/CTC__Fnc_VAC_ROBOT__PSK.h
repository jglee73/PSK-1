// CTC__Fnc_VAC_ROBOT__PSK.h : main header file for the CTC__Fnc_VAC_ROBOT__PSK DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CCTC__Fnc_VAC_ROBOT__PSKApp
// See CTC__Fnc_VAC_ROBOT__PSK.cpp for the implementation of this class
//

class CCTC__Fnc_VAC_ROBOT__PSKApp : public CWinApp
{
public:
	CCTC__Fnc_VAC_ROBOT__PSKApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
