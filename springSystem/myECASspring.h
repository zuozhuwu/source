#pragma once

#include "stdafx.h"

struct XKpair
{
	double X;
	double K;
};

class CmyECASspring : public CmySpring
{
public:
	CmyECASspring();
	~CmyECASspring();

	CmyECASspring(string kFileName, springPortType type0 = FREEPORT, springPortType type1 = FREEPORT);
	CmyECASspring(double freeLength, springPortType type0 = FREEPORT, springPortType type1 = FREEPORT);

private:
	vector<XKpair> xk;
	double m_freeLength;        //自由状态下的长度
	double m_freeLength_L;      //上一次自由状态下的长度
	double m_freeLength_LL;     //上上一次自由状态下的长度
	double m_Pres;              //气囊压力


public:
	void   setK(string kFileName);

	double getK();
	double getPres();
	double getFreeLenght();

	void setFreeLenght(double L);
	void setPres(double p);

private:
	void getXKFromFile(string fileName); 
};