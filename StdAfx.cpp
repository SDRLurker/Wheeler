// stdafx.cpp : source file that includes just the standard includes
//	Wheeler2.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

void press(int kind, DWORD vkorx, DWORD scanory)
{
	switch(kind)
	{
	case KEYBOARD:
		keybd_event((BYTE)vkorx,(BYTE)scanory,0,0);
		keybd_event((BYTE)vkorx,(BYTE)scanory,KEYEVENTF_KEYUP,0);
		break;
	case LEFTMOUSE:
		mouse_event(MOUSEEVENTF_LEFTDOWN,vkorx,scanory,NULL,NULL);
		mouse_event(MOUSEEVENTF_LEFTUP,vkorx,scanory,NULL,NULL);
		break;
	case RIGHTMOUSE:
		mouse_event(MOUSEEVENTF_RIGHTDOWN,vkorx,scanory,NULL,NULL);
		mouse_event(MOUSEEVENTF_RIGHTUP,vkorx,scanory,NULL,NULL);
	}
}

void shortcut(BYTE special, BYTE normal, BYTE scan)
{
	keybd_event(special,0,0,0);
	keybd_event(normal,scan,0,0);
	Sleep(10);					
	keybd_event(normal,scan,KEYEVENTF_KEYUP,0);
	keybd_event(special,0,KEYEVENTF_KEYUP,0);
}

BOOL isFileDialog(HWND hWnd)
{
	BOOL ret = FALSE;
	TCHAR classname[20];
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
			ret = TRUE;
		}
	}
	return ret;
}

HWND getRoot(HWND hWnd, BOOL isDialog)
{
	HWND hRoot = hWnd;
	HWND hTemp = hRoot;
	
	while(TRUE)
	{
		hTemp = ::GetParent(hRoot);
		
		// 해당 윈도우의 캡션이 존재하는 지 확인
		// 부모가 바탕화면인지 확인
		if(hTemp)
		{
			hRoot = hTemp;
			TCHAR str_dialog[8];
			if(isDialog)
			{
				::GetClassName(hRoot,str_dialog,8);
				if(lstrcmp(str_dialog,"#32770")==0)
					break;
			}
		}
		else
			break;
		
	}
	return hRoot;
}