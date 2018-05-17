#include "stdafx.h"

int CmyMass::massIndex = 0;		  //类的静态成员，需类外初始化
bool CmyMass::saveToFile = true;   //是否保存数据到文件，默认为保存

CmyMass::CmyMass()
{
	mass = 0.0;
	damper = 0.0;
	v = 0.0;
	a = 0.0;

	index = massIndex;
	massIndex ++;

	openFileForSave(); 
	
} 

CmyMass::CmyMass(double m, double vv, double dam)
{
	mass = m;
	damper = dam;
	v = vv;
	a = 0.0;

	index = massIndex;
	massIndex ++;

	openFileForSave();		
}

CmyMass::~CmyMass()
{
	if (!(*ofile))
	{
		ofile->close();
	}

}
void CmyMass::setMass(double m)
{
	mass = m;
}

void CmyMass::setDamper(double dam)
{
	damper = dam;
}

void CmyMass::setV(double vv)
{
	v = vv;

	*ofile <<v<<endl;
}

void CmyMass::setA(double aa)
{
	a = aa;
}

double CmyMass::getMass()
{
	return mass;
}

double CmyMass::getV()
{
	return v;
}

double CmyMass::getA()
{
	return a;
}

double CmyMass::getDumperForce()
{
	return -1 * v * damper;
}

void CmyMass::openFileForSave()
{
	if (saveToFile)
	{
		char fileName[32];

		sprintf_s(fileName, "./saveData/m%d_v.txt", index);

		string oFileName(fileName);

		ofile = new ofstream(oFileName.c_str(),ofstream::out); 
		
	} 
}