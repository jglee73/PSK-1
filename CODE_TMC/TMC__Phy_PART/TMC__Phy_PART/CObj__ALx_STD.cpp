#include "StdAfx.h"
#include "CObj__ALx_STD.h"
#include "CObj__ALx_STD__DEF.h"


//-------------------------------------------------------------------------
CObj__ALx_STD::CObj__ALx_STD()
{

}
CObj__ALx_STD::~CObj__ALx_STD()
{

}

//-------------------------------------------------------------------------
int CObj__ALx_STD::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT,  "INIT");
		ADD__CTRL_VAR(sMODE__ALIGN, "ALIGN");
	}
	return 1;
}
int CObj__ALx_STD::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}

int CObj__ALx_STD::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;
	
	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString str_name;
	CString dsc_item_list;
	int i;

	// ...
	{
		str_name = "PARA.SLOT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "slot", 0, 1, 2, "");
		LINK__VAR_ANALOG_CTRL(aCH__PARA_SLOT, str_name);
	}

	// ...
	{
		p_variable->Get__STD_DESCRIPTION(DSP__SLOT_STATUS,dsc_item_list);

		for(i=0;i<CFG_ALx__SLOT_MAX;i++)
		{
			// Slot Status 
			str_name.Format("OTR.OUT.MON.dSLOT%002d.STATUS",i+1);
			STD__ADD_DIGITAL_WITH_X_OPTION(str_name, dsc_item_list,"");
			LINK__VAR_DIGITAL_CTRL(dCH__SLOT_STATUS[i], str_name);

			// Slot Title
			str_name.Format("OTR.OUT.MON.sSLOT%002d.TITLE",i+1);
			STD__ADD_STRING_WITH_X_OPTION(str_name, "");
			LINK__VAR_STRING_CTRL(sCH__SLOT_TITLE[i], str_name);
		}

		// Slot Title
		str_name.Format("INR.sMSG");
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MSG, str_name);
	}

	return 1;
}


// ...
#define  ACT__RETRY_ABORT						\
l_act.RemoveAll();								\
l_act.Add("RETRY");								\
l_act.Add("ABORT");


int CObj__ALx_STD::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	return 1;
}

int CObj__ALx_STD::__Define__USER_FUNCTION(CII_DEFINE__FUNCTION *p_fnc_ctrl)
{
	p_fnc_ctrl->Link__ERROR_FEEDBACK(&mERROR__USER_FNC);

	return 1;
}

