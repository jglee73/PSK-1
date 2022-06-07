#pragma once

#include "resource.h"


class CDlg_Log_List : public CDialog
{
public:
	//.....
	int iMODULE_ID;

	int iPos_SX;
	int iPos_SY;
	int iPos_EX;
	int iPos_EY;

	CStringArray sList_COL_TITLE;
	int iTable_COL_CNT;
	int iEDIT_MODE;
	int iDATA_CHANGE_FLAG;

	CString sPara__DIR_LOG;

	int iFlag__Group_Use;
	CStringArray sList__Group_Item;

	// ...
	void Init_Page(const bool active_upload);
	void Undo_Page(CString& time);
	void Search_Item(const CString& s_item);
	void Get_Search_Item(const CString& s_item,CStringArray& l_item);

	int  Check__Win(const CString& win_str,
					CString& win_type,
					int& m_index,
					CString& ch_type);

	void Get__SAVE_DATA(CString& file_data);
	//


	// Construction
public:
	CDlg_Log_List(CWnd* pParent = NULL);   // standard constructor
	//  [9/12/2013 Won]
	~CDlg_Log_List();

	CFont m_Font;

	// Dialog Data
	//{{AFX_DATA(CDlg_Log_List)
	enum { IDD = IDD_DLG_LOG_LIST };
	CListCtrl	m_List_View;
	//}}AFX_DATA

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_Log_List)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlg_Log_List)
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkListView(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickListView(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
