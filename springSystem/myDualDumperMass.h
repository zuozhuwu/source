#pragma once

#include "stdafx.h"

class CmyDualDumperMass:public CmyMass
{
private:
	double damperReverse;	      //��v<0ʱ��ʹ�����damperֵ

public:
	CmyDualDumperMass();
	CmyDualDumperMass(double m, double vv = 0.0, double dam = 0.0, double dam2 = 0.0);
	~CmyDualDumperMass();

public:
	double getDumperForce();

};