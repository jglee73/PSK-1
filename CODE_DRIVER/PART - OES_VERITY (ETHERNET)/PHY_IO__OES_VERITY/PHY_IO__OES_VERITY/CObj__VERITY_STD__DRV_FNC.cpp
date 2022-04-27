#include "stdafx.h"
#include "CObj__VERITY_STD.h"


int	 g_nData[6]	  = { VTY_WAFER_LOT_NAME , VTY_WAFER_SLOT , VTY_WAFER_CASSETTE , VTY_WAFER_WAFERID , VTY_WAFER_RECIPE , VTY_WAFER_STEP_NUM };

void EPDRecipeWrite( char* szLogMsg , ... )
{
	FILE*		log_file;
	va_list		ap;
	char		cBuffer[MAX_STR_LENGTH] = { 0 , };
	char	    cFileName[64] = { 0 , };
	char		cFilePath[256] = { 0 , };

	ZeroMemory( cBuffer , MAX_STR_LENGTH );
	va_start( ap , szLogMsg );
	vsprintf( cBuffer , szLogMsg , ap );
	va_end( ap );

	sprintf( cFilePath , "%s%s" , EPD_RECIPE_DIRECTORY , cBuffer );

	log_file = fopen( cFilePath , "w" );

	if( log_file )
	{
		fprintf( log_file , "%s\n" , cBuffer );
		fclose( log_file );
	}
}

//-------------------------------------------------------------------------------------
void DATA_SEPERATE( unsigned char *SourceString , char delimiterChar , unsigned char *ResultString1 , unsigned char *ResultString2 , int ReadMaxCount ) {
	int Mode = 0 , count = 0;

	while( *SourceString ) {
		if      ( Mode == 0 ) {
			if ( *SourceString == delimiterChar ) {
				*ResultString1 = 0;
				Mode  = 1;
				count = 0;
			}
			else {
				if ( count < ReadMaxCount ) {
					*ResultString1 = *SourceString;
					*ResultString1++;
					count++;
				}
			}
		}
		else if ( Mode == 1 ) {
			if ( count < ReadMaxCount ) {
				*ResultString2 = *SourceString;
				*ResultString2++;
				count++;
			}
		}
		*SourceString++;
	}
	if      ( Mode == 0 ) {
		*ResultString1 = 0;
		*ResultString2 = 0;
	}
	else if ( Mode == 1 ) {
		*ResultString2 = 0;
	}
}

// ...
int CObj__VERITY_STD
::__Read__ANALOG(const CString& var_name, 
				 const CDS_IO__CHANNEL_INFO& io_info, 
				 double& read_data)
{
	if( aiCH__EPD_Monitor1->Check__VARIABLE_NAME(var_name) > 0 )
	{
		read_data = g_stReport.dMonitor[0];
		return 1;
	}
	else if( aiCH__EPD_Monitor2->Check__VARIABLE_NAME(var_name) > 0 )
	{
		read_data = g_stReport.dMonitor[1];
		return 1;
	}
	else if( aiCH__EPD_Monitor3->Check__VARIABLE_NAME(var_name) > 0 )
	{
		read_data = g_stReport.dMonitor[2];
		return 1;
	}
	else if( aiCH__EPD_Monitor4->Check__VARIABLE_NAME(var_name) > 0 )
	{
		read_data = g_stReport.dMonitor[3];
		return 1;
	}
	else if( aiCH__EPD_Monitor5->Check__VARIABLE_NAME(var_name) > 0 )
	{
		read_data = g_stReport.dMonitor[4];
		return 1;
	}
	else if( aiCH__EPD_Monitor6->Check__VARIABLE_NAME(var_name) > 0 )
	{
		read_data = g_stReport.dMonitor[5];
		return 1;
	}
	else if( aiCH__EPD_Monitor7->Check__VARIABLE_NAME(var_name) > 0 )
	{
		read_data = g_stReport.dMonitor[6];
		return 1;
	}
	else if( aiCH__EPD_Monitor8->Check__VARIABLE_NAME(var_name) > 0 )
	{
		read_data = g_stReport.dMonitor[7];
		return 1;
	}
	return -1;
}

