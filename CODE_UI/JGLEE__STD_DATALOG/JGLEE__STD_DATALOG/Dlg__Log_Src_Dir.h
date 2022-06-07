#if !defined(AFX_DLG__LOG_SRC_DIR_H__3317081F_4DC9_48E7_9EFF_BB2F90ED09BF__INCLUDED_)
#define AFX_DLG__LOG_SRC_DIR_H__3317081F_4DC9_48E7_9EFF_BB2F90ED09BF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg__Log_Src_Dir.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlg__Log_Src_Dir dialog

class CDlg__Log_Src_Dir : public CDialog
{
public:
	int iModuleID;

	CString sDir_Main;
	CString sDir_Sub;


// Construction
public:
	CDlg__Log_Src_Dir(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlg__Log_Src_Dir)
	enum { IDD = IDD_DLG__LOG_SRC_COPY };
	CComboBox	m_2st_List;
	CComboBox	m_1st_List;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg__Log_Src_Dir)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlg__Log_Src_Dir)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnEditchange1stFOLDER();
	afx_msg void OnEditchange2stFOLDER();
	afx_msg void OnSelchange1stFOLDER();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG__LOG_SRC_DIR_H__3317081F_4DC9_48E7_9EFF_BB2F90ED09BF__INCLUDED_)
