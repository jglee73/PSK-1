#pragma once
extern "C"
{
#include <stdio.h>
}
#include "Interface_Code.h"

#include "VTYRemoteMessages.h"
#define	EPD_RECIPE_DIRECTORY		".\\EPD_Recipe\\"

// ...
#define		CR						0x0D
#define		 LF						0x0A
#define		HUGE_STR_LENGTH			30000
#define		MAX_STR_LENGTH			2048
#define		DEFAULT_STR_LENGTH		256
#define		DATA_LENGTH				0x82
#define		MAX_DATA_CHANNEL		8


enum { OFF , ON };
enum { UNKNOWN, IDLE , RUN };
enum { STOPPED , RUNNING };	// Fan Status
enum { Normal, TempError, CommError , NAKError }; // Error Status

typedef struct
{
	//double dMonitor;	//0 - 1000.00
	double dMonitor[MAX_DATA_CHANNEL];
	int nWaveType;		//0:Unknown, 1:309nm, 2:387nm
	int nEndPoint;		//0:Off, 1:On
	int nRunning;		//0:Unknown, 1:Idle, 2:Run
	int nErrStatus;		//0:Normal, 1:Temp_Error, 2:CommError
	int nNakCommand;
	bool bRecvStart;
	char szChannelName[MAX_DATA_CHANNEL][DEFAULT_STR_LENGTH];
} REPORT;

class CObj__VERITY_STD : public __IOBJ__IO_TYPE
{
private:
	//-------------------------------------------------------------------------
	CString	sObject_Name;

	// ...
	SCX__USER_LOG_CTRL  mX__Log_Ctrl;
	SCX__ETHERNET_JGLEE mX__Net_Client;

	int iActive__SIM_MODE;
	//


	//-------------------------------------------------------------------------
	//  INTERNAL PROPERTY

	CX__VAR_STRING_CTRL sCH__COMM_STATE;
	//

	//-------------------------------------------------------------------------
	// INIT ...
	CString sMODE__INIT;
	CString sMODE__START;
	CString sMODE__STOP;
	CString sMODE__RESET;
	char	g_szRecipeName[128];
	
	int Call__INIT(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);
	//

	bool SEND_COMMAND( const unsigned char *_szSend , int _nLength );
	bool RECV_COMMAND( unsigned char *_pcData , const unsigned char *_pcSendData , int _nLength , int *_nDataLen );

	//-------------------------------------------------------------------------
	void Mon__IO_MONITORING(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);
	
	//
	CX__VAR_DIGITAL_CTRL	doCH__EPD_Start;
	CX__VAR_DIGITAL_CTRL	doCH__EPD_Stop;
	CX__VAR_DIGITAL_CTRL	doCH__EPD_Reset;
	CX__VAR_DIGITAL_CTRL	diCH__EPD_EndPoint;
	CX__VAR_DIGITAL_CTRL	diCH__EPD_Status;
	CX__VAR_DIGITAL_CTRL	diCH__EPD_SensorErr;
	CX__VAR_DIGITAL_CTRL	diCH__EPD_GetRecipe;
	CX__VAR_DIGITAL_CTRL	diCH__EPD_Nak_Command;
	CX__VAR_DIGITAL_CTRL	diCH__EPD_CommTest;
	CX__VAR_DIGITAL_CTRL	diCH__EPD_EndOverEtch;
	CX__VAR_DIGITAL_CTRL	diCH__EPD_Finish;
	CX__VAR_DIGITAL_CTRL	diCH__EPD_TimeSync;

	CX__VAR_ANALOG_CTRL		aiCH__EPD_Monitor1;
	CX__VAR_ANALOG_CTRL		aiCH__EPD_Monitor2;
	CX__VAR_ANALOG_CTRL		aiCH__EPD_Monitor3;
	CX__VAR_ANALOG_CTRL		aiCH__EPD_Monitor4;
	CX__VAR_ANALOG_CTRL		aiCH__EPD_Monitor5;
	CX__VAR_ANALOG_CTRL		aiCH__EPD_Monitor6;
	CX__VAR_ANALOG_CTRL		aiCH__EPD_Monitor7;
	CX__VAR_ANALOG_CTRL		aiCH__EPD_Monitor8;

	CX__VAR_STRING_CTRL		soCH__EPD_WAFER_INFO;
	CX__VAR_STRING_CTRL		soCH__EPD_Recipe_Name;
	CX__VAR_STRING_CTRL		siCH__EPD_Mon_Name1;
	CX__VAR_STRING_CTRL		siCH__EPD_Mon_Name2;
	CX__VAR_STRING_CTRL		siCH__EPD_Mon_Name3;
	CX__VAR_STRING_CTRL		siCH__EPD_Mon_Name4;
	CX__VAR_STRING_CTRL		siCH__EPD_Mon_Name5;
	CX__VAR_STRING_CTRL		siCH__EPD_Mon_Name6;
	CX__VAR_STRING_CTRL		siCH__EPD_Mon_Name7;
	CX__VAR_STRING_CTRL		siCH__EPD_Mon_Name8;

	REPORT	g_stReport;
	CRITICAL_SECTION mSc;
	bool	g_bEndThread;
	bool	g_bEPDThreadPause;

	typedef union{
		unsigned char szData[4];
		float fData;
		int nData;
	}Convert;

	Convert TypeConvert;
	void Fnc__Write_Log(const char *szMsg , bool _bSendRecv , bool _bResult , int _nLength );

public:
	CObj__VERITY_STD();
	~CObj__VERITY_STD();

	//-------------------------------------------------------------------------
	int __DEFINE__CONTROL_MODE(obj,l_mode);
	int __DEFINE__VERSION_HISTORY(version);

	int __DEFINE__VARIABLE_STD(p_variable);
	int __DEFINE__VARIABLE_IO(p_io_variable);

	int __DEFINE__ALARM(p_alarm);

	//-------------------------------------------------------------------------
	int __INITIALIZE__OBJECT(p_variable,p_ext_obj_create);
	int __INITIALIZE__IO(p_io_para);

	//-------------------------------------------------------------------------
	int __CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm);
	int __CALL__MONITORING(id,p_variable,p_alarm);

	//-------------------------------------------------------------------------
	int __Read__ANALOG(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, double& read_data);
	int __Read__DIGITAL(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, CString& read_data,int& item_index);
	int __Read__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, CString& read_data);

	int __Write__ANALOG(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const double set_data);
	int __Write__DIGITAL(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data,const int item_index);
	int __Write__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data);

};
