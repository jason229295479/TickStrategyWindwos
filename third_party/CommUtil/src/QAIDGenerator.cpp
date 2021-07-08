#include "QAIDGenerator.h"

std::atomic<uint64_t> QAIDGenerator::LastTimestamp_ = 0; //上次时间戳
std::atomic<int> QAIDGenerator::Sequence_ = 0;
int QAIDGenerator::DataCenterID_ = 1;
int QAIDGenerator::WorkerID_ = 1;

void QAIDGenerator::Init(const int &appID, const int &PosID)
{
	WorkerID_ = appID;
	DataCenterID_ = PosID;
	auto curTimestamp = GetCurTimeStamps();
}
int64_t QAIDGenerator::GetID()
{
	// 如果当前时间小于上一次ID生成的时间戳，说明系统时钟回退过这个时候应当抛出异常
	auto timeStamp = GetTimeOfDay();
	return timeStamp << 22 | (DataCenterID_ << 17) | (WorkerID_ << 12) | Sequence_;
}

//获取可用时间
uint64_t QAIDGenerator::GetTimeOfDay()
{
	auto curtimes = GetCurTimeStamps();
	while (LastTimestamp_ > curtimes) //时间回跳
	{
		curtimes = GetCurTimeStamps();
	}
	if (LastTimestamp_ < curtimes)
	{
		Sequence_ = 0;
	}
	else if (LastTimestamp_ == curtimes)
	{
		// 如果是同一时间生成的，则进行毫秒内序列
		Sequence_ = (Sequence_ + 1) & SEQUENCE_MASK;
		if (0 == Sequence_) {
			// 毫秒内序列溢出, 阻塞到下一个毫秒,获得新的时间戳
			curtimes = NextMillis();
		}
	}
	LastTimestamp_ = curtimes; //更新上一次时间
	return curtimes;
}

//当前时间搓
uint64_t QAIDGenerator::GetCurTimeStamps()
{
	std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds> tp = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
	auto tmp = std::chrono::duration_cast<std::chrono::milliseconds>(tp.time_since_epoch());
	return tmp.count();

}
//获取下一毫秒
uint64_t QAIDGenerator::NextMillis()
{
	uint64_t curtimes = GetCurTimeStamps();
	while (curtimes == LastTimestamp_)
	{
		curtimes = GetCurTimeStamps();
	}
	return curtimes;
}