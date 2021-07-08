#ifndef _QAIDGENERATOR_H_
#define  _QAIDGENERATOR_H_

#include <iostream>
#include <string>
#include <atomic>
#include <chrono>

#define MACHINE_NUM 5 //机器id位数 最多2^6 -1个机器
#define DATACENTOR_NUM 5 //数据中心id位数
#define SEQUENCE_NUM 12 //序列id
#define SEQUENCE_MASK 4095

//说明： 没有解决重启的时候时间回调了问题, 重启后生成的ID不保证比重启之前的ID大

//空位(1) + 时间搓（41）+ 数据中心(5) + 机器(5) + 序列(12) 
//唯一ID生成器
class QAIDGenerator
{
public:
	static void Init(const int &appID, const int &PosID);

	static int64_t GetID();

private:
	//获取可用时间
	static uint64_t GetTimeOfDay();
	
	//当前时间搓
	static uint64_t GetCurTimeStamps();
	
	//获取下一毫秒
	static uint64_t NextMillis();

private:
	static std::atomic<uint64_t> LastTimestamp_; //上次时间戳
	static std::atomic<int> Sequence_;
	static int DataCenterID_;
	static int WorkerID_;
};



#endif // _QAIDGENERATOR_H_
