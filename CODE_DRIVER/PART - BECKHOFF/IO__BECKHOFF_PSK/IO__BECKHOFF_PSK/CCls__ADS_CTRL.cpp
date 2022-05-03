#include "stdafx.h"
#include "CCls__ADS_CTRL.h"

#include "Macro_Function.h"


CCls__ADS_CTRL mADS_CTRL;


// ...
CCls__ADS_CTRL::CCls__ADS_CTRL()
{
	InitializeCriticalSection(&mCS_LOCK);

	bDRV_ERROR = false;
}
CCls__ADS_CTRL::~CCls__ADS_CTRL()
{
	DeleteCriticalSection(&mCS_LOCK);
}


// ...
void CCls__ADS_CTRL::Init__ADS_DRIVER(const int ads_port)
{
	EnterCriticalSection(&mCS_LOCK);

	_Init__ADS_DRIVER(ads_port);

	LeaveCriticalSection(&mCS_LOCK);
}
void CCls__ADS_CTRL::_Init__ADS_DRIVER(const int ads_port)
{
	long nPort = AdsPortOpen();
	long nErr = AdsGetLocalAddress(&mAMS_ADDR);

	printf(" * AdsPortOpen() : nPort(%1d) \n", nPort);
	printf(" * AdsGetLocalAddress() : nErr(%1d) \n", nErr);

	// ADDR ...
	{
		int i_limit = iList_NETID.GetSize();

		for(int i=0; i<_CFG__NETID_SIZE; i++)
		{
			if(i < i_limit)			mAMS_ADDR.netId.b[i] = iList_NETID[i];
			else					mAMS_ADDR.netId.b[i] = 0;
		}

		// TwinCAT 3 PLC1 : 851
		// TwinCAT 2 PLC1 : 801

		mAMS_ADDR.port = ads_port;
	}

	// ...
	{
		PAmsAddr pAddr = &mAMS_ADDR;

		AdsVersion Version;
		AdsVersion *pVersion = &Version;
		char       pDevName[50];

		nErr = AdsSyncReadDeviceInfoReq(pAddr, pDevName, pVersion);
		if (nErr)
		{
			printf("Error(%1d) : AdsSyncReadDeviceInfoReq() \n", nErr);

			sDRV_INFO__DEV_NAME = "???";
			iDRV_INFO__VERSION  = 0;
			iDRV_INFO__REVISION = 0;
			iDRV_INFO__BUILD = 0;
		}
		else
		{
			sDRV_INFO__DEV_NAME.Format("%s", pDevName);
			iDRV_INFO__VERSION  = (int)pVersion->version;
			iDRV_INFO__REVISION = (int)pVersion->revision;
			iDRV_INFO__BUILD = pVersion->build;
		}
	}

	//...
}

int  CCls__ADS_CTRL::
Link__ADS_VR_INFO(const CString& io_name,const CString& ads_name, const int md_id,const int ch_id)
{
	int io_type = _IO_TYPE__VR;

	_Add__ADS_IO(io_type, io_name, ads_name, md_id, ch_id);
	return 1;
}
int  CCls__ADS_CTRL::
Link__ADS_DO_INFO(const CString& io_name,const CString& ads_name, const int md_id,const int ch_id)
{
	int io_type = _IO_TYPE__DO;

	_Add__ADS_IO(io_type, io_name, ads_name, md_id, ch_id);
	return 1;
}
int  CCls__ADS_CTRL::
Link__ADS_AO_INFO(const CString& io_name,const CString& ads_name, const int md_id,const int ch_id)
{
	int io_type = _IO_TYPE__AO;

	_Add__ADS_IO(io_type, io_name, ads_name, md_id, ch_id);
	return 1;
}
int  CCls__ADS_CTRL::
Link__ADS_SO_INFO(const CString& io_name,const CString& ads_name, const int md_id,const int ch_id)
{
	int io_type = _IO_TYPE__SO;

	_Add__ADS_IO(io_type, io_name, ads_name, md_id, ch_id);
	return 1;
}

