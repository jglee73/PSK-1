#include "StdAfx.h"
#include "CObj__OVATION_2560.h"


union _hex_to_short
{
	UCHAR ucGet_Data[2];
	unsigned short usCvrtData;
};

union _hex_to_short4
{
	UCHAR ucGet_Data[4];
	DWORD dwCvrtData;
};


//--------------------------------------------------------------------------------
int CObj__OVATION_2560
::__Read__ANALOG(const CString& var_name, 
				 const CDS_IO__CHANNEL_INFO& io_info, 
				 double& read_data)
{
	int n_trans_data_len;
	int n_calced_data_len;

	int nSendDataSize;
	int nRecvDataSize;

	UCHAR ucACK = ACK;

	// -------------- Message Format -------------------------
	// header  (1byte : 11111xxx는 address, xxxxx111은 data 길이, 여기서 x는 유효하지 않음.)
	// Command (1byte) 
	// Optional(1byte)
	// data    (0~255 bytes)
	// checksum(1byte : header ~ data까지 XOR)
	// -------------------------------------------------------

	UCHAR SendData[MAX_DATA_LENGTH] = { 0, };
	UCHAR RecvData[MAX_DATA_LENGTH] = { 0, };
	_hex_to_short  data_convers;
	_hex_to_short4 data_convers4;

	int n_mask_data_length = 0x07;			// xxxxx111 에서 뒤의 3개의 bit만 유효 하므로..
	int n_dev_add = m_nAddress << 3;		// 하위 3개의 비트는 버림.

	
	if(aiCH__ForwardPower->Check__VARIABLE_NAME(var_name) > 0)				// Forward Power
	{
		n_trans_data_len  = 0;
		n_calced_data_len = n_mask_data_length & n_trans_data_len;

		SendData[HEADER] = n_dev_add | n_calced_data_len;
		SendData[CMD]    = 165;
		SendData[OPTION] = Check_Sum(SendData, 2);

		nSendDataSize = 3;
		nRecvDataSize = 6;

		Fnc__WRITE_LOG("var_name[%s], MAKE_PACKET: 0x%02X, 0x%02X, 0x%02X", 
					    var_name,
						SendData[HEADER],
						SendData[CMD],
						SendData[OPTION]);
	}
	else if(aiCH__ReflectPower->Check__VARIABLE_NAME(var_name) > 0)			// Reflect Power
	{
		n_trans_data_len  = 0;
		n_calced_data_len = n_mask_data_length & n_trans_data_len;

		SendData[HEADER] = n_dev_add | n_calced_data_len;
		SendData[CMD]    = 166;
		SendData[OPTION] = Check_Sum(SendData, 2);

		nSendDataSize = 3;
		nRecvDataSize = 6;

		Fnc__WRITE_LOG("var_name[%s], MAKE_PACKET: 0x%02X, 0x%02X, 0x%02X", 
						var_name,
						SendData[HEADER],
						SendData[CMD],
						SendData[OPTION]);
	}
	else if(aiCH__DeliveredPower->Check__VARIABLE_NAME(var_name) > 0)		// Delivered Power
	{
		n_trans_data_len  = 0;
		n_calced_data_len = n_mask_data_length & n_trans_data_len;

		SendData[HEADER] = n_dev_add | n_calced_data_len;
		SendData[CMD]    = 167;
		SendData[OPTION] = Check_Sum(SendData, 2);

		nSendDataSize = 3;
		nRecvDataSize = 6;

		Fnc__WRITE_LOG("var_name[%s], MAKE_PACKET: 0x%02X, 0x%02X, 0x%02X", 
						var_name,
						SendData[HEADER],
						SendData[CMD],
						SendData[OPTION]);
	}
	else if(aiCH__WhenOn_Actual_Frequency->Check__VARIABLE_NAME(var_name) > 0)		// Read When TurnOn Actual Frequency !!
	{
		n_trans_data_len  = 0;
		n_calced_data_len = n_mask_data_length & n_trans_data_len;

		SendData[HEADER] = n_dev_add | n_calced_data_len;
		SendData[CMD]    = 147;
		SendData[OPTION] = Check_Sum(SendData, 2);

		nSendDataSize = 3;
		nRecvDataSize = 8;

		Fnc__WRITE_LOG("var_name[%s], MAKE_PACKET: 0x%02X, 0x%02X, 0x%02X", 
						var_name,
						SendData[HEADER],
						SendData[CMD],
						SendData[OPTION]);
	}
	else if(aiCH__Ps_Frequency->Check__VARIABLE_NAME(var_name) > 0)		// Read Pulsing Frequency !!
	{
		n_trans_data_len  = 0;
		n_calced_data_len = n_mask_data_length & n_trans_data_len;

		SendData[HEADER] = n_dev_add | n_calced_data_len;
		SendData[CMD]    = 193;
		SendData[OPTION] = Check_Sum(SendData, 2);

		nSendDataSize = 3;
		nRecvDataSize = 8;

		Fnc__WRITE_LOG("var_name[%s], MAKE_PACKET: 0x%02X, 0x%02X, 0x%02X", 
			var_name,
			SendData[HEADER],
			SendData[CMD],
			SendData[OPTION]);
	}
	else if(aiCH__Ps_Duty->Check__VARIABLE_NAME(var_name) > 0)		// Read Pulsing Duty !!
	{
		n_trans_data_len  = 0;
		n_calced_data_len = n_mask_data_length & n_trans_data_len;

		SendData[HEADER] = n_dev_add | n_calced_data_len;
		SendData[CMD]    = 196;
		SendData[OPTION] = Check_Sum(SendData, 2);

		nSendDataSize = 3;
		nRecvDataSize = 6;

		Fnc__WRITE_LOG("var_name[%s], MAKE_PACKET: 0x%02X, 0x%02X, 0x%02X", 
			var_name,
			SendData[HEADER],
			SendData[CMD],
			SendData[OPTION]);
	}
	//else if(aiCH__Error_Status->Check__VARIABLE_NAME(var_name) > 0)		// Read When TurnOn Actual Frequency !!
	//{
	//	n_trans_data_len  = 0;
	//	n_calced_data_len = n_mask_data_length & n_trans_data_len;

	//	SendData[HEADER] = n_dev_add | n_calced_data_len;
	//	SendData[CMD]    = 223;
	//	SendData[OPTION] = 1;
	//	SendData[OPTION+1] = Check_Sum(SendData, 3);

	//	nSendDataSize = 4;
	//	nRecvDataSize = 1;

	//	Fnc__WRITE_LOG("fnc_name[%s], MAKE_PACKET: 0x%02X, 0x%02X, 0x%02X, 0x%02X", 
	//		var_name,
	//		SendData[HEADER],
	//		SendData[CMD],
	//		SendData[OPTION],
	//		SendData[OPTION+1]);
	//}

	//Fnc__WRITE_LOG("Read_Analog_RecvCommand_Time_Check_Start");	//20181227 @pck
	if(RecvCommand(SendData, RecvData, nSendDataSize, nRecvDataSize) < 0)
	{
		Fnc__WRITE_LOG("Send Command Failed(%s)", var_name);

		read_data = 0.0;
		return 1;	// Unknown 써주기 위해... 주석..
	}
	// [ACK][HEADER][CMD][DATA][CHKSUM]
	//Fnc__WRITE_LOG("Read_Analog_RecvCommand_Time_Check_Mid1");	//20181227 @pck

	if((aiCH__ForwardPower->Check__VARIABLE_NAME(var_name)   > 0)
	|| (aiCH__ReflectPower->Check__VARIABLE_NAME(var_name)   > 0)
	|| (aiCH__DeliveredPower->Check__VARIABLE_NAME(var_name) > 0)
	|| (aiCH__Ps_Duty->Check__VARIABLE_NAME(var_name) > 0))
	{
		data_convers.ucGet_Data[0] = RecvData[3];
		data_convers.ucGet_Data[1] = RecvData[4];

		read_data = data_convers.usCvrtData;
	}
	else if((aiCH__WhenOn_Actual_Frequency->Check__VARIABLE_NAME(var_name) > 0)
	||		(aiCH__Ps_Frequency->Check__VARIABLE_NAME(var_name) > 0))
	{
		data_convers4.ucGet_Data[0] = RecvData[3];
		data_convers4.ucGet_Data[1] = RecvData[4];
		data_convers4.ucGet_Data[2] = RecvData[5];
		data_convers4.ucGet_Data[3] = RecvData[6];

		read_data = data_convers4.dwCvrtData;
	}

	CString var_data;
	var_data.Format("%.1f", read_data);
	if(aiCH__ForwardPower->Check__VARIABLE_NAME(var_name)   > 0)
	{
		aCH__FWD_Power->Set__DATA(var_data);
	}
	else if (aiCH__ReflectPower->Check__VARIABLE_NAME(var_name)   > 0)
	{
		aCH__REFL_Power->Set__DATA(var_data);
	}

	//Fnc__WRITE_LOG("Read_Analog_RecvCommand_Time_Check_End");	//20181227 @pck
	/*
	if((aiCH__ForwardPower->Check__VARIABLE_NAME(var_name)   > 0)
	|| (aiCH__ReflectPower->Check__VARIABLE_NAME(var_name)   > 0)
	|| (aiCH__DeliveredPower->Check__VARIABLE_NAME(var_name) > 0))
	{
		data_convers.ucGet_Data[0] = RecvData[3];
		data_convers.ucGet_Data[1] = RecvData[4];

		read_data = data_convers.usCvrtData;
	}
	else if(aiCH__WhenOn_Actual_Frequency->Check__VARIABLE_NAME(var_name) > 0)
	{
		data_convers4.ucGet_Data[0] = RecvData[3];
		data_convers4.ucGet_Data[1] = RecvData[4];
		data_convers4.ucGet_Data[2] = RecvData[5];
		data_convers4.ucGet_Data[3] = RecvData[6];

		read_data = data_convers4.dwCvrtData;
	}
	*/

	mX_Serial->CHAR__SEND(&ucACK, 1);
	return 1;
}

