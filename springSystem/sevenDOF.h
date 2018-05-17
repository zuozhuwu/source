#pragma once

#include "stdafx.h"
//7自由度整车模型


//四个轮的顺序为：BL, BR, FL, FR
//x轴为车子前进方向
//y轴为垂直车子前进方向，指向左侧（面对前进方向）
//z轴为垂直地面，指向天空方向，
//原点为重心方向
struct Pt_wheel          //四个轮胎位置
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
	void calcTyre(int index);      //计算轮胎系统

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

	double m_a, m_phi, m_theta;              //m_a为竖直方向，即z方向的加速度
											 //m_phi为沿x轴的角加速度，即左右摇摆的角加速度
	                                         //m_theta为沿y轴的角加速度，即前后翻滚的角加速度
	double x_mTheta;                   //沿x轴的转动惯量
	double y_mTheta;                   //沿y轴的转动惯量

	double m_mass;                     //整车质量
};
