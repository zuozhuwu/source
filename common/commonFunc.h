#pragma once
#include "stdafx.h"
#include <fstream>
#include <regex>
#include <afx.h>
#include <string>
#include <iostream>

using namespace std;

class CcommonFunc
{
public:
	void trim(string &s);          //ȥ���ַ������ߵĿո�
	void SplitString(const std::string& in, std::vector<std::string>& out, const std::string& c);     //�ָ��ַ�������
	std::string UTF8_To_string(const std::string & str);                 //utf8ת��Ϊstring
	int hexToInt(char *pstr);                       //���ַ��� ��4F60�� ת��Ϊ20320������
	double cstringToDouble(const CString &cstr);
	double stringToDouble(const string& str);
	int stringToInt(const string& str);
	std::string cstringToString(const CString &cstr);
	void showMsg(const CString &cstr );
	string getStringElement(const string&str, string patten, int subMatch);
	void saveToFile(string name, vector<double> &data);
	CString stringToCString(const string &str);
	std::string UnicodeToASCII(LPCWSTR lpszWText);    //wchar_t wcChinese[2] = { 0x4F60, 0 }; ������ַ������㣬ע������0�������ֽ�
	CString ASCIIToUnicode(const std::string &str);
	CString getWorkDir();

protected:
	DWORD GetModuleDirectory(LPWSTR pszDir, DWORD nSize);
};

extern CcommonFunc commFunc;