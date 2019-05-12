// Program.cpp : implementation file
//

#include "stdafx.h"
#include "Wheeler2.h"
#include "Program.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProgram dialog

CProgram* CProgram::self = NULL;

CProgram::CProgram(CWnd* pParent /*=NULL*/)
	: CDialog(CProgram::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProgram)	
	m_one = FALSE;
	//}}AFX_DATA_INIT
	this->pParent = (CWheeler2Dlg*)pParent;
	lstrcpy(program_name,TEXT("mspaint.exe"));
}

// 다이얼로그를 바꿀 때 delete를 호출하기 때문에 파괴자를 이용하여
// 현재 다이얼로그에 보관된 값을 부모 윈도우에게 복사한다.
// (모달리스 다이얼로그처럼 만들어서 이게 가능한 듯 함.)
CProgram::~CProgram()
{
	UpdateData();
	pParent->m_one = m_one;	
}


void CProgram::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProgram)
	DDX_Check(pDX, IDC_PROGRAM_ONE, m_one);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProgram, CDialog)
	//{{AFX_MSG_MAP(CProgram)
	ON_BN_CLICKED(IDC_PROGRAM_SEL, OnProgramSel)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_ACTION, OnDoAction)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProgram message handlers

// 다이얼로그를 초기화할 때 부모 윈도우에게서 관련 값을 가져온다.
BOOL CProgram::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_one = pParent->m_one;
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CProgram::setInstance(CWheeler2Dlg *dlg)
{
	if(self==NULL)
	{
		self = new CProgram(dlg);
		self->Create(IDD_PROGRAM,dlg);
		self->MoveWindow(25,190,130,60);
	}	
}

CProgram* CProgram::getInstance()
{	
	return self;
}

LONG CProgram::OnDoAction(WPARAM wParam, LPARAM lParam)
{
	UpdateData();

	static HWND hProgram = NULL;
	STARTUPINFO si = { 0 };
	static PROCESS_INFORMATION pi = { 0 };
	TCHAR module_name[MAX_PATH] = { 0 };
	WINDOWPLACEMENT wp;
	
	BOOL ret = TRUE;
	RECT rect;
	int i=0;

	if(m_one)
	{
		ret = IsWindow(hProgram);
		if(ret==FALSE)
			hProgram = NULL;
	}
	else
		hProgram = NULL;
	if(hProgram==NULL)
		ret = CreateProcess(NULL,program_name,NULL,NULL,FALSE,0,NULL,NULL,&si,&pi);

	if(ret==TRUE)
	{
		WaitForInputIdle(pi.hProcess, INFINITE);		
		
		do 
		{
			hProgram = GetHandleFromPID(pi.dwProcessId);
			i++;
			Sleep(10);
		} while (i<100 && hProgram==NULL);

		AttachThreadInput(pi.dwThreadId,GetCurrentThreadId(),TRUE);

		::GetWindowPlacement(hProgram,&wp);
		::SendMessage(hProgram,WM_SYSCOMMAND,wp.showCmd==SW_MAXIMIZE?SC_MAXIMIZE:SC_RESTORE,0);

		::SetActiveWindow(hProgram);
		::SetFocus(hProgram);		
		
		::GetWindowRect(hProgram,&rect);
		::SetWindowPos(hProgram,HWND_TOPMOST,rect.left,rect.top,rect.right-rect.left,rect.bottom-rect.top,SWP_SHOWWINDOW);		
		
		SetCursorPos((rect.right+rect.left)>>1, rect.top+10);		
		press(LEFTMOUSE,(rect.right+rect.left)>>1, rect.top+10);		
		Sleep(100);
		mouse_event(MOUSEEVENTF_LEFTUP,0,0,NULL,NULL);

		shortcut(VK_CONTROL,(BYTE)VkKeyScan('v'),0x2f);
		AttachThreadInput(pi.dwThreadId,GetCurrentThreadId(),FALSE);
		::SetWindowPos(hProgram,HWND_NOTOPMOST,rect.left,rect.top,rect.right-rect.left,rect.bottom-rect.top,SWP_SHOWWINDOW);
	}

	UpdateData(FALSE);
	return 0;
}

HWND CProgram::GetHandleFromPID(DWORD pid)
{
	HWND hWnd = ::GetDesktopWindow();
	HWND hTmpWnd = NULL;  
	BOOL bFoundWnd = FALSE;  
	DWORD dwPID;  
	
	while ( hWnd != NULL && !bFoundWnd )  
	{  
		hTmpWnd = hWnd;  
		hWnd = ::GetWindow( hWnd, GW_CHILD );  
		if ( hWnd )  
		{  
			GetWindowThreadProcessId( hWnd, &dwPID );  
			
			if ( dwPID == pid )  
				if ( IsWindow( hWnd ) &&   
					::IsWindowVisible( hWnd ) )  
					bFoundWnd = TRUE;  
		}  
		else  
		{  
			hWnd = hTmpWnd;  
			hWnd = ::GetWindow( hWnd, GW_HWNDNEXT );  
			
			if ( hWnd )  
			{  
				GetWindowThreadProcessId( hWnd, &dwPID );  
				
				if ( dwPID == pid )  
					if ( IsWindow( hWnd ) &&   
						::IsWindowVisible( hWnd ) )  
						bFoundWnd = TRUE;  
			}  
			else  
			{  
				hWnd = hTmpWnd;  
				hWnd = ::GetParent( hWnd );  
				if ( hWnd )  
				{  
					BOOL bFoundBranch = FALSE;  
					
					while ( !bFoundBranch && !bFoundWnd && hWnd )  
					{  
						hTmpWnd = hWnd;  
						hWnd = ::GetWindow( hWnd, GW_HWNDNEXT );  
						if ( hWnd )  
						{  
							bFoundBranch = TRUE;  
							
							GetWindowThreadProcessId( hWnd, &dwPID );  
							if ( dwPID == pid )  
								if ( IsWindow( hWnd ) &&   
									::IsWindowVisible( hWnd ) )  
									bFoundWnd = TRUE;  
						}  
						else  
						{  
							hWnd = hTmpWnd;  
							hWnd = ::GetParent( hWnd );  
						}  
					}  
				}  
			}  
		}  
	}  
	return hWnd;  
}

#include "ProcessDlg.h"
void CProgram::OnProgramSel() 
{
	// TODO: Add your control notification handler code here
	CProcessDlg dlg(this);
	dlg.DoModal();
}

TCHAR* CProgram::getProgramName()
{
	return program_name;
}
void CProgram::setProgramName(TCHAR* str)
{
	lstrcpy(program_name,str);
}

