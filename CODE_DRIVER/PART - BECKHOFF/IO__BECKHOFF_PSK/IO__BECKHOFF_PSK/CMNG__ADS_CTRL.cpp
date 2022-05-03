#include "stdafx.h"
#include "CMNG__ADS_CTRL.h"

#include "Macro_Function.h"


#include "CDB__ADS_CTRL.h"
extern CDB__ADS_CTRL mDB__ADS_CTRL;

#include "CCls__ADS_CTRL.h"
extern CCls__ADS_CTRL mADS_CTRL;

#include "CCH__ADS_CTRL.h"
extern CCH__ADS_CTRL mCH__ADS_IN;
extern CCH__ADS_CTRL mCH__ADS_OUT;


CMNG__ADS_CTRL mMNG__ADS_CTRL; 


// ...
CMNG__ADS_CTRL::CMNG__ADS_CTRL()
{
	bActive__ADS_DRIVER = false;
}
CMNG__ADS_CTRL::~CMNG__ADS_CTRL()
{

}

// ...
int CMNG__ADS_CTRL::Init__ADS_LINK(const int active_sim)
{
	// DB.ADS_IN ...
	{
		CDRV__ADS_INFO* p_ads_drv = &mADS_IN;
		CDB__ADS_INFO* p_ads_db = &(mDB__ADS_CTRL.mDB__ADS_IN);
		
		Init__ADS_INFO(false, p_ads_drv,p_ads_db, active_sim);
	}
	
	// DB.ADS_OUT ...
	{
		CDRV__ADS_INFO* p_ads_drv = &mADS_OUT;
		CDB__ADS_INFO* p_ads_db = &(mDB__ADS_CTRL.mDB__ADS_OUT);

		Init__ADS_INFO(true, p_ads_drv,p_ads_db, active_sim);
	}

	bActive__ADS_DRIVER = true;
	return 1;
}

