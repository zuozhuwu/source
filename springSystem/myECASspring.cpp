#include "stdafx.h"

CmyECASspring::CmyECASspring()
{
	m_freeLength = 0.0;
	m_freeLength_L = 0.0;      //上一次自由状态下的长度
	m_freeLength_LL = 0.0;     //上上一次自由状态下的长度
	m_Pres = 0.0;
}

CmyECASspring::CmyECASspring(string kFileName, springPortType type0, springPortType type1):CmySpring(0, type0, type1)
{
	getXKFromFile(kFileName);
}

CmyECASspring::CmyECASspring(double freeLength, springPortType type0, springPortType type1) : CmySpring(0, type0, type1)
{
	m_freeLength = freeLength;
}

CmyECASspring::~CmyECASspring()
{

}

void CmyECASspring::setK(string kFileName)
{
	getXKFromFile(kFileName);
}

double CmyECASspring::getK()
{
	if (0 == xk.size())
	{
		cout<<"xk 数据为空，getK()函数失败"<<endl;
		return 0;
	}

	double X = fabs(X1 - X0) + m_freeLength;

	if (X <= xk[0].X)
	{
		return xk[0].K;
	}
	else if (X >= xk[xk.size() - 1].X )
	{
		return xk[xk.size() - 1].K;
	}
	else
	{
		double ret = 0;
		for (int i = 0; i < (int)xk.size() - 1; ++i)
		{
			double x0 = xk[i].X;
			double x1 = xk[i + 1].X;
			if (X >= x0 && X < x1)
			{
				ret = xk[i].K + (xk[i + 1].K - xk[i].K)*(X - x0)/(x1 - x0);		   //线性插值
				break;
			}
		}

		return ret;
	}
}

void CmyECASspring::getXKFromFile(string fileName)
{
	ifstream ifile(fileName, ios::in);

	if (!ifile)
	{
		cout<<"不能打开文件："<<fileName<<endl;
		return;
	}

	xk.clear();

	string str;

	string pattern = " ;,\t";

	vector<string> ret;

	XKpair pairTemp;

	while(getline(ifile,str))
	{
		ret = split(str, pattern);

		if (ret.size() != 2)
		{
			cout<<"XK文件格式出错！"<<endl;
			return;
		}

		pairTemp.X = atof(ret[0].c_str());
		pairTemp.K = atof(ret[1].c_str());

		xk.push_back(pairTemp);
	}

	ifile.close();
}

void CmyECASspring::setFreeLenght(double L)
{
	m_freeLength = L;

#ifdef USING_NEWMODEL

	if (m_freeLength != 0.0 && m_freeLenght_L != 0.0 && m_freeLenght_LL != 0.0)
	{
		SetX0(0.9 * (getX0() + m_freeLength_LL + m_freeLength - 2 * m_freeLength_L));            //设置X1端口为自由长度变化的二阶导数
	}

	m_freeLength_LL = m_freeLength_L;

	m_freeLength_L = m_freeLength;

#endif
}

void CmyECASspring::setPres(double p)
{
	m_Pres = p;
}

double CmyECASspring::getPres()
{
	return m_Pres;
}

double CmyECASspring::getFreeLenght()
{
	return m_freeLength;
}


