#if !defined(AFX_PROCESSDLG_H__41453E22_EF4F_4D93_BB9D_1CF4F64EDFB9__INCLUDED_)
#define AFX_PROCESSDLG_H__41453E22_EF4F_4D93_BB9D_1CF4F64EDFB9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProcessDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProcessDlg dialog

#include "Program.h"
#include "Psapi.h"
#include "afxwin.h"
#pragma comment(lib, "psapi.lib")

class CProcessDlg : public CDialog
{
// Construction
public:
	CProcessDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CProcessDlg)
	enum { IDD = IDD_PROCESS };
	CListCtrl	m_ProcessList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProcessDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CImageList m_iconSmall;
	int nIndex;
	static BOOL CALLBACK EnumWindowCallBack(HWND hWnd, LPARAM lParam);
	CProgram* pParent;

	// Generated message map functions
	//{{AFX_MSG(CProcessDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedFind();
	CEdit m_ProgramName;
//	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROCESSDLG_H__41453E22_EF4F_4D93_BB9D_1CF4F64EDFB9__INCLUDED_)