CString CMNG__ADS_CTRL::Get__ADS_OUT_INFO()
{
	return mADS_OUT.Get__ADS_INFO();
}
CString CMNG__ADS_CTRL::Get__ADS_IN_INFO()
{
	return mADS_IN.Get__ADS_INFO();
}
CString CMNG__ADS_CTRL::Get__ADS_TOTAL_INFO(const bool active_print)
{
	CString log_msg;
	CString log_bff;

	// ...
	mDB__ADS_CTRL.Clear__ADS_TOTAL_ALL();

	// ...
	AmsAddr* p_addr = mADS_CTRL.Get__AMS_ADDR();

	char *pchSymbols = NULL; 
	AdsSymbolUploadInfo tAdsSymbolUploadInfo; 
	PAdsSymbolEntry pAdsSymbolEntry; 

	// ...
	long n_err;

	n_err = AdsSyncReadReq( p_addr, 
							ADSIGRP_SYM_UPLOADINFO, 
							0x0, 
							sizeof(tAdsSymbolUploadInfo), 
							&tAdsSymbolUploadInfo);

	if(n_err != 0x00)
	{
		log_bff.Format(" * AdsSyncReadReq( ADSIGRP_SYM_UPLOADINFO ) : err (%1d) \n", n_err);
		log_msg += log_bff;

		log_bff.Format(" * Error_Msg <- %s \n", Macro__Get_TwinCAT_Error_Code(n_err));
		log_msg += log_bff;

		return log_msg;
	}

	if(active_print)
	{
		log_msg = "\n";
		log_bff.Format(" * tAdsSymbolUploadInfo.nSymSize <- %1d (byte) \n", tAdsSymbolUploadInfo.nSymSize);
		log_msg += log_bff;
		log_msg += "\n";
	}

	pchSymbols = new char[tAdsSymbolUploadInfo.nSymSize]; 

	// Read information about the PLC variables 
	n_err = AdsSyncReadReq( p_addr, 
						    ADSIGRP_SYM_UPLOAD, 
						    0, 
						    tAdsSymbolUploadInfo.nSymSize, 
						    pchSymbols); 

	if(n_err != 0x00)
	{
		log_bff.Format(" * AdsSyncReadReq( ADSIGRP_SYM_UPLOAD ) : err (%1d) \n", n_err);
		log_msg += log_bff;

		return log_msg;
	}

	// Output information about the PLC variables 
	pAdsSymbolEntry = (PAdsSymbolEntry) pchSymbols; 

	if(active_print)
	{
		log_bff.Format(" * Total Symbol.Size (%1d) \n", tAdsSymbolUploadInfo.nSymbols);
		log_msg += log_bff;
	}

	for (UINT uiIndex = 0; uiIndex < tAdsSymbolUploadInfo.nSymbols; uiIndex++)
	{ 
		CString str_name = PADSSYMBOLNAME(pAdsSymbolEntry);
		int i_group  = pAdsSymbolEntry->iGroup;
		int i_offset = pAdsSymbolEntry->iOffs;
		int i_size   = pAdsSymbolEntry->size;
		CString str_type = PADSSYMBOLTYPE(pAdsSymbolEntry);
		CString str_cmmt = PADSSYMBOLCOMMENT(pAdsSymbolEntry);

		mDB__ADS_CTRL.Load__ADS_TOTAL_INFO(str_name, i_size, str_type);

		if(active_print)
		{
			log_bff.Format(" * index_%02d \n", uiIndex);
			log_msg += log_bff;

			log_bff.Format("   Name    <- [%s]  \n",    PADSSYMBOLNAME(pAdsSymbolEntry));
			log_msg += log_bff;
			log_bff.Format("   iGroup  <- [%1d] \n",    pAdsSymbolEntry->iGroup);
			log_msg += log_bff;
			log_bff.Format("   iOffset <- [%1d] \n",    pAdsSymbolEntry->iOffs);
			log_msg += log_bff;
			log_bff.Format("   iSize   <- [%1d] \n",    pAdsSymbolEntry->size);
			log_msg += log_bff;
			log_bff.Format("   Symbol.Type <- [%s] \n", PADSSYMBOLTYPE(pAdsSymbolEntry));
			log_msg += log_bff;
			log_bff.Format("   Symbol.Cmmt <- [%s] \n", PADSSYMBOLCOMMENT(pAdsSymbolEntry));
			log_msg += log_bff;
		}

		pAdsSymbolEntry = PADSNEXTSYMBOLENTRY(pAdsSymbolEntry); 
	}

	if(active_print)
	{
		log_msg += "\n";
		printf(log_msg);
	}

	delete [] pchSymbols;
	return log_msg;
}

int CMNG__ADS_CTRL::Link__ADS_IN_INFO(const bool active_print)
{
	mDB__ADS_CTRL.Clear__ADS_IN_ALL();
	CCH__ADS_CTRL* p_ch_ctrl = &mCH__ADS_IN;

	// ...
	CStringArray l__io_name;
	CStringArray l__ads_full_name;

	p_ch_ctrl->Get__ADS_FULL_NAME_LIST(l__io_name, l__ads_full_name);

	// ...
	int i_limit = l__ads_full_name.GetSize();
	int i;

	for(i=0; i<i_limit; i++)
	{	
		CString io_name  = l__io_name[i];
		CString ads_name = l__ads_full_name[i];
		
		int data_size;
		CString data_type;

		if(mDB__ADS_CTRL.Get__ADS_TOTAL_INFO(ads_name, data_size,data_type) < 0)
		{
			continue;
		}

		int ads_index = mDB__ADS_CTRL.Load__ADS_IN_INFO(io_name,ads_name, data_size,data_type);
		p_ch_ctrl->Link__ADS_INDEX(i, ads_index);
	}
	return 1;
}
int CMNG__ADS_CTRL::Link__ADS_OUT_INFO(const bool active_print)
{
	mDB__ADS_CTRL.Clear__ADS_OUT_ALL();
	CCH__ADS_CTRL* p_ch_ctrl = &mCH__ADS_OUT;

	// ...
	CStringArray l__io_name;
	CStringArray l__ads_full_name;

	p_ch_ctrl->Get__ADS_FULL_NAME_LIST(l__io_name, l__ads_full_name);

	// ...
	int i_limit = l__ads_full_name.GetSize();
	int i;

	for(i=0; i<i_limit; i++)
	{	
		CString io_name  = l__io_name[i];
		CString ads_name = l__ads_full_name[i];

		int data_size;
		CString data_type;

		if(mDB__ADS_CTRL.Get__ADS_TOTAL_INFO(ads_name, data_size,data_type) < 0)
		{
			continue;
		}

		int ads_index = mDB__ADS_CTRL.Load__ADS_OUT_INFO(io_name,ads_name, data_size,data_type);
		p_ch_ctrl->Link__ADS_INDEX(i, ads_index);
	}
	return 1;
}