int  CCls__ADS_CTRL::Init__ADS_ADDR()
{
	EnterCriticalSection(&mCS_LOCK);

	int r_flag = _Init__ADS_ADDR();

	LeaveCriticalSection(&mCS_LOCK);
	return r_flag;
}
int  CCls__ADS_CTRL::_Init__ADS_ADDR()
{
	bDRV_ERROR = false;

	// ...
	PAmsAddr pAddr = &mAMS_ADDR; 
	char io_str[256];

	int i_limit = pList_IO.GetSize();
	for(int i=0; i<i_limit; i++)
	{
		CCls__ADS_IO* p_io = (CCls__ADS_IO*) pList_IO[i];

		strcpy(io_str, p_io->sADS_NAME);

		long nErr = AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(p_io->lVAR_ADDR), &p_io->lVAR_ADDR, sizeof(io_str), io_str);
		if(nErr)
		{
			bDRV_ERROR = true;
			sDRV_ERR_VAR = p_io->sIO_NAME;

			p_io->lVAR_ADDR = NULL;
			printf("Error: AdsSyncReadWriteReq: %1d (0x%X) \n", nErr,nErr);
			printf(" * Error.Variable <- [%s] \n", p_io->sIO_NAME);
			continue;
		}
	}
	return 1;
}

int  CCls__ADS_CTRL::Close__ADS_ADDR()
{
	EnterCriticalSection(&mCS_LOCK);

	int r_flag = _Close__ADS_ADDR();

	LeaveCriticalSection(&mCS_LOCK);
	return r_flag;
}
int  CCls__ADS_CTRL::_Close__ADS_ADDR()
{
	PAmsAddr pAddr = &mAMS_ADDR; 
	long nErr;

	int i_limit = pList_IO.GetSize();

	for(int i=0; i<i_limit; i++)
	{
		CCls__ADS_IO* p_io = (CCls__ADS_IO*) pList_IO[i];

		if(p_io->lVAR_ADDR != NULL)			continue;

		nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_RELEASEHND, 0, sizeof(p_io->lVAR_ADDR), &p_io->lVAR_ADDR); 
		if (nErr)
		{
			printf("Error(1) : AdsSyncWriteReq: %1d \n", nErr);
			break;
		}

		p_io->lVAR_ADDR = NULL;
	}

	// ...
	{
		nErr = AdsPortClose(); 
		if (nErr)			printf("Error: AdsPortClose: %1d \n", nErr);
	}
	return 1;
}

bool CCls__ADS_CTRL::Check__DRV_ERROR(CString& err_var)
{
	EnterCriticalSection(&mCS_LOCK);

	bool drv_err = bDRV_ERROR;
	err_var = sDRV_ERR_VAR;

	LeaveCriticalSection(&mCS_LOCK);
	return drv_err;
}
void CCls__ADS_CTRL::Clear__DRV_ERROR()
{
	EnterCriticalSection(&mCS_LOCK);

	bDRV_ERROR = false;
	sDRV_ERR_VAR = "";

	LeaveCriticalSection(&mCS_LOCK);
}

void CCls__ADS_CTRL::Show__ADS_INFO()
{
	EnterCriticalSection(&mCS_LOCK);

	_Show__ADS_INFO();

	LeaveCriticalSection(&mCS_LOCK);
}
void CCls__ADS_CTRL::_Show__ADS_INFO()
{
	printf(" CCls__ADS_CTRL::Show__ADS_INFO() ... \n");

	PAmsAddr pAddr = &mAMS_ADDR; 

	int i_limit = pList_IO.GetSize();

	for(int i=0; i<i_limit; i++)
	{
		CCls__ADS_IO* p_io = (CCls__ADS_IO*) pList_IO[i];

		if(p_io->lVAR_ADDR == NULL)		printf(" * %02d) %s : Error \n", i+1, p_io->sADS_NAME);
		else							printf(" * %02d) %s : [%1d] \n", i+1, p_io->sADS_NAME, p_io->lVAR_ADDR);
	}

	printf("\n");
}


AmsAddr* CCls__ADS_CTRL::Get__AMS_ADDR()
{
	return &mAMS_ADDR; 
}

