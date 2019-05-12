// TitleBar.h: interface for the CTitleBar class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TITLEBAR_H__78C0A59E_D4EB_4B9E_B2CE_38A1490AA4B1__INCLUDED_)
#define AFX_TITLEBAR_H__78C0A59E_D4EB_4B9E_B2CE_38A1490AA4B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Wheeler2Dlg.h"

class CTitleBar  
{
public:
	void doAction();
	CTitleBar(CWheeler2Dlg* dlg);
	virtual ~CTitleBar();
protected:
	CWheeler2Dlg* p_dlg;
};

#endif // !defined(AFX_TITLEBAR_H__78C0A59E_D4EB_4B9E_B2CE_38A1490AA4B1__INCLUDED_)
