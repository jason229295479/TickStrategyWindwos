
#include "JsonTools.h"
#include "ConfigTools.h"
#include "QuoteService.h"

#include <fstream>
#include <string>
#include <thread>
#include <list>
#include <map>
#include <iostream>

int main()
{
    CtpConfig ctpConfig;
    PGSqlConfig pgConfig;
    SysConfig sysConfig;
    //��ȡpg���ݿ������ļ�
    ReadPGSqlConfigFile("input/sysConfig/pgsql_config.json", pgConfig);
    //��½���ݿ�pg ��ȡ��Լ�б�
    std::list<CodeInfo_s> listCodes;
    InitPostgresql(pgConfig, listCodes);

    //��ȡtick����ģ�������ļ�
    ReadSysConfigFile("input/sysConfig/sys_config.json", sysConfig);
    
    //��ȡctp�����ļ�
    ReadCtpConfigFile("input/sysConfig/ctp_config.json", ctpConfig);
   
    QuoteService* quoteService = new QuoteService();
    quoteService->GetCodeList(listCodes);

    quoteService->InitSysConfig(sysConfig, ctpConfig);
    quoteService->InitTickStrategyConfig(sysConfig);
    quoteService->InitCtpConfig(ctpConfig,sysConfig);
    
    char action;
    while (true) {
        cout << "enter s to end" << endl;
        cin >> action;
        if (action == 's' || action == 'S')
            //getMarket.join();
            break;
    }
//    quoteService->OutPut(sysConfig);
   
    return 0;
}
 