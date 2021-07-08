#include "ThreadPool.h"

#include "QAProperties.h"

ThreadPool::ThreadPool()
{

}

ThreadPool::~ThreadPool()
{
// 	std::unique_lock<std::mutex> lk(m_muxQue);
// 	while (!m_TaskQue.empty()) {
// 		m_TaskQue.pop_back();
// 	}
// 	m_cvQute.notify_all();
// 	lk.unlock();

	for (std::thread& th : m_VecThread)
	{
		if (th.joinable())
		{
			th.join();
		}
	}
}


void ThreadPool::Init(int &num)
{
	m_idleNum = num;
	m_CURNUM = num;
	m_bStop = false;
	for (int i = 0; i < m_idleNum; i++)
	{
		//初始化线程数量
		m_VecThread.emplace_back(std::bind(&ThreadPool::workThread, this));
	}

}

void ThreadPool::AddTask(std::function<void(void)> task)
{
	if (m_bStop)
	{
		return;
	}
	//std::unique_lock<std::mutex> lk(m_muxQue);
	//m_TaskQue.emplace_back(std::move(task));
	//m_cvQute.notify_one();
	m_TaskQue.enqueue(task);
}

void ThreadPool::Stop()
{
	m_bStop = true;
}

void ThreadPool::workThread()
{
	while (1)
	{
// 		std::unique_lock<std::mutex> lock(m_muxQue);
// 		if (m_TaskQue.empty())
// 		{
// 			m_cvQute.wait(lock, [this]() {
// 				return (!m_TaskQue.empty() || m_bStop);
// 			});
// 		}
// 		if (m_bStop) {
// 			return;
// 		}
		TaskType task;
		bool bTake = m_TaskQue.wait_dequeue_timed(task, std::chrono::milliseconds(50));
		if (m_bStop)
		{
			return;
		}
		//m_TaskQue.pop_back();
		//std::cout << "work "  << m_TaskQue.size() << std::endl;
		//lock.unlock();
		if (task != nullptr)
		{
			--m_idleNum;
			task();
			++m_idleNum;
		}
	}
}

ThreadPool* ThreadPoolUtil::AmqpThreadPool = nullptr;
ThreadPool* ThreadPoolUtil::TaskThreadPool = nullptr;
ThreadPool* ThreadPoolUtil::UITaskThreadPool = nullptr;
ThreadPool* ThreadPoolUtil::SocketThrealPool = nullptr;
void ThreadPoolUtil::InitThreadPool()
{
	AmqpThreadPool = new ThreadPool();
	TaskThreadPool = new ThreadPool();
	UITaskThreadPool = new ThreadPool();
	SocketThrealPool = new ThreadPool();
	int num = std::thread::hardware_concurrency();
	int iNum = QAProperties::GetValueInt("thread.num");
	if (iNum != 0)
	{
		num = iNum;
	}
	AmqpThreadPool->Init(num);
	TaskThreadPool->Init(num);
	UITaskThreadPool->Init(num);
	SocketThrealPool->Init(num);
}

void ThreadPoolUtil::StopThreadPool()
{
	AmqpThreadPool->Stop();
	TaskThreadPool->Stop();
	UITaskThreadPool->Stop();
	SocketThrealPool->Stop();

	delete AmqpThreadPool;
	AmqpThreadPool = nullptr;

	delete TaskThreadPool;
	TaskThreadPool = nullptr;

	delete UITaskThreadPool;
	UITaskThreadPool = nullptr;

	delete SocketThrealPool;
	SocketThrealPool = nullptr;
}
