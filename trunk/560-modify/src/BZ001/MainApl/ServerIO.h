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
	
	int getPersisGoodsInfo(vector<TabNewInfRecord> &inf, inputParam& input);


    // Get new cars information
    int getNewCarsInf(vector<TabNewInfRecord> &inf, inputParam& input);     
    // Get custom cars information
    int getCustomCarsInf(vector<TabCustomInfRecord> &inf, inputParam& input);
    // Get my cars information
    int getMyCarsInf(vector<TabMyInfRecord> &inf, inputParam& input);

	int getPersisCarsInfo(vector<TabNewInfRecord> &inf, inputParam& input);

    // Get all special line information
    int getAllSpecialLineInf(vector<TabSpecialLineRecord> &inf, inputParam& input);
    // Get My special line information
    int getMySpecialLineInf(vector<TabSpecialLineRecord> &inf, inputParam& input);
    // Get Favorite special line information
    int getFavoriteSpecialLineInf(vector<TabSpecialLineRecord> &inf, inputParam& input);
    // Collect special Line
    string collectSpecialLine(string recordID);

	// Get new bulkGoods information
	int getNewBulkGoodsInf(vector<TabNewInfRecord> &inf, inputParam& input);
	// Get my BulkGoods information
	int getMyBulkGoodsInf(vector<TabMyInfRecord> &inf, inputParam& input);


    // Get search goods result
    int getSearchGoodsInf(const InSearchGoods& keyword, vector<TabNewInfRecord> &inf, inputParam& input);
	int getSearchGoodsInf(const string& sSearchKeyword, vector<TabNewInfRecord> &inf, inputParam& input);
    // Get search bulk goods result
    int getSearchBulkGoodsInf(const InSearchBulkGoods& keyword, vector<TabNewInfRecord> &inf, inputParam& input);
    // Get search cars result
    int getSearchCarsInf(const InSearchCars& keyword, vector<TabNewInfRecord> &inf, inputParam& input);
	int getSearchCarsInf(const string& sSearchKeyword, vector<TabNewInfRecord> &inf, inputParam& input);
    // Get search special line result
    int getSearchSpecialLineInf(const InSearchSpecail& keyword, vector<TabSpecialLineRecord> &inf, inputParam& input);

    // Get click search goods information
    int getClickSearchGoodsInf(const InClickSearch& keyword, vector<TabNewInfRecord> &inf, inputParam& input);
    // Get click search bulkGoods information
    int getClickSearchBulkGoodsInf(const InClickSearch& keyword, vector<TabNewInfRecord> &inf, inputParam& input);
    // Get click search cars information
    int getClickSearchCarsInf(const InClickSearch& keyword, vector<TabNewInfRecord> &inf, inputParam& input); 
    // Get click search special line information
    int getClickSearchSpecialLineInf(const InClickSearch& keyword, vector<TabSpecialLineRecord> &inf, inputParam& input);

    // Set pub goods information 
    string setPubGoodsInf(const string& input);
    // Set pub bulk goods information
    string setPubBulkGoodsInf(const string& input);
    // Set pub cars information
    string setPubCarsInf(const string& input);
    // Set pub special line information
    string setPubSpecialLineInf(const string& input);

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

    // 获取系统滚动广告信息
    string getSystemScrollAd();
    // 获取代理商弹出广告信息
    string getAgentPopAd();
    // 获取代理商滚动广告信息
    string getAgentScrollAd();
	//服务站信息
	string getServicestationInf(const InSearchService& keyword, vector<ServiceInfo> &inf, inputParamFwz& input);
	//给服务站发消息
	string ServerIO::setServicesMsg(string recordID,string sendMsg);
	//是否收费用户
	string ServerIO::check_charge_user (string login_name);

	string setGoodsStatus(const string& recordID, const string& sStatus);
	string setCarsStatus(const string& recordID, const string& sStatus);

public:
    UserInfo userInf; // 用户信息
    
    vector<CustomZoneInf> hyZoneInf; // 定制地区信息：货源
    vector<CustomZoneInf> cyZoneInf; // 定制地区信息：车源
    
    CountryRegion* myCR; // 区域信息指针
    
    SettingColor myColor; // 颜色信息
    
    SettingFont oddFont; // 奇数行字体信息
    SettingFont evenFont; // 偶数行字体信息 

    AdMsg sysScrollAd; // 系统滚动广告信息
    vector<AdMsg> agScrollAd;  // 代理商滚动广告信息
    AdMsg agPopAd;     // 代理商弹出广告信息

private:
    // UTF8编码字符串转换为多字节编码字符串
    int UTF8ToMultiByte(const std::string& in, std::string& out);
    // 宽字符转UTF8
    string EncodeUtf8(wstring in);
    // 多字节编码字符串转换为UTF8编码字符串
    int MultiByteToUTF8(const std::string& in, std::string& out);
    // 通过界定符串拆分字符串
    int tokenize(const std::string& str, std::vector<std::string>& tokens, const std::string& delimiters);
    // 初始化soap
    int initSoap();
    // 卸载soap
    int destroySoap();
private:
    // WebService 地址
    string svrURL;
    // gSOAP运行环境
    struct soap mySoap; 
};