int CObj__OVATION_2560
::__Read__DIGITAL(const CString& var_name,
				  const CDS_IO__CHANNEL_INFO& io_info, 
				  CString& read_data,
				  int& item_index)
{
	double read_value;
	int n_trans_data_len;
	int n_calced_data_len;

	int nSendDataSize;
	int nRecvDataSize;

	UCHAR ucACK = ACK;

	// -------------- Message Format -------------------------
	// header  (1byte : 11111xxx 는 address, xxxxx111은 data 길이, 여기서 x는 유효하지 않음.)
	// Command (1byte) 
	// Optional(1byte)
	// data    (0~255 bytes)
	// checksum(1byte : header ~ data 까지 XOR)
	// -------------------------------------------------------

	UCHAR SendData[MAX_DATA_LENGTH] = { 0, };
	UCHAR RecvData[MAX_DATA_LENGTH] = { 0, };

	int n_mask_data_length = 0x07;			// xxxxx111 에서 뒤의 3개의 bit만 유효 하므로..
	int n_dev_add = m_nAddress << 3;		// 하위 3개의 비트는 버림.

	_hex_to_short  converse2;

	if(diCH__COMM_STS->Check__VARIABLE_NAME(var_name) > 0)
	{
		if(m_nCommSts == ONLINE)	read_data = "Online";
		else						read_data = "Offline";

		return 1;
	}
	
	if(diCH__CONTROL_MODE->Check__VARIABLE_NAME(var_name) > 0)
	{
		n_trans_data_len  = 0;
		n_calced_data_len = n_mask_data_length & n_trans_data_len;

		SendData[HEADER] = n_dev_add | n_calced_data_len;
		SendData[CMD]    = 155;
		SendData[OPTION] = Check_Sum(SendData, 2);

		nSendDataSize = 3;
		nRecvDataSize = 5;

		Fnc__WRITE_LOG("var_name[%s], MAKE_PACKET: 0x%02X, 0x%02X, 0x%02X", 
						var_name,
						SendData[HEADER],
						SendData[CMD],
						SendData[OPTION]);
	}
	else if(diCH__Process_Status->Check__VARIABLE_NAME(var_name) > 0)			// "Unknown ReadOk"
	{
		n_trans_data_len  = 0;
		n_calced_data_len = n_mask_data_length & n_trans_data_len;

		SendData[HEADER] = n_dev_add | n_calced_data_len;
		SendData[CMD]    = 162;
		SendData[OPTION] = Check_Sum(SendData, 2);

		nSendDataSize = 3;
		nRecvDataSize = 8;

		Fnc__WRITE_LOG("var_name[%s], MAKE_PACKET: 0x%02X, 0x%02X, 0x%02X", 
						var_name,
						SendData[HEADER],
						SendData[CMD],
						SendData[OPTION]);
	}
	else if(diCH__Pulsing_Status->Check__VARIABLE_NAME(var_name) > 0)			// "false true"
	{
		WORD  wSET_DATA;

		n_trans_data_len  = 2;
		n_calced_data_len = n_mask_data_length & n_trans_data_len;

		wSET_DATA = (WORD)RF_Ps_Request;

		SendData[HEADER] = n_dev_add | n_calced_data_len;
		SendData[CMD]    = 172;
		SendData[OPTION]   = LOBYTE(wSET_DATA) ; 
		SendData[OPTION+1] = HIBYTE(wSET_DATA) ;
		SendData[OPTION+2] = Check_Sum(SendData, 4);				// checksum을 제외한 갯수..

		nSendDataSize = 5;
		nRecvDataSize = 8;

		Fnc__WRITE_LOG("var_name[%s], MAKE_PACKET: 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X", 
			var_name,
			SendData[HEADER],
			SendData[CMD],
			SendData[OPTION],
			SendData[OPTION+1],
			SendData[OPTION]+2);
	}

	//Fnc__WRITE_LOG("Read_Digital_RecvCommand_Time_Check_Start");	//20181227 @pck
	if(RecvCommand(SendData, RecvData, nSendDataSize, nRecvDataSize) < 0)
	{
		Fnc__WRITE_LOG("Send Command Failed(%s)", var_name);
		
		read_data = "Unknown";
		return 1;	
	}
	//Fnc__WRITE_LOG("Read_Digital_RecvCommand_Time_Check_Mid1");	//20181227 @pck
	if(diCH__CONTROL_MODE->Check__VARIABLE_NAME(var_name) > 0)				// "Unknown Local Remote"
	{
			 if(RecvData[3] == 2)	read_data = "Remote";
		else if(RecvData[3] == 4)	read_data = "Local";
		else						read_data = "Unknown";
	}
	else if(diCH__Process_Status->Check__VARIABLE_NAME(var_name) > 0)		// "Unknown ReadOk"
	{
		int nRet_Bit_Sts;

		//Byte[3], bit 0
		{
			nRet_Bit_Sts = Get_Bit_Sts(RecvData[3], 0);

				 if(nRet_Bit_Sts == 0)	vdiCH__Tunning_Status->Set__DATA("NotTuned");
			else if(nRet_Bit_Sts == 1)	vdiCH__Tunning_Status->Set__DATA("Tuned");
			else						vdiCH__Tunning_Status->Set__DATA("Unknown");
		}
		//Byte[3], bit 1
		{
			nRet_Bit_Sts = Get_Bit_Sts(RecvData[3], 1);
			
			if(nRet_Bit_Sts == 1)		vdiCH__SetPoint_Ramp->Set__DATA("RampInProgress");
			else						vdiCH__SetPoint_Ramp->Set__DATA("Unknown");
		}
		//Byte[3], bit 5
		{
			nRet_Bit_Sts = Get_Bit_Sts(RecvData[3], 5);
			
				 if(nRet_Bit_Sts == 0)	vdiCH__RFOutput_Power->Set__DATA("Off");
			else if(nRet_Bit_Sts == 1)	vdiCH__RFOutput_Power->Set__DATA("On");
			else						vdiCH__RFOutput_Power->Set__DATA("Unknown");
		}
		//Byte[3], bit 6
		{
			nRet_Bit_Sts = Get_Bit_Sts(RecvData[3], 6);
			
				 if(nRet_Bit_Sts == 0)	vdiCH__RFOn_Request->Set__DATA("Off");
			else if(nRet_Bit_Sts == 1)	vdiCH__RFOn_Request->Set__DATA("On");
			else						vdiCH__RFOn_Request->Set__DATA("Unknown");
		}
		//Byte[3], bit 7
		{
			nRet_Bit_Sts = Get_Bit_Sts(RecvData[3], 7);
			
				 if(nRet_Bit_Sts == 0)	vdiCH__SetPoint_Tolerance->Set__DATA("InTolerance");
			else if(nRet_Bit_Sts == 1)	vdiCH__SetPoint_Tolerance->Set__DATA("OutOfTolerance");
			else						vdiCH__SetPoint_Tolerance->Set__DATA("Unknown");
		}
		//Byte[4], bit 3
		{
			nRet_Bit_Sts = Get_Bit_Sts(RecvData[4], 3);
			
			if(nRet_Bit_Sts == 1)		vdiCH__ColdPlate_OverTemp_Fault->Set__DATA("Fault");
			else						vdiCH__ColdPlate_OverTemp_Fault->Set__DATA("Normal");
		}
		//Byte[4], bit 7
		{
			nRet_Bit_Sts = Get_Bit_Sts(RecvData[4], 7);
			
				 if(nRet_Bit_Sts == 0)	vdiCH__Interlock_Open->Set__DATA("Closed");
			else if(nRet_Bit_Sts == 1)	vdiCH__Interlock_Open->Set__DATA("Open");
			else						vdiCH__Interlock_Open->Set__DATA("Unknown");
		}
		// Byte[5] Reserved..
		{

		}
		// Byte[6], bit 1
		{
			nRet_Bit_Sts = Get_Bit_Sts(RecvData[6], 1);
			
			if(nRet_Bit_Sts == 1)		vdiCH__Inverter_Ready->Set__DATA("NotReady");
			else						vdiCH__Inverter_Ready->Set__DATA("Unknown");
		}
		// Byte[6], bit 5
		{
			nRet_Bit_Sts = Get_Bit_Sts(RecvData[6], 5);
			
				 if(nRet_Bit_Sts == 0)	vdiCH__Fault_Status->Set__DATA("Normal");
			else if(nRet_Bit_Sts == 1)	vdiCH__Fault_Status->Set__DATA("Fault");
			else						vdiCH__Fault_Status->Set__DATA("Unknown");
		}
		// Byte[6], bit 6
		{
			nRet_Bit_Sts = Get_Bit_Sts(RecvData[6], 5);
			
				 if(nRet_Bit_Sts == 0)	vdiCH__Warning_Status->Set__DATA("Normal");
			else if(nRet_Bit_Sts == 1)	vdiCH__Warning_Status->Set__DATA("Warning");
			else						vdiCH__Warning_Status->Set__DATA("Unknown");
		}
		read_data = "ReadOK";
	}
	else if (diCH__Pulsing_Status->Check__VARIABLE_NAME(var_name) > 0)	// false true
	{
		if		(RecvData[3] == 0)
		{
			read_data = "Disable";
			RF_Ps_state = 0;
		}
		else if	(RecvData[3] == 1)
		{
			read_data = "Enable";
			RF_Ps_state = 1;
		}
	}

	//Fnc__WRITE_LOG("Read_Digital_RecvCommand_Time_Check_End");	//20181227 @pck
	mX_Serial->CHAR__SEND(&ucACK, 1);
	return 1;
}

