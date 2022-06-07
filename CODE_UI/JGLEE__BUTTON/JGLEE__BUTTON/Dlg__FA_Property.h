#if !defined(AFX_DLG_FA_PROPERTY_H__2CFC60B6_ACA3_4EA0_8234_A600035025B8__INCLUDED_)
#define AFX_DLG_FA_PROPERTY_H__2CFC60B6_ACA3_4EA0_8234_A600035025B8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_FA_Property.h : header file
//

#include "Resource.h"


/////////////////////////////////////////////////////////////////////////////
// CDlg__FA_Property dialog

class CDlg__FA_Property : public CDialog
{
// Construction
public:
	CDlg__FA_Property(CWnd* pParent = NULL);   // standard constructor

	CString mPath;

	CString mStr_Connection;
	CString mStr_COMM_Port;
	CString mStr_HSMS_Mode;
	CString mStr_HSMS_IP;

	int Get_IP_to_Field(char *ip,BYTE &field0,BYTE &field1,BYTE &field2,BYTE &field3);


// Dialog Data
	//{{AFX_DATA(CDlg__FA_Property)
	enum { IDD = IDD_DLG_FA_PROPERTY };
	CEdit	m_Port;
	CComboBox	m_COM;
	CComboBox	m_HSMS_Mode;
	CIPAddressCtrl	m_IP;
	CComboBox	m_Connection;
	CString	mStr_HSMS_Port;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg__FA_Property)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlg__FA_Property)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnFieldchangedHsmsIp(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEditchangeConnection();
	afx_msg void OnSelchangeConnection();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_FA_PROPERTY_H__2CFC60B6_ACA3_4EA0_8234_A600035025B8__INCLUDED_)
