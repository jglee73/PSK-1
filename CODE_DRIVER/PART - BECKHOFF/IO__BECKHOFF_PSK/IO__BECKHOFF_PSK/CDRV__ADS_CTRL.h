#pragma once

#include "CDB__ADS_CTRL.h"


typedef struct dataPar
{
	unsigned long  indexGroup;		// index group in ADS server interface
	unsigned long  indexOffset;	// index offset in ADS server interface
	unsigned long  length;			// count of bytes to read
} 
TDataPar;

class CDRV__ADS_INFO
{
public:
	TDataPar mADS__DATA_PAR[4096];
	unsigned char* pADS_BUFFER;

	CStringArray sList__ADS_NAME;
	CUIntArray   iList__ADS_INDEX;
	CStringArray sList__ADS_TYPE;

	long iADS__MEMORYL_SIZE;
	long iADS__ITEM_COUNT;

public:
	CDRV__ADS_INFO()
	{
		pADS_BUFFER = NULL;
	}
};

class CDRV__ADS_CTRL
{
private:
	bool bActive__ADS_DRIVER;

	CDRV__ADS_INFO mADS_IN;
	CDRV__ADS_INFO mADS_OUT;

public:
	CDRV__ADS_CTRL();
	~CDRV__ADS_CTRL();

	// ...
	int Init__ADS_DRIVER(const int active_sim);

	CString Get__ADS_IN_INFO(const bool active_print);
	int Link__ADS_OUT_INFO(const bool active_print);

	int Init__ADS_INFO(CDRV__ADS_INFO* p_ads_drv,CDB__ADS_INFO* p_ads_db, const int active_sim);

	// ...
	int Update__ADS_READING(const bool active_print, const int active_sim);
	int Update__ADS_SETTING(const bool active_print, const int active_sim);
};
