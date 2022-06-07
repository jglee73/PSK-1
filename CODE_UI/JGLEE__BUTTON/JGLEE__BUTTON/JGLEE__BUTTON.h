// JGLEE__BUTTON.h : main header file for the JGLEE__BUTTON DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CJGLEE__BUTTONApp
// See JGLEE__BUTTON.cpp for the implementation of this class
//

class CJGLEE__BUTTONApp : public CWinApp
{
public:
	CJGLEE__BUTTONApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
