#pragma once

#include "stdafx.h"	

struct connectSpring	   //�����������ĵ��ɵ�����
{
	CmySpring *spring;	   //���ӵĵ���
	springPort pt;		   //��Port0�ڻ���Port1������������
};

typedef vector<connectSpring> SPRINGS ;


struct massToSpring
{
	CmyMass *mass;
	SPRINGS springs;
};


class CsystemFramework
{

private:
	vector<CmySpring> vecSpring;
	vector<CmyMass>   vecMass;

public:
	vector<massToSpring> connectedSprings;  //�������������������е���

protected:
	int isMassAdded(CmyMass &m);
	int isSpringAdd(SPRINGS &ss, CmySpring &s);

public:

	void addSpring(CmySpring &s);
	void addMass(CmyMass  &m);

	void showFramwork();	     //��ӡ����ϵͳ�ܹ�

	void connectSpingToMass(CmyMass &m, CmySpring &s, springPort portName);

	

public:
	CsystemFramework();
	~CsystemFramework(); 

};