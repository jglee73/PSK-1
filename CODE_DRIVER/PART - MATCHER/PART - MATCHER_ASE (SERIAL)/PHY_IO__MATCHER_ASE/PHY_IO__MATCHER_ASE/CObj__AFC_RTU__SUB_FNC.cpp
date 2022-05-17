#include "StdAfx.h"
#include "CObj__AFC_RTU.h"
#include "CObj__AFC_RTU__DEF.h"
#include "CObj__AFC_RTU.h"


//------------------------------------------------------------------------------------
CString CObj__AFC_RTU::_Get__Error_Code(const int err_code)
{
	CString err_msg;

	if(err_code == 0x00)
	{
		err_msg = "Normal completion";
	}
	else if(err_code == 0x01)
	{
		err_msg  = "ILLEGAL FUNCTION";
		err_msg += "\n";

		err_msg += "The function code received in the query is not an allowable action for the server (or slave).";
		err_msg += "\n";
		err_msg += "may be because the function code is only applicable to newer devices, ";
		err_msg += "\n";
		err_msg += "was not implemented in the unit selected. ";
		err_msg += "\n";
		err_msg += "It could also indicate that the server (o r slave) is in the wrong state ";
		err_msg += "\n";
		err_msg += "to process a request of this type, for example because it is unconfigured ";	
		err_msg += "\n";
		err_msg += "is being asked to return register values.";
	}	
	else if(err_code == 0x02)
	{
		err_msg  = "ILLEGAL DATA ADDRESS";
		err_msg += "\n";

		err_msg += "The data address received in the query is not an allowable address for the serve r (or slave). ";
		err_msg += "\n";
		err_msg += "More specifically, the combination of reference number and transfer length is invalid. ";
		err_msg += "\n";
		err_msg += "For a controller with 100 registers, the PDU addresses the first register as 0, and the last one as 99.";
		err_msg += "\n";
		err_msg += "If a request is submitted with a starting register address of 96 ";
		err_msg += "\n";
		err_msg += "and a quantity of registers of 4, then this request will successfully operate ";
		err_msg += "\n";
		err_msg += "(address wise at least) on registers 96, 97, 98, 99. ";
		err_msg += "\n";
		err_msg += "If a request is submitted with a starting register address of 96 and a quantity of registers of 5,";
		err_msg += "\n";
		err_msg += "then this re quest will fail with Exception Code 0x02";
		err_msg += "\n";
		err_msg += "\"Illegal Data Address\¡± since it attempts to operate on registers 96, 97, 98, 99 and 100,";
		err_msg += "\n";
		err_msg += "and there is no register with address 100.";
	}
	else if(err_code == 0x03)
	{
		err_msg  = "ILLEGAL DATA VALUE";
		err_msg += "\n";

		err_msg += "A value contained in the query data field is not an allowable value for server (or slave). ";
		err_msg += "\n";
		err_msg += "This indicates a fault in the structure of the remainder of a complex request,";
		err_msg += "\n";
		err_msg += "such as that the implied length is incorrect.";
		err_msg += "\n";
		err_msg += "It specifically does NOT mean that a data item submitted for storage in a register has a value ";
		err_msg += "\n";
		err_msg += "outside the expectation of the application program,";
		err_msg += "\n";
		err_msg += "since the MODBUS protocol is unaware of the significance of any particular value of any particular register.";
	}
	else if(err_code == 0x04)
	{
		err_msg  = "SLAVE DEVICE FAILURE";
		err_msg += "\n";
	
		err_msg += "An unrecoverable error occurred while the server (or slave) was attempting to perform the requested action.";
	}
	else 
	{
		err_msg.Format("Unknown Error (0x%02X)", err_code);
	}

	return err_msg;
}

