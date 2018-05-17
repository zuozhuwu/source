#pragma once

#include "stdafx.h"	

struct connectSpring	   //与质量相连的弹簧的声明
{
	CmySpring *spring;	   //连接的弹簧
	springPort pt;		   //是Port0口还是Port1口与质量相连
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
	vector<massToSpring> connectedSprings;  //描述与质量相连的所有弹簧

protected:
	int isMassAdded(CmyMass &m);
	int isSpringAdd(SPRINGS &ss, CmySpring &s);

public:

	void addSpring(CmySpring &s);
	void addMass(CmyMass  &m);

	void showFramwork();	     //打印整个系统架构

	void connectSpingToMass(CmyMass &m, CmySpring &s, springPort portName);

	

public:
	CsystemFramework();
	~CsystemFramework(); 

};