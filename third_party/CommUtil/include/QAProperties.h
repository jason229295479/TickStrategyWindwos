#ifndef _QAPROPERTIES_H
#define _QAPROPERTIES_H

#include <map>
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include "boost/property_tree/ini_parser.hpp"
#include "boost/lexical_cast.hpp"
#include "boost/algorithm/string.hpp"

class QAProperties
{
public:
	//设置文件路径
	static void SetFilePath(std::string &strFile);

	static void SetFilePath(const char *strFile);

	//是否加密，true 普通文件，false 加密文件 (暂未实现加密)
	static void ReadProperties(bool bCom = true);

	static std::string GetStringValue(const char *key, const char *value);

	static std::string GetStringValue(const std::string &strKey, std::string strValue = "");

	static std::map<std::string, std::string> Getmap()
	{
		return MapkeyValue;
	}
	static int64_t GetValueInt64(const std::string &strkey, int64_t iValue = 0);

	static int GetValueInt(const std::string &strkey, int iValue = 0);

	static std::map<std::string, std::string> InitMap();
private:

	static void parse(const std::string &strLine, std::string &strkey, std::string &strValue);
private:
	static std::map<std::string, std::string> MapkeyValue;
	static std::string StrFile;
};

#endif //_QAPROPERTIES_H
