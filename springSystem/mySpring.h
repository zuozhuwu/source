#pragma once

/*
规定：
	数字越小，位置越低。例如弹簧的端口0离地的距离小于端口1
	向上的方向为正
*/
enum springPortType{FIXEDPORT, FREEPORT, INPUTPORT};  //对于INPUTPORT，必须指定INPUTPORT的文件

enum springPort{PORT0, PORT1};

struct TXpair	    //根据时间得到X值，对INPUTPORT端口有效
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

	double getXbyT(double t);	 //根据时间来设定X值，对INPUTPORT端口有效

protected:
	ofstream *ofile0;
	ofstream *ofile1;

	void openFileForSave();
	vector<string> split( string str, string pattern);
};

