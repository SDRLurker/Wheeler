#if !defined(AFX_CAPTURETOGGLE_H__B69F97B4_1A19_4107_ADBB_C54511F39E9E__INCLUDED_)
#define AFX_CAPTURETOGGLE_H__B69F97B4_1A19_4107_ADBB_C54511F39E9E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CaptureToggle.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCaptureToggle dialog

#include "Wheeler2Dlg.h"

class CCaptureToggle : public CDialog
{
// Construction
public:
	static CDialog* getInstance();
	static void setInstance(CWheeler2Dlg* dlg);	

// Dialog Data
	//{{AFX_DATA(CCaptureToggle)
	enum { IDD = IDD_CAPTURE_TOGGLE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCaptureToggle)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CCaptureToggle(CWnd* pParent = NULL);   // standard constructor

	int passed;
	HBITMAP hCaptureCopy;
	void doCopy();
	BOOL isLeftPressed;
	BOOL isMiddleInit;
	void doFinish();
	CWheeler2Dlg* pParent;
	static CDialog* self;
	CBitmap CWillCopy;
	POINT start,end;

	// Generated message map functions
	//{{AFX_MSG(CCaptureToggle)
		// NOTE: the ClassWizard will add member functions here
		afx_msg void OnTimer(UINT nIDEvent);
		afx_msg void OnPaint();
		afx_msg void OnClose();
		afx_msg LONG OnDoStart(WPARAM wParam, LPARAM lParam);
		afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
		afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
		afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
		afx_msg LONG OnMButtonUp(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CAPTURETOGGLE_H__B69F97B4_1A19_4107_ADBB_C54511F39E9E__INCLUDED_)
