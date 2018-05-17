#include "stdafx.h"

Csolution::Csolution()
{
	stepTime = 0.0;
	endTime = 0.0;
	sysFrame.clear();
}

Csolution::Csolution(vector<massToSpring> &framework, double sT)
{
	sysFrame = framework;
	stepTime = sT;
}

Csolution::Csolution(vector<massToSpring> &framework, double sT, double eT)
{
	sysFrame = framework;
	stepTime = sT;
	endTime = eT;
}

void Csolution::setStepTime(double sT)
{
	stepTime = sT;
}

void Csolution::setEndTime(double eT)
{
	endTime = eT;
}

void Csolution::startCalc(byte massIndex)
{
	for (int j = 0; j < endTime/stepTime; ++j)
	{	
		calc1Step(massIndex, j);
	}
}

void Csolution::calc1Step(byte massIndex, int j)
{
	CmyMass* M = sysFrame[massIndex].mass;

	double f = getForceOnMass(sysFrame[massIndex].springs) + M->getDumperForce();	   //���㵯������������֮��

	double a = f / M->getMass();

	double v_n = M->getV() + a * stepTime; 	  //��һʱ���ٶ� 

	double v_p = (M->getV() + v_n) / 2;      //ȡ��ǰʱ�̺���һʱ���ٶȵ�ƽ��ֵ

	double diffA = (a - M->getA()) / stepTime;	  //���ٶ�a�ĵ���

	double deltX = v_p * stepTime + a * pow(stepTime, 2) / 2.0 + diffA * pow(stepTime, 3) / 6.0;	  //����̩��չ��ʽ��

	setDeltXOnSpring(sysFrame[massIndex].springs, deltX, (double)j * stepTime);    //�������е��ɵĶ˿ڱ仯

	M->setV(v_n);                                    //��������ģ��M���ٶ�

	M->setA(a);
}

Csolution::~Csolution()
{
	sysFrame.clear();
}

double Csolution::getForceOnMass(SPRINGS &springs)
{
	double force = 0.0;

	for (int i = 0; i < (int)springs.size(); ++i)
	{
		if (springs[i].pt == PORT0)
		{
			force += springs[i].spring->getForce0();
		}
		else 
		{
			force += springs[i].spring->getForce1();
		}
	}

	return force;
}

void  Csolution::setDeltXOnSpring(SPRINGS &springs, double deltX, double t)
{
	for (int i = 0; i < (int)springs.size(); ++i)
	{
		CmySpring *s = springs[i].spring;

		if (springs[i].pt == PORT0)
		{
			s->SetX0(s->getX0() + deltX);
			
			if (s->port1Type == INPUTPORT)
			{
				s->SetX1(s->getXbyT(t));
			}
		}
		else 
		{
			s->SetX1(s->getX1() + deltX);

			if (s->port0Type == INPUTPORT)
			{
				s->SetX0(s->getXbyT(t));
			}
		}
	}
}