// Wheeler2.h : main header file for the WHEELER2 application
//

#if !defined(AFX_WHEELER2_H__FF5BA9D5_0105_4E2D_B9C9_B0F075EE70A0__INCLUDED_)
#define AFX_WHEELER2_H__FF5BA9D5_0105_4E2D_B9C9_B0F075EE70A0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CWheeler2App:
// See Wheeler2.cpp for the implementation of this class
//

class CWheeler2App : public CWinApp
{
public:
	CWheeler2App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWheeler2App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CWheeler2App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WHEELER2_H__FF5BA9D5_0105_4E2D_B9C9_B0F075EE70A0__INCLUDED_)
