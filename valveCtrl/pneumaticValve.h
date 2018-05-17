#pragma once
#include "stdafx.h"

class CPneumaticValve : public CValve
{
private:
	double m_presThres;         //control pressure threshold value

public:
	CPneumaticValve();

	CPneumaticValve(string valveName, ubyte pos0Code, ubyte pos1Code, double presCtrlThres);

	~CPneumaticValve();

	void valveCtrl();
};