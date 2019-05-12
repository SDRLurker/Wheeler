// FileMouseGest.cpp: implementation of the CFileMouseGest class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Wheeler2.h"
#include "FileMouseGest.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFileMouseGest* CFileMouseGest::self = NULL;
void (*CFileMouseGest::default_gf[])(HWND) = {
	NULL,NULL,CFileMouseGest::top,CFileMouseGest::refresh,
	NULL,NULL,NULL,NULL,
	NULL,NULL,NULL,CFileMouseGest::close,
	NULL,NULL
};


CFileMouseGest::CFileMouseGest(CWheeler2Dlg *dlg)
{
	pParent = dlg;
}

CFileMouseGest::~CFileMouseGest()
{

}

void CFileMouseGest::setInstance(CWheeler2Dlg *dlg)
{
	if(self==NULL)
	{
		self = new CFileMouseGest(dlg);
	}
}

CFileMouseGest* CFileMouseGest::getInstance()
{
	return self;
}

void CFileMouseGest::doAction()
{
	pParent->UpdateData();
	if(pParent->m_dialog)
	{
		SHORT state = GetKeyState(VK_MBUTTON);
		POINT pt;
		GetCursorPos(&pt);
		HWND hWnd = ::WindowFromPoint(pt);
		hWnd = getRoot(hWnd,TRUE);
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
				// 다이얼로그라면 중간에 빠져나간다.
				TCHAR str_dialog[8];
				::GetClassName(hWnd,str_dialog,8);
				if(lstrcmp(str_dialog,"#32770")==0)
					break;
			}
			else
				break;
			
		}
		*/

		//TCHAR classname[20];
		if(state&0x8000)
		{
			isOnce = FALSE;
			m_list.AddTail(new CMouseGest(pt,hWnd));
			if(::isFileDialog(hWnd))
				pParent->setIsDone();
			/*
			::GetClassName(hWnd,classname,20);
			if(lstrcmp(classname,"#32770")==0)
			{
				HWND hTarget = GetWindow(hWnd, GW_CHILD);
				hTarget = GetWindow(hTarget,GW_HWNDNEXT);
				hTarget = GetWindow(hTarget,GW_HWNDNEXT);
				hTarget = GetWindow(hTarget,GW_HWNDNEXT);
				::GetClassName(hTarget,classname,20);
				if(lstrcmp(classname,"ToolbarWindow32")==0)
				{
					pParent->setIsDone();
				}
			}
			*/
		}
		else
		{
			if(!isOnce)
			{
				isOnce = TRUE;
				CArray<mark,mark> dir;
				static const CString classname("#32770");
				int ret = getDirection(m_list,classname,TRUE,dir);

				/*	디버그
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

void CFileMouseGest::close(HWND hWnd)
{
	::PostMessage( hWnd, WM_CLOSE, 0, 0 );
}

void CFileMouseGest::top(HWND hWnd)
{
	keybd_event(VK_BACK,0, 0, 0);
	Sleep(10);
	keybd_event(VK_BACK,0, KEYEVENTF_KEYUP, 0);
}

void CFileMouseGest::refresh(HWND hWnd)
{
	keybd_event(VK_F5,0, 0, 0);
	Sleep(10);
	keybd_event(VK_F5,0, KEYEVENTF_KEYUP, 0);
}
