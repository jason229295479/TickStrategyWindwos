#ifndef _THREADPOOL_H_
#define _THREADPOOL_H_

#include <iostream>
#include <functional>
#include <queue>
#include <thread>
#include <mutex>
#include <atomic>
#include <list>

#include "blockingconcurrentqueue.h"

class ThreadPool
{
public:

	using TaskType = std::function<void(void)>;

	ThreadPool();

	~ThreadPool();

	void Init(int &num);

	void AddTask(std::function<void(void)> task);

	void Stop();


private:
	void workThread(); //�����߳�

	moodycamel::BlockingConcurrentQueue<std::function<void(void)>> m_TaskQue;
	std::vector<std::thread> m_VecThread;

	std::atomic<int> m_CURNUM; //��ǰ����
	std::atomic<int> m_idleNum; //�����߳�

	std::mutex  m_muxQue;
	std::condition_variable m_cvQute;
	std::atomic<bool> m_bStop;

};

class ThreadPoolUtil
{
public:
	static ThreadPool* AmqpThreadPool;
	static ThreadPool* TaskThreadPool;
	static ThreadPool* UITaskThreadPool;
	static ThreadPool* SocketThrealPool;

	static void InitThreadPool();
	
	static void StopThreadPool();
};

#endif // _THREADPOOL_H_