#if !defined(AFX_DLG__LOG_TRG_DIR_H__D574FEEC_093C_4A71_B8C1_EA6FBAD20872__INCLUDED_)
#define AFX_DLG__LOG_TRG_DIR_H__D574FEEC_093C_4A71_B8C1_EA6FBAD20872__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg__Log_Trg_Dir.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlg__Log_Trg_Dir dialog

class CDlg__Log_Trg_Dir : public CDialog
{
public:
	int iModuleID;

	CString sCur_Dir;


// Construction
public:
	CDlg__Log_Trg_Dir(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlg__Log_Trg_Dir)
	enum { IDD = IDD_DLG__LOG_TRG_DIR };
	CButton	m_Check_D_Dir;
	CButton	m_Check_C_Dir;
	CString	m_Folder_Name;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg__Log_Trg_Dir)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlg__Log_Trg_Dir)
	virtual BOOL OnInitDialog();
	afx_msg void OnCheckCDir();
	afx_msg void OnCheckDDir();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG__LOG_TRG_DIR_H__D574FEEC_093C_4A71_B8C1_EA6FBAD20872__INCLUDED_)