void CCls__ADS_CTRL::Get__DEV_IINFO(CCls__DEV_INFO& dev_info)
{
	EnterCriticalSection(&mCS_LOCK);

	dev_info.sDEV_NAME = sDRV_INFO__DEV_NAME;
	dev_info.iVERSION  = iDRV_INFO__VERSION;
	dev_info.iREVISION = iDRV_INFO__REVISION;
	dev_info.iBUILD    = iDRV_INFO__BUILD;

	LeaveCriticalSection(&mCS_LOCK);
}

int  CCls__ADS_CTRL::Set__VAR_ACTIVE(const bool set_data)
{
	EnterCriticalSection(&mCS_LOCK);

	int r_flag = _Set__VAR_ACTIVE(set_data);

	LeaveCriticalSection(&mCS_LOCK);
	return r_flag;
}
int  CCls__ADS_CTRL::_Set__VAR_ACTIVE(const bool set_data)
{
	int io_type = _IO_TYPE__VR;
	CString io_name = _IO_NAME__diACTIVE;

	return _Set__ADS_IO(io_type, io_name, set_data);
}

int  CCls__ADS_CTRL::Get__VAR_ACTIVE()
{
	EnterCriticalSection(&mCS_LOCK);

	int r_flag = _Get__VAR_ACTIVE();

	LeaveCriticalSection(&mCS_LOCK);
	return r_flag;
}
int  CCls__ADS_CTRL::_Get__VAR_ACTIVE()
{
	int io_type = _IO_TYPE__VR;
	CString io_name = _IO_NAME__doACTIVE;

	bool r_data;

	int r_flag = _Get__ADS_IO(io_type, io_name, r_data);
	if(r_flag < 0)		return -1;

	if(r_data)			return 1;
	return -1;
}


// ...
void CCls__ADS_CTRL::_Add__ADS_IO(const int io_type, 
								  const CString& io_name, 
								  const CString& ads_name, 
								  const int md_id, 
								  const int ch_id)
{
	CCls__ADS_IO* p_io = new CCls__ADS_IO;
	pList_IO.Add(p_io);

	p_io->iIO_TYPE  = io_type;
	p_io->sIO_NAME  = io_name;
	p_io->sADS_NAME = ads_name;

	p_io->iMD_ID = md_id;
	p_io->iCH_ID = ch_id;
}

int  CCls__ADS_CTRL::_Set__ADS_IO(const int io_type, const CString& io_name, bool set_data)
{
	PAmsAddr pAddr = &mAMS_ADDR; 

	int i_limit = pList_IO.GetSize();

	for(int i=0; i<i_limit; i++)
	{
		CCls__ADS_IO* p_io = (CCls__ADS_IO*) pList_IO[i];

		if(p_io->iIO_TYPE != io_type)							continue;
		if(p_io->sIO_NAME.CompareNoCase(io_name) != 0)			continue;
		if(p_io->lVAR_ADDR == NULL)								return -11;

		long nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, p_io->lVAR_ADDR, sizeof(set_data), &set_data); 
		if (nErr)
		{
			if(!bDRV_ERROR)
			{
				bDRV_ERROR = true;
				sDRV_ERR_VAR = p_io->sIO_NAME;
			}

			printf("Error(11): AdsSyncWriteReq: %1d \n", nErr);
			return -12;
		}

		return 1;
	}

	return -1;
}
int  CCls__ADS_CTRL::_Get__ADS_IO(const int io_type, const CString& io_name, bool& get_data)
{
	PAmsAddr pAddr = &mAMS_ADDR; 

	int i_limit = pList_IO.GetSize();

	for(int i=0; i<i_limit; i++)
	{
		CCls__ADS_IO* p_io = (CCls__ADS_IO*) pList_IO[i];

		if(p_io->iIO_TYPE != io_type)							continue;
		if(p_io->sIO_NAME.CompareNoCase(io_name) != 0)			continue;
		if(p_io->lVAR_ADDR == NULL)								return -11;

		bool r_data;

		long nErr = AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, p_io->lVAR_ADDR, sizeof(r_data), &r_data); 
		if (nErr) 
		{
			if(!bDRV_ERROR)
			{
				bDRV_ERROR = true;
				sDRV_ERR_VAR = p_io->sIO_NAME;
			}

			printf("Error(21): AdsSyncReadReq: %1d \n", nErr); 
			return -12;
		}

		get_data = r_data;
		return 1;
	}

	return -22;
}

