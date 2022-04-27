#include "stdafx.h"

#include "CObj__VERITY_STD__ALID.h"
#include "CObj__VERITY_STD.h"


// ...
void CObj__VERITY_STD
::Mon__IO_MONITORING(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	bool			bResult = false;
	int				nResult = 0;
	int				nDataIndex = 0;
	int				nDataLength = 0;
	int				nDataZeroIndex = 0;
	int				nCnt = 0;
	int				nIndex = 0;
	int				nTempIndex = 0;
	unsigned char	szSendCommand[DEFAULT_STR_LENGTH] = { 0 , };
	unsigned char	szRecvCommand[MAX_STR_LENGTH] = { 0 , };
	unsigned char	szDataConvert[MAX_STR_LENGTH] = { 0 , };
	double			dPoll_sec = 0.05;

	
	if(iActive__SIM_MODE > 0)
	{

	}
	else
	{
		::EnterCriticalSection( &mSc );

		szSendCommand[nCnt++] = VTY_LP_TOURI % 256;
		szSendCommand[nCnt++] = VTY_LP_TOURI / 256;
		szSendCommand[nCnt++] = VTY_CONNECT % 256;
		szSendCommand[nCnt++] = 255;
		szSendCommand[nCnt++] = 0;
		szSendCommand[nCnt++] = 0;
		szSendCommand[nCnt++] = DATA_LENGTH % 256;
		szSendCommand[nCnt++] = DATA_LENGTH / 256;
		szSendCommand[nCnt++] = 0;
		szSendCommand[nCnt++] = 0;
		
		//sprintf( szSendCommand , "%c%c%c%c%c%c%c%c%c%cSpectraView1" , VTY_LP_TOURI % 256 , VTY_LP_TOURI / 256 , VTY_CONNECT % 256 , 255 , 0 , 0 , DATA_LENGTH % 256 , DATA_LENGTH / 256 , 0 , 0 );
		szSendCommand[138]	  = VTY_ASCII;
		szSendCommand[139]	  = 12;
		
		//sprintf( szSendCommand , "%c%c%c%c%c%c%c%c%c%cSpectraView1" , VTY_LP_TOURI % 256 , VTY_LP_TOURI / 256 , VTY_CONNECT % 256 , 255 , 0 , 0 , DATA_LENGTH % 256 , DATA_LENGTH / 256 , 0 , 0 );
		//sprintf( szSendCommand + 138 , "%c%c" , VTY_ASCII , 12 );
		
		while( !bResult )
		{
			bResult = SEND_COMMAND( szSendCommand , 10 + DATA_LENGTH );
			if( bResult )
			{
				bResult = RECV_COMMAND( szRecvCommand , szSendCommand , 10 , &nDataLength );
			}
			
			if( g_bEndThread )
			{
				break;
			}

			Sleep( 100 );
		}

		::LeaveCriticalSection( &mSc );
	}


	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(dPoll_sec);


		if(iActive__SIM_MODE > 0)
		{
			sCH__COMM_STATE->Set__DATA("ONLINE");
			continue;
		}

		if( g_stReport.nErrStatus == CommError )
		{
			sCH__COMM_STATE->Set__DATA("OFFLINE");

			//
			int alarm_id = ALID__EPD_COMMUNICATION_ALARM;
			CString r_act;

			p_alarm->Check__ALARM(alarm_id,r_act);
			p_alarm->Post__ALARM(alarm_id);
			
			continue;
		}
		else
		{
			sCH__COMM_STATE->Set__DATA("ONLINE");
		}

		if( ( g_stReport.nRunning < 2 ) )
		{
			g_bEPDThreadPause = TRUE;
			continue;
		}

		g_bEPDThreadPause = FALSE;
		::EnterCriticalSection( &mSc );
		bResult = RECV_COMMAND( szRecvCommand , NULL , 0 , &nDataLength );
		::LeaveCriticalSection( &mSc );
		
		if( szRecvCommand[2] == VTY_EVENT_NOTREADY )
		{
			g_stReport.bRecvStart = TRUE;
		}
		else if( szRecvCommand[2] == VTY_EVENT_RUNNING )
		{
			g_stReport.nRunning = 2;
		}
		else if( szRecvCommand[2] == VTY_EVENT_DATABLOCK )
		{
			g_stReport.bRecvStart = TRUE;
			memcpy( szDataConvert , szRecvCommand + 10 , nDataLength );
			for( nIndex = 0; nIndex < MAX_DATA_CHANNEL; nIndex++ )
			{
				nTempIndex = 33 * nIndex;
				memcpy( &( TypeConvert.szData ) , &( szDataConvert[nTempIndex + 4] ) , 4 );
				nDataIndex = TypeConvert.nData;
				
				if( nIndex > 0 )
				{
					if( nTempIndex >= nDataZeroIndex )
						break;
				}
				else
				{
					nDataZeroIndex = nDataIndex;
				}

				memcpy( TypeConvert.szData , &( szDataConvert[nDataIndex] ) , 4 );
				g_stReport.dMonitor[nIndex] = TypeConvert.fData;
			}
		}
		else if( szRecvCommand[2] == VTY_EVENT_MATRIX )
		{
			memcpy( szDataConvert , szRecvCommand + 10 , nDataLength );
			for( nIndex = 0; nIndex < MAX_DATA_CHANNEL; nIndex++ )
			{
				nTempIndex = nIndex * 136;
				if( nTempIndex >= nDataLength )
					break;
				//sprintf( g_stReport.szChannelName[nIndex] , "%s" , szDataConvert + ( nIndex * 136 ) );
				memcpy( g_stReport.szChannelName[nIndex] , szDataConvert + ( nIndex * 136 ) , strlen((char *)(szDataConvert + ( nIndex * 136 ) ) ) );
			}
		}
		else if( szRecvCommand[2] == VTY_EVENT_ENDPOINT )
		{
			g_stReport.nEndPoint = 1;
			g_stReport.nRunning = 1;
			g_stReport.bRecvStart = FALSE;
		}
	}
}


