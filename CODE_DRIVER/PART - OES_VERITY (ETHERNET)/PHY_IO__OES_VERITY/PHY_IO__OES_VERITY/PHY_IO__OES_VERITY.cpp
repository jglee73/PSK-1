// PHY_IO__OES_VERITY.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "PHY_IO__OES_VERITY.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: If this DLL is dynamically linked against the MFC DLLs,
//		any functions exported from this DLL which call into
//		MFC must have the AFX_MANAGE_STATE macro added at the
//		very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

// CPHY_IO__OES_VERITYApp

BEGIN_MESSAGE_MAP(CPHY_IO__OES_VERITYApp, CWinApp)
END_MESSAGE_MAP()


// CPHY_IO__OES_VERITYApp construction

CPHY_IO__OES_VERITYApp::CPHY_IO__OES_VERITYApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CPHY_IO__OES_VERITYApp object

CPHY_IO__OES_VERITYApp theApp;


// CPHY_IO__OES_VERITYApp initialization

BOOL CPHY_IO__OES_VERITYApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}
