// UltraFileConversionDlg.cpp : implementation file
//

#include "stdafx.h"

#include "Interface_Header.h"
#include "JGLEE__STD_DATALOG.h"
#include "UltraFileConversionDlg.h"


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
//	enum { IDD = IDD_ABOUTBOX };
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

// CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
// {
// 	//{{AFX_DATA_INIT(CAboutDlg)
// 	//}}AFX_DATA_INIT
// }
// 
// void CAboutDlg::DoDataExchange(CDataExchange* pDX)
// {
// 	CDialog::DoDataExchange(pDX);
// 	//{{AFX_DATA_MAP(CAboutDlg)
// 	//}}AFX_DATA_MAP
// }

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
	
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUltraFileConversionDlg dialog

CUltraFileConversionDlg::CUltraFileConversionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUltraFileConversionDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUltraFileConversionDlg)
		// NOTE: the ClassWizard will add member initialization here
	m_TXTF = FALSE;
	m_CSVF = TRUE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
//	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUltraFileConversionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUltraFileConversionDlg)
	DDX_Control(pDX, IDC_LIST_TARGET, m_ListTarget);
	DDX_Control(pDX, IDC_LIST_SOURCE, m_ListSource);
	DDX_Control(pDX, IDC_LIST_BOX, m_ListBox);
	DDX_Check(pDX, IDC_CHECK__FORMAT_CSV, m_CSVF);
	DDX_Check(pDX, IDC_CHECK__FORMAT_TXT, m_TXTF);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_CHECK__ALIGN_LEFT,  mCheck__Align_Left);
	DDX_Control(pDX, IDC_CHECK__ALIGN_RIGHT, mCheck__Align_Right);
}

BEGIN_MESSAGE_MAP(CUltraFileConversionDlg, CDialog)
	//{{AFX_MSG_MAP(CUltraFileConversionDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CREATE()
	ON_NOTIFY(HDN_ITEMCLICK, IDC_LIST_BOX, OnItemclickListBox)
	ON_NOTIFY(NM_CLICK, IDC_LIST_BOX, OnClickListBox)
	ON_BN_CLICKED(IDC_ALL, OnAll)
	ON_BN_CLICKED(IDC_CLEAR, OnClear)
	ON_CBN_EDITCHANGE(IDC_LIST_SOURCE, OnEditchangeListSource)
	ON_CBN_SELCHANGE(IDC_LIST_SOURCE, OnSelchangeListSource)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_BOX, OnColumnclickListBox)

	ON_BN_CLICKED(IDC_CHECK__FORMAT_CSV, OnCheck__Format_CSV)
	ON_BN_CLICKED(IDC_CHECK__FORMAT_TXT, OnCheck__Format_TXT)
	
	ON_BN_CLICKED(IDC_CHECK__ALIGN_LEFT,  &CUltraFileConversionDlg::OnBnClickedCheck__Align_Left)
	ON_BN_CLICKED(IDC_CHECK__ALIGN_RIGHT, &CUltraFileConversionDlg::OnBnClickedCheck__Align_Right)

	//}}AFX_MSG_MAP

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUltraFileConversionDlg message handlers

// void CUltraFileConversionDlg::OnSysCommand(UINT nID, LPARAM lParam)
// {
// 	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
// 	{
// 		CAboutDlg dlgAbout;
// 		dlgAbout.DoModal();
// 	}
// 	else
// 	{
// 		CDialog::OnSysCommand(nID, lParam);
// 	}
// }

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CUltraFileConversionDlg::OnPaint() 
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
HCURSOR CUltraFileConversionDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


//////////////////////////////////////////////////////////////////////
int CUltraFileConversionDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	///////////////////////////////////////////
	CRect  rect;
	GetWindowRect(rect);

	int   width, height;

	width    = rect.right  - rect.left; 
	height   = rect.bottom - rect.top;
	
	SetWindowPos(&wndTopMost,
		         rect.left, 
				 rect.top,
				 width,
				 height,
				 SWP_SHOWWINDOW);
	///////////////////////////////////////////

	return 0;
}

void CUltraFileConversionDlg::OnCheck__Format_CSV() 
{
	m_CSVF = TRUE;
	m_TXTF = FALSE;

	UpdateData(FALSE);	
}
void CUltraFileConversionDlg::OnCheck__Format_TXT() 
{
	m_CSVF = FALSE;
	m_TXTF = TRUE;

	UpdateData(FALSE);
}

BOOL CUltraFileConversionDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	/*
	// ...
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
	*/

	// ...
	{
		// ...
		{
			Upload_Inf();
			Init_Table();
		}

		// ...
		{
			m_Dir_ModuleID = m_Seq_ModuleID;

			/*
			if(m_Dir_ModuleID_From_Out < 1)
			{
				m_Dir_ModuleID = m_Seq_ModuleID;
			}
			else
			{
				m_Dir_ModuleID = m_Dir_ModuleID_From_Out;
			}
			*/
		}

		// ...
		{
			Upload_Dir(m_Dir_ModuleID);
		
			if(Upload_DirFile(m_Dir_ModuleID,mExt) > 0)
			{
				View_DirFileList();
			}
		}
	}

	/*	
	// ...
	if(mVersion < 2)
	{
		Upload_File(mDir,mExt,1);
		View_FileList();
	}
	else 
	{
		Upload_Dir(mDir);
		
		if(Upload_DirFile(mDir,mExt) > 0)
		{
			View_DirFileList();
		}
	}	
	*/

	// ...
	{
		mCheck__Align_Left.SetCheck(1);
		mCheck__Align_Right.SetCheck(0);
	}

	UpdateData(FALSE);
	return TRUE; 
}


LRESULT CUltraFileConversionDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	switch(message)
	{
		case WM_KEYDOWN:
			switch(wParam)
			{
				case VK_ESCAPE:		return 0;
			}
			break;
	}
	
	return CDialog::WindowProc(message, wParam, lParam);
}


int  CUltraFileConversionDlg::Init_Table() 
{
	LV_COLUMN lvcolumn;
	int  i;
	char *list[10] = {"FILE LIST","TIME"};
	int  width[10] = {  350, 120};
	COLORREF bcolor, tcolor;
	
	bcolor = RGB(255,255,255);
	tcolor = RGB(0,0,0);	
	m_ListBox.SetBkColor(bcolor);
	m_ListBox.SetTextBkColor(bcolor);
	m_ListBox.SetTextColor(tcolor);

	ListView_SetExtendedListViewStyle(m_ListBox.m_hWnd,
								      LVS_EX_FULLROWSELECT
									  |LVS_EX_GRIDLINES
									  |LVS_EX_CHECKBOXES
									  );

	for(i=0;i<2;i++)
	{
		lvcolumn.mask= LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
		lvcolumn.fmt = LVCFMT_LEFT;
		lvcolumn.pszText  = list[i];
		lvcolumn.iSubItem = i;
		lvcolumn.cx       = width[i];
		m_ListBox.InsertColumn(i,&lvcolumn);
	}

	return 1;
}
/*
int  CUltraFileConversionDlg::View_FileList()
{
	CString date;
	char    name[500];
	LV_ITEM lvitem;
	int		i, limit, index;

	index = m_ListSource.GetCurSel();
	if(index < 0)	return -1;
	
	m_ListSource.GetLBText(index,date);
	index = Get_ListIndex(date);
	if(index < 0)	return -1;

	lvitem.mask = LVIF_TEXT;
	limit = mFile_Name[index].GetSize();

	m_ListBox.DeleteAllItems();
	
	for(i=0;i<limit;i++)
	{
		lvitem.iItem = i;

		// 0
		strcpy(name,mFile_Name[index][i]);
		lvitem.iSubItem = 0;
		lvitem.pszText  = name;
		m_ListBox.InsertItem(&lvitem);

		// 1
		strcpy(name,mFile_Time[index][i]);
		lvitem.iSubItem = 1;
		lvitem.pszText  = name;
		m_ListBox.SetItem(&lvitem);
	}

	return 1;
}
*/

