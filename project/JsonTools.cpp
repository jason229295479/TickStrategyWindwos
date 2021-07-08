#include "JsonTools.h"

void readFromJson(std::vector <CThostFtdcInstrumentField>& instruments, std::string& filePath) {
    std::ifstream ifs(filePath);
    rapidjson::IStreamWrapper isw(ifs);

    rapidjson::Document docRead;
    docRead.ParseStream(isw);
    if (docRead.HasParseError()) {
        std::cout << "error" << std::endl;
    }
    if (docRead.IsArray()) {
        rapidjson::Value::Array instrumentArr = docRead.GetArray();
        int lengthOfInstrument = instrumentArr.Size();
        for (int i = 0; i < lengthOfInstrument; i++) {
            CThostFtdcInstrumentField field;
            memset(&field, 0, sizeof(CThostFtdcInstrumentField));
            strncpy_s(field.InstrumentID, instrumentArr[i]["InstrumentID"].GetString(), sizeof(field.InstrumentID));
            strncpy_s(field.ExchangeID, instrumentArr[i]["ExchangeID"].GetString(), sizeof(field.InstrumentID));
            instruments.push_back(field);
        }
    }
};

void WritToJson(std::vector <CThostFtdcInstrumentField>& instruments, std::string& filePath) {
    rapidjson::StringBuffer s;
    rapidjson::PrettyWriter <rapidjson::StringBuffer> writer(s);
    writer.StartArray();
    std::vector<CThostFtdcInstrumentField>::iterator itr;
    for (itr = instruments.begin(); itr != instruments.end(); itr++) {
        writer.StartObject();
        ///��Լ����
        writer.Key("InstrumentID");
        writer.String(itr->InstrumentID);
        ///����������
        writer.Key("ExchangeID");
        writer.String(itr->ExchangeID);
        ///��Լ�ڽ������Ĵ���
        writer.Key("ExchangeInstID");
        writer.String(itr->ExchangeInstID);
        ///��Ʒ����
        writer.Key("ProductID");
        writer.String(itr->ProductID);
        ///��Ʒ����
        writer.Key("ProductClass");
        writer.String(std::string(1, itr->ProductClass).c_str());
        ///�������
        writer.Key("DeliveryYear");
        writer.Int(itr->DeliveryYear);
        ///������
        writer.Key("DeliveryMonth");
        writer.Int(itr->DeliveryMonth);
        ///�м۵�����µ���
        writer.Key("MaxMarketOrderVolume");
        writer.Int(itr->MaxMarketOrderVolume);
        ///�м۵���С�µ���
        writer.Key("MinMarketOrderVolume");
        writer.Int(itr->MinMarketOrderVolume);
        ///�޼۵�����µ���
        writer.Key("MaxLimitOrderVolume");
        writer.Int(itr->MaxLimitOrderVolume);
        ///�޼۵���С�µ���
        writer.Key("MinLimitOrderVolume");
        writer.Int(itr->MinLimitOrderVolume);
        ///��Լ��������
        writer.Key("VolumeMultiple");
        writer.Int(itr->VolumeMultiple);
        ///��С�䶯��λ
        writer.Key("PriceTick");
        writer.Double(itr->PriceTick);
        ///������
        writer.Key("CreateDate");
        writer.String(itr->CreateDate);
        ///������
        writer.Key("OpenDate");
        writer.String(itr->OpenDate);
        ///������
        writer.Key("ExpireDate");
        writer.String(itr->ExpireDate);
        ///��ʼ������
        writer.Key("StartDelivDate");
        writer.String(itr->StartDelivDate);
        ///����������
        writer.Key("EndDelivDate");
        writer.String(itr->EndDelivDate);
        ///��Լ��������״̬
        writer.Key("InstLifePhase");
        writer.String(std::string(1, itr->InstLifePhase).c_str());
        ///��ǰ�Ƿ���
        writer.Key("IsTrading");
        writer.Bool(itr->IsTrading);
        ///�ֲ�����
        writer.Key("PositionType");
        writer.String(std::string(1, itr->PositionType).c_str());
        ///�ֲ���������
        writer.Key("PositionDateType");
        writer.String(std::string(1, itr->PositionDateType).c_str());
        ///��ͷ��֤����
        writer.Key("LongMarginRatio");
        writer.Double(itr->LongMarginRatio);
        ///��ͷ��֤����
        writer.Key("ShortMarginRatio");
        writer.Double(itr->ShortMarginRatio);
        ///�Ƿ�ʹ�ô��߱�֤���㷨
        writer.Key("MaxMarginSideAlgorithm");
        writer.Double(itr->MaxMarginSideAlgorithm);
        ///������Ʒ����
        writer.Key("UnderlyingInstrID");
        writer.String(itr->UnderlyingInstrID);
        ///ִ�м�
        writer.Key("ProductClass");
        writer.String(std::string(1, itr->ProductClass).c_str());
        ///��Ȩ����
        writer.Key("OptionsType");
        writer.String(std::string(1, itr->OptionsType).c_str());
        ///��Լ������Ʒ����
        writer.Key("UnderlyingMultiple");
        writer.Double(itr->UnderlyingMultiple);
        ///�������
        writer.Key("CombinationType");
        writer.String(std::string(1, itr->CombinationType).c_str());

        writer.EndObject();
    }
    writer.EndArray();

    std::ofstream ofs("instrument.json");
    if (ofs.is_open()) {
        ofs << s.GetString() << std::endl;
        ofs.close();
    }
};