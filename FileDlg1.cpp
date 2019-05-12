// FileDlg1.cpp : implementation file
//

#include "stdafx.h"
#include "Wheeler2.h"
#include "FileDlg1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileDlg dialog

CFileDlg* CFileDlg::self = NULL;

CFileDlg::CFileDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFileDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFileDlg)
	m_file = -1;
	//}}AFX_DATA_INIT
	this->pParent = (CWheeler2Dlg*)pParent;
}

// ���̾�α׸� �ٲ� �� delete�� ȣ���ϱ� ������ �ı��ڸ� �̿��Ͽ�
// ���� ���̾�α׿� ������ ���� �θ� �����쿡�� �����Ѵ�.
// (��޸��� ���̾�α�ó�� ���� �̰� ������ �� ��.)
CFileDlg::~CFileDlg()
{
	UpdateData();
	pParent->m_file = m_file;
}

void CFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFileDlg)
	DDX_Radio(pDX, IDC_FILE_JPEG, m_file);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFileDlg, CDialog)
	//{{AFX_MSG_MAP(CFileDlg)
	ON_BN_CLICKED(IDC_FILE_FOLDER, OnFileFolder)
	ON_BN_CLICKED(IDC_FILE_JPEG, OnFileJpeg)
	ON_BN_CLICKED(IDC_FILE_PNG, OnFilePng)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_ACTION,OnDoAction)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileDlg message handlers

// ���̾�α׸� �ʱ�ȭ�� �� �θ� �����쿡�Լ� ���� ���� �����´�.
BOOL CFileDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_file = pParent->m_file;
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFileDlg::setInstance(CWheeler2Dlg *dlg)
{
	if(self==NULL)
	{
		self = new CFileDlg(dlg);
		self->Create(IDD_FILE,dlg);
		self->MoveWindow(25,190,130,60);
	}
}

CFileDlg* CFileDlg::getInstance()
{
	return self;
}

LONG CFileDlg::OnDoAction(WPARAM wParam,LPARAM lParam)
{
	CxImage willsave;
	HBITMAP hCaptureCopy = (HBITMAP)lParam;
	unsigned int filename = 0;
	TCHAR filepath[MAX_PATH];
	FILE *fp = NULL;

	willsave.CreateFromHBITMAP(hCaptureCopy);
	if(m_file + IDC_FILE_JPEG == IDC_FILE_JPEG)
		willsave.SetJpegQuality(99);
	do
	{
		filename++;
		wsprintf(filepath,TEXT("%s\\%d.%s"),save_dir,filename,m_file + IDC_FILE_JPEG == IDC_FILE_JPEG?TEXT("jpg"):TEXT("png"));	// ���� Ȯ��
		fp = _tfopen(filepath,TEXT("r"));		
		if(fp)	fclose(fp);
	}while(fp!=NULL);
	willsave.Save(filepath, m_file + IDC_FILE_JPEG == IDC_FILE_JPEG?CXIMAGE_FORMAT_JPG:CXIMAGE_FORMAT_PNG);
	return 0;
}

void CFileDlg::OnFileFolder() 
{
	// TODO: Add your control notification handler code here
	GetCurrentDirectory(MAX_PATH,save_dir);
	BrowseFolder(m_hWnd, TEXT("ĸ�ĵ� ������ ������ ������ �����ϼ���."),
				save_dir, save_dir);
}

BOOL CFileDlg::BrowseFolder(HWND hParent, LPCTSTR szTitle, LPCTSTR StartPath, TCHAR *szFolder)
{
	LPMALLOC pMalloc;
	LPITEMIDLIST pidl;
	BROWSEINFO bi;

	bi.hwndOwner = hParent;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = NULL;
	bi.lpszTitle = szTitle;
	bi.ulFlags = 0;
	bi.lpfn = BrowseCallbackProc;
	bi.lParam = (LPARAM)StartPath;

	pidl = SHBrowseForFolder(&bi);

	if(pidl==NULL)
		return FALSE;

	SHGetPathFromIDList(pidl, szFolder);

	if(SHGetMalloc(&pMalloc)!=NOERROR)
		return FALSE;

	pMalloc->Free(pidl);
	pMalloc->Release();
	
	return FALSE;
}

int CALLBACK CFileDlg::BrowseCallbackProc(HWND hWnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{
	switch(uMsg)
	{
	case BFFM_INITIALIZED:
		if(lpData!=NULL)
			::SendMessage(hWnd, BFFM_SETSELECTION, TRUE, (LPARAM)lpData);
	}
	return 0;
}

void CFileDlg::OnFileJpeg() 
{
	// TODO: Add your control notification handler code here
	UpdateData();	
}

void CFileDlg::OnFilePng() 
{
	// TODO: Add your control notification handler code here
	UpdateData();	
}
