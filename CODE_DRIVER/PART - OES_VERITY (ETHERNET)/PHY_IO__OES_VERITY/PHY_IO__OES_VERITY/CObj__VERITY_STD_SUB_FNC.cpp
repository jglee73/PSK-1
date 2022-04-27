#include "StdAfx.h"
#include "CObj__VERITY_STD.h"

void CObj__VERITY_STD::
Fnc__Write_Log(const char *szMsg , bool _bSendRecv , bool _bResult , int _nLength)
{
	int nIndex= 0;
	CString szLogMsg;

	if( _bSendRecv )
		szLogMsg = "[SEND]";
	else
		szLogMsg = "[RECV]";

	if( _bResult )
		szLogMsg.Append(" [SUCCESS]");
	else
		szLogMsg.Append(" [COMFAIL]");


	for(nIndex = 0 ; nIndex < _nLength ; nIndex++ )
	{
		szLogMsg.Append(" %02x" , szMsg[nIndex]);
	}

	mX__Log_Ctrl->WRITE__LOG(szLogMsg);
}