int CObj__OVATION_2560
::__Read__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, CString& read_data)
{

	return 1;
}


//--------------------------------------------------------------------------------
int CObj__OVATION_2560
::__Write__ANALOG(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const double set_data)
{
	int n_trans_data_len;
	int n_calced_data_len;

	int nSendDataSize;
	int nRecvDataSize;

	// -------------- Message Format -------------------------
	// header  (1byte : 11111xxx 는 address, xxxxx111은 data 길이, 여기서 x는 유효하지 않음.)
	// Command (1byte) 
	// Optional(1byte)
	// data    (0~255 bytes)
	// checksum(1byte : header ~ data 까지 XOR)
	// -------------------------------------------------------

	UCHAR SendData[MAX_DATA_LENGTH] = { 0, };
	UCHAR RecvData[MAX_DATA_LENGTH] = { 0, };

	int   n_mask_data_length = 0x07;	// xxxxx111 에서 뒤의 3개의 bit만 유효 하므로..
	int   n_dev_add = m_nAddress << 3;	// 하위 3개의 비트는 버림.

	DWORD dwSET_DATA;
	WORD  wSET_DATA;
	WORD  wMode;
	WORD  wRamp_Up;
	WORD  wRamp_Down;
	WORD   wLO;
	WORD   wHI;

	Fnc__WRITE_LOG("check_log : m_nAddress[%d]", m_nAddress);

	if(aoCH__SetPower->Check__VARIABLE_NAME(var_name) > 0)
	{
		wSET_DATA = (WORD)set_data;

		n_trans_data_len  = 2;
		n_calced_data_len = n_mask_data_length & n_trans_data_len;

		SendData[HEADER]   = n_dev_add | n_calced_data_len;
		SendData[CMD]      = 8;
		SendData[OPTION]   = LOBYTE(wSET_DATA) ; 
		SendData[OPTION+1] = HIBYTE(wSET_DATA) ;
		SendData[OPTION+2] = Check_Sum(SendData, 4);				// checksum을 제외한 갯수..

		nSendDataSize = 5;
		nRecvDataSize = 5;

		Fnc__WRITE_LOG("var_name[%s], MAKE_PACKET: 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X", 
						var_name,
						SendData[HEADER],   
						SendData[CMD],
						SendData[OPTION],   
						SendData[OPTION+1], 
						SendData[OPTION+2]);
	}
	else if(aoCH__Power_Limit->Check__VARIABLE_NAME(var_name) > 0)
	{
		wSET_DATA;
		wSET_DATA = (WORD)set_data;

		n_trans_data_len  = 2;
		n_calced_data_len = n_mask_data_length & n_trans_data_len;

		SendData[HEADER]   = n_dev_add | n_calced_data_len;
		SendData[CMD]      = 4;
		SendData[OPTION]   = LOBYTE(wSET_DATA) ; 
		SendData[OPTION+1] = HIBYTE(wSET_DATA) ;
		SendData[OPTION+2] = Check_Sum(SendData, 4);					// checksum을 제외한 갯수..

		nSendDataSize = 5;
		nRecvDataSize = 5;

		Fnc__WRITE_LOG("var_name[%s], MAKE_PACKET: 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X", 
						var_name,
						SendData[HEADER],   
						SendData[CMD],
						SendData[OPTION],   
						SendData[OPTION+1], 
						SendData[OPTION+2]);
	}
	else if(aoCH__RampUp_Time->Check__VARIABLE_NAME(var_name) > 0)		// Ramp Up Time ...
	{
		wSET_DATA  = (WORD)set_data;

		if(vdoCH__Ramp_Mode->Check__DATA("Disable") > 0)
		{
			wMode = 0x00;
			wSET_DATA = 0x00;
		}
		else if(vdoCH__Ramp_Mode->Check__DATA("WattSec") > 0)
		{
			wMode = 0x01;
		}
		else if(vdoCH__Ramp_Mode->Check__DATA("Timed") > 0)
		{
			wMode = 0x02;
		}

		wRamp_Up   = wSET_DATA;
		wRamp_Down = 1000;		// 1000 ms

		n_trans_data_len  = 6;
		n_calced_data_len = n_mask_data_length & n_trans_data_len;

		SendData[HEADER]   = n_dev_add | n_calced_data_len;
		SendData[CMD]      = 31;

		// Mode
		SendData[OPTION]   = LOBYTE(wMode); 
		SendData[OPTION+1] = HIBYTE(wMode);

		// Ramp Up
		SendData[OPTION+2] = LOBYTE(wRamp_Up); 
		SendData[OPTION+3] = HIBYTE(wRamp_Up);

		// Ramp Down
		SendData[OPTION+4] = LOBYTE(wRamp_Down); 
		SendData[OPTION+5] = HIBYTE(wRamp_Down);

		SendData[OPTION+6] = Check_Sum(SendData, 8);				// checksum을 제외한 갯수..

		nSendDataSize = 9;
		nRecvDataSize = 5;

		Fnc__WRITE_LOG("var_name[%s], MAKE_PACKET: 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X",
						var_name,
						SendData[HEADER],   
						SendData[CMD],
						SendData[OPTION],   
						SendData[OPTION+1], 
						SendData[OPTION+2],
						SendData[OPTION+3], 
						SendData[OPTION+4], 
						SendData[OPTION+5],
						SendData[OPTION+6]);
	}
	else if(aoCH__RampDown_Time->Check__VARIABLE_NAME(var_name) > 0)		// Ramp Down Time ...
	{
		wSET_DATA  = (WORD)set_data;

		if(vdoCH__Ramp_Mode->Check__DATA("Disable") > 0)
		{
			wMode = 0x00;
			wSET_DATA = 0x00;
		}
		else if(vdoCH__Ramp_Mode->Check__DATA("WattSec") > 0)
		{
			wMode = 0x01;
		}
		else if(vdoCH__Ramp_Mode->Check__DATA("Timed") > 0)
		{
			wMode = 0x02;
		}

		wRamp_Down   = wSET_DATA;
		wRamp_Up     = 1000;// 1000ms

		n_trans_data_len  = 6;
		n_calced_data_len = n_mask_data_length & n_trans_data_len;

		SendData[HEADER]   = n_dev_add | n_calced_data_len;
		SendData[CMD]      = 31;

		// Mode
		SendData[OPTION]   = LOBYTE(wMode); 
		SendData[OPTION+1] = HIBYTE(wMode);

		// Ramp Up
		SendData[OPTION+2] = LOBYTE(wRamp_Up); 
		SendData[OPTION+3] = HIBYTE(wRamp_Up);

		// Ramp Down
		SendData[OPTION+4] = LOBYTE(wRamp_Down); 
		SendData[OPTION+5] = HIBYTE(wRamp_Down);

		SendData[OPTION+6] = Check_Sum(SendData, 8);				// checksum을 제외한 갯수..

		nSendDataSize = 9;
		nRecvDataSize = 5;

		Fnc__WRITE_LOG("var_name[%s], MAKE_PACKET: 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X",
						var_name,
						SendData[HEADER],   
						SendData[CMD],
						SendData[OPTION],   
						SendData[OPTION+1], 
						SendData[OPTION+2],
						SendData[OPTION+3], 
						SendData[OPTION+4], 
						SendData[OPTION+5],
						SendData[OPTION+6]);
	}
	else if(aoCH__RF_Freq->Check__VARIABLE_NAME(var_name) > 0)		// Set Fixed Frequency !!
	{
		dwSET_DATA = (DWORD)set_data;
		wLO        = LOWORD(dwSET_DATA);
		wHI        = HIWORD(dwSET_DATA);

		n_trans_data_len  = 4;
		n_calced_data_len = n_mask_data_length & n_trans_data_len;

		SendData[HEADER]   = n_dev_add | n_calced_data_len;
		SendData[CMD]      = 61;

		SendData[OPTION]   = LOBYTE(wLO); 
		SendData[OPTION+1] = HIBYTE(wLO);
		SendData[OPTION+2] = LOBYTE(wHI); 
		SendData[OPTION+3] = HIBYTE(wHI);

		SendData[OPTION+4] = Check_Sum(SendData, 6);				// checksum을 제외한 갯수..

		nSendDataSize = 7;
		nRecvDataSize = 5;

		Fnc__WRITE_LOG("var_name[%s], MAKE_PACKET: 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X",
						var_name,
						SendData[HEADER],   
						SendData[CMD],
						SendData[OPTION],   
						SendData[OPTION+1], 
						SendData[OPTION+2],
						SendData[OPTION+3], 
						SendData[OPTION+4]);
	}
	else if(aoCH__Start_Freq->Check__VARIABLE_NAME(var_name) > 0)		// Set Tuning Start Frequency !!
	{
		dwSET_DATA = (DWORD)set_data;
		wLO        = LOWORD(dwSET_DATA);
		wHI        = HIWORD(dwSET_DATA);

		n_trans_data_len  = 4;
		n_calced_data_len = n_mask_data_length & n_trans_data_len;

		SendData[HEADER]   = n_dev_add | n_calced_data_len;
		SendData[CMD]      = 46;

		SendData[OPTION]   = LOBYTE(wLO); 
		SendData[OPTION+1] = HIBYTE(wLO);
		SendData[OPTION+2] = LOBYTE(wHI); 
		SendData[OPTION+3] = HIBYTE(wHI);

		SendData[OPTION+4] = Check_Sum(SendData, 6);				// checksum을 제외한 갯수..

		nSendDataSize = 7;
		nRecvDataSize = 5;

		Fnc__WRITE_LOG("var_name[%s], MAKE_PACKET: 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X",
						var_name,
						SendData[HEADER],   
						SendData[CMD],
						SendData[OPTION],   
						SendData[OPTION+1], 
						SendData[OPTION+2],
						SendData[OPTION+3], 
						SendData[OPTION+4]);
	}
	else if(aoCH__Set_Tuning_Timeout->Check__VARIABLE_NAME(var_name) > 0)		// Set Tuning Timeout !!
	{
		dwSET_DATA = (DWORD)set_data;
		wLO        = LOWORD(dwSET_DATA);
		wHI        = HIWORD(dwSET_DATA);

		n_trans_data_len  = 4;
		n_calced_data_len = n_mask_data_length & n_trans_data_len;

		SendData[HEADER]   = n_dev_add | n_calced_data_len;
		SendData[CMD]      = 38;

		SendData[OPTION]   = LOBYTE(wLO); 
		SendData[OPTION+1] = HIBYTE(wLO);
		SendData[OPTION+2] = LOBYTE(wHI); 
		SendData[OPTION+3] = HIBYTE(wHI);

		SendData[OPTION+4] = Check_Sum(SendData, 6);				// checksum을 제외한 갯수..

		nSendDataSize = 7;
		nRecvDataSize = 5;

		Fnc__WRITE_LOG("var_name[%s], MAKE_PACKET: 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X",
						var_name,
						SendData[HEADER],   
						SendData[CMD],
						SendData[OPTION],   
						SendData[OPTION+1], 
						SendData[OPTION+2],
						SendData[OPTION+3], 
						SendData[OPTION+4]);
	}
	else if(aoCH__HostPort_Timeout->Check__VARIABLE_NAME(var_name) > 0)		// Set HostPort Timeout !!
	{
		wSET_DATA = (WORD)set_data;		// Valid Range is 2~500

		n_trans_data_len  = 2;
		n_calced_data_len = n_mask_data_length & n_trans_data_len;

		SendData[HEADER]   = n_dev_add | n_calced_data_len;
		SendData[CMD]      = 40;

		SendData[OPTION]   = LOBYTE(wSET_DATA); 
		SendData[OPTION+1] = HIBYTE(wSET_DATA);

		SendData[OPTION+2] = Check_Sum(SendData, 4);				// checksum을 제외한 갯수..

		nSendDataSize = 5;
		nRecvDataSize = 5;

		Fnc__WRITE_LOG("var_name[%s], MAKE_PACKET: 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X",
						var_name,
						SendData[HEADER],   
						SendData[CMD],
						SendData[OPTION],   
						SendData[OPTION+1], 
						SendData[OPTION+2]);
	}
	else if(aoCH__Tune_Delay->Check__VARIABLE_NAME(var_name) > 0)	// Set Tune Delay !!
	{
		wSET_DATA = (WORD)set_data;

		n_trans_data_len  = 2;
		n_calced_data_len = n_mask_data_length & n_trans_data_len;

		SendData[HEADER]   = n_dev_add | n_calced_data_len;
		SendData[CMD]      = 60;

		SendData[OPTION]   = LOBYTE(wSET_DATA); 
		SendData[OPTION+1] = HIBYTE(wSET_DATA);

		SendData[OPTION+2] = Check_Sum(SendData, 4);				// checksum을 제외한 갯수..

		nSendDataSize = 5;
		nRecvDataSize = 5;

		Fnc__WRITE_LOG("var_name[%s], MAKE_PACKET: 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X",
						var_name,
						SendData[HEADER],   
						SendData[CMD],
						SendData[OPTION],   
						SendData[OPTION+1], 
						SendData[OPTION+2]);
	}
	else if(aoCH__Ps_Frequency_Set->Check__VARIABLE_NAME(var_name) > 0)		// Set Pulsing Frequency !!
	{
		dwSET_DATA = (DWORD)set_data;		// Valid Range is 10~100000
		wLO        = LOWORD(dwSET_DATA);
		wHI        = HIWORD(dwSET_DATA);

		n_trans_data_len  = 4;
		n_calced_data_len = n_mask_data_length & n_trans_data_len;

		SendData[HEADER]   = n_dev_add | n_calced_data_len;
		SendData[CMD]      = 93;

		SendData[OPTION]   = LOBYTE(wLO); 
		SendData[OPTION+1] = HIBYTE(wLO);
		SendData[OPTION+2] = LOBYTE(wHI); 
		SendData[OPTION+3] = HIBYTE(wHI);

		SendData[OPTION+4] = Check_Sum(SendData, 6);				// checksum을 제외한 갯수..

		nSendDataSize = 7;
		nRecvDataSize = 5;

		Fnc__WRITE_LOG("var_name[%s], MAKE_PACKET: 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X",
			var_name,
			SendData[HEADER],   
			SendData[CMD],
			SendData[OPTION],   
			SendData[OPTION+1], 
			SendData[OPTION+2],
			SendData[OPTION+3], 
			SendData[OPTION+4]);
	}
	else if(aoCH__Ps_Duty_Set->Check__VARIABLE_NAME(var_name) > 0)		// Set Pulsing Duty !!
	{
		wSET_DATA = (WORD)set_data;		// Valid Range is 10~90

		n_trans_data_len  = 2;
		n_calced_data_len = n_mask_data_length & n_trans_data_len;

		SendData[HEADER]   = n_dev_add | n_calced_data_len;
		SendData[CMD]      = 96;

		SendData[OPTION]   = LOBYTE(wSET_DATA); 
		SendData[OPTION+1] = HIBYTE(wSET_DATA);

		SendData[OPTION+2] = Check_Sum(SendData, 4);				// checksum을 제외한 갯수..

		nSendDataSize = 5;
		nRecvDataSize = 5;

		Fnc__WRITE_LOG("var_name[%s], MAKE_PACKET: 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X",
			var_name,
			SendData[HEADER],   
			SendData[CMD],
			SendData[OPTION],   
			SendData[OPTION+1], 
			SendData[OPTION+2]);
	}

	if(SendCommand(SendData, RecvData, nSendDataSize, nRecvDataSize) < 0)
	{
		Fnc__WRITE_LOG("Send Command Failed(%s)", var_name);
		return -1;
	}
	return 1;
}

