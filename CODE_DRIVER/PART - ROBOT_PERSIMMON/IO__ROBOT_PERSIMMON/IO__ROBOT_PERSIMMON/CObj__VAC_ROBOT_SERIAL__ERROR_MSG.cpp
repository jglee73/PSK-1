#include "StdAfx.h"
#include "CObj__VAC_ROBOT_SERIAL.h"
#include "CObj__VAC_ROBOT_SERIAL__DEF.h"
#include "CObj__VAC_ROBOT_SERIAL__ALID.h"

#include "math.h"
#include "CCommon_DEF.h"


// ...
CString CObj__VAC_ROBOT_SERIAL::Get__ERROR_MSG(const int err_id)
{
	if(err_id == 0)			return "OK";

	if(err_id == 210)		return "NOT_AT_STATION";
	if(err_id == 220)		return "NOT_RETRACTED";
	if(err_id == 221)		return "NO_ACTIVE_ARM";
	if(err_id == 233)		return "HANDSHAKE";
	if(err_id == 305)		return "INVALID_COMMAND";
	if(err_id == 309)		return "NOT_SUPPORTED";
	if(err_id == 352)		return "NO_MEMORY";
	if(err_id == 443)		return "INVALID_STATION";
	if(err_id == 450)		return "INVALID_STATION_POSITION";
	if(err_id == 451)		return "APS_DEVIATION_LIMIT";
	if(err_id == 509)		return "Z_LESS";
	if(err_id == 510)		return "W_LESS";
	if(err_id == 553)		return "S_LESS";
	if(err_id == 527)		return "MCC_COM";
	if(err_id == 528)		return "MCC_QUEUE";
	if(err_id == 558)		return "UNKNOWN_ERROR";
	if(err_id == 602)		return "BUSY";
	if(err_id == 603)		return "HALTED";
	if(err_id == 607)		return "NO_MCC";
	if(err_id == 608)		return "HALTING";
	if(err_id == 658)		return "NOT_ALLOWED";
	if(err_id == 705)		return "PAYLOAD_MISSING";
	if(err_id == 706)		return "PAYLOAD_PRESENT";
	if(err_id == 770)		return "APS_INVALID_SENSOR";
	if(err_id == 771)		return "APS_INVALID_DATA";
	if(err_id == 772)		return "APS_BROKEN_WAFER";
	if(err_id == 773)		return "APS_LARGE_BURST";
	if(err_id == 774)		return "APS_INVALID_BURSTS";
	if(err_id == 775)		return "APS_DISABLED";
	if(err_id == 776)		return "APS_MISSING_DATA";
	if(err_id == 777)		return "APS_CALCULATE";
	if(err_id == 778)		return "APS_NO_SENSOR";
	if(err_id == 821)		return "OBJECT_NOT_FOUND";
	if(err_id == 822)		return "INVALID_OBJECT";
	if(err_id == 823)		return "BAD_TYPE";
	if(err_id == 830)		return "NOT_CONFIGURED";
	if(err_id == 832)		return "READ_ONLY";
	if(err_id == 838)		return "INVALID_NAME";
	if(err_id == 840)		return "INVALID_TYPE";
	if(err_id == 844)		return "INVALID_PARAM";
	if(err_id == 951)		return "EVENT_NOT_FOUND";
	if(err_id == 952)		return "UNKNOWN_EVENT";
	if(err_id == 1101)		return "WORK_SPACE";
	if(err_id == 1805)		return "CDM_CONTROL";
	if(err_id == 2003)		return "TIMEOUT";
	if(err_id == 3000)		return "TRACE_ACTIVE";
	if(err_id == 3001)		return "ALREADY_CONFIGURED";
	if(err_id == 4007)		return "LOG_ERROR";
	if(err_id == 6010)		return "OVERTEMP";
	if(err_id == 6011)		return "PRESSURE";
	if(err_id == 10007)		return "SETTLE_TIMEOUT";
	if(err_id == 10009)		return "HARDTRACK";
	if(err_id == 10012)		return "MOTOR_CONFIG";
	if(err_id == 10013)		return "NOT_REFERENCED";
	if(err_id == 10014)		return "REFERENCING";
	if(err_id == 10016)		return "TRAJECTORY";
	if(err_id == 10019)		return "ENCODER";
	if(err_id == 10021)		return "POWER";
	if(err_id == 10022)		return "OVERTRAVEL_LIMIT";
	if(err_id == 10024)		return "MCC_TIMEOUT";
	if(err_id == 10029)		return "EMERGENCY_STOP";
	if(err_id == 10030)		return "OVERCURRENT";
	if(err_id == 10061)		return "TRJ_SINGULARITY";
	if(err_id == 10067)		return "BAD_SYNC_STATE";

	// ...
	CString err_msg;

	err_msg.Format("Unknown (%1d)", err_id);
	return err_msg;
}
