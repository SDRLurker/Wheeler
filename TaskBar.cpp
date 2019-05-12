// TaskBar.cpp: implementation of the CTaskBar class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Wheeler2.h"
#include "TaskBar.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTaskBar::CTaskBar(CWheeler2Dlg* dlg)
{
	p_dlg = dlg;
}

CTaskBar::~CTaskBar()
{

}

void CTaskBar::doAction()
{
	p_dlg->UpdateData();
	if(p_dlg->isOperate() && p_dlg->m_close)
	{
		GetCursorPos(&pt);
		hRunProg = WindowFromPoint(pt);		
		GetWindowText(hRunProg,window_name,128);
		GetClassName(hRunProg,class_name,128);
		if(p_dlg->m_close)
			doTaskBar();
	}
}

#define RESTORE_TIMER()				AttachThreadInput(pid,GetCurrentThreadId(),FALSE);ClipCursor(NULL);return;
void CTaskBar::doTaskBar()
{
	CString taskbar;
	taskbar.LoadString(IDS_TASKBAR);

	if(lstrcmp(class_name,TEXT("ToolbarWindow32"))==0 && 
		(lstrcmp(window_name,taskbar)==0 ||	// �۾�â�� ���...
		lstrcmp(window_name,TEXT(""))==0)  )
	{
		HWND hWnd = p_dlg->GetSafeHwnd();
		HWND hWorking; 
		TCHAR upwindow[128], upclass[128];
		RECT rect;
		GetWindowRect(hRunProg,&rect);
		
		// ��ŷ�� ���� ����. �� ��ŷ.
		int i;
		int before_num, after_num;
		
		// Foreground ������� �۾�â�� �����ϱ� ���� �߰��� �κ�.
		DWORD pid;
		GetWindowThreadProcessId(hRunProg,&pid);
		AttachThreadInput(pid,GetCurrentThreadId(),TRUE);
		
		// ��ŷ�� ���� ���콺 ��ġ ����. �� ��ŷ.
		POINT current;
		RECT r;
		GetCursorPos(&current);
		r.left = current.x-1;
		r.right = current.x;
		r.top = current.y;
		r.bottom = current.y+1;
		ClipCursor(&r);
		
		if(rect.top<=pt.y)	// �۾�â ���� �ȿ��� ��� ��ư�� ���� ���.
		{
			// Foreground �����츦 �۾�â���� ����. (�ٸ� �����쿡 ���� ��� ���࿡ ���� �޴� ��� ���.)		
			SetForegroundWindow(hRunProg);
			press(LEFTMOUSE, pt.x, pt.y);
			Sleep(50);
		}
		else					
			// �ش� ��ư�� �׷�ȭ �Ǿ� �ְ� ���α׷� �ϳ��� ���� ��� ������ ����. �� �Լ� ���� ����.
		{
			press(RIGHTMOUSE, pt.x, pt.y);
			Sleep(100);
			press(KEYBOARD, VkKeyScan('c'), 0x2e);
			RESTORE_TIMER()		
		}
		
		// �׷�ȭ�� ��ư���� �ƴ��� �˻��ϱ� ���� �κ�.
		int temp = pt.y;
		do 
		{
			pt.y -= 4;
			SetCursorPos(pt.x,pt.y);						
			hWorking = WindowFromPoint(pt);
		}while(rect.top<=pt.y);
		hWorking = WindowFromPoint(pt);
		GetWindowText(hWorking,upwindow,128);
		GetClassName(hWorking,upclass,128);
		pt.y = temp;
		SetCursorPos(pt.x,pt.y);	
		
		// ��ŷ�� ���� �̸� ��ư ���� ����Ѵ�. �� ��ŷ.
		before_num = (int)SendMessage(hRunProg, TB_BUTTONCOUNT, 0, 0);
		
		// ���α׷��� �ݴ´�.
		press(RIGHTMOUSE, pt.x, pt.y);
		Sleep(100);
		press(KEYBOARD, VkKeyScan('c'), 0x2e);	
		// ��ŷ�� �ƴϸ� alt+f4�κ� �ҽ� �߰�!
		
		// ��ŷ ����. �� ��ŷ.
		if(lstrcmp(upclass,TEXT("ToolbarWindow32"))!=0)
			// �Ϲ� ��ư�� �ݾҴ�.
		{	
			// '���α׷��� ������ Ȯ���ϴ�' ��ŷ ����.
			InstallHook(WM_CLOSE);
			// taskbar ��ư���� ���ϳ� �Ⱥ��ϳ� 0.1�ʾ� 5�� �˻��� ����.
			for(i=0;i<5;i++)
			{
				
				// �ݴ� �����찡 ���α׷��̸� ������ ����.	�� �Լ� ���� ����.
				ClipCursor(&r);		// Kaspersky ������ �ñ׷� ������ ������ �ѹ��� ���콺 ��ġ ����.
				Sleep(100);
				if(GetForegroundWindow()==hWnd)		
				{
					PostMessage(hWnd,WM_SYSCOMMAND,SC_CLOSE,0);
					RESTORE_TIMER()			
				}
				after_num = (int)SendMessage(hRunProg, TB_BUTTONCOUNT, 0, 0);
				if(before_num!=after_num)
					break;
			}
			BOOL closed = ReleaseHook();
			
			// taskbar ��ư ������ ������ �ʴ´ٸ� '�޴� �ߴ� ������ ã�� �ݴ�' ��ŷ ����.
			if(closed==FALSE && before_num==after_num)
			{
				press(KEYBOARD, VK_ESCAPE, 0x29);
				Sleep(50);
				InstallHook(WM_INITMENU);
				press(RIGHTMOUSE, pt.x, pt.y);
				Sleep(50);
				ReleaseHook();
			}
		}		
		RESTORE_TIMER()
		p_dlg->setIsDone();
	}
}

