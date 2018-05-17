#pragma once
#include "stdafx.h"

class CSolenoidValve : public CValve
{

public:
	CSolenoidValve();

	CSolenoidValve(string valveName, ubyte pos0Code, ubyte pos1Code);

	~CSolenoidValve();

	void valveCtrl();
};