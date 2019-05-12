// ProcessDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Wheeler2.h"
#include "ProcessDlg.h"
#include ".\processdlg.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProcessDlg dialog


CProcessDlg::CProcessDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProcessDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProcessDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	this->pParent = (CProgram*)pParent;
}


void CProcessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProcessDlg)
	DDX_Control(pDX, IDC_LIST1, m_ProcessList);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_EDIT1, m_ProgramName);
}


BEGIN_MESSAGE_MAP(CProcessDlg, CDialog)
	//{{AFX_MSG_MAP(CProcessDlg)
	//}}AFX_MSG_MAP
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnNMDblclkList1)
	ON_BN_CLICKED(IDC_FIND, OnBnClickedFind)
//	ON_NOTIFY(NM_CLICK, IDC_LIST1, OnNMClickList1)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, OnLvnItemchangedList1)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProcessDlg message handlers

BOOL CProcessDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	nIndex = 0;
	m_iconSmall.Create( 16 , 16, ILC_COLOR24, 1, 256 );
	m_ProcessList.SetImageList( &m_iconSmall, LVSIL_SMALL );
	
	TCHAR str[256];
	lstrcpy(str,pParent->getProgramName());
	TCHAR* lastpath = str + lstrlen(str);
	while(*lastpath-- != '\\' && lastpath!=str);
	lstrcpy(str,lastpath+2);

	m_ProgramName.SetWindowText(str);
	EnumWindows(EnumWindowCallBack,(LPARAM)this);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

// 참고주소
// http://crynut84.tistory.com/49 : 제일 괜찮은 참고자료
// http://enswathe.tistory.com/17
// 윈도우 스타일
// http://blondie.dowling.edu/plugins/scmcvs/cvsweb.php/external_packages/nsis-2.21-src/Contrib/System/System.nsh?rev=1.1.1.1;cvsroot=rasmol;f=s
// http://tipssoft.com/bulletin/board.php?bo_table=FAQ&wr_id=231

BOOL CProcessDlg::EnumWindowCallBack(HWND hWnd, LPARAM lParam)
{
	CProcessDlg *dlg = (CProcessDlg*)lParam;
	LONG style = GetWindowLong(hWnd,GCL_HMODULE);
	TCHAR process_name[256];
	// 해당 윈도우의 캡션이 존재하는 지 확인
	if((style&WS_VISIBLE)==WS_VISIBLE && (style&WS_CAPTION)==WS_CAPTION)
	{
		// 부모가 바탕화면인지 확인
		if(::GetParent(hWnd)==NULL)
		{
			CWinApp *pApp = (CWinApp*)AfxGetApp();
			CWnd *pWnd = pApp->GetMainWnd();
			if(hWnd==pWnd->GetSafeHwnd())
				return TRUE;
			
			DWORD pid = 0;
			::GetWindowThreadProcessId(hWnd,&pid);
			
			HANDLE handle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);
			if(handle !=NULL)
			{
				::GetModuleFileNameEx(handle,NULL,process_name,256);				
				TCHAR* lastpath = process_name + lstrlen(process_name);
				while(*lastpath-- != '\\');
				lstrcpy(process_name,lastpath+2);
			}
			CloseHandle(handle);			

			int nIndex = dlg->nIndex++;			
			HICON hIcon = (HICON)GetClassLong(hWnd,GCL_HICON);
			dlg->m_iconSmall.Add(hIcon);
			LVITEM item;
			memset(&item,0,sizeof(item));
			item.mask = LVIF_IMAGE|LVIF_PARAM|LVIF_TEXT;
			item.iItem = nIndex;			
			item.pszText = process_name;
			item.cchTextMax = 256;
			item.lParam = (LPARAM)hWnd;
			item.iImage = nIndex;
			
			for(int i=0;i<dlg->m_ProcessList.GetItemCount();i++)
			{
				CString str = dlg->m_ProcessList.GetItemText(i,0);				
				if(lstrcmp(str,process_name)==0)
				{					
					return TRUE;
				}
			}			

			dlg->m_ProcessList.InsertItem(&item);
		}
	}
	return TRUE;
}

void CProcessDlg::OnOK() 
{
	// TODO: Add extra validation here
	POSITION pos = m_ProcessList.GetFirstSelectedItemPosition();
	int nItem;
	if(pos)
		nItem = m_ProcessList.GetNextSelectedItem(pos);
	else
	{
		CDialog::OnOK();
		return;
	}
	HWND hWnd = (HWND)m_ProcessList.GetItemData(nItem);

	TCHAR process_name[256];
	DWORD pid = 0;
	::GetWindowThreadProcessId(hWnd,&pid);
	
	HANDLE handle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);
	if(handle !=NULL)
	{
		::GetModuleFileNameEx(handle,NULL,process_name,256);				
	}
	CloseHandle(handle);
	//lstrcpy(pParent->getProgramName(),process_name);
	pParent->setProgramName(process_name);

	CDialog::OnOK();
}

void CProcessDlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnOK();
	*pResult = 0;
}

void CProcessDlg::OnBnClickedFind()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	TCHAR str[MAX_PATH];
	CString szFilter;
	szFilter.LoadString(IDS_SZFILTER);
	
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY,szFilter);
	if(dlg.DoModal()==IDOK)
	{
		lstrcpy(str,dlg.GetPathName());
		pParent->setProgramName(str);
		TCHAR* lastpath = str + lstrlen(str);
		while(*lastpath-- != '\\' && lastpath!=str);
		lstrcpy(str,lastpath+2);
		m_ProgramName.SetWindowText(str);
	}
}

void CProcessDlg::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	POSITION pos = m_ProcessList.GetFirstSelectedItemPosition();
	int nItem;
	if(pos)
		nItem = m_ProcessList.GetNextSelectedItem(pos);
	else
	{
		*pResult = 0;
		return;
	}
	
	CString str = m_ProcessList.GetItemText(nItem,0);
	m_ProgramName.SetWindowText(str);

	*pResult = 0;
}