int  CUltraFileConversionDlg::View_DirFileList()
{
	CString date;
	char    name[500];
	LV_ITEM lvitem;
	int		i, limit, index;

	index = m_ListSource.GetCurSel();
	if(index < 0)	return -1;
	
	lvitem.mask = LVIF_TEXT;
	limit = m_FileList.GetSize();

	m_ListBox.DeleteAllItems();

// 	CString ts;
// 	ts.Format("%d", limit);
// 	AfxMessageBox(ts);

	for(i=0;i<limit;i++)
	{
		lvitem.iItem = i;

		// 0
		strcpy(name,m_FileList.GetAt(i));
		lvitem.iSubItem = 0;
		lvitem.pszText  = name;
		m_ListBox.InsertItem(&lvitem);

		// 1
		strcpy(name,m_FileDateList.GetAt(i));
		lvitem.iSubItem = 1;
		lvitem.pszText  = name;
		m_ListBox.SetItem(&lvitem);

		m_ListBox.SetItemData(i, i);
	}

	return 1;
}

/*
int  CUltraFileConversionDlg::Upload_File(CString dir,CString ext,int mode) 
{
	/////////////////////////////////////
	WIN32_FIND_DATA wfd;
	SYSTEMTIME      file_time;
	FILETIME        lftime;
	HANDLE          hsrch;
	CString			path, date, order, time, t_order;

	BOOL	hresult = TRUE;
	int		i, index, file_count = 0;

	path.Format("%s\\*.%s",dir,ext);

	strcpy(wfd.cFileName,"");
	hsrch = FindFirstFile(path,&wfd);
	if((hsrch != NULL)&&(strlen(wfd.cFileName) > 0))
	{
		while(hresult)
		{
			if(wfd.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY)
			{
				i = file_count++;	
				
				FileTimeToLocalFileTime(&wfd.ftLastWriteTime,&lftime);
				FileTimeToSystemTime(&lftime,&file_time);

				date.Format("%00004d/%002d/%002d",
							file_time.wYear,
							file_time.wMonth,
							file_time.wDay);

				order.Format("%00004d%002d%002d",
							 file_time.wYear,
							 file_time.wMonth,
							 file_time.wDay);				

				time.Format("%002d:%002d:%002d",
							file_time.wHour,
							file_time.wMinute,
							file_time.wSecond);
				
				t_order.Format("%002d%002d%002d",
							   file_time.wHour,
							   file_time.wMinute,
							   file_time.wSecond);

				index = Load_Date(date,order);

				if(index >= 0)
				{
					int limit = mFile_Name[index].GetSize();

					mFile_Name[index].SetSize(limit+1);
					mFile_Time[index].SetSize(limit+1);
					mFile_Order[index].SetSize(limit+1);

					mFile_Name[index][limit] = wfd.cFileName;
					mFile_Time[index][limit] = time;
					mFile_Order[index][limit] = t_order;
				}
			}

			hresult = FindNextFile(hsrch,&wfd);
		}
	}
	FindClose(hsrch);

	Sort_Date();
	Sort_Time();

	int limit = mList_OrderDate.GetSize();
	for(i=0;i<limit;i++)
	{
		m_ListSource.AddString(mList_OrderDate[i]);
	}
	if(limit > 0)		m_ListSource.SetCurSel(0);


	/////////////////////////////////////////	
	char root_dir[100];
	char ch;
	UINT flag;

	for(ch = 'A'; ch <= 'Z'; ch++)
	{
		sprintf(root_dir,"%1c:\\",ch);
		flag = GetDriveType(root_dir);
		
		if((flag != DRIVE_UNKNOWN)
		&& (flag != DRIVE_NO_ROOT_DIR)
		&& (flag != DRIVE_CDROM))
		{
			sprintf(root_dir,"%sPROCESS_DATALOG\\",root_dir);

			CreateDirectory(root_dir,NULL);
			m_ListTarget.AddString(root_dir);
		}
	}
	m_ListTarget.SetCurSel(0);
	/////////////////////////////////////

	return 1;
}
*/
/*
int  CUltraFileConversionDlg::Upload_File(int modulID,CString ext,int mode) 
{
	CGX_FILE__DATALOG_CTRL cx_datalog_ctrl;
	CStringArray DirList;
	cx_datalog_ctrl->Get__DIR_LIST(modulID,DirList);
	int DirListSize = DirList.GetSize();

	CStringArray TotalFileList;
	CStringArray TotalFileDateList;

	for(int i=0; i<DirListSize; i++)
	{
		CString DirName;
		CStringArray FileList;
		CStringArray FileDateList;

		DirName = DirList.GetAt(i);
		cx_datalog_ctrl->Get__FILE_LIST(modulID,DirName,ext,FileList,FileDateList);
		TotalFileList.Append(FileList);
		TotalFileDateList.Append(FileDateList);
	}

	/////////////////////////////////////
	WIN32_FIND_DATA wfd;
	SYSTEMTIME      file_time;
	FILETIME        lftime;
	HANDLE          hsrch;
	CString			path, date, order, time, t_order;

	BOOL	hresult = TRUE;
	int		i, index, file_count = 0;

	path.Format("%s\\*.%s",dir,ext);

	strcpy(wfd.cFileName,"");
	hsrch = FindFirstFile(path,&wfd);
	if((hsrch != NULL)&&(strlen(wfd.cFileName) > 0))
	{
		while(hresult)
		{
			if(wfd.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY)
			{
				i = file_count++;	
				
				FileTimeToLocalFileTime(&wfd.ftLastWriteTime,&lftime);
				FileTimeToSystemTime(&lftime,&file_time);

				date.Format("%00004d/%002d/%002d",
							file_time.wYear,
							file_time.wMonth,
							file_time.wDay);

				order.Format("%00004d%002d%002d",
							 file_time.wYear,
							 file_time.wMonth,
							 file_time.wDay);				

				time.Format("%002d:%002d:%002d",
							file_time.wHour,
							file_time.wMinute,
							file_time.wSecond);
				
				t_order.Format("%002d%002d%002d",
							   file_time.wHour,
							   file_time.wMinute,
							   file_time.wSecond);

				index = Load_Date(date,order);

				if(index >= 0)
				{
					int limit = mFile_Name[index].GetSize();

					mFile_Name[index].SetSize(limit+1);
					mFile_Time[index].SetSize(limit+1);
					mFile_Order[index].SetSize(limit+1);

					mFile_Name[index][limit] = wfd.cFileName;
					mFile_Time[index][limit] = time;
					mFile_Order[index][limit] = t_order;
				}
			}

			hresult = FindNextFile(hsrch,&wfd);
		}
	}
	FindClose(hsrch);

	Sort_Date();
	Sort_Time();

	int limit = mList_OrderDate.GetSize();
	for(i=0;i<limit;i++)
	{
		m_ListSource.AddString(mList_OrderDate[i]);
	}
	if(limit > 0)		m_ListSource.SetCurSel(0);


	/////////////////////////////////////////	
	char root_dir[100];
	char ch;
	UINT flag;

	for(ch = 'A'; ch <= 'Z'; ch++)
	{
		sprintf(root_dir,"%1c:\\",ch);
		flag = GetDriveType(root_dir);
		
		if((flag != DRIVE_UNKNOWN)
		&& (flag != DRIVE_NO_ROOT_DIR)
		&& (flag != DRIVE_CDROM))
		{
			sprintf(root_dir,"%sPROCESS_DATALOG\\",root_dir);

			CreateDirectory(root_dir,NULL);
			m_ListTarget.AddString(root_dir);
		}
	}
	m_ListTarget.SetCurSel(0);
	/////////////////////////////////////

	return 1;
}
*/
int  CUltraFileConversionDlg::Upload_Dir(int modulID) 
{
	CGX_FILE__DATALOG_CTRL cx_datalog_ctrl;

	// ...
	{
		cx_datalog_ctrl->Get__DIR_LIST(modulID,"",m_DirList);
		int DirListSize = m_DirList.GetSize();

		for(int i=0;i<DirListSize;i++)
		{
			m_ListSource.AddString(m_DirList.GetAt(i));
		}
		if(DirListSize > 0)
		{
			m_ListSource.SetCurSel(0);
		}
	}

	// ...
	{
		char root_dir[256];
		char ch;
		UINT flag;

		for(ch = 'A'; ch <= 'Z'; ch++)
		{
			sprintf(root_dir,"%1c:\\",ch);
			flag = GetDriveType(root_dir);
		
			if((flag != DRIVE_UNKNOWN)
			&& (flag != DRIVE_NO_ROOT_DIR)
			&& (flag != DRIVE_CDROM))
			{
				sprintf(root_dir,"%sPROCESS_DATALOG\\",root_dir);

				CreateDirectory(root_dir,NULL);
				m_ListTarget.AddString(root_dir);
			}
		}
		m_ListTarget.SetCurSel(0);
	}

	return 1;

}
/*
int  CUltraFileConversionDlg::Upload_Dir(CString dir) 
{
	/////////////////////////////////////
	WIN32_FIND_DATA wfd;
	SYSTEMTIME      file_time;
	FILETIME        lftime;
	HANDLE          hsrch;
	CString			path, name, date;

	BOOL	hresult = TRUE;
	int		i, dir_count = 0;

	path.Format("%s\\*.*",dir);

	strcpy(wfd.cFileName,"");
	hsrch = FindFirstFile(path,&wfd);
	if((hsrch != NULL)&&(strlen(wfd.cFileName) > 0))
	{
		while(hresult)
		{
			if(wfd.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
			{
				if((strcmp(wfd.cFileName,".")  != 0)
				&& (strcmp(wfd.cFileName,"..") != 0))
				{
					i = dir_count++;	
				
					FileTimeToLocalFileTime(&wfd.ftLastWriteTime,&lftime);
					FileTimeToSystemTime(&lftime,&file_time);

					name = wfd.cFileName;

					date.Format("%00004d/%002d/%002d",
								file_time.wYear,
								file_time.wMonth,
								file_time.wDay);

					Load_Dir(name,date);
				}
			}

			hresult = FindNextFile(hsrch,&wfd);
		}
	}
	FindClose(hsrch);

	Sort_Date();
	//Sort_Time();

	int limit = mList_OrderDate.GetSize();
	for(i=0;i<limit;i++)
	{
		m_ListSource.AddString(mList_OrderDate[i]);
	}
	if(limit > 0)		m_ListSource.SetCurSel(0);


	/////////////////////////////////////////	
	char root_dir[100];
	char ch;
	UINT flag;

	for(ch = 'A'; ch <= 'Z'; ch++)
	{
		sprintf(root_dir,"%1c:\\",ch);
		flag = GetDriveType(root_dir);
		
		if((flag != DRIVE_UNKNOWN)
		&& (flag != DRIVE_NO_ROOT_DIR)
		&& (flag != DRIVE_CDROM))
		{
			sprintf(root_dir,"%sPROCESS_DATALOG\\",root_dir);

			CreateDirectory(root_dir,NULL);
			m_ListTarget.AddString(root_dir);
		}
	}
	m_ListTarget.SetCurSel(0);
	/////////////////////////////////////

	return 1;
}
*/
int  CUltraFileConversionDlg::Upload_DirFile(int modulID,CString ext)
{

	/////////////////////////////////////
	CString dir, sub_dir;
	int index;

	index = m_ListSource.GetCurSel();
	if(index < 0)	return -1;

	CGX_FILE__DATALOG_CTRL cx_datalog_ctrl;
	m_ListSource.GetLBText(index,sub_dir);

	m_FileList.RemoveAll();
	m_FileDateList.RemoveAll();

	//////////////////////////////////////////////////////////////////////////
	CStringArray tmpFileList;
	cx_datalog_ctrl->Get__FILE_LIST(modulID,sub_dir,ext,tmpFileList,m_FileDateList);
	CString addSubDir;
	for(int j=0; j< tmpFileList.GetSize(); j++)
	{
		addSubDir.Format("%s",tmpFileList.GetAt(j));
		addSubDir.MakeUpper();
		m_FileList.Add(addSubDir);
	}
	//////////////////////////////////////////////////////////////////////////


	CStringArray sub2List;
	cx_datalog_ctrl->Get__DIR_LIST(modulID,sub_dir,sub2List);
	
	int sub2Size = sub2List.GetSize();

	if(sub2Size > 0)
	{
		//////////////////////////////////////////////////////////////////////////
		
		//////////////////////////////////////////////////////////////////////////
		for(int i=0; i<sub2Size; i++)
		{
			
			CString DirName;
			CString Sub_D;
			CStringArray subFileList;
			CStringArray subFileDateList;
			
			DirName = sub2List.GetAt(i);
			
			Sub_D += sub_dir;
			Sub_D += "\\";
			Sub_D += DirName;
			cx_datalog_ctrl->Get__FILE_LIST(modulID,Sub_D,ext,subFileList,subFileDateList);
			
			CString addSubDir;
			for(int j=0; j< subFileList.GetSize(); j++)
			{
				addSubDir.Format("%s\\%s",DirName,subFileList.GetAt(j));
				addSubDir.MakeUpper();
				m_FileList.Add(addSubDir);
			}
			
			//m_FileList.Append(subFileList);
			m_FileDateList.Append(subFileDateList);
			
		}
	}
		
		

//	cx_datalog_ctrl->Get__FILE_LIST(modulID,sub_dir,ext,m_FileList,m_FileDateList);

	/*
	for(int i=0; i<DirListSize; i++)
	{
		CString DirName;
		CStringArray FileList;
		CStringArray FileDateList;

		DirName = DirList.GetAt(i);
		cx_datalog_ctrl->Get__FILE_LIST(modulID,DirName,ext,FileList,FileDateList);
		TotalFileList.Append(FileList);
		TotalFileDateList.Append(FileDateList);
	}
  */

	return 1;
}

