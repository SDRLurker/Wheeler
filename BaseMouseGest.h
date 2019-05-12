// BaseMouseGest.h: interface for the CBaseMouseGest class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BASEMOUSEGEST_H__F5F97BB8_F13E_4FB1_9C18_CE582753CB6C__INCLUDED_)
#define AFX_BASEMOUSEGEST_H__F5F97BB8_F13E_4FB1_9C18_CE582753CB6C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef enum{W,E,N,S,NW,NE,SW,SE,WE,EW,SN,NS,EN,ES} move;

class CBaseMouseGest  
{
public:	
	CBaseMouseGest();
	virtual ~CBaseMouseGest();
	virtual void doAction() = 0;
protected:
	int getDirection(const CPtrList& mouseGest, CString classname, BOOL isFileDialog, CArray<mark,mark>& dir);	
};

#endif // !defined(AFX_BASEMOUSEGEST_H__F5F97BB8_F13E_4FB1_9C18_CE582753CB6C__INCLUDED_)
