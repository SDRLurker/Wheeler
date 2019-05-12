// FileMoustGest.h: interface for the CFileMoustGest class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEMOUSTGEST_H__7A521577_D161_4543_B784_B9AB82F20851__INCLUDED_)
#define AFX_FILEMOUSTGEST_H__7A521577_D161_4543_B784_B9AB82F20851__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Wheeler2Dlg.h"

class CFileMoustGest:public CObject 
{
public:
	CFileMoustGest(CWheeler2Dlg* dlg);
	virtual ~CFileMoustGest();
protected:
	CWheeler2Dlg* pParent;
};

#endif // !defined(AFX_FILEMOUSTGEST_H__7A521577_D161_4543_B784_B9AB82F20851__INCLUDED_)
