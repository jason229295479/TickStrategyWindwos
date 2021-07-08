#ifndef _QATIMERTASK_H_
#define _QATIMERTASK_H_

#include<functional>
#include<list>
#include<thread>
#include<mutex>
#include <atomic>
#include <map>
#include <string>

//用位运算效率更高

#define  MINUTES_SLOT 60
#define  SECONDS_SLOT 60
#define  MILLISECONDES_SLOT 10

#include <set>

typedef std::function<void(void)> TaskType;

struct TimeStamp //时间戳
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

struct Event     //挂在时间槽上的事件
{
	TaskType call_back;
	TimeStamp tri_time;    //事件触发的时间
	int dur;               //多久触发
	int count;             //执行次数
	int execuNum;          //已经执行次数
	int64_t taskID;		   //任务ID
	bool bStatus;		   //状态
};

class QATimerTask
{
public:

	QATimerTask();

	~QATimerTask();

	void Start(); //开始

	//添加定时任务
	int64_t SetTimer(int intervalTime, TaskType func, int count = 0); // 0 默认重复 返回任务ID

	//停止定时器
	void Stop();

	//取消定时任务
	void CancelTimer(int64_t taskID);

private:
	//当前时间搓(毫秒)
	uint64_t GetCurTimeStamps();
	//获取ms
	uint64_t GetMs(const TimeStamp &timeStamp);
	void run(); //主循环
	void insertTimer(Event &event); //插入事件
	void execuSlot(std::list<Event> &listEvent); //执行事件
	void getNextTimeStamp(TimeStamp &timeStamp, int Dur); //得到下一个时间
private:
	static std::atomic<uint64_t> LASTTIMESTAMPS;

	int m_Slot[MINUTES_SLOT][SECONDS_SLOT][MILLISECONDES_SLOT];
	std::list<Event> *m_taskList;
	TimeStamp m_timeStamp;
	std::mutex m_mux;
	int m_step;        //最小的间隔时间
	std::atomic<bool> m_bStopFlag;
	std::atomic<bool> m_bExitFlag;
	std::map<int64_t, int> m_mapEventPos; //记录当前节点位置，方便查找
	std::condition_variable m_cvEvent;
	std::mutex m_muxEvent;
	std::set<int64_t> m_setDelTaskID;
};

#endif // _QATIMERTASK_H_
