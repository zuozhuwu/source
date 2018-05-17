#include "stdafx.h"

CsystemFramework::CsystemFramework()
{

}

CsystemFramework::~CsystemFramework()
{

}

void CsystemFramework::addSpring(CmySpring &s)
{
	
	int insertIndex = 0; 

	for(int i = 0; i < (int)vecSpring.size(); ++i)
	{

		if(vecSpring[i].index == s.index) return;     //说明该弹簧已经存在，不能再添加

		if (i <= s.index)
		{
			insertIndex = i;
		}
	}

	vecSpring.insert(vecSpring.begin() + insertIndex,1, s);
}

void CsystemFramework::addMass(CmyMass &m)
{
	int insertIndex = 0; 

	for(int i = 0; i < (int)vecMass.size(); ++i)
	{ 

		if(vecMass[i].index == m.index) return;		 //质量已经存在，不能再添加

		if (i <= m.index)
		{
			insertIndex = i;
		}
	}

	vecMass.insert(vecMass.begin() + insertIndex,1, m);

}

void CsystemFramework::connectSpingToMass(CmyMass &m, CmySpring &s, springPort portName)
{
	int ret = isMassAdded(m);

	connectSpring cS;				  //定义连接的弹簧以及端口
	cS.spring = &s;
	cS.pt = portName;
	

	if (-1 == ret)                 //没有找到连接到质量m的弹簧
	{
		massToSpring ms;		   //定义弹簧与质量连接的变量
		ms.mass = &m;
		
		SPRINGS sp;
		sp.push_back(cS);

		ms.springs = sp;

		connectedSprings.push_back(ms);	 //添加到整个架构中

	}
	else								//之前已经有弹簧连接到质量m
	{
		if (-1 == isSpringAdd(connectedSprings[ret].springs, s))  //判断是否该弹簧时候已经连接到质量m上，避免重复添加
		{
			connectedSprings[ret].springs.push_back(cS);
		} 		
	}
}

int CsystemFramework::isMassAdded(CmyMass &m)
{
	int ret = -1;
	for (int i = 0; i <(int) connectedSprings.size(); ++i)
	{
		if(m.index == connectedSprings[i].mass->index)
		{
			ret = i;
			break;
		}
	}

	return ret;
}

int CsystemFramework::isSpringAdd(SPRINGS &ss, CmySpring &s)
{
	int ret = -1;

	for (int i = 0; i <(int) ss.size(); ++i)
	{
		if(s.index == ss[i].spring->index)
		{
			ret = i;
			break;
		}
	}

	return ret;	
}

void CsystemFramework::showFramwork()
{
	for (int i = 0; i < (int)connectedSprings.size(); ++i)
	{
		printf("与质量%d连接的弹簧有：\n", connectedSprings[i].mass->index);

		for (int j = 0; j < (int)connectedSprings[i].springs.size(); ++j)
		{
			printf("弹簧%d端口%d\n",connectedSprings[i].springs[j].spring->index, connectedSprings[i].springs[j].pt);
		}
		cout<<endl<<endl;
	}
}

