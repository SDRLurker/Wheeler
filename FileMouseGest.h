// FileMouseGest.h: interface for the CFileMouseGest class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEMOUSEGEST_H__D5647A56_D14F_4734_A4DE_718481B272D1__INCLUDED_)
#define AFX_FILEMOUSEGEST_H__D5647A56_D14F_4734_A4DE_718481B272D1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Wheeler2Dlg.h"
#include "MouseGest.h"

class CFileMouseGest:public CBaseMouseGest
{
public:
	void doAction();
	static CFileMouseGest* getInstance();
	static void setInstance(CWheeler2Dlg* dlg);	
	virtual ~CFileMouseGest();

protected:
	static void refresh(HWND hWnd);
	static void top(HWND hWnd);
	static void close(HWND hWnd);
	static void (*default_gf[])(HWND);

	CFileMouseGest(CWheeler2Dlg *dlg);
	BOOL isOnce;
	CWheeler2Dlg* pParent;
	static CFileMouseGest* self;
	CPtrList m_list;
};

#endif // !defined(AFX_FILEMOUSEGEST_H__D5647A56_D14F_4734_A4DE_718481B272D1__INCLUDED_)
