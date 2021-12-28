#include "StdAfx.h"
#include "CDriver__LPx_ETHERNET.h"
#include "CDriver__LPx_ETHERNET__DEF.h"
#include "CDriver__LPx_ETHERNET__ALID.h"

#include "Macro_Function.h"


// ...
#define _STAT__LPx_INITIAL						1
#define _VAL__LPx_INITIAL__INCOMPLETE			0
#define _VAL__LPx_INITIAL__COMPLETE				1

#define _STAT__LPx_STATUS						2
#define _VAL__LPx_STATUS__STOP					0
#define _VAL__LPx_STATUS__RUN					1
#define _VAL__LPx_STATUS__PAUSE					2
#define _VAL__LPx_STATUS__ERROR					3

#define _STAT__FOUP_EXIST						3
#define _VAL__FOUP_EXIST__NO					0
#define _VAL__FOUP_EXIST__YES					1
#define _VAL__FOUP_EXIST__UNKNOWN				2

#define _STAT__DOOR_STATUS						4 
#define _VAL__DOOR_STATUS__CLOSE				0
#define _VAL__DOOR_STATUS__OPEN					1
#define _VAL__DOOR_STATUS__UNKNOWN				2

#define _STAT__CLAMP_STATUS						5
#define _VAL__CLAMP_STATUS__UNCLAMP				0
#define _VAL__CLAMP_STATUS__CLAMP				1

#define _STAT__RFID_STATUS						6
#define _VAL__RFID_STATUS__READY				0
#define _VAL__RFID_STATUS__READING				1
#define _VAL__RFID_STATUS__READ_COMPLETE		2
#define _VAL__RFID_STATUS__WRITING				3 
#define _VAL__RFID_STATUS__WRITE_COMPLETE		4
#define _VAL__RFID_STATUS__ERROR				5

#define _STAT__AGV_STATUS						7
#define _VAL__AGV_STATUS__READY					0
#define _VAL__AGV_STATUS__BUSY					1
#define _VAL__AGV_STATUS__ERROR					3

#define _STAT__LPx_ENABLE						8
#define _VAL__LPx_ENABLE__NO					0
#define _VAL__LPx_ENABLE__YES					1

#define _STAT__RFID_ENABLE						9
#define _VAL__RFID_ENABLE__NO					0
#define _VAL__RFID_ENABLE__YES					1

#define _STAT__CLOSE_MAPPING_ENABLE				10
#define _VAL__CLOSE_MAPPING_ENABLE__NO			0
#define _VAL__CLOSE_MAPPING_ENABLE__YES			1

#define _STAT__ONLINE_MODE                      11
#define _VAL__ONLINE_MODE__MANUAL               0
#define _VAL__ONLINE_MODE__AMHS                 1

#define _STAT__LOAD_BUTTON_STATUS               12
#define _VAL__LOAD_BUTTON_STATUS__OFF           0
#define _VAL__LOAD_BUTTON_STATUS__ON            1

#define _STAT__UNLOAD_BUTTON_STATUS             13
#define _VAL__UNLOAD_BUTTON_STATUS__OFF         0
#define _VAL__UNLOAD_BUTTON_STATUS__ON          1

#define _STAT__PIO_INPUT_HIGH_WORD              14
#define _VAL__PIO_INPUT__BIT_7__CONT            8
#define _VAL__PIO_INPUT__BIT_6__COMPT           4
#define _VAL__PIO_INPUT__BIT_5__BUSY            2
#define _VAL__PIO_INPUT__BIT_4__TR_REQ          1

#define _STAT__PIO_INPUT_LOW_WORD               15
#define _VAL__PIO_INPUT__BIT_3__NC              8
#define _VAL__PIO_INPUT__BIT_2__CS_1            4
#define _VAL__PIO_INPUT__BIT_1__CS_0            2
#define _VAL__PIO_INPUT__BIT_0__VALID           1

