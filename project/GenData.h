#pragma once
#ifndef GEN_DATA_H
#define GEN_DATA_H
#include <string>
#include <vector>

const int TICK_NUM = 66606; // maximum number fo ticks per day, for example the au and ag reaches this number theoretically
struct SysConfig
{
	
	std::string tickData_file;
	std::string tickModelConfig_file;
	std::string mainContract_file;
	std::string productInfo_file;
	std::string productExchange_file;
	std::string cancel_file;
	std::string outputIndicator_file;
	std::string pred_file;
	std::string tradeLog_file;
	std::string mdLog_file;
	
};
struct CtpConfig
{
	std::string account_id;
	std::string password;
	std::string broker_id;
	std::string td_url;
	std::string md_url;
	std::string app_id;
	std::string auth_code;
	std::string orderType;
};

struct ContractInfo
{	//Ʒ��
	std::string Product;
	//��Լ����
	std::string Contract;
	//����
	std::string Intraday;
	//������
	std::string ExchangeID;
	//��Լ��������
	int VolumeMultiple;
	///��С�䶯��λ
	double PriceTick;
	//�Զ��屶��
	int Factor;
	//ҹ������ʱ��
	std::string NightEnd;
	//��������ʱ��
	std::string Afternoon;
	//����ʱ��
	std::string ClearTime;
	

	ContractInfo()
		: VolumeMultiple(0)
		, PriceTick(0)
		, Factor(0)
	{}
	bool operator == (const ContractInfo& src) const
	{
		if (Product == src.Product)
		{
			return true;
		}
		return false;
	}
	bool operator != (const ContractInfo& src) const
	{
		if (*this == src)
		{
			return false;
		}
		return true;
	}
};



struct PGSqlConfig
{
	//���ݿ� ����
	std::string dbname;
	std::string dbhostaddr;
	std::string dbuser;
	std::string dbpassword;
	std::string dbport;
};
enum CodeType_e
{

	FUT_INDEX = 0, //�ڻ�ָ��
	FUTURE = 1, //��ͨ��Լ
	FUT_MAIN = 2, //����
	A_STOCK = 3, //A��
	B_STOCK = 4, //B��
	STOCK_INDEX = 5, //��Ʊָ��

};
//��Լ��Ϣ
struct CodeInfo_s
{
	std::string strCode; //��Լ
	std::string strMarket; //�г�
	std::string strName; //��Լ����
	std::string strShortName; //���
	std::string strLastDay; //��������
	std::string strListDay; //��������
	std::string strRoot; //Ʒ��
	std::string strRootName; //Ʒ������
	std::string strType;//����
	double dbMult; //��Լ����
	double dbUnit; //��С�䶯��λ
	CodeType_e eType; //����
	CodeInfo_s()
		: dbMult(0)
		, dbUnit(0)
	{}
};
struct RtData_s
{
	///������
	std::string strDate; //0
	///����������
	std::string strCode; //1
	///������
	std::string strMarket; //2
	///���¼�
	double dbLastPrice; //3
	///�ϴν����
	double dbPreSettlePrice;//4
	///������
	double dbPreClosePrice; //5
	///��ֲ���
	double dbPreOpenInterest; //6
	///����
	double dbOpenPrice;
	///��߼�
	double dbHighestPrice;
	///��ͼ�
	double dbLowestPrice;
	///����
	double dbVolume; //10
	///����
	double dbVolumeTick;
	///�ɽ����
	double dbTurnover;
	///�ֲ���
	double dbOpenInterest; //13
	///������
	double dbClosePrice;
	///���ν����
	double dbSettlePrice;
	///��ͣ���
	double dbUpperLimitPrice;
	///��ͣ���
	double dbLowerLimitPrice;
	///����ʵ��
	double dbPreDelta;
	///����ʵ��
	double dbCurDelta;
	///����޸�ʱ��
	std::string UpdateTime;
	//����޸ĺ���
	int iUpdateMillisec;
	///�����
	std::vector<double> vecBidPrice;
	///������
	std::vector<double> vecBidVolume;
	//������
	std::vector<double> vecAskPrice;
	///������
	std::vector<double> vecAskVolume; //25
	///���վ���
	double dbAveragePrice;
	///ҵ������
	std::string strActionDay;


	RtData_s()
		: dbLastPrice(0)
		, dbPreSettlePrice(0)
		, dbPreClosePrice(0)
		, dbPreOpenInterest(0)
		, dbOpenPrice(0)
		, dbHighestPrice(0)
		, dbLowestPrice(0)
		, dbVolume(0)
		, dbVolumeTick(0)
		, dbTurnover(0)
		, dbOpenInterest(0)
		, dbClosePrice(0)
		, dbSettlePrice(0)
		, dbUpperLimitPrice(0)
		, dbLowerLimitPrice(0)
		, dbPreDelta(0)
		, dbCurDelta(0)
		, iUpdateMillisec(0)
		, dbAveragePrice(0)
	{
		vecBidPrice.resize(5);
		vecBidVolume.resize(5);
		vecAskPrice.resize(5);
		vecAskVolume.resize(5);
	}