int CObj__VERITY_STD
::__Read__STRING(const CString& var_name, 
				 const CDS_IO__CHANNEL_INFO& io_info, 
				 CString& read_data)
{
	if( siCH__EPD_Mon_Name1->Check__VARIABLE_NAME(var_name) > 0 )
	{
		read_data = g_stReport.szChannelName[0];
		return 1;
	}
	else if( siCH__EPD_Mon_Name2->Check__VARIABLE_NAME(var_name) > 0 )
	{
		read_data = g_stReport.szChannelName[1];
		return 1;
	}
	else if( siCH__EPD_Mon_Name3->Check__VARIABLE_NAME(var_name) > 0 )
	{
		read_data = g_stReport.szChannelName[2];
		return 1;
	}
	else if( siCH__EPD_Mon_Name4->Check__VARIABLE_NAME(var_name) > 0 )
	{
		read_data = g_stReport.szChannelName[3];
		return 1;
	}
	else if( siCH__EPD_Mon_Name5->Check__VARIABLE_NAME(var_name) > 0 )
	{
		read_data = g_stReport.szChannelName[4];
		return 1;
	}
	else if( siCH__EPD_Mon_Name6->Check__VARIABLE_NAME(var_name) > 0 )
	{
		read_data = g_stReport.szChannelName[5];
		return 1;
	}
	else if( siCH__EPD_Mon_Name7->Check__VARIABLE_NAME(var_name) > 0 )
	{
		read_data = g_stReport.szChannelName[6];
		return 1;
	}
	else if( siCH__EPD_Mon_Name8->Check__VARIABLE_NAME(var_name) > 0 )
	{
		read_data = g_stReport.szChannelName[7];
		return 1;
	}
	return -1;
}

int CObj__VERITY_STD
::__Read__DIGITAL(const CString& var_name,
				  const CDS_IO__CHANNEL_INFO& io_info, 
				  CString& read_data,
				  int& item_index)
{
	int nIndex = 0;
	int nTempIndex = 0;
	int nData = 0;
	int nLength = 0;
	int nCnt = 0;
	unsigned char szSendCommand[DEFAULT_STR_LENGTH] = { 0 , };
	unsigned char szRecvCommand[HUGE_STR_LENGTH] = { 0 , };
	char szEPDRecipeName[DEFAULT_STR_LENGTH] = { 0 , };
	bool bResult = false;
	
	if(diCH__EPD_EndPoint->Check__VARIABLE_NAME(var_name) > 0 )
		return g_stReport.nEndPoint;
	else if(diCH__EPD_Status->Check__VARIABLE_NAME(var_name) > 0 )
		return g_stReport.nRunning;
	else if(diCH__EPD_SensorErr->Check__VARIABLE_NAME(var_name) > 0 )
		return g_stReport.nErrStatus;
	else if(diCH__EPD_GetRecipe->Check__VARIABLE_NAME(var_name) > 0 )
	{
		szSendCommand[nCnt++] = VTY_LP_TOURI % 256;
		szSendCommand[nCnt++] = VTY_LP_TOURI / 256;
		szSendCommand[nCnt++] = VTY_CMD_CFG_LIST % 256;
		szSendCommand[nCnt++] = VTY_CMD_CFG_LIST / 256;
		szSendCommand[nCnt++] = 0;
		szSendCommand[nCnt++] = 0;
		szSendCommand[nCnt++] = 0;
		szSendCommand[nCnt++] = 0;
		szSendCommand[nCnt++] = 0;
		szSendCommand[nCnt++] = 0;
		//sprintf( szSendCommand , "%c%c%c%c%c%c%c%c%c%c" , VTY_LP_TOURI % 256 , VTY_LP_TOURI / 256 , VTY_CMD_CFG_LIST % 256 , VTY_CMD_CFG_LIST / 256 , 0 , 0 , 0 , 0 , 0 , 0 );
		if( ::TryEnterCriticalSection( &mSc ) == TRUE )
		{
			if( SEND_COMMAND( szSendCommand , 10 ) )
			{
				bResult = RECV_COMMAND( szRecvCommand , NULL , 0 , &nLength );
				if( bResult )
				{
					nTempIndex = 10;
					for( nIndex = 0; nIndex < 100; nIndex++ )
					{
						memset( szEPDRecipeName , 0x00 , DEFAULT_STR_LENGTH );
						sprintf( szEPDRecipeName , "%s" , szRecvCommand + nTempIndex );
						if( strlen( (char *)szEPDRecipeName ) == 0 )
							return -1;

						nTempIndex += 264;
						EPDRecipeWrite( "%s" , szEPDRecipeName );
					}
				}
			}
			::LeaveCriticalSection( &mSc );
		}
	}
	else if(diCH__EPD_Nak_Command->Check__VARIABLE_NAME(var_name) > 0 )
		return g_stReport.nNakCommand;
	else if(diCH__EPD_CommTest->Check__VARIABLE_NAME(var_name) > 0 )
	{
		szSendCommand[nCnt++] = VTY_LP_TOURI % 256;
		szSendCommand[nCnt++] = VTY_LP_TOURI / 256;
		szSendCommand[nCnt++] = VTY_CMD_TEST % 256;
		szSendCommand[nCnt++] = VTY_CMD_TEST / 256;
		szSendCommand[nCnt++] = 0;
		szSendCommand[nCnt++] = 0;
		szSendCommand[nCnt++] = 0;
		szSendCommand[nCnt++] = 0;
		szSendCommand[nCnt++] = 0;
		szSendCommand[nCnt++] = 0;
		//sprintf( szSendCommand , "%c%c%c%c%c%c%c%c%c%c" , VTY_LP_TOURI % 256 , VTY_LP_TOURI / 256 , VTY_CMD_TEST % 256 , VTY_CMD_TEST / 256 , 0 , 0 , 0 , 0 , 0 , 0 );
		if( ::TryEnterCriticalSection( &mSc ) == TRUE )
		{
			if( SEND_COMMAND( szSendCommand , 10 ) )
			{
				return RECV_COMMAND( szRecvCommand , NULL , 0 , &nLength );				
			}
			::LeaveCriticalSection( &mSc );
		}
	}
	
	return -1;
}


