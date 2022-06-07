// JGLEE__BUTTON.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "JGLEE__BUTTON.h"

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

// CJGLEE__BUTTONApp

BEGIN_MESSAGE_MAP(CJGLEE__BUTTONApp, CWinApp)
END_MESSAGE_MAP()


// CJGLEE__BUTTONApp construction

CJGLEE__BUTTONApp::CJGLEE__BUTTONApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CJGLEE__BUTTONApp object

CJGLEE__BUTTONApp theApp;


// CJGLEE__BUTTONApp initialization

BOOL CJGLEE__BUTTONApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}