int CMNG__ADS_CTRL::Init__ADS_INFO(const bool active__ads_out, CDRV__ADS_INFO* p_ads_drv,CDB__ADS_INFO* p_ads_db, const int active_sim)
{
	CStringArray l__var_name;
	CStringArray l__var_type;

	p_ads_db->Get__ADS_LIST(l__var_name, l__var_type);

	// ...
	CStringArray l__ads_name;
	CUIntArray   l__ads_index;
	CStringArray l__ads_type;

	CStringArray l__err_name;
	CStringArray l__err_code;

	// ...
	CString str_err;
	long n_err;

	AdsSymbolEntry	Info_Var;
	AdsSymbolEntry*	pInfo_Var = &Info_Var;
	PAdsSymbolEntry pAdsSymbolEntry; 

	if(active_sim > 0)
	{
		long req_size = 0;
		int n_count = 0;

		int i_limit = l__var_name.GetSize();
		int i;

		for(i=0; i<i_limit; i++)
		{
			CString var_name = l__var_name[i];
			CString var_type = l__var_type[i];

			l__ads_name.Add(var_name);
			l__ads_index.Add(i);
			l__ads_type.Add(var_type);

				 if(var_type.CompareNoCase("BOOL") == 0)		req_size += 1;
			else if(var_type.CompareNoCase("BYTE") == 0)		req_size += 1;
			else if(var_type.CompareNoCase("WORD") == 0)		req_size += 2;
			else if(var_type.CompareNoCase("INT")  == 0)		req_size += 2;
			else    											req_size += 4;

			n_count++;
		}

		//
		p_ads_drv->iADS__MEMORYL_SIZE = req_size;
		p_ads_drv->iADS__ITEM_COUNT   = n_count;

		//
		p_ads_drv->sList__ADS_NAME.RemoveAll();
		p_ads_drv->iList__ADS_INDEX.RemoveAll();
		p_ads_drv->sList__ADS_TYPE.RemoveAll();

		p_ads_drv->sList__ADS_NAME.Copy(l__ads_name);
		p_ads_drv->iList__ADS_INDEX.Copy(l__ads_index);
		p_ads_drv->sList__ADS_TYPE.Copy(l__ads_type);
	}
	else
	{
		AmsAddr*  p_addr = mADS_CTRL.Get__AMS_ADDR();
		TDataPar* p_data_par = p_ads_drv->mADS__DATA_PAR;

		long req_size = 0;
		int n_count = 0;

		int i_limit = l__var_name.GetSize();
		int i;

		for(i=0; i<i_limit; i++)
		{
			char str__var_name[256];
			strcpy(str__var_name, l__var_name[i]);
			CString str__var_type = l__var_type[i];

			n_err = AdsSyncReadWriteReq(p_addr,
										ADSIGRP_SYM_INFOBYNAMEEX,
										0x0,
										sizeof(Info_Var),
										pInfo_Var, 
										sizeof(str__var_name),
										str__var_name);

			// Error ...
			if(n_err != 0x0)
			{
				str_err.Format("%1d", n_err);

				l__err_name.Add(str__var_name);
				l__err_code.Add(str_err);
				continue;
			}

			// 
			l__ads_name.Add(str__var_name);
			l__ads_index.Add(i);
			l__ads_type.Add(str__var_type);

			//
			pAdsSymbolEntry = (PAdsSymbolEntry) pInfo_Var;

			p_data_par[n_count].indexGroup  = pAdsSymbolEntry->iGroup;
			p_data_par[n_count].indexOffset = pAdsSymbolEntry->iOffs;
			p_data_par[n_count].length      = pAdsSymbolEntry->size;

			req_size += pAdsSymbolEntry->size;
			n_count++;
		}

		//
		p_ads_drv->iADS__MEMORYL_SIZE = req_size;
		p_ads_drv->iADS__ITEM_COUNT   = n_count;

		//
		p_ads_drv->sList__ADS_NAME.RemoveAll();
		p_ads_drv->iList__ADS_INDEX.RemoveAll();
		p_ads_drv->sList__ADS_TYPE.RemoveAll();

		p_ads_drv->sList__ADS_NAME.Copy(l__ads_name);
		p_ads_drv->iList__ADS_INDEX.Copy(l__ads_index);
		p_ads_drv->sList__ADS_TYPE.Copy(l__ads_type);
	}

	// Error List ...
	{
		p_ads_db->Load__ERR_INFO(l__err_name, l__err_code);
	}

	// ...
	{
		if(p_ads_drv->pADS_BUFFER != NULL)
		{
			delete [] p_ads_drv->pADS_BUFFER;
		}
		if(p_ads_drv->pADS_ERROR != NULL)
		{
			delete [] p_ads_drv->pADS_ERROR;
		}

		//
		int item_count  = p_ads_drv->iADS__ITEM_COUNT;
		int memory_size = p_ads_drv->iADS__MEMORYL_SIZE;

		int size__ads_buffer = 0;
		if(active__ads_out)
		{
			size__ads_buffer = (12 * item_count) + memory_size;
			
			int size__err_code = (4 * item_count) + 1;
			p_ads_drv->pADS_ERROR = new unsigned char[size__err_code];
		}
		else
		{
			size__ads_buffer = ( 4 * item_count) + memory_size;

			p_ads_drv->pADS_ERROR = NULL;
		}

		int max__ads_buffer  = size__ads_buffer + 1;

		p_ads_drv->pADS_BUFFER = new unsigned char[max__ads_buffer];
	}

	return 1;
}

