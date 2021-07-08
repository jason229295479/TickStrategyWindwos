#pragma once
#ifndef QUOTE_SERVICE_H
#define QUOTE_SERVICE_H

#define THOST_FTDC_TC_IOC '1'
#define THOST_FTDC_TC_GFD '3'

#include "GenData.h"

#include "blockingconcurrentqueue.h"
#include "orderBook.h"
#include "linear.h"
#include "indicator.h"

#include "CtpMD.h"
#include "CtpTD.h"

#include <functional>
#include <vector>
#include <thread>
#include <iostream>
#include <sstream>
#include <fstream>
#include <list>
#include <map>
#include <io.h>
#include <direct.h>

class QuoteService
{
public:
	QuoteService();
	~QuoteService();
	//��ʼ��Ctp,��½���飬����
	void InitCtpConfig(CtpConfig& ctpConfig, SysConfig& sysConfig);
	//��ʼ��ϵͳ�����ļ�����ȡ������Լ�����Ϣ
	void InitSysConfig(SysConfig& sysConfig, CtpConfig& ctpConfig);
	//��ʼ��tick����������Ϣ
	void InitTickStrategyConfig(SysConfig& sysConfig);


	void StartTask();
	void PushQue();
	void DealDepthMarketData(RtData_s& rtData);
	void GetCodeList(std::list<CodeInfo_s>& listCodes);
	
	
	void WriteTickToCsv(std::string fileName,
		std::string date,
		std::string time,
		int iUpdateMillisec,
		std::string contract,double& pred);

	void WriteTickTpToCsv(std::string fileName, time_pre_value & tp);

	void OutPut(SysConfig& sysConfig);
	void MarketLog(const char* FilePath);
	std::string getTime();
public:
	void listModelFiles(const char* dir);
	void listFiles(char* dir, std::string& dirName);
	std::string getFileName(const char* dirPath);
private:
	std::map<std::string, std::map<std::string, modeConfigFile>> mapProduct;
	std::map<std::string, modeConfigFile> mapModel;
public:
	inline void NewTick(NewData_s &newData, RtData_s& rtData)
	{
		newData.ActionDay = rtData.strActionDay;
		newData.UpdateTime = rtData.UpdateTime;
		newData.StrCode = rtData.strCode;
		newData.LastPrice = rtData.dbLastPrice;
		newData.NewVolume = (int)rtData.dbVolume - newData.NewVolume;
		newData.NewTrunover = rtData.dbTurnover - newData.NewTrunover;
		newData.OpenInterest = rtData.dbOpenInterest;
		newData.PreClosePrice = rtData.dbPreClosePrice;
		newData.BidPrice[0] = rtData.vecBidPrice[0];
		newData.AskPrice[0] = rtData.vecAskPrice[0];
		newData.BidVolume[0] = rtData.vecBidVolume[0];
		newData.AskVolume[0] = rtData.vecAskVolume[0];

		if (fabs(rtData.dbUpperLimitPrice - rtData.vecBidPrice[0]) < 1e-6)
			newData.AskPrice[0] = 0; // upper limit
		else if (fabs(rtData.dbLowerLimitPrice - rtData.vecAskPrice[0]) < 1e-6)
			newData.BidPrice[0] = 0; // lower limit
	}
private:
	CtpMD* md = NULL;
	CtpTD* td = NULL;
	bool m_realTrade = false; // trade started or not
	std::vector<std::thread> m_thDepthMarketData;
	moodycamel::BlockingConcurrentQueue<RtData_s> m_QueueRtdata; //��Ч��������
	
	std::map <std::string, ContractInfo> m_mapContracttInfo;
	//��Լ�б� map<��Լ���룬������>
	std::map<std::string, std::string> m_mapMarket;
	//��Լ�б� map<Ʒ�֣�������>
	//std::map<std::string, std::string> m_exchangeID;
	std::map<std::string, TThostFtdcExchangeIDType> m_exchangeID;
	//��Լ�б� map<Ʒ�֣���Լ����>
	std::map<std::string, int> m_multiplier;
	//��Լ�б� map<Ʒ�֣���С�䶯��λ>
	std::map<std::string, double> m_spread;
	//��Լ�б� map<Ʒ�֣��Զ��屶��>
	std::map<std::string, int> m_intFactor;
	//��Լ�б� map<Ʒ�֣�ҹ������>
	std::map<std::string, std::string> m_nightEnd;
	//��Լ�б� map<Ʒ�֣���������>
	std::map<std::string, std::string> m_afternoon;
	//��Լ�б� map<Ʒ�֣�����>
	std::map<std::string, std::string> m_clearTime;

	std::vector<std::string> m_instrument; // vector of contract to subscribte
	std::vector<double> m_turnover; // accumulative turnover of each contract
	std::vector<int> m_qty; // accumulative volune of each contract
	std::map<std::string, double> m_iniTurnover;
	std::map<std::string, int> m_iniQty;
	std::map<std::string, std::string> m_contractProduct; // contract->product
	std::map<std::string, int> m_lastCancel;
	std::map<std::string, bool> m_closeIntraday; // whether a contract should close intraday
	std::map<std::string, int> m_contractIndex; // index of the contract
	std::map<std::string, std::string> m_exchange; // the exchange thsi contract belong to 1: shanghai, 2:dalian, 3: zhengzhou, 4:zhongjin

	std::vector<BookPtr> m_bookPtr; // pointer to order book
	std::map<std::string,std::vector<BookPtr>> map_bookPtr; // pointer to order book
	std::vector<IndicatorPtr> m_signalPtr; // pointer to signal
	std::map<std::string,std::vector<IndicatorPtr>> map_signalPtr; // pointer to signal
	std::vector<LinearPtr> m_linearPtr; // pointer to linear model
	std::map<std::string,std::vector<LinearPtr>> map_linearPtr; // pointer to linear model
	std::map<std::string, std::vector<time_pre_value>> Pre_value_map;

	
	std::list<std::map<std::string, std::map<std::string, modeConfigFile>>> fileListModel; //ģ���б�
	std::ofstream m_marketLog;
	std::string pred_csv;
	std::string tp_csv;
	std::string dateFile;
	char m_orderType=NULL;
	int tLong=0;
	int tShort=0;
	int curPos=0;


	std::map<std::string, std::vector<BookPtr>>::iterator itr_mapBookPtr;
	std::vector<BookPtr>::iterator itr_BookPtr;

//	std::vector<IndicatorPtr>::iterator itr_SignalPtr; // pointer to signal
	std::map<std::string, std::vector<IndicatorPtr>>::iterator itr_mapSignalPtr; // pointer to signal

//	std::vector<LinearPtr>::iterator itr_linearPtr; // pointer to linear model
	std::map<std::string, std::vector<LinearPtr>>::iterator itr_maplinearPtr; // pointer to linear model

	
	string pre_value_date;
	std::string contract;
};




#endif // !QUOTE_SERVICE_H
