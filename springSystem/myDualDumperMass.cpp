#include "stdafx.h"

CmyDualDumperMass::CmyDualDumperMass()
{

}

CmyDualDumperMass::CmyDualDumperMass(double m, double vv, double dam, double dam2):CmyMass(m, vv, dam)
{
	damperReverse = dam2;
}

CmyDualDumperMass::~CmyDualDumperMass()
{

}

double CmyDualDumperMass::getDumperForce()
{
	if (v >= 0)
	{
		return -1 * v * damper;
	}
	else
		return -1 * v * damperReverse; 
}