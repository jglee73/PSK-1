#include "StdAfx.h"
#include "CDriver__LPx_ETHERNET.h"
#include "CDriver__LPx_ETHERNET__DEF.h"
#include "CDriver__LPx_ETHERNET__ALID.h"


// ...
int CDriver__LPx_ETHERNET
::Call__CHECK_LPx_STATE(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	CString str_rsp;

	CString ch_data = dCH__TEST_PARA_LPx_ID->Get__STRING();
	int lp_id = atoi(ch_data);

	// ...
	{
		str_rsp = "";

		// 1.
		ch_data = dCH__TEST_STATE__LPx_INITAL->Get__STRING();
		str_rsp += ch_data;

		// 2.
		ch_data = dCH__TEST_STATE__LPx_STATUS->Get__STRING();
		str_rsp += ch_data;

		// 3.
		ch_data = dCH__TEST_STATE__FOUP_EXIST->Get__STRING();
		str_rsp += ch_data;

		// 4.
		ch_data = dCH__TEST_STATE__DOOR_STATUS->Get__STRING();
		str_rsp += ch_data;

		// 5.
		ch_data = dCH__TEST_STATE__CLAMP_STATUS->Get__STRING();
		str_rsp += ch_data;

		// 6.
		ch_data = dCH__TEST_STATE__RFID_STATUS->Get__STRING();
		str_rsp += ch_data;

		// 7.
		ch_data = dCH__TEST_STATE__AGV_STATUS->Get__STRING();
		str_rsp += ch_data;

		// 8.
		ch_data = dCH__TEST_STATE__LPx_ENABLE->Get__STRING();
		str_rsp += ch_data;

		// 9.
		ch_data = dCH__TEST_STATE__RFID_ENABLE->Get__STRING();
		str_rsp += ch_data;

		// 10.
		ch_data = dCH__TEST_STATE__CLOSE_MAPPING_ENABLE->Get__STRING();
		str_rsp += ch_data;

		// 11.
		ch_data = dCH__TEST_STATE__ONLINE_MODE->Get__STRING();
		str_rsp += ch_data;

		// 12.
		ch_data = dCH__TEST_STATE__LOAD_BUTTON_STATUS->Get__STRING();
		str_rsp += ch_data;

		// 13.
		ch_data = dCH__TEST_STATE__UNLOAD_BUTTON_STATUS->Get__STRING();
		str_rsp += ch_data;

		// 14.
		ch_data = dCH__TEST_STATE__PIO_INPUT_HIGH_WORD->Get__STRING();
		str_rsp += ch_data;

		// 15.
		ch_data = dCH__TEST_STATE__PIO_INPUT_LOW_WORD->Get__STRING();
		str_rsp += ch_data;

		// 16.
		ch_data = dCH__TEST_STATE__PIO_OUTPUT_HIGH_WORD->Get__STRING();
		str_rsp += ch_data;

		// 17.
		ch_data = dCH__TEST_STATE__PIO_OUTPUT_LOW_WORD->Get__STRING();
		str_rsp += ch_data;

		// 18.
		ch_data = dCH__TEST_STATE__FOUP_TYPE->Get__STRING();
		str_rsp += ch_data;
	}

	_Update__LPx_STATE(lp_id, str_rsp);
	return 1;
}
