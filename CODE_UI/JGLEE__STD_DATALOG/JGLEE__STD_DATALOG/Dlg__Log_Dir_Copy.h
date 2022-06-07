#if !defined(AFX_DLG__LOG_DIR_COPY_H__FCF19ABE_F0A5_4DFE_81E4_5B9E6D5B2FF3__INCLUDED_)
#define AFX_DLG__LOG_DIR_COPY_H__FCF19ABE_F0A5_4DFE_81E4_5B9E6D5B2FF3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg__Log_Dir_Copy.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlg__Log_Dir_Copy dialog

class CDlg__Log_Dir_Copy : public CDialog
{
public:
	int iModuleID;
	int iFlag_FileCopy;

	// ...
	void Fnc__File_Copy();
	void Fnc__SubFile_Copy(const CString& ref_src);


// Construction
public:
	CDlg__Log_Dir_Copy(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlg__Log_Dir_Copy)
	enum { IDD = IDD_DLG__LOG_DIR_COPY };
	CButton	m_Bttn_Cancel;
	CButton	m_Bttn_FileCopy;
	CString	m_Src_Dir_Path;
	CString	m_Trg_Dir_Path;
	CString	m_Copy_Process_Data;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg__Log_Dir_Copy)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlg__Log_Dir_Copy)
	virtual BOOL OnInitDialog();
	afx_msg void OnBttnSrcDir();
	afx_msg void OnBttnTrgDir();
	virtual void OnOK();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void Macro__CreateDir(const CString& str_path);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG__LOG_DIR_COPY_H__FCF19ABE_F0A5_4DFE_81E4_5B9E6D5B2FF3__INCLUDED_)
