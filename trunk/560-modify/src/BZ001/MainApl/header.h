#ifndef _HEADER123456_
#define _HEADER123456_
#include "GLB.h"
struct ServiceData//服务站的信息
{
	char cprovince[50]; //省
	char ccity[50];//市
	char serviceN[50];//服务站名称
	char Number[50];//服务站编号
	char Address[500];//服务站地址
	char Name[50];//联系人
	char Tel[50];//联系电话
	char serviceID[50];//服务站ID
};
#define WM_REQUEST WM_USER+1
#define WM_SETGRID WM_USER+77

#define WM_TNI_START_SEARCH		(WM_USER+1000)
#define WM_TNI_CANCEL_SEARCH	(WM_USER+1001)
#define WM_TNI_STOP_REFRESH		(WM_USER+1002)
#define WM_TNI_SECRECY			(WM_USER+1003)
#define WM_TNI_CLOSE_SEARCH_TAB	(WM_USER+1004)

//最新信息（货源、零担、车源）
extern vector<TabNewInfRecord> contentDataHY;
extern vector<TabNewInfRecord> contentDataLD;
extern vector<TabNewInfRecord> contentDataCY;
extern vector<TabMyInfRecord> contentDataMYHY;
extern vector<TabMyInfRecord> contentDataMYLD;
extern vector<TabMyInfRecord> contentDataMYCY;
extern vector<TabNewInfRecord> contentDataPHY;
extern vector<TabNewInfRecord> contentDataPCY;
//专线
extern vector<TabSpecialLineRecord> contentDataALL;//所有专线
extern vector<TabSpecialLineRecord> contentDataMY;//我的专线
extern vector<TabSpecialLineRecord> contentDataSAVE;//收藏专线
extern vector<CustomZoneInf> zoneInfHY;
extern vector<CustomZoneInf> zoneInfCY;

extern string retValue;//滚动信息
extern UserInfo user; // 用户信息
extern HWND m_progress;

extern HWND m_servicehwnd;
extern CRITICAL_SECTION csPrint; //临界区
extern CRITICAL_SECTION csPrintMore; //临界区
extern CRITICAL_SECTION csPrintOther;
extern CRITICAL_SECTION csPrintSpecial;
extern CRITICAL_SECTION csPrintMy;
extern CRITICAL_SECTION csPrintCustom;
extern CRITICAL_SECTION csPrintFresh;
extern CRITICAL_SECTION csClick;//防止点击过快导致vector崩溃


extern CRITICAL_SECTION csService;//服务站


extern HANDLE hThread;

extern int nnewhy;
extern int nnewcy;
extern int nnewld;

extern HANDLE hThreadTimer;
extern HANDLE hThreadCY;
extern HANDLE hThreadLD;

extern vector<TabCustomInfRecord> contentDataDZHY[5];
extern vector<TabCustomInfRecord> contentDataDZCY[5];

extern int index;//定制的下拉项的序号
extern CArray<ServiceData,ServiceData> m_servicedata;//服务站的数据
extern BOOL m_bClose;//程序关闭
extern HANDLE m_hThreadSyn;//线程同步的信号
extern BOOL m_bSleep;//线程是否安全的暂停了
#endif