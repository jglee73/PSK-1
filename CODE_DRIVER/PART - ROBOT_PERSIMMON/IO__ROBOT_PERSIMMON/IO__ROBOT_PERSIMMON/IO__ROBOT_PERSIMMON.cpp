// IO__ROBOT_PERSIMMON.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "IO__ROBOT_PERSIMMON.h"

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

// CIO__ROBOT_PERSIMMONApp

BEGIN_MESSAGE_MAP(CIO__ROBOT_PERSIMMONApp, CWinApp)
END_MESSAGE_MAP()


// CIO__ROBOT_PERSIMMONApp construction

CIO__ROBOT_PERSIMMONApp::CIO__ROBOT_PERSIMMONApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CIO__ROBOT_PERSIMMONApp object

CIO__ROBOT_PERSIMMONApp theApp;


// CIO__ROBOT_PERSIMMONApp initialization

BOOL CIO__ROBOT_PERSIMMONApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}
