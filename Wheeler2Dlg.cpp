// Wheeler2Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "Wheeler2.h"
#include "Wheeler2Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)		
		// No message handlers
	//}}AFX_MSG_MAP	
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWheeler2Dlg dialog

CWheeler2Dlg::CWheeler2Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWheeler2Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWheeler2Dlg)
	m_title = -1;
	m_capture = -1;
	m_isCapture = FALSE;
	m_addon = -1;
	m_close = FALSE;
	m_clock = FALSE;
	m_icon = FALSE;
	m_tray = FALSE;
	m_exp = FALSE;
	m_dialog = FALSE;	
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32

	m_one = FALSE;
	m_file = -1;
	
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_hMenu = LoadMenu(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDR_MENU));
	p_addon = NULL;
	p_capture = NULL;
	p_ExMouseGest = NULL;
	p_FileMouseGest = NULL;
}

void CWheeler2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWheeler2Dlg)
	DDX_Radio(pDX, IDC_TITLE_NONE, m_title);
	DDX_Radio(pDX, IDC_CAPTURE_PRESS, m_capture);
	DDX_Check(pDX, IDC_ISCAPTURE, m_isCapture);
	DDX_Radio(pDX, IDC_ADDON_NONE, m_addon);
	DDX_Check(pDX, IDC_CLOSE, m_close);
	DDX_Check(pDX, IDC_DOUBLE_CLOCK, m_clock);
	DDX_Check(pDX, IDC_DOUBLE_ICON, m_icon);
	DDX_Check(pDX, IDC_DOUBLE_TRAY, m_tray);
	DDX_Check(pDX, IDC_MOUSE_EXP, m_exp);
	DDX_Check(pDX, IDC_MOUSE_DIALOG, m_dialog);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWheeler2Dlg, CDialog)
	//{{AFX_MSG_MAP(CWheeler2Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ISCAPTURE, OnIscapture)
	ON_WM_CLOSE()
	ON_WM_DESTROY()		
	ON_WM_TIMER()	
	ON_BN_CLICKED(IDC_MOUSE_DIALOG, OnMouseDialog)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_MOUSE_EXP, OnMouseExp)
	ON_BN_CLICKED(IDC_ADDON_NONE, OnAddon)	
	ON_BN_CLICKED(IDC_ADDON_PROGRAM, OnAddon)
	ON_BN_CLICKED(IDC_ADDON_FILE, OnAddon)
	//ON_CONTROL_RANGE(BN_CLICKED,IDC_ADDON_NONE,IDC_ADDON_FILE,OnAddon)
	ON_BN_CLICKED(IDC_CAPTURE_PRESS, OnSelectCapture)
	ON_BN_CLICKED(IDC_CAPTURE_TOGGLE, OnSelectCapture)
	ON_BN_CLICKED(IDC_CAPTURE_WINDOW, OnSelectCapture)
	//ON_CONTROL_RANGE(BN_CLICKED,IDC_CAPTURE_PRESS,IDC_CAPTURE_TOGGLE,OnSelectCapture)
	ON_MESSAGE(WM_APP+1, OnApp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWheeler2Dlg message handlers

#include "Register.h"
#include "FileDlg1.h"
#include "Program.h"
#include "CapturePress.h"
#include "CaptureToggle.h"
#include "CaptureWindow.h"
#include "ExMouseGest.h"
#include "FileMouseGest.h"
#define KEY		TEXT("Software\\sdr1982\\Wheeler")
BOOL CWheeler2Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	CRegister Setting(KEY);
	m_title = Setting.ReadInt(TEXT("Setting"), TEXT("title"), 0);
	m_capture = Setting.ReadInt(TEXT("Setting"), TEXT("capture"), 0);
	m_addon = Setting.ReadInt(TEXT("Setting"), TEXT("addon"), 0);
	m_clock = Setting.ReadInt(TEXT("Setting"), TEXT("clock"), FALSE);
	m_close = Setting.ReadInt(TEXT("Setting"), TEXT("close"), FALSE);
	m_dialog = Setting.ReadInt(TEXT("Setting"), TEXT("dialog"), FALSE);
	m_exp = Setting.ReadInt(TEXT("Setting"), TEXT("exp"), FALSE);
	m_file = Setting.ReadInt(TEXT("Setting"), TEXT("file"), 0);
	m_icon = Setting.ReadInt(TEXT("Setting"), TEXT("icon"), FALSE);
	m_isCapture = Setting.ReadInt(TEXT("Setting"), TEXT("isCapture"), FALSE);
	m_one = Setting.ReadInt(TEXT("Setting"), TEXT("one"), FALSE);
	m_title = Setting.ReadInt(TEXT("Setting"), TEXT("title"), FALSE);
	m_tray = Setting.ReadInt(TEXT("Setting"), TEXT("tray"), FALSE);
	UpdateData(FALSE);

	CProgram::setInstance(this);
	CFileDlg::setInstance(this);

	CCapturePress::setInstance(this);
	CCaptureToggle::setInstance(this);
	CCaptureWindow::setInstance(this);

	CExMouseGest::setInstance(this);
	CFileMouseGest::setInstance(this);

	m_isDone = m_isPressed = FALSE;
	OnAddon();
	OnIscapture();	
	OnMouseExp();
	OnMouseDialog();
	SetTimer(1,50,NULL);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CWheeler2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CWheeler2Dlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CWheeler2Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CWheeler2Dlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	NOTIFYICONDATA nid;

	nid.cbSize = sizeof(nid);
	nid.hWnd = m_hWnd;
	nid.uID = IDR_MAINFRAME;
	nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
	nid.uCallbackMessage = WM_APP+1;
	nid.hIcon = m_hIcon;
	lstrcpy(nid.szTip, TEXT("Wheeler"));
	
	Shell_NotifyIcon(NIM_ADD, &nid);
	ShowWindow(SW_HIDE);
	
	//CDialog::OnClose();
}

