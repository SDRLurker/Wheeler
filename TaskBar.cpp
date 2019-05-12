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
		(lstrcmp(window_name,taskbar)==0 ||	// 작업창일 경우...
		lstrcmp(window_name,TEXT(""))==0)  )
	{
		HWND hWnd = p_dlg->GetSafeHwnd();
		HWND hWorking; 
		TCHAR upwindow[128], upclass[128];
		RECT rect;
		GetWindowRect(hRunProg,&rect);
		
		// 후킹용 변수 선언. ※ 후킹.
		int i;
		int before_num, after_num;
		
		// Foreground 윈도우로 작업창을 설정하기 위해 추가한 부분.
		DWORD pid;
		GetWindowThreadProcessId(hRunProg,&pid);
		AttachThreadInput(pid,GetCurrentThreadId(),TRUE);
		
		// 후킹을 위해 마우스 위치 고정. ※ 후킹.
		POINT current;
		RECT r;
		GetCursorPos(&current);
		r.left = current.x-1;
		r.right = current.x;
		r.top = current.y;
		r.bottom = current.y+1;
		ClipCursor(&r);
		
		if(rect.top<=pt.y)	// 작업창 영역 안에서 가운데 버튼을 누른 경우.
		{
			// Foreground 윈도우를 작업창으로 설정. (다른 윈도우에 의해 명령 실행에 방해 받는 경우 대비.)		
			SetForegroundWindow(hRunProg);
			press(LEFTMOUSE, pt.x, pt.y);
			Sleep(50);
		}
		else					
			// 해당 버튼이 그룹화 되어 있고 프로그램 하나만 닫을 경우 다음을 수행. ※ 함수 빠져 나감.
		{
			press(RIGHTMOUSE, pt.x, pt.y);
			Sleep(100);
			press(KEYBOARD, VkKeyScan('c'), 0x2e);
			RESTORE_TIMER()		
		}
		
		// 그룹화된 버튼인지 아닌지 검사하기 위한 부분.
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
		
		// 후킹을 위해 미리 버튼 수를 계산한다. ※ 후킹.
		before_num = (int)SendMessage(hRunProg, TB_BUTTONCOUNT, 0, 0);
		
		// 프로그램을 닫는다.
		press(RIGHTMOUSE, pt.x, pt.y);
		Sleep(100);
		press(KEYBOARD, VkKeyScan('c'), 0x2e);	
		// 후킹이 아니면 alt+f4부분 소스 추가!
		
		// 후킹 관련. ※ 후킹.
		if(lstrcmp(upclass,TEXT("ToolbarWindow32"))!=0)
			// 일반 버튼을 닫았다.
		{	
			// '프로그램이 닫히나 확인하는' 후킹 실행.
			InstallHook(WM_CLOSE);
			// taskbar 버튼수가 변하나 안변하나 0.1초씩 5번 검사해 본다.
			for(i=0;i<5;i++)
			{
				
				// 닫는 윈도우가 프로그램이면 다음을 실행.	※ 함수 빠져 나감.
				ClipCursor(&r);		// Kaspersky 개쓰끼 플그램 때문에 강제로 한번더 마우스 위치 고정.
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
			
			// taskbar 버튼 개수가 변하지 않는다면 '메뉴 뜨는 윈도우 찾아 닫는' 후킹 실행.
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