// ...
int CObj__VERITY_STD
::__Write__ANALOG(const CString& var_name, 
				  const CDS_IO__CHANNEL_INFO& io_info, 
				  const double set_data)
{
	return -1;
}

int CObj__VERITY_STD
::__Write__DIGITAL(const CString& var_name,
				   const CDS_IO__CHANNEL_INFO& io_info, 
				   const CString& set_data,
				   const int item_index)
{
	int nDataLength = 0;
	int nSendLength = 0;
	int nCnt = 0;
	unsigned char szSendCommand[DEFAULT_STR_LENGTH] = { 0 , };
	unsigned char szRecvCommand[DEFAULT_STR_LENGTH] = { 0 , };
	bool bResult = false;
	bool bStart = false;

	::EnterCriticalSection( &mSc );
	if( doCH__EPD_Start->Check__VARIABLE_NAME(var_name) > 0 )	// Start
	{
		szSendCommand[nCnt++] = VTY_LP_TOURI % 256;
		szSendCommand[nCnt++] = VTY_LP_TOURI / 256;
		szSendCommand[nCnt++] = VTY_CMD_START % 256;
		szSendCommand[nCnt++] = VTY_CMD_START / 256;
		szSendCommand[nCnt++] = 0;
		szSendCommand[nCnt++] = 0;
		szSendCommand[nCnt++] = DATA_LENGTH % 256;
		szSendCommand[nCnt++] = DATA_LENGTH / 256;
		szSendCommand[nCnt++] = 0;
		szSendCommand[nCnt++] = 0;
		//sprintf( szSendCommand , "%c%c%c%c%c%c%c%c%c%c%s" , VTY_LP_TOURI % 256 , VTY_LP_TOURI / 256 , VTY_CMD_START % 256 , VTY_CMD_START / 256 , 0 , 0 , DATA_LENGTH % 256 , DATA_LENGTH / 256 , 0 , 0 , g_szRecipeName );
		szSendCommand[138]	  = VTY_ASCII;
		szSendCommand[139]	  = strlen( g_szRecipeName );
		//sprintf( szSendCommand + 138 , "%c%c" , VTY_ASCII , strlen( g_szRecipeName ) );
		nSendLength = 140;
		g_stReport.nEndPoint = 0;
		bStart = true;
	}
	else if( doCH__EPD_Stop->Check__VARIABLE_NAME(var_name) > 0 )	// Stop
	{
		szSendCommand[nCnt++] = VTY_LP_TOURI % 256;
		szSendCommand[nCnt++] = VTY_LP_TOURI / 256;
		szSendCommand[nCnt++] = VTY_CMD_STOP % 256;
		szSendCommand[nCnt++] = VTY_CMD_STOP / 256;
		szSendCommand[nCnt++] = 0;
		szSendCommand[nCnt++] = 0;
		szSendCommand[nCnt++] = 0;
		szSendCommand[nCnt++] = 0;
		szSendCommand[nCnt++] = 0;
		szSendCommand[nCnt++] = 0;
		//sprintf( szSendCommand , "%c%c%c%c%c%c%c%c%c%c" , VTY_LP_TOURI % 256 , VTY_LP_TOURI / 256 , VTY_CMD_STOP % 256 , VTY_CMD_STOP / 256 , 0 , 0 , 0 , 0 , 0 , 0 );
		nSendLength = 10;
		g_stReport.nRunning = 1;
		while( !g_bEPDThreadPause )
		{
			Sleep( 1 );
		}
	}
	else if( doCH__EPD_Reset->Check__VARIABLE_NAME(var_name) > 0 )	// Reset
	{
		szSendCommand[nCnt++] = VTY_LP_TOURI % 256;
		szSendCommand[nCnt++] = VTY_LP_TOURI / 256;
		szSendCommand[nCnt++] = VTY_CMD_RESET % 256;
		szSendCommand[nCnt++] = VTY_CMD_RESET / 256;
		szSendCommand[nCnt++] = VTY_RSC_RESETALL % 256;
		szSendCommand[nCnt++] = VTY_RSC_RESETALL / 256;
		szSendCommand[nCnt++] = 0;
		szSendCommand[nCnt++] = 0;
		szSendCommand[nCnt++] = 0;
		szSendCommand[nCnt++] = 0;
		//sprintf( szSendCommand , "%c%c%c%c%c%c%c%c%c%c" , VTY_LP_TOURI % 256 , VTY_LP_TOURI / 256 , VTY_CMD_RESET % 256 , VTY_CMD_RESET / 256 , VTY_RSC_RESETALL % 256 , VTY_RSC_RESETALL / 256 , 0 , 0 , 0 , 0 );
		nSendLength = 10;
		g_stReport.nRunning = 1;
	}

	if( SEND_COMMAND( szSendCommand , nSendLength ) )
	{
		bResult = RECV_COMMAND( szRecvCommand , szSendCommand , 10 , &nDataLength );
		if( ( bResult ) && ( bStart ) )
		{
			g_stReport.nRunning = 2;
			return 1;
		}
	}
	::LeaveCriticalSection( &mSc );
	return -1;
}

