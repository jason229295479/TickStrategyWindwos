#ifndef _COMMUTIL_HPP_
#define  _COMMUTIL_HPP_

#include <codecvt>

#include "boost/date_time/posix_time/posix_time.hpp"



class CommUtil
{
public:
	static std::string WS2S(const std::wstring &wstr);

	static std::wstring S2WS(const std::string &str);

	//默认精度6 四舍五入
	static std::string Double2Str(const double &dbValue, int iPre = 6);

	static void Double2Str(const double &dbValue, std::string &strValue, int iPre);

	static std::string db2Str(const double &dbValue);

	static double DoublePre(const double &dbValue, int iPre);
	//获取精度
	static int GetPre(const double &dbUnit);
	//根据最小变动单位调整价格
	static double ConvertUnit(const double &dbvalue, const double &dbUnit);

	static char* Utf82Gbk(const char* utf8);  //解决中文乱码

	static char* Utf82Gbk(const std::string &utf8);  //解决中文乱码

	static std::string GetTime(const boost::posix_time::ptime &pt);

	static std::string GetDate(const boost::gregorian::date &dt, bool bISO = true);

	static boost::gregorian::date GetGreDate(const std::string &strdate);

	static boost::gregorian::date GetGreDate(const int idate);

	static void ptTime2DateTime(const boost::posix_time::ptime& pt, std::string &strDate, std::string &strTime);
};
#endif // _COMMUTIL_HPP_