int  CCls__ADS_CTRL::
_Set__ADS_IO_SO(const CString& io_name, const int md_id, const int ch_id, const CString& ads_type, const CString& set_data)
{
	PAmsAddr pAddr = &mAMS_ADDR; 

	int i_limit = pList_IO.GetSize();

	for(int i=0; i<i_limit; i++)
	{
		CCls__ADS_IO* p_io = (CCls__ADS_IO*) pList_IO[i];

		if(p_io->iMD_ID != md_id)					continue;
		if(p_io->iCH_ID != ch_id)					continue;
		if(p_io->iIO_TYPE != _IO_TYPE__SO)			continue;

		if(p_io->lVAR_ADDR == NULL)					return -11;

		if(p_io->sIO_NAME.CompareNoCase(io_name) != 0)			continue;

		// ...
		long r_err = -10001;

		if(ads_type.CompareNoCase(_ADS_TYPE__BYTE) == 0)
		{
			unsigned char s_data = (unsigned char) atoi(set_data);

			r_err = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, p_io->lVAR_ADDR, sizeof(s_data), &s_data); 
		}
		else if(ads_type.CompareNoCase(_ADS_TYPE__USINT) == 0)
		{
			unsigned char s_data = (unsigned char) atoi(set_data);

			r_err = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, p_io->lVAR_ADDR, sizeof(s_data), &s_data); 
		}
		else if(ads_type.CompareNoCase(_ADS_TYPE__UDINT) == 0)
		{
			DWORD s_data = (DWORD) atoi(set_data);

			r_err = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, p_io->lVAR_ADDR, sizeof(s_data), &s_data); 
		}
		else if(ads_type.CompareNoCase(_ADS_TYPE__INT) == 0)
		{
			WORD s_data = (WORD) atoi(set_data);

			r_err = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, p_io->lVAR_ADDR, sizeof(s_data), &s_data); 
		}
		else if(ads_type.CompareNoCase(_ADS_TYPE__REAL) == 0)
		{
			float s_data = (float) atof(set_data);

			r_err = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, p_io->lVAR_ADDR, sizeof(s_data), &s_data); 
		}

		if(r_err)
		{
			if(!bDRV_ERROR)
			{
				bDRV_ERROR = true;
				sDRV_ERR_VAR = p_io->sIO_NAME;
			}

			printf("Error(%1d) : _Set__ADS_IO_SO() - AdsSyncWriteReq() \n", r_err);
			return -21;
		}
		return 1;
	}

	return -1;
}
int  CCls__ADS_CTRL::
_Get__ADS_IO_SO(const CString& io_name, const int md_id, const int ch_id, const CString& ads_type, CString& get_data)
{
	PAmsAddr pAddr = &mAMS_ADDR; 

	int i_limit = pList_IO.GetSize();

	for(int i=0; i<i_limit; i++)
	{
		CCls__ADS_IO* p_io = (CCls__ADS_IO*) pList_IO[i];

		if(p_io->iMD_ID != md_id)					continue;
		if(p_io->iCH_ID != ch_id)					continue;
		if(p_io->iIO_TYPE != _IO_TYPE__SO)			continue;

		if(p_io->lVAR_ADDR == NULL)					return -11;

		if(p_io->sIO_NAME.CompareNoCase(io_name) != 0)			continue;

		// ...
		long r_err = -10001;

		if(ads_type.CompareNoCase(_ADS_TYPE__BYTE) == 0)
		{
			unsigned char r_data;

			r_err = AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, p_io->lVAR_ADDR, sizeof(r_data), &r_data); 

			get_data.Format("%1d", 0x0ff & r_data);
		}
		else if(ads_type.CompareNoCase(_ADS_TYPE__USINT) == 0)
		{
			unsigned char r_data;

			r_err = AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, p_io->lVAR_ADDR, sizeof(r_data), &r_data); 

			get_data.Format("%1d", 0x0ff & r_data);
		}
		else if(ads_type.CompareNoCase(_ADS_TYPE__UDINT) == 0)
		{
			DWORD r_data;

			r_err = AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, p_io->lVAR_ADDR, sizeof(r_data), &r_data); 

			get_data.Format("%1d", r_data);
		}
		else if(ads_type.CompareNoCase(_ADS_TYPE__INT) == 0)
		{
			WORD r_data;

			r_err = AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, p_io->lVAR_ADDR, sizeof(r_data), &r_data); 

			get_data.Format("%1d", r_data);
		}
		else if(ads_type.CompareNoCase(_ADS_TYPE__REAL) == 0)
		{
			float r_data;

			r_err = AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, p_io->lVAR_ADDR, sizeof(r_data), &r_data); 

			get_data.Format("%.3f", r_data);
		}

		if(r_err)
		{
			if(!bDRV_ERROR)
			{
				bDRV_ERROR = true;
				sDRV_ERR_VAR = p_io->sIO_NAME;
			}

			printf("Error(%1d) : _Get__ADS_IO_SO() - AdsSyncReadReq() \n", r_err);
			printf("  * error <- %s \n",Macro__Get_TwinCAT_Error_Code(r_err));
			printf("  * ads_name <- %s \n",  p_io->sADS_NAME);
			printf("  * ads_type <- %s \n",  ads_type);
			printf("  * ads_addr <- %1d \n", p_io->lVAR_ADDR);
			return -21;
		}
		return 1;
	}

	return -1;
}
int  CCls__ADS_CTRL::_Get__ADS_IO_SI(const CString& io_name, const int md_id, const int ch_id, const CString& ads_type, CString& get_data)
{
	PAmsAddr pAddr = &mAMS_ADDR; 

	int i_limit = pList_IO.GetSize();

	for(int i=0; i<i_limit; i++)
	{
		CCls__ADS_IO* p_io = (CCls__ADS_IO*) pList_IO[i];

		if(p_io->iMD_ID != md_id)					continue;
		if(p_io->iCH_ID != ch_id)					continue;
		if(p_io->iIO_TYPE != _IO_TYPE__SI)			continue;

		if(p_io->lVAR_ADDR == NULL)					return -11;

		if(p_io->sIO_NAME.CompareNoCase(io_name) != 0)			continue;

		// ...
		long r_err = -10001;
	
		if(ads_type.CompareNoCase(_ADS_TYPE__BYTE) == 0)
		{
			unsigned char r_data;

			r_err = AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, p_io->lVAR_ADDR, sizeof(r_data), &r_data); 

			get_data.Format("%1d", 0x0ff & r_data);
		}
		else if(ads_type.CompareNoCase(_ADS_TYPE__USINT) == 0)
		{
			unsigned char r_data;

			r_err = AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, p_io->lVAR_ADDR, sizeof(r_data), &r_data); 

			get_data.Format("%1d", 0x0ff & r_data);
		}
		else if(ads_type.CompareNoCase(_ADS_TYPE__UDINT) == 0)
		{
			DWORD r_data;

			r_err = AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, p_io->lVAR_ADDR, sizeof(r_data), &r_data); 

			get_data.Format("%1d", r_data);
		}
		else if(ads_type.CompareNoCase(_ADS_TYPE__REAL) == 0)
		{
			float r_data;

			r_err = AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, p_io->lVAR_ADDR, sizeof(r_data), &r_data); 

			get_data.Format("%.3f", r_data);
		}

		if(r_err) 
		{
			if(!bDRV_ERROR)
			{
				bDRV_ERROR = true;
				sDRV_ERR_VAR = p_io->sIO_NAME;
			}

			printf("Error(%1d) : _Get__ADS_IO_SI() - AdsSyncReadReq() \n", r_err); 
			return -12;
		}
		return 1;
	}

	return -1;
}

