#ifndef _HEADER123456_
#define _HEADER123456_
#include "GLB.h"
struct ServiceData//����վ����Ϣ
{
	char cprovince[50]; //ʡ
	char ccity[50];//��
	char serviceN[50];//����վ����
	char Number[50];//����վ���
	char Address[500];//����վ��ַ
	char Name[50];//��ϵ��
	char Tel[50];//��ϵ�绰
	char serviceID[50];//����վID
};
#define WM_REQUEST WM_USER+1
#define WM_SETGRID WM_USER+77

#define WM_TNI_START_SEARCH		(WM_USER+1000)
#define WM_TNI_CANCEL_SEARCH	(WM_USER+1001)
#define WM_TNI_STOP_REFRESH		(WM_USER+1002)
#define WM_TNI_SECRECY			(WM_USER+1003)
#define WM_TNI_CLOSE_SEARCH_TAB	(WM_USER+1004)

//������Ϣ����Դ���㵣����Դ��
extern vector<TabNewInfRecord> contentDataHY;
extern vector<TabNewInfRecord> contentDataLD;
extern vector<TabNewInfRecord> contentDataCY;
extern vector<TabMyInfRecord> contentDataMYHY;
extern vector<TabMyInfRecord> contentDataMYLD;
extern vector<TabMyInfRecord> contentDataMYCY;
extern vector<TabNewInfRecord> contentDataPHY;
extern vector<TabNewInfRecord> contentDataPCY;
//ר��
extern vector<TabSpecialLineRecord> contentDataALL;//����ר��
extern vector<TabSpecialLineRecord> contentDataMY;//�ҵ�ר��
extern vector<TabSpecialLineRecord> contentDataSAVE;//�ղ�ר��
extern vector<CustomZoneInf> zoneInfHY;
extern vector<CustomZoneInf> zoneInfCY;

extern string retValue;//������Ϣ
extern UserInfo user; // �û���Ϣ
extern HWND m_progress;

extern HWND m_servicehwnd;
extern CRITICAL_SECTION csPrint; //�ٽ���
extern CRITICAL_SECTION csPrintMore; //�ٽ���
extern CRITICAL_SECTION csPrintOther;
extern CRITICAL_SECTION csPrintSpecial;
extern CRITICAL_SECTION csPrintMy;
extern CRITICAL_SECTION csPrintCustom;
extern CRITICAL_SECTION csPrintFresh;
extern CRITICAL_SECTION csClick;//��ֹ������쵼��vector����


extern CRITICAL_SECTION csService;//����վ


extern HANDLE hThread;

extern int nnewhy;
extern int nnewcy;
extern int nnewld;

extern HANDLE hThreadTimer;
extern HANDLE hThreadCY;
extern HANDLE hThreadLD;

extern vector<TabCustomInfRecord> contentDataDZHY[5];
extern vector<TabCustomInfRecord> contentDataDZCY[5];

extern int index;//���Ƶ�����������
extern CArray<ServiceData,ServiceData> m_servicedata;//����վ������
extern BOOL m_bClose;//����ر�
extern HANDLE m_hThreadSyn;//�߳�ͬ�����ź�
extern BOOL m_bSleep;//�߳��Ƿ�ȫ����ͣ��
#endif