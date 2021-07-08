#ifndef _QALOG_H_
#define  _QALOG_H_

#include <iostream>
#include <thread>
#include "spdlog/spdlog.h"
#include "spdlog/async.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/daily_file_sink.h"
#include "Singleton.h"

/*
日志对象
*/
class QALog
{
public:
	static void Init(spdlog::level::level_enum log_level = spdlog::level::debug);
	
	//先Init初始化日志对象
	static spdlog::logger* GetInstance();
		
	QALog() {}

	~QALog() 
	{
		if (PTRLOGGER != nullptr)
		{
			delete PTRLOGGER;
			PTRLOGGER = nullptr;
		}
	}
	static void Destroy();
	
private:
	static std::string LOGGERNAME;
	static spdlog::async_logger* PTRLOGGER;
};

#endif // _QALOG_H_
