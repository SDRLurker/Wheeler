// ExMouseGest.h: interface for the CExMouseGest class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXMOUSEGEST_H__309E5429_1997_4085_94D7_12D64A9F870C__INCLUDED_)
#define AFX_EXMOUSEGEST_H__309E5429_1997_4085_94D7_12D64A9F870C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Wheeler2Dlg.h"
#include "MouseGest.h"

class CExMouseGest:public CBaseMouseGest
{
public:	
	virtual ~CExMouseGest();
	void doAction();
	static CExMouseGest* getInstance();
	static void setInstance(CWheeler2Dlg *dlg);		

protected:
	static void folder(HWND hWnd);
	static void find(HWND hWnd);
	CExMouseGest(CWheeler2Dlg* dlg);

	static void close(HWND hWnd);
	static void forward(HWND hWnd);
	static void back(HWND hWnd);
	static void (*default_gf[])(HWND);
	static void top(HWND hWnd);
	static void refresh(HWND hWnd);	

	BOOL isOnce;
	CPtrList m_list;
	static CExMouseGest* self;	
	CWheeler2Dlg* pParent;
};

#endif // !defined(AFX_EXMOUSEGEST_H__309E5429_1997_4085_94D7_12D64A9F870C__INCLUDED_)
