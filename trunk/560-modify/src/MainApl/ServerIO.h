#pragma once

#include "GLB.h"
#include "soap/soapH.h"
#include "CountryRegion.h"
#include "header.h"
class ServerIO
{
public:
    ServerIO(void);
public:
    ~ServerIO(void);
public:
    // user login
    string usrLogin(string username, string pwd);
    // get user custom information
    string getUserCustomInfHY();
	string getUserCustomInfCY();
    // add user custom information
    string addUserCustomInf(CustomZoneInf input);
    // delete user custom information
    string deleteUserCustomInf(string customID);

    // Get new goods information
    int getNewGoodsInf(vector<TabNewInfRecord> &inf, inputParam& input);     
    // Get custom goods information
    //int getCustomGoodsInf(vector<TabCustomInfRecord> &inf, int id = -1, int recordNum = 10, int curpage = 1);
    int getCustomGoodsInf(vector<TabCustomInfRecord> &inf, inputParam& input);
    // Get my goods information
    int getMyGoodsInf(vector<TabMyInfRecord> &inf, inputParam& input);

    // Get new bulkGoods information
    int getNewBulkGoodsInf(vector<TabNewInfRecord> &inf, inputParam& input);
    // Get my BulkGoods information
    int getMyBulkGoodsInf(vector<TabMyInfRecord> &inf, inputParam& input);
       
    // Get new cars information
    int getNewCarsInf(vector<TabNewInfRecord> &inf, inputParam& input);     
    // Get custom cars information
    int getCustomCarsInf(vector<TabCustomInfRecord> &inf, inputParam& input);
    // Get my cars information
    int getMyCarsInf(vector<TabMyInfRecord> &inf, inputParam& input);

    // Get all special line information
    int getAllSpecialLineInf(vector<TabSpecialLineRecord> &inf, inputParam& input);
    // Get My special line information
    int getMySpecialLineInf(vector<TabSpecialLineRecord> &inf, inputParam& input);
    // Get Favorite special line information
    int getFavoriteSpecialLineInf(vector<TabSpecialLineRecord> &inf, inputParam& input);
    // Collect special Line
    string collectSpecialLine(string recordID);

    // Get search goods result
    int getSearchGoodsInf(InSearchGoods keyword, vector<TabNewInfRecord> &inf, inputParam& input);
    // Get search bulk goods result
    int getSearchBulkGoodsInf(InSearchBulkGoods keyword, vector<TabNewInfRecord> &inf, inputParam& input);
    // Get search cars result
    int getSearchCarsInf(InSearchCars keyword, vector<TabNewInfRecord> &inf, inputParam& input);
    // Get search special line result
    int getSearchSpecialLineInf(InSearchSpecail keyword, vector<TabSpecialLineRecord> &inf, inputParam& input);

    // Get click search goods information
    int getClickSearchGoodsInf(InClickSearch keyword, vector<TabNewInfRecord> &inf, inputParam& input);
    // Get click search bulkGoods information
    int getClickSearchBulkGoodsInf(InClickSearch keyword, vector<TabNewInfRecord> &inf, inputParam& input);
    // Get click search cars information
    int getClickSearchCarsInf(InClickSearch keyword, vector<TabNewInfRecord> &inf, inputParam& input); 
    // Get click search special line information
    int getClickSearchSpecialLineInf(InClickSearch keyword, vector<TabSpecialLineRecord> &inf, inputParam& input);

    // Set pub goods information 
    string setPubGoodsInf(string input);
    // Set pub bulk goods information
    string setPubBulkGoodsInf(string input);
    // Set pub cars information
    string setPubCarsInf(string input);
    // Set pub special line information
    string setPubSpecialLineInf(string input);

    // Delete goods information
    string delGoodsInf(string recordID);
    // Delete bulk goods information
    string delBulkGoodsInf(string recordID);
    // Delete cars information
    string delCarsInf(string recordID);
    // Delete special line information
    string delSpecialLineInf(string recordID);
    // delete favorite specail line
    string delFavoriteSpecialLine(string recordID);

    // Send Phone Message
    string sendPhoneMessage(string phone, string msg); 

    // ��ȡϵͳ���������Ϣ
    string getSystemScrollAd();
    // ��ȡ�����̵��������Ϣ
    string getAgentPopAd();
    // ��ȡ�����̹��������Ϣ
    string getAgentScrollAd();
	//����վ��Ϣ
	string getServicestationInf(InSearchService keyword, vector<ServiceInfo> &inf, inputParamFwz& input);
	//������վ����Ϣ
	string ServerIO::setServicesMsg(string recordID,string sendMsg);
	//�Ƿ��շ��û�
	string ServerIO::check_charge_user (string login_name);

public:
    UserInfo userInf; // �û���Ϣ
    
    vector<CustomZoneInf> hyZoneInf; // ���Ƶ�����Ϣ����Դ
    vector<CustomZoneInf> cyZoneInf; // ���Ƶ�����Ϣ����Դ
    
    CountryRegion* myCR; // ������Ϣָ��
    
    SettingColor myColor; // ��ɫ��Ϣ
    
    SettingFont oddFont; // ������������Ϣ
    SettingFont evenFont; // ż����������Ϣ 

    AdMsg sysScrollAd; // ϵͳ���������Ϣ
    vector<AdMsg> agScrollAd;  // �����̹��������Ϣ
    AdMsg agPopAd;     // �����̵��������Ϣ

private:
    // UTF8�����ַ���ת��Ϊ���ֽڱ����ַ���
    int UTF8ToMultiByte(const std::string& in, std::string& out);
    // ���ַ�תUTF8
    string EncodeUtf8(wstring in);
    // ���ֽڱ����ַ���ת��ΪUTF8�����ַ���
    int MultiByteToUTF8(const std::string& in, std::string& out);
    // ͨ���綨��������ַ���
    int tokenize(const std::string& str, std::vector<std::string>& tokens, const std::string& delimiters);
    // ��ʼ��soap
    int initSoap();
    // ж��soap
    int destroySoap();
private:
    // WebService ��ַ
    string svrURL;
    // gSOAP���л���
    struct soap mySoap; 
};
