#if !defined(AFX_FILEDLG1_H__F85C06C8_F912_4338_9470_84D12E0B76E8__INCLUDED_)
#define AFX_FILEDLG1_H__F85C06C8_F912_4338_9470_84D12E0B76E8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FileDlg1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFileDlg dialog

#include "Wheeler2Dlg.h"

class CFileDlg : public CDialog
{
// Construction
public:
	static CFileDlg* getInstance();
	static void setInstance(CWheeler2Dlg* dlg);	
	virtual ~CFileDlg();

// Dialog Data
	//{{AFX_DATA(CFileDlg)
	enum { IDD = IDD_FILE };
	int		m_file;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CFileDlg(CWnd* pParent = NULL);   // standard constructor
	static int CALLBACK BrowseCallbackProc(HWND hWnd, UINT uMsg, LPARAM lParam, LPARAM lpData);
	BOOL BrowseFolder(HWND hParent, LPCTSTR szTitle, LPCTSTR StartPath, TCHAR *szFolder);
	static CFileDlg* self;
	CWheeler2Dlg *pParent;
	TCHAR save_dir[MAX_PATH];
	// Generated message map functions
	//{{AFX_MSG(CFileDlg)
	virtual BOOL OnInitDialog();
	afx_msg LONG OnDoAction(WPARAM wParam,LPARAM lParam);
	afx_msg void OnFileFolder();
	afx_msg void OnFileJpeg();
	afx_msg void OnFilePng();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILEDLG1_H__F85C06C8_F912_4338_9470_84D12E0B76E8__INCLUDED_)
