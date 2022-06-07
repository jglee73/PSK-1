#pragma once


/////////////////////////////////////////////////////////////////////////////
// CDlg_Search_List dialog

class CDlg_Search_List : public CDialog
{
public:
	CStringArray sList_Item;
	CString sSel_Name;


	// Construction
public:
	CDlg_Search_List(CWnd* pParent = NULL);   // standard constructor

	// Dialog Data
	//{{AFX_DATA(CDlg_Search_List)
	enum { IDD = IDD_DLG_SEARCH_LIST };
	CButton	m_Bttn_OK;
	CListBox	m_List_View;
	//}}AFX_DATA


	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_Search_List)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlg_Search_List)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