/*
int  CUltraFileConversionDlg::Upload_DirFile(CString dir_root,CString ext) 
{
	/////////////////////////////////////
	CString dir, sub_dir;
	int index;

	index = m_ListSource.GetCurSel();
	if(index < 0)	return -1;

	dir  = dir_root;
	dir += "\\";
	m_ListSource.GetLBText(index,sub_dir);
	dir += sub_dir;
	/////////////////////////////////////

	mList_FileName.RemoveAll();
	mList_PathName.RemoveAll();
	mList_FileTime.RemoveAll();
	mList_FileOrder.RemoveAll();

	/////////////////////////////////////
	WIN32_FIND_DATA wfd;
	SYSTEMTIME      file_time;
	FILETIME        lftime;
	HANDLE          hsrch;
	CString			path, time, order;

	BOOL	hresult = TRUE;
	int		i, file_count = 0;

	CString dot_ext;
	dot_ext.Format(".%s",ext);

	//path.Format("%s\\*.%s",dir,ext);
	path.Format("%s\\*.*",dir);

	strcpy(wfd.cFileName,"");
	hsrch = FindFirstFile(path,&wfd);
	if((hsrch != NULL)&&(strlen(wfd.cFileName) > 0))
	{
		while(hresult)
		{
			if(wfd.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY)
			{
				CString file_name = wfd.cFileName;
				if(file_name.Find(dot_ext) < 0)	continue;
				
				i = file_count++;	
				
				FileTimeToLocalFileTime(&wfd.ftLastWriteTime,&lftime);
				FileTimeToSystemTime(&lftime,&file_time);

				time.Format("%002d:%002d:%002d",
							file_time.wHour,
							file_time.wMinute,
							file_time.wSecond);
				
				order.Format("%002d%002d%002d",
							 file_time.wHour,
							 file_time.wMinute,
							 file_time.wSecond);

				file_name.MakeUpper();
				mList_FileName.Add(file_name);
				mList_PathName.Add(file_name);
				mList_FileTime.Add(time);
				mList_FileOrder.Add(order);
			}
			else 
			{
				if((strcmp(wfd.cFileName,".")  != 0)
				&& (strcmp(wfd.cFileName,"..") != 0))
				{
					CString sub_dir;
					CString sub_file;

					sub_file = wfd.cFileName;
					sub_dir.Format("%s\\%s\\",dir,sub_file);
					
					Upload_SubFile(sub_dir,ext,sub_file);
				}
			}

			hresult = FindNextFile(hsrch,&wfd);
		}
	}
	FindClose(hsrch);

	//Sort_Time_DirFile();
	Sort_Name_DirFile();
	return 1;
}
*/
int  CUltraFileConversionDlg::Upload_SubFile(CString sub_dir,
											 CString ext,
											 CString sub_file)
{
	//---------------------------------------------------------------
	WIN32_FIND_DATA wfd;
	SYSTEMTIME      file_time;
	FILETIME        lftime;
	HANDLE          hsrch;
	CString			path, time, order;

	BOOL	hresult = TRUE;
	int		i, file_count = 0;

	CString dot_ext;
	dot_ext.Format(".%s",ext);

	//path.Format("%s\\*.%s",sub_dir,ext);
	path.Format("%s\\*.*",sub_dir);

	strcpy(wfd.cFileName,"");
	hsrch = FindFirstFile(path,&wfd);

	if((hsrch != NULL)&&(strlen(wfd.cFileName) > 0))
	{
		while(hresult)
		{
			if(wfd.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY)
			{
				CString file_name = wfd.cFileName;
				if(file_name.Find(dot_ext) < 0)	continue;

				i = file_count++;	
				
				FileTimeToLocalFileTime(&wfd.ftLastWriteTime,&lftime);
				FileTimeToSystemTime(&lftime,&file_time);

				time.Format("%002d:%002d:%002d",
							file_time.wHour,
							file_time.wMinute,
							file_time.wSecond);
				
				order.Format("%002d%002d%002d",
							 file_time.wHour,
							 file_time.wMinute,
							 file_time.wSecond);

				CString dir_file_name;
				dir_file_name.Format("%s\\%s",sub_file,file_name);
				dir_file_name.MakeUpper();

				mList_FileName.Add(dir_file_name);
				mList_PathName.Add(file_name);

				mList_FileTime.Add(time);
				mList_FileOrder.Add(order);
			}

			hresult = FindNextFile(hsrch,&wfd);
		}
	}
	FindClose(hsrch);

	return 1;
}

