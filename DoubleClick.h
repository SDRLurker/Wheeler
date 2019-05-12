// DoubleClick.h: interface for the CDoubleClick class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DOUBLECLICK_H__B7A55EF9_F82C_4E44_9528_911E898F2318__INCLUDED_)
#define AFX_DOUBLECLICK_H__B7A55EF9_F82C_4E44_9528_911E898F2318__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Wheeler2Dlg.h"

#define KEYBOARD	1
#define	LEFTMOUSE	2
#define RIGHTMOUSE	3

class CDoubleClick  
{
public:	
	void doAction();
	CDoubleClick(CWheeler2Dlg* dlg);
	virtual ~CDoubleClick();
protected:	
	inline void press();
	inline void doClock();
	inline void doIcon();
	inline void doTray();
	CWheeler2Dlg* p_dlg;

	HWND hRunProg;
	TCHAR window_name[128], class_name[128];
	POINT pt;
};

#endif // !defined(AFX_DOUBLECLICK_H__B7A55EF9_F82C_4E44_9528_911E898F2318__INCLUDED_)
