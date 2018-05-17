#pragma once
#include "stdafx.h"

//tanks always use intake port

class CTank :public CMyObject
{
private:
	double m_pres;
	double m_volumn;

	double m_massFlowRate;

public:
	enum tankType
	{
		constPress,
		constVolumn
	};

	CTank();

	CTank(double press, tankType type = tankType::constPress);

	CTank(double press, double volumn, tankType type = tankType::constVolumn);

	CTank(string name, double press, tankType type = tankType::constPress);

	CTank(string name, double press, double volumn, tankType type = tankType::constVolumn);

	void setPortPres(double pres, CValve::valvePort port = CValve::valvePort::intake);   //tank only has one port, but in order to compatible with valve type function, so .. 

	double getPortPres(CValve::valvePort port = CValve::valvePort::intake);

	void changePresByFlow(double massFlowRate, int timeStep);

	string getTypeName();

	void saveData(int time);

	~CTank(){};
};