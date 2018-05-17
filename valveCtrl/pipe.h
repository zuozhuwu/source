#pragma once
#include "stdafx.h"

class CPipe :public CMyObject
{
private:
	double m_area;      //Sectional area
	double m_press;     //pressure in pipe

public:
	CPipe();
	CPipe(double area);
	CPipe(string pipeName, double area);

	void setPress(double pres);
	double getPress();

	double getArea();

	~CPipe(){};

};