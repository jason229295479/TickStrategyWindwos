#include "CommUtil.h"
#include "dtoa_milo.h"
#include "windows.h"

std::string CommUtil::WS2S(const std::wstring &wstr)
{
	std::wstring_convert<std::codecvt<wchar_t, char, std::mbstate_t>> converter(new std::codecvt<wchar_t, char, std::mbstate_t>("CHS"));
	std::string str = converter.to_bytes(wstr);
	return str;
}

std::wstring CommUtil::S2WS(const std::string &str)
{
	std::wstring_convert<std::codecvt<wchar_t, char, std::mbstate_t>> converter(new std::codecvt<wchar_t, char, std::mbstate_t>("CHS"));
	std::wstring wstr = converter.from_bytes(str);
	return wstr;
}


std::string CommUtil::Double2Str(const double &dbValue, int iPre)
{
	std::string strValue;
	Double2Str(dbValue, strValue, iPre);
	return strValue;
}

void CommUtil::Double2Str(const double &dbValue, std::string &strValue, int iPre)
{
	char buf[1024] = { 0 };
	std::string strPre = "%." + std::to_string(iPre) + "f";
	sprintf_s(buf, strPre.c_str(), dbValue);
	strValue = buf;
}

std::string CommUtil::db2Str(const double &dbValue)
{
	std::ostringstream oss;
	oss << dbValue;	
	return oss.str();
}

double CommUtil::DoublePre(const double &dbValue, int iPre)
{
	char buf[1024] = { 0 };
	std::string strPre = "%." + std::to_string(iPre) + "f";
	sprintf_s(buf, strPre.c_str(), dbValue);
	return atof(buf);
}

int CommUtil::GetPre(const double &dbUnit)
{
	std::string strUnit = db2Str(dbUnit);
	int idotSize = 0;
	auto itdot = strUnit.find(".");
	if (itdot != std::string::npos)
	{
		std::string strDot = strUnit.substr(itdot + 1);
		idotSize = static_cast<int>(strDot.size());
	}
	return idotSize;
}

double CommUtil::ConvertUnit(const double &dbvalue, const double &dbUnit)
{
	//doubleת�ַ���
	std::string strUnit = db2Str(dbUnit);
	int iunit = 1;
	int idotSize = 0;
	//find ���� ����. ��strUnit �е��±�λ��
	auto itdot = strUnit.find(".");
	// ����ҵ���
	if (itdot != std::string::npos)
	{
		//�ַ�����ȡ
		std::string strDot = strUnit.substr(itdot + 1);
		//ȡ��
		idotSize = static_cast<int>(strDot.size());
		//�ַ���ת��
		iunit = std::stoi(strDot);
	}
	//���û���ҵ�
	else
	{
		//�ַ���ת��
		iunit = std::stoi(strUnit);
	}
	//double��ȷ2λС��
	double dbDotVal = DoublePre(dbvalue, idotSize);

	//��� ��С�䶯��λ��1
	if (iunit == 1)
	{
		return dbDotVal;
	}
	//����
	int64_t iAdjust = 1;
	for (int i = 0; i < idotSize; ++i)
	{
		iAdjust *= 10;
	}

	int64_t remainder = static_cast<int64_t>(dbDotVal * iAdjust) % iunit;
	int64_t iQuotient =static_cast<int64_t>(dbDotVal * iAdjust) / iunit;
	if (static_cast<double>(remainder) >= static_cast<double>(iunit) / 2.0)
	{
		iQuotient += 1;
	}
	double dbRet = iQuotient * iunit / static_cast<double>(iAdjust);
	return dbRet;
}

char* CommUtil::Utf82Gbk(const char* utf8)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len + 1];
	memset(wstr, 0, len + 1);
	MultiByteToWideChar(CP_UTF8, 0, utf8, -1, wstr, len);
	len = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len + 1];
	memset(str, 0, len + 1);
	WideCharToMultiByte(CP_ACP, 0, wstr, -1, str, len, NULL, NULL);
	if (wstr) delete[] wstr;
	return str;
}

char* CommUtil::Utf82Gbk(const std::string &utf8)
{
	return Utf82Gbk(utf8.c_str());
}

std::string CommUtil::GetTime(const boost::posix_time::ptime &pt)
{
	if (pt.is_not_a_date_time())
	{
		return "";
	}
	std::string strpt = boost::posix_time::to_iso_extended_string(pt);
	auto itT = strpt.find("T");
	if (itT != std::string::npos)
	{
		strpt = strpt.replace(itT, 1, " ");
	}
	return strpt;
}


std::string CommUtil::GetDate(const boost::gregorian::date &dt, bool bISO/*= true*/)
{
	if (dt.is_not_a_date())
	{
		return "";
	}
	if (bISO)
	{
		return boost::gregorian::to_iso_string(dt);
	}
	else
	{
		return boost::gregorian::to_iso_extended_string(dt);
	}
	
}

boost::gregorian::date CommUtil::GetGreDate(const std::string &strdate)
{
	return boost::gregorian::from_undelimited_string(strdate);
}

boost::gregorian::date CommUtil::GetGreDate(const int idate)
{
	std::string strDate = std::to_string(idate);
	return GetGreDate(strDate);
}

void CommUtil::ptTime2DateTime(const boost::posix_time::ptime& pt, std::string &strDate, std::string &strTime)
{
	strDate = boost::gregorian::to_iso_string(pt.date());
	strTime = boost::posix_time::to_simple_string(pt.time_of_day());
}

