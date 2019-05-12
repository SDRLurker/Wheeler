// CapturePress.cpp : implementation file
//

#include "stdafx.h"
#include "Wheeler2.h"
#include "CapturePress.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCapturePress dialog

CDialog* CCapturePress::self = NULL;

CCapturePress::CCapturePress(CWnd* pParent /*=NULL*/)
	: CDialog(CCapturePress::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCapturePress)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	this->pParent = (CWheeler2Dlg*)pParent;	
}


void CCapturePress::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCapturePress)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCapturePress, CDialog)
	//{{AFX_MSG_MAP(CCapturePress)
	ON_WM_TIMER()
	ON_WM_PAINT()
	ON_WM_CLOSE()
	ON_WM_RBUTTONUP()
	//}}AFX_MSG_MAP
	
	ON_MESSAGE(WM_ACTION, OnDoStart)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCapturePress message handlers

void CCapturePress::setInstance(CWheeler2Dlg *dlg)
{
	if(self==NULL)
	{
		self = new CCapturePress(dlg);
		self->Create(IDD_CAPTURE_PRESS,GetDesktopWindow());		
	}
}

CDialog* CCapturePress::getInstance()
{
	return self;
}

void CCapturePress::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	SHORT state = GetKeyState(VK_MBUTTON);
	SHORT rstate = GetKeyState(VK_RBUTTON);
	SHORT escstate = GetKeyState(VK_ESCAPE);

	if(rstate&0x8000 || escstate&0x8000)
	{		
		doFinish();
		CDialog::OnTimer(nIDEvent);
		return;
	}

	if(state&0x8000)
	{
		GetCursorPos(&end);
		InvalidateRect(NULL,FALSE);
	}
	else
	{
		doCopy();
	}

	
	CDialog::OnTimer(nIDEvent);
}

LONG CCapturePress::OnDoStart(WPARAM wParam,LPARAM lParam)
{	
	if(pParent->m_isCapture && pParent->m_capture + IDC_CAPTURE_PRESS == IDC_CAPTURE_PRESS && pParent->isOperate())
	{		
		GetCursorPos(&start);
		
		CClientDC dc(this);
		CWillCopy.CreateCompatibleBitmap(&dc,GetSystemMetrics(SM_CXVIRTUALSCREEN),GetSystemMetrics(SM_CYVIRTUALSCREEN));		
		CWindowDC ScreenDC(GetDesktopWindow());
		CDC MemDC;
		MemDC.CreateCompatibleDC(&dc);
		
		CBitmap* pOldBitmap = (CBitmap*)MemDC.SelectObject(&CWillCopy);
		MemDC.BitBlt(0,0,GetSystemMetrics(SM_CXVIRTUALSCREEN),GetSystemMetrics(SM_CYVIRTUALSCREEN),
			&ScreenDC,GetSystemMetrics(SM_XVIRTUALSCREEN),GetSystemMetrics(SM_YVIRTUALSCREEN),SRCCOPY);
		MemDC.SelectObject(pOldBitmap);

		//ScreenDC.DeleteDC();
		//MemDC.DeleteDC();

		Sleep(200);
		SetCursorPos(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
		press(LEFTMOUSE, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));		
		SetCursorPos(start.x,start.y);
		Sleep(50);

		SHORT state = GetKeyState(VK_MBUTTON);
		if(state&0x8000)
		{
			pParent->KillTimer(1);		
			SetWindowPos(&CWnd::wndTopMost,GetSystemMetrics(SM_XVIRTUALSCREEN),GetSystemMetrics(SM_YVIRTUALSCREEN),
			GetSystemMetrics(SM_CXVIRTUALSCREEN),GetSystemMetrics(SM_CYVIRTUALSCREEN),SWP_SHOWWINDOW);
			SetTimer(2,50,NULL);
			ShowWindow(SW_SHOW);
			SetFocus();
		}
		else
		{			
			doFinish();
		}
		
		/*
		HDC hDC = ::GetDC(m_hWnd);
		hWillCopy = ::CreateCompatibleBitmap(hDC,GetSystemMetrics(SM_CXVIRTUALSCREEN),GetSystemMetrics(SM_CYVIRTUALSCREEN));
		HDC hScreenDC = CreateDC(TEXT("DISPLAY"), NULL, NULL, NULL);
		HDC hMemDC = CreateCompatibleDC(hDC);

		HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemDC,hWillCopy);
		BitBlt(hMemDC,0,0,GetSystemMetrics(SM_CXVIRTUALSCREEN),GetSystemMetrics(SM_CYVIRTUALSCREEN),
			hScreenDC,GetSystemMetrics(SM_XVIRTUALSCREEN),GetSystemMetrics(SM_YVIRTUALSCREEN),SRCCOPY);
		SelectObject(hMemDC,hOldBitmap);

		DeleteDC(hScreenDC);
		DeleteDC(hMemDC);
		::ReleaseDC(m_hWnd,hDC);

		Sleep(200);
		SetCursorPos(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
		press(LEFTMOUSE, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));		
		SetCursorPos(start.x,start.y);
		Sleep(50);

		SHORT state = GetKeyState(VK_MBUTTON);
		if(state&0x8000)
		{
			pParent->KillTimer(1);			
			//SetWindowPos(&CWnd::wndTopMost,GetSystemMetrics(SM_XVIRTUALSCREEN),GetSystemMetrics(SM_YVIRTUALSCREEN),
			//GetSystemMetrics(SM_CXVIRTUALSCREEN),GetSystemMetrics(SM_CYVIRTUALSCREEN),SWP_SHOWWINDOW);			
			SetTimer(2,50,NULL);
			ShowWindow(SW_SHOW);
			SetFocus();
		}
		else
		{
			DeleteObject(hWillCopy);
			doFinish();
		}
		*/
	}
	return 0;
}

