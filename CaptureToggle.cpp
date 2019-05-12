// CaptureToggle.cpp : implementation file
//

#include "stdafx.h"
#include "Wheeler2.h"
#include "CaptureToggle.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCaptureToggle dialog

CDialog* CCaptureToggle::self = NULL;

CCaptureToggle::CCaptureToggle(CWnd* pParent /*=NULL*/)
	: CDialog(CCaptureToggle::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCaptureToggle)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	this->pParent = (CWheeler2Dlg*)pParent;
	isLeftPressed = FALSE;
	isMiddleInit = TRUE;
	start.x=0;
	start.y=0;
	end.x=0;
	end.y=0;
	passed=0;
}


void CCaptureToggle::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCaptureToggle)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCaptureToggle, CDialog)
	//{{AFX_MSG_MAP(CCaptureToggle)
	ON_WM_PAINT()
	ON_WM_CLOSE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONUP()	
	ON_WM_TIMER()
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_ACTION,OnDoStart)
	ON_MESSAGE(WM_MBUTTONUP,OnMButtonUp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCaptureToggle message handlers



void CCaptureToggle::setInstance(CWheeler2Dlg *dlg)
{
	if(self==NULL)
	{
		self = new CCaptureToggle(dlg);
		self->Create(IDD_CAPTURE_TOGGLE,GetDesktopWindow());
	}
}

CDialog* CCaptureToggle::getInstance()
{
	return self;
}

LONG CCaptureToggle::OnDoStart(WPARAM wParam, LPARAM lParam)
{
	if(pParent->m_isCapture && pParent->m_capture + IDC_CAPTURE_PRESS == IDC_CAPTURE_TOGGLE && pParent->isOperate())
	{	
		isMiddleInit = TRUE;
		//pParent->SendMessage(WM_CLOSE,0,0);
		//Sleep(100);
		CClientDC dc(this);
		CWillCopy.CreateCompatibleBitmap(&dc,GetSystemMetrics(SM_CXVIRTUALSCREEN),GetSystemMetrics(SM_CYVIRTUALSCREEN));		
		CWindowDC ScreenDC(GetDesktopWindow());
		CDC MemDC;
		MemDC.CreateCompatibleDC(&dc);
		
		CBitmap* pOldBitmap = (CBitmap*)MemDC.SelectObject(&CWillCopy);
		MemDC.BitBlt(0,0,GetSystemMetrics(SM_CXVIRTUALSCREEN),GetSystemMetrics(SM_CYVIRTUALSCREEN),
			&ScreenDC,GetSystemMetrics(SM_XVIRTUALSCREEN),GetSystemMetrics(SM_YVIRTUALSCREEN),SRCCOPY);
		MemDC.SelectObject(pOldBitmap);

		SHORT state = GetKeyState(VK_MBUTTON);
		if(state&0x8000)
		{
			pParent->KillTimer(1);		
			SetWindowPos(&CWnd::wndTopMost,GetSystemMetrics(SM_XVIRTUALSCREEN),GetSystemMetrics(SM_YVIRTUALSCREEN),
			GetSystemMetrics(SM_CXVIRTUALSCREEN),GetSystemMetrics(SM_CYVIRTUALSCREEN),SWP_SHOWWINDOW);			
			SetTimer(2,50,NULL);
			ShowWindow(SW_SHOW);						
			start.x = start.y = end.x = end.y = 0;
			InvalidateRect(NULL,TRUE);
			SetFocus();
			passed = 0;
		}
	}

	return 0;
}

void CCaptureToggle::doFinish()
{
	CWillCopy.DeleteObject();
	KillTimer(0);
	pParent->SetTimer(1,50,NULL);
	ShowWindow(SW_HIDE);
	hCaptureCopy = NULL;
}

void CCaptureToggle::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(!isLeftPressed)
	{
		GetCursorPos(&start);
	}	
	isLeftPressed = TRUE;	
		
	
	CDialog::OnLButtonDown(nFlags, point);
}

void CCaptureToggle::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(isLeftPressed)
	{
		GetCursorPos(&end);
	}
	isLeftPressed = FALSE;		
	InvalidateRect(NULL,FALSE);
	
	CDialog::OnLButtonUp(nFlags, point);
}

void CCaptureToggle::OnTimer(UINT nIDEvent)
{		
	if(isLeftPressed)
	{
		GetCursorPos(&end);
		InvalidateRect(NULL,FALSE);
		isMiddleInit = FALSE;
	}
	passed++;
	if(passed>5)
	{
		isMiddleInit = FALSE;
	}
}

void CCaptureToggle::OnPaint() 
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

	if(!(start.x == 0 && start.y ==0 && end.x ==0 && end.y == 0))
	{
		CBrush *pBrush = CBrush::FromHandle((HBRUSH)GetStockObject(HOLLOW_BRUSH));
		CBrush *pOldBrush = dc.SelectObject(pBrush);
		CPen *pOldPen = dc.SelectObject(&pen);
		dc.Rectangle(start.x,start.y,end.x,end.y);
		dc.SelectObject(pOldPen);
		dc.SelectObject(pOldBrush);
	}
	
	CString toggle;
	toggle.LoadString(IDS_TOGGLE);
	//dc.SetBkMode(TRANSPARENT);
	dc.SetBkColor(RGB(255,255,255));
	dc.SetTextColor(RGB(0,0,0));
	dc.TextOut(0,0,toggle,lstrlen(toggle));

	//ScreenDC.DeleteDC();
	//MemDC.DeleteDC();
}

void CCaptureToggle::OnClose() 
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

void CCaptureToggle::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	//start.x = start.y = end.x = end.y = 0;
	//InvalidateRect(NULL,TRUE);
	doFinish();
}

LONG CCaptureToggle::OnMButtonUp(WPARAM wParam, LPARAM lParam)
{
	// TODO: Add your message handler code here and/or call default	
	if(!isMiddleInit){
		if(start.x==0 && start.y==0 && end.x==0 && end.y==0)
			doFinish();			
		else
			doCopy();
	}
	if(isMiddleInit)
	{
		isMiddleInit = FALSE;
	}	
	return 0;
}

void CCaptureToggle::doCopy()
{
	// 반드시 타이머를 죽여야 화면이 그대로 보관되서 잘 복사된다.
	KillTimer(2);
	
	RECT rect;	
	rect.left = min(start.x, end.x);
	rect.top = min(start.y, end.y);
	rect.right = max(start.x, end.x);
	rect.bottom = max(start.y, end.y);	
	
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
	
	doFinish();
}
