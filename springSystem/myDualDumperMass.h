#pragma once

#include "stdafx.h"

class CmyDualDumperMass:public CmyMass
{
private:
	double damperReverse;	      //当v<0时，使用这个damper值

public:
	CmyDualDumperMass();
	CmyDualDumperMass(double m, double vv = 0.0, double dam = 0.0, double dam2 = 0.0);
	~CmyDualDumperMass();

public:
	double getDumperForce();

};