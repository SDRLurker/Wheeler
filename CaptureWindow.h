#if !defined(AFX_CAPTUREWINDOW_H__0A945FB4_67FF_429A_904F_F570DD0A8567__INCLUDED_)
#define AFX_CAPTUREWINDOW_H__0A945FB4_67FF_429A_904F_F570DD0A8567__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CaptureWindow.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCaptureWindow dialog

#include "Wheeler2Dlg.h"

class CCaptureWindow : public CDialog
{
// Construction
public:
	static CCaptureWindow* getInstance();
	static void setInstance(CWheeler2Dlg *dlg);	

// Dialog Data
	//{{AFX_DATA(CCaptureWindow)
	enum { IDD = IDD_CAPTURE_WINDOW };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCaptureWindow)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CCaptureWindow(CWnd* pParent = NULL);   // standard constructor
	CCriticalSection m_cs;
	//HWND hBefore;
	void doAction();
	BOOL m_isDone;
	BOOL m_isPressed;
	HWND hRoot;
	static CCaptureWindow* self;
	CWheeler2Dlg* pParent;

	// afx_msg LONG OnDoStart(WPARAM wParam, LPARAM lParam);
	// Generated message map functions
	//{{AFX_MSG(CCaptureWindow)
	afx_msg LONG OnDoStart(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CAPTUREWINDOW_H__0A945FB4_67FF_429A_904F_F570DD0A8567__INCLUDED_)
