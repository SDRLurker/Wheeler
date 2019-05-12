// DoubleClick.cpp: implementation of the CDoubleClick class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Wheeler2.h"
#include "DoubleClick.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDoubleClick::CDoubleClick(CWheeler2Dlg* dlg)
{
	p_dlg = dlg;
}

CDoubleClick::~CDoubleClick()
{

}

void CDoubleClick::doAction()
{		
	if(p_dlg->isOperate())
	{
		GetCursorPos(&pt);
		hRunProg = WindowFromPoint(pt);
		GetWindowText(hRunProg,window_name,128);
		GetClassName(hRunProg,class_name,128);
		
		p_dlg->UpdateData();
		if(p_dlg->m_tray)
		{
			doTray();
		}
		if(p_dlg->m_icon)
		{
			doIcon();
		}
		if(p_dlg->m_clock)
		{
			doClock();
		}
	}
}

void CDoubleClick::doTray()
{
	CString tray;
	tray.LoadString(IDS_TRAY);

	if(lstrcmp(window_name,tray)==0)
	{
		press();
	}	
}

void CDoubleClick::doIcon()
{
	if(lstrcmp(window_name,TEXT("FolderView"))==0)
	{
		LRESULT current = SendMessage(hRunProg,LVM_GETHOTITEM,0,0);
		if(current!=-1)
			press();
	}	
}

void CDoubleClick::doClock()
{
	if(lstrcmp(class_name,TEXT("TrayClockWClass"))==0)
	{
		press();	
	}	
}


void CDoubleClick::press()
{
	mouse_event(MOUSEEVENTF_LEFTDOWN,pt.x,pt.y,NULL,NULL);
	mouse_event(MOUSEEVENTF_LEFTUP,pt.x,pt.y,NULL,NULL);
	Sleep(10);
	mouse_event(MOUSEEVENTF_LEFTDOWN,pt.x,pt.y,NULL,NULL);
	mouse_event(MOUSEEVENTF_LEFTUP,pt.x,pt.y,NULL,NULL);
	p_dlg->setIsDone();
}