void CCapturePress::doFinish()
{
	CWillCopy.DeleteObject();
	KillTimer(2);
	pParent->SetTimer(1,50,NULL);
	ShowWindow(SW_HIDE);
}

void CCapturePress::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	// Do not call CDialog::OnPaint() for painting messages
	CDC MemDC;
	MemDC.CreateCompatibleDC(&dc);
	CWindowDC ScreenDC(GetDesktopWindow());	
	CPen pen(PS_SOLID,1,RGB(0,255,0));
	CBitmap *pOldBitmap = MemDC.SelectObject(&CWillCopy);
	dc.BitBlt(GetSystemMetrics(SM_XVIRTUALSCREEN),GetSystemMetrics(SM_YVIRTUALSCREEN),
				GetSystemMetrics(SM_CXVIRTUALSCREEN),GetSystemMetrics(SM_CYVIRTUALSCREEN),&MemDC,0,0,SRCCOPY);
	MemDC.SelectObject(pOldBitmap);

	CBrush *pBrush = CBrush::FromHandle((HBRUSH)GetStockObject(HOLLOW_BRUSH));
	CBrush *pOldBrush = dc.SelectObject(pBrush);
	CPen *pOldPen = dc.SelectObject(&pen);
	dc.Rectangle(start.x,start.y,end.x,end.y);
	dc.SelectObject(pOldPen);
	dc.SelectObject(pOldBrush);


	//ScreenDC.DeleteDC();
	//MemDC.DeleteDC();
}



void CCapturePress::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	CWheeler2Dlg *p_dlgTemp = pParent;
	doFinish();
	delete getInstance();
	self = NULL;
	setInstance(p_dlgTemp);

	//AfxMessageBox("CCapturePress::OnClose()");
	
	CDialog::OnClose();
}

void CCapturePress::doCopy()
{
	// 반드시 타이머를 죽여야 화면이 그대로 보관되서 잘 복사된다.
	KillTimer(2);

	RECT rect;
	GetCursorPos(&end);

	rect.left = min(start.x, end.x);
	rect.top = min(start.y, end.y);
	rect.right = max(start.x, end.x);
	rect.bottom = max(start.y, end.y);

	
	if(rect.right-rect.left>10 && rect.bottom-rect.top>10)
	{		
		CClientDC dc(this);
		
		CDC MemDC,Mem1DC;
		MemDC.CreateCompatibleDC(&dc);
		Mem1DC.CreateCompatibleDC(&dc);
		
		CBitmap CCaptureCopy;
		CCaptureCopy.CreateCompatibleBitmap(&dc,rect.right-rect.left,rect.bottom-rect.top);	
		CBitmap *pOldBitmap = (CBitmap*)MemDC.SelectObject(&CWillCopy);
		CBitmap *pOldBitmap2 = (CBitmap*)Mem1DC.SelectObject(&CCaptureCopy);
		Mem1DC.BitBlt(0,0,rect.right-rect.left,rect.bottom-rect.top,&MemDC,
			rect.left,
			rect.top,SRCCOPY);
		//dc.BitBlt(0,0,rect.right-rect.left,rect.bottom-rect.top,&Mem1DC,0,0,SRCCOPY);
		
		hCaptureCopy = (HBITMAP)CCaptureCopy;
		if(OpenClipboard())
		{		
			EmptyClipboard();				
			SetClipboardData(CF_BITMAP,(HBITMAP)hCaptureCopy);		
			CloseClipboard();
		}
		Mem1DC.SelectObject(pOldBitmap2);
		MemDC.SelectObject(pOldBitmap);	
		
		// 중간과정 더 추가~
		CDialog *p_addon = pParent->getAddOn();
		if(p_addon)
		{
			p_addon->SendMessage(WM_ACTION,0,(LPARAM)hCaptureCopy);
		}
	}
	
	doFinish();
}

