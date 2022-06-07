#include "stdafx.h"
#include "Interface_Header.h"

#include "JGLEE__STD_DATALOG.h"
#include "Dlg_Log_List.h"


extern int Macro__Get_File_Data(const CString& file_path, CString& file_data);


/////////////////////////////////////////////////////////////////////////////
// CDlg_Log_List dialog

#define  DEF_COL__CH_NAME			1
#define  DEF_COL__TITLE				3
#define  DEF_COL__MODE				4
#define  DEF_COL__GROUP				7


CDlg_Log_List::CDlg_Log_List(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_Log_List::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlg_Log_List)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	iFlag__Group_Use = -1;
	sList__Group_Item.RemoveAll();
}

//  [9/12/2013 Won]
CDlg_Log_List::~CDlg_Log_List()
{
	DeleteObject(m_Font);
}

void CDlg_Log_List::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_Log_List)
	DDX_Control(pDX, IDC_LIST_VIEW, m_List_View);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg_Log_List, CDialog)
	//{{AFX_MSG_MAP(CDlg_Log_List)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_VIEW, OnDblclkListView)
	ON_NOTIFY(NM_CLICK, IDC_LIST_VIEW, OnClickListView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDlg_Log_List message handlers

BOOL CDlg_Log_List::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_Font.CreatePointFont(100, _T("Arial"));
	SetFont(&m_Font, TRUE);

	SendMessageToDescendants(WM_SETFONT, (WPARAM)m_Font.m_hObject, MAKELONG(FALSE, 0), FALSE);
	return TRUE;  
}

void CDlg_Log_List::Init_Page(const bool active_upload)
{
	iDATA_CHANGE_FLAG = -1;
	iEDIT_MODE = -1;

	int x = iPos_SX;
	int y = iPos_SY + 40;
	int w = iPos_EX - iPos_SX;
	int h = iPos_EY - y;

	m_List_View.DeleteAllItems();

	// ...
	{
		int list_view_stype;

		list_view_stype  = LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES;
		list_view_stype += LVS_EX_ONECLICKACTIVATE|LVS_EX_UNDERLINEHOT;
		list_view_stype += LVS_EX_INFOTIP;

		m_List_View.SetExtendedStyle(list_view_stype);
	}

	// ...
	{
		iTable_COL_CNT = 8;
		sList_COL_TITLE.RemoveAll();

		CString col_name;
		int col_cx;
		int i;

		for(i=0;i<10;i++)
		{
			m_List_View.DeleteColumn(0);
		}

		for(i=0;i<iTable_COL_CNT;i++)
		{
			switch(i)
			{
				case 0:
					col_name = "No.";
					col_cx   = 60;
					break;

				case 1:
					col_name = "Channel";
					col_cx   = 300;
					break;

				case 2:
					col_name = "Type";
					col_cx   = 80;
					break;

				case 3:
					col_name = "Title";
					col_cx   = 300;
					break;

				case 4:
					col_name = "Mode";
					col_cx   = 80;
					break;

				case 5:
					col_name = "Index";
					col_cx   = 50;
					break;

				case 6:
					col_name = "CH-Type";
					col_cx   = 50;
					break;

				case 7:
					col_name = "Group";
					col_cx   = 120;
					break;

				default:
					continue;
			}

			sList_COL_TITLE.Add(col_name);

			if(i == 1)
			{
				m_List_View.InsertColumn(i,col_name,LVCFMT_LEFT,col_cx);
			}
			else
			{
				m_List_View.InsertColumn(i,col_name,LVCFMT_CENTER,col_cx);
			}		
		}

		if(active_upload)
		{
			CGX__CONFIG_CTRL cx_config_ctrl;

			CStringArray l_ch;
			CStringArray l_win;

			if(cx_config_ctrl->Get__LOG_INFO(iMODULE_ID,
										     l_ch,
										     l_win) > 0)
			{
				CString ch_name;
				CString win_name;

				int t_limit = l_ch.GetSize();

				for(int t=0; t<t_limit; t++)
				{
					ch_name  = l_ch[t];
					win_name = l_win[t];

					for(int k=t+1; k<t_limit; k++)
					{
						if(ch_name.Compare(l_ch[k]) <= 0)		continue;

						//
						l_ch[t]  = l_ch[k];
						l_win[t] = l_win[k];

						l_ch[k]  = ch_name;
						l_win[k] = win_name;

						ch_name  = l_ch[t];
						win_name = l_win[t];
					}
				}
			}

			// ...
			CString data;
			CString win_type;
			CString ch_type;
			int m_index;

			int count = 0;

			int limit = l_ch.GetSize();
			int i;
			int c;

			for(i=0;i<limit;i++)
			{
				if(Check__Win(l_win[i],win_type,m_index,ch_type) > 0)
				{
					for(c=0;c<iTable_COL_CNT;c++)
					{
						data = "";

						//
						if(c==0)	data.Format("%0003d",count+1);	// No.
						if(c==1)	data = l_ch[i];
						if(c==2)									// Type
						{
							if(win_type.Compare("E") == 0)		data = "EVENT";	
							else								data = "INTERVAL";	
						}
						if(c==3)	data = "";						// Title
						if(c==4)	data = "DISABLE";				// Check
						if(c==5)									// ID
						{
							data.Format("%1d",m_index);
						}
						if(c==6)
						{
							data = ch_type;
						}

						//
						if(c == 0)
						{
							m_List_View.InsertItem(count,data,0);
						}
						else
						{
							m_List_View.SetItem(count,c,LVIF_TEXT,data,0,0,0,0);
						}
					}

					count++;
				}
			}
		}

		// ...
	}

	m_List_View.MoveWindow(0,0,w-3,h-3);

	MoveWindow(x,y,w,h);
}

