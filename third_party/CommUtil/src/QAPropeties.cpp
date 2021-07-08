#include "QAProperties.h"


std::string QAProperties::StrFile = "./properties";
std::map<std::string, std::string> QAProperties::MapkeyValue = QAProperties::InitMap();

void QAProperties::SetFilePath(std::string &strFile)
{
	StrFile = strFile;
	std::cout << "StrFiel:" << StrFile << std::endl;
}

void QAProperties::SetFilePath(const char *strFile)
{
	StrFile = strFile;
}

void QAProperties::ReadProperties(bool bCom)
{
	if (bCom)
	{
		std::fstream outfile;
		outfile.open(StrFile, std::ios_base::in);
		if (outfile.is_open())
		{
			std::string strLine;
			while (getline(outfile, strLine))
			{
				std::string strKey, strValue;
				if (!strLine.empty())
				{
					parse(strLine, strKey, strValue);
					if (strKey.empty() || strValue.empty())
					{
						continue;
					}
					MapkeyValue[strKey] = strValue;
				}
			}
			outfile.close();
		}
	}
}


int64_t QAProperties::GetValueInt64(const std::string &strkey, int64_t iValue)
{
	std::string strRet = GetStringValue(strkey);
	if (strRet.empty())
	{
		return iValue;
	}
	return boost::lexical_cast<int64_t>(strRet);
}

int QAProperties::GetValueInt(const std::string &strkey, int iValue)
{
	std::string strRet = GetStringValue(strkey);
	if (strRet.empty())
	{
		return iValue;
	}
	return boost::lexical_cast<int>(strRet);
}

std::map<std::string, std::string> QAProperties::InitMap()
{
	std::map<std::string, std::string> mapTmp;
	return mapTmp;
}

void QAProperties::parse(const std::string &strLine, std::string &strkey, std::string &strValue)
{
	std::string strValid = strLine;

	//解析
	auto itFind = strLine.find("#");
	if (itFind != std::string::npos && itFind != 0)
	{
		strValid = strLine.substr(0, itFind);
	}
	else if (itFind == 0)
	{
		return;
	}

	if (strValid.find("=") == std::string::npos) //无key value
	{
		return;
	}
	std::vector<std::string> destination;
	boost::split(destination, strValid, boost::is_any_of("="), boost::token_compress_off);
	if (destination.size() != 2)
	{
		return;//无效配置
	}
	strkey = destination.at(0);
	strValue = destination.at(1);
	boost::trim(strkey);
	boost::trim(strValue);
}

std::string QAProperties::GetStringValue(const std::string &strKey, std::string strValue /*= ""*/)
{
	std::string strTmp = strKey;
	/*boost::to_lower(strTmp);*/
	auto iter = MapkeyValue.find(strTmp);
	if (iter == MapkeyValue.end())
	{
		return strValue;
		std::cout << "strValue=" << strValue << std::endl;
	}
	return iter->second;
	std::cout << "iter->second=" << iter->second << std::endl;
}


std::string QAProperties::GetStringValue(const char *key, const char *value)
{
	std::string strKey = key;
	std::string val = value;
	return GetStringValue(key, val);
}
