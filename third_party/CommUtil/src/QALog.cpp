#include "QALog.h"
#include "boost/filesystem.hpp"
std::string QALog::LOGGERNAME = "QAlog";
spdlog::async_logger* QALog::PTRLOGGER = nullptr;



void QALog::Init(spdlog::level::level_enum log_level/*= spdlog::level::debug*/)
{
	if (spdlog::get(LOGGERNAME) != nullptr)
	{
		return;
	}
	try
	{
		std::string strLogDir = "./log";
		std::string strFile = strLogDir + "/log.txt";
		if (!boost::filesystem::exists(strLogDir))
		{
			boost::filesystem::create_directory(strLogDir);
		}
		spdlog::init_thread_pool(8192, 1);
		auto stdout_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt >();
		auto rotating_sink = std::make_shared<spdlog::sinks::daily_file_sink_mt>(strFile, 11, 18);
		std::vector<spdlog::sink_ptr> vecSinks{ stdout_sink, rotating_sink };
		PTRLOGGER = new spdlog::async_logger(LOGGERNAME, vecSinks.begin(), vecSinks.end(), spdlog::thread_pool(), spdlog::async_overflow_policy::block);
		spdlog::register_logger(std::shared_ptr<spdlog::async_logger>(PTRLOGGER));
		spdlog::set_pattern("[%H:%M:%S %X.%e][%n][%s][thread_id %t][%^%l%$] %v");
		PTRLOGGER->set_level(log_level);
		PTRLOGGER->flush_on(spdlog::level::err);
		PTRLOGGER->info("--------- init log -------------");
	}
	catch (...)
	{
		PTRLOGGER = nullptr;
	}

}
spdlog::logger* QALog::GetInstance()
{
	return PTRLOGGER;
}

void QALog::Destroy()
{
	PTRLOGGER->info("-------End log ---------");

	spdlog::drop_all();
	PTRLOGGER = nullptr;
}