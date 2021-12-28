#pragma once


#define  SP					0x20
#define  CR					0x0D
#define  LF					0x0A
#define  SOH				0x01
#define  STX				0x02
#define  ETX				0x03
#define  ACK				0x06
#define  NAK				0x15
#define  EOT				0x04
#define  ENQ				0x05
#define	 SAC				0x23
#define	 ECH				0x3E


#define MAX_MON_PARAM		10
#define MAX_DATA_LENGTH		64

enum SEND_PACKET_ORDER
{
	HEADER = 0, 
	CMD    = 1,
	OPTION = 2,
	DATA   = 3,
};

