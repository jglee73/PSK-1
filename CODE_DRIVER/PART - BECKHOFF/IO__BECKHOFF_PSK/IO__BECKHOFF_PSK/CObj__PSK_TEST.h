#pragma once

#include "Interface_Code.h"

#include "CObj__PSK_TEST__ALID.h"
#include "CObj__PSK_TEST__DEF.h"

#include "CCls__ADS_CTRL.h"
#include "CCls__Error_Mng.h"


class CObj__PSK_TEST : public __IOBJ__IO_TYPE
{
private:
	//-------------------------------------------------------------------------
	CString	sObject_Name;

	//-------------------------------------------------------------------------
	SCX__USER_LOG_CTRL xI__APP_LOG_CTRL;
	SCX__USER_LOG_CTRL xI__DRV_LOG_CTRL;

	int iFLAG__DRV_FLAG;

	int iActive__SIM_MODE;

	// ...
	CII_EXT_OBJECT__CTRL* pOBJ_CTRL;

	CCls__Error_Mng mERR_MSG;

	bool bActive__DRV_PRINT;
	//

	//-------------------------------------------------------------------------
	//  INTERNAL PROPERTY

	// OBJ ...
	CX__VAR_STRING_CTRL  sCH__OBJ_MSG;

	// MON ...
	CX__VAR_STRING_CTRL  sCH__MON_COMM_STATE;

	// INFO ...
	CX__VAR_STRING_CTRL  sCH__INFO_PLC_NETID_STR;
	CX__VAR_STRING_CTRL  sCH__INFO_PLC_NETID_X[_CFG__NETID_SIZE];

	CX__VAR_STRING_CTRL  sCH__INFO_PLC_PORT;
	CX__VAR_STRING_CTRL  sCH__INFO_PLC_ADS_NAME_OUTPUT;
	CX__VAR_STRING_CTRL  sCH__INFO_PLC_ADS_NAME_INPUT;

	CX__VAR_STRING_CTRL  sCH__INFO_IO_FILE;

	//
	CX__VAR_STRING_CTRL  sCH__INFO_DRV__DEV_NAME;
	CX__VAR_STRING_CTRL  sCH__INFO_DRV__VERSION;
	CX__VAR_STRING_CTRL  sCH__INFO_DRV__REVISION;
	CX__VAR_STRING_CTRL  sCH__INFO_DRV__BUILD;

	// CFG ...
	CX__VAR_DIGITAL_CTRL dCH__CFG_IO_TEST_MODE;

	/*
	// ADS ...
	CX__VAR_DIGITAL_CTRL diCH__ADS_ACTIVE;
	CX__VAR_DIGITAL_CTRL doCH__ADS_ACTIVE;
	*/
	//

	//-------------------------------------------------------------------------
	//  EXTERNAL PROPERTY

	// ...
	int iPARA__ADS_PORT;	

	CString sPARA__ADS_NAME_OUTPUT;
	CString sPARA__ADS_NAME_INPUT;
	//


	//-------------------------------------------------------------------------
	CString sMODE__INIT;
	int  Call__INIT(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	//
	CString sMODE__ADS_GET_INFO;
	int  Call__ADS_GET_INFO(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	CString sMODE__ADS_BLOCK_LINK;
	int  Call__ADS_BLOCK_LINK(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	CString sMODE__ADS_UPDATE_READING;
	int  Call__ADS_UPDATE_READING(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	CString sMODE__ADS_UPDATE_SETTING;
	int  Call__ADS_UPDATE_SETTING(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	//
	void Get__PLC_NETID(const CString& str_netid, CStringArray& l_id);

	int  Init__ADS_DRIVER();
	int  Update__ADS_ALL_INFO();
	int  Update__ADS_IN_INFO(const bool active_print);
	int  Update__ADS_OUT_INFO(const bool active_print);

	int  Update__ADS_OUTPUT_CHANNEL();
	int  Update__IO_OUTPUT_CHANNEL();

	// ...
	void Mon__MONITOR(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);
	void Mon__ADS_CHECK(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);
	//


public:
	CObj__PSK_TEST();
	~CObj__PSK_TEST();

	//-------------------------------------------------------------------------
	int __DEFINE__CONTROL_MODE(obj, l_mode);
	int __DEFINE__VERSION_HISTORY(version);

	int __DEFINE__VARIABLE_STD(p_variable);
	int __DEFINE__VARIABLE_IO(p_io_variable);

	int __DEFINE__ALARM(p_alarm);

	//-------------------------------------------------------------------------
	int __INITIALIZE__OBJECT(p_variable,p_ext_obj_create);
	int __INITIALIZE__IO(p_io_para);

	//-------------------------------------------------------------------------
	int __CALL__CONTROL_MODE(mode, p_debug, p_variable, p_alarm);
	int __CALL__MONITORING(id, p_variable, p_alarm);

	int __Close__OBJECT();

	//-------------------------------------------------------------------------
	int __Read__ANALOG(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, double& read_data);
	int __Read__DIGITAL(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, CString& read_data,int& item_index);
	int __Read__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, CString& read_data);

	int __Write__ANALOG(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const double set_data);
	int __Write__DIGITAL(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data,const int item_index);
	int __Write__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data);
};

