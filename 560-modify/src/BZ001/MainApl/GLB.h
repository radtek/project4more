#pragma once

#include "CommDef.h"
#include <math.h>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <list>
using namespace std;
//#define _NEWCODE_
//#define _LOCAL_TEST_
//#define _OFF_LINE_
//#define _AUTO_LOGIN_

#ifdef _LOCAL_TEST_
const string WEB_SERVICE_ADDRESS = "http://192.168.7.108:8080";
#else
const string WEB_SERVICE_ADDRESS = "http://www.566560.com:8603";
//const string WEB_SERVICE_ADDRESS = "http://www.566560.com";
#endif

//extern string global_web_service_home;


// 定时器ID
const unsigned int AUTO_REFRESH_TIMER_ID = 60;  // 自动刷新定时器ID
const unsigned int CHECK_NOTICE_TIMER_ID = 61;  // 检查公告定时器ID
const unsigned int START_CHAT_CLIENT = 62;      // 启动聊天程序定时器ID
const unsigned int SEND_ACCOUNT_MSG_TO_CHAT = 63;  // 发送账号信息给聊天客户端定时器ID


#define  RECORD_NUM 200//读取的信息条数

// 用户信息结构
struct UserInfo {
	string id;       // 用户ID
    string realName; // 用户真实姓名
    string company;  // 公司名称
    string tel;      // 联系电话
	string province; // 所在省
	string city;     // 所在市
    string userName; // 会员名
    string loginName;// 登录名
    string passWord; // 密码
	string sex; //性别
};

// 定制地区信息
struct CustomZoneInf {
    string id;
    string type;
    string startProvince;
    string startCity;
    string endProvince;
    string endCity;
};

  

/** 
 *  每条记录信息
 */
// 最新信息（货源、零担、车源）
struct TabNewInfRecord {
    string totalNum;   // total record number
    string returnNum;  // return record number
    string recordID;   // this record id
    string startPlace; // start place
    string endPlace;   // arrive place
    string record;     // record information
    string tel;        // tel information
    string pubUID;     // the user id of pub this record
};
    
// 定制信息（货源、零担、车源）
struct TabCustomInfRecord {
    string totalNum;   // total record number
    string returnNum;  // return record number
    string recordID;   // this record id
    string startPlace; // start place
    string endPlace;   // arrive place
    string record;     // record information
    string tel;        // tel information
    string pubUID;     // the user id of pub this record
};
    
// 我的信息（货源、零担、车源）
struct TabMyInfRecord {
    string totalNum;   // total record number
    string returnNum;  // return record number
    string recordID;   // this record id
    string startPlace; // start place
    string endPlace;   // arrive place
    string record;     // record information
    string tel;        // tel information
    string pubUID;     // the user id of pub this record
};
    
// 专线信息（最新专线、我的专线、我收藏的专线）
struct TabSpecialLineRecord {
    string totalNum;   // total record number
    string returnNum;  // return record number
    string recordID;   // this record id
    string startPlace; // start place
    string endPlace;   // arrive place
    string weightPrice; // weight goods price
    string lightPrice; // light goods price
    string schedules;  // start schedules
    string needTime;   // need time
    string record;     // record information
    string tel;        // tel information
    string pubUID;     // the user id of pub this record
};
//服务站的信息
struct ServiceInfo
{
	string totalNum;   // total record number
	string returnNum;  // return record number
	string recordID;   // this record id
	string serviceName; // 服务站名
	string serviceNo;   // 编号
	string serviceAddr;     // 地址
	string servicePerson;        // 联系人
	string tel;     // 电话
	//string serviceID;//服务站ID
};
//搜索服务站输入信息
struct InSearchService{
	string Province;
	string City;
};
//服务站发送请求输入信息
struct InServiceMSG{
	string Province;
	string City;
};
// 搜索的输入信息：货源
struct InSearchGoods
{
	tdMapAddr	 lstStartAddr;
	tdMapAddr	 lstEndAddr;
    list<string> lstCarLength;
    list<string> lstCarType;
	list<string> lstGoods;
	list<string> lstGoodsType;
	list<string> lstPublisher;
	list<string> lstPhoneNum;
	string		 sKeyword;
	bool		 bMatchAll;
};

// 搜索的输入信息：零担
struct InSearchBulkGoods{
    string startProvince;
    string startCity;
    string startCounty;
    string endProvince;
    string endCity;
    string endCounty;
};

