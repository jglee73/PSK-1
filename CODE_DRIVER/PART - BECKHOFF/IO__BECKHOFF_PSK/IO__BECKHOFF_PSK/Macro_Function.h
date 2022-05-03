#pragma once


extern int Macro__StringArrray_From_String(const CString& str_org_data,const CString& str_sep,CStringArray& l_data);
extern int Macro__Hexa_From_String(const CString& str_data);


extern CString Macro__Get_TwinCAT_Error_Code(const int err_code);
extern CString _Macro__Get_Global_Error_Code(const int err_code);
extern CString _Macro__Get_ADS_Error_Code(const int err_code);

