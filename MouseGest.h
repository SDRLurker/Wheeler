// MouseGest.h: interface for the CMouseGest class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MOUSEGEST_H__601D3401_B86B_476C_9674_50F755C62D24__INCLUDED_)
#define AFX_MOUSEGEST_H__601D3401_B86B_476C_9674_50F755C62D24__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMouseGest
{
public:
	CMouseGest(POINT pt,HWND hWnd);	
	POINT pt;
	HWND hWnd;
};

#endif // !defined(AFX_MOUSEGEST_H__601D3401_B86B_476C_9674_50F755C62D24__INCLUDED_)