// 搜索的输入信息：车源
struct InSearchCars{
	tdMapAddr	 lstStartAddr;
	tdMapAddr	 lstEndAddr;
    list<string> lstCarLength;
    list<string> lstCarType;
	list<string> lstGoods;
	list<string> lstGoodsType;
	list<string> lstPublisher;
	list<string> lstPhoneNum;
	string		 sKeyword;
	bool		 bMatchAll;
};

// 搜索的输入信息：专线
struct InSearchSpecail{
    string startProvince;
    string startCity;
    string startCounty;
    string endProvince;
    string endCity;
    string endCounty;
};
    
// 点击搜索输入信息
struct InClickSearch {
    string province;
    string city;
};

// 输入参数
struct inputParam {
    int record;   // 每页显示的记录数
    int curpage;  // 当前第几页    
    string customid; // 定制地区ID
};

// 输入参数(服务站)
struct inputParamFwz {
	string uid;     //用户ID
	string  input;   // 省名称|市名称
	int curpage;  // 当前第几页    
	int  record; // 每页显示的记录数
};

// 颜色设置
struct SettingColor {   
    unsigned long  sysBKClr;  // 系统背景色
    unsigned long  oddRowBKClr; // 奇数行背景色    
    unsigned long  oddRowFgClr; // 奇数行文字色    
    unsigned long  evenRowBKClr; // 偶数行背景色    
    unsigned long  evenRowFgClr; // 偶数行文字色    
    unsigned long  gridClr; // 网格线颜色
};

// 字体设置
struct SettingFont {        
    long    lfHeight;
    long    lfWidth;
    long    lfEscapement;
    long    lfOrientation;
    long    lfWeight;
    unsigned char   lfItalic;
    unsigned char   lfUnderline;
    unsigned char   lfStrikeOut;
    unsigned char   lfCharSet;
    unsigned char   lfOutPrecision;
    unsigned char   lfClipPrecision;
    unsigned char   lfQuality;
    unsigned char   lfPitchAndFamily;
    string    lfFaceName;
};

// 广告信息
struct AdMsg {        
    string id;   // 广告ID
    string inf;  // 广告信息
};

class GLB
{
public:
    GLB(void);
public:
    ~GLB(void);

public:
	//void OnShemaChanged(int nSchema);
	//CString GetStylesPath(void);

public:
    // 主对话框背景色
    static unsigned long mainDlgBgColor;

    // TAB控件背景色
    static unsigned long tabCtrlBgColor;
    
    // 滚动条文字色
    static unsigned long scrollBarFgColor;
    // 滚动条背景色
    static unsigned long scrollBarBgColor;

	// 是否最小化标志
	static bool ifMiniSize;
};

/************************************************************
  将整数转换为字符串
    to_string()的第二个参数应为如下中的一个
        std::hex, std::dec 或 std::oct
    例如：
    std::cout<<to_string<long>(123456, std::hex)<<std::endl;
    std::cout<<to_string<long>(123456, std::oct)<<std::endl;
 ************************************************************/
template <class T>
std::string to_string(T t, std::ios_base & (*f)(std::ios_base&))
{
   std::ostringstream oss;
   oss << f << t;
   return oss.str();
}

void OnShemaChanged(int nSchema);
void SuspendMyThread();//挂起线程
void ResumeMyThread();//恢复线程

bool   greatermark(const   CustomZoneInf&   s1,const   CustomZoneInf&   s2); 



template < class T >
void ClearVector( vector< T >& vt )
{
	vector< T > vtTemp;
	vtTemp.swap( vt );
}
//CString GetStylesPath(void);

/************************************************************
TRUE|0
总记录数|1
返回记录数|2
当前记录的ID|3
出发地省|4
出发地市|5
目的地省|6
目的地市|7
公司名称|8
会员名称|9
联系电话|10
预览信息|11
发布时间|12
发布记录的用户ID|13
************************************************************/
/************************************************************
TRUE|0
总记录数|1
返回记录数|2
当前记录的ID|3
出发地省|4
出发地市|5
目的地省|6
目的地市|7
重货价|8
泡货价|9
发车班次|10
途中时间|11
会员名称|12
联系电话|13
发布时间|14
发布记录的用户ID|15
************************************************************/

