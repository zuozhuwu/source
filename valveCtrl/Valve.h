#pragma once
#include "stdafx.h"

typedef unsigned char ubyte;

class CValve :public CMyObject
{
public:
	enum valvePort         //the valve port contains 3 port, you can increase the port below as you need to
	{
		controlPort = 0,
		intake,
		outtake,
		exhaust
	};

	double m_portSignal[4];    //4 ports signal
	double m_portArea[4];

private:
	ubyte m_pos;            //the valve pos, pos = 0 is the default pos

	ubyte m_pos0Code;       //pos0 code, eg: 0xEF, E means the intake side port, in a two way valve, E always 1 (represent intake port, refer to the valvePort)
	ubyte m_pos1Code;

	double m_flowRateCoeff;   //the mass flow rate is calculated by 0.0135 * deltP * S, refer to my IFAC paper

public:
	CValve();

	CValve(string valveName);

	CValve(string valveName, ubyte pos0Code, ubyte pos1Code);

	CValve(string valveName, ubyte pos0Code, ubyte pos1Code, double coeff);

	void saveData(int time);

	void setPortArea(double area1, double area2, double area3 = 0.0);

	void setPortPres(double pres, valvePort port);

	double getPortPres(valvePort port);	

	ubyte getPosCode();

	void setFlowRateCoeff(double coeff);

	double getFlowRateCoeff();

	string getTypeName();

	~CValve(){};

	virtual void valveCtrl();

private:

	void setInit();

protected:

	void setPos(ubyte pos);
};

typedef CValve::valvePort portType;
