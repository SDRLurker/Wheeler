// Wheeler2.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Wheeler2.h"
#include "Wheeler2Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWheeler2App

BEGIN_MESSAGE_MAP(CWheeler2App, CWinApp)
	//{{AFX_MSG_MAP(CWheeler2App)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWheeler2App construction

CWheeler2App::CWheeler2App()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CWheeler2App object

CWheeler2App theApp;

/////////////////////////////////////////////////////////////////////////////
// CWheeler2App initialization

BOOL CWheeler2App::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

	HANDLE hMutex = CreateMutex(NULL,FALSE,TEXT("Wheeler"));
	if(!hMutex || GetLastError() == ERROR_ALREADY_EXISTS)
		return FALSE;

	CWheeler2Dlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