//-------------------------------------------------------------------------
int CObj__ALx_STD::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	CString def_name;
	CString def_data;
	CString ch_name;
	CString obj_name;
	CString var_name;

	int al_id = -1;


	// DB_CFG ...
	{
		def_name = "OBJ__DB";
		p_variable->Get__DEF_CONST_DATA(def_name, def_data);

		// ...
		{
			var_name = "MAINT.TARGET.LLx.NAME";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__MAINT_TARGT_LLx_NAME, def_data,var_name);

			var_name = "MODULE.LINK.sTARGET.LLx.NAME";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__MODULE_LINK_TARGT_LLx_NAME, def_data,var_name);

			//
			var_name = "CUR.AL1.TARGET.LLx.NAME";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__CUR_AL1_TARGET_LLx_NAME, def_data,var_name);

			var_name = "CUR.AL1.CCD.POS";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__CUR_AL1_CCD_POS, def_data,var_name);
		}

		// ...
		{
			var_name = "CFG.LL1.ALIGN.POS";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__CFG_LL1_ALIGN_ANGLE, def_data,var_name);

			var_name = "CFG.LL2.ALIGN.POS";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__CFG_LL2_ALIGN_ANGLE, def_data,var_name);

			var_name = "CFG.LL3.ALIGN.POS";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__CFG_LL3_ALIGN_ANGLE, def_data,var_name);

			var_name = "CFG.LL4.ALIGN.POS";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__CFG_LL4_ALIGN_ANGLE, def_data,var_name);
		}

		// ...
		{
			var_name = "CFG.aLL1.POST.POSITION.INCREMENT";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__CFG_LL1_POST_POSITION_INCREMENT, def_data,var_name);

			var_name = "CFG.aLL2.POST.POSITION.INCREMENT"; 
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__CFG_LL2_POST_POSITION_INCREMENT, def_data,var_name);

			var_name = "CFG.aLL3.POST.POSITION.INCREMENT";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__CFG_LL3_POST_POSITION_INCREMENT, def_data,var_name);

			var_name = "CFG.aLL4.POST.POSITION.INCREMENT"; 
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__CFG_LL4_POST_POSITION_INCREMENT, def_data,var_name);
		}

		// ...
		{
			var_name = "CFG.aLL1.POST.POSITION.INCREMENT.RANGE";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__CFG_LL1_POST_POSITION_INCREMENT_RANGE, def_data,var_name);

			var_name = "CFG.aLL2.POST.POSITION.INCREMENT.RANGE";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__CFG_LL2_POST_POSITION_INCREMENT_RANGE, def_data,var_name);

			var_name = "CFG.aLL3.POST.POSITION.INCREMENT.RANGE";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__CFG_LL3_POST_POSITION_INCREMENT_RANGE, def_data,var_name);

			var_name = "CFG.aLL4.POST.POSITION.INCREMENT.RANGE";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__CFG_LL4_POST_POSITION_INCREMENT_RANGE, def_data,var_name);
		}

		// ...
		{
			var_name = "CFG.aLL1.POST.POSITION.INCREMENT.START.ANGLE";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__CFG_LL1_POST_POSITION_INCREMENT_START_ANGLE, def_data,var_name);

			var_name = "CFG.aLL2.POST.POSITION.INCREMENT.START.ANGLE";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__CFG_LL2_POST_POSITION_INCREMENT_START_ANGLE, def_data,var_name);

			var_name = "CFG.aLL3.POST.POSITION.INCREMENT.START.ANGLE";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__CFG_LL3_POST_POSITION_INCREMENT_START_ANGLE, def_data,var_name);

			var_name = "CFG.aLL4.POST.POSITION.INCREMENT.START.ANGLE";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__CFG_LL4_POST_POSITION_INCREMENT_START_ANGLE, def_data,var_name);
		}

		// ...
		{
			var_name = "CFG.LL1.POST.POSITION.INCREMENT.APPLY";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CFG_LL1_POST_POSITION_INCREMENT_APPLY, def_data,var_name);

			var_name = "CFG.LL2.POST.POSITION.INCREMENT.APPLY";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CFG_LL2_POST_POSITION_INCREMENT_APPLY, def_data,var_name);

			var_name = "CFG.LL3.POST.POSITION.INCREMENT.APPLY";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CFG_LL3_POST_POSITION_INCREMENT_APPLY, def_data,var_name);

			var_name = "CFG.LL4.POST.POSITION.INCREMENT.APPLY";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CFG_LL4_POST_POSITION_INCREMENT_APPLY, def_data,var_name);
		}

		// ...
		{
			var_name = "CUR.aLL1.POST.POSITION.INCREMENT.ANGLE";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__CUR_LL1_POST_POSITION_INCREMENT_ANGLE, def_data,var_name);

			var_name = "CUR.aLL2.POST.POSITION.INCREMENT.ANGLE"; 
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__CUR_LL2_POST_POSITION_INCREMENT_ANGLE, def_data,var_name);

			var_name = "CUR.aLL3.POST.POSITION.INCREMENT.ANGLE";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__CUR_LL3_POST_POSITION_INCREMENT_ANGLE, def_data,var_name);

			var_name = "CUR.aLL4.POST.POSITION.INCREMENT.ANGLE"; 
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__CUR_LL4_POST_POSITION_INCREMENT_ANGLE, def_data,var_name);
		}
	}

	// LINK : CHANNEL ...
	{
		//
		def_name = "CH.AL_OBJ_STATUS";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);

		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__OBJ_STATUS, obj_name,var_name);

		//
		def_name = "CH.CFG_SLOT_MAX";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);

		LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__CFG_SLOT_MAX, obj_name,var_name);
	}

	// ALx OBJECT ...
	{
		def_name = "OBJ__AL";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

		pALx__OBJ_CTRL = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);
	
		//
		var_name = "PARA.STN.SLOT";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__ALx_PARA_SLOT, obj_name,var_name);

		var_name = "PARA.CCD.POS";
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__ALx_PARA_CCD_POS, obj_name,var_name);
	}

	// ...
	{
		CString file_name;
		CString log_msg;

		file_name.Format("%s_App.log", sObject_Name);

		log_msg  = "\n\n";
		log_msg += "//------------------------------------------------------------------------";

		xLOG_CTRL->CREATE__SUB_DIRECTORY(sObject_Name);
		xLOG_CTRL->SET__PROPERTY(file_name,24*5,60);

		xLOG_CTRL->DISABLE__TIME_LOG();
		xLOG_CTRL->WRITE__LOG(log_msg);

		xLOG_CTRL->ENABLE__TIME_LOG();
		xLOG_CTRL->WRITE__LOG("   START   \n");
	}
	return 1;
}

