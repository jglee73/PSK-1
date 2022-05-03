#include "stdafx.h"
#include "Macro_Function.h"


// ...
int Macro__StringArrray_From_String(const CString& str_org_data,const CString& str_sep,CStringArray& l_data)
{
	CString str_data = str_org_data;

	l_data.RemoveAll();

	while(1)
	{
		int db_index = str_data.Find(str_sep);
		if(db_index < 0)
		{
			if(str_data.GetLength() > 0)
			{
				l_data.Add(str_data);
			}
			break;
		}

		CString str_token = str_data;			
		str_token.Delete(db_index, str_token.GetLength()-db_index);

		str_data.Delete(0, 1+db_index);

		if(db_index > 0)
		{
			l_data.Add(str_token);
		}
	}

	return 1;
}

int Macro__Hexa_From_String(const CString& str_data)
{
	int i_hexa = 0;

	int i_limit = str_data.GetLength();
	int i;

	for(i=0; i<i_limit; i++)
	{
		char ch = str_data[i];

		i_hexa *= 0x10;

		if((ch >= '0') && (ch <= '9'))
		{
			i_hexa += (ch - '0');
			continue;
		}
		if((ch >= 'A') && (ch <= 'F'))
		{
			i_hexa += ((ch - 'A') + 10);
			continue;
		}
		if((ch >= 'a') && (ch <= 'f'))
		{
			i_hexa += ((ch - 'a') + 10);
			continue;
		}		
	}

	return i_hexa;
}

CString Macro__Get_TwinCAT_Error_Code(const int err_code)
{
	CString err_msg;

	if(err_code <= 0)
	{
		err_msg.Format("(0x02X) No Error", err_code);
		return err_msg;
	}

	// 0x0000 : ERR_GROBAL
	if(err_code < 0x0500)
	{
		return _Macro__Get_Global_Error_Code(err_code);
	}

	// 0x0500 : ERR_ROUTER
	if(err_code < 0x0600)
	{
		err_msg.Format("(0x02X) ERR_ROUTER", err_code);
		return err_msg;
	}

	// 0x0600 : ERR_TASK
	if(err_code < 0x0700)
	{
		err_msg.Format("(0x02X) ERR_TASK", err_code);
		return err_msg;
	}

	// 0x0700 : ERR_ADS
	if(err_code < 0x0800)
	{
		return _Macro__Get_ADS_Error_Code(err_code);
	}

	// 0x0800 : ERR_SYSSMPLERRE
	{

	}

	//
	err_msg.Format("(0x02X) Unknown Error", err_code);
	return err_msg;
}

CString _Macro__Get_Global_Error_Code(const int err_code)
{
	CString err_msg;
	CString err_bff;

	err_msg.Format("Ox%04X (%1d) \n", err_code,err_code);

	switch(err_code)
	{
		case 1:
			err_bff = "Internal error";
			break;

		case 2:
			err_bff = "No Rtime";
			break;

		case 3:
			err_bff = "Allocation locked memory error";
			break;

		case 4:
			err_bff = "Insert mailbox error";
			err_msg += err_bff;
			err_msg += "\n";

			err_bff = "No ADS mailbox was available to process this message.";
			err_msg += err_bff;
			err_msg += "\n";

			err_bff = "Reduce the number of ADS calls (e.g ADS-Sum commands or Max Delay Parameter)";
			break;

		case 5:
			err_bff = "Wrong receive HMSG";
			break;

		case 6:
			err_bff = "target port not found";
			err_msg += err_bff;
			err_msg += "\n";

			err_bff = "ADS Server not started";
			break;

		case 7:
			err_bff = "target machine not found	Missing ADS routes";
			break;

		case 8:
			err_bff = "Unknown command ID";
			break;

		case 9:
			err_bff = "Bad task ID";
			break;

		case 10:
			err_bff = "No IO";
			break;

		case 11:
			err_bff = "Unknown ADS command";
			break;

		case 12:
			err_bff = "Win 32 error";
			break;

		case 13:
			err_bff = "Port not connected";
			break;

		case 14:
			err_bff = "Invalid ADS length";
			break;

		case 15:
			err_bff = "Invalid AMS Net ID";
			break;

		case 16:
			err_bff = "Low Installation level";
			break;

		case 17:
			err_bff = "No debug available";
			break;

		case 18:
			err_bff = "Port disabled";
			break;

		case 19:
			err_bff = "Port already connected";
			break;

		case 20:
			err_bff = "ADS Sync Win32 error";
			break;

		case 21:
			err_bff = "ADS Sync Timeout";
			break;

		case 22:
			err_bff = "ADS Sync AMS error";
			break;

		case 23:
			err_bff = "ADS Sync no index map";
			break;

		case 24:
			err_bff = "Invalid ADS port";
			break;

		case 25:
			err_bff = "No memory";
			break;

		case 26:
			err_bff = "TCP send error";
			break;

		case 27:
			err_bff = "Host unreachable";
			break;

		case 28:
			err_bff = "Invalid AMS fragment";
			break;

		default:
			err_bff = "Unknown error !";
			break;
	}

	err_msg += err_bff;
	err_msg += "\n";

	return err_msg;
}

