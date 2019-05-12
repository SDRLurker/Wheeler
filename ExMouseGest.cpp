// ExMouseGest.cpp: implementation of the CExMouseGest class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Wheeler2.h"
#include "ExMouseGest.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CExMouseGest* CExMouseGest::self = NULL;
//typedef enum{W,E,N,S,NW,NE,SW,SE,WE,EW,SN,NS,EN,ES} move;
void (*CExMouseGest::default_gf[])(HWND) = {
	CExMouseGest::back,CExMouseGest::forward,CExMouseGest::top,CExMouseGest::refresh,
	CExMouseGest::find,CExMouseGest::folder,NULL,NULL,
	NULL,NULL,NULL,CExMouseGest::close,
	NULL,NULL
};

CExMouseGest::CExMouseGest(CWheeler2Dlg* dlg)
{
	pParent = dlg;
}

CExMouseGest::~CExMouseGest()
{

}

void CExMouseGest::setInstance(CWheeler2Dlg *dlg)
{
	if(self==NULL)
	{
		self = new CExMouseGest(dlg);
	}
}

CExMouseGest* CExMouseGest::getInstance()
{
	return self;
}

void CExMouseGest::doAction()
{
	pParent->UpdateData();
	if(pParent->m_exp)
	{
		SHORT state = GetKeyState(VK_MBUTTON);
		POINT pt;
		GetCursorPos(&pt);
		HWND hWnd = ::WindowFromPoint(pt);
		hWnd = getRoot(hWnd,FALSE);
		/*
		HWND hTemp = hWnd;		
		
		while(TRUE)
		{
			hTemp = ::GetParent(hWnd);
			
			// 해당 윈도우의 캡션이 존재하는 지 확인
			// 부모가 바탕화면인지 확인
			if(hTemp)
			{
				hWnd = hTemp;
			}
			else
				break;
			
		}
		*/

		TCHAR classname[20];
		if(state&0x8000)
		{
			isOnce = FALSE;			
			m_list.AddTail(new CMouseGest(pt,hWnd));
			::GetClassName(hWnd,classname,20);
			if(lstrcmp(classname,"CabinetWClass")==0 || lstrcmp(classname,"ExploreWClass")==0)
				pParent->setIsDone();
		}
		else
		{
			if(!isOnce)
			{
				int ret;
				isOnce = TRUE;
				CArray<mark,mark> dir;
				static const CString classname1("CabinetWClass");
				ret = getDirection(m_list,classname1,FALSE,dir);
				if(dir.GetSize()==0)
				{
					static const CString classname2("ExploreWClass");
					ret = getDirection(m_list,classname2,FALSE,dir);
				}				
				
				/*
				CString str;
				for(int i=0;i<dir.GetSize();i++)
				{
					static TCHAR* lookup[] = {"EAST\n","WEST\n","SOUTH\n","NORTH\n"};
					str += lookup[dir[i]];
				}
				AfxMessageBox(str);
				*/
								
				while(m_list.GetHeadPosition())		
					delete m_list.RemoveHead();

				if(ret>=0 && default_gf[ret]!=NULL)
				{
					default_gf[ret](hWnd);					
				}
			}
		}
	}
}

// F5 : 새로고침
void CExMouseGest::refresh(HWND hWnd)
{
	keybd_event(VK_F5,0, 0, 0);
	Sleep(10);
	keybd_event(VK_F5,0, KEYEVENTF_KEYUP, 0);

	//::PostMessage( hWnd, WM_KEYDOWN, VK_F5, 0 );
	//::PostMessage( hWnd, WM_KEYUP, VK_F5, 0 );
	//::PostMessage( hWnd, 0x111, 28931, 0);
}

// backspace : 상위 폴더 비슷.
void CExMouseGest::top(HWND hWnd)
{	
	keybd_event(VK_BACK,0, 0, 0);
	Sleep(10);
	keybd_event(VK_BACK,0, KEYEVENTF_KEYUP, 0);

	//::PostMessage( hWnd, WM_KEYDOWN, VK_BACK, 0 );
	//::PostMessage( hWnd, WM_KEYUP, VK_BACK, 0 );
	//::PostMessage( hWnd, 0x111, 40994, 0);
}

// alt + ← : 탐색기 back
void CExMouseGest::back(HWND hWnd)
{	
	keybd_event(VK_MENU,0, 0, 0);
	keybd_event(VK_LEFT,0, 0, 0);
	Sleep(10);
	keybd_event(VK_LEFT,0, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_MENU,0, KEYEVENTF_KEYUP, 0);
	
	//::PostMessage( hWnd, 0x111, 41249, 0);
}

// alt + → : 탐색기 forward
void CExMouseGest::forward(HWND hWnd)
{
	keybd_event(VK_MENU,0, 0, 0);
	keybd_event(VK_RIGHT,0, 0, 0);
	Sleep(10);
	keybd_event(VK_RIGHT,0, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_MENU,0, KEYEVENTF_KEYUP, 0);

	//::PostMessage( hWnd, 0x111, 41250, 0);
}

void CExMouseGest::close(HWND hWnd)
{
	::PostMessage( hWnd, WM_CLOSE, 0, 0 );
}

// ctrl + E : 탐색기 찾기
void CExMouseGest::find(HWND hWnd)
{
	keybd_event(VK_CONTROL,0, 0, 0);
	keybd_event(0x45,0, 0, 0);
	Sleep(10);
	keybd_event(0x45,0, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_CONTROL,0, KEYEVENTF_KEYUP, 0);
}

void CExMouseGest::folder(HWND hWnd)
{
	::PostMessage(hWnd,0x111,41525,0);
}