int  CCls__ADS_CTRL::_Set__ADS_IO_DO(const CString& io_name, const int md_id, const int ch_id, bool set_data)
{
	PAmsAddr pAddr = &mAMS_ADDR; 

	int i_limit = pList_IO.GetSize();

	for(int i=0; i<i_limit; i++)
	{
		CCls__ADS_IO* p_io = (CCls__ADS_IO*) pList_IO[i];

		if(p_io->iMD_ID != md_id)					continue;
		if(p_io->iCH_ID != ch_id)					continue;
		if(p_io->iIO_TYPE != _IO_TYPE__DO)			continue;

		if(p_io->lVAR_ADDR == NULL)					return -11;

		if(p_io->sIO_NAME.CompareNoCase(io_name) != 0)			continue;

		long nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, p_io->lVAR_ADDR, sizeof(set_data), &set_data); 
		if (nErr)
		{
			if(!bDRV_ERROR)
			{
				bDRV_ERROR = true;
				sDRV_ERR_VAR = p_io->sIO_NAME;
			}

			printf("Error(%1d) : _Set__ADS_IO_DO() - AdsSyncWriteReq() \n", nErr);
			return -21;
		}

		return 1;
	}

	return -1;
}
int  CCls__ADS_CTRL::_Get__ADS_IO_DO(const CString& io_name, const int md_id, const int ch_id, bool& r_data)
{
	PAmsAddr pAddr = &mAMS_ADDR; 

	int i_limit = pList_IO.GetSize();

	for(int i=0; i<i_limit; i++)
	{
		CCls__ADS_IO* p_io = (CCls__ADS_IO*) pList_IO[i];

		if(p_io->iMD_ID != md_id)					continue;
		if(p_io->iCH_ID != ch_id)					continue;
		if(p_io->iIO_TYPE != _IO_TYPE__DO)			continue;

		if(p_io->lVAR_ADDR == NULL)					return -11;
		
		if(p_io->sIO_NAME.CompareNoCase(io_name) != 0)			continue;

		//
		long nErr = AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, p_io->lVAR_ADDR, sizeof(r_data), &r_data); 
		if (nErr)
		{
			if(!bDRV_ERROR)
			{
				bDRV_ERROR = true;
				sDRV_ERR_VAR = p_io->sIO_NAME;
			}

			printf("Error(%1d) :_Get__ADS_IO_DO() - AdsSyncReadReq() \n", nErr); 
			return -21;
		}

		return 1;
	}

	return -1;
}
int  CCls__ADS_CTRL::_Get__ADS_IO_DI(const CString& io_name, const int md_id, const int ch_id, bool& r_data)
{
	PAmsAddr pAddr = &mAMS_ADDR; 

	int i_limit = pList_IO.GetSize();

	for(int i=0; i<i_limit; i++)
	{
		CCls__ADS_IO* p_io = (CCls__ADS_IO*) pList_IO[i];

		if(p_io->iMD_ID != md_id)					continue;
		if(p_io->iCH_ID != ch_id)					continue;
		if(p_io->iIO_TYPE != _IO_TYPE__DI)			continue;

		if(p_io->lVAR_ADDR == NULL)					return -11;

		if(p_io->sIO_NAME.CompareNoCase(io_name) != 0)			continue;

		//
		long nErr = AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, p_io->lVAR_ADDR, sizeof(r_data), &r_data); 
		if (nErr) 
		{
			if(!bDRV_ERROR)
			{
				bDRV_ERROR = true;
				sDRV_ERR_VAR = p_io->sIO_NAME;
			}

			printf("Error(%1d) : _Get__ADS_IO_DI() - AdsSyncReadReq() \n", nErr); 
			return -12;
		}

		return 1;
	}

	return -1;
}