int  CUltraFileConversionDlg::Load_Date(CString date,CString order)
{
	int i, limit;

	limit = mList_Date.GetSize();
	for(i=0;i<limit;i++)
	{
		if(mList_Date[i].Compare(date) == 0)
		{
			return i;
		}
	}

	if(limit >= 100)	return -1;

	mList_Date.SetSize(limit+1);
	mList_Order.SetSize(limit+1);
	mList_OrderDate.SetSize(limit+1);

	mList_Date[limit]  = date;
	mList_Order[limit] = order;
	mList_OrderDate[limit] = date;
	return limit;
}

int  CUltraFileConversionDlg::Load_Dir(CString name,CString date)
{
	int limit;

	limit = mList_Date.GetSize();
	if(limit >= 100)	return -1;

	mList_Date.SetSize(limit+1);
	mList_Order.SetSize(limit+1);
	mList_OrderDate.SetSize(limit+1);

	mList_Date[limit]  = name;
	mList_Order[limit] = date;
	mList_OrderDate[limit] = name;
	return limit;
}

int  CUltraFileConversionDlg::Sort_Date()
{
	CString order, date;
	double  i_order;
	int	    i, i_limit, k, k_limit;

	i_limit = mList_Date.GetSize() - 1;
	k_limit = i_limit + 1;
	for(i=0;i<i_limit;i++)
	{
		date  = mList_OrderDate[i];
		order = mList_Order[i];

		i_order = atof(order);

		for(k=i+1;k<k_limit;k++)
		{
			if(i_order < atof(mList_Order[k]))
			{
				mList_OrderDate[i]  = mList_OrderDate[k];
				mList_Order[i] = mList_Order[k];

				mList_OrderDate[k]  = date;
				mList_Order[k] = order;

				date  = mList_OrderDate[i];
				order = mList_Order[i];

				i_order = atof(order);
			}
		}
	}

	return 1;
}

int  CUltraFileConversionDlg::Sort_Time()
{
	CString name, time, order;
	double  i_order;
	int	    n, n_limit, i, i_limit, k, k_limit;

	n_limit = mList_Date.GetSize();
	for(n=0;n<n_limit;n++)
	{
		i_limit = mFile_Name[n].GetSize() - 1;
		k_limit = i_limit + 1;
		for(i=0;i<i_limit;i++)
		{
			name  = mFile_Name[n][i];
			time  = mFile_Time[n][i];
			order = mFile_Order[n][i];
			
			i_order = atof(order);
		
			for(k=i+1;k<k_limit;k++)
			{
				if(i_order < atof(mFile_Order[n][k]))
				{
					mFile_Name[n][i]  = mFile_Name[n][k];
					mFile_Time[n][i]  = mFile_Time[n][k];
					mFile_Order[n][i] = mFile_Order[n][k];

					mFile_Name[n][k]  = name;
					mFile_Time[n][k]  = time;
					mFile_Order[n][k] = order;

					name  = mFile_Name[n][i];
					time  = mFile_Time[n][i];
					order = mFile_Order[n][i];

					i_order = atof(order);
				}
			}
		}
	}

	return 1;
}

