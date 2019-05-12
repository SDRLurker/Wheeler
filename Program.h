#if !defined(AFX_PROGRAM_H__AD9CC9DB_8F31_4044_B4EB_D6D21D1788B9__INCLUDED_)
#define AFX_PROGRAM_H__AD9CC9DB_8F31_4044_B4EB_D6D21D1788B9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Program.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProgram dialog

#include "Wheeler2Dlg.h"

// ºÎ°¡ function
#define KEYBOARD	1
#define	LEFTMOUSE	2
#define RIGHTMOUSE	3

class CProgram : public CDialog
{
// Construction
public:		
	TCHAR* getProgramName();
	void setProgramName(TCHAR* str);
	static CProgram* getInstance();
	static void setInstance(CWheeler2Dlg* dlg);
	CProgram(CWnd* pParent = NULL);   // standard constructor
	virtual ~CProgram();

// Dialog Data
	//{{AFX_DATA(CProgram)
	enum { IDD = IDD_PROGRAM };
	BOOL	m_one;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProgram)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HWND GetHandleFromPID(DWORD pid);

	CWheeler2Dlg *pParent;
	static CProgram* self;
	TCHAR program_name[MAX_PATH];
	// Generated message map functions
	//{{AFX_MSG(CProgram)
	virtual BOOL OnInitDialog();
	afx_msg LONG OnDoAction(WPARAM wParam, LPARAM lParam);
	afx_msg void OnProgramSel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROGRAM_H__AD9CC9DB_8F31_4044_B4EB_D6D21D1788B9__INCLUDED_)
