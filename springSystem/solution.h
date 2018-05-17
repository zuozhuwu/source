#pragma once

#include "stdafx.h"

class Csolution
{
public:
	double endTime;
	double stepTime;

	vector<massToSpring> sysFrame;

public:
	Csolution();
	Csolution(vector<massToSpring> &framework, double sT);
	Csolution(vector<massToSpring> &framework, double sT, double eT);

	void setStepTime(double sT);
	void setEndTime(double eT);

	void startCalc(byte massIndex);

	void calc1Step(byte massIndex, int j);

	~Csolution();

public:
	double getForceOnMass(SPRINGS &springs);
	void   setDeltXOnSpring(SPRINGS &springs, double deltX, double t);
};