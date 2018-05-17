#include "stdafx.h"

CPneumaticValve::CPneumaticValve() :CValve()
{
	
	m_presThres = 0.0;         //control pressure threshold value

}

CPneumaticValve::CPneumaticValve(string valveName, ubyte pos0Code, ubyte pos1Code, double presCtrlThres) : CValve(valveName, pos0Code, pos1Code)
{

	m_presThres = presCtrlThres;         //control pressure threshold value

}

CPneumaticValve::~CPneumaticValve()
{

}

void CPneumaticValve::valveCtrl()
{
	if (getPortPres(CValve::valvePort::controlPort) > m_presThres)
	{
		setPos(1);
	}
	else
	{
		setPos(0);      //set to default pos
	}
}