int  CUltraFileConversionDlg::Sort_Time_DirFile()
{
	CString name, path, time, order;
	int	    i, limit, k;
	int     com_time, cur_time;

	limit = mList_FileName.GetSize();
	
	for(i=0;i<limit;i++)
	{
		com_time = atoi(mList_FileOrder[i]);
				
		for(k=i+1;k<limit;k++)
		{
			cur_time = atoi(mList_FileOrder[k]);
			if(com_time < cur_time)
			{
				com_time = cur_time;

				name  = mList_FileName[i];
				path  = mList_PathName[i];
				time  = mList_FileTime[i];
				order = mList_FileOrder[i];

				mList_FileName[i]  = mList_FileName[k];
				mList_PathName[i]  = mList_PathName[k];
				mList_FileTime[i]  = mList_FileTime[k];
				mList_FileOrder[i] = mList_FileOrder[k];

				mList_FileName[k]  = name;
				mList_PathName[k]  = path;
				mList_FileTime[k]  = time;
				mList_FileOrder[k] = order;
			}
		}
	}

	return 1;
}
/*
int  CUltraFileConversionDlg::Sort_Name_DirFile()
{
	CString name, path, time, order;
	int	    i, limit, k;
	CString com_name, cur_name;

	limit = mList_FileName.GetSize();
	
	for(i=0;i<limit;i++)
	{
		com_name = mList_FileName[i];
				
		for(k=i+1;k<limit;k++)
		{
			cur_name = mList_FileName[k];

			if(strcmp(com_name,cur_name) > 0)
			{
				com_name = cur_name;

				name  = mList_FileName[i];
				path  = mList_PathName[i];
				time  = mList_FileTime[i];
				order = mList_FileOrder[i];

				mList_FileName[i]  = mList_FileName[k];
				mList_PathName[i]  = mList_PathName[k];
				mList_FileTime[i]  = mList_FileTime[k];
				mList_FileOrder[i] = mList_FileOrder[k];

				mList_FileName[k]  = name;
				mList_PathName[k]  = path;
				mList_FileTime[k]  = time;
				mList_FileOrder[k] = order;
			}
		}
	}

	return 1;
}
*/

int CALLBACK CUltraFileConversionDlg::SortFunc1(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	CListCtrl *pListCtrl = (CListCtrl*) lParamSort;
	
	
	LVFINDINFO info1, info2;
	info1.flags = LVFI_PARAM;
	info1.lParam = lParam1;
	info2.flags = LVFI_PARAM;
	info2.lParam = lParam2;
 	int irow1 = pListCtrl->FindItem(&info1,-1);
 	int irow2 = pListCtrl->FindItem(&info2,-1);
	
 	CString strItem1 = pListCtrl->GetItemText(irow1, 0);
 	CString strItem2 = pListCtrl->GetItemText(irow2, 0);

	return strcmp(strItem1, strItem2);	

}

int CALLBACK CUltraFileConversionDlg::SortFunc2(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	CListCtrl *pListCtrl = (CListCtrl*) lParamSort;
	
	
	LVFINDINFO info1, info2;
	info1.flags = LVFI_PARAM;
	info1.lParam = lParam1;
	info2.flags = LVFI_PARAM;
	info2.lParam = lParam2;
 	int irow1 = pListCtrl->FindItem(&info1,-1);
 	int irow2 = pListCtrl->FindItem(&info2,-1);
	
 	CString strItem1 = pListCtrl->GetItemText(irow1, 1);
 	CString strItem2 = pListCtrl->GetItemText(irow2, 1);
	
	CString year;
	int year1, year2;
	CString month;
	int month1, month2;
	CString day;
	int day1, day2;
	CString hour;
	int hour1, hour2;
	CString minute;
	int minute1, minute2;
	CString sec;
	int sec1, sec2;

	year = strItem1.Mid(0,4);
	year1 = atoi(year);
	month = strItem1.Mid(5,2);
	month1 = atoi(month);
	day = strItem1.Mid(8,2);
	day1 = atoi(day);
	hour = strItem1.Mid(11,2);
	hour1 = atoi(hour);
	minute = strItem1.Mid(14,2);
	minute1 = atoi(minute);
	sec = strItem1.Mid(17,2);
	sec1 = atoi(sec);

	year = strItem2.Mid(0,4);
	year2 = atoi(year);
	month = strItem2.Mid(5,2);
	month2 = atoi(month);
	day = strItem2.Mid(8,2);
	day2 = atoi(day);
	hour = strItem2.Mid(11,2);
	hour2 = atoi(hour);
	minute = strItem2.Mid(14,2);
	minute2 = atoi(minute);
	sec = strItem2.Mid(17,2);
	sec2 = atoi(sec);


	if(year2 >= year1) 
	{
		if(year2 > year1) 
		{
			return 1;
		} else {
			if(month2 >= month1)
			{
				if(month2 > month1)
				{
					return 1;
				} else {
					if(day2 >= day1)
					{
						if( day2 > day1)
						{
							return 1;
						} else {
							if( hour2 >= hour1)
							{
								if(hour2 > hour1)
								{
									return 1;
								} else {
									if(minute2 >= minute1)
									{
										if(minute2>minute1)
										{
											return 1;
										} else {
											if(sec2 >= sec1)
											{
												if(sec2 > sec1)
													return 1;
												else return 0;

											} else {
												return -1;
											}
										}

									} else {
										return -1;
									}
								}

							}else {
								return -1;
							}
						}

					} else {
						return -1;
					}
				}
					
			} else {
				return -1;
			}
		}

	} else {
		return -1;
	}
	

}


int  CUltraFileConversionDlg::Sort_Name_DirFile()
{
	CString name, path, time, order;
	int	    i, limit, k;
	CString com_name, cur_name;

	limit = mList_FileName.GetSize();
	
	for(i=0;i<limit;i++)
	{
		com_name = mList_FileName[i];
				
		for(k=i+1;k<limit;k++)
		{
			cur_name = mList_FileName[k];

			if(strcmp(com_name,cur_name) > 0)
			{
				com_name = cur_name;

				name  = mList_FileName[i];
				path  = mList_PathName[i];
				time  = mList_FileTime[i];
				order = mList_FileOrder[i];

				mList_FileName[i]  = mList_FileName[k];
				mList_PathName[i]  = mList_PathName[k];
				mList_FileTime[i]  = mList_FileTime[k];
				mList_FileOrder[i] = mList_FileOrder[k];

				mList_FileName[k]  = name;
				mList_PathName[k]  = path;
				mList_FileTime[k]  = time;
				mList_FileOrder[k] = order;
			}
		}
	}

	return 1;
}

int  CUltraFileConversionDlg::Get_ListIndex(CString date)
{
	int i, limit;

	limit = mList_Date.GetSize();
	for(i=0;i<limit;i++)
	{
		if(date.Compare(mList_Date[i]) == 0)
		{
			return i;
		}
	}

	return -1;
}

