#include "stdafx.h"

#include "CObj__RFID_CTRL.h"

#include "CObj__RFID_CTRL__ALID.h"
#include "CObj__RFID_CTRL__DEF.h"


// ...
int	CObj__RFID_CTRL
::Call__INIT(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{

	return 1;
}

int	CObj__RFID_CTRL
::Call__CID_READ(CII_OBJECT__VARIABLE* p_variable,
				 CII_OBJECT__ALARM* p_alarm)
{
LOOP_RETRY:

	if(iActive__SIM_MODE > 0)
	{
		siEXT_CH__RFID_READ->Set__DATA(STR__OK);
	}

	// ...
	int page_id = 0;
	aEXT_CH__PARA_RFID_PAGE_ID->Set__VALUE(page_id);

	CString ch_data = siEXT_CH__RFID_READ->Get__STRING();

	// ...
	{
		int r_flag = Check__ERROR(p_alarm, CTRL_MODE__CID_READ);

		if(r_flag <  0)			return -11;
		if(r_flag == 0)			goto LOOP_RETRY;
	}

	ch_data = sEXT_CH__LP_INFO__RFID_RSP->Get__STRING();
	sCH__RSP_CID_DATA->Set__DATA(ch_data);

	if(iActive__SIM_MODE > 0)	
	{
		ch_data.Format("CID.%1d", iLINK__LPx_ID);
		sCH__RSP_CID_DATA->Set__DATA(ch_data);
	}
	return 1;
}
int	CObj__RFID_CTRL
::Call__PAGE_READ(CII_OBJECT__VARIABLE* p_variable, 
				  CII_OBJECT__ALARM* p_alarm)
{
LOOP_RETRY:

	if(iActive__SIM_MODE > 0)
	{
		siEXT_CH__RFID_READ->Set__DATA(STR__OK);
	}

	// ...
	CString ch_data;

	aCH__PARA_PAGE_ID->Get__DATA(ch_data);
	aEXT_CH__PARA_RFID_PAGE_ID->Set__DATA(ch_data);

	ch_data = siEXT_CH__RFID_READ->Get__STRING();

	// ...
	{
		int r_flag = Check__ERROR(p_alarm, CTRL_MODE__CID_READ);

		if(r_flag <  0)			return -11;
		if(r_flag == 0)			goto LOOP_RETRY;
	}

	ch_data = sEXT_CH__LP_INFO__RFID_RSP->Get__STRING();
	sCH__RSP_PAGE_DATA->Set__DATA(ch_data);

	if(iActive__SIM_MODE > 0)	
	{
		ch_data.Format("PAGE.%1d", iLINK__LPx_ID);
		sCH__RSP_PAGE_DATA->Set__DATA(ch_data);
	}
	return 1;
}

int	CObj__RFID_CTRL
::Call__CID_WRITE(CII_OBJECT__VARIABLE* p_variable, 
				  CII_OBJECT__ALARM* p_alarm)
{
	int page_id = 0;
	aEXT_CH__PARA_RFID_PAGE_ID->Set__VALUE(page_id);

	CString ch_data = sCH__PARA_CID_DATA->Get__STRING();

	int r_flag = soEXT_CH__RFID_WRITE->Set__DATA(ch_data);

	if(iActive__SIM_MODE > 0)
	{
		return 1;
	}
	return r_flag;
}
int	CObj__RFID_CTRL
::Call__PAGE_WRITE(CII_OBJECT__VARIABLE* p_variable, 
				   CII_OBJECT__ALARM* p_alarm)
{
	int page_id = (int) aCH__PARA_PAGE_ID->Get__VALUE();
	aEXT_CH__PARA_RFID_PAGE_ID->Set__VALUE(page_id);

	CString ch_data = sCH__PARA_PAGE_DATA->Get__STRING();

	int r_flag = soEXT_CH__RFID_WRITE->Set__DATA(ch_data);

	if(iActive__SIM_MODE > 0)
	{
		return 1;
	}
	return r_flag;
}

// ...
int  CObj__RFID_CTRL::Is__LP_AUTO_MODE()
{
	if(dEXT_CH__LINK_PIO_ACTIVE_FA_AUTO->Check__DATA(STR__ON) > 0)
	{
		return 1;
	}

	return -1;
}

int  CObj__RFID_CTRL::Check__ERROR(CII_OBJECT__ALARM* p_alarm, const CString& ctrl_mode)
{
	if(sEXT_CH__MON_COMMUNICATION_STATE->Check__DATA(STR__ONLINE) < 0)
	{
		int alarm_id = ALID__OFFLINE_ALARM;

		p_alarm->Post__ALARM(alarm_id);
		return -1;
	}

	// ...
	int alarm_id;
	CString alm_title;
	CString alm_msg;
	CString r_act;

	if(iActive__SIM_MODE > 0)
	{
		sEXT_CH__LP_INFO__RFID_ERROR_CODE->Set__DATA(STR__NONE);
		return 1;
	}

	if(sEXT_CH__MON_COMMUNICATION_STATE->Check__DATA(STR__ONLINE) < 0)
	{
		if(ctrl_mode.CompareNoCase(CTRL_MODE__CID_READ) == 0)
		{
			if(Is__LP_AUTO_MODE() > 0)
			{
				alarm_id = ALID__OFFLINE_ALARM_FULL_AUTO;

				p_alarm->Check__ALARM(alarm_id,r_act);
				p_alarm->Post__ALARM(alarm_id);

				return 1;
			}
			else
			{
				alarm_id = ALID__OFFLINE_ALARM_NOT_FULL_AUTO;
				p_alarm->Popup__ALARM(alarm_id,r_act);		

					 if(r_act.CompareNoCase(ACT__RETRY) == 0)		return 0;
				else if(r_act.CompareNoCase(ACT__ABORT) == 0)		return -1;

				return 1;
			}
		}
		else
		{
			alarm_id = ALID__OFFLINE_ALARM;
			p_alarm->Popup__ALARM(alarm_id,r_act);

			if(r_act.CompareNoCase(ACT__RETRY) == 0)				return 0;

			return -1;
		}
	}

	// ERROR.CHECK ...
	{
		CString err_code = sEXT_CH__LP_INFO__RFID_ERROR_CODE->Get__STRING();

		if(dCH__CFG_TAG_READ_ID_INSTALLED_CHECK_SKIP->Check__DATA("TRUE") > 0)
		{
			if(err_code.CompareNoCase("NOTAG") == 0)
			{
				return 1;
			}
		}

		if(err_code.CompareNoCase("AUTOFAIL") == 0)
		{
			if(ctrl_mode.CompareNoCase(CTRL_MODE__CID_READ) == 0)
			{
				if(Is__LP_AUTO_MODE() > 0)
				{
					alarm_id = ALID__RF_AUTOFAIL_FULL_AUTO;

					p_alarm->Check__ALARM(alarm_id,r_act);
					p_alarm->Post__ALARM(alarm_id);

					sEXT_CH__LP_INFO__RFID_ERROR_CODE->Set__DATA(STR__NONE);
					return 1;
				}
				else
				{
					alarm_id = ALID__RF_AUTOFAIL_NOT_FULL_AUTO;

					p_alarm->Popup__ALARM(alarm_id,r_act);	

					sEXT_CH__LP_INFO__RFID_ERROR_CODE->Set__DATA(STR__NONE);

						 if(r_act.CompareNoCase(ACT__RETRY) == 0)		return 0;
					else if(r_act.CompareNoCase(ACT__ABORT) == 0)		return OBJ_ABORT;

					return 1;
				}
			}
			else
			{
				alarm_id = ALID__RF_AUTOFAIL;

				p_alarm->Check__ALARM(alarm_id,r_act);
				p_alarm->Post__ALARM(alarm_id);

				sEXT_CH__LP_INFO__RFID_ERROR_CODE->Set__DATA(STR__NONE);
				return -1;
			}
		}
		else if(err_code.CompareNoCase("EXFAIL") == 0)
		{
			if(ctrl_mode.CompareNoCase(CTRL_MODE__CID_READ) == 0)
			{
				if(Is__LP_AUTO_MODE() > 0)
				{
					alarm_id = ALID__RF_EXFAIL_FULL_AUTO;

					p_alarm->Check__ALARM(alarm_id,r_act);
					p_alarm->Post__ALARM(alarm_id);

					sEXT_CH__LP_INFO__RFID_ERROR_CODE->Set__DATA(STR__NONE);
					return 1;
				}
				else
				{
					alarm_id = ALID__RF_EXFAIL_NOT_FULL_AUTO;

					p_alarm->Popup__ALARM(alarm_id,r_act);	

					sEXT_CH__LP_INFO__RFID_ERROR_CODE->Set__DATA(STR__NONE);

						 if(r_act.CompareNoCase(ACT__RETRY) == 0)		return 0;
					else if(r_act.CompareNoCase(ACT__ABORT) == 0)		return -1;

					return 1;
				}
			}
			else
			{
				alarm_id = ALID__RF_EXFAIL;

				p_alarm->Check__ALARM(alarm_id,r_act);
				p_alarm->Post__ALARM(alarm_id);

				sEXT_CH__LP_INFO__RFID_ERROR_CODE->Set__DATA(STR__NONE);
				return -1;
			}
		}
		else if(err_code.CompareNoCase("WRITEFAIL") == 0)
		{
			if(ctrl_mode.CompareNoCase(CTRL_MODE__CID_READ) == 0)
			{
				if(Is__LP_AUTO_MODE() > 0)
				{
					alarm_id = ALID__RF_WRITEFAIL_FULL_AUTO;

					p_alarm->Check__ALARM(alarm_id,r_act);
					p_alarm->Post__ALARM(alarm_id);

					sEXT_CH__LP_INFO__RFID_ERROR_CODE->Set__DATA(STR__NONE);
					return 1;
				}
				else
				{
					alarm_id = ALID__RF_WRITEFAIL_NOT_FULL_AUTO;

					p_alarm->Popup__ALARM(alarm_id,r_act);	

					sEXT_CH__LP_INFO__RFID_ERROR_CODE->Set__DATA(STR__NONE);

						 if(r_act.CompareNoCase(ACT__RETRY) == 0)		return 0;
					else if(r_act.CompareNoCase(ACT__ABORT) == 0)		return -1;

					return 1;
				}
			}
			else
			{
				alarm_id = ALID__RF_WRITEFAIL;

				p_alarm->Check__ALARM(alarm_id,r_act);
				p_alarm->Post__ALARM(alarm_id);

				sEXT_CH__LP_INFO__RFID_ERROR_CODE->Set__DATA(STR__NONE);
				return -1;
			}
		}
		else if(err_code.CompareNoCase("NOTAG") == 0)
		{
			if(ctrl_mode.CompareNoCase(CTRL_MODE__CID_READ) == 0)
			{
				if(Is__LP_AUTO_MODE() > 0)
				{
					alarm_id = ALID__RF_NOTAG_FULL_AUTO;

					p_alarm->Check__ALARM(alarm_id,r_act);
					p_alarm->Post__ALARM(alarm_id);

					sEXT_CH__LP_INFO__RFID_ERROR_CODE->Set__DATA(STR__NONE);
					return 1;
				}
				else
				{
					alarm_id = ALID__RF_NOTAG_NOT_FULL_AUTO;

					p_alarm->Popup__ALARM(alarm_id,r_act);	

					sEXT_CH__LP_INFO__RFID_ERROR_CODE->Set__DATA(STR__NONE);

						 if(r_act.CompareNoCase(ACT__RETRY) == 0)		return 0;
					else if(r_act.CompareNoCase(ACT__ABORT) == 0)		return -1;

					return 1;
				}
			}
			else
			{
				alarm_id = ALID__RF_NOTAG;

				p_alarm->Check__ALARM(alarm_id,r_act);
				p_alarm->Post__ALARM(alarm_id);

				sEXT_CH__LP_INFO__RFID_ERROR_CODE->Set__DATA(STR__NONE);
				return -1;
			}
		}
		else if(err_code.CompareNoCase("INVALID1") == 0)
		{
			if(ctrl_mode.CompareNoCase(CTRL_MODE__CID_READ) == 0)
			{
				if(Is__LP_AUTO_MODE() > 0)
				{
					alarm_id = ALID__RF_INVALID1_FULL_AUTO;

					p_alarm->Check__ALARM(alarm_id,r_act);
					p_alarm->Post__ALARM(alarm_id);

					sEXT_CH__LP_INFO__RFID_ERROR_CODE->Set__DATA(STR__NONE);
					return 1;
				}
				else
				{
					alarm_id = ALID__RF_INVALID1_NOT_FULL_AUTO;

					p_alarm->Popup__ALARM(alarm_id,r_act);	

					sEXT_CH__LP_INFO__RFID_ERROR_CODE->Set__DATA(STR__NONE);

						 if(r_act.CompareNoCase(ACT__RETRY) == 0)		return 0;
					else if(r_act.CompareNoCase(ACT__ABORT) == 0)		return -1;

					return 1;
				}
			}
			else
			{
				alarm_id = ALID__RF_INVALID1;
				p_alarm->Check__ALARM(alarm_id,r_act);
				p_alarm->Post__ALARM(alarm_id);

				sEXT_CH__LP_INFO__RFID_ERROR_CODE->Set__DATA(STR__NONE);
				return -1;
			}
		}
		else if(err_code.CompareNoCase("UNKNOWN") == 0)
		{
			if(ctrl_mode.CompareNoCase("CID_READ") == 0)
			{
				if(Is__LP_AUTO_MODE() > 0)
				{
					alarm_id = ALID__RF_UNKNOWN_FULL_AUTO;

					p_alarm->Check__ALARM(alarm_id,r_act);
					p_alarm->Post__ALARM(alarm_id);

					sEXT_CH__LP_INFO__RFID_ERROR_CODE->Set__DATA(STR__NONE);
					return 1;
				}
				else
				{
					alarm_id = ALID__RF_UNKNOWN_NOT_FULL_AUTO;

					p_alarm->Popup__ALARM(alarm_id,r_act);	

					sEXT_CH__LP_INFO__RFID_ERROR_CODE->Set__DATA(STR__NONE);

						 if(r_act.CompareNoCase(ACT__RETRY) == 0)		return 0;
					else if(r_act.CompareNoCase(ACT__ABORT) == 0)		return -1;

					return 1;
				}
			}
			else
			{
				alarm_id = ALID__RF_UNKNOWN;

				p_alarm->Check__ALARM(alarm_id,r_act);
				p_alarm->Post__ALARM(alarm_id);

				sEXT_CH__LP_INFO__RFID_ERROR_CODE->Set__DATA(STR__NONE);
				return -1;
			}
		}
		else if(err_code.CompareNoCase("UNCONFIG") == 0)
		{
			if(ctrl_mode.CompareNoCase(CTRL_MODE__CID_READ) == 0)
			{
				if(Is__LP_AUTO_MODE() > 0)
				{
					alarm_id = ALID__RF_UNCONFIG_FULL_AUTO;

					p_alarm->Check__ALARM(alarm_id,r_act);
					p_alarm->Post__ALARM(alarm_id);

					sEXT_CH__LP_INFO__RFID_ERROR_CODE->Set__DATA(STR__NONE);
					return 1;
				}
				else
				{
					alarm_id = ALID__RF_UNCONFIG_NOT_FULL_AUTO;

					p_alarm->Popup__ALARM(alarm_id,r_act);	

					sEXT_CH__LP_INFO__RFID_ERROR_CODE->Set__DATA(STR__NONE);

						 if(r_act.CompareNoCase("RETRY") == 0)			return 0;
					else if(r_act.CompareNoCase("ABORT") == 0)			return -1;

					return 1;
				}
			}
			else
			{
				alarm_id = ALID__RF_UNCONFIG;

				p_alarm->Check__ALARM(alarm_id,r_act);
				p_alarm->Post__ALARM(alarm_id);

				sEXT_CH__LP_INFO__RFID_ERROR_CODE->Set__DATA(STR__NONE);
				return -1;
			}
		}
		else if(err_code.CompareNoCase("CHECK") == 0)
		{
			if(ctrl_mode.CompareNoCase(CTRL_MODE__CID_READ) == 0)
			{
				if(Is__LP_AUTO_MODE() > 0)
				{
					alarm_id = ALID__RF_CHECK_FULL_AUTO;

					p_alarm->Check__ALARM(alarm_id,r_act);
					p_alarm->Post__ALARM(alarm_id);

					sEXT_CH__LP_INFO__RFID_ERROR_CODE->Set__DATA(STR__NONE);
					return 1;
				}
				else
				{
					alarm_id = ALID__RF_CHECK_NOT_FULL_AUTO;

					p_alarm->Popup__ALARM(alarm_id,r_act);	

					sEXT_CH__LP_INFO__RFID_ERROR_CODE->Set__DATA(STR__NONE);

						 if(r_act.CompareNoCase(ACT__RETRY) == 0)		return 0;
					else if(r_act.CompareNoCase(ACT__ABORT) == 0)		return -1;

					return 1;
				}
			}
			else
			{
				alarm_id = ALID__RF_CHECK;

				p_alarm->Check__ALARM(alarm_id,r_act);
				p_alarm->Post__ALARM(alarm_id);

				sEXT_CH__LP_INFO__RFID_ERROR_CODE->Set__DATA(STR__NONE);
				return -1;
			}
		}
		else if(err_code.CompareNoCase("VOIDACKN") == 0)
		{
			if(ctrl_mode.CompareNoCase(CTRL_MODE__CID_READ) == 0)
			{
				if(Is__LP_AUTO_MODE() > 0)
				{
					alarm_id = ALID__RF_VOIDACKNE_FULL_AUTO;

					p_alarm->Check__ALARM(alarm_id,r_act);
					p_alarm->Post__ALARM(alarm_id);

					sEXT_CH__LP_INFO__RFID_ERROR_CODE->Set__DATA(STR__NONE);
					return 1;
				}
				else
				{
					alarm_id = ALID__RF_VOIDACKNE_NOT_FULL_AUTO;

					p_alarm->Popup__ALARM(alarm_id,r_act);	

					sEXT_CH__LP_INFO__RFID_ERROR_CODE->Set__DATA(STR__NONE);

						 if(r_act.CompareNoCase(ACT__RETRY) == 0)		return 0;
					else if(r_act.CompareNoCase(ACT__ABORT) == 0)		return -1;

					return 1;
				}
			}
			else
			{
				alarm_id = ALID__RF_VOIDACKNE;

				p_alarm->Check__ALARM(alarm_id,r_act);
				p_alarm->Post__ALARM(alarm_id);

				sEXT_CH__LP_INFO__RFID_ERROR_CODE->Set__DATA(STR__NONE);
				return -1;
			}
		}
		else if(err_code.CompareNoCase("LOCKED") == 0)
		{
			if(ctrl_mode.CompareNoCase(CTRL_MODE__CID_READ) == 0)
			{
				if(Is__LP_AUTO_MODE() > 0)
				{
					alarm_id = ALID__RF_LOCKED_FULL_AUTO;

					p_alarm->Check__ALARM(alarm_id,r_act);
					p_alarm->Post__ALARM(alarm_id);

					sEXT_CH__LP_INFO__RFID_ERROR_CODE->Set__DATA(STR__NONE);
					return 1;
				}
				else
				{
					alarm_id = ALID__RF_LOCKED_NOT_FULL_AUTO;

					p_alarm->Popup__ALARM(alarm_id,r_act);	

					sEXT_CH__LP_INFO__RFID_ERROR_CODE->Set__DATA(STR__NONE);

						 if(r_act.CompareNoCase(ACT__RETRY) == 0)		return 0;
					else if(r_act.CompareNoCase(ACT__ABORT) == 0)		return -1;

					return 1;
				}
			}
			else
			{
				alarm_id = ALID__RF_LOCKED;

				p_alarm->Check__ALARM(alarm_id,r_act);
				p_alarm->Post__ALARM(alarm_id);

				sEXT_CH__LP_INFO__RFID_ERROR_CODE->Set__DATA(STR__NONE);
				return -1;
			}
		}
		else if(err_code.CompareNoCase("MSGLEN") == 0)
		{
			if(ctrl_mode.CompareNoCase(CTRL_MODE__CID_READ) == 0)
			{
				if(Is__LP_AUTO_MODE() > 0)
				{
					alarm_id = ALID__RF_MSGLEN_FULL_AUTO;

					p_alarm->Check__ALARM(alarm_id,r_act);
					p_alarm->Post__ALARM(alarm_id);

					sEXT_CH__LP_INFO__RFID_ERROR_CODE->Set__DATA(STR__NONE);
					return 1;
				}
				else
				{
					alarm_id = ALID__RF_MSGLEN_NOT_FULL_AUTO;

					p_alarm->Popup__ALARM(alarm_id,r_act);	

					sEXT_CH__LP_INFO__RFID_ERROR_CODE->Set__DATA(STR__NONE);

						 if(r_act.CompareNoCase(ACT__RETRY) == 0)		return 0;
					else if(r_act.CompareNoCase(ACT__ABORT) == 0)		return -1;

					return 1;
				}
			}
			else
			{
				alarm_id = ALID__RF_MSGLEN;

				p_alarm->Check__ALARM(alarm_id,r_act);
				p_alarm->Post__ALARM(alarm_id);

				sEXT_CH__LP_INFO__RFID_ERROR_CODE->Set__DATA(STR__NONE);
				return -1;
			}
		}
		else if(err_code.CompareNoCase("INVALID2") == 0)
		{
			if(ctrl_mode.CompareNoCase(CTRL_MODE__CID_READ) == 0)
			{
				if(Is__LP_AUTO_MODE() > 0)
				{
					alarm_id = ALID__RF_INVALID2_FULL_AUTO;

					p_alarm->Check__ALARM(alarm_id,r_act);
					p_alarm->Post__ALARM(alarm_id);

					sEXT_CH__LP_INFO__RFID_ERROR_CODE->Set__DATA(STR__NONE);
					return 1;
				}
				else
				{
					alarm_id = ALID__RF_INVALID2_NOT_FULL_AUTO;

					p_alarm->Popup__ALARM(alarm_id,r_act);	

					sEXT_CH__LP_INFO__RFID_ERROR_CODE->Set__DATA(STR__NONE);

						 if(r_act.CompareNoCase(ACT__RETRY) == 0)		return 0;
					else if(r_act.CompareNoCase(ACT__ABORT) == 0)		return -1;

					return 1;
				}
			}
			else
			{
				alarm_id = ALID__RF_INVALID2;

				p_alarm->Check__ALARM(alarm_id,r_act);
				p_alarm->Post__ALARM(alarm_id);

				sEXT_CH__LP_INFO__RFID_ERROR_CODE->Set__DATA(STR__NONE);
				return -1;
			}
		}
		else if(err_code.CompareNoCase("NOACKN") == 0)
		{
			if(ctrl_mode.CompareNoCase(CTRL_MODE__CID_READ) == 0)
			{
				if(Is__LP_AUTO_MODE() > 0)
				{
					alarm_id = ALID__RF_NOACKN_FULL_AUTO;

					p_alarm->Check__ALARM(alarm_id,r_act);
					p_alarm->Post__ALARM(alarm_id);

					sEXT_CH__LP_INFO__RFID_ERROR_CODE->Set__DATA(STR__NONE);
					return 1;
				}
				else
				{
					alarm_id = ALID__RF_NOACKN_NOT_FULL_AUTO;

					p_alarm->Popup__ALARM(alarm_id,r_act);	

					sEXT_CH__LP_INFO__RFID_ERROR_CODE->Set__DATA(STR__NONE);

						 if(r_act.CompareNoCase(ACT__RETRY) == 0)		return 0;
					else if(r_act.CompareNoCase(ACT__ABORT) == 0)		return -1;

					return 1;
				}
			}
			else
			{
				alarm_id = ALID__RF_NOACKN;

				p_alarm->Check__ALARM(alarm_id,r_act);
				p_alarm->Post__ALARM(alarm_id);

				sEXT_CH__LP_INFO__RFID_ERROR_CODE->Set__DATA(STR__NONE);
				return -1;
			}
		}
		else
		{
			return 1;
		}
	}

	return 1;
}

