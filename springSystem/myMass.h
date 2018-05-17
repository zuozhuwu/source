#pragma once

class CmyMass
{
protected:
	double mass;
	double damper;
	double v;
	double a; 

public:
	int index;
	static int massIndex;
	static bool saveToFile;	

public:
	CmyMass();
	CmyMass(double m, double vv = 0.0, double dam = 0.0);
	~CmyMass();

	void setMass(double m);
	void setDamper(double dam);
	void setV(double vv);
	void setA(double aa);

	double getMass();
	double getV();
	double getA();
	virtual double getDumperForce();

protected:
	ofstream *ofile;

	void openFileForSave();

};