void CUltraFileConversionDlg::OnItemclickListBox(NMHDR* pNMHDR, LRESULT* pResult) 
{
	HD_NOTIFY *phdn = (HD_NOTIFY *) pNMHDR;

	*pResult = 0;
}

void CUltraFileConversionDlg::OnClickListBox(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	/*
	CString msg;
	msg.Format("Index : %1d, %1d",
			   pNMListView->iSubItem,
			   pNMListView->iItem);
	MessageBox(msg,"CLICK",MB_OK);
	*/

	if(m_ListBox.GetCheck(pNMListView->iItem) == TRUE)
		m_ListBox.SetCheck(pNMListView->iItem,FALSE);
	else
		m_ListBox.SetCheck(pNMListView->iItem,TRUE);

	*pResult = 0;
}

void CUltraFileConversionDlg::OnColumnclickListBox(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	/////////////////////////////////////////
	if(pNMListView->iSubItem == 0)
	{
		if(mVersion < 2)
		{

		}
		else
		{
			//Sort_Name_DirFile();
			m_ListBox.SortItems(SortFunc1, (LPARAM) &m_ListBox);
			//View_DirFileList();
			
			
		}
	}
	else if(pNMListView->iSubItem == 1)
	{
		if(mVersion < 2)
		{

		}
		else
		{
			//Sort_Time_DirFile();
			m_ListBox.SortItems(SortFunc2, (LPARAM) &m_ListBox);
			//View_DirFileList();
			
			
		}
	}
	/////////////////////////////////////////

	
	*pResult = 0;
}


void CUltraFileConversionDlg::OnAll() 
{
	int i, limit;
	limit = m_ListBox.GetItemCount();	

	for(i=0;i<limit;i++)
	{
		m_ListBox.SetCheck(i,TRUE);
	}
}

void CUltraFileConversionDlg::OnClear() 
{
	int i, limit;
	limit = m_ListBox.GetItemCount();	

	for(i=0;i<limit;i++)
	{
		m_ListBox.SetCheck(i,FALSE);
	}
}

void CUltraFileConversionDlg::Upload_Inf()
{
	FILE* in = fopen(sPath__Log_Conversion, "r");
	if(in == NULL)		return;

	mVersion = 1;

	///////////////////////////////////
	CString word;
	char ch, str_ch[2];
	int  command, flag, para, limit;

	str_ch[1] = 0;
	command = -1;
	flag = 1;
	para = 0;

	while(flag > 0)
	{
		ch = fgetc(in);
		str_ch[0] = ch;

		if((ch == ',')||(ch == '\n')||(ch == EOF))
		{
			if(word.GetLength() > 0)
			{
				if(word.Compare("@VERSION") == 0)
				{
					command = 10001;
					para = 0;
				}
				else if(word.Compare("@DIRECTORY") == 0)
				{
					command = 1;
					para = 0;
				}
				else if(word.Compare("@EXT") == 0)
				{
					command = 2;
					para = 0;
				}
				else if(word.Compare("@INTERVAL_ITEM") == 0)
				{
					command = 3;
					para = 0;
				}	
				else if(word.Compare("@EVENT_ITEM") == 0)
				{
					command = 4;
					para = 0;
				}
				else if(command == 10001)
				{
					para++;

					if(para == 1)	mVersion = atoi(word);
				}
				else if(command == 1)
				{
					para++;

					if(para == 1)	m_Dir_ModuleID = atoi(word);
				}
				else if(command == 2)
				{
					para++;

					if(para == 1)	mExt = word;
				}
				else if(command == 3)
				{
					para++;

					if(para == 1)
					{
						limit = mTable_Interval_Item.GetSize();
						mTable_Interval_Item.SetSize(limit+1);
						mTable_Interval_Item[limit] = word;

						mTable_Interval_Title.SetSize(limit+1);
						mTable_Interval_Title[limit] = "";
					} 
					else if(para == 2)
					{
						limit = mTable_Interval_Title.GetSize();
						mTable_Interval_Title.SetSize(limit);
						mTable_Interval_Title[limit-1] = word;
					}
					
					if(ch == '\n')
					{
						para = 0;
					}
				}
				else if(command == 4)
				{
					para++;

					if(para == 1)
					{
						limit = mTable_Event_Item.GetSize();
						mTable_Event_Item.SetSize(limit+1);
						mTable_Event_Item[limit] = word;

						mTable_Event_Title.SetSize(limit+1);
						mTable_Event_Title[limit] = "";
					} 
					else if(para == 2)
					{
						limit = mTable_Event_Title.GetSize();
						mTable_Event_Title.SetSize(limit);
						mTable_Event_Title[limit-1] = word;
						
					}
					
					if(ch == '\n')
					{
						para = 0;
					}
				}
			}

			word = "";
		}
		else
		{
			word += str_ch;
		}

		if(ch == EOF)
		{
			flag = -1;		
		}
	}

	fclose(in);
}

void CUltraFileConversionDlg::OnOK() 
{
	if(mVersion < 2)	Fnc_FileConversion();
	else				Fnc_DirFileConversion();

	CDialog::OnOK();
}

int CUltraFileConversionDlg::Fnc_FileConversion()
{
	CString path, new_path, new_dir, file;
	int i, limit;

	m_ListTarget.GetLBText(m_ListTarget.GetCurSel(),new_dir);
	limit = m_ListBox.GetItemCount();	

	for(i=0;i<limit;i++)
	{
		if(m_ListBox.GetCheck(i) == TRUE)
		{
			UpdateData(TRUE);

			bool align_left = false;
			if(mCheck__Align_Left.GetCheck() > 0)		align_left = true;

			file = m_ListBox.GetItemText(i,0);

			if(m_CSVF == TRUE)
			{
				Make_CSVLogFile("",file,mExt,new_dir,file,"csv", align_left);
			} 
			else 
			{
				Make_LogFile("",file,mExt,new_dir,file,"txt", align_left);
			}
		}
	}

	return 1;
}

int  CUltraFileConversionDlg::Fnc_DirFileConversion()
{
	CString path, new_path, new_dir, file, sub_dir;
	int i, limit, index;

	index = m_ListSource.GetCurSel();
	if(index < 0)	return -1;
	m_ListSource.GetLBText(index,sub_dir);

	m_ListTarget.GetLBText(m_ListTarget.GetCurSel(),new_dir);
	limit = m_ListBox.GetItemCount();	

	for(i=0;i<limit;i++)
	{
		if(m_ListBox.GetCheck(i) == TRUE)
		{
			file = m_ListBox.GetItemText(i,0);
			
			int position = file.Find("\\");

			CString subD = file.Left(position);
			CString ddir;
			ddir = sub_dir;
			ddir += "\\";
			ddir += subD;

			CString filename = file.Mid(position+1);
			CString new_file;

			if(Search_PathName(file,new_file) < 0)
			{
				continue;
			}

			// ...
			UpdateData(TRUE);

			bool align_left = false;
			if(mCheck__Align_Left.GetCheck() > 0)		align_left = true;

			if(m_CSVF == TRUE)
			{	
				Make_CSVLogFile(ddir,filename,mExt,new_dir,new_file,"csv", align_left);
			} 
			else 
			{
				Make_LogFile(ddir,filename,mExt,new_dir,new_file,"txt", align_left);
			}
		}
	}

	return 1;
}

