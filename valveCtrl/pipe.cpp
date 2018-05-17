#include "stdafx.h"

CPipe::CPipe() : CMyObject()
{
	m_area = 1e-4;      //1cm^2    
	m_press = 0.0;
}

CPipe::CPipe(double area) : CMyObject()
{
	m_area = area;
	m_press = 0.0;
}

CPipe::CPipe(string pipeName, double area) : CMyObject(pipeName)
{
	m_area = area;          
	m_press = 0.0;
}

void CPipe::setPress(double pres)
{
	m_press = pres;
}

double CPipe::getPress()
{
	return m_press;
}

double CPipe::getArea()
{
	return m_area;
}