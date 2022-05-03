#pragma once

#include "CDB__ADS_CTRL.h"


typedef struct dataPar
{
	unsigned long  indexGroup;		// index group in ADS server interface
	unsigned long  indexOffset;		// index offset in ADS server interface
	unsigned long  length;			// count of bytes to read
} 
TDataPar;

class CDRV__ADS_INFO
{
public:
	TDataPar mADS__DATA_PAR[4096];

	unsigned char* pADS_BUFFER;
	unsigned char* pADS_ERROR;

	CStringArray sList__ADS_NAME;
	CUIntArray   iList__ADS_INDEX;
	CStringArray sList__ADS_TYPE;

	long iADS__MEMORYL_SIZE;
	long iADS__ITEM_COUNT;

public:
	CDRV__ADS_INFO()
	{
		pADS_BUFFER = NULL;
		pADS_ERROR  = NULL;
	}

	CString Get__ADS_INFO()
	{
		CString log_msg;
		CString log_bff;

		log_msg  = "\n";
		log_msg += " CDRV__ADS_INFO::Get__ADS_INFO() ... \n";

		log_bff.Format("   MEMORY_SIZE <- %1d \n", iADS__MEMORYL_SIZE);
		log_msg += log_bff;
		log_bff.Format("   ADS__ITEM_COUNT <- %1d \n", iADS__ITEM_COUNT);
		log_msg += log_bff;

		int i_limit = sList__ADS_NAME.GetSize();
		for(int i=0; i<i_limit; i++)
		{
			TDataPar* p_par = &(mADS__DATA_PAR[i]);

			log_bff.Format("   %02d)  [%s] [%1d] [%s] - (%1d, %1d, %1d) \n",
				            i+1,
							sList__ADS_NAME[i],
							iList__ADS_INDEX[i],
							sList__ADS_TYPE[i],
							p_par->indexGroup,
							p_par->indexOffset,
							p_par->length);
			log_msg += log_bff;
		}

		return log_msg;
	}
};

class CMNG__ADS_CTRL
{
private:
	bool bActive__ADS_DRIVER;

	CDRV__ADS_INFO mADS_IN;
	CDRV__ADS_INFO mADS_OUT;

public:
	CMNG__ADS_CTRL();
	~CMNG__ADS_CTRL();

	// ...
	int Init__ADS_LINK(const int active_sim);

	CString Get__ADS_TOTAL_INFO(const bool active_print);
	CString Get__ADS_IN_INFO();
	CString Get__ADS_OUT_INFO();

	int Link__ADS_IN_INFO(const bool active_print);
	int Link__ADS_OUT_INFO(const bool active_print);

	int Init__ADS_INFO(const bool active__ads_out, CDRV__ADS_INFO* p_ads_drv,CDB__ADS_INFO* p_ads_db, const int active_sim);

	// ...
	int Update__ADS_READING(const bool active_print, const int active_sim);
	int Update__ADS_SETTING(const bool active_print, const int active_sim);
};