void CDlg_Log_List::Undo_Page(CString& time)
{
	CString file_data;

	// ...
	{
		CString log_path;
		log_path.Format("%s\\%s", sPara__DIR_LOG, "channel_list.csv");

		if(Macro__Get_File_Data(log_path, file_data) < 0)
		{	
			printf(" * CDlg_Log_List::Undo_Page() - Error ! \n");
			printf(" ** log_path <- [%s] \n", log_path);
			return;
		}

		file_data += (char) EOF;
	}

	// ...
	CStringArray list_channel;
	CStringArray list_title;
	CStringArray list_mode;
	CStringArray list_group;

	// ...
	{
		CString word = "";
		
		int command = -1;
		int para = 0;
		int flag = 1;

		int limit = file_data.GetLength();

		for(int i=0; i<limit; i++)
		{
			char ch = file_data.GetAt(i);

			if((ch == ',')
			|| (ch == '\n')
			|| (ch == EOF))
			{
				if(ch == ',')		para++;

				if(word.GetLength() > 0)
				{
					if(command > 0)
					{
						if(para == 1)
						{
							list_channel.Add(word);
							list_title.Add("");
							list_mode.Add("");
							list_group.Add("");
						}
						else if(para == 3)
						{
							int index = list_title.GetSize() - 1;

							if(index >= 0)	list_title[index] = word;
						}
						else if(para == 4)
						{
							int index = list_mode.GetSize() - 1;

							if(index >= 0)	list_mode[index] = word;
						}
						else if(para == 7)
						{
							if(iFlag__Group_Use > 0)
							{
								int index = list_group.GetSize() - 1;

								if(index >= 0)	list_group[index] = word;
							}
						}
					}
					else if(command == -1)
					{
						if(para == 1)
						{
							time = word;
						}
					}

					word = "";
				}
			}
			else
			{
				word += ch;
			}

			if(ch == '\n')
			{
				para = 0;

				if(command < 1)		command++;
			}

			if(ch == EOF)	flag = -1;
		}
	}

	iDATA_CHANGE_FLAG = -1;
	iEDIT_MODE = -1;

	// ...
	{
		CListCtrl* p_table = &m_List_View;
		p_table->SetRedraw(false);

		// ...
		CUIntArray   l__db_check;
		CStringArray l__db_name;

		// ...
		{
			int t_limit = p_table->GetItemCount();

			for(int t=0; t<t_limit; t++)
			{
				CString ch_name = p_table->GetItemText(t, DEF_COL__CH_NAME);

				l__db_check.Add(false);
				l__db_name.Add(ch_name);
			}
		}

		// ...
		{
			int t_limit = p_table->GetItemCount();
			int x_limit = list_channel.GetSize();

			for(int x=0; x<x_limit; x++)
			{
				CString db_name  = list_channel[x];
				CString db_title = list_title[x];
				CString db_mode  = list_mode[x];
				CString db_group = list_group[x];

				// ...
				bool active_check = false;
				int  active_index = -1;

				// ...
				{
					int db_limit = l__db_check.GetSize();
					int db_i;
					
					for(db_i=0; db_i<db_limit; db_i++)
					{
						if(l__db_check[db_i])									continue;
						if(db_name.CompareNoCase(l__db_name[db_i]) != 0)		continue;

						l__db_check[db_i] = true;
						active_index = db_i;
						active_check = true;
						break;
					}
				}				

				if(active_check)
				{
					if(db_title.GetLength() > 0)		p_table->SetItemText(active_index, DEF_COL__TITLE, db_title);
					else								p_table->SetItemText(active_index, DEF_COL__TITLE, db_name);

					p_table->SetItemText(active_index, DEF_COL__MODE,  db_mode);
					p_table->SetItemText(active_index, DEF_COL__GROUP, db_group);
				}
			}
		}

		p_table->SetRedraw(true);
	}
}