#define _STAT__PIO_OUTPUT_HIGH_WORD             16
#define _VAL__PIO_OUTPUT__BIT_7__ES             8
#define _VAL__PIO_OUTPUT__BIT_6__HO_AVBL        4
#define _VAL__PIO_OUTPUT__BIT_5__NC             2
#define _VAL__PIO_OUTPUT__BIT_4__NC             1

#define _STAT__PIO_OUTPUT_LOW_WORD              17
#define _VAL__PIO_OUTPUT__BIT_3__READY          8
#define _VAL__PIO_OUTPUT__BIT_2__NC             4
#define _VAL__PIO_OUTPUT__BIT_1__U_REQ          2
#define _VAL__PIO_OUTPUT__BIT_0__L_REQ          1

#define _STAT__FOUP_TYPE                        18
#define _VAL__FOUP_TYPE__UNKNOWN                0
#define _VAL__FOUP_TYPE__300MM                  1
#define _VAL__FOUP_TYPE__200MM                  2


// ...
int  CDriver__LPx_ETHERNET
::_Update__LPx_STATE(const int lp_id, const CString& rsp_data)
{
	int lp_index = lp_id - 1;

	if(lp_index <  0)						return -11;
	if(lp_index >= CFG_LPx__SIZE)			return -12;

	// ...
	CString str_rsp;

	int i_limit = rsp_data.GetLength();
	int i;

	for(i=0; i<i_limit; i++)
	{
		str_rsp = rsp_data[i];
		int i_data = atoi(str_rsp);

		// ...
		CString str_data;

		int id = i + 1;

		if(id == _STAT__LPx_INITIAL)
		{	
				 if(i_data == _VAL__LPx_INITIAL__INCOMPLETE)		str_data = STR__OFF;
			else if(i_data == _VAL__LPx_INITIAL__COMPLETE)			str_data = STR__ON;
			else													str_data = STR__UNKNOWN;

			sCH__LP_INFO__INITIAL_X[lp_index]->Set__DATA(str_data);
			continue;
		}
		if(id == _STAT__LPx_STATUS)
		{
				 if(i_data == _VAL__LPx_STATUS__STOP)				str_data = STR__STOP;
		    else if(i_data == _VAL__LPx_STATUS__RUN)				str_data = STR__RUN;
			else if(i_data == _VAL__LPx_STATUS__PAUSE)				str_data = STR__PAUSE;
			else if(i_data == _VAL__LPx_STATUS__ERROR)				str_data = STR__ERROR;
			else													str_data = STR__UNKNOWN;

			sCH__LP_INFO__STATUS_X[lp_index]->Set__DATA(str_data);
			continue;
		}
		if(id == _STAT__FOUP_EXIST)
		{
				 if(i_data == _VAL__FOUP_EXIST__NO)					str_data = STR__NO;
			else if(i_data == _VAL__FOUP_EXIST__YES)				str_data = STR__YES;
			else 													str_data = STR__UNKNOWN;

			sCH__LP_INFO__FOUP_EXIST_X[lp_index]->Set__DATA(str_data);
			continue;
		}
		if(id == _STAT__DOOR_STATUS)
		{
				 if(i_data == _VAL__DOOR_STATUS__CLOSE)				str_data = STR__CLOSE;
			else if(i_data == _VAL__DOOR_STATUS__OPEN)				str_data = STR__OPEN;
			else													str_data = STR__UNKNOWN;

			sCH__LP_INFO__DOOR_STATUS_X[lp_index]->Set__DATA(str_data);
			continue;
		}
		if(id == _STAT__CLAMP_STATUS)
		{
				 if(i_data == _VAL__CLAMP_STATUS__UNCLAMP)			str_data = STR__UNCLAMP;
			else if(i_data == _VAL__CLAMP_STATUS__CLAMP)			str_data = STR__CLAMP;
			else													str_data = STR__UNKNOWN;

			sCH__LP_INFO__CLAMP_STATUS_X[lp_index]->Set__DATA(str_data);
			continue;
		}
		if(id == _STAT__RFID_STATUS)
		{
				 if(i_data == _VAL__RFID_STATUS__READY)				str_data = STR__READY;
			else if(i_data == _VAL__RFID_STATUS__READING)			str_data = STR__READING;
			else if(i_data == _VAL__RFID_STATUS__READ_COMPLETE)		str_data = STR__READ_COMPLETE;
			else if(i_data == _VAL__RFID_STATUS__WRITING)			str_data = STR__WRITING;
			else if(i_data == _VAL__RFID_STATUS__WRITE_COMPLETE)	str_data = STR__WRITE_COMPLETE;
			else if(i_data == _VAL__RFID_STATUS__ERROR)				str_data = STR__ERROR;
			else													str_data = STR__UNKNOWN;

			sCH__LP_INFO__RFID_STATUS_X[lp_index]->Set__DATA(str_data);
			continue;
		}
		if(id == _STAT__AGV_STATUS)
		{
				 if(i_data == _VAL__AGV_STATUS__READY)				str_data = STR__READY;
			else if(i_data == _VAL__AGV_STATUS__BUSY)				str_data = STR__BUSY;
			else if(i_data == _VAL__AGV_STATUS__ERROR)				str_data = STR__ERROR;
			else													str_data = STR__UNKNOWN;

			sCH__LP_INFO__AGV_STATUS_X[lp_index]->Set__DATA(str_data);
			continue;
		}
		if(id == _STAT__LPx_ENABLE)
		{
				 if(i_data == _VAL__LPx_ENABLE__NO)					str_data = STR__NO;
			else if(i_data == _VAL__LPx_ENABLE__YES)				str_data = STR__YES;
			else													str_data = STR__UNKNOWN;

			sCH__LP_INFO__ENABLE_X[lp_index]->Set__DATA(str_data);
			continue;
		}
		if(id == _STAT__RFID_ENABLE)
		{
				 if(i_data == _VAL__RFID_ENABLE__NO)				str_data = STR__NO;
			else if(i_data == _VAL__RFID_ENABLE__YES)				str_data = STR__YES;
			else													str_data = STR__UNKNOWN;

			sCH__LP_INFO__RFID_ENABLE_X[lp_index]->Set__DATA(str_data);
			continue;
		}
		if(id == _STAT__CLOSE_MAPPING_ENABLE)
		{
				 if(i_data == _VAL__CLOSE_MAPPING_ENABLE__NO)		str_data = STR__NO;
			else if(i_data == _VAL__CLOSE_MAPPING_ENABLE__YES)		str_data = STR__YES;
			else													str_data = STR__UNKNOWN;

			sCH__LP_INFO__CLOSE_MAPPING_ENABLE_X[lp_index]->Set__DATA(str_data);
			continue;
		}
		if(id == _STAT__ONLINE_MODE)
		{
				 if(i_data == _VAL__ONLINE_MODE__MANUAL)			str_data = STR__MANUAL;
			else if(i_data == _VAL__ONLINE_MODE__AMHS)				str_data = STR__AMHS;
			else													str_data = STR__UNKNOWN;

			sCH__LP_INFO__ONLINE_MODE_X[lp_index]->Set__DATA(str_data);
			continue;
		}
		if(id == _STAT__LOAD_BUTTON_STATUS)
		{
				 if(i_data == _VAL__LOAD_BUTTON_STATUS__OFF)		str_data = STR__OFF;
			else if(i_data == _VAL__LOAD_BUTTON_STATUS__ON)			str_data = STR__ON;
			else													str_data = STR__UNKNOWN;

			sCH__LP_INFO__LOAD_BUTTON_STATUS_X[lp_index]->Set__DATA(str_data);
			continue;
		}
		if(id == _STAT__UNLOAD_BUTTON_STATUS)
		{
				 if(i_data == _VAL__UNLOAD_BUTTON_STATUS__OFF)		str_data = STR__OFF;
			else if(i_data == _VAL__UNLOAD_BUTTON_STATUS__ON)		str_data = STR__ON;
			else													str_data = STR__UNKNOWN;

			sCH__LP_INFO__UNLOAD_BUTTON_STATUS_X[lp_index]->Set__DATA(str_data);
			continue;
		}
		if(id == _STAT__PIO_INPUT_HIGH_WORD)
		{
			sCH__LP_INFO__PIO_INPUT_HIGH_WORD_X[lp_index]->Set__DATA(str_rsp);

			i_data = Fnc__HexToDec(str_rsp);

			// BIT : 7
			{
				str_data = STR__OFF;
				if(i_data >= _VAL__PIO_INPUT__BIT_7__CONT)
				{
					i_data -= _VAL__PIO_INPUT__BIT_7__CONT;
					str_data = STR__ON;
				}
				sCH__LP_INFO__PIO_INPUT__BIT_7__CONT_X[lp_index]->Set__DATA(str_data);
			}
			// BIT : 6
			{
				str_data = STR__OFF;
				if(i_data >= _VAL__PIO_INPUT__BIT_6__COMPT)
				{
					i_data -= _VAL__PIO_INPUT__BIT_6__COMPT;
					str_data = STR__ON;
				}
				sCH__LP_INFO__PIO_INPUT__BIT_6__COMPTT_X[lp_index]->Set__DATA(str_data);
			}
			// BIT : 5
			{
				str_data = STR__OFF;
				if(i_data >= _VAL__PIO_INPUT__BIT_5__BUSY)
				{
					i_data -= _VAL__PIO_INPUT__BIT_5__BUSY;
					str_data = STR__ON;
				}
				sCH__LP_INFO__PIO_INPUT__BIT_5__BUSY_X[lp_index]->Set__DATA(str_data);
			}
			// BIT : 4
			{
				str_data = STR__OFF;
				if(i_data >= _VAL__PIO_INPUT__BIT_4__TR_REQ)
				{
					i_data -= _VAL__PIO_INPUT__BIT_4__TR_REQ;
					str_data = STR__ON;
				}
				sCH__LP_INFO__PIO_INPUT__BIT_4__TR_REQ_X[lp_index]->Set__DATA(str_data);
			}
			continue;
		}
		if(id == _STAT__PIO_INPUT_LOW_WORD)
		{
			sCH__LP_INFO__PIO_INPUT_LOW_WORD_X[lp_index]->Set__DATA(str_rsp);

			i_data = Fnc__HexToDec(str_rsp);

			// BIT : 3
			{
				str_data = STR__OFF;
				if(i_data >= _VAL__PIO_INPUT__BIT_3__NC)
				{
					i_data -= _VAL__PIO_INPUT__BIT_3__NC;
					str_data = STR__ON;
				}
				sCH__LP_INFO__PIO_INPUT__BIT_3__NC_X[lp_index]->Set__DATA(str_data);
			}
			// BIT : 2
			{
				str_data = STR__OFF;
				if(i_data >= _VAL__PIO_INPUT__BIT_2__CS_1)
				{
					i_data -= _VAL__PIO_INPUT__BIT_2__CS_1;
					str_data = STR__ON;
				}
				sCH__LP_INFO__PIO_INPUT__BIT_2__CS_1_X[lp_index]->Set__DATA(str_data);
			}
			// BIT : 1
			{
				str_data = STR__OFF;
				if(i_data >= _VAL__PIO_INPUT__BIT_1__CS_0)
				{
					i_data -= _VAL__PIO_INPUT__BIT_1__CS_0;
					str_data = STR__ON;
				}
				sCH__LP_INFO__PIO_INPUT__BIT_1__CS_0_X[lp_index]->Set__DATA(str_data);
			}
			// BIT : 0
			{
				str_data = STR__OFF;
				if(i_data >= _VAL__PIO_INPUT__BIT_0__VALID)
				{
					i_data -= _VAL__PIO_INPUT__BIT_0__VALID;
					str_data = STR__ON;
				}
				sCH__LP_INFO__PIO_INPUT__BIT_0__VALID_X[lp_index]->Set__DATA(str_data);
			}
			continue;
		}
		if(id == _STAT__PIO_OUTPUT_HIGH_WORD)
		{
			sCH__LP_INFO__PIO_OUTPUT_HIGH_WORD_X[lp_index]->Set__DATA(str_rsp);

			i_data = Fnc__HexToDec(str_rsp);

			// BIT : 7
			{
				str_data = STR__OFF;
				if(i_data >= _VAL__PIO_OUTPUT__BIT_7__ES)
				{
					i_data -= _VAL__PIO_OUTPUT__BIT_7__ES;
					str_data = STR__ON;
				}
				sCH__LP_INFO__PIO_OUTPUT__BIT_7__ES_X[lp_index]->Set__DATA(str_data);
			}
			// BIT : 6
			{
				str_data = STR__OFF;
				if(i_data >= _VAL__PIO_OUTPUT__BIT_6__HO_AVBL)
				{
					i_data -= _VAL__PIO_OUTPUT__BIT_6__HO_AVBL;
					str_data = STR__ON;
				}
				sCH__LP_INFO__PIO_OUTPUT__BIT_6__HO_AVBL_X[lp_index]->Set__DATA(str_data);
			}
			// BIT : 5
			{
				str_data = STR__OFF;
				if(i_data >= _VAL__PIO_OUTPUT__BIT_5__NC)
				{
					i_data -= _VAL__PIO_OUTPUT__BIT_5__NC;
					str_data = STR__ON;
				}
				sCH__LP_INFO__PIO_OUTPUT__BIT_5__NC_X[lp_index]->Set__DATA(str_data);
			}
			// BIT : 4
			{
				str_data = STR__OFF;
				if(i_data >= _VAL__PIO_OUTPUT__BIT_4__NC)
				{
					i_data -= _VAL__PIO_OUTPUT__BIT_4__NC;
					str_data = STR__ON;
				}
				sCH__LP_INFO__PIO_OUTPUT__BIT_4__NC_X[lp_index]->Set__DATA(str_data);
			}
			continue;
		}
		if(id == _STAT__PIO_OUTPUT_LOW_WORD)
		{
			sCH__LP_INFO__PIO_OUTPUT_LOW_WORD_X[lp_index]->Set__DATA(str_rsp);

			i_data = Fnc__HexToDec(str_rsp);

			// BIT : 3
			{
				str_data = STR__OFF;
				if(i_data >= _VAL__PIO_OUTPUT__BIT_3__READY)
				{
					i_data -= _VAL__PIO_OUTPUT__BIT_3__READY;
					str_data = STR__ON;
				}
				sCH__LP_INFO__PIO_OUTPUT__BIT_3__READY_X[lp_index]->Set__DATA(str_data);
			}
			// BIT : 2
			{
				str_data = STR__OFF;
				if(i_data >= _VAL__PIO_OUTPUT__BIT_2__NC)
				{
					i_data -= _VAL__PIO_OUTPUT__BIT_2__NC;
					str_data = STR__ON;
				}
				sCH__LP_INFO__PIO_OUTPUT__BIT_2__NC_X[lp_index]->Set__DATA(str_data);
			}
			// BIT : 1
			{
				str_data = STR__OFF;
				if(i_data >= _VAL__PIO_OUTPUT__BIT_1__U_REQ)
				{
					i_data -= _VAL__PIO_OUTPUT__BIT_1__U_REQ;
					str_data = STR__ON;
				}
				sCH__LP_INFO__PIO_OUTPUT__BIT_1__U_REQ_X[lp_index]->Set__DATA(str_data);
			}
			// BIT : 0
			{
				str_data = STR__OFF;
				if(i_data >= _VAL__PIO_OUTPUT__BIT_0__L_REQ)
				{
					i_data -= _VAL__PIO_OUTPUT__BIT_0__L_REQ;
					str_data = STR__ON;
				}
				sCH__LP_INFO__PIO_OUTPUT__BIT_0__L_REQ_X[lp_index]->Set__DATA(str_data);
			}
			continue;
		}
		if(id == _STAT__FOUP_TYPE)
		{
				 if(i_data == _VAL__FOUP_TYPE__300MM)				str_data = "300mm";
			else if(i_data == _VAL__FOUP_TYPE__200MM)				str_data = "200mm";
			else													str_data = STR__UNKNOWN;

			sCH__LP_INFO__FOUP_TYPE_X[lp_index]->Set__DATA(str_data);
			continue;
		}
	}

	return 1;
}