int CObj__OVATION_2560
::__Write__DIGITAL(const CString& var_name,
				   const CDS_IO__CHANNEL_INFO& io_info, 
				   const CString& set_data,
				   const int item_index)
{
	int n_trans_data_len;
	int n_dev_add;
	int n_calced_data_len;

	int nSendDataSize;
	int nRecvDataSize;

	// -------------- Message Format -------------------------
	// header  (1byte : 11111xxx 는 address, xxxxx111은 data 길이, 여기서 x는 유효하지 않음.)
	// Command (1byte) 
	// Optional(1byte)
	// data    (0~255 bytes)
	// checksum(1byte : header ~ data 까지 XOR)
	// -------------------------------------------------------

	UCHAR SendData[MAX_DATA_LENGTH] = { 0, };
	UCHAR RecvData[MAX_DATA_LENGTH] = { 0, };

	int n_mask_data_length = 0x07;		// xxxxx111 에서 뒤의 3개의 bit만 유효 하므로..
	n_dev_add = m_nAddress << 3;		// 하위 3개의 비트는 버림.

	if(doCH__RF_CMD->Check__VARIABLE_NAME(var_name) > 0)
	{
		n_trans_data_len  = 0;
		n_calced_data_len = n_mask_data_length & n_trans_data_len;

		SendData[HEADER]  = n_dev_add | n_calced_data_len;

		if(set_data.CompareNoCase("On") == 0)	SendData[CMD]      = 2; // On
		else									SendData[CMD]      = 1;	// Off

		SendData[OPTION]  = Check_Sum(SendData, 2);

		nSendDataSize = 3;
		nRecvDataSize = 5;

		Fnc__WRITE_LOG("var_name[%s], MAKE_PACKET: 0x%02X, 0x%02X, 0x%02X", 
						var_name,
						SendData[HEADER],   
						SendData[CMD],	
						SendData[OPTION]);
	}
	else if(doCH__CONTROL_MODE->Check__VARIABLE_NAME(var_name) > 0)
	{
		n_trans_data_len  = 1;
		n_calced_data_len = n_mask_data_length & n_trans_data_len;

		SendData[HEADER]  = n_dev_add | n_calced_data_len;
		SendData[CMD]	  = 14;

		if(set_data.CompareNoCase("Remote") == 0)	SendData[OPTION]  = 2;	// Host
		else										SendData[OPTION]  = 4;	// User Port(analog)

		SendData[OPTION+1]  = Check_Sum(SendData, 3);

		nSendDataSize = 4;
		nRecvDataSize = 5;

		Fnc__WRITE_LOG("var_name[%s], MAKE_PACKET: 0x%02X, 0x%02X, 0x%02X, 0x%02X", 
						var_name,
						SendData[HEADER],   
						SendData[CMD],	
						SendData[OPTION],	
						SendData[OPTION+1]);
	}
	else if(doCH__FREQUENCY_CONTROL_MODE->Check__VARIABLE_NAME(var_name) > 0)
	{
		n_trans_data_len  = 1;
		n_calced_data_len = n_mask_data_length & n_trans_data_len;

		SendData[HEADER]  = n_dev_add | n_calced_data_len;
		SendData[CMD]	  = 48;

		if(set_data.CompareNoCase("Fixed") == 0)	SendData[OPTION]  = 0;	// Fixed
		else										SendData[OPTION]  = 1;	// Variable

		SendData[OPTION+1]  = Check_Sum(SendData, 3);

		nSendDataSize = 4;
		nRecvDataSize = 5;

		Fnc__WRITE_LOG("var_name[%s], MAKE_PACKET: 0x%02X, 0x%02X, 0x%02X, 0x%02X", 
						var_name,
						SendData[HEADER],   
						SendData[CMD],	
						SendData[OPTION],	
						SendData[OPTION+1]);
	}
	else if (doCH__Pulsing_Mode_Set->Check__VARIABLE_NAME(var_name) > 0)
	{
		WORD mode;

		mode = (WORD)RF_Ps_Request;
		n_trans_data_len  = 6;
		n_calced_data_len = n_mask_data_length & n_trans_data_len;

		SendData[HEADER]   = n_dev_add | n_calced_data_len;
		SendData[CMD]	   = 26;
		SendData[OPTION]   = LOBYTE(mode);
		SendData[OPTION+1] = HIBYTE(mode);
		if		(set_data.CompareNoCase("Pulsing") == 0)	SendData[OPTION+2] = 1;	// Pulsing mode set
		else if (set_data.CompareNoCase("Enable") == 0)		SendData[OPTION+2] = 1;	// Pulsing enabled
		else												SendData[OPTION+2] = 0;	// Standard (Pulsing disabled, Arc management disabled)
		SendData[OPTION+3] = 0;
		SendData[OPTION+4] = 0;
		SendData[OPTION+5] = 0;
		SendData[OPTION+6] = Check_Sum(SendData, 8);

		nSendDataSize = 9;
		nRecvDataSize = 5;

		Fnc__WRITE_LOG("var_name[%s], MAKE_PACKET: 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X", 
			var_name,
			SendData[HEADER],   
			SendData[CMD],	
			SendData[OPTION],	
			SendData[OPTION+1],
			SendData[OPTION+2],
			SendData[OPTION+3],
			SendData[OPTION+4],
			SendData[OPTION+5],
			SendData[OPTION+6]);
	}

	if(SendCommand(SendData, RecvData, nSendDataSize, nRecvDataSize) < 0)
	{
		Fnc__WRITE_LOG("Send Command Failed(%s)", var_name);
		return -1;
	}

	if (doCH__Pulsing_Mode_Set->Check__VARIABLE_NAME(var_name) > 0)
	{
		if (set_data.CompareNoCase("Enable") == 0)
		{
			RF_Ps_state = 1;
		}
		else
		{
			RF_Ps_state = 0;
		}
	}

	return 1;
}

