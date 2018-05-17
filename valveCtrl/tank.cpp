#include "stdafx.h"

CTank::CTank() : CMyObject()
{
	m_pres = 0.0;
	m_volumn = 0.0;
}

CTank::CTank(double press, tankType type) :CMyObject()
{
	m_pres = press;
}

CTank::CTank(double press, double volumn, tankType type) : CMyObject()
{
	m_pres = press;
	m_volumn = volumn;
}

CTank::CTank(string name, double press, tankType type) :CMyObject(name)
{
	m_pres = press;
}

CTank::CTank(string name, double press, double volumn, tankType type) : CMyObject(name)
{
	m_pres = press;
	m_volumn = volumn;
}

void CTank::setPortPres(double pres, CValve::valvePort port)  //tank only has one port, but in order to compatible with valve type function, so .. 
{
	m_pres = pres;
}

double CTank::getPortPres(CValve::valvePort port)
{
	return m_pres;
}

string CTank::getTypeName()
{
	return "CTank";
}

void CTank::changePresByFlow(double massFlowRate, int timeStep)
{
	m_massFlowRate = massFlowRate;

	if (m_volumn != 0.0)   //not a const press tank
	{

		double massFlow = massFlowRate * (double)timeStep / 1000.0;

		double volumnFlow = massFlow / 1.29;              //the density of air is 1.29kg/m^3 at standard condition

		double deltV = volumnFlow * 1.01325e5 / m_pres;     //the volumn at m_pres

		double newPres = m_pres * (m_volumn - deltV) / m_volumn;    //pressure changes because of volumn changes

		m_pres = newPres;      //set the new pressure
	}
}

void CTank::saveData(int time)
{
	*ofile << time << "\t" << m_pres << "\t" << m_massFlowRate << endl;
}