int CMNG__ADS_CTRL::Update__ADS_READING(const bool active_print, const int active_sim)
{
	if(active_sim > 0)
	{

	}
	else
	{
		if(!bActive__ADS_DRIVER)		return -1;
	}

	// ...
	CDRV__ADS_INFO* p_ads_info = &mADS_IN;
	AmsAddr* p_addr = mADS_CTRL.Get__AMS_ADDR();

	// ...
	int item_count  = p_ads_info->iADS__ITEM_COUNT;
	int memory_size = p_ads_info->iADS__MEMORYL_SIZE;

	// ...
	int size__ads_buffer = (4 * item_count) + memory_size;
	int max__ads_buffer  = size__ads_buffer + 1;

	unsigned char* p_ads_buffer = p_ads_info->pADS_BUFFER;

	// ...
	long n_err;

	if(active_sim > 0)
	{

	}
	else
	{
		memset(p_ads_buffer, 0, max__ads_buffer);

		n_err = AdsSyncReadWriteReq(p_addr, 
									ADSIGRP_SUMUP_READ,					// 0xf080, 
									item_count, 
									size__ads_buffer,					// we request additional "error"-flag(long) for each ADS-sub commands
									(void*) p_ads_buffer, 
									12*item_count,						// send 12 bytes (3 * long : IG, IO, Len) of each ADS-sub command	
									&(p_ads_info->mADS__DATA_PAR));

		if(n_err != 0)
		{
			printf(" * AdsSyncReadWriteReq() \n");
			printf(" * Error_Code <- %1d \n", n_err);
			printf(" * Error_Msg  <- %s \n", Macro__Get_TwinCAT_Error_Code(n_err));
		}
	}

	// ...
	CString log_msg;
	CString log_bff;

	// ...
	TDataPar* p_data_par = p_ads_info->mADS__DATA_PAR;

	PBYTE pObjAdsRes    = (BYTE*) p_ads_buffer + (item_count * 4);		// point to ADS-data
	PBYTE pObjAdsErrRes = (BYTE*) p_ads_buffer;							// point to ADS-err
	PBYTE pdata = pObjAdsRes;

	if(n_err == 0)
	{
		for(long idx=0; idx<item_count; idx++)
		{
			CString ads_name = p_ads_info->sList__ADS_NAME[idx];
			int ads_index    = p_ads_info->iList__ADS_INDEX[idx];
			CString ads_type = p_ads_info->sList__ADS_TYPE[idx];

			if(active_print)
			{
				log_bff.Format(" * idx <- %1d \n", idx);
				log_msg += log_bff;

				log_bff.Format("   ** ads_name <- %s (%1d) (%s) \n", ads_name,ads_index,ads_type);
				log_msg += log_bff;
			}

			// was communication for ADS-sub command OK ??
			long nAdsErr = *(long*) pObjAdsErrRes;

			if(nAdsErr == 0)
			{
				int len = p_data_par[idx].length;

				mDB__ADS_CTRL.Set__ADS_IN_DATA(ads_index, len, pObjAdsRes);

				if(active_print)
				{
					log_bff.Format("   ** length <- %1d \n", len);
					log_msg += log_bff;

					log_bff = "      ";
					log_msg += log_bff;

					for(int t=0; t<len; t++)
					{
						log_bff.Format("[%02X] ", 0x0ff & *(pObjAdsRes + t));
						log_msg += log_bff;
					}
			
					log_bff = "\n";
					log_msg += log_bff;
				}

				if(active_print)
				{
					if(len == 4)
					{
						if(ads_type.CompareNoCase("DWORD") == 0)
						{
							DWORD data = *(DWORD*) pObjAdsRes;
						
							log_bff.Format("      %0X (%1d) \n", data, data);
							log_msg += log_bff;
						}
						else if(ads_type.CompareNoCase("REAL") == 0)
						{
							UNION_4_BYTE__FLOAT data;
							
							data.cBYTE[0] = *(BYTE*) (pObjAdsRes + 0);
							data.cBYTE[1] = *(BYTE*) (pObjAdsRes + 1);
							data.cBYTE[2] = *(BYTE*) (pObjAdsRes + 2);
							data.cBYTE[3] = *(BYTE*) (pObjAdsRes + 3);

							log_bff.Format("      %0X (%.5f) \n", data.uiDATA, data.fDATA);
							log_msg += log_bff;
						}
						else
						{
							DWORD data = *(DWORD*) pObjAdsRes;

							log_bff.Format("      %0X (???) \n", data);
							log_msg += log_bff;
						}
					}
					else if(len == 2)
					{
						if(ads_type.CompareNoCase("WORD") == 0)
						{
							WORD data = *(WORD*) pObjAdsRes;

							log_bff.Format("      %0X (%1d) \n", data, data);
							log_msg += log_bff;
						}
						else
						{
							WORD data = *(WORD*) pObjAdsRes;

							log_bff.Format("      %0X (???) \n", data);
							log_msg += log_bff;
						}
					}
					else if(len == 1)
					{
						BYTE data = *(BYTE*) pObjAdsRes;

						log_bff.Format("      %0X (%1d) \n", data, data);
						log_msg += log_bff;
					}
					else
					{
						log_bff.Format("      ??? \n");
						log_msg += log_bff;
					}

					log_bff = "\n";
					log_msg += log_bff;
				}
				else
				{
					log_bff.Format(" * Error  <- %1d \n", nAdsErr);
					log_msg += log_bff;
				}
			}
			else	
			{
				// Error

			}

			pObjAdsRes = pObjAdsRes + p_data_par[idx].length;
			pObjAdsErrRes = pObjAdsErrRes + 4;					// point to next ADS-err object
		}
	}

	if(active_print)
	{
		int k_limit = (4 * item_count) + memory_size;
		int k;

		log_msg += "===================================== \n";
		
		log_bff.Format(" * k_limit <- %1d \n", k_limit);
		log_msg += log_bff;

		for(k=0; k<k_limit; k++)
		{
			if(k > 0)
			{
				if(k % 10 == 0)			log_msg += "\n";
			}

			log_bff.Format("[%02X] ", 0x0ff & p_ads_buffer[k]);
			log_msg += log_bff;
		}

		log_msg += "\n";
		log_msg += "===================================== \n";

		printf(log_msg);
	}

	return 1;
}

