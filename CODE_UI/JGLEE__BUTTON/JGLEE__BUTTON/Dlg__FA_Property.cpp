// Dlg_FA_Property.cpp : implementation file
//

#include "stdafx.h"
#include "JGLEE__BUTTON.h"
#include "Dlg__FA_Property.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg__FA_Property dialog


CDlg__FA_Property::CDlg__FA_Property(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg__FA_Property::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlg__FA_Property)
	mStr_HSMS_Port = _T("");
	//}}AFX_DATA_INIT
}


void CDlg__FA_Property::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg__FA_Property)
	DDX_Control(pDX, IDC_PORT, m_Port);
	DDX_Control(pDX, IDC_COM, m_COM);
	DDX_Control(pDX, IDC_HSMS_MODE, m_HSMS_Mode);
	DDX_Control(pDX, IDC_HSMS_IP, m_IP);
	DDX_Control(pDX, IDC_CONNECTION, m_Connection);
	DDX_Text(pDX, IDC_PORT, mStr_HSMS_Port);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg__FA_Property, CDialog)
	//{{AFX_MSG_MAP(CDlg__FA_Property)
	ON_NOTIFY(IPN_FIELDCHANGED, IDC_HSMS_IP, OnFieldchangedHsmsIp)
	ON_CBN_EDITCHANGE(IDC_CONNECTION, OnEditchangeConnection)
	ON_CBN_SELCHANGE(IDC_CONNECTION, OnSelchangeConnection)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg__FA_Property message handlers

int CDlg__FA_Property::Get_IP_to_Field(char *ip,BYTE &field0,BYTE &field1,BYTE &field2,BYTE &field3)
{
	int		i, limit, count;
	char	ch, str_ch[2];
	CString word;

	field0 = 0;
	field1 = 0;
	field2 = 0;
	field3 = 0;

	count = -1;
	str_ch[1] = 0;
	limit = strlen(ip);
	for(i=0;i<=limit;i++)
	{
		if(i < limit)	ch = ip[i];
		else			ch = '.';

		if(ch == '.')
		{
			count++;

				 if(count == 0)		field0 = atoi(word);
			else if(count == 1)		field1 = atoi(word);
			else if(count == 2)		field2 = atoi(word);
			else if(count == 3)		field3 = atoi(word);

			word = "";
		}
		else
		{
			str_ch[0] = ch;
			word += str_ch;
		}
	}

	if(count < 3)	return -1;
	return 1;
}

BOOL CDlg__FA_Property::OnInitDialog() 
{
	CDialog::OnInitDialog();


	char connection[255], comm[255], hsms_mode[255], ip[255], port[255];
	BYTE field0, field1, field2, field3;
	
	GetPrivateProfileString("PROPERTY","CONNECTION","",connection,255,mPath);
	GetPrivateProfileString("PROPERTY","COMM",      "",comm,      255,mPath);
	GetPrivateProfileString("PROPERTY","HSMS_MODE", "",hsms_mode, 255,mPath);
	GetPrivateProfileString("PROPERTY","IP",        "",ip,        255,mPath);
	GetPrivateProfileString("PROPERTY","PORT",      "",port,      255,mPath);

	Get_IP_to_Field(ip,field0,field1,field2,field3);
	

	//////////////////////////////////////////
	m_Connection.AddString("SECSI RS232");
	m_Connection.AddString("HSMS");
	if(strcmp(connection,"HSMS") == 0)
	{
		m_Connection.SetCurSel(1);

		m_COM.EnableWindow(FALSE);

		m_HSMS_Mode.EnableWindow(TRUE);
		m_IP.EnableWindow(TRUE);
		m_Port.EnableWindow(TRUE);
	}
	else
	{
		m_Connection.SetCurSel(0);

		m_COM.EnableWindow(TRUE);

		m_HSMS_Mode.EnableWindow(FALSE);
		m_IP.EnableWindow(FALSE);
		m_Port.EnableWindow(FALSE);
	}
	
	m_COM.AddString("COM1");
	m_COM.AddString("COM2");
	m_COM.AddString("COM3");
	m_COM.AddString("COM4");
	m_COM.AddString("COM5");
	m_COM.AddString("COM6");
	m_COM.AddString("COM7");
	m_COM.AddString("COM8");
	m_COM.AddString("COM9");
	m_COM.AddString("COM10");
	if(strcmp(comm,"COM2") == 0)		m_COM.SetCurSel(1);
	else if(strcmp(comm,"COM3") == 0)	m_COM.SetCurSel(2);
	else if(strcmp(comm,"COM4") == 0)	m_COM.SetCurSel(3);
	else if(strcmp(comm,"COM5") == 0)	m_COM.SetCurSel(4);
	else if(strcmp(comm,"COM6") == 0)	m_COM.SetCurSel(5);
	else if(strcmp(comm,"COM7") == 0)	m_COM.SetCurSel(6);
	else if(strcmp(comm,"COM8") == 0)	m_COM.SetCurSel(7);
	else if(strcmp(comm,"COM9") == 0)	m_COM.SetCurSel(8);
	else if(strcmp(comm,"COM10") == 0)	m_COM.SetCurSel(9);
	else if(strcmp(comm,"COM1") == 0)	m_COM.SetCurSel(0);

	m_HSMS_Mode.AddString("PASSIVE");
	m_HSMS_Mode.AddString("ACTIVE");
	if(strcmp(hsms_mode,"PASSIVE") == 0)	m_HSMS_Mode.SetCurSel(0);
	else									m_HSMS_Mode.SetCurSel(1);

	m_IP.SetAddress(field0,field1,field2,field3);
	m_Port.ReplaceSel(port,FALSE);
	//////////////////////////////////////////

	return TRUE;
}

void CDlg__FA_Property::OnOK() 
{
	//////////////////////////////////////////
	UpdateData(TRUE);

	CString data;
	int     index;

	index = m_Connection.GetCurSel();
	if(index >= 0)
	{
		m_Connection.GetLBText(index,data);
		mStr_Connection = data;
	}

	index = m_COM.GetCurSel();
	if(index >= 0)
	{
		m_COM.GetLBText(index,data);
		mStr_COMM_Port = data;
	}
	
	index = m_HSMS_Mode.GetCurSel();
	if(index >= 0)
	{
		m_HSMS_Mode.GetLBText(index,data);
		mStr_HSMS_Mode = data;
	}

	BYTE field0, field1, field2, field3;
	m_IP.GetAddress(field0,field1,field2,field3);
	mStr_HSMS_IP.Format("%1d.%1d.%1d.%1d",field0,field1,field2,field3);
	
	UpdateData(FALSE);
	//////////////////////////////////////////

	CDialog::OnOK();
}

void CDlg__FA_Property::OnFieldchangedHsmsIp(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}

void CDlg__FA_Property::OnEditchangeConnection() 
{
}

void CDlg__FA_Property::OnSelchangeConnection() 
{
	CString data;
	int     index;

	index = m_Connection.GetCurSel();
	if(index >= 0)
	{
		m_Connection.GetLBText(index,data);
		
		if(data.Compare("HSMS") == 0)
		{
			m_COM.EnableWindow(FALSE);

			m_HSMS_Mode.EnableWindow(TRUE);
			m_IP.EnableWindow(TRUE);
			m_Port.EnableWindow(TRUE);
		}
		else
		{
			m_HSMS_Mode.EnableWindow(FALSE);
			m_IP.EnableWindow(FALSE);
			m_Port.EnableWindow(FALSE);

			m_COM.EnableWindow(TRUE);
		}
	}
}
