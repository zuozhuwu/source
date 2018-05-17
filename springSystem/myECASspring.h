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
	double m_freeLength;        //����״̬�µĳ���
	double m_freeLength_L;      //��һ������״̬�µĳ���
	double m_freeLength_LL;     //����һ������״̬�µĳ���
	double m_Pres;              //����ѹ��


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