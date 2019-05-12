// CaptureWindow.cpp : implementation file
//

#include "stdafx.h"
#include "Wheeler2.h"
#include "CaptureWindow.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCaptureWindow dialog

CCaptureWindow* CCaptureWindow::self = NULL;

CCaptureWindow::CCaptureWindow(CWnd* pParent /*=NULL*/)
	: CDialog(CCaptureWindow::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCaptureWindow)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	this->pParent = (CWheeler2Dlg*)pParent;
	m_isDone = m_isPressed = FALSE;
}


void CCaptureWindow::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCaptureWindow)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCaptureWindow, CDialog)
	//{{AFX_MSG_MAP(CCaptureWindow)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_ACTION,OnDoStart)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCaptureWindow message handlers

LONG CCaptureWindow::OnDoStart(WPARAM wParam, LPARAM lParam)
{
	if(pParent->isOperate() && pParent->m_isCapture && pParent->m_capture + IDC_CAPTURE_PRESS == IDC_CAPTURE_WINDOW)
	{		
		SHORT state = GetKeyState(VK_MBUTTON);
		if(state&0x8000)
		{
			m_isPressed = TRUE;
		}
		else
		{
			m_isPressed = FALSE;
			m_isDone = FALSE;
		}		
		doAction();
	}
	else
	{
		m_isPressed = FALSE;
		m_isDone = FALSE;
	}
	//	::InvalidateRect(NULL,NULL,TRUE);

	return 0;
}

void CCaptureWindow::setInstance(CWheeler2Dlg *dlg)
{
	if(self==NULL)
	{
		self = new CCaptureWindow(dlg);
		self->Create(IDD_CAPTURE_WINDOW);
	}
}

CCaptureWindow* CCaptureWindow::getInstance()
{
	return self;
}

void CCaptureWindow::doAction()
{
	POINT pt;
	RECT rect;
	//HWND hTemp;
	WINDOWPLACEMENT wp;

	GetCursorPos(&pt);
	hRoot = ::WindowFromPoint(pt);
	hRoot = getRoot(hRoot,TRUE);
	/*
	hTemp = hRoot;		
	
	while(TRUE)
	{
		hTemp = ::GetParent(hRoot);
		
		// 해당 윈도우의 캡션이 존재하는 지 확인
		// 부모가 바탕화면인지 확인
		if(hTemp)
		{
			hRoot = hTemp;
			TCHAR str_dialog[8];
			::GetClassName(hRoot,str_dialog,8);
			if(lstrcmp(str_dialog,"#32770")==0)
				break;
		}
		else
			break;		
	}
	*/
	//if(hBefore!=hRoot)
	//	::InvalidateRect(NULL,NULL,TRUE);
	//hBefore = hRoot;
	
	::GetWindowRect(hRoot,&rect);
	::GetWindowPlacement(hRoot,&wp);
	
	if(m_isPressed && !m_isDone && pParent->isOperate())
	{	
		m_cs.Lock();
		//::SetFocus(hRoot);		
		HDC hDC = ::GetWindowDC(hRoot);
		HDC hMemDC = CreateCompatibleDC(hDC);
		HBITMAP hBitmap = CreateCompatibleBitmap(hDC,
			wp.showCmd==SW_SHOWMAXIMIZED?rect.right-rect.left-8:rect.right-rect.left,
			wp.showCmd==SW_SHOWMAXIMIZED?rect.bottom-rect.top-8:rect.bottom-rect.top);
		HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemDC,hBitmap);
		BitBlt(hMemDC,0,0,
			wp.showCmd==SW_SHOWMAXIMIZED?rect.right-rect.left-4:rect.right-rect.left,
			wp.showCmd==SW_SHOWMAXIMIZED?rect.bottom-rect.top-4:rect.bottom-rect.top,
			hDC,
			wp.showCmd==SW_SHOWMAXIMIZED?4:0,
			wp.showCmd==SW_SHOWMAXIMIZED?4:0,
			SRCCOPY);
		SelectObject(hMemDC,hOldBitmap);
		if(OpenClipboard())
		{		
			EmptyClipboard();				
			SetClipboardData(CF_BITMAP,(HBITMAP)hBitmap);		
			CloseClipboard();
		}
		DeleteDC(hMemDC);
		::ReleaseDC(hRoot,hDC);
		m_cs.Unlock();

		CDialog *p_addon = pParent->getAddOn();
		if(p_addon)
		{			
			p_addon->SendMessage(WM_ACTION,0,(LPARAM)hBitmap);
		}	

		m_isDone = TRUE;
	}
	/*
	else
	{		
		HDC hDC = ::GetWindowDC(hRoot);
		HPEN hPen = CreatePen(PS_INSIDEFRAME, 1, RGB(0,0,0));
		SelectObject(hDC,GetStockObject(NULL_BRUSH));
		HPEN hOldPen = (HPEN)SelectObject(hDC,hPen);
		::Rectangle(hDC,0,0,rect.right-rect.left,rect.bottom-rect.top);
		SelectObject(hDC,hOldPen);
		::ReleaseDC(hRoot,hDC);
	}
	*/
}

