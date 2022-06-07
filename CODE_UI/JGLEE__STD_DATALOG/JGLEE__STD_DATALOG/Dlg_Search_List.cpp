#include "stdafx.h"
#include "Interface_Header.h"

#include "JGLEE__STD_DATALOG.h"
#include "Dlg_Search_List.h"


/////////////////////////////////////////////////////////////////////////////
// CDlg_Search_List dialog


CDlg_Search_List::CDlg_Search_List(CWnd* pParent /*=NULL*/)
: CDialog(CDlg_Search_List::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlg_Search_List)
	//}}AFX_DATA_INIT
}


void CDlg_Search_List::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_Search_List)
	DDX_Control(pDX, IDOK, m_Bttn_OK);
	DDX_Control(pDX, IDC_LIST_VIEW, m_List_View);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg_Search_List, CDialog)
	//{{AFX_MSG_MAP(CDlg_Search_List)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg_Search_List message handlers


BOOL CDlg_Search_List::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// ...
	int limit = sList_Item.GetSize();
	int i;

	for(i=0;i<limit;i++)
		m_List_View.AddString(sList_Item[i]);

	if(limit < 1)
		m_Bttn_OK.EnableWindow(FALSE);

	return TRUE;  
}
void CDlg_Search_List::OnOK() 
{
	UpdateData(TRUE);

	int db_index = m_List_View.GetCurSel();
	if(db_index >= 0)
			m_List_View.GetText(db_index,sSel_Name);

	CDialog::OnOK();
}