void CDlg_Log_List::Search_Item(const CString& s_item)
{
	CString ch_name;

	int limit = m_List_View.GetItemCount();
	int i;

	for(i=0;i<limit;i++)
	{
		ch_name = m_List_View.GetItemText(i,DEF_COL__CH_NAME);

		if(ch_name.Find(s_item) >= 0)
		{
			m_List_View.SetFocus();

			ListView_SetItemState(m_List_View.m_hWnd, -1, 0, LVIS_FOCUSED|LVIS_SELECTED);
			ListView_EnsureVisible(m_List_View.m_hWnd, i, FALSE); 
			ListView_SetItemState(m_List_View.m_hWnd, i, LVIS_FOCUSED|LVIS_SELECTED, LVIS_FOCUSED|LVIS_SELECTED);	
			return;
		}
	}
}

void CDlg_Log_List::Get_Search_Item(const CString& s_item,CStringArray& l_item)
{
	l_item.RemoveAll();

	// ...
	CString ch_name;

	int limit = m_List_View.GetItemCount();
	int i;

	for(i=0;i<limit;i++)
	{
		ch_name = m_List_View.GetItemText(i,DEF_COL__CH_NAME);
		if(ch_name.Find(s_item) < 0)		continue;

		l_item.Add(ch_name);
	}
}