int CObj__OVATION_2560
::__Write__STRING(const CString& var_name, 
				  const CDS_IO__CHANNEL_INFO& io_info, 
				  const CString& set_data)
{

	return 1;
}


int CObj__OVATION_2560
::SendCommand(unsigned char * str_cmd, unsigned char * str_recv, int nSendDataSize, int nRecvDataSize)
{
	int retVal = -1;
	int nCount = 0;
	CString buffer;
	int nrecv_byte_size;
	
	UCHAR ucNAK = NAK;
	UCHAR ucACK = ACK;
	int i;

	do 
	{
		mX_Serial->CLEAR__BUFFER(&buffer);
		nrecv_byte_size = nRecvDataSize;

		//Sleep(30);
		Fnc__WRITE_LOG("---> [%d]. Send (size: %d) Start...", nCount+1, nSendDataSize);

		for(i=0; i<nSendDataSize; i++)		
		{
			Fnc__WRITE_LOG("0x%02X", str_cmd[i]);
		}

		mX_Serial->CHAR__SEND(str_cmd, nSendDataSize);
		retVal = mX_Serial->CHAR__RECV(str_recv, &nrecv_byte_size, m_nTimeout);
		
		if(retVal < 0)
		{
			Fnc__WRITE_LOG("<--- RetVal: %d, (size: %d), RecvData :", retVal, nrecv_byte_size);

			for (i=0; i<nrecv_byte_size; i++)
			{
				Fnc__WRITE_LOG("0x%02X", str_recv[i]);
			}
			m_nCommSts = OFFLINE;
		}
		else
		{
			m_nCommSts = ONLINE;
			Fnc__WRITE_LOG("<--- RECV: ret(%d), RecvData :", retVal);

			for (i=0; i<nrecv_byte_size; i++)
			{
				Fnc__WRITE_LOG("0x%02X", str_recv[i]);
			}

			// PP+ 로부터의 ACK 까지 포함한 경우.
			if(nrecv_byte_size == nRecvDataSize)
			{
				if(str_recv[3] != 0x0)		// CSR
				{
					Chk_CSR_CODE(str_recv[3]);
					return -1;
				}	

				if(str_recv[0] != ACK)
				{
					Fnc__WRITE_LOG("<--- 1. SEND: Data[0x%02X] and Retry...Cmd Send...", ucNAK);
					continue;	// command 다시 resend..
				}	

				// Checksum 은 ACK 를 제외함.
				// str_recv + 1 은 앞에 ACK 를 제외하기 위함.
				// nRecvDataSize - 1 은 앞에 ACK 를 제외한 나머지 것들에 대한 checksum을 위해..
				if(Check_Sum(str_recv+1, nRecvDataSize-1) == 0x0)	// 0이면 data OK...
				{
					mX_Serial->CHAR__SEND(&ucACK, 1);
					Fnc__WRITE_LOG("OK.... <--- SEND: Data[0x%02X]", ucACK);
					return 1;
				}
				else
				{
					mX_Serial->CHAR__SEND(&ucNAK, 1);
					Fnc__WRITE_LOG("<--- 2. SEND: Data[0x%02X] and Retry...Cmd Send...", ucNAK);
					continue;
				}
			}
		}
	} 
	while (++nCount <= m_nRetryCount);
	
	Fnc__WRITE_LOG("Count Over : [%d] / [%d]", nCount, m_nRetryCount);

	if(m_nCommSts == OFFLINE)
	{
		return -1;
	}
	return -1;
}