int  CDriver__LPx_ETHERNET
::_Update__LPx_MAP(const int lp_id, const CString& rsp_data)
{
	int lp_index = lp_id - 1;

	int k_limit = rsp_data.GetLength();
	int k;

	for(k=0; k<k_limit; k++)
	{
		CString ch_data;

		ch_data = rsp_data[k];
		int i_data = atoi(ch_data);

		     if(i_data == 0)		ch_data = "NONE";
		else if(i_data == 1)		ch_data = "EXIST";	
		else if(i_data == 2)		ch_data = "DOUBLE";
		else if(i_data == 3)		ch_data = "CROSS";
		else if(i_data == 4)		ch_data = "ERROR";
		else						ch_data = "UNKNOWN";

		if(k < CFG_LPx__SLOT_SIZE)
			dCH__LPx_MAP__RESULT_XY[lp_index][k]->Set__DATA(ch_data);
	}

	return 1;
}

int  CDriver__LPx_ETHERNET
::_Update__LPx_N2_STS(const int lp_id, const CString& str_rsp)
{
	char ch_check = '/';
	CStringArray l_para;

	Macro__Get_String_List(str_rsp,ch_check, l_para);

	int lp_index = lp_id - 1;

	int i_limit = l_para.GetSize();
	int i;

	for(i=0; i<i_limit; i++)
	{
		CString ch_data = l_para[i];
		
			 if(i == 0)		sCH__N2_INFO__TIME_X[lp_index]->Set__DATA(ch_data);
		else if(i == 1)		sCH__N2_INFO__NOZZLE_1__FLOW_X[lp_index]->Set__DATA(ch_data);
		else if(i == 2)		sCH__N2_INFO__NOZZLE_2__FLOW_X[lp_index]->Set__DATA(ch_data);
		else if(i == 3)		sCH__N2_INFO__NOZZLE_3__FLOW_X[lp_index]->Set__DATA(ch_data);
		else if(i == 4)		sCH__N2_INFO__NOZZLE_1__PRESSURE_X[lp_index]->Set__DATA(ch_data);
		else if(i == 5)		sCH__N2_INFO__NOZZLE_2__PRESSURE_X[lp_index]->Set__DATA(ch_data);
		else if(i == 6)		sCH__N2_INFO__NOZZLE_3__PRESSURE_X[lp_index]->Set__DATA(ch_data);
		else if(i == 7)		sCH__N2_INFO__NOZZLE_4__PRESSURE_X[lp_index]->Set__DATA(ch_data);
		else if(i == 8)		sCH__N2_INFO__OXYGEN_DENSITY_X[lp_index]->Set__DATA(ch_data);
		else if(i == 9)		sCH__N2_INFO__CASSETTE_TYPE_X[lp_index]->Set__DATA(ch_data);
	}
	
	return 1;
}