int  CCls__ADS_CTRL::_Set__ADS_IO_AO(const CString& io_name, const int md_id, const int ch_id, const CString& ads_type, const int cnt_byte, const double set_data)
{
	PAmsAddr pAddr = &mAMS_ADDR; 

	int i_limit = pList_IO.GetSize();

	for(int i=0; i<i_limit; i++)
	{
		CCls__ADS_IO* p_io = (CCls__ADS_IO*) pList_IO[i];

		if(p_io->iMD_ID != md_id)					continue;
		if(p_io->iCH_ID != ch_id)					continue;
		if(p_io->iIO_TYPE != _IO_TYPE__AO)			continue;

		if(p_io->lVAR_ADDR == NULL)					return -11;

		if(p_io->sIO_NAME.CompareNoCase(io_name) != 0)			continue;

		// ...
		long r_err = 1;

		if(ads_type.CompareNoCase(_ADS_TYPE__REAL) == 0)
		{
			float s_data = (float) set_data;

			r_err = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, p_io->lVAR_ADDR, sizeof(s_data), &s_data); 
		}
		else if(ads_type.CompareNoCase(_ADS_TYPE__DINT) == 0)
		{
			DWORD s_data = (DWORD) set_data;

			r_err = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, p_io->lVAR_ADDR, sizeof(s_data), &s_data); 			
		}
		else
		{
			if(cnt_byte > 2)
			{
				DWORD s_data = (DWORD) set_data;

				r_err = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, p_io->lVAR_ADDR, sizeof(s_data), &s_data); 
			}
			else
			{
				WORD s_data = (WORD) set_data;

				r_err = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, p_io->lVAR_ADDR, sizeof(s_data), &s_data); 
			}
		}

		if(r_err)
		{
			if(!bDRV_ERROR)
			{
				bDRV_ERROR = true;
				sDRV_ERR_VAR = p_io->sIO_NAME;
			}

			printf("Error(%1d) : _Set__ADS_IO_AO() - AdsSyncWriteReq() \n", r_err);
			return -21;
		}
		return 1;
	}

	return -1;
}
int  CCls__ADS_CTRL::_Get__ADS_IO_AO(const CString& io_name, const int md_id, const int ch_id, const CString& ads_type, const int cnt_byte, double& read_data)
{
	PAmsAddr pAddr = &mAMS_ADDR; 

	int i_limit = pList_IO.GetSize();

	for(int i=0; i<i_limit; i++)
	{
		CCls__ADS_IO* p_io = (CCls__ADS_IO*) pList_IO[i];

		if(p_io->iMD_ID != md_id)					continue;
		if(p_io->iCH_ID != ch_id)					continue;
		if(p_io->iIO_TYPE != _IO_TYPE__AO)			continue;

		if(p_io->lVAR_ADDR == NULL)					return -11;

		if(p_io->sIO_NAME.CompareNoCase(io_name) != 0)			continue;

		// ...
		long r_err = 1;

		if(ads_type.CompareNoCase(_ADS_TYPE__REAL) == 0)
		{
			float r_data = 0;

			r_err = AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, p_io->lVAR_ADDR, sizeof(r_data), &r_data); 

			read_data = (double) r_data;
		}
		else if(ads_type.CompareNoCase(_ADS_TYPE__DINT) == 0)
		{
			DWORD r_data = 0;

			r_err = AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, p_io->lVAR_ADDR, sizeof(r_data), &r_data); 

			read_data = (double) r_data;
		}
		else
		{
			if(cnt_byte > 2)
			{
				DWORD r_data = 0;

				r_err = AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, p_io->lVAR_ADDR, sizeof(r_data), &r_data); 
	
				read_data = (double) r_data;
			}
			else
			{
				WORD r_data = 0;

				r_err = AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, p_io->lVAR_ADDR, sizeof(r_data), &r_data); 
	
				read_data = (double) r_data;
			}
		}

		if(r_err) 
		{
			if(!bDRV_ERROR)
			{
				bDRV_ERROR = true;
				sDRV_ERR_VAR = p_io->sIO_NAME;
			}

			printf("Error(%1d) : _Get__ADS_IO_AO() - AdsSyncReadReq() \n", r_err); 
			return -12;
		}
		return 1;
	}

	return -1;
}
int  CCls__ADS_CTRL::_Get__ADS_IO_AI(const CString& io_name, const int md_id, const int ch_id, const int cnt_byte, double& read_data)
{
	PAmsAddr pAddr = &mAMS_ADDR; 

	int i_limit = pList_IO.GetSize();

	for(int i=0; i<i_limit; i++)
	{
		CCls__ADS_IO* p_io = (CCls__ADS_IO*) pList_IO[i];

		if(p_io->iMD_ID != md_id)					continue;
		if(p_io->iCH_ID != ch_id)					continue;
		if(p_io->iIO_TYPE != _IO_TYPE__AI)			continue;

		if(p_io->lVAR_ADDR == NULL)					return -11;

		if(p_io->sIO_NAME.CompareNoCase(io_name) != 0)			continue;

		// ...
		long r_err = 1;

		if(cnt_byte > 2)
		{
			DWORD r_data = 0;

			r_err = AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, p_io->lVAR_ADDR, sizeof(r_data), &r_data); 

			read_data = (double) r_data;
		}
		else
		{
			WORD r_data = 0;

			r_err = AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, p_io->lVAR_ADDR, sizeof(r_data), &r_data); 

			read_data = (double) r_data;
		}

		if(r_err) 
		{
			if(!bDRV_ERROR)
			{
				bDRV_ERROR = true;
				sDRV_ERR_VAR = p_io->sIO_NAME;
			}

			printf("Error(%1d) : _Get__ADS_IO_AI() - AdsSyncReadReq() \n", r_err); 
			return -12;
		}
		return 1;
	}

	return -1;
}


