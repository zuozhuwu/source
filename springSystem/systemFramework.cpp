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

		if(vecSpring[i].index == s.index) return;     //˵���õ����Ѿ����ڣ����������

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

		if(vecMass[i].index == m.index) return;		 //�����Ѿ����ڣ����������

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

	connectSpring cS;				  //�������ӵĵ����Լ��˿�
	cS.spring = &s;
	cS.pt = portName;
	

	if (-1 == ret)                 //û���ҵ����ӵ�����m�ĵ���
	{
		massToSpring ms;		   //���嵯�����������ӵı���
		ms.mass = &m;
		
		SPRINGS sp;
		sp.push_back(cS);

		ms.springs = sp;

		connectedSprings.push_back(ms);	 //��ӵ������ܹ���

	}
	else								//֮ǰ�Ѿ��е������ӵ�����m
	{
		if (-1 == isSpringAdd(connectedSprings[ret].springs, s))  //�ж��Ƿ�õ���ʱ���Ѿ����ӵ�����m�ϣ������ظ����
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
		printf("������%d���ӵĵ����У�\n", connectedSprings[i].mass->index);

		for (int j = 0; j < (int)connectedSprings[i].springs.size(); ++j)
		{
			printf("����%d�˿�%d\n",connectedSprings[i].springs[j].spring->index, connectedSprings[i].springs[j].pt);
		}
		cout<<endl<<endl;
	}
}

