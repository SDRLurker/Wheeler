#if !defined(AFX_CAPTUREPRESS_H__0A3F8D3C_233A_489D_B9BD_CF0163AE69D0__INCLUDED_)
#define AFX_CAPTUREPRESS_H__0A3F8D3C_233A_489D_B9BD_CF0163AE69D0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CapturePress.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCapturePress dialog

#include "Wheeler2Dlg.h"

// ºÎ°¡ function
#define KEYBOARD	1
#define	LEFTMOUSE	2
#define RIGHTMOUSE	3

class CCapturePress : public CDialog
{
// Construction
public:	
	static CDialog* getInstance();
	static void setInstance(CWheeler2Dlg* dlg);
	
// Dialog Data
	//{{AFX_DATA(CCapturePress)
	enum { IDD = IDD_CAPTURE_PRESS };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCapturePress)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
// Implementation
protected:
	CCapturePress(CWnd* pParent = NULL);   // standard constructor
	//HBITMAP hCaptureCopy;
	void doCopy();
	POINT end;
	void doFinish();
	POINT start;
	CWheeler2Dlg* pParent;
	static CDialog* self;
	HBITMAP hCaptureCopy;

	//HBITMAP hWillCopy;
	//afx_msg LONG OnDoStart(WPARAM wParam, LPARAM lParam);
	CBitmap CWillCopy;
	// Generated message map functions
	//{{AFX_MSG(CCapturePress)
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnPaint();
	afx_msg void OnClose();	
	afx_msg LONG OnDoStart(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CAPTUREPRESS_H__0A3F8D3C_233A_489D_B9BD_CF0163AE69D0__INCLUDED_)