bool CObj__VERITY_STD
::SEND_COMMAND( const unsigned char *_szSend , int _nLength )
{
	int		nResult = 0;
	bool	bReturn = false;
	CString err_msg;

	if( mX__Net_Client->IS_CONNECT_EX() < 0 )
	{
		g_stReport.nErrStatus = CommError;
		// Log
		return false;
	}

	g_stReport.nErrStatus = Normal;

	nResult = mX__Net_Client->CHAR__SEND((char *)_szSend , strlen((char *)_szSend) , 1 , &err_msg );

	if( nResult > 0 )
		bReturn = true;
	
	Fnc__Write_Log((char *)_szSend , true , bReturn , nResult );
	
	return bReturn;
}


bool CObj__VERITY_STD
::RECV_COMMAND( unsigned char *_pcData , const unsigned char *_pcSendData , int _nLength , int *_nDataLen )
{
	int		nCount = 0;
	int		nResult = 0;
	int		nLength = 0;
	int		nReadCount = 0;
	int		nDataLength = 0;
	bool	bResult = false;
	CString err_msg;
	
	if( _nLength > 0 )
	{
		for( nCount = 0; nCount < 5; nCount++ )
		{
			Sleep( 15 );
			nResult = mX__Net_Client->CHAR__RECV( (char *)(_pcData + nLength) , _nLength , 1 , &err_msg );
			//bReslut = Net_Read_Count_Char( _pcData + nLength , _nLength , &nReadCount , g_nTimeOut );
			nLength += nReadCount;
			if( nResult )
			{
				if( ( _pcData[2] == VTY_EVENT_READY ) && ( _pcSendData[2] == VTY_CMD_WAFERINFO ) )
				{
					//LogMsgWrite( _pcData , nLength , FALSE );
					nLength = 0;
					continue;
				}
				break;
			}
		}
	}
	else
	{
		for( nCount = 0; nCount < 5; nCount++ )
		{
			if( nDataLength == 0 )
			{
				nResult = mX__Net_Client->CHAR__RECV( (char *)(_pcData + nLength) , 10 , 1 , &err_msg );
				nLength += nReadCount;
				if( nReadCount == 10 )
				{
					memcpy( TypeConvert.szData , &( _pcData[6] ) , 4 );
					nDataLength = TypeConvert.nData;
					if( nDataLength == 0 )
						break;
				}
			}
			else
			{
				nResult = mX__Net_Client->CHAR__RECV( (char *)(_pcData + nLength) , _nLength , 1 , &err_msg );
				nLength += nReadCount;
				if( nResult )
				{
					*_nDataLen = nDataLength;
					nDataLength += 10;
				}
				break;
			}
		}
		if( nCount == 5 )	bResult = false;
	}

	// log

	if( !nResult )
	{
		g_stReport.nErrStatus = CommError;
	}
	else
	{
		g_stReport.nErrStatus = Normal;
		bResult = true;
		if( ( _pcSendData != NULL ) && ( strncmp((char *) _pcData ,(char *) _pcSendData , 4 ) != 0 ) )
		{
			bResult = false;
		}

		if( ( _nLength > 0 ) && ( _pcData[4] != VTY_OK ) )
		{
			bResult = false;
			switch( _pcData[2] )
			{
				case VTY_CMD_START:
					g_stReport.nNakCommand = 1;
					break;
				case VTY_CMD_STOP:
					g_stReport.nNakCommand = 2;
					break;
				case VTY_CMD_RESET:
					g_stReport.nNakCommand = 3;
					break;
				case VTY_CMD_WAFERINFO:
					g_stReport.nNakCommand = 4;
					break;
			}

		}
	}
	
	Fnc__Write_Log((char *)_pcData , false , bResult , nResult );
	return bResult;
}