	bool operator == (const RtData_s& rtData) const
	{
		if (dbSettlePrice == rtData.dbSettlePrice && dbVolume == rtData.dbVolume
			&& dbOpenInterest == rtData.dbOpenInterest && dbLastPrice == rtData.dbLastPrice && dbTurnover == rtData.dbTurnover &&
			vecAskPrice[0] == rtData.vecAskPrice[0] && vecAskVolume[0] == rtData.vecAskVolume[0] &&
			vecBidPrice[0] == rtData.vecBidPrice[0] && vecBidVolume[0] == rtData.vecBidVolume[0])
		{
			return true;
		}
		return false;
	}
};
/*
//�����ҳ�ʼ��ָ��ṹ��
struct IndicatorPara {
	int period;
	double lambda;
	double threshold;
	double shortLambda;
	bool adjust;

	IndicatorPara()
		:period(0)
		, lambda(0)
		, threshold(0)
		, shortLambda(0)
		, adjust(false)
	{}
};
*/


struct time_v
{
	std::string p_date;
	std::string p_time;
	double ask;
	double askqty;
	double bid;
	double bidqty;
	double turnover;
	double qty;
	double buytrade;
	double selltrade;
	double buy2trade;
	double sell2trade;
	double price;
	double resulthigh;
	double resultlow;
	double inthigh;
	double intlow;
	double aa;
	time_v()
		:ask(0)
		,askqty(0)
		,bid(0)
		,bidqty(0)
		,turnover(0)
		,qty(0)
		,buytrade(0)
		,selltrade(0)
		,buy2trade(0)
		,sell2trade(0)
		,price(0)
		,resulthigh(0)
		,resultlow(0)
		,inthigh(0)
		,intlow(0)
		,aa(0)
	{}
};


struct time_pre_value
{
	double prediction_value;
	std::string p_date;
	std::string p_time;
	double ask;
	double askqty;
	double bid;
	double bidqty;
	double turnover;
	double qty;
	double buytrade;
	double selltrade;
	double buy2trade;
	double sell2trade;
	double price;
	double resulthigh;
	double resultlow;
	double inthigh;
	double intlow;
	double resultlow2;
	double resulthigh2;
	time_pre_value()
		:prediction_value(0)
		,ask(0)
		,askqty(0)
		,bid(0)
		,bidqty(0)
		,turnover(0)
		,qty(0)
		,buytrade(0)
		,selltrade(0)
		,buy2trade(0)
		,sell2trade(0)
		,price(0)
		,resulthigh(0)
		,resultlow(0)
		,inthigh(0)
		,intlow(0)
		,resultlow2(0)
		,resulthigh2(0)
	{}

};


struct TradeThre {
	double open;
	double close;
	int qty;
	TradeThre()
		:open(0)
		,close(0)
		,qty(0)
	{}
};

//��������
enum Direction_e
{
	DIREC_NA = 0,
	DIREC_Buy=1,  //��
	DIREC_Sell=2 //��
};
//��ƽ
enum OffSetFlag_e
{
	OFFSET_NA = 0,
	OFFSET_Open = 1, //��
	OFFSET_Close = 2, //ƽ
	OFFSET_CloseYestoday = 3, //ƽ��
	OFFSET_CloseToday = 4, //ƽ��
	OFFSET_ForceOff = 5, //ǿ��
	OFFSET_LOCALForceClose = 6 //����ǿƽ
};

enum HedgeFlag_e
{
	HedgeFlag_Spe = 0, //Ͷ��
	HedgeFlag_Arbitrage = 2,//����
	HedgeFlag_Hedge = 3,//�ױ�
	HedgeFlag_MarketMaker = 4 //������
};

enum OrderPriceType_e
{
	MarketPrice = 0, //�м�
	LimitPrice = 1, //�޼�
	LastPrice = 2 //���¼�
};

enum OrderSubmitStatus_e
{
	//�Ѿ��ύ
	Order_InsertSubmitted = 0,
	//�����Ѿ��ύ
	Order_CancelSubmitted = 1,
	//�޸��Ѿ��Ѿ�
	Order_ModifySubmitted = 2,
	//�Ѿ�����
	Order_Accepted = 3,
	//�������ܾ�
	Order_InsertRejuected = 4,
	//�������ܾ�
	Order_CancelRejuected = 5,
	//�ĵ����ܾ�
	Order_ModifyRejuected = 6
};

