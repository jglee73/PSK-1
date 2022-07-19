#pragma once

#include "CCommon_SYSTEM.h"


// DRV.SET ...
#define _DRV_SET__INIT				"@INIT~"
#define _DRV_SET__LOAD				"@LOADL"
#define _DRV_SET__UNLOAD			"@UNLDL"
#define _DRV_SET__OPEN				"@OPEN~"
#define _DRV_SET__CLOSE				"@CLOSE"
#define _DRV_SET__CLAMP				"@CLAMP"
#define _DRV_SET__UCLAMP			"@UCLAM"
#define _DRV_SET__MODE				"@MODE~"
#define _DRV_SET__SIGNAL_LAMP       "@SIGLM"
#define _DRV_SET__RESET				"@RESET"
#define _DRV_SET__N2_RUN            "@N2RUN"
#define _DRV_SET__AVG_TIMEOUT       "@AVGTM"
#define _DRV_SET__RFID_WRITE        "@RFIDW"

// RSP.SET ...
#define _RSP_SET__INIT				"$INIT~"
#define _RSP_SET__LOAD				"$LOADL"
#define _RSP_SET__UNLOAD			"$UNLDL"
#define _RSP_SET__OPEN				"$OPEN~"
#define _RSP_SET__CLOSE				"$CLOSE"
#define _RSP_SET__CLAMP				"$CLAMP"
#define _RSP_SET__UCLAMP			"$UCLAM"
#define _RSP_SET__MODE				"$MODE~"
#define _RSP_SET__SIGNAL_LAMP       "$SIGLM"
#define _RSP_SET__RESET				"$RESET"
#define _RSP_SET__N2_RUN            "$N2RUN"
#define _RSP_SET__AVG_TIMEOUT       "$AVGTM"
#define _RSP_SET__RFID_WRITE        "$RFIDW"


// DRV.GET ...
#define _DRV_GET__STATE				"@STAT~"
#define _DRV_GET__LP_MAP            "@MAPP~"
#define _DRV_GET__ALM_TXT           "@ALTXT"
#define _DRV_GET__ALM_MSG			"@ALMSG"
#define _DRV_GET__N2_STS            "@N2STS"
#define _DRV_GET__RFID_READ         "@RFIDR"
#define _DRV_GET__TIME_READ         "@TIMRD"

// RSP.GET ...
#define _RSP_GET__STATE				"$STAT~"
#define _RSP_GET__LP_MAP            "$MAPP~"
#define _RSP_GET__ALM_TXT           "$ALTXT"
#define _RSP_GET__ALM_MSG			"$ALMSG"
#define _RSP_GET__N2_STS            "$N2STS"
#define _RSP_GET__RFID_READ         "$RFIDR"
#define _RSP_GET__TIME_READ         "$TIMRD"


// ...
#define _CMD__INIT					"INIT"
#define _CMD__LOAD					"LOAD"
#define _CMD__UNLOAD				"UNLOAD"
#define _CMD__OPEN					"OPEN"
#define _CMD__CLOSE					"CLOSE"
#define _CMD__CLAMP                 "CLAMP"
#define _CMD__UNCLAMP               "UNCLAMP"


// ...
#define STR__Change					"Change"
#define STR__UnChange				"UnChange"

