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


// ��ʱ��ID
const unsigned int AUTO_REFRESH_TIMER_ID = 60;  // �Զ�ˢ�¶�ʱ��ID
const unsigned int CHECK_NOTICE_TIMER_ID = 61;  // ��鹫�涨ʱ��ID
const unsigned int START_CHAT_CLIENT = 62;      // �����������ʱ��ID
const unsigned int SEND_ACCOUNT_MSG_TO_CHAT = 63;  // �����˺���Ϣ������ͻ��˶�ʱ��ID


#define  RECORD_NUM 200//��ȡ����Ϣ����

// �û���Ϣ�ṹ
struct UserInfo {
	string id;       // �û�ID
    string realName; // �û���ʵ����
    string company;  // ��˾����
    string tel;      // ��ϵ�绰
	string province; // ����ʡ
	string city;     // ������
    string userName; // ��Ա��
    string loginName;// ��¼��
    string passWord; // ����
	string sex; //�Ա�
};

// ���Ƶ�����Ϣ
struct CustomZoneInf {
    string id;
    string type;
    string startProvince;
    string startCity;
    string endProvince;
    string endCity;
};

  

/** 
 *  ÿ����¼��Ϣ
 */
// ������Ϣ����Դ���㵣����Դ��
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
    
// ������Ϣ����Դ���㵣����Դ��
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
    
// �ҵ���Ϣ����Դ���㵣����Դ��
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
    
// ר����Ϣ������ר�ߡ��ҵ�ר�ߡ����ղص�ר�ߣ�
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
//����վ����Ϣ
struct ServiceInfo
{
	string totalNum;   // total record number
	string returnNum;  // return record number
	string recordID;   // this record id
	string serviceName; // ����վ��
	string serviceNo;   // ���
	string serviceAddr;     // ��ַ
	string servicePerson;        // ��ϵ��
	string tel;     // �绰
	//string serviceID;//����վID
};
//��������վ������Ϣ
struct InSearchService{
	string Province;
	string City;
};
//����վ��������������Ϣ
struct InServiceMSG{
	string Province;
	string City;
};
// ������������Ϣ����Դ
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

// ������������Ϣ���㵣
struct InSearchBulkGoods{
    string startProvince;
    string startCity;
    string startCounty;
    string endProvince;
    string endCity;
    string endCounty;
};

// ������������Ϣ����Դ
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

// ������������Ϣ��ר��
struct InSearchSpecail{
    string startProvince;
    string startCity;
    string startCounty;
    string endProvince;
    string endCity;
    string endCounty;
};
    
// �������������Ϣ
struct InClickSearch {
    string province;
    string city;
};

// �������
struct inputParam {
    int record;   // ÿҳ��ʾ�ļ�¼��
    int curpage;  // ��ǰ�ڼ�ҳ    
    string customid; // ���Ƶ���ID
};

// �������(����վ)
struct inputParamFwz {
	string uid;     //�û�ID
	string  input;   // ʡ����|������
	int curpage;  // ��ǰ�ڼ�ҳ    
	int  record; // ÿҳ��ʾ�ļ�¼��
};

// ��ɫ����
struct SettingColor {   
    unsigned long  sysBKClr;  // ϵͳ����ɫ
    unsigned long  oddRowBKClr; // �����б���ɫ    
    unsigned long  oddRowFgClr; // ����������ɫ    
    unsigned long  evenRowBKClr; // ż���б���ɫ    
    unsigned long  evenRowFgClr; // ż��������ɫ    
    unsigned long  gridClr; // ��������ɫ
};

// ��������
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

// �����Ϣ
struct AdMsg {        
    string id;   // ���ID
    string inf;  // �����Ϣ
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
    // ���Ի��򱳾�ɫ
    static unsigned long mainDlgBgColor;

    // TAB�ؼ�����ɫ
    static unsigned long tabCtrlBgColor;
    
    // ����������ɫ
    static unsigned long scrollBarFgColor;
    // ����������ɫ
    static unsigned long scrollBarBgColor;

	// �Ƿ���С����־
	static bool ifMiniSize;
};

/************************************************************
  ������ת��Ϊ�ַ���
    to_string()�ĵڶ�������ӦΪ�����е�һ��
        std::hex, std::dec �� std::oct
    ���磺
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
void SuspendMyThread();//�����߳�
void ResumeMyThread();//�ָ��߳�

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
�ܼ�¼��|1
���ؼ�¼��|2
��ǰ��¼��ID|3
������ʡ|4
��������|5
Ŀ�ĵ�ʡ|6
Ŀ�ĵ���|7
��˾����|8
��Ա����|9
��ϵ�绰|10
Ԥ����Ϣ|11
����ʱ��|12
������¼���û�ID|13
************************************************************/
/************************************************************
TRUE|0
�ܼ�¼��|1
���ؼ�¼��|2
��ǰ��¼��ID|3
������ʡ|4
��������|5
Ŀ�ĵ�ʡ|6
Ŀ�ĵ���|7
�ػ���|8
�ݻ���|9
�������|10
;��ʱ��|11
��Ա����|12
��ϵ�绰|13
����ʱ��|14
������¼���û�ID|15
************************************************************/

