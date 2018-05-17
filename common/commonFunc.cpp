#include "stdafx.h"

#define BUFFSIZE 512
char c[BUFFSIZE];
double CcommonFunc::cstringToDouble(const CString &cstr)
{
	memset(c, 0, BUFFSIZE);
	int len = cstr.GetLength();
	for (int i = 0; i<len; i++)
		c[i] = (char)cstr.GetAt(i);
	return atof(c);
}

double CcommonFunc::stringToDouble(const string& str)
{
	return cstringToDouble(stringToCString(str));
}

int CcommonFunc::stringToInt(const string& str)
{
	return atoi(str.c_str());
}

std::string CcommonFunc::UTF8_To_string(const std::string & str)
{
	int nwLen = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);

	wchar_t * pwBuf = new wchar_t[nwLen + 1];//一定要加1，不然会出现尾巴  
	memset(pwBuf, 0, nwLen * 2 + 2);

	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), (int)str.length(), pwBuf, nwLen);

	int nLen = WideCharToMultiByte(CP_ACP, 0, pwBuf, -1, NULL, NULL, NULL, NULL);

	char * pBuf = new char[nLen + 1];
	memset(pBuf, 0, nLen + 1);

	WideCharToMultiByte(CP_ACP, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

	std::string retStr = pBuf;

	delete[]pBuf;
	delete[]pwBuf;

	pBuf = NULL;
	pwBuf = NULL;

	return retStr;
}

void CcommonFunc::SplitString(const std::string& s, std::vector<std::string>& v, const std::string& c)
{
	std::string::size_type pos1, pos2;
	pos2 = s.find(c);
	pos1 = 0;
	while (std::string::npos != pos2)
	{
		v.push_back(s.substr(pos1, pos2 - pos1));

		pos1 = pos2 + c.size();
		pos2 = s.find(c, pos1);
	}
	if (pos1 != s.length())
		v.push_back(s.substr(pos1));
}

void CcommonFunc::trim(string &s)          //去掉字符串两边的空格
{
	if (s.empty())
	{
		return;
	}
	s.erase(0, s.find_first_not_of(" "));
	s.erase(s.find_last_not_of(" ") + 1);	
}

int CcommonFunc::hexToInt(char *pstr)                       //将字符串 “4F60” 转化为20320等整形
{
	int ans = 0;
	char *pt;
	pt = pstr;
	if (!pstr)
	{
		return 0;
	}
	while (*pt)
	{
		ans = ans << 4;
		if ((*pt >= 'A' && *pt <= 'F') || (*pt >= 'a' && *pt <= 'f'))
			ans = ans | ((*pt & 0x5f) - 0x37);
		else
			ans = ans | (*pt) - 0x30;
		pt++;
	}
	return ans;
}

string CcommonFunc::cstringToString(const CString &cstr)
{
	memset(c, 0, BUFFSIZE);
	int len = cstr.GetLength();
	for (int i = 0; i<len; i++)
		c[i] = (char)cstr.GetAt(i);

	return string(c);
}

void CcommonFunc::showMsg(const CString &cstr)
{
#ifdef _CONSOLE	
	cout << cstringToString(cstr) << endl;
#endif
}


string CcommonFunc::getStringElement(const string&str, string patten, int subMatch)
{
	std::string temp;
	regex getStringElement;
	getStringElement.assign(patten);
	smatch what_getStringElement;
	std::string::const_iterator getStringElement_begin, getStringElement_end;
	getStringElement_begin = str.begin();
	getStringElement_end = str.end();
	while (regex_search(getStringElement_begin, getStringElement_end, what_getStringElement, getStringElement))
	{
		if (subMatch<(int)what_getStringElement.size())
		{

			temp = what_getStringElement[subMatch].str();
			break;
		}
		else
		{
			//cerr<<"getStringElement 函数的第三个参数超出了范围"<<endl;
			return "";
		}
	}
	return temp;
}


void CcommonFunc::saveToFile(string name, vector<double> &data)
{
	wchar_t szFileName[MAX_PATH];
	if (!GetModuleDirectory(szFileName, ARRAYSIZE(szFileName)))
	{
		_putws(L"GetModuleDirectory failed");
		return ;
	}	

	string savedPath = commFunc.UnicodeToASCII(szFileName);

	name = savedPath + "savedData\\" + name;
	ofstream of(name.c_str(), ios::out);

	if (!of)
	{
		return;
	}

	for (size_t i = 0; i < (size_t)data.size(); i++)
	{
		of << data[i] << endl;
	}

	of.close();
}

CString CcommonFunc::stringToCString(const string &str)
{
	CString cstr;
	for (unsigned int i = 0; i<str.size(); i++)
		cstr.AppendChar(str[i]);
	return cstr;
}

std::string CcommonFunc::UnicodeToASCII(LPCWSTR lpszWText)  //wchar_t wcChinese[2] = { 0x4F60, 0 }; 这个宽字符代表你，注意后面的0，共两字节
{
	int ansiLen = ::WideCharToMultiByte(CP_ACP, NULL, lpszWText, -1, NULL, 0, NULL, NULL);         //这里是-1的话，就包括了末尾的\0，如果是wcslen(lpszWText)，则不包括，决定了ansiLen是否需要+1

	char* szAnsi = new char[ansiLen];

	::WideCharToMultiByte(CP_ACP, NULL, lpszWText, (int)wcslen(lpszWText), szAnsi, ansiLen, NULL, NULL);

	szAnsi[ansiLen - 1] = '\0';                         //最后一个字符要让他为‘\0’

	std::string str(szAnsi);

	delete[] szAnsi;

	return str;
}

CString CcommonFunc::ASCIIToUnicode(const std::string &str)
{
	CString cstr;

	if (str.empty()) return cstr;

	int size_needed = (int)str.size() + 1;

	wchar_t* wsz = new wchar_t[str.size() + 1];
	wsz[str.size()] = '\0';

	MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, wsz, (int)str.size());

	cstr = CString(wsz);

	delete[]wsz;

	return cstr;
}

DWORD CcommonFunc::GetModuleDirectory(LPWSTR pszDir, DWORD nSize)
{
	// Retrieve the path of the executable file of the current process.
	nSize = GetModuleFileName(NULL, pszDir, nSize);
	if (!nSize || GetLastError() == ERROR_INSUFFICIENT_BUFFER)
	{
		*pszDir = L'\0'; // Ensure it's NULL terminated
		return 0;
	}

	// Run through looking for the last slash in the file path.
	// When we find it, NULL it to truncate the following filename part.

	for (int i = nSize - 1; i >= 0; i--)
	{
		if (pszDir[i] == L'\\' || pszDir[i] == L'/')
		{
			pszDir[i + 1] = L'\0';
			nSize = i + 1;
			break;
		}
	}
	return nSize;
}

CString CcommonFunc::getWorkDir()
{
	wchar_t szFileName[MAX_PATH];
	if (!GetModuleDirectory(szFileName, ARRAYSIZE(szFileName)))
	{		
		return _T("");
	}

	return CString(szFileName);
}

CcommonFunc commFunc;