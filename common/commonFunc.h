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
	void trim(string &s);          //去掉字符串两边的空格
	void SplitString(const std::string& in, std::vector<std::string>& out, const std::string& c);     //分割字符串函数
	std::string UTF8_To_string(const std::string & str);                 //utf8转化为string
	int hexToInt(char *pstr);                       //将字符串 “4F60” 转化为20320等整形
	double cstringToDouble(const CString &cstr);
	double stringToDouble(const string& str);
	int stringToInt(const string& str);
	std::string cstringToString(const CString &cstr);
	void showMsg(const CString &cstr );
	string getStringElement(const string&str, string patten, int subMatch);
	void saveToFile(string name, vector<double> &data);
	CString stringToCString(const string &str);
	std::string UnicodeToASCII(LPCWSTR lpszWText);    //wchar_t wcChinese[2] = { 0x4F60, 0 }; 这个宽字符代表你，注意后面的0，共两字节
	CString ASCIIToUnicode(const std::string &str);
	CString getWorkDir();

protected:
	DWORD GetModuleDirectory(LPWSTR pszDir, DWORD nSize);
};

extern CcommonFunc commFunc;