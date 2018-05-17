#include "stdafx.h"

CsevenDOF::CsevenDOF()
{

}

CsevenDOF::CsevenDOF(Csolution* s[4])
{
	for (ubyte i = 0; i < 4; i++)
	{
		m_solutions[i] = s[i];
	}
}

CsevenDOF::~CsevenDOF()
{

}

void CsevenDOF::startCalc()
{
	double endTime = m_solutions[0]->endTime;
	double stepTime = m_solutions[0]->stepTime;
	
	for (int j = 0; j < endTime / stepTime; ++j)    //�ĸ����ӱ���ͬһ�������;���
	{
		//calcTyre(j);    //���㳵��
		calcForce();
		calcA();
		calcPhi();
		calcTheta();
		
		for (ubyte i = 0; i < 4; i++)    //_T ��ʾtyre��_L ��ʾload
		{
			double a_L = m_a + m_phi * m_Pt[i].y + m_theta * m_Pt[i].x;

			CmyMass* M_L = m_solutions[i]->sysFrame[1].mass;

			double v_n_L = M_L->getV() + a_L * stepTime; 	  //��һʱ���ٶ� 

			double v_p_L = (M_L->getV() + v_n_L) / 2;      //ȡ��ǰʱ�̺���һʱ���ٶȵ�ƽ��ֵ

			double diffA_L = (a_L - M_L->getA()) / stepTime;	  //���ٶ�a�ĵ���

			double deltX_L = v_p_L * stepTime + a_L * pow(stepTime, 2) / 2.0 + diffA_L * pow(stepTime, 3) / 6.0;	  //����̩��չ��ʽ��


			/////////////////////////////////////////////////////////��̥����
			CmyMass* M_T = m_solutions[i]->sysFrame[0].mass;

			double f_T = m_solutions[i]->getForceOnMass(m_solutions[i]->sysFrame[0].springs) + M_T->getDumperForce();	   //���㵯������������֮��

			double a_T = f_T / M_T->getMass();

			double v_n_T = M_T->getV() + a_T * stepTime; 	  //��һʱ���ٶ� 

			double v_p_T = (M_T->getV() + v_n_T) / 2;      //ȡ��ǰʱ�̺���һʱ���ٶȵ�ƽ��ֵ

			double diffA_T = (a_T - M_T->getA()) / stepTime;	  //���ٶ�a�ĵ���

			double deltX_T = v_p_T * stepTime + a_T * pow(stepTime, 2) / 2.0 + diffA_T * pow(stepTime, 3) / 6.0;	  //����̩��չ��ʽ��


			///////////////////////////////////////////////////////////���³���
			m_solutions[i]->setDeltXOnSpring(m_solutions[i]->sysFrame[1].springs, deltX_L, (double)j * stepTime);    //�������е��ɵĶ˿ڱ仯

			M_L->setV(v_n_L);                                    //��������ģ��M���ٶ�

			M_L->setA(a_L);

			m_solutions[i]->setDeltXOnSpring(m_solutions[i]->sysFrame[0].springs, deltX_T, (double)j * stepTime);    //�������е��ɵĶ˿ڱ仯

			M_T->setV(v_n_T);                                    //��������ģ��M���ٶ�

			M_T->setA(a_T);
		}
	}
}

void CsevenDOF::calcTyre(int index)
{
	for (ubyte i = 0; i < 4; i++)
	{
		m_solutions[i]->calc1Step(0, index);     //0������̥
	}
}

void CsevenDOF::calcForce()
{
	for (ubyte i = 0; i < 4; i++)
	{
		CmyMass* M = m_solutions[i]->sysFrame[1].mass;

		m_force[i] = m_solutions[i]->getForceOnMass(m_solutions[i]->sysFrame[1].springs) + M->getDumperForce();

		if (Abs(m_force[i]) > 1.2e5)
		{
			int index = 0;
		}

	}
}

void CsevenDOF::calcA()
{
	double totalF = 0.0;

	for (ubyte i = 0; i < 4; i++)
	{
		totalF += m_force[i];
	}
	m_a = totalF / m_mass;
}

void CsevenDOF::calcPhi()
{
	double totalTor = 0.0;

	for (ubyte i = 0; i < 4; i++)
	{
		totalTor += m_force[i] * m_Pt[i].y;
	}

	m_phi = totalTor / x_mTheta;
}

void CsevenDOF::calcTheta()
{
	double totalTor = 0.0;

	for (ubyte i = 0; i < 4; i++)
	{
		totalTor += m_force[i] * m_Pt[i].x;
	}

	m_theta = totalTor / y_mTheta;
}

void CsevenDOF::setMass(double m)
{
	m_mass = m;
}

void CsevenDOF::setMTheta(double x, double y)
{
	x_mTheta = x;
	y_mTheta = y;
}

void CsevenDOF::setPos_BL(double x, double y)
{
	m_Pt[BL].x = x;
	m_Pt[BL].y = y;
}

void CsevenDOF::setPos_BR(double x, double y)
{
	m_Pt[BR].x = x;
	m_Pt[BR].y = y;
}

void CsevenDOF::setPos_FL(double x, double y)
{
	m_Pt[FL].x = x;
	m_Pt[FL].y = y;
}

void CsevenDOF::setPos_FR(double x, double y)
{
	m_Pt[FR].x = x;
	m_Pt[FR].y = y;
}