int CObj__VERITY_STD
::__Write__STRING(const CString& var_name, 
				  const CDS_IO__CHANNEL_INFO& io_info, 
				  const CString& set_data)
{
	int nIndex = 0;
	int nCnt = 0;
	int nTempIndex = 0;
	unsigned char szSendCommand[MAX_STR_LENGTH] = { 0 , };
	unsigned char szRecvCommand[MAX_STR_LENGTH] = { 0 , };
	unsigned char szValue[DEFAULT_STR_LENGTH] = { 0 , };

	if( soCH__EPD_WAFER_INFO->Check__VARIABLE_NAME(var_name) > 0 )
	{
		memcpy( szRecvCommand , (unsigned char*)(LPCTSTR)set_data , set_data.GetLength() );
		szSendCommand[nCnt++] = VTY_LP_TOURI % 256;
		szSendCommand[nCnt++] = VTY_LP_TOURI / 256;
		szSendCommand[nCnt++] = VTY_CMD_WAFERINFO % 256;
		szSendCommand[nCnt++] = VTY_CMD_WAFERINFO / 256;
		szSendCommand[nCnt++] = VTY_WISC_NEWWAFER % 256;
		szSendCommand[nCnt++] = VTY_WISC_NEWWAFER / 256;
		szSendCommand[nCnt++] = 1584 % 256;
		szSendCommand[nCnt++] = 1584 / 256;
		szSendCommand[nCnt++] = 0;
		szSendCommand[nCnt++] = 0;
		//sprintf( szSendCommand , "%c%c%c%c%c%c%c%c%c%c" , VTY_LP_TOURI % 256 , VTY_LP_TOURI / 256 , VTY_CMD_WAFERINFO % 256 , VTY_CMD_WAFERINFO / 256 , VTY_WISC_NEWWAFER % 256 , VTY_WISC_NEWWAFER / 256 , 1584 % 256 , 1584 / 256 , 0 , 0 );
			
		for( nIndex = 0; nIndex < 6; nIndex++ )
		{
			nTempIndex = 10 + ( nIndex * 264 );
			DATA_SEPERATE( szRecvCommand , '|' , szValue , szRecvCommand , DEFAULT_STR_LENGTH );
			//strcat( szSendCommand + nTempIndex , szValue );
			memcpy( szSendCommand + nTempIndex , szValue , strlen((char*)szValue) );
			szSendCommand[nTempIndex + 129] = strlen( (char*)szValue );
			DATA_SEPERATE( szRecvCommand , '|' , szValue , szRecvCommand , DEFAULT_STR_LENGTH );
			//strcat( szSendCommand + nTempIndex + 130 , szValue );
			memcpy( szSendCommand + nTempIndex + 130 , szValue , strlen((char*)szValue) );
			szSendCommand[nTempIndex + 259] = strlen( (char*)szValue );
			TypeConvert.nData = g_nData[nIndex];
			memcpy( &( szSendCommand[nTempIndex + 260] ) , TypeConvert.szData , 4 );
		}
		::EnterCriticalSection( &mSc );
		if( SEND_COMMAND( szSendCommand , 1594 ) )
		{
			RECV_COMMAND( szRecvCommand , szSendCommand , 10 , &nTempIndex );
		}
		::LeaveCriticalSection( &mSc );
		return 1;
	}
	else if( soCH__EPD_Recipe_Name->Check__VARIABLE_NAME(var_name) > 0 )
	{	
		sprintf( g_szRecipeName , "%s" , set_data );
		return 1;
	}
	return -1;
}

