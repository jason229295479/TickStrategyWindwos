#include "QATimerTask.h"

#include <time.h>
#include "boost/algorithm/string.hpp"
#include "boost/lexical_cast.hpp"
#include "QAIDGenerator.h"



std::atomic<uint64_t> QATimerTask::LASTTIMESTAMPS = 0;
QATimerTask::QATimerTask()
{
	m_timeStamp.min = m_timeStamp.s = m_timeStamp.ms = 0;
	// 	auto t = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now());
	// 	LASTTIMESTAMPS = t.time_since_epoch().count();
	m_step = 1000 / MILLISECONDES_SLOT;
	//getNextTimeStamp(m_timeStamp, m_step);
	m_bStopFlag = true;
	m_bExitFlag = false;
	m_taskList = new std::list<Event>[MINUTES_SLOT + SECONDS_SLOT + MILLISECONDES_SLOT];
}

QATimerTask::~QATimerTask()
{
	if (m_taskList != nullptr)
	{
		delete[] m_taskList;
		m_taskList = nullptr;
	}
	m_mapEventPos.clear();
}

void QATimerTask::Start()
{
	m_bStopFlag = false;
	m_bExitFlag = false;
	std::thread th([this]()
	{
		this->run();
	});
	th.detach();
}


int64_t QATimerTask::SetTimer(int intervalTime, TaskType func, int count /*= 0*/)
{
	if (intervalTime < m_step)
	{
		return -1;  //发生事件小于最小间隔
	}
	if (intervalTime%m_step != 0)
	{
		return -1;
	}

	

	Event event;
	event.call_back = func;
	event.tri_time.ms = m_timeStamp.ms;
	event.tri_time.s = m_timeStamp.s;
	event.tri_time.min = m_timeStamp.min;
	event.dur = intervalTime;
	event.count = count;
	event.execuNum = 0;
	event.taskID = QAIDGenerator::GetID();
	getNextTimeStamp(event.tri_time, event.dur);

	std::unique_lock<std::mutex> lock(m_mux);
	insertTimer(std::move(event));
	lock.unlock();

	return event.taskID;
}

void QATimerTask::Stop()
{
	m_bStopFlag = true;
	while (!m_bExitFlag)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}

void QATimerTask::CancelTimer(int64_t taskID)
{
	std::unique_lock<std::mutex> lock(m_mux);
	auto itFindTaskID = m_mapEventPos.find(taskID);
	if (itFindTaskID != m_mapEventPos.end())
	{
		std::unique_lock<std::mutex> lk(m_muxEvent);
		m_setDelTaskID.insert(taskID);
		for (auto itEvent = m_taskList[itFindTaskID->second].begin(); itEvent != m_taskList[itFindTaskID->second].end();)
		{
			if (itEvent->taskID == taskID)
			{
				if (itEvent->bStatus == true)
				{
					m_cvEvent.wait(lk, [itEvent]() {
						if (itEvent->bStatus == false)
						{
							return true;
						}
						return false; 
					});
				}

				m_taskList[itFindTaskID->second].erase(itEvent);
				m_mapEventPos.erase(itFindTaskID);
				m_setDelTaskID.erase(taskID);
				return;
			}
			else
			{
				++itEvent;
			}
		}
	}
}

uint64_t QATimerTask::GetCurTimeStamps()
{
	uint64_t curTime = 0;
	while (curTime < LASTTIMESTAMPS)
	{
		//UTC时间
		std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds> tp = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
		auto tmp = std::chrono::duration_cast<std::chrono::milliseconds>(tp.time_since_epoch());
		curTime = tmp.count();
	}

	if (curTime > LASTTIMESTAMPS)
	{
		LASTTIMESTAMPS = curTime;
	}
	return curTime;
}



uint64_t QATimerTask::GetMs(const TimeStamp &timeStamp)
{
	uint64_t ms = timeStamp.min * 60 * 1000 + timeStamp.s * 1000 + timeStamp.ms * m_step;
	return ms;
}

void QATimerTask::run()
{
	while (!m_bStopFlag)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(m_step));
		std::unique_lock<std::mutex> lock(m_mux);
		TimeStamp per = m_timeStamp;        //per是原来的时间
		getNextTimeStamp(m_timeStamp, m_step);      //timeStamp向后走一步
		int Pos = 0;
		if (per.min != m_timeStamp.min) //分钟进位
		{
			Pos = SECONDS_SLOT + MILLISECONDES_SLOT + m_timeStamp.min;
			std::list<Event> &listTask = m_taskList[Pos];
			if (!listTask.empty())
			{
				execuSlot(listTask);
				listTask.clear();
			}
		}
		else if (per.s != m_timeStamp.s)
		{
			Pos = MILLISECONDES_SLOT + m_timeStamp.s;
			std::list<Event> &listTask = m_taskList[Pos];
			if (!listTask.empty())
			{
				execuSlot(listTask);
				listTask.clear();
			}
		}
		else if (per.ms != m_timeStamp.ms)
		{
			Pos = m_timeStamp.ms;
			std::list<Event> &listTask = m_taskList[Pos];
			if (!listTask.empty())
			{
				execuSlot(listTask);
				listTask.clear();
			}
		}

	}
	if (m_bStopFlag)
	{
		m_bExitFlag = true;
	}
}

void QATimerTask::insertTimer(Event &event)
{
	//std::cout << "-------------------------event tri time " << event.tri_time.ToString() <<  std::endl;

	//分钟与现在不同的分钟就插入分的槽
	int Pos = 0;

	if (event.tri_time.min != m_timeStamp.min)
	{
		Pos = MILLISECONDES_SLOT + SECONDS_SLOT + event.tri_time.min;
		m_taskList[Pos].push_back(event);
	}
	else if (event.tri_time.s != m_timeStamp.s)
	{
		Pos = MILLISECONDES_SLOT + event.tri_time.s;
		m_taskList[Pos].push_back(event);
	}
	else if (event.tri_time.ms != m_timeStamp.ms)
	{
		Pos = event.tri_time.ms;
		m_taskList[Pos].push_back(event);
	}
	if (Pos != 0)
	{
		m_mapEventPos[event.taskID] = Pos;
	}

}

void QATimerTask::execuSlot(std::list<Event> &listEvent)
{
	for (auto item = listEvent.begin(); item != listEvent.end(); item++)
	{
		if (item->tri_time == m_timeStamp)  //触发时间到了
		{
			item->bStatus = true;
			item->call_back();           //执行函数
			++item->execuNum;           //已经执行次数
			item->bStatus = false;
			std::unique_lock < std::mutex> lk(m_muxEvent);
			if (m_setDelTaskID.find(item->taskID) != m_setDelTaskID.end())
			{
				m_cvEvent.notify_one();
				continue;
			}
			lk.unlock();
			if (item->count == 0 || item->execuNum < item->count)
			{
				getNextTimeStamp(item->tri_time, item->dur);
				insertTimer(*item);
			}

		}
		else
		{
			insertTimer(*item);
		}
	}
}

void QATimerTask::getNextTimeStamp(TimeStamp &timeStamp, int Dur)
{
	uint64_t ms = GetMs(timeStamp) + Dur;
	timeStamp.min = (ms / 60 / 1000) % MINUTES_SLOT;
	timeStamp.s = (ms % (1000 * 60)) / 1000;
	timeStamp.ms = (ms % 1000) / m_step;
}
