// MouseGest.cpp: implementation of the CMouseGest class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Wheeler2.h"
#include "MouseGest.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMouseGest::CMouseGest(POINT pt, HWND hWnd)
{
	this->pt = pt;
	this->hWnd = hWnd;
}