int  CUltraFileConversionDlg::Search_PathName(const CString& file,CString& new_file)
{
	int flag = -1;
	int i;
	//int limit = mList_FileName.GetSize();
	int limit = m_FileList.GetSize();

	for(i=0;i<limit;i++)
	{
		if(m_FileList[i] != file)	continue;

		flag = 1;

		//new_file = mList_PathName[i];

		int position = m_FileList[i].Find("\\");
		CString subD = m_FileList[i].Mid(position+1);

		new_file = subD;
		break;
	}

	return flag;
}

int  CUltraFileConversionDlg
::Make_LogFile(CString sub_path, 
			   CString filename, 
			   CString ext, 
			   CString new_sub_path, 
			   CString new_fimename, 
			   CString new_ext,
			   const bool align_left)
{
	CString file_data;
	CGX_FILE__DATALOG_CTRL cx_pm_ctrl;

	int flag = cx_pm_ctrl->Upload__FILE(m_Dir_ModuleID,
										sub_path,
										ext,
										filename,
										file_data);
		
	if(flag < 0)	return -1;

	CStringArray	list_file_data, list_interval_data, list_event_data;
	int				i, limit;

	//////////////////////////////////////////////////////
	// Logging File 분석 

	list_file_data.SetSize(0);
	list_interval_data.SetSize(0);
	list_event_data.SetSize(0);

	char    ch, str_ch[2];
	CString word, name_str, data_str, time_str;
	int     loop, fnc_num;
	int     under_line;//, flag;
	CString line_word;
	int     interval_flag;

	interval_flag = -1;
	loop = 1;
	str_ch[1] = 0;
	fnc_num = -1;
	flag = 0;
	under_line = 0;

	int data_limit = file_data.GetLength();

	for(i=0;i<data_limit;i++)
	{
		ch = file_data.GetAt(i);
		str_ch[0] = ch;

		if(ch == EOF)	loop = -1;

		if((ch == ';')||(ch == ',')||(ch == '\n')||(ch == ' ')||(ch == EOF))
		{
			if(word.GetLength() > 0)
			{
				if(strcmp(word,"#1") == 0)
				{
					fnc_num = 1;
					flag = 0;
				}
				else if(strcmp(word,"#2") == 0)
				{
					fnc_num = 2;
					flag = 0;
				}
				else if(strcmp(word,"#STEP_MIN") == 0)
				{
					fnc_num = 11;
					flag = 0;
				}
				else if(strcmp(word,"#STEP_MAX") == 0)
				{
					fnc_num = 12;
					flag = 0;
				}
				else if(strcmp(word,"#STEP_AVG") == 0)
				{
					fnc_num = 13;
					flag = 0;
				}
			
				if(fnc_num == 0) 
				{
					flag++;

						 if(flag == 1)	name_str = word;
					else if(flag == 2)	data_str = word;
				}
				else if(fnc_num == 2)
				{
					flag++;

					if(flag == 2)		time_str = word;
				}
			}

			word = "";
		}
		else 
		{
			word += str_ch;
		}


		if(fnc_num == 1)
		{
				 if(ch == '\n')		line_word  = "";
			else if(ch !=  ';')  	line_word += str_ch;
		}
		

		if(ch == ';')
		{
			if(fnc_num == 1)
			{
				CString msg;

				msg.Format(" Datalog Report of File : %s\\%s.%s\n",sub_path,filename,ext);
				
				limit = list_file_data.GetSize();
				list_file_data.SetSize(limit+1);
				list_file_data[limit] = msg;

				msg.Format(" %s\n\n",line_word);
				limit = list_file_data.GetSize();
				list_file_data.SetSize(limit+1);
				list_file_data[limit] = msg;

				//////////////////////////////////////
				CString bff;
				int     k, k_limit;
				k_limit = mTable_Interval_Item.GetSize();
				mTable_Interval_Item.SetSize(k_limit);
				msg = " hh:mm:ss  ";
				for(k=0;k<k_limit;k++)
				{
					if(align_left)			bff.Format("%-20s",mTable_Interval_Title[k]); 
					else					bff.Format("%20s",mTable_Interval_Title[k]); 

					msg += bff;
				}
				msg += "\n"; 

				limit = list_file_data.GetSize();
				list_file_data.SetSize(limit+1);
				list_file_data[limit] = msg;
				//////////////////////////////////////
			}
			else if(fnc_num == 2)
			{
			}
			else if(fnc_num == 0)
			{
				int k, k_limit;

				// Interval
				k_limit = mTable_Interval_Item.GetSize();
				list_interval_data.SetSize(k_limit);
				for(k=0;k<k_limit;k++) 
				{
					if(mTable_Interval_Item[k].Compare(name_str) == 0)
					{
						list_interval_data[k] = data_str;
						k = k_limit;
						interval_flag = 1;
					}						
				}

				// Event
				k_limit = mTable_Event_Item.GetSize();
				for(k=0;k<k_limit;k++) 
				{
					if(mTable_Event_Item[k].Compare(name_str) == 0)
					{
						list_event_data.SetSize(1);

						list_event_data[0].Format("   %s -> %s", mTable_Event_Title[k], data_str);
						k = k_limit;
					}						
				}
			}

			if((fnc_num == 11)
			|| (fnc_num == 12)
			|| (fnc_num == 13))
			{
				fnc_num = -1;
			}
			else if(fnc_num > 0)
			{
				fnc_num = 0;
			}

			name_str = "";
			data_str = "";					
			
			flag = 0;
		}
		else if(ch == '$')
		{
			if(fnc_num == 0)
			{
				CString msg, bff;
				int		k, k_limit, log_flag;

				log_flag = -1;
				msg = time_str; 

				// Interval 
				if(interval_flag > 0)
				{
					k_limit = list_interval_data.GetSize();
					if(k_limit > 0)
					{
						for(k=0;k<k_limit;k++) 
						{
							if(align_left)		bff.Format("%-20s",list_interval_data[k]);
							else				bff.Format("%20s",list_interval_data[k]);

							msg += bff;
						}
						log_flag = 1;
						msg += "\n";
					}
				}
				// Event
				k_limit = list_event_data.GetSize();
				if(k_limit > 0)
				{
					for(k=0;k<k_limit;k++) 
					{
						msg += list_event_data[k];
					}
					log_flag = 1;
					msg += "\n";
				}

				if(log_flag > 0)
				{
					k_limit = list_file_data.GetSize();
					list_file_data.SetSize(k_limit+1);
					list_file_data[k_limit] = msg;
				}

				interval_flag = -1;
				list_event_data.SetSize(0);
			}
		}
	}

//	fclose(in);
	//////////////////////////////////////////////////////

	//////////////////////////////////////////////////////
	FILE *out;

	CString newpath;
	newpath = new_sub_path;
	newpath += new_fimename;
	newpath += ".";
	newpath += new_ext;
	
	out = fopen(newpath,"w");
	if(out != NULL)
	{
		limit = list_file_data.GetSize();
		for(i=0;i<limit;i++)
		{
			fputs(list_file_data[i],out);
		}

		fclose(out);
	}
	//////////////////////////////////////////////////////
	/*flag = cx_pm_ctrl->Download__FILE(m_Dir_ModulID,
				new_sub_path,
				new_exe,
				new_fimename,
				file_data);
			
	if(flag < 0)	return -1;*/

	return 1;
}

