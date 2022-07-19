#include "StdAfx.h"
#include "CObj__PSK_TEST.h"
#include "CObj__PSK_TEST__DEF.h"
#include "CObj__PSK_TEST__ALID.h"


#include "CDB__ADS_CTRL.h"
extern CDB__ADS_CTRL mDB__ADS_CTRL;

#include "CCls__ADS_CTRL.h"
extern CCls__ADS_CTRL mADS_CTRL;

#include "CMNG__ADS_CTRL.h"
extern CMNG__ADS_CTRL mMNG__ADS_CTRL; 


//------------------------------------------------------------------------------------
void CObj__PSK_TEST
::Mon__MONITOR(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	int loop_count = 0;

	CString ch_name;	
	CString ch_data;	
	int i;


	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.05);

		loop_count++;
		if(loop_count > 10)		loop_count = 1;


		if(iActive__SIM_MODE > 0)
		{

		}
		else
		{
			mMNG__ADS_CTRL.Update__ADS_SETTING(false, iActive__SIM_MODE);
			mMNG__ADS_CTRL.Update__ADS_READING(false, iActive__SIM_MODE);

			if(loop_count == 1)
			{
				CStringArray l_io_name;
				CStringArray l_data_hexa;

				mDB__ADS_CTRL.Get__OUT_IO_HEXA_LIST(l_io_name, l_data_hexa);

				int k_limit = l_io_name.GetSize();
				for(int k=0; k<k_limit; k++)
				{
					ch_name = l_io_name[k];
					ch_data = l_data_hexa[k];

					pOBJ_CTRL->Set__VARIABLE_DATA(ch_name, ch_data);
				}
			}
		}

		if(loop_count == 1)
		{
			// ADS.Driver Check ...
			{
				CString drv_err__var;

				if(mADS_CTRL.Check__DRV_ERROR(drv_err__var))
				{
					mADS_CTRL.Clear__DRV_ERROR();

					// ...
					{
						int alm_id = ALID__PLC_OFFLINE;
						CString alm_msg;
						CString	r_act;

						alm_msg.Format("Error Variable <- %s \n", drv_err__var);
	
						p_alarm->Check__ALARM(alm_id,r_act);
						p_alarm->Post__ALARM_With_MESSAGE(alm_id, alm_msg);
					}

					sCH__MON_COMM_STATE->Set__DATA(STR__OFFLINE);
				}
				else
				{
					sCH__MON_COMM_STATE->Set__DATA(STR__ONLINE);
				}
			}

			// ADS.Variable Check ...
			{
				int err_id;
				CString err_msg;

				while(mERR_MSG.Check__Error_Info(err_id, err_msg))
				{
					CString	r_act;

					p_alarm->Check__ALARM(err_id, r_act);
					p_alarm->Post__ALARM_With_MESSAGE(err_id, err_msg);
				}
			}
		}

		// ...
	}
}

void CObj__PSK_TEST
::Mon__ADS_CHECK(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	SCX__ASYNC_TIMER_CTRL x_loop_timer;
	x_loop_timer->START__COUNT_UP(9999);

	// ...
	CString ch_data;

	int loop_count = 0;


	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.1);

		loop_count++;
		if(loop_count > 10)		loop_count = 1;

		/*
		if(loop_count == 1)
		{
			bool s_data = false;

			if(diCH__ADS_ACTIVE->Check__DATA(STR__ON) > 0)
			{
				diCH__ADS_ACTIVE->Set__DATA(STR__OFF);
				s_data = true;
			}
			else
			{
				diCH__ADS_ACTIVE->Set__DATA(STR__ON);
				s_data = false;
			}

			mADS_CTRL.Set__VAR_ACTIVE(s_data);
		}
		if((loop_count % 3) == 0)
		{
			if(mADS_CTRL.Get__VAR_ACTIVE() > 0)		doCH__ADS_ACTIVE->Set__DATA(STR__ON);
			else									doCH__ADS_ACTIVE->Set__DATA(STR__OFF);
		}
		*/

		// ...
	}
}
