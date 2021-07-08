#include "ConfigTools.h"

void ReadCtpConfigFile(const char* configPath, CtpConfig& ctpConfig)
{
	//��ȡ�����ļ�
	std::ifstream ifs(configPath);
	rapidjson::IStreamWrapper isw(ifs);
	rapidjson::Document docRead;
	docRead.ParseStream(isw);
	if (docRead.HasParseError()) {
		std::cout << "error:" << docRead.GetParseError() << std::endl;
	}
	//CTP ���������
	ctpConfig.orderType = docRead["order_Type"].GetString();
	ctpConfig.account_id = docRead["account_id"].GetString();
	ctpConfig.password = docRead["password"].GetString();
	ctpConfig.broker_id = docRead["broker_id"].GetString();
	ctpConfig.td_url = docRead["td_uri"].GetString();
	ctpConfig.md_url = docRead["md_uri"].GetString();
	ctpConfig.app_id = docRead["app_id"].GetString();
	ctpConfig.auth_code = docRead["auth_code"].GetString();
	ifs.close();
	std::cout << "====================ctpConfig===================="<< std::endl;
	std::cout << "ctpConfig.orderType:" << ctpConfig.orderType << std::endl;
	std::cout << "ctpConfig.account_id:" << ctpConfig.account_id << std::endl;
	std::cout << "ctpConfig.password:" << ctpConfig.password << std::endl;
	std::cout << "ctpConfig.broker_id:" << ctpConfig.broker_id << std::endl;
	std::cout << "ctpConfig.td_url:" << ctpConfig.td_url << std::endl;
	std::cout << "ctpConfig.md_url:" << ctpConfig.md_url << std::endl;
	std::cout << "ctpConfig.app_id:" << ctpConfig.app_id << std::endl;
	std::cout << "ctpConfig.auth_code:" << ctpConfig.auth_code << std::endl;
}
void ReadPGSqlConfigFile(const char* configPath, PGSqlConfig& pgConfig)
{
	//��ȡ�����ļ�
	std::ifstream ifs(configPath);
	rapidjson::IStreamWrapper isw(ifs);
	rapidjson::Document docRead;
	docRead.ParseStream(isw);
	if (docRead.HasParseError()) {
		std::cout << "error:" << docRead.GetParseError() << std::endl;
	}
    //���ݿ� ����
	pgConfig.dbname = docRead["dbname"].GetString();
	pgConfig.dbhostaddr = docRead["dbip"].GetString();
	pgConfig.dbuser = docRead["dbuser"].GetString();
	pgConfig.dbpassword = docRead["dbpassword"].GetString();
	pgConfig.dbport = docRead["dbport"].GetString();

	std::cout << "====================pgConfig====================" << std::endl;
	std::cout << "pgConfig.dbname:" << pgConfig.dbname << std::endl;
	std::cout << "pgConfig.dbhostaddr:" << pgConfig.dbhostaddr << std::endl;
	std::cout << "pgConfig.dbuser:" << pgConfig.dbuser << std::endl;
	std::cout << "pgConfig.dbpassword:" << pgConfig.dbpassword << std::endl;
	std::cout << "pgConfig.dbport:" << pgConfig.dbport << std::endl;
	ifs.close();
}

void ReadSysConfigFile(const char* configPath, SysConfig& sysConfig)
{
	//��ȡ�����ļ�
	std::ifstream ifs(configPath);
	rapidjson::IStreamWrapper isw(ifs);
	rapidjson::Document docRead;
	docRead.ParseStream(isw);
	if (docRead.HasParseError()) {
		std::cout << "error:" << docRead.GetParseError() << std::endl;
	}
	//���ݿ� ����
	
	sysConfig.tickData_file = docRead["tickData_file"].GetString();
	sysConfig.tickModelConfig_file = docRead["tickModelConfig_file"].GetString();
	sysConfig.mainContract_file = docRead["mainContract_file"].GetString();
	sysConfig.productInfo_file = docRead["productInfo_file"].GetString();
	sysConfig.productExchange_file = docRead["productExchange_file"].GetString();
	sysConfig.cancel_file = docRead["cancel_file"].GetString();
	sysConfig.outputIndicator_file = docRead["outputIndicator_file"].GetString();
	sysConfig.pred_file = docRead["pred_file"].GetString();
	sysConfig.tradeLog_file = docRead["tradeLog_file"].GetString();
	sysConfig.mdLog_file = docRead["mdLog_file"].GetString();
	ifs.close();
	std::cout << "====================sysConfig====================" << std::endl;
	std::cout << "sysConfig.tickData_file:" << sysConfig.tickData_file << std::endl;
	std::cout << "sysConfig.tickModelConfig_file:" << sysConfig.tickModelConfig_file << std::endl;
	std::cout << "sysConfig.mainContract_file:" << sysConfig.mainContract_file << std::endl;
	std::cout << "sysConfig.productInfo_file:" << sysConfig.productInfo_file << std::endl;
	std::cout << "sysConfig.productExchange_file:" << sysConfig.productExchange_file << std::endl;
	std::cout << "sysConfig.outputIndicator_file:" << sysConfig.outputIndicator_file << std::endl;
	std::cout << "sysConfig.pred_file:" << sysConfig.pred_file << std::endl;
	std::cout << "sysConfig.tradeLog_file:" << sysConfig.tradeLog_file << std::endl;
	std::cout << "sysConfig.mdLog_file:" << sysConfig.mdLog_file << std::endl;
}

void InitPostgresql(PGSqlConfig& pgConfig, std::list<CodeInfo_s> &listCodes)
{
	std::cout << "====================InitPostgresql====================" << std::endl;
	const std::string connstr = "dbname=" + pgConfig.dbname + " " + "user=" + pgConfig.dbuser + " " + "password=" + pgConfig.dbpassword + " " + "hostaddr=" + pgConfig.dbhostaddr + " " + "port=" + pgConfig.dbport;
	//  std::cout << "connstr: " << connstr << std::endl;
	try {
		PGconn* conn = PQconnectdb(connstr.c_str());
		if (PQstatus(conn) == CONNECTION_BAD)
		{
			std::cout << "...Can't open database..." << std::endl;
			PQfinish(conn);
		}
		else
		{
			std::cout << "hostaddr:" << pgConfig.dbhostaddr << std::endl;;
			std::cout << "...Opened database successfully..." << std::endl;
		}
		char  sql[128] = "select * from contract";
		//PQexecִ�����
		PGresult* res = PQexec(conn, sql);
		CodeInfo_s codeInfo_s;
		std::string strType;
		for (int i = 0; i < PQntuples(res); i++) {
			strType = PQgetvalue(res, i, 6);
			if (strType == "general"|| strType == "real_main")
			{
				codeInfo_s.strCode = PQgetvalue(res, i, 0);
				codeInfo_s.strMarket = PQgetvalue(res, i, 1);
				codeInfo_s.strName = PQgetvalue(res, i, 2);
				codeInfo_s.dbUnit = atof(PQgetvalue(res, i, 3));
				codeInfo_s.dbMult = atof(PQgetvalue(res, i, 4));
				codeInfo_s.strRoot = PQgetvalue(res, i, 5);
				codeInfo_s.strType = PQgetvalue(res, i, 6);
				listCodes.push_back(codeInfo_s);
			}

		}

		PQfinish(conn);
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;

	}
}


