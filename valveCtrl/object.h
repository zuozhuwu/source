#pragma once
#include "stdafx.h"
#include <vector>

class CMyObject
{
private:
	string m_objectName;

	int m_objIndex;


public:
	static int objectIndex;

protected:
	ofstream* ofile;


public:
	CMyObject();

	CMyObject(string objname);

	~CMyObject();

	virtual void saveData(int time){};

	int getObjIndex();

	void showMsg(string msg);

	virtual string getTypeName(){ return ""; }

private:
	void createFileStream();

};

extern vector<CMyObject*> objList;