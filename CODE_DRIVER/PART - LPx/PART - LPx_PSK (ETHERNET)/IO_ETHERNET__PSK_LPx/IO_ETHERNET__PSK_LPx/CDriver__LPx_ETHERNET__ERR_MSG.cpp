#include "StdAfx.h"
#include "CDriver__LPx_ETHERNET.h"


//------------------------------------------------------------------------------------
CString CDriver__LPx_ETHERNET::Get__CANCEL_CODE_OF_NAK(const CString err_hexa)
{
	CString err_msg;

	if(err_hexa.CompareNoCase("01") == 0)
	{
		err_msg = "원점 미완료 (Initial 미완료)";
		return err_msg;
	}
	if(err_hexa.CompareNoCase("02") == 0)
	{
		err_msg = "Check sum[NAK]";
		return err_msg;
	}
	if(err_hexa.CompareNoCase("03") == 0)
	{
		err_msg = "Bad command[NAK]";
		return err_msg;
	}

	if(err_hexa.CompareNoCase("04") == 0)
	{
		err_msg = "지정된 Arm 은 없음";
		return err_msg;
	}
	if(err_hexa.CompareNoCase("05") == 0)
	{
		err_msg = "Error 발생 중";
		return err_msg;
	}
	if(err_hexa.CompareNoCase("06") == 0)
	{
		err_msg = "PAUSE 상태임";
		return err_msg;
	}
	if(err_hexa.CompareNoCase("07") == 0)
	{
		err_msg = "PAUSE 상태가 아님";
		return err_msg;
	}
	if(err_hexa.CompareNoCase("08") == 0)
	{
		err_msg = "Running 상태임";
		return err_msg;
	}
	if(err_hexa.CompareNoCase("09") == 0)
	{
		err_msg = "Running 상태가 아님";
		return err_msg;
	}

	if(err_hexa.CompareNoCase("0A") == 0)
	{
		err_msg = "Upper Blade 에 Wafer 가 있음";
		return err_msg;
	}
	if(err_hexa.CompareNoCase("0B") == 0)
	{
		err_msg = "Upper Blade 에 Wafer 가 없음";
		return err_msg;
	}
	if(err_hexa.CompareNoCase("0C") == 0)
	{
		err_msg = "Lower Blade 에 Wafer 가 있음";
		return err_msg;
	}
	if(err_hexa.CompareNoCase("0D") == 0)
	{
		err_msg = "Lower Blade 에 Wafer 가 없음";
		return err_msg;
	}
	if(err_hexa.CompareNoCase("0E") == 0)
	{
		err_msg = "지정된 Slot 에 Wafer 가 있음";
		return err_msg;
	}
	if(err_hexa.CompareNoCase("0F") == 0)
	{
		err_msg = "지정된 Slot 에 Wafer 가 없음";
		return err_msg;
	}

	if(err_hexa.CompareNoCase("10") == 0)
	{
		err_msg = "Robot Arm Extend.";
		return err_msg;
	}
	if(err_hexa.CompareNoCase("11") == 0)
	{
		err_msg = "Port Disable Mode.";
		return err_msg;
	}
	if(err_hexa.CompareNoCase("12") == 0)
	{
		err_msg = "Port Door Closed.";
		return err_msg;
	}
	if(err_hexa.CompareNoCase("13") == 0)
	{
		err_msg = "지정된 Port 에 FOUP 이 없음";
		return err_msg;
	}
	if(err_hexa.CompareNoCase("14") == 0)
	{
		err_msg = "Mapping 미완료 상태임";
		return err_msg;
	}
	if(err_hexa.CompareNoCase("15") == 0)
	{
		err_msg = "Position 이상";
		return err_msg;
	}
	if(err_hexa.CompareNoCase("15") == 0)
	{
		err_msg = "Position 이상";
		return err_msg;
	}
	if(err_hexa.CompareNoCase("16") == 0)
	{
		err_msg = "Port Error 발생 중";
		return err_msg;
	}
	if(err_hexa.CompareNoCase("17") == 0)
	{
		err_msg = "지정된 Port 는 RFID 를 사용하지 않음";
		return err_msg;
	}
	if(err_hexa.CompareNoCase("18") == 0)
	{
		err_msg = "RFID 에 Error 발생 중";
		return err_msg;
	}
	if(err_hexa.CompareNoCase("19") == 0)
	{
		err_msg = "지정한 Page 는 RFID 에 존재하지 않음";
		return err_msg;
	}
	if(err_hexa.CompareNoCase("1A") == 0)
	{
		err_msg = "RFID	에 지정한 Page 를 Write 할 수 없음";
		return err_msg;
	}
	if(err_hexa.CompareNoCase("1B") == 0)
	{
		err_msg = "RFID Reading";
		return err_msg;
	}
	if(err_hexa.CompareNoCase("1C") == 0)
	{
		err_msg = "AMHS Busy";
		return err_msg;
	}
	if(err_hexa.CompareNoCase("1D") == 0)
	{
		err_msg = "Port 초기화 미완료";
		return err_msg;
	}
	if(err_hexa.CompareNoCase("1E") == 0)
	{
		err_msg = "Port Running 상태 임";
		return err_msg;
	}
	
	err_msg = "Unknown Error";
	return err_msg;
}