int CObj__OVATION_2560
::RecvCommand(unsigned char * str_cmd, unsigned char * str_recv, int nSendDataSize, int nRecvDataSize)
{
	int retVal = -1;
	int nCount = 0;
	CString buffer;
	int nrecv_byte_size;
	UCHAR ucNAK = NAK;
	UCHAR ucACK = ACK;
	int i;

	do 
	{
		mX_Serial->CLEAR__BUFFER(&buffer);
		nrecv_byte_size = nRecvDataSize;

		//Sleep(30);
		Fnc__WRITE_LOG("---> [%d]. Send (size: %d) Start...", nCount+1, nSendDataSize);

		for (i=0; i<nSendDataSize; i++)		
		{
			Fnc__WRITE_LOG("0x%02X", str_cmd[i]);
		}

		mX_Serial->CHAR__SEND(str_cmd, nSendDataSize);
		retVal = mX_Serial->CHAR__RECV(str_recv, &nrecv_byte_size, m_nTimeout);

		if(retVal < 0)
		{
			Fnc__WRITE_LOG("<--- RetVal: %d, (size: %d), RecvData :", retVal, nrecv_byte_size);

			for (i=0; i<nrecv_byte_size; i++)
			{
				Fnc__WRITE_LOG("0x%02X", str_recv[i]);
			}
			m_nCommSts = OFFLINE;
		}
		else
		{
			m_nCommSts = ONLINE;
			Fnc__WRITE_LOG("<--- RECV: ret(%d), RecvData :", retVal);

			for (i=0; i<nrecv_byte_size; i++)
			{
				Fnc__WRITE_LOG("0x%02X", str_recv[i]);
			}

			// PP+ 로부터의 ACK 까지 포함한 경우.
			if(nrecv_byte_size == nRecvDataSize)
			{
				if(str_recv[0] != ACK)
				{
					Fnc__WRITE_LOG("<--- 1. SEND: Data[0x%02X] and Retry...Cmd Send...", ucNAK);
					continue;	// command 다시 resend..
				}

				// Checksum 은 ACK 를 제외함.
				// str_recv + 1 은 앞에 ACK 를 제외하기 위함.
				// nRecvDataSize - 1 은 앞에 ACK 를 제외한 나머지 것들에 대한 checksum을 위해..
				if(Check_Sum(str_recv+1, nRecvDataSize-1) == 0x0)	// 0이면 data OK...
				{
					Fnc__WRITE_LOG("OK.... return 1.. <--- ");
					return 1;
				}
				else
				{
					mX_Serial->CHAR__SEND(&ucNAK, 1);
					Fnc__WRITE_LOG("<--- 2. SEND: Data[0x%02X] and Retry...Cmd Send...", ucNAK);
					continue;
				}
			}
		}
	} 
	while (++nCount <= m_nRetryCount);

	Fnc__WRITE_LOG("Count Over : [%d] / [%d]", nCount, m_nRetryCount);

	if(m_nCommSts == OFFLINE)
	{
		return -1;
	}
	return -1;
}

int CObj__OVATION_2560
::Get_Bit_Sts (BYTE source , int pos)
{
	int nResult;

	BYTE mask[8] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
	BYTE Temp;

	Temp    = (int)(source & mask[pos]);
	nResult = Temp >> pos;

	return nResult;
}