int CMNG__ADS_CTRL::Update__ADS_SETTING(const bool active_print, const int active_sim)
{
	if(active_sim > 0)
	{

	}
	else
	{
		if(!bActive__ADS_DRIVER)		return -1;
	}

	// ...
	CDRV__ADS_INFO* p_ads_info = &mADS_OUT;
	AmsAddr* p_addr = mADS_CTRL.Get__AMS_ADDR();

	// ...
	int item_count  = p_ads_info->iADS__ITEM_COUNT;
	int memory_size = p_ads_info->iADS__MEMORYL_SIZE;

	// ...
	int size__ads_buffer = (12 * item_count) + memory_size;
	int max__ads_buffer  = size__ads_buffer + 1;

	unsigned char* p_ads_buffer = p_ads_info->pADS_BUFFER;
	unsigned char* p_ads_error  = p_ads_info->pADS_ERROR;

	// ...
	{
		UNION_4_BYTE__UINT x_data;

		memset(p_ads_buffer, 0, max__ads_buffer);

		//
		BYTE* p_ads_res = (BYTE*) p_ads_buffer;
		int idx;

		for(idx=0; idx<item_count; idx++)
		{
			TDataPar* p_data_par = &(p_ads_info->mADS__DATA_PAR[idx]);

			x_data.uiDATA = p_data_par->indexGroup;
			memcpy(p_ads_res, x_data.cBYTE, 4);
			p_ads_res += 4;

			x_data.uiDATA = p_data_par->indexOffset;
			memcpy(p_ads_res, x_data.cBYTE, 4);
			p_ads_res += 4;

			x_data.uiDATA = p_data_par->length;
			memcpy(p_ads_res, x_data.cBYTE, 4);
			p_ads_res += 4;
		}

		for(idx=0; idx<item_count; idx++)
		{
			CString ads_name = p_ads_info->sList__ADS_NAME[idx];
			int ads_index    = p_ads_info->iList__ADS_INDEX[idx];
			CString ads_type = p_ads_info->sList__ADS_TYPE[idx];

			//
			CString str_hexa;
			int data_size;

			mDB__ADS_CTRL.Get__ADS_OUT_HEXA(ads_index, str_hexa,data_size);

			CStringArray l_para;
			Macro__StringArrray_From_String(str_hexa, " ", l_para);

			if(active_print)
			{
				printf(" # ads_index(%1d) \n", ads_index);
			}

			l_para.SetSize(data_size);
				
			for(int k=0; k<data_size; k++)
			{
				str_hexa = l_para[k];
				*p_ads_res = 0x0ff & Macro__Hexa_From_String(str_hexa);				

				if(active_print)
				{
					printf("   * %1d) [%s] \n", k, str_hexa);
				}

				p_ads_res += 1;
			}
		}
	}

	if(active_sim > 0)
	{

	}
	else
	{
		long n_err;
		n_err = AdsSyncReadWriteReq(p_addr, 
									ADSIGRP_SUMUP_WRITE,				// 0xf081, 
									item_count, 
									4*item_count,						// we request additional "error"-flag(long) for each ADS-sub commands
									(void*) p_ads_error, 
									size__ads_buffer,					// send 12 bytes (3 * long : IG, IO, Len) of each ADS-sub command	
									p_ads_buffer);

		if(n_err != 0)
		{
			printf(" * AdsSyncReadWriteReq() - \n");
			printf(" * Error_Code <- %1d \n", n_err);
			printf(" * Error_Msg  <- %s \n", Macro__Get_TwinCAT_Error_Code(n_err));
		}
	}

	if(active_print)
	{
		CString log_msg;
		CString log_bff;

		int k_limit = size__ads_buffer;
		int k;

		log_msg += "===================================== \n";

		log_bff.Format(" * k_limit <- %1d \n", k_limit);
		log_msg += log_bff;

		log_bff.Format(" * item_count <- %1d \n", item_count);
		log_msg += log_bff;

		log_bff.Format(" * memory_size <- %1d \n", memory_size);
		log_msg += log_bff;

		log_msg += "\n";

		for(k=0; k<k_limit; k++)
		{
			if(k > 0)
			{
				if(k % 10 == 0)			log_msg += "\n";
			}

			log_bff.Format("[%02X] ", 0x0ff & p_ads_buffer[k]);
			log_msg += log_bff;
		}

		log_msg += "\n";
		log_msg += "===================================== \n";

		printf(log_msg);
	}

	return 1;
}