LONG CWheeler2Dlg::OnApp(WPARAM wParam,LPARAM lParam)
{
	NOTIFYICONDATA nid;	
	POINT pt;	
	HMENU hMenu;

	switch(LOWORD(lParam))
	{
	case WM_LBUTTONDBLCLK:
		nid.cbSize = sizeof(nid);
		nid.hWnd = m_hWnd;
		nid.uID = IDR_MAINFRAME;
		nid.uFlags = NIF_ICON | NIF_TIP;
		nid.hIcon = m_hIcon;

		Shell_NotifyIcon(NIM_DELETE,&nid);		
		ShowWindow(SW_SHOW);
		break;
	case WM_RBUTTONUP:
	case WM_CONTEXTMENU:
		GetCursorPos(&pt);		
		hMenu = GetSubMenu(m_hMenu,0);
		SetForegroundWindow();	// 이게 있어야 ESC 눌렀을 때 컨텍스트 메뉴가 없어진다.
		TrackPopupMenu(hMenu,TPM_RIGHTALIGN,pt.x,pt.y,NULL,m_hWnd,NULL);
		break;
	}
	
	return 0;
}

void CWheeler2Dlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	NOTIFYICONDATA nid;
	nid.cbSize = sizeof(nid);
	nid.hWnd = m_hWnd;
	nid.uID = IDR_MAINFRAME;
	nid.uFlags = NIF_ICON | NIF_TIP;
	nid.hIcon = m_hIcon;
	Shell_NotifyIcon(NIM_DELETE,&nid);

	DeleteObject(m_hMenu);
	delete CProgram::getInstance();
	delete CFileDlg::getInstance();

	delete CCapturePress::getInstance();
	delete CCaptureToggle::getInstance();
	delete CCaptureWindow::getInstance();

	delete CExMouseGest::getInstance();
	delete CFileMouseGest::getInstance();

	CRegister Setting(KEY);
	Setting.WriteInt(TEXT("Setting"), TEXT("title"), m_title);
	Setting.WriteInt(TEXT("Setting"), TEXT("capture"), m_capture);
	Setting.WriteInt(TEXT("Setting"), TEXT("addon"), m_addon);
	Setting.WriteInt(TEXT("Setting"), TEXT("clock"), m_clock);
	Setting.WriteInt(TEXT("Setting"), TEXT("close"), m_close);
	Setting.WriteInt(TEXT("Setting"), TEXT("dialog"), m_dialog);
	Setting.WriteInt(TEXT("Setting"), TEXT("exp"), m_exp);
	Setting.WriteInt(TEXT("Setting"), TEXT("file"), m_file);
	Setting.WriteInt(TEXT("Setting"), TEXT("icon"), m_icon);
	Setting.WriteInt(TEXT("Setting"), TEXT("isCapture"), m_isCapture);
	Setting.WriteInt(TEXT("Setting"), TEXT("one"), m_one);
	Setting.WriteInt(TEXT("Setting"), TEXT("title"), m_title);
	Setting.WriteInt(TEXT("Setting"), TEXT("tray"), m_tray);
}

