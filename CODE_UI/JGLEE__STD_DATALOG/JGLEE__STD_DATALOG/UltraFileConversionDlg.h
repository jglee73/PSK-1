// UltraFileConversionDlg.h : header file
//

#if !defined(AFX_ULTRAFILECONVERSIONDLG_H__1D5A0AF5_9E77_40B2_B82B_1C3A1E06D53A__INCLUDED_)
#define AFX_ULTRAFILECONVERSIONDLG_H__1D5A0AF5_9E77_40B2_B82B_1C3A1E06D53A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"
#include "afxwin.h"


/////////////////////////////////////////////////////////////////////////////
// CUltraFileConversionDlg dialog

class CUltraFileConversionDlg : public CDialog
{
// Construction
public:
	CUltraFileConversionDlg(CWnd* pParent = NULL);	// standard constructor

	// ...
	int  Init_Table();
	void Upload_Inf();
//	int  Upload_File(int modulID,CString ext,int mode);
	//int  Upload_File(CString dir,CString ext,int mode);
//	int  Upload_Dir(CString dir);
	int  Upload_Dir(int modulID);

//	int  Upload_DirFile(CString dir_root,CString ext);
	int  Upload_DirFile(int modulID,CString ext);
	int  Upload_SubFile(CString sub_dir,CString ext,CString sub_file);
	
	int  Sort_Date();
	int  Sort_Time();
	int  Sort_Time_DirFile();
	int  Sort_Name_DirFile();
	int  Load_Date(CString date,CString order);
	int  Load_Dir(CString name,CString date);
	int  Get_ListIndex(CString date);
//	int  Make_LogFile(CString path,CString new_path);
	int	 Make_LogFile(CString sub_path, CString filename, CString ext, 
					  CString new_sub_path, CString new_fimename, CString new_exe,
					  const bool align_left);
	int	 Make_CSVLogFile(CString sub_path, CString filename, CString ext, 
					     CString new_sub_path, CString new_fimename, CString new_exe,
					     const bool align_left);
//	int  View_FileList();
	int  View_DirFileList();
	int  Fnc_FileConversion();
	int  Fnc_DirFileConversion();

	static int CALLBACK SortFunc1(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
	static int CALLBACK SortFunc2(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
	

	// ...
	int mVersion;

	CStringArray m_DirList;
	CStringArray m_FileList;
	CStringArray m_FileDateList;

	CStringArray mList_Date;
	CStringArray mList_Order;
	CStringArray mList_OrderDate;

	CStringArray mList_FileName;
	CStringArray mList_PathName;
	CStringArray mList_FileTime;
	CStringArray mList_FileOrder;

	CStringArray mFile_Name[100];
	CStringArray mFile_Time[100];
	CStringArray mFile_Order[100];

	CStringArray mTable_Interval_Item;
	CStringArray mTable_Event_Item;
	CStringArray mTable_Interval_Title;
	CStringArray mTable_Event_Title;

	// ...
	int m_Dir_ModuleID_From_Out;
	int m_Dir_ModuleID;
	int m_Seq_ModuleID;

	CString mExt;
	CString sPath__Log_Conversion;
	
	// ...
	int  Search_PathName(const CString& file,CString& new_file);

	//


// Dialog Data
	//{{AFX_DATA(CUltraFileConversionDlg)
	enum { IDD = IDD_ULTRAFILECONVERSION_DIALOG };
	CComboBox	m_ListTarget;
	CComboBox	m_ListSource;
	CListCtrl	m_ListBox;
	BOOL		m_CSVF;
	BOOL		m_TXTF;

	CButton mCheck__Align_Left;
	CButton mCheck__Align_Right;

	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUltraFileConversionDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CUltraFileConversionDlg)
	virtual BOOL OnInitDialog();
//	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnItemclickListBox(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickListBox(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnAll();
	afx_msg void OnClear();
	virtual void OnOK();
	afx_msg void OnEditchangeListSource();
	afx_msg void OnSelchangeListSource();
	virtual void OnCancel();
	afx_msg void OnColumnclickListBox(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCheck__Format_CSV();
	afx_msg void OnCheck__Format_TXT();

	afx_msg void OnBnClickedCheck__Align_Left();
	afx_msg void OnBnClickedCheck__Align_Right();

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ULTRAFILECONVERSIONDLG_H__1D5A0AF5_9E77_40B2_B82B_1C3A1E06D53A__INCLUDED_)