CString _Macro__Get_ADS_Error_Code(const int err_code)
{
	CString err_msg;
	CString err_bff;

	err_msg.Format("Ox%04X (%1d) \n", err_code,err_code);

	switch(err_code)
	{
	case 1792:
		err_bff  = "error class <device error>";
		break;

	case 1793:
		err_bff  = "Service is not supported by server";
		break;

	case 1794:
		err_bff  = "invalid index group";
		break;

	case 1795:
		err_bff  = "invalid index offset";
		break;

	case 1796:
		err_bff  = "reading/writing not permitted";
		break;

	case 1797:
		err_bff  = "parameter size not correct";
		break;

	case 1798:
		err_bff  = "invalid parameter value(s)";
		break;

	case 1799:
		err_bff  = "device is not in a ready state";
		break;

	case 1800:
		err_bff  = "device is busy";
		break;

	case 1801:
		err_bff  = "invalid context (must be in Windows)";
		break;

	case 1802:
		err_bff  = "out of memory";
		break;

	case 1803:
		err_bff  = "invalid parameter value(s)";
		break;

	case 1804:
		err_bff  = "not found (files, ...)";
		break;

	case 1805:
		err_bff  = "syntax error in command or file";
		break;

	case 1806:
		err_bff  = "objects do not match";
		break;

	case 1807:
		err_bff  = "object already exists";
		break;

	case 1808:
		err_bff  = "symbol not found";
		break;

	case 1809:
		err_bff  = "symbol version invalid";
		err_msg += err_bff;
		err_msg += "\n";

		err_bff += "Onlinechange";
		err_msg += err_bff;
		err_msg += "\n";

		err_bff += "Release handle and get a new one";
		break;

	case 1810:
		err_bff  = "is in invalid state";
		break;

	case 1811:
		err_bff  = "AdsTransMode not supported";
		break;

	case 1812:
		err_bff  = "Notification handle is invalid";
		err_msg += err_bff;
		err_msg += "\n";

		err_bff += "Onlinechange";
		err_msg += err_bff;
		err_msg += "\n";

		err_bff  = "Release handle and get a new one";
		break;

	case 1813:
		err_bff  = "Notification client not registered";
		break;

	case 1814:
		err_bff  = "no more notification handles";
		break;

	case 1815:
		err_bff  = "size for watch too big";
		break;

	case 1816:
		err_bff  = "device not initialized";
		break;

	case 1817:
		err_bff  = "device has a timeout";
		break;

	case 1818:
		err_bff  = "query interface failed";
		break;

	case 1819:
		err_bff  = "wrong interface required";
		break;

	case 1820:
		err_bff  = "class ID is invalid";
		break;

	case 1821:
		err_bff  = "object ID is invalid";
		break;

	case 1822:
		err_bff  = "request is pending";
		break;

	case 1823:
		err_bff  = "request is aborted";
		break;

	case 1824:
		err_bff  = "signal warning";
		break;

	case 1825:
		err_bff  = "invalid array index";
		break;

	case 1826:
		err_bff  = "symbol not active";
		err_msg += err_bff;
		err_msg += "\n";

		err_bff += "Onlinechange";
		err_msg += err_bff;
		err_msg += "\n";

		err_bff += "Release handle and get a new one";
		break;

	case 1827:
		err_bff  = "access denied";
		break;

	case 1828:
		err_bff  = "missing license";
		err_msg += err_bff;
		err_msg += "\n";

		err_bff += "Activate license for TwinCAT 3 function";
		break;

	case 1836:
		err_bff  = "exception occured during system start";
		err_msg += err_bff;
		err_msg += "\n";

		err_bff += "Check each device transistions";
		break;

	case 1856:
		err_bff  = "Error class <client error>";
		break;

	case 1857:
		err_bff  = "invalid parameter at service";
		break;

	case 1858:
		err_bff  = "polling list is empty";
		break;

	case 1859:
		err_bff  = "var connection already in use";
		break;

	case 1860:
		err_bff  = "invoke ID in use";
		break;

	case 1861:
		err_bff  = "timeout elapsed";
		err_msg += err_bff;
		err_msg += "\n";

		err_bff += "ADS routes of sender and receiver and your  firewall setting";
		break;

	case 1862:
		err_bff  = "error in win32 subsystem";
		break;

	case 1863:
		err_bff  = "Invalid client timeout value";
		break;

	case 1864:
		err_bff  = "ads-port not opened";
		break;

	case 1872:
		err_bff  = "internal error in ads sync";
		break;

	case 1873:
		err_bff  = "hash table overflow";
		break;

	case 1874:
		err_bff  = "key not found in hash";
		break;

	case 1875:
		err_bff  = "no more symbols in cache";
		break;

	case 1876:
		err_bff  = "invalid response received";
		break;

	case 1877:
		err_bff  = "sync port is locked";
		break;

	default:
		err_bff = "Unknown error !";
		break;
	}

	err_msg += err_bff;
	err_msg += "\n";

	return err_msg;
}