int  CDlg_Log_List::Check__Win(const CString& win_str,
				 			   CString& win_type,
							   int& m_index,
							   CString& ch_type)
{
	int index;
	
	if(win_str.Find(':') >= 0)
	{
		index = win_str.Find('L');
		if(index >= 0)
		{
			CString data = win_str;
			data.SetAt(index,' ');
			
			if(data.Find('S') >= 0)
			{
				ch_type = "S";
			} 
			else if(data.Find('D') >= 0)
			{
				ch_type = "D";
			}
			else if(data.Find('A') >= 0)
			{
				ch_type = "A";
			}
			
			win_type = "L";
			m_index = atoi(data);
			return 1;
		}

		index = win_str.Find('E');
		if(index >= 0)
		{
			CString data = win_str;
			data.SetAt(index,' ');
			
			if(data.Find('S') >= 0)
			{
				ch_type = "S";
			} 
			else if(data.Find('D') >= 0)
			{
				ch_type = "D";
			}
			else if(data.Find('A') >= 0)
			{
				ch_type = "A";
			}
			
			win_type = "E";
			m_index = atoi(data);
			return 1;
		}
	} 
	else 
	{
		index = win_str.Find('L');
		if(index >= 0)
		{
			CString data = win_str;
			data.Delete(0,index+1);
			
			win_type = "L";
			m_index = atoi(data);
			
			ch_type = "A";
			return 1;
		}

		index = win_str.Find('E');
		if(index >= 0)
		{
			CString data = win_str;
			data.Delete(0,index+1);
			
			win_type = "E";
			m_index = atoi(data);

			ch_type = "A";
			return 1;
		}
	}

	return -1;
}

void CDlg_Log_List::OnClickListView(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LPNMITEMACTIVATE nia = (LPNMITEMACTIVATE) pNMHDR;

	int row = nia->iItem;
	int col = nia->iSubItem;

	if(iEDIT_MODE > 0)
	{
		if(col == DEF_COL__TITLE)
		{
			CGX__UTILITY_CTRL cx_utility_ctrl;

			CString title;
			CString in_data;
			CString out_data;

			title = "Input Title.";
			in_data = m_List_View.GetItemText(row,col);

			if(cx_utility_ctrl->Popup_Keyboard(title,in_data,out_data) > 0)
			{
				m_List_View.SetItemText(row,col,out_data);
				iDATA_CHANGE_FLAG = 1;
			}
		}
		else if(col == DEF_COL__MODE)
		{
			CGX__UTILITY_CTRL cx_utility_ctrl;

			CString title;
			CStringArray l_data;
			CString in_data;
			CString out_data;

			title = "Select Datalog Mode.";
			in_data = m_List_View.GetItemText(row,col);

			l_data.RemoveAll();
			l_data.Add("ENABLE");
			l_data.Add("DISABLE");

			if(cx_utility_ctrl->Popup__DIGITAL_PAD(title,l_data,in_data,out_data) > 0)
			{
				m_List_View.SetItemText(row,col,out_data);
				iDATA_CHANGE_FLAG = 1;
			}
		}
		else if(col == DEF_COL__GROUP)
		{
			if(iFlag__Group_Use > 0)
			{
				CGX__UTILITY_CTRL cx_utility_ctrl;

				CString title;
				CStringArray l_data;
				CString in_data;
				CString out_data;

				title = "Select Group Name";
				in_data = m_List_View.GetItemText(row,col);

				l_data.Copy(sList__Group_Item);
				l_data.InsertAt(0,"");

				if(cx_utility_ctrl->Popup__DIGITAL_PAD(title,l_data,in_data,out_data) > 0)
				{
					m_List_View.SetItemText(row,col,out_data);
					iDATA_CHANGE_FLAG = 1;
				}
			}
		}
	}

	*pResult = 0;
}

void CDlg_Log_List::OnDblclkListView(NMHDR* pNMHDR, LRESULT* pResult) 
{
	*pResult = 0;
}

void CDlg_Log_List::Get__SAVE_DATA(CString& file_data)
{
	CString bff;
	int c;

	file_data = "";

	// Column ...
	for(c=1;c<iTable_COL_CNT;c++)
	{
		file_data += sList_COL_TITLE[c];
		file_data += ",";
	}
	file_data += "\n";

	// Item ...
	int limit = m_List_View.GetItemCount();
	int i;

	for(i=0;i<limit;i++)
	{
		for(c=1;c<iTable_COL_CNT;c++)
		{
			file_data += m_List_View.GetItemText(i,c);
			file_data += ",";
		}

		file_data += "\n";
	}
}
