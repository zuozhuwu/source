#pragma once

/*
�涨��
	����ԽС��λ��Խ�͡����絯�ɵĶ˿�0��صľ���С�ڶ˿�1
	���ϵķ���Ϊ��
*/
enum springPortType{FIXEDPORT, FREEPORT, INPUTPORT};  //����INPUTPORT������ָ��INPUTPORT���ļ�

enum springPort{PORT0, PORT1};

struct TXpair	    //����ʱ��õ�Xֵ����INPUTPORT�˿���Ч
{
	double t;
	double X;
};

class CmySpring
{

protected:

	double k;
	double X0; 	  
	double X1; 

	vector<TXpair> tx;

public:
	int index;
	springPortType port0Type;
	springPortType port1Type;

	static int springIndex;
	static bool saveToFile;

public:
	CmySpring();
	CmySpring(double kk, springPortType type0 = FREEPORT, springPortType type1 = FREEPORT);
	~CmySpring();

	
	double getForce0();
	double getForce1();

	void   setK(double kk);
	void   SetX0(double xx);
	void   SetX1(double xx);

	virtual double getK();

	double getX0();
	double getX1();	

	void   setXinput(string kFileName);

	double getXbyT(double t);	 //����ʱ�����趨Xֵ����INPUTPORT�˿���Ч

protected:
	ofstream *ofile0;
	ofstream *ofile1;

	void openFileForSave();
	vector<string> split( string str, string pattern);
};

