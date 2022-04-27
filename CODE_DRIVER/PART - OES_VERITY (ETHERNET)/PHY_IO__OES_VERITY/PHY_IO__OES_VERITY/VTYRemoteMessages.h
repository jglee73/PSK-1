//*************************************************************************
//   Copyright [c] 2002  Verity Instruments, Inc.    All Rights Reserved
//********************************************************************[mps]
//
// $Project$ $Folder$
//
// $Workfile: VTYRemoteMessages.h $
//
// TITLE:        Standard Verity command messages header file
//
// HEADER CONTENTS:
//     This header file declares types, structures, command codes, etc. used for 
//     communication between Verity applications and URI.  When the host tool uses
//     this command set URI does not need to do any interpretation in order to 
//     communicate with any Verity tools.
//
//
// RESTRICTIONS AND NOTES:
//     ***IMPORTANT***
//        This header file is viewed and used by customers so great care should be used to 
//        preserve the format, consistency, backward compatibility, and OS independency
//        wherever possible.
//        Be sure no Verity Proprietary Information is stated within
//        Version History Comments Must NOT Contain Customer References
//     Verity reserves the right to extend or change this command set as needed.
//     Backward compatibility will be maintained if at all possible.
//     Not Every revision may be listed in the revision history  
//
// VERSION HISTORY:
// ----------------------------------------------
// NOTE THe following list has been generated MANUALLY, and is to be updated
// with These changes should detail relevent changes that affect our customer's use of this file
// ^Log: 
//
//    v71    5/18/2006 10:14am    SLynes          VTY_EVENT_AVAILABLE added to facilitate keeping in sync with new commands/events
//    v67    1/25/2005 5:18 pm    SLynes          -Displayed- option and VTYEventData updated to have flags separated from severity code
//    v65    10/4/2005 4:03 pm    SLynes          Added/extended commands/events/definitions for advanced status messaging
//    v63    7/16/2005 11:23 am   SLynes          New types added to the data block types and structures
//    v62    5/10/2005 3:45 pm    SLynes          Added the LAMPMISFIRE event
//    v56    1/5/2004  10:45 am   SLynes          Updated the data header to account for new status/error bits
//    v55    12/2/2003 4:49 pm    Rwhitfield      VTY_RECONNECT added
//    v47    8/15/2003 1:53 pm    SLynes          V3Dev: The flags for the extended header did not match the ones
//           coming from the device
//    v46    7/30/03   8:59 am    Rwhitfield      V3DEV: correct assignment operator
//    v45    7/30/03   8:57 am    Rwhitfield      V3DEV: add asignment operator to tVTYRawSpectrumHeaderEx for easy
//           conversion from tVTYRawSpectrumHeader
//    v44    7/29/03   9:23 pm    Rwhitfield      V3DEV: update tVTYRawSpectrumHeaderEx to include both a conversion
//           operator and constructor for tVTYRawSpectrumHeader.
//    v43    7/29/03   9:15 pm    Rwhitfield      V3DEV: Add Conversion routines to tVTYRawHeaderEx to convert to and
//           from tVTYRawHeader
//    v42    7/29/2003 3:25 pm    SLynes          V3DEV: Added the extended spectrum header struct
//    v41    6/24/2003 5:18 pm    SLynes          SCR 627: Minor adjustment for the writing of the dynamic string
//           streams  
//    v40    5/22/2003 11:23 am   SLynes          SCR 606: RTA added to tVTYProcessInfo structure
//
//    v38    5/15/2003 12:55 pm   SLynes          Added the support for dynamic strings
//    v30    10/24/2002 05:23 pm  SLynes          Added the VTY_CMD_SET_VAR and VTY_CMD_GET_VAR commands to allow tool 
//    v42    5/22/03    11:17 am   SLynes         SCR 606: RTA added to process details structure 
//    v41    5/15/03     1:23 pm   SLynes         SCR 584: Dynamic string support in standard protocol 
//    v40    4/08/03     4:49 pm   Rwhitfield     SCR 546,547,548: Fixed 
//    v37    3/05/03    12:18 pm   SLynes         add constructor for tVTYWaferDesc struct. 
//    v34    11/20/02   05:46 pm   SLynes         Syntax error corrected 
//    v33    11/20/02   05:44 pm   SLynes        VTY_CMD_RESET now has a status code that can be
//           set that will request resetting both SpectraView AND the device 
//    v30    10/24/2002 05:23 pm   SLynes         Added the VTY_CMD_SET_VAR and VTY_CMD_GET_VAR commands to allow tool 
//           controllers to pass variable values to override the current value 
//    v26    4/22/2002 01:14 pm   RDaignault      Updated Restrictions/Notes and Version history
//           format 
//    v25    4/16/2002 11:12 PM   Slynes          Added revision history
//    v20    4/12/2002 4:39 PM    Slynes          Wafer Info command now has status codes for 
//           replace/update/append. 
//           "Custom" bitmap codes were added for future expansion.
//    v18    11/14/2001 12:56p    Jmalone         Customer Specific Ethernet protocols added 
//           BUT NOT FULLY TESTED 
//    v17    11/14/2001 9:34a     Kmiller         Added DATABLOCK and SHUTDOWN
//    v16    10/01/2002 10:07a    Slynes          Fixed SCR 57 issue with saving/loading of 
//           multiple apps with DIO settings
//    v15    9/24/2001  9:36a     Slynes          Added a relative time stamp to the struct for 
//           DATABLOCK events and a data interval to the MATRIX event to make it possible for 
//           the tool to track graphically if desired with out internal timing
//    v13    8/15/2001  10:01a    Kmiller         Added the VTY_CMD_CFG_VERIFY and
//           VTY_CMD_CFG_VALIDATE messages
//    v12    8/08/2001  4:37p     Slynes          Added caching of DATABLOCK messages to try 
//           to avoid data backlogging
//    v01    10/18/2000 10:35p    Slynes          Created VTYRemoteMessages.h
// ^
extern "C"
{
	#ifndef _VTYREMOTEMESSAGES
	#define _VTYREMOTEMESSAGES

	//WARNING: These structures must be packed to one byte if they are to be used to interpret the communication
	// messages directly.  Since the bytes are sent, and must be received, by Verity in "Little Indian"
	// order some operating systems may find it easier to interpret the bytes into these structures rather
	// than using a pointer of the appropriate type.  Packing is automatically done here only for the 
	// Microsoft compiler.
	#ifdef _MSC_VER
		#pragma pack (push)
		#pragma pack (1)
	#endif

	#define BYTE unsigned char
	#define WORD unsigned short
	#define DWORD unsigned long

	#define VTY_TCPIP_PORT	0x5552	//TCP/IP connection port

	//Logical Ports
	#define VTY_LP_TOURI			1 // Logical port for the messages from the customer.  Replys have the same
	#define VTY_LP_FROMURI			2 // Logical port for the messages from URI.  Replys back to URI should have the same

	//Reply status codes
	#define VTY_OK		0	//Success! The data contains the desired information, if any.
	#define VTY_FAIL	1	//When the status is VTY_FAIL in a reply, there is a tVTYString in the data with a detailed description

	//String types
	#define VTY_ASCII	0
	#define VTY_UNICODE	1

	//NOTE: For protocols like RS232 that use ACK/NAK, negative commands/messages/events do not ACK.
	//		Only a reply should be expected.  Do not ACK/NAK to replys with negative command IDs either.

	//Connection messages
	#define VTY_RECONNECT			   -102
	#define VTY_CONNECT				   -101	//Expect only a reply or timeout if none comes.
	#define VTY_DISCONNECT				 99	//Positive so reply is received prior to closing the connection

	//Command identifiers
	#define VTY_CMD_RESET				100	// 0x64
	#define VTY_CMD_TEST				101	// 0x65
	#define VTY_CMD_PRESENT				102	// 0x66
	#define VTY_CMD_VERSION				103	// 0x67
	#define VTY_CMD_CFG_LIST			104	// 0x68
	#define VTY_CMD_GET_CFG				105	// 0x69
	#define VTY_CMD_SET_CFG				106	// 0x6A
	#define VTY_CMD_DEL_CFG				107	// 0x6B
	#define VTY_CMD_DEL_ALLCFG			108	// 0x6C
	#define VTY_CMD_SET_URI				109	// 0x6D
	#define VTY_CMD_GET_URI				110	// 0x6E
	#define VTY_CMD_TOOLISHOST			111	// 0x6F
	#define VTY_CMD_TOOLNOTHOST			112	// 0x70
	#define VTY_CMD_WAFERINFO			113	// 0x71	//New, generic, style of wafer infomation
	#define VTY_CMD_START				114	// 0x72	
	#define VTY_CMD_STOP				116	// 0x74	
	#define VTY_CMD_PAUSE				117	// 0x75	
	#define VTY_CMD_CONTINUE			118	// 0x76	
	#define VTY_CMD_COMPLETE			119	// 0x77	
	#define VTY_CMDINTERNAL1			120	// 0x78	//Place holder for internal command
	#define VTY_CMDINTERNAL2			121	// 0x79	//Place holder for internal command
	#define VTY_CMD_CFG_VERIFY			122	// 0x7A	//Verify validity of a list of configurations
	#define VTY_CMD_CFG_VALIDATE		123	// 0x7B	//Validate a single configuration and return the validation messages
	#define VTY_CMD_SHUTDOWN			124	// 0x7C	//Used by URI to shut down the PC
	#define VTY_CMD_SET_VAR				125	// 0x7D	//Set the current value for one more variables
	#define VTY_CMD_GET_VAR				126	// 0x7E	//Get the current value for one more variables
	#define VTY_CMD_OPEN_DATAFILE		127	// 0x7F	//Open a data file from wafer information passed
	#define VTY_CMD_GET_PROCESSDETAILS	128	// 0x80	//Get details about currently processing data or open data file
	#define VTY_CMD_START_REPROCESS		129	// 0x81	//Reprocess the currently open data file
	#define VTY_CMD_RESERVED			130	// 0x82	//Reserved for future expansion
	#define VTY_CMD_SETEVENTREPORTING	131	// 0x83	//Set the event reporting level
	#define VTY_CMD_ACK_USEREVENT		132	// 0x84	//Acknowledge one or more user events
	#define VTY_CMD_ACK_ERROR			133	// 0x85	//Acknowledge one or more system issues
	#define VTY_CMD_GETSTATUSERRORS		134	// 0x86	//Get a list of current system issues/errors
	#define VTY_CMD_GETSTATUSUSEREVENTS	135	// 0x87	//Get a list of current user events
	#define VTY_CMD_AVAILABLE			136	// 0x88	//Next available command.  Renumber each time one is added so tests 
													//  can be made to ASSERT or have compilation errors in places that 
													//  need to stay in sync with the commnand set

	//Event identifiers
	#define VTY_EVENT_ENDPOINT			200	//0xC8
	#define VTY_EVENT_LOCAL				201	//0xC9
	#define VTY_EVENT_REMOTE			202	//0xCA
	#define VTY_EVENT_RUNNING			203	//0xCB	//Always follows VTY_EVENT_NOTREADY mainly for support of legacy command sets, VTY_EVENT_READY is analogous to NOTRUNNING
	#define VTY_EVENT_READY				204	//0xCC
	#define VTY_EVENT_NOTREADY			205	//0xCD
	#define VTY_EVENT_MARKEVENT			206	//0xCE	//Mark events reached in the sequence will send this
	#define VTY_EVENT_USEREVENT			206	//0xCE	//Mark events are now called "User Events"
	#define VTY_EVENTINTERNAL1			207	//0xCF	//Place holder for internal event
	#define VTY_EVENT_MATRIX			208	//0xD0
	#define VTY_EVENT_DATABLOCK			209	//0xD1
	//#define VTY_EVENT_TREND			210	//0xD2
	#define VTY_EVENT_ERROR				211	//0xD3	//Any error that occurs, not in response to a command from the tool
	#define	VTY_EVENT_POWERUP			212	//0xD4 //Sent when a device becomes available when turned on or reset
	#define VTY_EVENT_RESERVED1			213	//0xD5
	#define VTY_EVENT_RESERVED2			214	//0xD6
	#define VTY_EVENT_RESERVED3			215	//0xD7
	#define VTY_EVENT_LAMPMISFIRE		216	//0xD8 //The flashlamp misfired
	#define VTY_EVENT_ERROR_ACK			217	//0xD9	//A system issue/error was acknowledged
	#define VTY_EVENT_USEREVENT_ACK		218	//0xD0	//A user event was acknowledged
	#define VTY_EVENT_AVAILABLE			219	//0xD1	//Next available event.  Renumber each time one is added so tests 
											//  can be made to ASSERT or have compilation errors in places that 
											//  need to stay in sync with the commnand set


	#define VTY_SCS_ALWAYS_SEND_DATABLOCK    1 // start command status flag. Causes (re)processing to always send a data block message when connected by remote mode.

	#define VTY_MAXTEXT		128
//Verity "fixed length" message string structure...
	typedef struct _tVTYString
	{
		char	Text[VTY_MAXTEXT];//ASCII or UNICODE string 
		BYTE	Type;//String type (0==ASCII)
		BYTE	Length;
	}tVTYString;

//Verity "dynamic length" message string structure.  For use with the dynamic string version of the protocol only.

//Capabilities structure
	// This is now sent in the reply to the VTY_CONNECT and VTY_RECONNECT.  If this is not received then advanced event levels are not available
	typedef struct _tVTY_SystemInfo
	{
		WORD		Info_Version;//This is incremented each time information is appended to this structure
		//Version 1...
		float		URI_Version;//Floating point version of URI.
		WORD		EventReportingLevels;//What is the highest reporting level available in the system that can be used with VTY_CMD_SETEVENTREPORTING
		//Version 2... 
			//Future capabilities details will be appended in the future...
	}tVTY_SystemInfo;

//Configuration descriptor...
	// An array of these is returned from GET_CONFIG_LIST
	typedef struct _tVTYConfigurationDesc
	{
		tVTYString	Name;
		tVTYString	DateTime;	//Date and time the file was last modified by a Verity configuration editor
		DWORD		Size;		//Byte size of the configuration.  (Actual storage space used may be slightly larger)
	}tVTYConfigurationDesc;

//Item Types...
	#define VTY_ITYPE_NONE			0x0000
	#define VTY_ITYPE_RAWSPECTRUM	0x0001	//Spectrum
	#define VTY_ITYPE_SPECTRALEQU	0x0002	//Spectral Equation
	#define VTY_ITYPE_REGIONEQU		0x0004	//Region Equation
	#define VTY_ITYPE_TRENDEQU		0x0008	//Trend Equation
	#define VTY_ITYPE_ADV_TREND		0x0010	//Advanced equation trend
	#define VTY_ITYPE_ADV_SPECTRA	0x0020	//Advanced equation spectrum
	#define VTY_ITYPE_TRENDVAR		0x0040	//Scalar Variable
	#define VTY_ITYPE_SPECTRALVAR	0x0080	//Spectral Variable
	#define VTY_ITYPE_VECTORVAR		0x0100	//Vector Variable
	#define VTY_ITYPE_TRENDSOURCE	0x0200	//Trend Data Source
	#define VTY_ITYPE_VECTOREQU		0x0400	//Vector Equation, Region Vector Equation, Vector Builder Equation
	#define VTY_ITYPE_ADV_VECTOR	0x0800	//Advanced equation vector
	#define VTY_ITYPE_ALL			0xFFFF	//All type bits

//Data Types...
	#define VTY_DTYPE_DEFAULT		0	//Used default data type for this type of information
	#define VTY_DTYPE_BYTE			1	//8 Bits representing a number from 0-255
	#define VTY_DTYPE_SHORT			2	//16 Bits representing a signed integer from -32768 to 32767
	#define VTY_DTYPE_WORD			3	//16 Bits representing an unsigned integer from 0 to 65536
	#define VTY_DTYPE_LONG			4	//32 Bit signed integer
	#define VTY_DTYPE_DWORD			5	//32 Bit unsigned integer
	#define VTY_DTYPE_FLOAT			6	//32 Bit Intel format floating point number
	#define VTY_DTYPE_DOUBLE		7	//64 Bit Intel format floating point number
	
//Reset sub commands...
	#define VTY_RSC_NORMAL			0	//This resets only the endpoint system
	#define VTY_RSC_RESETALL		1	//This resets the endpoint system AND the device

//Wafer Information...
	//VTY_CMD_WAFERINFO status is the # of tVTYWaferDesc structures or one of the following codes.
	//	If the status is 
	#define VTY_WISC_NEWWAFER	( 0)	//Replace Current information is cleared, replaced with the new information.  
										//	The result is the next step will be in a new directory even if path and 
										//	filename substitution are the same as previous. (VTY_CMD_WAFERCOMPLETE is performed as well)
	#define VTY_WISC_UPDATE		(-1)	//Information that already exists is updated, and any new information is 
										//	appended to the end of the existing information.  Only fields that are 
										//	to be added or updated need to be sent.  The information will be considered as 
										//part of the same wafer and will be saved with processing of the next step in the recipe. 
	#define VTY_WISC_APPEND		(-2)	//All current information is kept unchanged.  Passed information is 
										//	appended to existing wafer information without looking for duplicates.

	// An array of these is sent to Verity Endpoint Detector
	typedef struct tVTYWaferDesc
	{
		tVTYString	Label;//Label text to report the information to the user. Ex: "Lot Number:"
		tVTYString	Text;//Label text to report the information to the user. Ex: "789001"
		DWORD		Flags;//Bit flags that identify "special" informational text
	}tVTYWaferDesc;

	//Bit flags for tVTYWaferDesc.Flags
	#define VTY_WAFER_TOOLID		0x00000001
	#define VTY_WAFER_WORKFLOW		0x00000002
	#define VTY_WAFER_RECIPE		0x00000004	
	#define VTY_WAFER_WAFERID		0x00000008
	#define VTY_WAFER_LOT_NAME		0x00000010
	#define VTY_WAFER_CASSETTE		0x00000020
	#define VTY_WAFER_SLOT			0x00000040
	#define VTY_WAFER_OTHER_INFO	0x00000080
	#define VTY_WAFER_STEP_NUM		0x00000100
	#define VTY_WAFER_CUSTOM1		0x00000200
	#define VTY_WAFER_CUSTOM2		0x00000400
	#define VTY_WAFER_CUSTOM3		0x00000800
	#define VTY_WAFER_CUSTOM4		0x00001000
	#define VTY_WAFER_CUSTOM5		0x00002000
	#define VTY_WAFER_DATE			0x00004000
	#define VTY_WAFER_TIME			0x00008000

	#define VTY_WAFER_SYNCBIT		0x80000000	//Syncronize this item with the system if capable 
												//	(Change date and time of computer with this VTY_WAFER_TIME entry for example)
//Verify descriptor...
	#define VTY_VERIFY_ISSUE_NOTFOUND		0	//Configuration was not found
	#define VTY_VERIFY_ISSUE_VALIDATION		1	//Configuration failed validation

	#define VTY_VALIDATE_ISSUE_TEXT			0	//Simple text, not an error or warning
	#define VTY_VALIDATE_ISSUE_WARNING		1	//Validation warning
	#define VTY_VALIDATE_ISSUE_ERROR		2	//Validation error
	// An array of these is may be the reply to VTY_CMD_VALIDATE and VTY_CMD_VERIFY
	typedef struct
	{
		tVTYString	Text;	//Configuration name for VTY_CMD_VERIFY and validation message for VTY_CMD_VALIDATE
		WORD		Issue;	//Verify issue code for VTY_CMD_VERIFY and validate code for VTY_CMD_VALIDATE
	}tVTYValidateReply;

//Variables...
	// An array of these is sent to the Verity Endpoint Detector for VTY_CMD_SET_VAR
	// Also sent as a reply from the Verity Endpoint Detector for VTY_CMD_GET_VAR
	typedef struct
	{
		tVTYString	VariableName;//Variable name
		float		Value;//Value of the variable
	}tVTYVariable;

//Events/Errors...
	//Codes for the status field of VTY_CMD_SETEVENTREPORTING
	#define VTY_EVENTLEVEL_NORMAL		0	//Events and errors are reported when they occur only during execution of the system
	#define VTY_EVENTLEVEL_LEVEL_ADV1	1	//Events and errors are reported when they occur, are ACKed, and resolved during execution and when idle

	//Severity code in the lower byte of the "Code" field of tVTYEventData
	#define VTY_EVENTCODE_SYSTEM  (-1)	//Obsolete.  System errors/issues have a severity associated.  Endpoint will be set at VTY_EVENTCODE_NOTIFY
	#define VTY_EVENTCODE_NOTIFY	0	//Notification
	#define VTY_EVENTCODE_WARNING	1	//Warning
	#define VTY_EVENTCODE_ERROR		2	//Error
	#define VTY_EVENTCODE_FAULT		3	//Fault

	//VTY_EVENT_USEREVENT and VTY_EVENT_ERROR events have a Flags field that is a bit mask that contains some combination of the following the reveal details and nature of the event
	#define VTY_EVENTFLAGS_DISPLAYED	0x0001	//User event notifications are not always tracked by the system status window
	#define VTY_EVENTFLAGS_STATUS		0x0002	//(System Errors only) Status issues cannot be ACKed.  ACK message auto sent when the issue is auto resolved internally if (event level is 1 or higher)
	#define VTY_EVENTFLAGS_SYSFAILURE	0x0004	//(System Errors only) This flag is passed with system errors that have caused the system to stop processing
	#define VTY_EVENTFLAGS_EXPIRED		0x0100	//Added to ACK events for userevents and errors.  Represents an event that has expired based on the system rules and is no longer being tracked

	// An array of these is sent to Verity Endpoint Detector
	typedef struct _tVTYEventData
	{
		tVTYString	Text;//Event text
		WORD		Code;//Notification/warning/error for user events
		float		Time;//Relative seconds since start
		WORD		Flags;//Details about the event (VTY_EVENTFLAGS_... defined above)
		tVTYString	DateTime;//Date/Time stamp
	}tVTYEventData;

	//VTY_CMD_ACK... commands may set the status code of the message to a bit mask to specify what severity levels are to be ACKed
	#define VTY_ACKCMDBIT_STRINGS 		0x0000 // Specific user event text strings are being sent.  (Can only be combined with VTY_ACKCMDBIT_SENDACKS)
	#define VTY_ACKCMDBIT_NOTIFY 		0x0001 // All notifications to be cleared
	#define VTY_ACKCMDBIT_WARNING 		0x0002 // All warnings to be cleared
	#define VTY_ACKCMDBIT_ERROR 		0x0004 // All errors to be cleared
	#define VTY_ACKCMDBIT_FAULT 		0x0008 // All faults to be cleared
	#define VTY_ACKCMDBIT_ALLLEVELS 	0x00FF // All events/errors to be cleared
	#define VTY_ACKCMDBIT_SENDACKS		0x0100 // Send ACK events for every item cleared if this is set

	//VTY_CMD_GETSTATUS... commands may set the status code of the message to a bit mask to specify what severity levels are to be returned
	#define VTY_GETSTATUSBIT_NOTIFY 	0x0001 // Include events/sys errors with VTY_EVENTCODE_NOTIFY
	#define VTY_GETSTATUSBIT_WARNING 	0x0002 // Include events/sys errors with VTY_EVENTCODE_WARNING
	#define VTY_GETSTATUSBIT_ERROR 		0x0004 // Include events/sys errors with VTY_EVENTCODE_ERROR
	#define VTY_GETSTATUSBIT_FAULT 		0x0008 // Include events/sys errors with VTY_EVENTCODE_FAULT
	#define VTY_GETSTATUSBIT_ALLLEVELS	0x00FF // Include all events/sys regardless of severity

	//Data Items Descriptor...
	typedef struct _tVTYDataItem
	{
		WORD	DataItemID;	//Id that corresponds to the ID given in VTY_EVENT_MATRIX
		WORD	ItemType;	//Type of item described here
		DWORD	Offset;		//Byte offset to the data for descriptor in the data block
		BYTE	DataType;	//Type of basic data type used for each piece of the data
		WORD	Number;		//Number of data items found at the offset
		float	FirstItemTime;//Relative time of the first data point in the set of data
		union
		{
			//VTY_ITYPE_RAWSPECTRUM	
			//VTY_ITYPE_SPECTRALEQU	
			//VTY_ITYPE_ADV_SPECTRA	
			//VTY_ITYPE_SPECTRALVAR//Spectral Variable
			struct
			{
				WORD	HeaderSize;		//Byte size of the header preceding every spectrum
				WORD	SpectrumSize;	//Byte size of each spectrum not including the header
				DWORD	TotalSize;		//Bytes that the "Number" of spectra use in the data block
				float	NMBegin;		//Beginning wavelength of the spectrum
				float	NMEnd;			//Ending wavelength of the spectrum
				WORD	NMSteps;		//Number of data points per wavelength(2 = ?NM resolution, 4=four values per wavelength)
			}Spectrum;
			//VTY_ITYPE_REGIONEQU		
			//VTY_ITYPE_TRENDEQU		
			//VTY_ITYPE_TRENDSOURCE//Trend Data Source
			//VTY_ITYPE_ADV_TREND		
			//VTY_ITYPE_TRENDVAR
			struct
			{
				DWORD	TotalSize;		//Bytes that the "Number" of datapoints use in the data block
			}Trend;
			//VTY_ITYPE_VECTORVAR//Vector Variable
			//VTY_ITYPE_VECTOREQU//Vector Equation
			//VTY_ITYPE_ADV_VECTOR//Advanced equ vector
			struct
			{
				WORD	Size;			//Number of data elements in the vector
				WORD	ByteSize;		//Byte size of the vector
				DWORD	TotalSize;	//Bytes that the "Number" of vectors use in the data block
			}Vector;
		}Details;
	}tVTYDataItem;

	//This header preceeds the actual spectral data for every raw spectrum
	typedef struct _tVTYRawSpectrumHdr
	{
		DWORD	TimeStamp;	//Milliseconds from the beginning of execution
		DWORD	Index;		//Index of the spectrum
		DWORD	Flags;		//Error and status flags
		WORD	FiberID;	//Optical fiber ID number where the data originated
		WORD	ArraySize;	//Currently holds the array size of the spectrum but is reserved and subject to change
	}tVTYRawSpectrumHdr;

	//Types
	typedef enum ExtendedFlagBits
	{
		VRTYSPECTRADATA_EX_ERROR_MASK = 0xFFFF0000 ,
		VRTYSPECTRADATA_EX_ERROR_FIELD = 0xFF000000 ,
		VRTYSPECTRADATA_EX_FLASHLAMP = 0x00000001 ,
		VRTYSPECTRADATA_EX_BIN_TOSEND = 0x00000006 ,
		VRTYSPECTRADATA_EX_BIN_SEND_BOTTOM = 0x00000002 ,
		VRTYSPECTRADATA_EX_BIN_SEND_TOP = 0x00000004 ,
		VRTYSPECTRADATA_EX_SHUTTER = 0x00000008 ,
		VRTYSPECTRADATA_EX_EMBEDDED_INTERPOLATION = 0x00000010 ,
		VRTYSPECTRADATA_EX_SPECTRA_DATUM_SIZE = 0x00000060 ,
		VRTYSPECTRADATA_EX_SPECTRA_DATUM_SIZE32 = 0x00000020 ,
		VRTYSPECTRADATA_EX_SPECTRA_DATUM_SIZE64 = 0x00000040 ,
		VRTYSPECTRADATA_EX_SD1024_FANFAILURE = 0x00010000 ,
		VRTYSPECTRADATA_EX_SD1024_OVERTEMP = 0x00020000 ,
		VRTYSPECTRADATA_EX_FL200X_MISFIRE = 0x00040000 ,
		VRTYSPECTRADATA_EX_FL2004_FANFAILURE = 0x00080000 ,
	};

	//Extended header information
	typedef struct _tVTYRawSpectrumHdrEx
	{
		//Members
		unsigned __int64	timeStamp;		// Time of read of the CCD
		DWORD				index;			// Channel Number
		DWORD				flags;			// Multiplexed bit field;
		DWORD				channelNumber;	// FiberId
		DWORD				integrationTime;// total cycle time
		DWORD				startRow;		// Number of pixels of this channel (Vertical)
		DWORD				endRow;			// Number of pixels of this channel (Vertical)
		DWORD				backgroundSubtractionVal; 
		DWORD				exposureTime;
		DWORD				flashlampIntensity;
		DWORD				numOfSamples;	// Number of spectra in data

	}tVTYRawSpectrumHdrEx;

	//This is the first information received in the notification message VTY_EVENT_MATRIX
	typedef struct
	{
		tVTYString	Name;//Name of the data from the configuration
		WORD		ID;//ID unique only to the current execution of the configuration
		WORD		Type;//Type of data that will be sent
		WORD		DataInterval;//The interval between data items that will be received in the DATABLOCK event expressed in milliseconds (Convert to seconds: float Seconds=(DataInterval/1000.0))
	}tVTYEventInfo;

	//This is the structure that is returned from a VTY_CMD_GET_PROCESSDETAILS
	typedef struct
	{
		tVTYString	DataFileName;//Name of the data file
		DWORD		DataInterval;//The interval in milliseonds that raw data is being processed
		DWORD		NumRawData;  //Number of sets of raw spectra that have been processed
		BYTE		Processing;  //1 if processing is still being performed and 0 if processing is complete
		float		RTA;		 //Response time adjustment.  Difference in time from receipt of start 
								 //request and the acknowledgement from the device that data is being collected.  
								 //This adjustment is applied in the system to graph data in "real-time"
	}tVTYProcessInfo;

	#ifdef _MSC_VER
		#pragma pack (pop)
	#endif

	#endif ///_VTYREMOTEMESSAGES
}