enum OrderStatus_e
{
	//ȫ���ɽ�
	Order_ALLTraded = 0,
	//���ֳɽ����ڶ�����
	Order_PartTradedQueueing = 1,
	///���ֳɽ����ڶ�����
	Order_PartTradedNotQueueing = 2,
	//δ�ɽ����ڶ�����
	Order_NoTradeQueueing = 3,
	//δ�ɽ����ڶ�����
	Order_NoTradeNotQueueing = 4,
	//����
	Order_Canceled = 5,
	//�ɽ�
	Order_Unknown = 6,
	//��δ����
	Order_NotTouched = 7,
	//�Ѵ���
	Order_Touched = 8,
	//�������ܾ�
	Order_Reject = 9,
	//���ֳɽ�
	Order_PartTrade = 10
};
enum OrderForceType_e
{
	Force_Not = 0, //��ǿƽ
	Force_LackDeposit = 1 //�ʽ���
};
//��Ч������
enum TimeConditionType_e
{
	///������ɣ�������
	FTDC_TC_IOC = 1,
	///������Ч
	FTDC_TC_GFS = 2,
	///������Ч
	FTDC_TC_GFD = 3,
	///ָ������ǰ��Ч
	FTDC_TC_GTD = 4,
	///����ǰ��Ч
	FTDC_TC_GTC = 5,
	///���Ͼ�����Ч
	FTDC_TC_GFA = 6
};
//ί�е�
struct Orders_s
{
	
	//��Լ
	std::string strCode;
	//������
	std::string strMarket;
	//������ţ����������أ�
	std::string strOrderThirdID;
	//��������
	std::string strOrderRef;
	//����
	Direction_e eDirection;
	//��ƽ
	OffSetFlag_e eOffSetFlag;
	//Ͷ��
	HedgeFlag_e eHedgeFlage;
	//�۸�����
	OrderPriceType_e ePriceType;
	

	
	int intVolume; //ί������

	//ί�м۸�
	double dbPrice;
	//�ɽ�����
	double dbTradeVolume;
	//������
	std::string strTradingDay;
	//��������
	std::string strInsertData;
	//ί��ʱ��
	std::string strInsertTime;
	//����ʱ��
	std::string strUpdateTime;
	//����ʱ��
	std::string strCancelTime;
	//�����ύ״̬
	OrderSubmitStatus_e eSubmitStatus;
	//����״̬
	OrderStatus_e eStatus;
	//��������
	std::string strNotice;
	//������Դ
	std::string strOrderSource;
	//������
	int64_t iSettlementID;
	//ǿƽԭ��
	OrderForceType_e eForceClose;
	TimeConditionType_e eTimeConditionType;


		Orders_s()
		: dbPrice(0)
		, intVolume(0)
		, dbTradeVolume(0)
		, iSettlementID(0)
	{}
};



//�޸�tick����

struct NewData_s
{
	std::string ActionDay;	//ҵ������
	///����޸�ʱ��
	std::string UpdateTime;
	//����޸ĺ���
	int UpdateMillisec;
	std::string StrCode;
	//���¼�
	double LastPrice;
	//tick ��ǰ�ɽ���
	int NewVolume;
	//��ǰ�ɽ����
	double NewTrunover;
	//�ֲ���
	double OpenInterest;
	//�������̼�
	double PreClosePrice;
	//�����
	std::vector<double> BidPrice;
	//������
	std::vector<double> BidVolume;
	//������
	std::vector<double> AskPrice;
	//������
	std::vector<double> AskVolume; 

	double m_mid;
	double m_buyTrade;// estimated active buy volume at best ask ������1
	double m_sellTrade;// estimated active sell volume at best bid ������1
	double m_buy2Trade;// estimated active buy volume at higher ask ������2
	double m_sell2Trade;//  estimated active sell volume at lower bid ������2


	NewData_s()
		: UpdateMillisec(0)
		, LastPrice(0)
		, NewVolume(0)
		, NewTrunover(0)
		, OpenInterest(0)
		, PreClosePrice(0)
		, m_mid(0)
		, m_buyTrade(0)
		, m_sellTrade(0)
		, m_buy2Trade(0)
		, m_sell2Trade(0)
	{
		BidPrice.resize(5);
		BidVolume.resize(5);
		AskPrice.resize(5);
		AskVolume.resize(5);
	}
};


struct modeConfigFile
{
	std::string model = "model.txt";
	std::string position = "position.txt";
	std::string signal = "signal.txt";
	std::string threshold = "threshold.txt";
};
#endif // !GEN_DATA_H



