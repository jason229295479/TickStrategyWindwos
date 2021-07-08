#pragma once
#ifndef CTP_TD_H
#define CTP_TD_H
#include "ThostFtdcTraderApi.h"
#include "GenData.h"
#include <mutex>
#include <fstream>
#include <time.h>
#include <ctime>
#include <thread>
#include <map>
#include <iostream>
#include <algorithm>
#include <list>
# include <sstream>
/*
����������
�̳�CThostFtdcTraderSpiʵ���Լ�������ص���CtpTD
*/

const int MAX_INSTRUMENT = 100;
class CtpTD : public CThostFtdcTraderSpi {
public:
	CtpTD();
	~CtpTD();

	///���ͻ����뽻�׺�̨������ͨ������ʱ����δ��¼ǰ�����÷��������á�
	virtual void OnFrontConnected();

	///���ͻ����뽻�׺�̨ͨ�����ӶϿ�ʱ���÷��������á���������������API���Զ��������ӣ��ͻ��˿ɲ�������
	///@param nReason ����ԭ��
	///        0x1001 �����ʧ��
	///        0x1002 ����дʧ��
	///        0x2001 ����������ʱ
	///        0x2002 ��������ʧ��
	///        0x2003 �յ�������
	virtual void OnFrontDisconnected(int nReason);

	///������ʱ���档����ʱ��δ�յ�����ʱ���÷��������á�
	///@param nTimeLapse �����ϴν��ձ��ĵ�ʱ��
	virtual void OnHeartBeatWarning(int nTimeLapse);

	///�ͻ�����֤��Ӧ
	virtual void OnRspAuthenticate(CThostFtdcRspAuthenticateField* pRspAuthenticateField, 
		CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);
	///��¼������Ӧ
	virtual void OnRspUserLogin(CThostFtdcRspUserLoginField* pRspUserLogin, 
		CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);
	///Ͷ���߽�����ȷ����Ӧ
	virtual void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField* pSettlementInfoConfirm, 
		CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);
	///�ǳ�������Ӧ
	virtual void OnRspUserLogout(CThostFtdcUserLogoutField* pUserLogout, 
		CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);
	///����Ӧ��
	virtual void OnRspError(CThostFtdcRspInfoField* pRspInfo, int nRequestID,
		bool bIsLast);
	///�����ѯ��Լ��Ӧ
	virtual void OnRspQryInstrument(CThostFtdcInstrumentField* pInstrument, 
		CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);
	///�����ѯ�ʽ��˻���Ӧ
	virtual void OnRspQryTradingAccount(CThostFtdcTradingAccountField* pTradingAccount,
		CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);
	///�����ѯͶ���ֲ߳���Ӧ
	virtual void OnRspQryInvestorPosition(CThostFtdcInvestorPositionField* pInvestorPosition, 
		CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);
	/////����¼��������Ӧ
	virtual void OnRspOrderInsert(CThostFtdcInputOrderField* pInputOrder, 
		CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);
	
	//ί�б���֪ͨ
	virtual void OnRtnOrder(CThostFtdcOrderField* pOrder);

	//�ɽ�֪ͨ
	virtual void OnRtnTrade(CThostFtdcTradeField* pTrade);
public:
	void GetMainContractInfo(const char* configPath);
	void GetCancelFile(const char* configPath);
	//����
	void reqOrderAction(CThostFtdcOrderField* pOrder);
	//����
	void reqOrderInsert(Orders_s& orderData);
	
public:
	void Init(CtpConfig& ctpconfig);
	void TradetLog(const char* FilePath);
public:
	std::string front_uri_;
	std::string broker_id_;
	std::string account_id_;
	std::string password_;
	std::string app_id_;
	std::string auth_code_;
	std::string tradingDate; //������
	std::map<std::string, int> m_sentCancel;
	std::map<std::string, int> m_cancelCount; // count the cancelation number of each instrument
	std::map<std::string, int> m_yesterdayLong; // yesterday long position of each instrument
	std::map<std::string, int> m_yesterdayShort; // yesterday short position of each instrument
	std::map<std::string, int> m_todayLong; // today long position of each instrument
	std::map<std::string, int> m_todayShort; // today short position of each instrument
	int m_instrumentNum=0; // number of instruments
	char* m_instrumentID[MAX_INSTRUMENT]; // to send subscribe;
	std::vector<std::string> orderRefs;
	std::map<std::string, CThostFtdcOrderField*> m_activeOrder; /// current active(not canceled or fully traded) order of each instrument
	std::map<std::string, CThostFtdcOrderField*> m_sentOrder; /// current active(not canceled or fully traded) order of each instrument
	std::map<std::string, int> m_count; // counting of ticks of each instrument
	
	std::map<std::string, int> m_remainQty; // remaining qty of each instrument ��Լ��Ӧ��ί������
	bool m_finishPos = false; // whether finish reading historical position
	bool m_mytrade=false;
private:
	
	TThostFtdcOrderRefType	m_orderRef;
	CThostFtdcQryInvestorPositionField m_positionReq; // request for position
	CThostFtdcInputOrderActionField m_orderActionReq; // this is used to cancel an order
	CThostFtdcInputOrderField m_orderInsertReq;
	TThostFtdcFrontIDType	m_tradeFrontID;
	TThostFtdcSessionIDType	m_sessionID;
private:
	std::fstream m_log;
	CThostFtdcTraderApi* m_tdapi = nullptr;

	int m_requestID;
	bool m_loginFlag = false;
	int m_maxOrderRef; // the current maximum order reference
	char m_currentTime[87] = {0}; // current time

	std::list<CodeInfo_s> m_listCode;
	//��͸ʽ��֤����
	void reqAuthenticate();
	//��½
	void reqUserlogin();
	//��ʼ��ί������
	void setOrderInfo(CThostFtdcRspUserLoginField* pRspUserLogin);

	//��ѯͶ���߽���������
	void reqSettlementInfoConfirm();
	//�����ѯ�ʽ��˻�
	void reqQueryTradingAccount();
	//�����ѯ��Լ����տ��Բ�ѯ�����к�Լ��
	void reqQryInstrument();
	
	void reqQueryInvestorPosition(const char* brokerID, const char* InvestorID);
	bool isMyOrder(CThostFtdcOrderField* pOrder);
	bool isTradingOrder(CThostFtdcOrderField* pOrder);
	bool isMyTrader(std::vector<std::string> orderRefs, CThostFtdcTradeField* pTrade);
	//������Ϣ
	bool isErrorRspInfo(CThostFtdcRspInfoField* pRspInfo);
	void getTime();

	
	
	//������ ��
	std::mutex m_muxLogin;   
	std::mutex m_muxReq;
	std::mutex m_muxAccount;
	std::mutex m_muxIns;
	std::mutex m_muxPos;
	std::mutex m_muxTrade;
	std::mutex m_muxOrder;
	std::condition_variable m_cvLogin;
};


#endif // !CTP_TD_H