//-------------------------------------------------------------------------
int CObj__ALx_STD::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	CString log_msg;
	CString log_bff;

	// ...
	{	
		log_msg.Format("Start ... :  [%s]",mode);

		xLOG_CTRL->WRITE__LOG(log_msg);
		sCH__MSG->Set__DATA(log_msg);
	}

	int flag = -1;

	if(mode.CompareNoCase(sMODE__ALIGN) == 0)
	{
		CString llx_name;
		CString al_angle;

		CString var_data;

		if(sEXT_CH__OBJ_STATUS->Check__DATA(STR__MAINTMODE) > 0)
		{
			dEXT_CH__MAINT_TARGT_LLx_NAME->Get__DATA(llx_name);
		}
		else
		{
			sEXT_CH__MODULE_LINK_TARGT_LLx_NAME->Get__DATA(llx_name);	
			if(llx_name == "")		llx_name = "LBA";
		}

		// ...
		{
			log_msg = "\n";

			log_bff.Format("[%s] Align Info ... \n", llx_name);
			log_msg += log_bff;
		}

		if(llx_name.CompareNoCase("LBA") == 0)
		{
			if(dEXT_CH__CFG_LL1_POST_POSITION_INCREMENT_APPLY->Check__DATA(STR__ENABLE) > 0)
			{
				aEXT_CH__CUR_LL1_POST_POSITION_INCREMENT_ANGLE->Get__DATA(var_data);
				double cur_angle = atof(var_data);

				aEXT_CH__CFG_LL1_POST_POSITION_INCREMENT->Get__DATA(var_data);
				double cfg_inc = atof(var_data);

				aEXT_CH__CFG_LL1_POST_POSITION_INCREMENT_RANGE->Get__DATA(var_data);
				double max_angle = atof(var_data);

				if(cur_angle > max_angle)		cur_angle = 0;

				// ...
				aEXT_CH__CFG_LL1_POST_POSITION_INCREMENT_START_ANGLE->Get__DATA(var_data);
				double start_angle = atof(var_data);

				al_angle.Format("%.0f", (start_angle+cur_angle));

				// ...
				{
					double next_angle = cur_angle + cfg_inc;
					if(next_angle > max_angle)		next_angle = 0;

					var_data.Format("%.0f", next_angle);
					aEXT_CH__CUR_LL1_POST_POSITION_INCREMENT_ANGLE->Set__DATA(var_data);
				}

				// ...
				{
					log_bff.Format("   CFG Increment Apply <- [%s] \n", STR__ENABLE);
					log_msg += log_bff;

					log_bff.Format("   Current Increment Angle <- [%.0f] \n", cur_angle);
					log_msg += log_bff;

					log_bff.Format("   CFG Increment Start Angle <- [%.0f] \n", start_angle);
					log_msg += log_bff;

					log_bff.Format("   CFG Increment Angle <- [%.0f] \n", cfg_inc);
					log_msg += log_bff;

					log_bff.Format("   CFG Increment Range <- [%.0f] \n", max_angle);
					log_msg += log_bff;

					log_bff.Format("   Target Align Angle <- [%s] \n", al_angle);
					log_msg += log_bff;
				}
			}	
			else
			{
				aEXT_CH__CFG_LL1_ALIGN_ANGLE->Get__DATA(al_angle);

				// ...
				{
					log_bff.Format("   Target Align Angle <- [%s] \n", al_angle);
					log_msg += log_bff;
				}
			}
		}
		else if(llx_name.CompareNoCase("LBB") == 0)
		{
			if(dEXT_CH__CFG_LL2_POST_POSITION_INCREMENT_APPLY->Check__DATA(STR__ENABLE) > 0)
			{
				aEXT_CH__CUR_LL2_POST_POSITION_INCREMENT_ANGLE->Get__DATA(var_data);
				double cur_angle = atof(var_data);

				aEXT_CH__CFG_LL2_POST_POSITION_INCREMENT->Get__DATA(var_data);
				double cfg_inc = atof(var_data);

				aEXT_CH__CFG_LL2_POST_POSITION_INCREMENT_RANGE->Get__DATA(var_data);
				double max_angle = atof(var_data);

				if(cur_angle > max_angle)		cur_angle = 0;

				// ...
				aEXT_CH__CFG_LL2_POST_POSITION_INCREMENT_START_ANGLE->Get__DATA(var_data);
				double start_angle = atof(var_data);

				al_angle.Format("%.0f", (start_angle+cur_angle));

				// ...
				{
					double next_angle = cur_angle + cfg_inc;
					if(next_angle > max_angle)		next_angle = 0;

					var_data.Format("%.0f", next_angle);
					aEXT_CH__CUR_LL2_POST_POSITION_INCREMENT_ANGLE->Set__DATA(var_data);
				}

				// ...
				{
					log_bff.Format("   CFG Increment Apply <- [%s] \n", STR__ENABLE);
					log_msg += log_bff;

					log_bff.Format("   Current Increment Angle <- [%.0f] \n", cur_angle);
					log_msg += log_bff;

					log_bff.Format("   CFG Increment Start Angle <- [%.0f] \n", start_angle);
					log_msg += log_bff;

					log_bff.Format("   CFG Increment Angle <- [%.0f] \n", cfg_inc);
					log_msg += log_bff;

					log_bff.Format("   CFG Increment Range <- [%.0f] \n", max_angle);
					log_msg += log_bff;

					log_bff.Format("   Target Align Angle <- [%s] \n", al_angle);
					log_msg += log_bff;
				}
			}	
			else
			{
				aEXT_CH__CFG_LL2_ALIGN_ANGLE->Get__DATA(al_angle);

				// ...
				{
					log_bff.Format("   Target Align Angle <- [%s] \n", al_angle);
					log_msg += log_bff;
				}
			}
		}
		else if(llx_name.CompareNoCase("LBC") == 0)
		{
			if(dEXT_CH__CFG_LL3_POST_POSITION_INCREMENT_APPLY->Check__DATA(STR__ENABLE) > 0)
			{
				aEXT_CH__CUR_LL3_POST_POSITION_INCREMENT_ANGLE->Get__DATA(var_data);
				double cur_angle = atof(var_data);

				aEXT_CH__CFG_LL3_POST_POSITION_INCREMENT->Get__DATA(var_data);
				double cfg_inc = atof(var_data);

				aEXT_CH__CFG_LL3_POST_POSITION_INCREMENT_RANGE->Get__DATA(var_data);
				double max_angle = atof(var_data);

				if(cur_angle > max_angle)		cur_angle = 0;

				// ...
				aEXT_CH__CFG_LL3_POST_POSITION_INCREMENT_START_ANGLE->Get__DATA(var_data);
				double start_angle = atof(var_data);

				al_angle.Format("%.0f", (start_angle+cur_angle));

				// ...
				{
					double next_angle = cur_angle + cfg_inc;
					if(next_angle > max_angle)		next_angle = 0;

					var_data.Format("%.0f", next_angle);
					aEXT_CH__CUR_LL3_POST_POSITION_INCREMENT_ANGLE->Set__DATA(var_data);
				}

				// ...
				{
					log_bff.Format("   CFG Increment Apply <- [%s] \n", STR__ENABLE);
					log_msg += log_bff;

					log_bff.Format("   Current Increment Angle <- [%.0f] \n", cur_angle);
					log_msg += log_bff;

					log_bff.Format("   CFG Increment Start Angle <- [%.0f] \n", start_angle);
					log_msg += log_bff;

					log_bff.Format("   CFG Increment Angle <- [%.0f] \n", cfg_inc);
					log_msg += log_bff;

					log_bff.Format("   CFG Increment Range <- [%.0f] \n", max_angle);
					log_msg += log_bff;

					log_bff.Format("   Target Align Angle <- [%s] \n", al_angle);
					log_msg += log_bff;
				}
			}	
			else
			{
				aEXT_CH__CFG_LL3_ALIGN_ANGLE->Get__DATA(al_angle);

				// ...
				{
					log_bff.Format("   Target Align Angle <- [%s] \n", al_angle);
					log_msg += log_bff;
				}
			}
		}
		else if(llx_name.CompareNoCase("LBD") == 0)
		{
			if(dEXT_CH__CFG_LL4_POST_POSITION_INCREMENT_APPLY->Check__DATA(STR__ENABLE) > 0)
			{
				aEXT_CH__CUR_LL4_POST_POSITION_INCREMENT_ANGLE->Get__DATA(var_data);
				double cur_angle = atof(var_data);

				aEXT_CH__CFG_LL4_POST_POSITION_INCREMENT->Get__DATA(var_data);
				double cfg_inc = atof(var_data);

				aEXT_CH__CFG_LL4_POST_POSITION_INCREMENT_RANGE->Get__DATA(var_data);
				double max_angle = atof(var_data);

				if(cur_angle > max_angle)		cur_angle = 0;

				// ...
				aEXT_CH__CFG_LL4_POST_POSITION_INCREMENT_START_ANGLE->Get__DATA(var_data);
				double start_angle = atof(var_data);

				al_angle.Format("%.0f", (start_angle+cur_angle));

				// ...
				{
					double next_angle = cur_angle + cfg_inc;
					if(next_angle > max_angle)		next_angle = 0;

					var_data.Format("%.0f", next_angle);
					aEXT_CH__CUR_LL4_POST_POSITION_INCREMENT_ANGLE->Set__DATA(var_data);
				}

				// ...
				{
					log_bff.Format("   CFG Increment Apply <- [%s] \n", STR__ENABLE);
					log_msg += log_bff;

					log_bff.Format("   Current Increment Angle <- [%.0f] \n", cur_angle);
					log_msg += log_bff;

					log_bff.Format("   CFG Increment Start Angle <- [%.0f] \n", start_angle);
					log_msg += log_bff;

					log_bff.Format("   CFG Increment Angle <- [%.0f] \n", cfg_inc);
					log_msg += log_bff;

					log_bff.Format("   CFG Increment Range <- [%.0f] \n", max_angle);
					log_msg += log_bff;

					log_bff.Format("   Target Align Angle <- [%s] \n", al_angle);
					log_msg += log_bff;
				}
			}	
			else
			{
				aEXT_CH__CFG_LL4_ALIGN_ANGLE->Get__DATA(al_angle);

				// ...
				{
					log_bff.Format("   Target Align Angle <- [%s] \n", al_angle);
					log_msg += log_bff;
				}
			}
		}

		sEXT_CH__CUR_AL1_TARGET_LLx_NAME->Set__DATA(llx_name);
		sEXT_CH__CUR_AL1_CCD_POS->Set__DATA(al_angle);

		xLOG_CTRL->WRITE__LOG(log_msg);
	}

	// ...
	{
			 IF__CTRL_MODE(sMODE__INIT)			flag = Call__INIT(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__ALIGN)		flag = Call__ALIGN(p_variable,p_alarm);
	}

	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{
		CString log_msg;
		log_msg.Format("Aborted ... :  [%s]",mode);

		xLOG_CTRL->WRITE__LOG(log_msg);
		sCH__MSG->Set__DATA(log_msg);
	}
	else
	{
		CString log_msg;
		log_msg.Format("Completed ... :  [%s]",mode);

		xLOG_CTRL->WRITE__LOG(log_msg);
		sCH__MSG->Set__DATA(log_msg);
	}

	return flag;
}
int CObj__ALx_STD::__CALL__MONITORING(id,p_variable,p_alarm)
{

	return 1;
}
