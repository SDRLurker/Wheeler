// TitleBar.cpp: implementation of the CTitleBar class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Wheeler2.h"
#include "TitleBar.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTitleBar::CTitleBar(CWheeler2Dlg* dlg)
{
	p_dlg = dlg;
}

CTitleBar::~CTitleBar()
{

}

void CTitleBar::doAction()
{
	HWND hRoot, hTemp;
	WINDOWPLACEMENT wp;
	LONG style;
	RECT rect;
	POINT pt;
	int height = GetSystemMetrics(SM_CYCAPTION);	

	if(p_dlg->isOperate())
	{
		GetCursorPos(&pt);
		hRoot = WindowFromPoint(pt);
		while(TRUE)
		{
			hTemp = GetParent(hRoot);
			if(hTemp)
				hRoot = hTemp;
			else
				break;
		}
		GetWindowRect(hRoot,&rect);
		style = GetWindowLong(hRoot,GWL_STYLE);

		if(pt.x>=rect.left && pt.x<rect.right && pt.y>=rect.top && pt.y<rect.top+height)
		{
			p_dlg->UpdateData();
			switch(p_dlg->m_title + IDC_TITLE_NONE)
			{
				case IDC_TITLE_ZOOM:
					GetWindowPlacement(hRoot,&wp);
					if(style&WS_MAXIMIZEBOX)
					{							
						PostMessage(hRoot,WM_SYSCOMMAND,wp.showCmd==SW_MAXIMIZE?SC_RESTORE:SC_MAXIMIZE,0);						
					}
					break;
				case IDC_TITLE_MINI:
					if(style&WS_MINIMIZEBOX)
					{
						PostMessage(hRoot,WM_SYSCOMMAND,SC_MINIMIZE,0);
					}
					break;
				case IDC_TITLE_CLOSE:
					if(style&WS_SYSMENU)
					{
						PostMessage(hRoot,WM_SYSCOMMAND,SC_CLOSE,0);
					}
					break;
			}
			p_dlg->setIsDone();
		}
		
	}
}