int  CUltraFileConversionDlg
::Make_CSVLogFile(CString sub_path, 
				  CString filename, 
				  CString ext, 
				  CString new_sub_path, 
				  CString new_fimename, 
				  CString new_ext,
				  const bool align_left)
{
	CString file_data;
	CGX_FILE__DATALOG_CTRL cx_pm_ctrl;

	int flag = cx_pm_ctrl->Upload__FILE(m_Dir_ModuleID,
										sub_path,
										ext,
										filename,
										file_data);
		
	if(flag < 0)	return -1;

	//.....
	CStringArray	list_file_data, list_interval_data, list_event_data;
	int				i, limit;

	//////////////////////////////////////////////////////
	// Logging File 분석 

	list_file_data.SetSize(0);
	list_interval_data.SetSize(0);
	list_event_data.SetSize(0);

	char    ch, str_ch[2];
	CString word, name_str, data_str, time_str;
	int     loop, fnc_num;
	int     under_line;
	CString line_word;
	int     interval_flag;

	interval_flag = -1;
	loop = 1;
	str_ch[1] = 0;
	fnc_num = -1;
	flag = 0;
	under_line = 0;

	int data_limit = file_data.GetLength();

	for(i=0;i<data_limit;i++)
	{
		//ch = fgetc(in);
		ch = file_data.GetAt(i);
		str_ch[0] = ch;

		if(ch == EOF)	loop = -1;

		if((ch == ';')||(ch == ',')||(ch == '\n')||(ch == ' ')||(ch == EOF))
		{
			if(word.GetLength() > 0)
			{
				if(strcmp(word,"#1") == 0)
				{
					fnc_num = 1;
					flag = 0;
				}
				else if(strcmp(word,"#2") == 0)
				{
					fnc_num = 2;
					flag = 0;
				}
				else if(strcmp(word,"#STEP_MIN") == 0)
				{
					fnc_num = 11;
					flag = 0;
				}
				else if(strcmp(word,"#STEP_MAX") == 0)
				{
					fnc_num = 12;
					flag = 0;
				}
				else if(strcmp(word,"#STEP_AVG") == 0)
				{
					fnc_num = 13;
					flag = 0;
				}
			
				if(fnc_num == 0) 
				{
					flag++;

						 if(flag == 1)	name_str = word;
					else if(flag == 2)	data_str = word;
				}
				else if(fnc_num == 2)
				{
					flag++;

					if(flag == 2)		time_str = word;
				}
			}

			word = "";
		}
		else 
		{
			word += str_ch;
		}


		if(fnc_num == 1)
		{
				 if(ch == '\n')		line_word  = "";
			else if(ch !=  ';')  	line_word += str_ch;
		}
		

		if(ch == ';')
		{
			if(fnc_num == 1)
			{
				CString msg;

				msg.Format(" Datalog Report of File : %s\\%s.%s\n",sub_path,filename,ext);
				
				limit = list_file_data.GetSize();
				list_file_data.SetSize(limit+1);
				list_file_data[limit] = msg;

				msg.Format(" %s\n\n",line_word);
				limit = list_file_data.GetSize();
				list_file_data.SetSize(limit+1);
				list_file_data[limit] = msg;

				//////////////////////////////////////
				CString bff;
				int     k, k_limit;
				k_limit = mTable_Interval_Item.GetSize();
				mTable_Interval_Item.SetSize(k_limit);
				msg = " hh:mm:ss  ";
				for(k=0;k<k_limit;k++)
				{
					if(align_left)			bff.Format("%-20s",mTable_Interval_Title[k]); 
					else					bff.Format("%20s",mTable_Interval_Title[k]); 

					msg += ",";
					msg += bff;
				}
				msg += "\n"; 

				list_file_data.Add(msg);
			}
			else if(fnc_num == 2)
			{
			}
			else if(fnc_num == 0)
			{
				int k, k_limit;

				// Interval
				k_limit = mTable_Interval_Item.GetSize();
				list_interval_data.SetSize(k_limit);
				for(k=0;k<k_limit;k++) 
				{
					if(mTable_Interval_Item[k].Compare(name_str) == 0)
					{
						list_interval_data[k] = data_str;
						k = k_limit;
						interval_flag = 1;
					}						
				}

				// Event
				k_limit = mTable_Event_Item.GetSize();
				for(k=0;k<k_limit;k++) 
				{
					if(mTable_Event_Item[k].Compare(name_str) == 0)
					{
						list_event_data.SetSize(1);

						list_event_data[0].Format("   %s -> %s",
												  name_str,
												  data_str);

						k = k_limit;
					}						
				}
			}

			if((fnc_num == 11)
			|| (fnc_num == 12)
			|| (fnc_num == 13))
			{
				fnc_num = -1;
			}
			else if(fnc_num > 0)
			{
				fnc_num = 0;
			}
			
			name_str = "";
			data_str = "";					
			
			flag = 0;
		}
		else if(ch == '$')
		{
			if(fnc_num == 0)
			{
				CString msg, bff;
				int		k, k_limit, log_flag;

				log_flag = -1;
				msg = time_str; 

				// Interval 
				if(interval_flag > 0)
				{
					k_limit = list_interval_data.GetSize();
					if(k_limit > 0)
					{
						for(k=0;k<k_limit;k++) 
						{
							if(align_left)			bff.Format("%-20s",list_interval_data[k]);
							else					bff.Format("%20s",list_interval_data[k]);
							
							msg += ",";
							msg += bff;
						}
						log_flag = 1;
						msg += "\n";
					}
				}
			
				// Event
				k_limit = list_event_data.GetSize();
				if(k_limit > 0)
				{
					for(k=0;k<k_limit;k++) 
					{
						msg += ",";
						msg += list_event_data[k];
					}
					log_flag = 1;
					msg += "\n";
				}

				if(log_flag > 0)
				{
					list_file_data.Add(msg);
				}

				interval_flag = -1;
				list_event_data.SetSize(0);
			}
		}
	}

	// ...
	{
		FILE *out;
		CString newpath;
		
		newpath = new_sub_path;
		newpath += new_fimename;
		newpath += ".";
		newpath += new_ext;
	
		out = fopen(newpath,"w");
		
		if(out != NULL)
		{
			limit = list_file_data.GetSize();
			for(i=0;i<limit;i++)
			{
				fputs(list_file_data[i],out);
			}

			fclose(out);
		}
	}

	return 1;
}

void CUltraFileConversionDlg::OnEditchangeListSource() 
{
}

void CUltraFileConversionDlg::OnSelchangeListSource() 
{
	if(mVersion < 2)
	{
		// View_FileList();
	}
	else
	{
		// if(Upload_DirFile(mDir,mExt) > 0)
		if(Upload_DirFile(m_Dir_ModuleID,mExt) > 0)
		{
			View_DirFileList();
		}
	}
}

void CUltraFileConversionDlg::OnCancel() 
{
	CDialog::OnCancel();
}


void CUltraFileConversionDlg::OnBnClickedCheck__Align_Left()
{
	mCheck__Align_Left.SetCheck(1);
	mCheck__Align_Right.SetCheck(0);
	
	UpdateData(FALSE);
}
void CUltraFileConversionDlg::OnBnClickedCheck__Align_Right()
{
	mCheck__Align_Left.SetCheck(0);
	mCheck__Align_Right.SetCheck(1);

	UpdateData(FALSE);
}

