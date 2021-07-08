// msgpack.cpp : 定义控制台应用程序的入口点。
//

// #include <string>
// #include <iostream>
// #include <sstream>
// #include "QAMsgPack.hpp"
// 
// struct A
// {
// private:
// 	std::wstring wstr;
// 	int i;
// 	double dbVal;
// 	std::list<int> listA;
// 	std::map<int, std::string> mapVal;
// public:
// 	MSGPACK_DEFINE( wstr, i, dbVal, listA, mapVal);
// 
// public:
// 	A()
// 	{
// 		wstr = L"hello world 我是谁";
// 		i = 10;
// 		dbVal = 0.9;
// 		listA.emplace_back(5);
// 		listA.emplace_back(6);
// 		mapVal[1] = "go";
// 		mapVal[2] = "c++";
// 	}
// 
// 	void clear()
// 	{
// 		dbVal = 0;
// 		i = 0;
// 		listA.clear();
// 		mapVal.clear();
// 	}
// };
// 
// class B
// {
// 	std::list<A> ba;
// public:
// 	MSGPACK_DEFINE(ba);
// 	B()
// 	{
// 		A a1, a2;
// 
// 		ba.emplace_back(a1);
// 		ba.emplace_back(a2);
// 	}
// };
// 
#include <iostream>
#include <thread>
#include <functional>

#include "QAIDGenerator.h"
#include "QALog.h"
#include "Timer.h"
#include "QAProperties.h"
#include "QABase64.h"
#include "QATimerTask.h"
#include "dtoa_milo.h"
#include "CommUtil.h"
#include "FileUtil.h"
#include "QAMsgPack.h"
#include "ThreadPool.h"

void fun100()
{
	std::cout << "------------fun 100--------------" << std::endl;
}

void fun200()
{
	std::cout << "------------fun 200--------------" << std::endl;
}

void fun500()
{
	std::cout << "------------fun 500--------------" << std::endl;
}

void fun1500()
{
	std::cout << "------------fun 1500-------------" << std::endl;
}

struct Mys
{
	int i;
	std::vector<double> vecdb;
	std::string str;
	MSGPACK_DEFINE(i, vecdb, str)
};


struct gfun {
	int operator()(int n) {

		std::thread::id iID = std::this_thread::get_id();

		std::cout << "gfun " <<  iID << std::endl;
		printf("%d  hello, gfun !", n);
		return 42;
	}
};

class Test
{
public:
	int GetThreadId(std::string a, double b)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(10000));
		std::thread::id i = std::this_thread::get_id();
		std::cout << "In Test, thread id: " << i << std::endl;
		std::cout << "a: " << a.c_str() << ", b = " << b << std::endl;
		return 56;
	}
};

int main(void)
{
#if 0
	// 	std::string p = "55";
	// 	std::string s = "12345";
	// 	std::cout << "加密前:" << s << std::endl;
	// 	std::string ss = QABase64::EncodeBase64(s, s.length());//加密
	// 	std::cout << "加密后:" << ss << std::endl;
	// 	p = QABase64::DecodeBase64(ss);//解密
	// 	std::cout << "解密后:" << p << std::endl;
	// 
	// 	QALog::Init();
	// 	auto k = QALog::GetInstance();
	// 	k->debug("hwllo");;
	// 	QALog::Destroy();

	// 	 std::cout << "start generate id" << std::endl;
	// 
	// 	 int workid = 1;
	// 	 int posid = 2;
	// 	 QAIDGenerator::Init(workid, posid);
	// 	
	// 
	// 	 const size_t count = 20000000;
	// 
	// 	 Timer timer;
	// 	 static int64_t IPRe = 0;
	// 	 for (size_t i = 0; i < count; i++)
	// 	 {
	// 		 QAIDGenerator::GetID();
	// 	 }
	// 	 // 我的电脑生成 20000000 id 的耗时为 4.887s
	// 	 std::cout << "generate " << count << " id elapsed: " << timer.ElapsedMicro() << "ms" << std::endl;

	//	QAProperties::SetFilePath("./test");
	//	QAProperties::ReadProperties(true);

	//	std::string strAppName = QAProperties::GetStringValue("appName", "kak");
	//	std::map<std::string, std::string> MapkeyValue = QAProperties::Getmap();

	// 	 int workid = 1;
	// 	 int posid = 2;
	// 	 QAIDGenerator::Init(workid, posid);
	// 	 std::function<void(void)> f100 = std::bind(&fun100);
	// 	 std::function<void(void)> f200 = std::bind(&fun200);
	// 	 std::function<void(void)> f500 = std::bind(&fun500);
	// 	 std::function<void(void)> f1500 = std::bind(&fun1500);
	// // 
	// 	 QATimerTask timeWheel;
	// 	 timeWheel.Start();
	// 
	// 	 //加入定时器
	// 	auto tid1 =  timeWheel.SetTimer(1000, f100);
	// 	auto tid2 = timeWheel.SetTimer(2000, f200);
	// 	auto tid3 = timeWheel.SetTimer(5000, f500);
	// 	auto tid4 = timeWheel.SetTimer(1500, f1500);
	// 
	// 
	// 	
	// 	getchar();
	// 	std::cout << "cancel " << std::endl;
	// 	timeWheel.CancelTimer(tid4);
	// 	timeWheel.CancelTimer(tid3);
	// 	timeWheel.CancelTimer(tid1);


	// 	std::string strD = "";
	// 
	// 	//double db = 10/6.0;
	// 	double db = 2.0;
	// 	std::cout << CommUtil::Double2Str(db,0) << std::endl;

	std::string strFile = "./111.txt";

	// 	std::string strDir = "./dirtest";
	// 
	// 	if (FileUtil::isDirExist(strDir))
	// 	{
	// 		std::cout << "exist dir ." << std::endl;
	// 	}
	// 	if (FileUtil::IsFileExist(strFile))
	// 	{
	// 		std::cout << "exist file" << std::endl;
	// 	}
	// 
	// 	bool bRe = FileUtil::Remove(strDir);
	// 	bool bRe1 = FileUtil::Remove(strFile);
	// 
	// 	bool bMkdir = FileUtil::CreateDir(strDir);
	// 	bool bMkdi1r = FileUtil::CreateDir(strFile);


	// 	Mys ms1, ms2;
	// 
	// 	ms1.i = 1;
	// 	ms1.vecdb.emplace_back(5);
	// 	std::string str1, str2;
	// 	QAMsgPack::Serialize(ms1, str1);
	// 	FileUtil::WriteFileApp(strFile, str1);
	// 
	// 	ms2.i = 5;
	// 	ms2.vecdb.emplace_back(6);
	// 	QAMsgPack::Serialize(ms2, str1);
	// 	FileUtil::WriteFileApp(strFile, str1);
	// 
	// 
	// 	std::list<std::string> listP;
	// 	FileUtil::ReadFileLine(strFile, listP);
	// 	std::list<Mys> list1;
	// 	for (auto &l1 : listP)
	// 	{
	// 		Mys ms2;
	// 		QAMsgPack::Deserialized(l1, ms2);
	// 		list1.emplace_back(ms2);
	// 	}
#endif
	ThreadPoolUtil::InitThreadPool();

	Test t;

	ThreadPoolUtil::AmqpThreadPool->AddTask(std::bind(&Test::GetThreadId, &t, "123", 456.789));
	
	gfun gg;
	auto ii = std::bind(gg, 5);
	ThreadPoolUtil::AmqpThreadPool->AddTask(ii);


	getchar();

	ThreadPoolUtil::StopThreadPool();

	return 0;
}

