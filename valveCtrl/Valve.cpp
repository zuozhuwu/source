#include "stdafx.h"

CValve::CValve() :CMyObject()
{
	setInit();
}

CValve::CValve(string valveName) : CMyObject(valveName)
{
	setInit();
}

CValve::CValve(string valveName, ubyte pos0Code, ubyte pos1Code) : CMyObject(valveName)
{
	setInit();

	m_pos0Code = pos0Code;
	m_pos1Code = pos1Code;
}

CValve::CValve(string valveName, ubyte pos0Code, ubyte pos1Code, double coeff) : CMyObject(valveName)
{
	setInit();

	m_pos0Code = pos0Code;
	m_pos1Code = pos1Code;
	m_flowRateCoeff = coeff;
}

void CValve::setInit()
{
	m_pos = 0;
	m_pos0Code = 0;
	m_pos1Code = 0;

	m_portArea[valvePort::intake]  = \
	m_portArea[valvePort::outtake] = \
	m_portArea[valvePort::exhaust] = 1e-4;

	m_flowRateCoeff = 0.000235;
}

ubyte CValve::getPosCode()
{
	if (0 == m_pos)
	{
		return m_pos0Code;
	}
	else if(1 == m_pos)
	{
		return m_pos1Code;
	}
	else
	{
		return m_pos0Code;
	}
}

void CValve::setPos(ubyte pos)
{
	m_pos = pos;
}

void CValve::setFlowRateCoeff(double coeff)
{
	m_flowRateCoeff = coeff;
}

double CValve::getFlowRateCoeff()
{
	return m_flowRateCoeff;
}

void CValve::setPortArea(double area1, double area2, double area3)
{
	m_portArea[valvePort::controlPort] = 0;
	m_portArea[valvePort::intake] = area1;
	m_portArea[valvePort::outtake] = area2;
	m_portArea[valvePort::exhaust] = area3;
}

void CValve::setPortPres(double pres, valvePort port)
{
	m_portSignal[port] = pres;
}

double CValve::getPortPres(valvePort port)
{
	return m_portSignal[port];
}

string CValve::getTypeName()
{
	return "CValve";
}

void CValve::saveData(int time)
{
	*ofile << time                 \
		<< "\t" << m_portSignal[0] \
		<< "\t" << m_portSignal[1] \
		<< "\t" << m_portSignal[2] \
		<< "\t" << m_portSignal[3] \
		<< endl;
}

void CValve::valveCtrl()
{
	;
}
