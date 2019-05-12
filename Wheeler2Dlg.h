// Wheeler2Dlg.h : header file
//

#if !defined(AFX_WHEELER2DLG_H__E27BC55E_DD9A_405F_8A3F_692054B1C3C8__INCLUDED_)
#define AFX_WHEELER2DLG_H__E27BC55E_DD9A_405F_8A3F_692054B1C3C8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CWheeler2Dlg dialog

//#include "resource.h"
#include "BaseMouseGest.h"

class CWheeler2Dlg : public CDialog
{
// Construction
public:
	CDialog* getAddOn();
	BOOL isOperate() const;
	void setIsDone();
	CWheeler2Dlg(CWnd* pParent = NULL);	// standard constructor
	int		m_file;
	BOOL	m_one;

// Dialog Data
	//{{AFX_DATA(CWheeler2Dlg)
	enum { IDD = IDD_WHEELER2_DIALOG };
	int		m_title;
	int		m_capture;
	BOOL	m_isCapture;
	int		m_addon;
	BOOL	m_close;
	BOOL	m_clock;
	BOOL	m_icon;
	BOOL	m_tray;
	BOOL	m_exp;
	BOOL	m_dialog;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWheeler2Dlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation	
protected:	
	HICON m_hIcon;
	HMENU m_hMenu;
	BOOL m_isDone;		// 원하는 걸 실행을 마친 상태...
	BOOL m_isPressed;	// 가운데 버튼 눌림
	CDialog *p_addon;
	CDialog *p_capture;
	
	CBaseMouseGest* p_ExMouseGest;
	CBaseMouseGest* p_FileMouseGest;

	

	//afx_msg void OnAddon();
	//afx_msg LONG OnApp(WPARAM wParam,LPARAM lParam);
	//afx_msg void OnSelectCapture();

	//afx_msg void OnCapturePress();
	//afx_msg void OnCaptureToggle();

	// Generated message map functions
	//{{AFX_MSG(CWheeler2Dlg)
	afx_msg void OnAddon();
	afx_msg LONG OnApp(WPARAM wParam,LPARAM lParam);
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnIscapture();
	afx_msg void OnClose();
	afx_msg void OnDestroy();	
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSelectCapture();
	afx_msg void OnMouseExp();
	afx_msg void OnMouseDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WHEELER2DLG_H__E27BC55E_DD9A_405F_8A3F_692054B1C3C8__INCLUDED_)
