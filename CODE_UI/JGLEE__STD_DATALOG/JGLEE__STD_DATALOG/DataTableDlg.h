#if !defined(AFX_DATATABLEDLG_H__F3161E68_8EB4_4DFA_833F_6AAF462C3510__INCLUDED_)
#define AFX_DATATABLEDLG_H__F3161E68_8EB4_4DFA_833F_6AAF462C3510__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DataTableDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DataTableDlg dialog

class DataTableDlg : public CDialog
{
// Construction
public:

	POINT m_pst,m_pet;

	DataTableDlg(CWnd* pParent = NULL);   // standard constructor
	//  [9/13/2013 Won]
	~DataTableDlg();
	HFONT m_hFont;

	void Interface_Show();

 	BOOL m_bFirst;
// Dialog Data
	//{{AFX_DATA(DataTableDlg)
	enum { IDD = IDD_DIALOG1 };
	CListCtrl	m_ListView;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DataTableDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DataTableDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATATABLEDLG_H__F3161E68_8EB4_4DFA_833F_6AAF462C3510__INCLUDED_)
