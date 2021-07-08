#include "QAIDGenerator.h"

std::atomic<uint64_t> QAIDGenerator::LastTimestamp_ = 0; //�ϴ�ʱ���
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
	// �����ǰʱ��С����һ��ID���ɵ�ʱ�����˵��ϵͳʱ�ӻ��˹����ʱ��Ӧ���׳��쳣
	auto timeStamp = GetTimeOfDay();
	return timeStamp << 22 | (DataCenterID_ << 17) | (WorkerID_ << 12) | Sequence_;
}

//��ȡ����ʱ��
uint64_t QAIDGenerator::GetTimeOfDay()
{
	auto curtimes = GetCurTimeStamps();
	while (LastTimestamp_ > curtimes) //ʱ�����
	{
		curtimes = GetCurTimeStamps();
	}
	if (LastTimestamp_ < curtimes)
	{
		Sequence_ = 0;
	}
	else if (LastTimestamp_ == curtimes)
	{
		// �����ͬһʱ�����ɵģ�����к���������
		Sequence_ = (Sequence_ + 1) & SEQUENCE_MASK;
		if (0 == Sequence_) {
			// �������������, ��������һ������,����µ�ʱ���
			curtimes = NextMillis();
		}
	}
	LastTimestamp_ = curtimes; //������һ��ʱ��
	return curtimes;
}

//��ǰʱ���
uint64_t QAIDGenerator::GetCurTimeStamps()
{
	std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds> tp = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
	auto tmp = std::chrono::duration_cast<std::chrono::milliseconds>(tp.time_since_epoch());
	return tmp.count();

}
//��ȡ��һ����
uint64_t QAIDGenerator::NextMillis()
{
	uint64_t curtimes = GetCurTimeStamps();
	while (curtimes == LastTimestamp_)
	{
		curtimes = GetCurTimeStamps();
	}
	return curtimes;
}