// ...
int  CCls__ADS_CTRL::Set__IO_SO(const CString& io_name, const int md_id, const int ch_id, const CString& ads_type, const CString& set_data)
{
	EnterCriticalSection(&mCS_LOCK);

	int r_flag = _Set__ADS_IO_SO(io_name, md_id, ch_id, ads_type, set_data);	

	LeaveCriticalSection(&mCS_LOCK);
	return r_flag;
}
int  CCls__ADS_CTRL::Get__IO_SO(const CString& io_name, const int md_id, const int ch_id, const CString& ads_type, CString& r_data)
{
	EnterCriticalSection(&mCS_LOCK);

	int r_flag = _Get__ADS_IO_SO(io_name, md_id, ch_id, ads_type, r_data);	

	LeaveCriticalSection(&mCS_LOCK);
	return r_flag;
}
int  CCls__ADS_CTRL::Get__IO_SI(const CString& io_name, const int md_id, const int ch_id, const CString& ads_type, CString& r_data)
{
	EnterCriticalSection(&mCS_LOCK);

	int r_flag = _Get__ADS_IO_SI(io_name, md_id, ch_id, ads_type, r_data);	

	LeaveCriticalSection(&mCS_LOCK);
	return r_flag;
}

int  CCls__ADS_CTRL::Set__IO_DO(const CString& io_name, const int md_id, const int ch_id, bool set_data)
{
	EnterCriticalSection(&mCS_LOCK);

	int r_flag = _Set__ADS_IO_DO(io_name, md_id, ch_id, set_data);	

	LeaveCriticalSection(&mCS_LOCK);
	return r_flag;
}
int  CCls__ADS_CTRL::Get__IO_DO(const CString& io_name, const int md_id, const int ch_id, bool& r_data)
{
	EnterCriticalSection(&mCS_LOCK);

	int r_flag = _Get__ADS_IO_DO(io_name, md_id, ch_id, r_data);	

	LeaveCriticalSection(&mCS_LOCK);
	return r_flag;
}
int  CCls__ADS_CTRL::Get__IO_DI(const CString& io_name, const int md_id, const int ch_id, bool& r_data)
{
	EnterCriticalSection(&mCS_LOCK);

	int r_flag = _Get__ADS_IO_DI(io_name, md_id, ch_id, r_data);	

	LeaveCriticalSection(&mCS_LOCK);
	return r_flag;
}

