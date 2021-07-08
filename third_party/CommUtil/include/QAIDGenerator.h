#ifndef _QAIDGENERATOR_H_
#define  _QAIDGENERATOR_H_

#include <iostream>
#include <string>
#include <atomic>
#include <chrono>

#define MACHINE_NUM 5 //����idλ�� ���2^6 -1������
#define DATACENTOR_NUM 5 //��������idλ��
#define SEQUENCE_NUM 12 //����id
#define SEQUENCE_MASK 4095

//˵���� û�н��������ʱ��ʱ��ص�������, ���������ɵ�ID����֤������֮ǰ��ID��

//��λ(1) + ʱ��꣨41��+ ��������(5) + ����(5) + ����(12) 
//ΨһID������
class QAIDGenerator
{
public:
	static void Init(const int &appID, const int &PosID);

	static int64_t GetID();

private:
	//��ȡ����ʱ��
	static uint64_t GetTimeOfDay();
	
	//��ǰʱ���
	static uint64_t GetCurTimeStamps();
	
	//��ȡ��һ����
	static uint64_t NextMillis();

private:
	static std::atomic<uint64_t> LastTimestamp_; //�ϴ�ʱ���
	static std::atomic<int> Sequence_;
	static int DataCenterID_;
	static int WorkerID_;
};



#endif // _QAIDGENERATOR_H_
