#include "StdAfx.h"
#include "CObj__DB_INF.h"


#define STR__UNKNOWN				"UNKNOWN"
#define STR__VAC					"VAC"
#define STR__ATM					"ATM"

#define STR__ON						"ON"
#define STR__OFF					"OFF"


// ...
void CObj__DB_INF
::Mon__UPDATE_INFO(CII_OBJECT__VARIABLE *p_variable)
{
	CString cur_data;
	CString pre_data;

	// ...
	{
		sCH__CHM_PRESSURE_STATUS->Set__DATA(STR__UNKNOWN);
	}

	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.1);

		// ...
		{
			xCH__RECIPE->Get__DATA(cur_data);
		
			if(cur_data != pre_data)
			{
				cur_data.Delete(0, cur_data.Find("\\")+1);
				pre_data = cur_data;

				xCH__RECIPE_WITHOUT_FOLDER_NAME->Set__DATA(cur_data);
			}
		}

		// ...
		{
			CString str__vac_sns = xCH__CHM_VAC_SNS->Get__STRING();
			CString str__atm_sns = xCH__CHM_ATM_SNS->Get__STRING();

			if(str__vac_sns.CompareNoCase(STR__ON) == 0)
			{
				if(str__atm_sns.CompareNoCase(STR__OFF) == 0)
				{
					sCH__CHM_PRESSURE_STATUS->Set__DATA(STR__VAC);
				}
				else
				{
					sCH__CHM_PRESSURE_STATUS->Set__DATA(STR__UNKNOWN);
				}
			}
			else
			{
				if(str__atm_sns.CompareNoCase(STR__ON) == 0)
				{
					sCH__CHM_PRESSURE_STATUS->Set__DATA(STR__VAC);
				}
				else
				{
					sCH__CHM_PRESSURE_STATUS->Set__DATA(STR__UNKNOWN);
				}
			}
		}

		// ...
	}
}

