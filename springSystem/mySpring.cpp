#include "stdafx.h"

#pragma once  

int CmySpring::springIndex = 0;	       //类的静态成员，需类外初始化
bool CmySpring::saveToFile = true;

CmySpring::CmySpring()
{
	k = 0.0;
	X0 = 0.0;
	X1 = 0.0;

	index = springIndex;
	springIndex++;

	openFileForSave(); 
}

CmySpring::CmySpring(double kk, springPortType type0, springPortType type1)
{
	k = kk;
	port0Type = type0;
	port1Type = type1;
	X0 = 0.0;
	X1 = 0.0;

	index = springIndex;
	springIndex++;

	openFileForSave(); 
}

CmySpring::~CmySpring()
{
	if (!(*ofile0))
	{
		ofile0->close();
	}

	if (!(*ofile1))
	{
		ofile1->close();
	}
}

void CmySpring::setK(double kk)
{
	k = kk;
}

void CmySpring::SetX0(double xx)
{
	X0 = xx;
	*ofile0 << X0<<endl;
}

void CmySpring::SetX1(double xx)
{
	X1 = xx;
	*ofile1 << X1<<endl;
}

double CmySpring::getForce0()
{
	return getK() * (X1 - X0);
}

double CmySpring::getForce1()
{
	return getK() * (X0 - X1);
}

double CmySpring::getK()
{
	return k;
}

double CmySpring::getX0()
{
	return X0;
}

double CmySpring::getX1()
{
	return X1;
}

void CmySpring::openFileForSave()
{
	if (saveToFile)
	{
		char fileName[32];

		sprintf_s(fileName, "./saveData/s%d_x0.txt", index);

		string oFileName(fileName);

		ofile0 = new ofstream(oFileName.c_str(),ofstream::out); 

		char fileName1[32];

		sprintf_s(fileName1, "./saveData/s%d_x1.txt", index);

		string oFileName1(fileName1);

		ofile1 = new ofstream(oFileName1.c_str(),ofstream::out); 

	} 
}
vector<string> CmySpring::split( string str, string pattern)
{
	vector<string> ret;
	if(pattern.empty()) return ret;
	size_t start=0,index=str.find_first_of(pattern,0);
	while(index!=str.npos)
	{
		if(start!=index)
			ret.push_back(str.substr(start,index-start));
		start=index+1;
		index=str.find_first_of(pattern,start);
	}
	if(!str.substr(start).empty())
		ret.push_back(str.substr(start));
	return ret;
}

void CmySpring::setXinput(string kFileName)
{
	ifstream ifile(kFileName, ios::in);

	if (!ifile)
	{
		cout<<"不能打开文件："<<kFileName<<endl;
		return;
	}

	tx.clear();

	string str;

	string pattern = " ;,\t";

	vector<string> ret;

	TXpair pairTemp;

	while(getline(ifile,str))
	{
		ret = split(str, pattern);

		if (ret.size() != 2)
		{
			cout<<"XT文件格式出错！"<<endl;
			return;
		}

		pairTemp.t = atof(ret[0].c_str());
		pairTemp.X = atof(ret[1].c_str());

		tx.push_back(pairTemp);
	}

	ifile.close();
}

double CmySpring::getXbyT(double t)
{
	if (0 == tx.size())
	{
		cout<<"tx 数据为空，setXbyT(double t)函数失败"<<endl;
		return 0;
	} 	

	if (t <= tx[0].t)
	{
		return tx[0].X;
	}
	else if (t >= tx[tx.size() - 1].t )
	{
		return tx[tx.size() - 1].X;
	}
	else
	{
		double ret = 0;
		for (int i = 0; i < (int)tx.size() - 1; ++i)
		{
			double t0 = tx[i].t;
			double t1 = tx[i + 1].t;
			if (t >= t0 && t < t1)
			{
				ret = tx[i].X + (tx[i + 1].X - tx[i].X)*(t - t0)/(t1 - t0);		   //线性插值
				break;
			}
		}

		return ret;
	}
}