// void CWheeler2Dlg::OnIscapture() 
// 캡쳐하기 체크박스를 눌렀을 때 실행하는 함수...
// 기능 : 캡쳐하기가 가능하면 캡쳐관련 컨트롤을 활성화 그렇지 않으면 비활성화 한다.
void CWheeler2Dlg::OnIscapture() 
{
	// TODO: Add your control notification handler code here
	CButton *pPress,*pToggle, *pWindow;
	CButton *pNone, *pProgram, *pFile;

	pPress = (CButton*)GetDlgItem(IDC_CAPTURE_PRESS);
	pToggle = (CButton*)GetDlgItem(IDC_CAPTURE_TOGGLE);
	pWindow = (CButton*)GetDlgItem(IDC_CAPTURE_WINDOW);

	pNone = (CButton*)GetDlgItem(IDC_ADDON_NONE);
	pProgram = (CButton*)GetDlgItem(IDC_ADDON_PROGRAM);
	pFile = (CButton*)GetDlgItem(IDC_ADDON_FILE);

	UpdateData();
	// 캡쳐 관련 버튼 활성화 혹은 비활성화
	pPress->EnableWindow(m_isCapture);
	pToggle->EnableWindow(m_isCapture);
	pWindow->EnableWindow(m_isCapture);
	pNone->EnableWindow(m_isCapture);
	pProgram->EnableWindow(m_isCapture);
	pFile->EnableWindow(m_isCapture);

	if(!m_isCapture)
	{		
		// addon 관련 다이얼로그바를 숨김.
		CFileDlg::getInstance()->ShowWindow(SW_HIDE);
		CProgram::getInstance()->ShowWindow(SW_HIDE);
		// 캡쳐모드 처리
		p_capture = NULL;
	}
	else
	{
		// 캡쳐모드 처리
		OnSelectCapture();
		OnAddon();
	}

	UpdateData(FALSE);	
}

void CWheeler2Dlg::OnAddon()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	
	CFileDlg::getInstance()->ShowWindow(SW_HIDE);
	CProgram::getInstance()->ShowWindow(SW_HIDE);

	switch(m_addon + IDC_ADDON_NONE)
	{
		case IDC_ADDON_PROGRAM:		// IDC_ADDON_PROGRAM
			p_addon = CProgram::getInstance();			
			break;
		case IDC_ADDON_FILE:		// IDC_ADDON_FILE
			p_addon = CFileDlg::getInstance();						
			break;
		default:
			p_addon = NULL;
			break;
	}

	if(p_addon)		
		p_addon->ShowWindow(SW_SHOW);
	
	
	UpdateData(FALSE);
}

#include "DoubleClick.h"
#include "TitleBar.h"
#include "TaskBar.h"
void CWheeler2Dlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default	
	CDoubleClick dbclk(this);
	CTitleBar titlebar(this);
	CTaskBar taskbar(this);
	SHORT state;
	state = GetKeyState(VK_MBUTTON);
	if(state&0x8000)
	{
		m_isPressed = TRUE;
	}
	else
	{
		m_isPressed = FALSE;
		m_isDone = FALSE;
	}

	taskbar.doAction();
	dbclk.doAction();
	titlebar.doAction();
	if(p_ExMouseGest)	p_ExMouseGest->doAction();
	if(p_FileMouseGest)	p_FileMouseGest->doAction();

	if(p_capture)	p_capture->SendMessage(WM_ACTION,0,0);
	
	CDialog::OnTimer(nIDEvent);
}

void CWheeler2Dlg::setIsDone()
{
	m_isDone = TRUE;
}

BOOL CWheeler2Dlg::isOperate() const
{
	BOOL ret = FALSE;
	if(m_isPressed && !m_isDone)
		ret = TRUE;
	return ret;
}

#include "CapturePress.h"
#include "CaptureToggle.h"
void CWheeler2Dlg::OnSelectCapture() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	if(m_isCapture)
	{
		switch(m_capture+IDC_CAPTURE_PRESS)
		{
			case IDC_CAPTURE_PRESS:
				p_capture = CCapturePress::getInstance();
				break;
			case IDC_CAPTURE_TOGGLE:
				p_capture = CCaptureToggle::getInstance();
				break;
			case IDC_CAPTURE_WINDOW:
				p_capture = CCaptureWindow::getInstance();
				break;
			default:
				p_capture = NULL;
				break;
		}
	}
	UpdateData(FALSE);
}

CDialog* CWheeler2Dlg::getAddOn()
{
	return p_addon;
}

// ESC 및 엔터키를 누를 때 종료를 막는 코드
// http://minimonk.tistory.com/561
BOOL CWheeler2Dlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->wParam==VK_RETURN || pMsg->wParam==VK_ESCAPE)
		return TRUE;
	
	return CDialog::PreTranslateMessage(pMsg);
}

void CWheeler2Dlg::OnMouseExp() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	p_ExMouseGest = m_exp?CExMouseGest::getInstance():NULL;
}

void CWheeler2Dlg::OnMouseDialog()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	p_FileMouseGest = m_dialog?CFileMouseGest::getInstance():NULL;
}
