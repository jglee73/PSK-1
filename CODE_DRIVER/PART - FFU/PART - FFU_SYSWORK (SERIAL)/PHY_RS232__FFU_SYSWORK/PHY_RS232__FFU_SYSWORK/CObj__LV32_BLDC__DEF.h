#pragma once


// ...
#define  CFG__FAN_SIZE									4
#define  CFG__MAX_DATA									100


// ...
#define  _ALARM_STS__LOCAL_MODE__BIT_0					0x01
#define  _ALARM_STS__POWER_OFF__BIT_1					0x02
#define  _ALARM_STS__OVER_CURRENT__BIT_5				0x20
#define  _ALARM_STS__MOTOR_ERROR__BIT_6					0x40
#define  _ALARM_STS__CONNECTION_ERROR__BIT_7			0x80


// ...
#define  STR__ONLINE									"ONLINE"
#define  STR__OFFLINE									"OFFLINE"

#define  STR__LOCAL										"LOCAL"
#define  STR__REMOTE									"REMOTE"

#define  STR__YES										"YES"
#define  STR__NO										"NO"

#define  STR__OK										"OK"
#define  STR__ERROR										"ERROR"

#define  STR__ON										"ON"
#define  STR__OFF										"OFF"

#define  STR__GET										"GET"
#define  STR__SET										"SET"

#define  STR__RPM										"RPM"
#define  STR__PRESSURE									"PRESSURE"


// ...
#define  OFFLINE										-1
#define  ONLINE											1

#define  STX											0x02
#define  ETX											0x03


// ...
#define _CMMD_MODE__BLOCK_GET							0x8A
#define _CMMD_MODE__BLOCK_SET							0x89

#define _CMMD_MODE__UNIT_GET							0xA2
#define _CMMD_MODE__UNIT_SET							0xA1

