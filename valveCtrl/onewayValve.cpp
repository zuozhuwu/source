#include "stdafx.h"

COnewayValve::COnewayValve() : CValve()
{
	;
}

COnewayValve::COnewayValve(string valveName) : CValve(valveName, 0x00, 0x12)
{
	;
}

COnewayValve::~COnewayValve()
{

}

void COnewayValve::valveCtrl()
{
	double pres1 = getPortPres(portType::intake);
	
	double pres2 = getPortPres(portType::outtake);

	if (pres1 > pres2)
	{
		setPos(1);
	}
	else
	{
		setPos(0);
	}
}

//ubyte COnewayValve::getPosCode()
//{
//	double pres1 = getPortPres(portType::intake);
//
//	double pres2 = getPortPres(portType::outtake);
//
//	if (pres1 > pres2)
//	{
//		return (ubyte)0x12;
//	}
//	else
//	{
//		return (ubyte)0x0;
//	}
//}