#pragma once

#include "stdafx.h"
//7���ɶ�����ģ��


//�ĸ��ֵ�˳��Ϊ��BL, BR, FL, FR
//x��Ϊ����ǰ������
//y��Ϊ��ֱ����ǰ������ָ����ࣨ���ǰ������
//z��Ϊ��ֱ���棬ָ����շ���
//ԭ��Ϊ���ķ���
struct Pt_wheel          //�ĸ���̥λ��
{
	double x;
	double y;
};

class CsevenDOF
{

public:
	CsevenDOF();
	CsevenDOF(Csolution* s[4]);
	~CsevenDOF();

public:
	void startCalc();

	void calcA();
	void calcPhi();
	void calcTheta();

	void calcForce();
	void calcTyre(int index);      //������̥ϵͳ

	void setMass(double m);

	void setPos_BL(double x, double y);
	void setPos_BR(double x, double y);
	void setPos_FL(double x, double y);
	void setPos_FR(double x, double y);
	void setMTheta(double x, double y);

private:
	Csolution* m_solutions[4];
	Pt_wheel   m_Pt[4];

	double m_force[4];

	double m_a, m_phi, m_theta;              //m_aΪ��ֱ���򣬼�z����ļ��ٶ�
											 //m_phiΪ��x��ĽǼ��ٶȣ�������ҡ�ڵĽǼ��ٶ�
	                                         //m_thetaΪ��y��ĽǼ��ٶȣ���ǰ�󷭹��ĽǼ��ٶ�
	double x_mTheta;                   //��x���ת������
	double y_mTheta;                   //��y���ת������

	double m_mass;                     //��������
};
