#include "stdafx.h"
#include <io.h>

int CMyObject::objectIndex = 0;

vector<CMyObject*> objList;

CMyObject::CMyObject()
{
	char objectName[32];

	sprintf_s(objectName, "object%d", objectIndex);

	m_objectName = objectName;

	createFileStream();

	m_objIndex = objectIndex;

	objectIndex++;

	objList.push_back(this);
}

CMyObject::CMyObject(string objname)
{
	m_objectName = objname;

	createFileStream();

	m_objIndex = objectIndex;

	objectIndex++;

	objList.push_back(this);
}

CMyObject::~CMyObject()
{
	if (!(*ofile))
	{
		ofile->close();
	}
}

void CMyObject::createFileStream()
{
	if (-1 == _access("saveData", 0))      //if the return value is -1, then we have to create the folder
	{
		system("md saveData");
	}

	string fileName = "./saveData/" + m_objectName + ".txt";

	ofile = new ofstream(fileName.c_str(), ofstream::out);

	if (!(*ofile))
	{
		cout << "create output file stream failed! exit" << endl;

		exit(-1);
	}
}

int CMyObject::getObjIndex()
{
	return m_objIndex;
}

void CMyObject::showMsg(string msg)
{
#ifdef _CONSOLE       //make sure it is console program
	cout << msg << endl;
#else
	::MessageBox(NULL,commFunc.stringToCString(msg),NULL,NULL);
#endif
}