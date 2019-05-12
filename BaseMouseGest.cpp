// BaseMouseGest.cpp: implementation of the CBaseMouseGest class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Wheeler2.h"
#include "BaseMouseGest.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBaseMouseGest::CBaseMouseGest()
{

}

CBaseMouseGest::~CBaseMouseGest()
{

}

// CArray는 복사 생성자가 없기 때문에 리턴될 수 없다.
// 참고주소 : http://www.codeguru.com/forum/archive/index.php/t-295486.html
#include "MouseGest.h"
int CBaseMouseGest::getDirection(const CPtrList& mouseGest, CString classname, BOOL isFileDialog, CArray<mark,mark>& dir)
{	
	TCHAR one_name[256], two_name[256];
	if(dir.GetSize()>0)		dir.RemoveAll();
	POSITION pos = mouseGest.GetHeadPosition();
	while(pos)
	{
		CMouseGest* one = (CMouseGest*)mouseGest.GetNext(pos);
		if(pos==NULL)
			break;
		CMouseGest* two = (CMouseGest*)mouseGest.GetAt(pos);
		::GetClassName(one->hWnd,one_name,256);
		::GetClassName(two->hWnd,two_name,256);
		if(lstrcmp(one_name,two_name)==0 && lstrcmp(one_name,classname)==0 && lstrcmp(two_name,classname)==0)
		{
			if(isFileDialog && !::isFileDialog(one->hWnd))
			{
				if(dir.GetSize()>0)		dir.RemoveAll();
				return -1;
				/*
				HWND hTarget = GetWindow(one->hWnd, GW_CHILD);
				hTarget = GetWindow(hTarget,GW_HWNDNEXT);
				hTarget = GetWindow(hTarget,GW_HWNDNEXT);
				hTarget = GetWindow(hTarget,GW_HWNDNEXT);
				
				::GetClassName(hTarget,child_name,20);
				if(lstrcmp(child_name,"ToolbarWindow32")!=0)
				{
					if(dir.GetSize()>0)		dir.RemoveAll();
					return -1;
				}
				*/
			}
			int width = two->pt.x - one->pt.x;
			int height = two->pt.y - one->pt.y;
			mark current = 
				(abs(width)>abs(height))?((width>0)?EAST:WEST):((height>0)?SOUTH:NORTH);
			if(width!=0 || height!=0)
				dir.Add(current);
			if(dir.GetSize()>1 && dir[dir.GetSize()-1] == dir[dir.GetSize()-2])
				dir.RemoveAt(dir.GetSize()-1);
		}
		else
		{
			if(dir.GetSize()>0)		dir.RemoveAll();
			return -1;
		}
	}
	
	static int dir_lookup[][2] = {
		{WEST,-1},{EAST,-1},{NORTH,-1},{SOUTH,-1},
		{NORTH,WEST},{NORTH,EAST},{SOUTH,WEST},{SOUTH,EAST},
		{WEST,EAST},{EAST,WEST},{SOUTH,NORTH},{NORTH,SOUTH},
		{EAST,NORTH},{EAST,SOUTH}	
	};
	int i;
	switch(dir.GetSize())
	{
		//typedef enum{W,E,N,S,NW,NE,SW,SE,WE,EW,SN,NS,EN,ES} move;
		//EAST,WEST,SOUTH,NORTH
	case 1:		
		for(i=0;i<4;i++)
		{
			if(dir_lookup[i][0]==dir[0])
				return i;
		}		
	case 2:
		for(i=4;i<14;i++)
		{
			if(dir_lookup[i][0]==dir[0] && dir_lookup[i][1]==dir[1])
				return i;
		}				
	default:
		return -1;
	}

}
