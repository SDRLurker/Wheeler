// TaskBar.h: interface for the CTaskBar class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TASKBAR_H__FEC41903_D752_4D0F_BC2A_139E105F6394__INCLUDED_)
#define AFX_TASKBAR_H__FEC41903_D752_4D0F_BC2A_139E105F6394__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Wheeler2Dlg.h"

// ºÎ°¡ function
#define KEYBOARD	1
#define	LEFTMOUSE	2
#define RIGHTMOUSE	3

class CTaskBar  
{
public:
	void doAction();
	CTaskBar(CWheeler2Dlg* dlg);
	virtual ~CTaskBar();
protected:
	void doTaskBar();
	CWheeler2Dlg* p_dlg;
	HWND hRunProg;		
	TCHAR window_name[128], class_name[128];
	POINT pt;
};

#endif // !defined(AFX_TASKBAR_H__FEC41903_D752_4D0F_BC2A_139E105F6394__INCLUDED_)
