// Dlg__Ctrl_List.cpp : implementation file
//

#include "stdafx.h"
#include "JGLEE__BUTTON.h"
#include "Dlg__Ctrl_List.h"

// ...
#define _SIZE__COL_PARA					3
#define _COL_PARA__NO					0
#define _COL_PARA__DATA					1
#define _COL_PARA__COMMENT				2


// CDlg__Ctrl_List dialog

IMPLEMENT_DYNAMIC(CDlg__Ctrl_List, CDialog)

CDlg__Ctrl_List::CDlg__Ctrl_List(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg__Ctrl_List::IDD, pParent)
{

}

CDlg__Ctrl_List::~CDlg__Ctrl_List()
{
}

void CDlg__Ctrl_List::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_ITEM, mCtrl__Item_Table);
	DDX_Control(pDX, IDOK, mCtrl_Run);
}


BEGIN_MESSAGE_MAP(CDlg__Ctrl_List, CDialog)
	ON_NOTIFY(NM_CLICK, IDC_LIST_ITEM, &CDlg__Ctrl_List::OnNMClickListItem__Item_Table)
END_MESSAGE_MAP()


// CDlg__Ctrl_List message handlers

BOOL CDlg__Ctrl_List::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Table.List ...
	{
		CBitmap cBit;
		cBit.LoadBitmap(IDB_DIGITAL_LIST_IMG);

		CListCtrl *p_table = &mCtrl__Item_Table;
		CImageList *p_img = &mImg__Info_Table;

		p_img->Create(1,20, ILC_COLOR4,1,1);
		p_img->Add(&cBit, RGB(0,0,0));	

		p_table->SetImageList(p_img, LVSIL_SMALL);

		// ...
		int list_view_stype;

		list_view_stype  = LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES;
		list_view_stype += LVS_EX_ONECLICKACTIVATE|LVS_EX_UNDERLINEHOT;
		list_view_stype += LVS_EX_INFOTIP;

		p_table->SetExtendedStyle(list_view_stype);

		// ...
		iRESULT__SEL_INDEX = -1;
		sRESULT__SEL_DATA  = "";

		_Init__Item_Table();
		_Update__Item_Table(sList__DATA, sList__COMMENT);
	}

	mCtrl_Run.EnableWindow(FALSE);
	return TRUE;  
}

void CDlg__Ctrl_List::OnNMClickListItem__Item_Table(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	int sel_index = pNMItemActivate->iItem;
	
	if(sel_index >= 0)
	{
		iRESULT__SEL_INDEX = sel_index;
		sRESULT__SEL_DATA  = mCtrl__Item_Table.GetItemText(sel_index, _COL_PARA__DATA);

		mCtrl_Run.EnableWindow(TRUE);
	}
	else
	{
		mCtrl_Run.EnableWindow(FALSE);
	}

	*pResult = 0;
}


void CDlg__Ctrl_List::_Init__Item_Table()
{
	CListCtrl *p_table = &mCtrl__Item_Table;

	// ...
	CStringArray l__col_name;
	CUIntArray   l__col_width;

	// ...
	{
		l__col_name.RemoveAll();
		l__col_width.RemoveAll();

		int i_limit = _SIZE__COL_PARA;
		int i;

		for(i=0; i<i_limit; i++)
		{
			if(i == _COL_PARA__NO)
			{
				l__col_name.Add("No.");
				l__col_width.Add(50);
			}
			else if(i == _COL_PARA__DATA)
			{
				l__col_name.Add("Data");
				l__col_width.Add(300);
			}
			else if(i == _COL_PARA__COMMENT)
			{
				l__col_name.Add("Comment");
				l__col_width.Add(400);
			}
		}
	}

	// ...
	{
		p_table->DeleteAllItems();

		for(int i=0; i<_SIZE__COL_PARA; i++)
		{
			p_table->DeleteColumn(0);
		}
	}

	// ...
	{
		CString col_name;
		int col_cx;

		int limit = l__col_name.GetSize();
		int i;

		for(i=0; i<limit; i++)
		{
			col_name = l__col_name[i];
			col_cx   = (int) l__col_width[i];

			if(col_cx < 1)
			{
				col_cx = 10 + (col_name.GetLength() * 10);
			}

			p_table->InsertColumn(i, col_name, LVCFMT_CENTER, col_cx);
		}		
	}
}

void CDlg__Ctrl_List
::_Update__Item_Table(const CStringArray& l_data, const CStringArray& l_comment)
{
	CListCtrl *p_table = &mCtrl__Item_Table;

	p_table->SetRedraw(FALSE);
	p_table->DeleteAllItems();

	// ...
	int col_id   = _COL_PARA__NO;
	int col_data = _COL_PARA__DATA;
	int col_cmmt = _COL_PARA__COMMENT;

	// ...
	int i_limit = l_data.GetSize();
	int i;

	for(i=0; i<i_limit; i++)
	{	
		CString str_no;
		CString str_data = l_data[i];
		CString str_cmmt = l_comment[i];

		str_no.Format("%1d", i+1);

		p_table->InsertItem(i, str_no, 0);
		p_table->SetItem(i,col_data, LVIF_TEXT, str_data, 0,0,0,0);
		p_table->SetItem(i,col_cmmt, LVIF_TEXT, str_cmmt, 0,0,0,0);
	}

	p_table->SetRedraw(TRUE);
}

