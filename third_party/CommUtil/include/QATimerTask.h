#ifndef _QATIMERTASK_H_
#define _QATIMERTASK_H_

#include<functional>
#include<list>
#include<thread>
#include<mutex>
#include <atomic>
#include <map>
#include <string>

//��λ����Ч�ʸ���

#define  MINUTES_SLOT 60
#define  SECONDS_SLOT 60
#define  MILLISECONDES_SLOT 10

#include <set>

typedef std::function<void(void)> TaskType;

struct TimeStamp //ʱ���
{
	int ms;
	int s;
	int min;
	bool operator==(TimeStamp timeStamp)
	{
		return timeStamp.ms == ms&&timeStamp.s == s&&timeStamp.min == min;
	}

	std::string ToString()
	{
		std::string str = std::to_string(min) + " " + std::to_string(s) + " " + std::to_string(ms);
		return str;
	}
};

struct Event     //����ʱ����ϵ��¼�
{
	TaskType call_back;
	TimeStamp tri_time;    //�¼�������ʱ��
	int dur;               //��ô���
	int count;             //ִ�д���
	int execuNum;          //�Ѿ�ִ�д���
	int64_t taskID;		   //����ID
	bool bStatus;		   //״̬
};

class QATimerTask
{
public:

	QATimerTask();

	~QATimerTask();

	void Start(); //��ʼ

	//��Ӷ�ʱ����
	int64_t SetTimer(int intervalTime, TaskType func, int count = 0); // 0 Ĭ���ظ� ��������ID

	//ֹͣ��ʱ��
	void Stop();

	//ȡ����ʱ����
	void CancelTimer(int64_t taskID);

private:
	//��ǰʱ���(����)
	uint64_t GetCurTimeStamps();
	//��ȡms
	uint64_t GetMs(const TimeStamp &timeStamp);
	void run(); //��ѭ��
	void insertTimer(Event &event); //�����¼�
	void execuSlot(std::list<Event> &listEvent); //ִ���¼�
	void getNextTimeStamp(TimeStamp &timeStamp, int Dur); //�õ���һ��ʱ��
private:
	static std::atomic<uint64_t> LASTTIMESTAMPS;

	int m_Slot[MINUTES_SLOT][SECONDS_SLOT][MILLISECONDES_SLOT];
	std::list<Event> *m_taskList;
	TimeStamp m_timeStamp;
	std::mutex m_mux;
	int m_step;        //��С�ļ��ʱ��
	std::atomic<bool> m_bStopFlag;
	std::atomic<bool> m_bExitFlag;
	std::map<int64_t, int> m_mapEventPos; //��¼��ǰ�ڵ�λ�ã��������
	std::condition_variable m_cvEvent;
	std::mutex m_muxEvent;
	std::set<int64_t> m_setDelTaskID;
};

#endif // _QATIMERTASK_H_