int  CCls__ADS_CTRL::Set__IO_AO(const CString& io_name, const int md_id, const int ch_id, const CString& ads_type, const int cnt_byte, const double s_data)
{
	EnterCriticalSection(&mCS_LOCK);

	int r_flag = _Set__ADS_IO_AO(io_name, md_id, ch_id, ads_type, cnt_byte, s_data);	

	LeaveCriticalSection(&mCS_LOCK);
	return r_flag;
}
int  CCls__ADS_CTRL::Get__IO_AO(const CString& io_name, const int md_id, const int ch_id, const CString& ads_type, const int cnt_byte, double& r_data)
{
	EnterCriticalSection(&mCS_LOCK);

	int r_flag = _Get__ADS_IO_AO(io_name, md_id, ch_id, ads_type, cnt_byte, r_data);	

	LeaveCriticalSection(&mCS_LOCK);
	return r_flag;
}
int  CCls__ADS_CTRL::Get__IO_AI(const CString& io_name, const int md_id, const int ch_id, const int cnt_byte, double& r_data)
{
	EnterCriticalSection(&mCS_LOCK);

	int r_flag = _Get__ADS_IO_AI(io_name, md_id, ch_id, cnt_byte, r_data);	

	LeaveCriticalSection(&mCS_LOCK);
	return r_flag;
}


