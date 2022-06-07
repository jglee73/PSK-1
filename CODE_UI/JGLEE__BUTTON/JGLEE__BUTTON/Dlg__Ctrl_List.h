#pragma once

#include "Resource.h"
#include "afxcmn.h"
#include "afxwin.h"


// CDlg__Ctrl_List dialog

class CDlg__Ctrl_List : public CDialog
{
	DECLARE_DYNAMIC(CDlg__Ctrl_List)

public:
	CDlg__Ctrl_List(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlg__Ctrl_List();

// Dialog Data
	enum { IDD = IDD_DLG_TABLE_LIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	afx_msg void OnNMClickListItem__Item_Table(NMHDR *pNMHDR, LRESULT *pResult);

	DECLARE_MESSAGE_MAP()

private:
	CListCtrl mCtrl__Item_Table;
	CImageList mImg__Info_Table;

	void _Init__Item_Table();
	void _Update__Item_Table(const CStringArray& l_data, const CStringArray& l_comment);

public:
	CStringArray sList__DATA;
	CStringArray sList__COMMENT;

	int iRESULT__SEL_INDEX;
	CString sRESULT__SEL_DATA;
	CButton mCtrl_Run;
};
