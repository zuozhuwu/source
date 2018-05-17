#pragma once
#include "stdafx.h"

class COnewayValve : public CValve
{
public:
	COnewayValve();

	COnewayValve(string valveName);

	void valveCtrl();

	~COnewayValve();
};