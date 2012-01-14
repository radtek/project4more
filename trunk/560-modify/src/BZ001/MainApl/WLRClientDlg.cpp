// WLRClientDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WLRClient.h"
#include "WLRClientDlg.h"

#include "AutoUpdater.h"

#include "SearchSelectDlg.h"
#include "SearchGoodsDlg.h"
#include "SearchBulkGoodsDlg.h"
#include "SearchCarsDlg.h"
#include "SearchSpecialDlg.h"

#include "PubSelectDlg.h"
#include "PubGoodsDlg.h"
#include "PubBulkGoodsDlg.h"
#include "PubCarsDlg.h"
#include "PubSpecialDlg.h"

#include "UserLoginDlg.h"

#include "ValueAddedServiceDlg.h"

#include "ConfigSetDlg.h"


#include "EmbeddedIeDlg.h"

#include "PopNoticeDlg.h"

#include "CameraDlg.h"

#include "header.h"

#include "UserCenter.h"
#include "WebHTTP.h"

#include "PublishWayOneDlg.h"
#include "PublishWayTwoDlg.h"
#include "SearchMainDlg.h"
#include "SearchFavorite.h"
#include "CommDef.h"
// ������۲��
//#include "SkinFeature.h"
//#pragma comment(lib,"SkinFeature.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define WM_SENDFRESH WM_USER+100//ˢ��ҳ��
#define WM_TCGG WM_USER+101//��������
//������Ϣ����Դ���㵣����Դ��
vector<TabNewInfRecord> contentDataHY;
vector<TabNewInfRecord> contentDataLD;
vector<TabNewInfRecord> contentDataCY;
//�ҵ���Ϣ����Դ���㵣����Դ��
vector<TabMyInfRecord> contentDataMYHY;
vector<TabMyInfRecord> contentDataMYLD;
vector<TabMyInfRecord> contentDataMYCY;
//ר��
vector<TabSpecialLineRecord> contentDataALL;//����ר��
vector<TabSpecialLineRecord> contentDataMY;//�ҵ�ר��
vector<TabSpecialLineRecord> contentDataSAVE;//�ղ�ר��

vector<CustomZoneInf> zoneInfHY;//����
vector<CustomZoneInf> zoneInfCY;

vector<TabCustomInfRecord> contentDataDZHY[5];
vector<TabCustomInfRecord> contentDataDZCY[5];

UserInfo user; // �û���Ϣ
HANDLE hThread;
HANDLE hThreadTimer;
HANDLE hThreadCY;
HANDLE hThreadLD;


CRITICAL_SECTION csPrint; //�ٽ���
CRITICAL_SECTION csPrintMore; //�ٽ���
CRITICAL_SECTION csPrintOther;
CRITICAL_SECTION csPrintSpecial;
CRITICAL_SECTION csPrintMy;
CRITICAL_SECTION csPrintCustom;

CRITICAL_SECTION csClick;//��ֹ������쵼��vector����

CRITICAL_SECTION csPrintFresh;

CRITICAL_SECTION csService;

string result1;
string result2;

unsigned int nHysize =1;//�ж϶��ƻ�Դѡ�
unsigned int nCysize =1;//�ж϶��Ƴ�Դѡ�

BOOL m_bClose = FALSE;//����ر�

WLRConfig myConfig;

enum MSG_Type
{
	NewGood = 0,
	CustomGood,
	MyGood,
	NewCar,
	CustomCar,
	MyCar,
	NewBulkGood,
	MyBulkGood,
	NewSpecial,
	MySpecial,
	MyFavoritesSpecial
};
MSG_Type showtype;
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���


class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CWLRClientDlg �Ի���




CWLRClientDlg::CWLRClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWLRClientDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

    // ��ʼ������
    //curTabType = GOODS;
	
    ifInit = false;
    ifShowPhone = true;
    ifAutoRefresh = false;
	
	m_dock = FALSE;
	m_break = FALSE;

	m_bgColor = RGB(229,243,254);
	m_textColor = RGB(64, 74, 83); // ����ɫ

	// ����Ƥ��
	OnShemaChanged(0);
	//OnShemaChanged
	InitExceptionCatch();

}

void CWLRClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_Main, mTabMain);
	DDX_Control(pDX, IDC_TREE_Main, mTreeMain);
	DDX_Control(pDX, IDC_BTN_TakePhoto, btnTakePhoto);
	//DDX_Control(pDX, IDC_BTN_AutoUpdate, autoRefresh);
	//DDX_Control(pDX, IDC_BTN_HideTel, showPhone);
	DDX_Control(pDX, IDC_STATIC_AD, pubAD);
	DDX_Control(pDX, IDC_BTN_Goods, btnGoods);
	//DDX_Control(pDX, IDC_BTN_BulkGoods, btnBulkGoods);
	DDX_Control(pDX, IDC_BTN_Cars, btnCars);
	DDX_Control(pDX, IDC_BTN_Line, btnSpecial);
	//DDX_Control(pDX, IDC_BTN_Search, btnSearch);
	DDX_Control(pDX, IDC_BTN_Setting, btnSysSetting);
	//DDX_Control(pDX, IDC_BTN_PayService, btnAddValued);
	//xqh:ɾ�����ٷ�������
	//DDX_Control(pDX, IDC_BTN_Pub, btnQuickPub);
	DDX_Control(pDX, IDC_BTN_NOTICE, btnNotice);
	//	DDX_Control(pDX, IDC_BTN_CHAT, btnChat);
	DDX_Control(pDX, IDC_BTN_SERVER, m_btnserver);
	DDX_Control(pDX, IDC_BTN_WLR, m_btnwlr);
	//DDX_Control(pDX, IDC_CEMTER, m_btnuser);

	//������Դ
	DDX_Control(pDX, IDC_BTN_ReleaseGoods, m_btnReleaseGoods);
	//������Դ
	DDX_Control(pDX, IDC_BTN_ReleaseTruckInfo, m_btnReleaseTruckInfo);
	//����ר��
	DDX_Control(pDX, IDC_BTN_ReleaseSpecialLine, m_btnReleaseSpecialLine);

	//�ҵ��˻�
	DDX_Control(pDX, IDC_BTN_MyAccountant, m_btnMyAccountant);
	//����Ӧ��
	DDX_Control(pDX, IDC_BTN_MY_APP, m_btnMyApp);
	//GPS ��λ
	DDX_Control(pDX, IDC_BTN_GPS_LOCATING, m_btnGPSLocating);
	//�����̳�
	DDX_Control(pDX, IDC_BTN_SHOPPING_MALL, m_btnShoppingMall);

	DDX_Control(pDX, IDC_BUTTON_PUB_WAY_ONE, m_btnPubWayOne);
	DDX_Control(pDX, IDC_BUTTON_PUB_WAY_TWO, m_btnPubWayTwo);
}

BEGIN_MESSAGE_MAP(CWLRClientDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
    ON_WM_SIZE()
    ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_Main, &CWLRClientDlg::OnTcnSelchangeTabMain)
    ON_BN_CLICKED(IDC_BTN_MainPage, &CWLRClientDlg::OnBnClickedBtnMainpage)
    ON_BN_CLICKED(IDC_BTN_Goods, &CWLRClientDlg::OnBnClickedBtnGoods)
    //ON_BN_CLICKED(IDC_BTN_BulkGoods, &CWLRClientDlg::OnBnClickedBtnBulkgoods)
    ON_BN_CLICKED(IDC_BTN_Cars, &CWLRClientDlg::OnBnClickedBtnCars)
    ON_BN_CLICKED(IDC_BTN_Line, &CWLRClientDlg::OnBnClickedBtnLine)
    ON_BN_CLICKED(IDC_BTN_Search, &CWLRClientDlg::OnBnClickedBtnSearch)
    ON_BN_CLICKED(IDC_BTN_Setting, &CWLRClientDlg::OnBnClickedBtnSetting)
    ON_BN_CLICKED(IDC_BTN_PayService, &CWLRClientDlg::OnBnClickedBtnPayservice)
    ON_BN_CLICKED(IDC_BTN_AutoUpdate, &CWLRClientDlg::OnBnClickedBtnAutoupdate)
    ON_BN_CLICKED(IDC_BTN_HideTel, &CWLRClientDlg::OnBnClickedBtnHidetel)

	//xqh:ɾ�����ٷ�������
    //ON_BN_CLICKED(IDC_BTN_Pub, &CWLRClientDlg::OnBnClickedBtnPub)

    ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_Main, &CWLRClientDlg::OnTvnSelchangedTreeMain)
    ON_WM_TIMER()
    ON_WM_CLOSE()
    ON_BN_CLICKED(IDC_BTN_NOTICE, &CWLRClientDlg::OnBnClickedBtnNotice)
    ON_WM_CTLCOLOR()
	ON_WM_MOVE()
	// for recv chat msg
	ON_WM_COPYDATA()
	ON_BN_CLICKED(IDC_BTN_CHAT, &CWLRClientDlg::OnBnClickedBtnChat)
	ON_BN_CLICKED(IDC_BTN_SERVER, &CWLRClientDlg::OnBnClickedBtnServer)
	ON_BN_CLICKED(IDC_BTN_WLR, &CWLRClientDlg::OnBnClickedBtnWlr)
	ON_BN_CLICKED(IDC_CEMTER, &CWLRClientDlg::OnBnClickedCenter)

	ON_MESSAGE(WM_SENDFRESH,OnFresh)
	ON_MESSAGE(WM_TCGG,OnTCGG)
	ON_BN_CLICKED(IDOK, &CWLRClientDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CWLRClientDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BTN_ReleaseGoods, &CWLRClientDlg::OnBnClickedBtnReleasegoods)
	ON_BN_CLICKED(IDC_BTN_ReleaseTruckInfo, &CWLRClientDlg::OnBnClickedBtnReleasetruckinfo)
	ON_BN_CLICKED(IDC_BTN_ReleaseSpecialLine, &CWLRClientDlg::OnBnClickedBtnReleasespecialline)
	ON_BN_CLICKED(IDC_BTN_MyAccountant, &CWLRClientDlg::OnBnClickedBtnMyaccountant)
	ON_BN_CLICKED(IDC_BTN_SHOPPING_MALL, &CWLRClientDlg::OnBnClickedBtnShoppingMall)
	ON_BN_CLICKED(IDC_BTN_GPS_LOCATING, &CWLRClientDlg::OnBnClickedBtnGpsLocating)
	ON_BN_CLICKED(IDC_BTN_MY_APP, &CWLRClientDlg::OnBnClickedBtnMyApp)
	ON_BN_CLICKED(IDC_BUTTON_PUB_WAY_ONE, &CWLRClientDlg::OnBnClickedButtonPubWayOne)
	ON_BN_CLICKED(IDC_BUTTON_PUB_WAY_TWO, &CWLRClientDlg::OnBnClickedButtonPubWayTwo)
END_MESSAGE_MAP()

BEGIN_EASYSIZE_MAP(CWLRClientDlg)
    //EASYSIZE(control,left,top,right,bottom,options)
	//EASYSIZE(IDC_BTN_Pub, ES_KEEPSIZE, ES_BORDER, ES_BORDER, ES_KEEPSIZE, 0)
    //EASYSIZE(IDC_TREE_Main, ES_KEEPSIZE, IDC_BTN_Pub, ES_BORDER, ES_BORDER, 0)

	//EASYSIZE(IDC_BTN_Goods, ES_KEEPSIZE, ES_BORDER, IDC_BTN_Cars, IDC_TAB_Main, 0)
	//EASYSIZE(IDC_BTN_Cars, IDC_BTN_Goods, ES_BORDER, IDC_BTN_Line, IDC_TAB_Main, 0)
	//EASYSIZE(IDC_BTN_Line, IDC_BTN_Cars, ES_BORDER, IDC_BTN_Search, IDC_TAB_Main, 0)
	//EASYSIZE(IDC_BTN_Search, IDC_BTN_Line, ES_BORDER, IDC_BTN_MainPage, IDC_TAB_Main, 0)
	//EASYSIZE(IDC_BTN_MainPage, IDC_BTN_Search, ES_BORDER, IDC_BTN_ReleaseGoods, IDC_TAB_Main, 0)
	//EASYSIZE(IDC_BTN_ReleaseGoods, IDC_BTN_MainPage, ES_BORDER, IDC_BTN_ReleaseTruckInfo, IDC_TAB_Main, 0)
	//EASYSIZE(IDC_BTN_ReleaseTruckInfo, IDC_BTN_ReleaseGoods, ES_BORDER, IDC_BTN_ReleaseSpecialLine, IDC_TAB_Main, 0)
	//EASYSIZE(IDC_BTN_ReleaseSpecialLine, IDC_BTN_ReleaseTruckInfo, ES_BORDER, IDC_BTN_MyAccountant, IDC_TAB_Main, 0)


	EASYSIZE(IDC_TREE_Main, ES_KEEPSIZE, IDC_BTN_SERVER, ES_BORDER, ES_BORDER, 0)
    EASYSIZE(IDC_TAB_Main, ES_BORDER, IDC_BTN_Goods, IDC_TREE_Main, ES_BORDER, 0)	
    EASYSIZE(IDC_BTN_NOTICE, ES_KEEPSIZE, ES_KEEPSIZE, ES_BORDER, ES_BORDER, 0)

	EASYSIZE(IDC_BTN_CHAT, ES_KEEPSIZE, ES_KEEPSIZE, IDC_BTN_NOTICE, ES_BORDER, 0)
//	EASYSIZE(IDC_BTN_Setting, ES_KEEPSIZE, ES_KEEPSIZE, IDC_BTN_NOTICE, ES_BORDER, 0)
    EASYSIZE(IDC_STATIC_AD, ES_BORDER, ES_KEEPSIZE, IDC_BTN_CHAT, ES_BORDER, 0)

/*
	//�ҵ��˻�
	EASYSIZE(IDC_BTN_MyAccountant, ES_KEEPSIZE, ES_BORDER, ES_BORDER, ES_BORDER, 0)
	//��ҳ
	EASYSIZE(IDC_BTN_WLR, ES_KEEPSIZE, ES_BORDER, ES_BORDER, ES_BORDER, 0)
	//GPS��λ
	EASYSIZE(IDC_BTN_GPS_LOCATING, ES_KEEPSIZE, ES_BORDER, ES_BORDER, ES_BORDER, 0)
	//����Ӧ��
	EASYSIZE(IDC_BTN_MY_APP, ES_KEEPSIZE, ES_BORDER, ES_BORDER, ES_BORDER, 0)
	//�����̳�
	EASYSIZE(IDC_BTN_SHOPPING_MALL, ES_KEEPSIZE, ES_BORDER, ES_BORDER, ES_BORDER, 0)
	//����վ
	EASYSIZE(IDC_BTN_SERVER, ES_KEEPSIZE, ES_BORDER, ES_BORDER, ES_BORDER, 0)
	//�û�����
	EASYSIZE(IDC_CEMTER, ES_KEEPSIZE, ES_BORDER, ES_BORDER, ES_BORDER, 0)
	//�Զ�ˢ�� IDC_BTN_AutoUpdate
	EASYSIZE(IDC_BTN_AutoUpdate, ES_KEEPSIZE, ES_BORDER, ES_BORDER, ES_BORDER, 0)
	//��ֵ���� IDC_BTN_PayService
	EASYSIZE(IDC_BTN_PayService, ES_KEEPSIZE, ES_BORDER, ES_BORDER, ES_BORDER, 0)
	//���ص绰 IDC_BTN_HideTel
	EASYSIZE(IDC_BTN_HideTel, ES_KEEPSIZE, ES_BORDER, ES_BORDER, ES_BORDER, 0)*/
	

END_EASYSIZE_MAP
// CWLRClientDlg ��Ϣ�������

BOOL CWLRClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	//SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	//SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	//EnableCursor(FALSE);
	InitializeCriticalSection(&csPrint);
	InitializeCriticalSection(&csPrintMore);
	InitializeCriticalSection(&csPrintOther);
	InitializeCriticalSection(&csPrintSpecial);
	InitializeCriticalSection(&csPrintMy);
	InitializeCriticalSection(&csPrintCustom);
	InitializeCriticalSection(&csPrintFresh);
	InitializeCriticalSection(&csClick);
	InitializeCriticalSection(&csService);


    // ������-----���廪ȡ��������
    //checkUpate();
	

    // ��������
    loadConfig();

    // ��ʼ������
    initConfig();

    // ���ص�����Ϣ
	if ( -1 == CountryRegion::loadData(myCR, "RegionInfo.bin") ) {
		AfxMessageBox("���س��������ļ�ʧ�ܣ������°�װӦ�ó���");
		exit(0);
	}

	g_pCountryRegion = &myCR;
    // ������Ϣָ�븳ֵ
    svrIO.myCR = &myCR;
	svrIONew.myCR = &myCR;
	svrIOMore.myCR = &myCR;
	svrIOMy.myCR = &myCR;
	svrIOCustom.myCR = &myCR;
	svrIOSpecial.myCR = &myCR;
	svrIOService.myCR = &myCR;
	svrIOPub.myCR = &myCR;

    // �û���¼
    userLogin();
   
	
	//xqh:�ͻ��˵ı�������
	string welcome(",��ӭʹ��560������");
	if ( "��" == svrIO.userInf.sex )
		welcome=svrIO.userInf.realName+"��������" + welcome;
	else if ( "Ů" == svrIO.userInf.sex ) 
		welcome=svrIO.userInf.realName+"Ůʿ����" + welcome;
	else
		welcome=svrIO.userInf.realName+"����" + welcome;
    
	this->SetWindowText(welcome.c_str());
    
	//ȡ���û�����
	this->is_funcs_enabled = this->get_funcs_status(svrIO.userInf.loginName);

	//
	InitCommData();

                                         
    // ��ʼ����ť
    initButton();

    // ��ʼ��TAB�ؼ�
    initTabCtrl();
    
    // ��ʼ��Tree�ؼ�
    initTreeCtrl();

    // ������������
    startShowAD();   

    // �����Զ�ˢ��
    startTimer();

    // ������鹫�涨ʱ��
    //SetTimer(CHECK_NOTICE_TIMER_ID, checkNoticeGap, NULL);

	// ��������ͻ��˶�ʱ��
    SetTimer(START_CHAT_CLIENT, 1000, NULL);
    
    //bgBrush.CreateSolidBrush(svrIO.myColor.sysBKClr); 

    // ��ʼ���Զ������ؼ�λ��
    INIT_EASYSIZE;

	// ���ô���λ��
	//int cxScreen = ::GetSystemMetrics(SM_CXSCREEN);//�����Ļ�� 
 //   int cyScreen = ::GetSystemMetrics(SM_CYSCREEN); //�����Ļ��
	//int xPos = ((cxScreen-1024)/2) > 0 ? ((cxScreen-1024)/2) : 0 ;
	//::MoveWindow(m_hWnd, xPos, (cyScreen-600)/2, 800, 600, TRUE);

	//��ʱ�ɼ�
	DWORD PID;
	hEvent=CreateEvent(NULL,TRUE,FALSE,NULL);
	hThread=CreateThread(NULL,0,Proc,this,0,&PID);//��ʱˢ�µ����ݲɼ�

	/*DWORD PIDTIMER;//��ʱˢ�� ���������
	hThreadTimer=CreateThread(NULL,0,ProcTimer,this,0,&PIDTIMER);

	DWORD PIDTIMER1;//��ʱˢ�� ��������
	hThreadCY=CreateThread(NULL,0,ProcCY,this,0,&PIDTIMER1);*/
		
	//SetTimer(1,50,NULL);
	//svrIONew = svrIO;
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CWLRClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CWLRClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
//
HCURSOR CWLRClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
    
// ������
bool CWLRClientDlg::checkUpate()
{
	CString updateURL = WEB_SERVICE_ADDRESS.c_str();
    updateURL = updateURL + "/fmp/pc_client/update/";
    CAutoUpdater updater;

	// ���update�ļ��Ƿ���Ҫ���£������Ҫ���£������ update �ļ�
	if (CAutoUpdater::UpdateRequired == updater.CheckUpdate(updateURL, "update_file.txt")) {
		updater.RunUpdate(updateURL, "update_file.txt");
	} 

	// ���������ļ��Ƿ���Ҫ���£������Ҫ���£������� update �ļ�
	if (CAutoUpdater::UpdateRequired == updater.CheckUpdate(updateURL, "updates.txt")) {
		MessageBox("�������°汾���������ȷ������ʼ���¡�", "�Զ�����", MB_ICONINFORMATION|MB_OK);
        // ���и��³���
        WinExec("update.exe", SW_SHOW);
        exit(0);
	} 

    return true;
}
        
// ��������
int CWLRClientDlg::saveConfig(){
    WLRConfig myConfig;

    myConfig.colorSetting.sysBKClr = svrIO.myColor.sysBKClr;
    myConfig.colorSetting.gridClr  = svrIO.myColor.gridClr;
    myConfig.colorSetting.oddRowBKClr  = svrIO.myColor.oddRowBKClr;
    myConfig.colorSetting.oddRowFgClr  = svrIO.myColor.oddRowFgClr;
    myConfig.colorSetting.evenRowBKClr = svrIO.myColor.evenRowBKClr;
    myConfig.colorSetting.evenRowFgClr = svrIO.myColor.evenRowFgClr;

    myConfig.oddFont.lfFaceName = svrIO.oddFont.lfFaceName;
    myConfig.oddFont.lfWeight = svrIO.oddFont.lfWeight; 
    myConfig.oddFont.lfWidth = svrIO.oddFont.lfWidth; 
    myConfig.oddFont.lfHeight = svrIO.oddFont.lfHeight;  
    myConfig.oddFont.lfEscapement = svrIO.oddFont.lfEscapement; 
    myConfig.oddFont.lfUnderline = svrIO.oddFont.lfUnderline; 
    myConfig.oddFont.lfItalic = svrIO.oddFont.lfItalic; 
    myConfig.oddFont.lfStrikeOut = svrIO.oddFont.lfStrikeOut; 
    myConfig.oddFont.lfCharSet = svrIO.oddFont.lfCharSet;

    myConfig.evenFont.lfFaceName = svrIO.evenFont.lfFaceName;
    myConfig.evenFont.lfWeight = svrIO.evenFont.lfWeight; 
    myConfig.evenFont.lfWidth = svrIO.evenFont.lfWidth; 
    myConfig.evenFont.lfHeight = svrIO.evenFont.lfHeight;  
    myConfig.evenFont.lfEscapement = svrIO.evenFont.lfEscapement; 
    myConfig.evenFont.lfUnderline = svrIO.evenFont.lfUnderline; 
    myConfig.evenFont.lfItalic = svrIO.evenFont.lfItalic; 
    myConfig.evenFont.lfStrikeOut = svrIO.evenFont.lfStrikeOut; 
    myConfig.evenFont.lfCharSet = svrIO.evenFont.lfCharSet;
	TCHAR szStylesPath[_MAX_PATH];

	VERIFY(::GetModuleFileName(
		AfxGetApp()->m_hInstance, szStylesPath, _MAX_PATH));		

	CString csStylesPath(szStylesPath);
	int nIndex  = csStylesPath.ReverseFind(_T('\\'));
	if (nIndex > 0) {
		csStylesPath = csStylesPath.Left(nIndex);
	}
	else {
		csStylesPath.Empty();
	}
	CString path;
	path = csStylesPath;
	path += "\\config.bin";

	string s(path.GetBuffer());

    WLRConfig::saveData(myConfig, s);

    return 0;
}
    
// ��������
int CWLRClientDlg::loadConfig(){
   
	TCHAR szStylesPath[_MAX_PATH];

	VERIFY(::GetModuleFileName(
		AfxGetApp()->m_hInstance, szStylesPath, _MAX_PATH));		

	CString csStylesPath(szStylesPath);
	int nIndex  = csStylesPath.ReverseFind(_T('\\'));
	if (nIndex > 0) {
		csStylesPath = csStylesPath.Left(nIndex);
	}
	else {
		csStylesPath.Empty();
	}
	CString path;
	path = csStylesPath;
	path += "\\config.bin";

	string s(path.GetBuffer());

	if ( -1 == WLRConfig::loadData(myConfig, s)) {
        return -1;
	}
	
	SetInitColor(svrIO);
	SetInitColor(svrIONew);
	SetInitColor(svrIOMore);
	SetInitColor(svrIOMy);
	SetInitColor(svrIOSpecial);
	SetInitColor(svrIOCustom);
	SetInitColor(svrIOService);
	SetInitColor(svrIOPub);

    return 0;
}
    
// ��ʼ������
int CWLRClientDlg::initConfig()
{
    // ���Ի��򱳾�ɫ
    GLB::mainDlgBgColor = /*RGB(238, 238, 238);*/RGB(238, 238, 238);//RGB(199, 230, 196);

    // TAB�ؼ�����ɫ
    GLB::tabCtrlBgColor = RGB(238, 238, 238);

    // ����������ɫ
    GLB::scrollBarFgColor = m_textColor;//RGB(0, 0, 0);
    // ����������ɫ
    GLB::scrollBarBgColor = m_bgColor;

    // �Զ�ˢ��ʱ����
    autoRefreshGap = 1000;  // 10��
    // ��鹫����ʱ��
    checkNoticeGap = 30000;  // 30��

	return 0;
}
    
//  �û���¼
int CWLRClientDlg::userLogin()
{
#ifdef _AUTO_LOGIN_
    string username("dot");
    string password("123456");    
    string result = svrIO.usrLogin(username, password);
    svrIO.userInf.loginName = username;
    svrIO.userInf.passWord = password;
    if (result != "TRUE") {
        MessageBox(result.c_str(), "�û���¼");
        exit(0);
    } else {
        return 0;
    }
#else
    CUserLoginDlg dlg;
    
    if (dlg.DoModal() == IDOK) {

		
        svrIO.userInf.loginName = (LPTSTR)(LPCTSTR)dlg.userName;
        svrIO.userInf.passWord = (LPTSTR)(LPCTSTR)dlg.passWord;


		svrIONew.userInf.loginName = (LPTSTR)(LPCTSTR)dlg.userName;
		svrIONew.userInf.passWord = (LPTSTR)(LPCTSTR)dlg.passWord;

		svrIOMore.userInf.loginName = (LPTSTR)(LPCTSTR)dlg.userName;
		svrIOMore.userInf.passWord = (LPTSTR)(LPCTSTR)dlg.passWord;

		svrIOMy.userInf.loginName = (LPTSTR)(LPCTSTR)dlg.userName;
		svrIOMy.userInf.passWord = (LPTSTR)(LPCTSTR)dlg.passWord;

		svrIOCustom.userInf.loginName = (LPTSTR)(LPCTSTR)dlg.userName;
		svrIOCustom.userInf.passWord = (LPTSTR)(LPCTSTR)dlg.passWord;

		svrIOSpecial.userInf.loginName = (LPTSTR)(LPCTSTR)dlg.userName;
		svrIOSpecial.userInf.passWord = (LPTSTR)(LPCTSTR)dlg.passWord;

		svrIOService.userInf.loginName = (LPTSTR)(LPCTSTR)dlg.userName;
		svrIOService.userInf.passWord = (LPTSTR)(LPCTSTR)dlg.passWord;


		svrIOPub.userInf.loginName = (LPTSTR)(LPCTSTR)dlg.userName;
		svrIOPub.userInf.passWord = (LPTSTR)(LPCTSTR)dlg.passWord;


        string result = svrIO.usrLogin((LPTSTR)(LPCTSTR)dlg.userName, (LPTSTR)(LPCTSTR)dlg.passWord);
		
		//------------------------
		//���廪���Ը�д
		//------------------------
		
        if (result != "TRUE") {
            MessageBox(result.c_str(), "�û���¼");
            exit(0);
        } else {
			user = svrIO.userInf;
			/**/svrIONew.userInf = user;
			svrIOMore.userInf  = user;
			svrIOMy.userInf  = user;
			svrIOCustom.userInf  = user;
			svrIOSpecial.userInf  = user;
			svrIOService.userInf  = user;
			svrIOPub.userInf  = user;
            return 0;
        }
    } else {
        exit(0);
    }

#endif  

    return 0;
}
    
// ��ʼ����ť
int CWLRClientDlg::initButton()
{
    // ��Դ��ť
    btnGoods.LoadBitmap(IDB_GOODS);

    // ��Դ��ť
    btnCars.LoadBitmap(IDB_CARS);

    // ר�߰�ť
    btnSpecial.LoadBitmap(IDB_SPECIAL);

	//������Դ
	this->m_btnReleaseGoods.LoadBitmap(IDB_RELEASE_GOODS);

	//������Դ
	this->m_btnReleaseTruckInfo.LoadBitmap(IDB_RELEASE_TRUCK_INFO);

	//����ר��
	this->m_btnReleaseSpecialLine.LoadBitmap(IDB_RELEASE_SPECIAL_LINE);

	// ���հ�ť
	btnTakePhoto.LoadBitmap(IDB_TAKE_PHOTO);

	//�ҵ��˻�
	this->m_btnMyAccountant.LoadBitmap(IDB_MY_ACCOUNTANT);


	//�����̳�
	this->m_btnShoppingMall.LoadBitmap(IDB_SHOPPING_MALL);

	//����Ӧ��
	this->m_btnMyApp.LoadBitmap(IDB_MY_APP);

    // ϵͳ���ð�ť
    btnSysSetting.LoadBitmap(IDB_SYSSETTING);

	// ����վ
	m_btnserver.LoadBitmap(IDB_SERVER);

	// ��¼��վ
	m_btnwlr.LoadBitmap(IDB_WLR);

	//GPS��λ
	this->m_btnGPSLocating.LoadBitmap(IDB_GPS_LOCATING);

	// ���水ť    
	btnNotice.LoadBitmap(IDB_NOTICE);

	m_btnPubWayOne.LoadBitmap(IDB_PUBLISH_ONE);
	m_btnPubWayTwo.LoadBitmap(IDB_PUBLISH_TWO);
	m_btnPubWayOne.ShowWindow(SW_HIDE);
	m_btnPubWayTwo.ShowWindow(SW_HIDE);

    // ��ֵ����
    //btnAddValued.LoadBitmap(IDB_ADDVALUED);
    // �Զ�ˢ�°�ť
    //autoRefresh.LoadBitmap(IDB_NOREFRESH);
    // ��ʾ�绰
    //showPhone.LoadBitmap(IDB_SHOWPHONE);
	// ������ť
	//btnSearch.LoadBitmap(IDB_SEARCH);
	//�û�����
	//m_btnuser.LoadBitmap(IDB_CENTER);
    // ���ٷ�����ť xqh:ɾ�����ٷ�������
    //btnQuickPub.LoadBitmap(IDB_QUICKPUB);
	// ���찴ť    
	//btnChat.LoadBitmap(IDB_CHAT);
    return 0;
}
    
// ��ʼ��TAB�ؼ�
int CWLRClientDlg::initTabCtrl()
{
    // ��ʼ��TAB�ؼ���ʽ
    BOOL	m_bFlat;
	BOOL	m_bColor;
	BOOL	m_bSelection;
	BOOL	m_bGradient;
	BOOL	m_bBackTabs;
	BOOL	m_bBackColor;

    COLORREF m_color = GLB::tabCtrlBgColor;
    DWORD dwFlags = 0;

    m_bFlat = 1;
    m_bColor = false;
    m_bSelection = false;
    m_bGradient = false;
    m_bBackTabs = 1;
    m_bBackColor = 1;

    //m_color = RGB(0, 255, 0);
/*
	if (m_bFlat)
		dwFlags |= ETC_FLAT;

	if (m_bColor)
		dwFlags |= ETC_COLOR;

	if (m_bSelection)
		dwFlags |= ETC_SELECTION;

	if (m_bGradient)
		dwFlags |= ETC_GRADIENT;

	if (m_bBackTabs)
		dwFlags |= ETC_BACKTABS;

	mTabMain.SetBkgndColor(m_bBackColor ? m_color : ::GetSysColor(COLOR_3DFACE));
	mTabMain.EnableDraw(m_bFlat ? BTC_ALL : dwFlags ? BTC_TABS : BTC_NONE);
	CEnTabCtrl::EnableCustomLook(dwFlags | 1, dwFlags);
*/
    //�����Ի���,���ҽ�IDC_TAB_Main�ؼ���Ϊ�����ڣ���Դ
    newGoodsInf.Create(IDD_TAB_NEW_INF, GetDlgItem(IDC_TAB_Main));
    customGoodsInf.Create(IDD_TAB_CUSTOM_INF, GetDlgItem(IDC_TAB_Main));
    myGoodsInf.Create(IDD_TAB_MY_INF, GetDlgItem(IDC_TAB_Main));  

    //�����Ի���,���ҽ�IDC_TAB_Main�ؼ���Ϊ�����ڣ��㵣
    newBulkGoodsInf.Create(IDD_TAB_NEW_INF, GetDlgItem(IDC_TAB_Main));
    myBulkGoodsInf.Create(IDD_TAB_MY_INF, GetDlgItem(IDC_TAB_Main)); 

    //�����Ի���,���ҽ�IDC_TAB_Main�ؼ���Ϊ�����ڣ���Դ
    newCarsInf.Create(IDD_TAB_NEW_INF, GetDlgItem(IDC_TAB_Main));
    customCarsInf.Create(IDD_TAB_CUSTOM_INF, GetDlgItem(IDC_TAB_Main));
    myCarsInf.Create(IDD_TAB_MY_INF, GetDlgItem(IDC_TAB_Main));

    //�����Ի���,���ҽ�IDC_TAB_Main�ؼ���Ϊ�����ڣ�ר��
    allspecialLine.Create(IDD_TAB_SPECIAL_LINE, GetDlgItem(IDC_TAB_Main));
    mySpecialLine.Create(IDD_TAB_SPECIAL_LINE, GetDlgItem(IDC_TAB_Main));
    favoriteSpecialLine.Create(IDD_TAB_SPECIAL_LINE, GetDlgItem(IDC_TAB_Main));

    //�����Ի���,���ҽ�IDC_TAB_Main�ؼ���Ϊ�����ڣ�����
    searchGoodsInf.Create(IDD_TAB_NEW_INF, GetDlgItem(IDC_TAB_Main));
    searchBulkGoodsInf.Create(IDD_TAB_NEW_INF, GetDlgItem(IDC_TAB_Main));
    searchCarsInf.Create(IDD_TAB_NEW_INF, GetDlgItem(IDC_TAB_Main));
    searchSpecialLine.Create(IDD_TAB_SPECIAL_LINE, GetDlgItem(IDC_TAB_Main)); 

    setGoodsInf();
    ifInit = true;
    curTabIndex = 0;

    return 0;
}
    
// ��ʼ��Tree�ؼ�
int CWLRClientDlg::initTreeCtrl()
{
    mTreeMain.ModifyStyle(0,WS_VISIBLE|WS_HSCROLL|WS_VSCROLL
		|TVS_LINESATROOT|TVS_HASLINES|TVS_HASBUTTONS|TVS_TRACKSELECT|TVS_SHOWSELALWAYS);
	//pCtrl->SetBkColor(RGB(193,221,186));
	//mTreeMain.SetBkColor(RGB(239,246,236));

	TVINSERTSTRUCT tvInsert;
	tvInsert.hParent = NULL;
	tvInsert.hInsertAfter = NULL;
	tvInsert.item.mask = TVIF_TEXT;
	tvInsert.item.pszText = _T("�й�");

	HTREEITEM hCountry = mTreeMain.InsertItem(&tvInsert);

	vector<Province>::iterator iter = myCR.govProvince.begin();
    while (iter != myCR.govProvince.end()) {
		HTREEITEM hPA = mTreeMain.InsertItem((*iter).name.c_str(), 0, 0, hCountry, NULL);
		vector<City>::iterator iter2 = (*iter).govCity.begin();
		while (iter2 != (*iter).govCity.end()) {
			mTreeMain.InsertItem((*iter2).name.c_str(), 0, 0, hPA, NULL);
			++iter2;
		}
        ++iter;
    }
	mTreeMain.Expand(hCountry, TVE_EXPAND);
    return 0;
}
      
// OnSize
void CWLRClientDlg::OnSize(UINT nType, int cx, int cy)
{
    CDialog::OnSize(nType, cx, cy);   
    // TODO: �ڴ˴������Ϣ����������
	UPDATE_EASYSIZE;  // �Զ��ı�ؼ�λ�ô�С

    if (!ifInit) {
        return;
    }

	//if( nType != SIZE_MAXIMIZED )
	//{
	//	// ��Դ��ť
	//	btnGoods.LoadBitmap(IDB_GOODS_MIN);

	//	// ��Դ��ť
	//	btnCars.LoadBitmap(IDB_CARS_MIN);

	//	// ר�߰�ť
	//	btnSpecial.LoadBitmap(IDB_SPECIAL_MIN);

	//	// ������ť
	//	btnSearch.LoadBitmap(IDB_SEARCH_MIN);

	//	//���հ�ť
	//	btnMainPage.LoadBitmap(IDB_MAINPAGE_MIN);

	//	// �㵣��ť
	//	//btnBulkGoods.LoadBitmap(IDB_BULKGOODS);

	//	//������Դ
	//	this->m_btnReleaseGoods.LoadBitmap(IDB_RELEASE_GOODS_MIN);
	//	//������Դ
	//	this->m_btnReleaseTruckInfo.LoadBitmap(IDB_RELEASE_TRUCK_INFO_MIN);
	//	//����ר��
	//	this->m_btnReleaseSpecialLine.LoadBitmap(IDB_RELEASE_SPECIAL_LINE_MIN);
	//}
	//else
	//{
	//	// ��Դ��ť
	//	btnGoods.LoadBitmap(IDB_GOODS);

	//	// ��Դ��ť
	//	btnCars.LoadBitmap(IDB_CARS);

	//	// ר�߰�ť
	//	btnSpecial.LoadBitmap(IDB_SPECIAL);

	//	// ������ť
	//	btnSearch.LoadBitmap(IDB_SEARCH);

	//	//���հ�ť
	//	btnMainPage.LoadBitmap(IDB_MAINPAGE);
	//	
	//	// �㵣��ť
	//	//btnBulkGoods.LoadBitmap(IDB_BULKGOODS);

	//	//������Դ
	//	this->m_btnReleaseGoods.LoadBitmap(IDB_RELEASE_GOODS);
	//	//������Դ
	//	this->m_btnReleaseTruckInfo.LoadBitmap(IDB_RELEASE_TRUCK_INFO);
	//	//����ר��
	//	this->m_btnReleaseSpecialLine.LoadBitmap(IDB_RELEASE_SPECIAL_LINE);
	//}



	//
	//if( nType != SIZE_MAXIMIZED )
	//{
	//	CRect rc1, rc2;
	//	btnGoods.GetWindowRect(rc1);
	//	btnCars.GetWindowRect(rc2);
	//	ScreenToClient(rc1);
	//	ScreenToClient(rc2);
	//	btnCars.MoveWindow(rc1.right+2, rc2.top, rc2.Width(), rc2.Height());
	//	btnCars.Invalidate();
	//	btnCars.UpdateWindow();
	//}
	//else
	//{
	//	CRect rc1, rc2;
	//	btnGoods.GetWindowRect(rc1);
	//	btnCars.GetWindowRect(rc2);
	//	ScreenToClient(rc1);
	//	ScreenToClient(rc2);
	//	btnCars.MoveWindow(rc1.right+2, rc2.top, rc2.Width(), rc2.Height());
	//	btnCars.Invalidate();
	//	btnCars.UpdateWindow();

	///*	btnCars.MoveWindow(rc1.right+(rc2.left-rc1.right)/2, rc2.top, rc2.Width(), rc2.Height());
	//	btnCars.Invalidate();
	//	btnCars.UpdateWindow();*/
	//}
	//

    /*
        //���IDC_TABTEST�ͻ�����С
    CRect rect;
    mTabMain.GetClientRect(&rect);

    //�����ӶԻ����ڸ������е�λ��
    rect.top+=20; 
    rect.left+=1; 
    rect.right-=2;

    //�����ӶԻ���ߴ粢�ƶ���ָ��λ��
    // ��Դ                
    newGoodsInf.MoveWindow(&rect);
    customGoodsInf.MoveWindow(&rect);
    myGoodsInf.MoveWindow(&rect);

    // �㵣 
    newBulkGoodsInf.MoveWindow(&rect);
    myBulkGoodsInf.MoveWindow(&rect);
 
    // ��Դ
    newCarsInf.MoveWindow(&rect);
    customCarsInf.MoveWindow(&rect);
    myCarsInf.MoveWindow(&rect);

    // ר��

    // ����
*/

/*
    switch (curTabType) {
    case GOODS:  // ��Դ                
        setGoodsInf();
        break;
    case BULKGOODS: // �㵣 
        setBulkGoodsInf();
        break;
    case CARS:      // ��Դ
        break;
    case LINES:     // ר��
        break;
    case SEARCH:     // ����
        break;
    default:
        ;
    }
    */
//*
    //���IDC_TABTEST�ͻ�����С
    CRect rect;
    mTabMain.GetClientRect(&rect);
	
	GLB::ifMiniSize = false;
    // ����С��ʱ
    if(rect.Width() < 1 || rect.Height() < 1) {
		GLB::ifMiniSize = true;
		//SuspendThread(hThread);
		KillTimer(AUTO_REFRESH_TIMER_ID);//ֹͣˢ�£���Ҫ�Ƕ���ҳʱ���ˢ�£�
        return;
    }
// 	DWORD dip = 0;
// 	if (hThread != NULL)
// 	{
// 		while(1)
// 		{
// 			dip = ResumeThread(hThread);
// 			if (dip == 0)
// 			{
// 				break;
// 			}
// 			Sleep(100);
// 		}
// 	}
	//ResumeThread(hThreadLD);
    //�����ӶԻ����ڸ������е�λ��
    rect.top+=20; 
    rect.left+=1; 
    rect.right-=2;

    //�����ӶԻ���ߴ粢�ƶ���ָ��λ��
	//EnterCriticalSection(&csPrint);
    switch (curTabType) {
    case GOODS:  // ��Դ                
        newGoodsInf.MoveWindow(&rect);
        customGoodsInf.MoveWindow(&rect);
        myGoodsInf.MoveWindow(&rect);
        setGoodsInf(curTabIndex);
        break;
    case BULKGOODS: // �㵣 
        newBulkGoodsInf.MoveWindow(&rect);
        myBulkGoodsInf.MoveWindow(&rect);
        setBulkGoodsInf(curTabIndex);
        break;
    case CARS:      // ��Դ
        newCarsInf.MoveWindow(&rect);
        customCarsInf.MoveWindow(&rect);
        myCarsInf.MoveWindow(&rect);
        setCarsInf(curTabIndex);
        break;
    case LINES:     // ר��
        allspecialLine.MoveWindow(&rect);
        mySpecialLine.MoveWindow(&rect);
        favoriteSpecialLine.MoveWindow(&rect);
        setSpecialLineInf(curTabIndex);
        break;
    case SEARCH_GOODS:     // ������Դ
        searchGoodsInf.MoveWindow(&rect);
        searchGoodsInf.ShowWindow(false);
        searchGoodsInf.ShowWindow(true);
        break;
    case SEARCH_BULKGOODS: // �����㵣
        searchBulkGoodsInf.MoveWindow(&rect);
        searchBulkGoodsInf.ShowWindow(false);
        searchBulkGoodsInf.ShowWindow(true);
        break;
    case SEARCH_CARS:      // ������Դ
        searchCarsInf.MoveWindow(&rect);
        searchCarsInf.ShowWindow(false);
        searchCarsInf.ShowWindow(true);
        break;
    case SEARCH_SPECIAL:   // ����ר��
        searchSpecialLine.MoveWindow(&rect);
        searchSpecialLine.ShowWindow(false);
        searchSpecialLine.ShowWindow(true);
        break;
    case CLICK_SEARCH_GOODS:      // ���������Դ
        searchGoodsInf.MoveWindow(&rect);
        searchGoodsInf.ShowWindow(false);
        searchGoodsInf.ShowWindow(true);
        break;
    case CLICK_SEARCH_BULKGOODS:  // ��������㵣
        searchBulkGoodsInf.MoveWindow(&rect);
        searchBulkGoodsInf.ShowWindow(false);
        searchBulkGoodsInf.ShowWindow(true);
        break;
    case CLICK_SEARCH_CARS:       // ���������Դ
        searchCarsInf.MoveWindow(&rect);
        searchCarsInf.ShowWindow(false);
        searchCarsInf.ShowWindow(true);
        break;
    case CLICK_SEARCH_SPECIAL:    // �������ר��
        searchSpecialLine.MoveWindow(&rect);
        searchSpecialLine.ShowWindow(false);
        searchSpecialLine.ShowWindow(true);
        break;
    default:
        ;
    }
    //*/

    // ���ù�������
	//LeaveCriticalSection(&csPrint);
    pubAD.Resize();
}
    
// ���TAB�ؼ����л���ͬ�ı�ǩ
void CWLRClientDlg::OnTcnSelchangeTabMain(NMHDR *pNMHDR, LRESULT *pResult)
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
	KillTimer(AUTO_REFRESH_TIMER_ID);
    int CurSel = mTabMain.GetCurSel();
    curTabIndex = CurSel;
    if (curTabType == GOODS) { // ��Դ 
        setGoodsInf(CurSel);
        /*
        switch(CurSel) { 
        case 0:
            newGoodsInf.ShowWindow(true);
            customGoodsInf.ShowWindow(false);
            myGoodsInf.ShowWindow(false);
            newGoodsInf.setGrid();
            break;
        case 1:
            newGoodsInf.ShowWindow(false);
            customGoodsInf.ShowWindow(true);
            myGoodsInf.ShowWindow(false);
            customGoodsInf.setGrid();
            break; 
        case 2:
            //m_result.UpdateData(false);  
            newGoodsInf.ShowWindow(false);
            customGoodsInf.ShowWindow(false);
            myGoodsInf.ShowWindow(true); 
            myGoodsInf.setGrid();
            break; 
        default: 
            break;
        }
        */
    } else if (curTabType == BULKGOODS) { // �㵣 
        setBulkGoodsInf(CurSel);
        /*
        switch(CurSel) { 
        case 0:
            newBulkGoodsInf.ShowWindow(true);
            myBulkGoodsInf.ShowWindow(false);
            newBulkGoodsInf.setGrid();
            break;
        case 1:
            newBulkGoodsInf.ShowWindow(false);
            myBulkGoodsInf.ShowWindow(true);
            myBulkGoodsInf.setGrid();
            break; 
        default: 
            break;
        }*/
    } else if (curTabType == CARS) {      // ��Դ
        setCarsInf(CurSel);
    } else if (curTabType == LINES) {     // ר��
        setSpecialLineInf(CurSel);;
    } else { // ����
        //setSearchInf(CurSel);;
    }

    *pResult = 0;
}
    
// �����״�ؼ�
void CWLRClientDlg::OnTvnSelchangedTreeMain(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
    // TODO: �ڴ���ӿؼ�֪ͨ����������
	//�õ�ѡ����
    HTREEITEM selectHtm = mTreeMain.GetSelectedItem();
    CString strSelect = mTreeMain.GetItemText(selectHtm);
	KillTimer(AUTO_REFRESH_TIMER_ID);
    //�õ����ڵ���
	HTREEITEM parentHtm = mTreeMain.GetParentItem(selectHtm);
    CString parStr = mTreeMain.GetItemText(parentHtm);

    if (parStr==_T("�й�")||parStr==_T(""))
        return;

	//MessageBox("��ѡ�е���:" + parStr + " " + strSelect);
    
    if(curTabType == GOODS || curTabType == SEARCH_GOODS || curTabType == CLICK_SEARCH_GOODS) {
        InClickSearch tmp;
        tmp.province = (LPTSTR)(LPCTSTR)parStr;
        tmp.city = (LPTSTR)(LPCTSTR)strSelect;
        clickSearchGoods(tmp);
    } else if(curTabType == BULKGOODS || curTabType == SEARCH_BULKGOODS || curTabType == CLICK_SEARCH_BULKGOODS) {
        InClickSearch tmp;
        tmp.province = (LPTSTR)(LPCTSTR)parStr;
        tmp.city = (LPTSTR)(LPCTSTR)strSelect;
        clickSearchBulkGoods(tmp);
    } else if(curTabType == CARS || curTabType == SEARCH_CARS || curTabType == CLICK_SEARCH_CARS) {
        InClickSearch tmp;
        tmp.province = (LPTSTR)(LPCTSTR)parStr;
        tmp.city = (LPTSTR)(LPCTSTR)strSelect;
        clickSearchCars(tmp);
    } else if(curTabType == LINES || curTabType == SEARCH_SPECIAL || curTabType == CLICK_SEARCH_SPECIAL) {
        InClickSearch tmp;
        tmp.province = (LPTSTR)(LPCTSTR)parStr;
        tmp.city = (LPTSTR)(LPCTSTR)strSelect;
        clickSearchSpecialLine(tmp);
    } else {
        /*InClickSearch tmp;
        tmp.province = (LPTSTR)(LPCTSTR)parStr;
        tmp.city = (LPTSTR)(LPCTSTR)strSelect;
        clickSearchGoods(tmp);*/
    }

	*pResult = 0;
}
       
// �������еĴ���
int CWLRClientDlg::hideAllWindows() {
    // ��Դ
    newGoodsInf.ShowWindow(false);
    customGoodsInf.ShowWindow(false);
    myGoodsInf.ShowWindow(false); 

    // �㵣
    newBulkGoodsInf.ShowWindow(false);
    myBulkGoodsInf.ShowWindow(false);

    // ��Դ
    newCarsInf.ShowWindow(false);
    customCarsInf.ShowWindow(false);
    myCarsInf.ShowWindow(false);

    // ר��
    allspecialLine.ShowWindow(false);
    mySpecialLine.ShowWindow(false);
    favoriteSpecialLine.ShowWindow(false);

    // ����
    searchGoodsInf.ShowWindow(false);
    searchBulkGoodsInf.ShowWindow(false);
    searchCarsInf.ShowWindow(false);
    searchSpecialLine.ShowWindow(false);

    return 0;
}
    
// ��������ա���ť
void CWLRClientDlg::OnBnClickedBtnMainpage()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    //string url = "http://www.wibang.com";
    //string url = "http://192.168.10.212";
    /*string str = WEB_SERVICE_ADDRESS + "/fmp/user.login.action?user.name=" + svrIO.userInf.loginName
        + "&user.pwd=" + svrIO.userInf.passWord; 
    //CEmbeddedIeDlg dlg;
    //dlg.url = url;
    //dlg.DoModal();
    ShellExecute(NULL, NULL, "iexplore", str.c_str(), NULL, SW_SHOW);
	*/
	KillTimer(AUTO_REFRESH_TIMER_ID);
	CCameraDlg dlg;
	if (0 == dlg.searchDevice()) {
		dlg.DoModal();
		return;
		//MessageBox("û���ҵ�����ͷ�豸��", "560");
	}
	MessageBox("û���ҵ�����ͷ�豸��", "560");
}
    
// �������Դ����ť
void CWLRClientDlg::OnBnClickedBtnGoods()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
	EnterCriticalSection(&csClick);
	curTabIndex = 0;
    setGoodsInf();
	LeaveCriticalSection(&csClick);
}
    
// ������㵣����ť
void CWLRClientDlg::OnBnClickedBtnBulkgoods()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
	EnterCriticalSection(&csClick);
	curTabIndex = 0;
    setBulkGoodsInf();
	LeaveCriticalSection(&csClick);
}
    
// �������Դ����ť
void CWLRClientDlg::OnBnClickedBtnCars()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
	EnterCriticalSection(&csClick);
	curTabIndex = 0;
    setCarsInf();
	LeaveCriticalSection(&csClick);
}
    
// �����ר�ߡ���ť
void CWLRClientDlg::OnBnClickedBtnLine()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
	EnterCriticalSection(&csClick);
	curTabIndex = 0;
    setSpecialLineInf();
	LeaveCriticalSection(&csClick);
}
    
// �������������ť
void CWLRClientDlg::OnBnClickedBtnSearch()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
	KillTimer(AUTO_REFRESH_TIMER_ID);
    CSearchSelectDlg dlg;
	if (dlg.DoModal() == IDOK) { 
		search(dlg.selectValue, 2);

		//switch (dlg.selectValue) {
		//	case 0: // ������Դ 
  //          {
  //              CSearchGoodsDlg sgDlg;
  //              sgDlg.myCR = &myCR;
  //              if (sgDlg.DoModal() == IDOK) {
  //                  InSearchGoods tmp;
  //                  tmp.startProvince = (LPTSTR)(LPCTSTR)sgDlg.strStartProvince;
  //                  tmp.startCity = (LPTSTR)(LPCTSTR)sgDlg.strStartCity;
  //                  tmp.startCounty = (LPTSTR)(LPCTSTR)sgDlg.strStartCounty;
  //                  tmp.endProvince = (LPTSTR)(LPCTSTR)sgDlg.strEndProvince;
  //                  tmp.endCity = (LPTSTR)(LPCTSTR)sgDlg.strEndCity;
  //                  tmp.endCounty = (LPTSTR)(LPCTSTR)sgDlg.strEndCounty;
  //                  tmp.carLength = (LPTSTR)(LPCTSTR)sgDlg.strCarLength;
  //                  tmp.carType = (LPTSTR)(LPCTSTR)sgDlg.strCarType;
  //                  setSearchGoods(tmp, 2);
  //              }
		//		break;
  //          }
		//	case 1:	// �����㵣
  //          {
  //              CSearchBulkGoodsDlg sbgDlg;
  //              sbgDlg.myCR = &myCR;
  //              if (sbgDlg.DoModal() == IDOK) {
  //                  InSearchBulkGoods tmp;
  //                  tmp.startProvince = (LPTSTR)(LPCTSTR)sbgDlg.strStartProvince;
  //                  tmp.startCity = (LPTSTR)(LPCTSTR)sbgDlg.strStartCity;
  //                  tmp.startCounty = (LPTSTR)(LPCTSTR)sbgDlg.strStartCounty;
  //                  tmp.endProvince = (LPTSTR)(LPCTSTR)sbgDlg.strEndProvince;
  //                  tmp.endCity = (LPTSTR)(LPCTSTR)sbgDlg.strEndCity;
  //                  tmp.endCounty = (LPTSTR)(LPCTSTR)sbgDlg.strEndCounty;
  //                  setSearchBulkGoods(tmp, 2);
  //              }
		//		break;
  //          }
		//	case 2:	// ������Դ
  //          {                
  //              CSearchCarsDlg scDlg;
  //              scDlg.myCR = &myCR;
  //              if (scDlg.DoModal() == IDOK) {
  //                  InSearchCars tmp;
  //                  tmp.startProvince = (LPTSTR)(LPCTSTR)scDlg.strStartProvince;
  //                  tmp.startCity = (LPTSTR)(LPCTSTR)scDlg.strStartCity;
  //                  tmp.startCounty = (LPTSTR)(LPCTSTR)scDlg.strStartCounty;
  //                  tmp.endProvince = (LPTSTR)(LPCTSTR)scDlg.strEndProvince;
  //                  tmp.endCity = (LPTSTR)(LPCTSTR)scDlg.strEndCity;
  //                  tmp.endCounty = (LPTSTR)(LPCTSTR)scDlg.strEndCounty;
  //                  tmp.carLength = (LPTSTR)(LPCTSTR)scDlg.strCarLength;
  //                  tmp.carType = (LPTSTR)(LPCTSTR)scDlg.strCarType;
  //                  setSearchCars(tmp, 2);
  //              }
		//		break;
  //          }
		//	case 3:	// ����ר��
  //          {
  //              CSearchSpecialDlg ssDlg;
  //              ssDlg.myCR = &myCR;
  //              if (ssDlg.DoModal() == IDOK) {
  //                  InSearchSpecail tmp;
  //                  tmp.startProvince = (LPTSTR)(LPCTSTR)ssDlg.strStartProvince;
  //                  tmp.startCity = (LPTSTR)(LPCTSTR)ssDlg.strStartCity;
  //                  tmp.startCounty = (LPTSTR)(LPCTSTR)ssDlg.strStartCounty;
  //                  tmp.endProvince = (LPTSTR)(LPCTSTR)ssDlg.strEndProvince;
  //                  tmp.endCity = (LPTSTR)(LPCTSTR)ssDlg.strEndCity;
  //                  tmp.endCounty = (LPTSTR)(LPCTSTR)ssDlg.strEndCounty;
  //                  setSearchSpecail(tmp, 2);
  //              }
		//		break;
  //          }
		//	default:
		//		//faBuHuoYuan();
  //              break;
		//}
	}
}
    
// �����ϵͳ���á���ť
void CWLRClientDlg::OnBnClickedBtnSetting()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
	//EnterCriticalSection(&csPrint);
    CConfigSetDlg dlg;
    dlg.myColor = svrIO.myColor;
    dlg.oddFont = svrIO.oddFont;
    dlg.evenFont = svrIO.evenFont;
    if (dlg.DoModal() == IDOK) {
        svrIO.myColor = dlg.myColor;
        svrIO.oddFont = dlg.oddFont;
        svrIO.evenFont = dlg.evenFont;

		svrIONew.myColor = dlg.myColor;
		svrIONew.oddFont = dlg.oddFont;
		svrIONew.evenFont = dlg.evenFont;

		svrIOMore.myColor = dlg.myColor;
		svrIOMore.oddFont = dlg.oddFont;
		svrIOMore.evenFont = dlg.evenFont;

		svrIOMy.myColor = dlg.myColor;
		svrIOMy.oddFont = dlg.oddFont;
		svrIOMy.evenFont = dlg.evenFont;

		svrIOCustom.myColor = dlg.myColor;
		svrIOCustom.oddFont = dlg.oddFont;
		svrIOCustom.evenFont = dlg.evenFont;

		svrIOSpecial.myColor = dlg.myColor;
		svrIOSpecial.oddFont = dlg.oddFont;
		svrIOSpecial.evenFont = dlg.evenFont;

		svrIOService.myColor = dlg.myColor;
		svrIOService.oddFont = dlg.oddFont;
		svrIOService.evenFont = dlg.evenFont;

		svrIOPub.myColor = dlg.myColor;
		svrIOPub.oddFont = dlg.oddFont;
		svrIOPub.evenFont = dlg.evenFont;
    }
// 	BYTE nred = ((BYTE)(svrIO.myColor.sysBKClr));
// 	BYTE ngreen = ((BYTE)(svrIO.myColor.sysBKClr))>>8;
// 	BYTE nblue = ((BYTE)(svrIO.myColor.sysBKClr))>>16;
// 
// 	
// 
// 	XTPSkinManager()->RemoveColorFilters();
// 
// 	XTPSkinManager()->AddColorFilter(new CXTPSkinManagerColorFilterShiftRGB(nred,ngreen,nblue));
// 
// 
// 	XTPSkinManager()->RedrawAllControls();
    // ��������
    saveConfig();

    // ˢ�µ�ǰ��ʾ����
    refreshShow();

    // ���½���
	//LeaveCriticalSection(&csPrint);
    //Invalidate();    
    //mTabMain.Invalidate();
    //RedrawWindow(NULL,NULL,RDW_ERASENOW);
}
    
// �������ֵ���񡱰�ť
void CWLRClientDlg::OnBnClickedBtnPayservice()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    CValueAddedServiceDlg dlg;
    dlg.DoModal();
}
    
// ������Զ�ˢ�¡���ť
void CWLRClientDlg::OnBnClickedBtnAutoupdate()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    if (ifAutoRefresh) {
	//	autoRefresh.LoadBitmap(IDB_AUTOREFRESH);
        stopTimer();
      //  autoRefresh.SetWindowTextA("�Զ�ˢ��");
        //ifAutoRefresh = false;
        //MessageBox("�Զ�ˢ���ѹرգ�", "�Զ�ˢ��");
    } else {
		//autoRefresh.LoadBitmap(IDB_NOREFRESH);
        startTimer();
       // autoRefresh.SetWindowTextA("ֹͣˢ��");
        //ifAutoRefresh = true;
        //MessageBox("�Զ�ˢ���ѿ�����", "�Զ�ˢ��");
    }
}
    
// ��������ص绰����ť
void CWLRClientDlg::OnBnClickedBtnHidetel()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
	static int i = 0;
	if (i%2 == 0)
	{
		// showPhone.LoadBitmap(IDB_NOSHOWPHONE);
	} 
	else
	{
		// showPhone.LoadBitmap(IDB_SHOWPHONE);
	}
	i++;
    if (curTabType == GOODS) { // ��Դ 
        switch(curTabIndex) { 
        case 0:
            newGoodsInf.setIfShowPhone(switchShowPhone());
            break;
        case 1:
            customGoodsInf.setIfShowPhone(switchShowPhone());
            break; 
        case 2:
            myGoodsInf.setIfShowPhone(switchShowPhone());
            break; 
        default: 
            break;
        }
    }
    
    if (curTabType == BULKGOODS) { // �㵣 
        switch(curTabIndex) { 
        case 0:
            newBulkGoodsInf.setIfShowPhone(switchShowPhone());
            break;
        case 1:
            myBulkGoodsInf.setIfShowPhone(switchShowPhone());
            break; 
        case 2:
            break; 
        default: 
            break;
        }
    } 
    
    if (curTabType == CARS) { // ��Դ
        switch(curTabIndex) { 
        case 0:
            newCarsInf.setIfShowPhone(switchShowPhone());
            break;
        case 1:
            customCarsInf.setIfShowPhone(switchShowPhone());
            break; 
        case 2:
            myCarsInf.setIfShowPhone(switchShowPhone());
            break; 
        default: 
            break;
        }
    } 
    
    if (curTabType == LINES) { // ר��
        switch(curTabIndex) { 
        case 0:
            allspecialLine.setIfShowPhone(switchShowPhone());
            break;
        case 1:
            mySpecialLine.setIfShowPhone(switchShowPhone());
            break; 
        case 2:
            favoriteSpecialLine.setIfShowPhone(switchShowPhone());
            break; 
        default: 
            break;
        }
    } 

    if (curTabType == SEARCH_GOODS || curTabType == CLICK_SEARCH_GOODS) {
        searchGoodsInf.setIfShowPhone(switchShowPhone());
    } 

    if (curTabType == SEARCH_BULKGOODS || curTabType == CLICK_SEARCH_BULKGOODS) {
        searchBulkGoodsInf.setIfShowPhone(switchShowPhone());
    } 

    if (curTabType == SEARCH_CARS || curTabType == CLICK_SEARCH_CARS) {
        searchCarsInf.setIfShowPhone(switchShowPhone());
    }

    if (curTabType == SEARCH_SPECIAL || curTabType == CLICK_SEARCH_SPECIAL) {
        searchSpecialLine.setIfShowPhone(switchShowPhone());
    }
}
 
/*xqh:ɾ�����ٷ�������
// ��������ٷ�������ť
void CWLRClientDlg::OnBnClickedBtnPub()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    CPubSelectDlg dlg;
	if (dlg.DoModal() == IDOK) { 
		switch (dlg.selectValue) {
			case 0: // ������Դ 
                pubGoodsInf();
				break;
			case 1:	// �����㵣
                pubBulkGoodsInf();
				break;
			case 2:	// ������Դ
                pubCarsInf();
				break;
			case 3:	// ����ר��
                pubSpecialLineInf();
				break;
			default:
				//faBuHuoYuan();
                break;
		}
// 		DWORD dip = 0;
// 		if (hThread != NULL)
// 		{
// 			while(1)
// 			{
// 				dip = ResumeThread(hThread);
// 				if (dip == 0)
// 				{
// 					break;
// 				}
// 				Sleep(100);
// 			}
// 		}
	}
}*/
    
// ���û�Դ��Ϣ

int CWLRClientDlg::setGoodsInf(int tabIndex)
{
    curTabType = GOODS;
    hideAllWindows();

    mTabMain.DeleteAllItems();
    mTabMain.InsertItem(0,"���»�Դ");
    mTabMain.InsertItem(1,"������Ϣ");
    mTabMain.InsertItem(2,"�ҵĻ�Դ");
    
    //���IDC_TABTEST�ͻ�����С
    CRect rect;
    mTabMain.GetClientRect(&rect);

    //�����ӶԻ����ڸ������е�λ��
    rect.top+=20; 
    rect.left+=1; 
    rect.right-=2;
    
    if (0 == tabIndex) { // ���»�Դ    
        //�����ӶԻ���ߴ粢�ƶ���ָ��λ��
		showtype = NewGood;
// 		KillTimer(AUTO_REFRESH_TIMER_ID);
// 		DWORD dip = 0;
// 		if (hThread != NULL)
// 		{
// 			while(1)
// 			{
// 				dip = ResumeThread(hThread);
// 				if (dip == 0)
// 				{
// 					break;
// 				}
// 				Sleep(100);
// 			}
// 		}
        newGoodsInf.MoveWindow(&rect);
        //�ֱ��������غ���ʾ
        newGoodsInf.ShowWindow(true);
        // ��ʾ����
        newGoodsInf.svrIONew = &svrIONew; 
		newGoodsInf.svrIO = &svrIOMore;

        newGoodsInf.setIfShowPhone(ifShowPhone); 
        newGoodsInf.setData(0);
    } else if (1 == tabIndex) { // ������Ϣ
		showtype = CustomGood;
		index = 0;
		SetTimer(AUTO_REFRESH_TIMER_ID, 1500, NULL);
        //�����ӶԻ���ߴ粢�ƶ���ָ��λ��
        customGoodsInf.MoveWindow(&rect);
        //�ֱ��������غ���ʾ
        customGoodsInf.ShowWindow(true);
        // ��ʾ����
        customGoodsInf.svrIO = &svrIO; 
		customGoodsInf.svrIONew = &svrIOCustom;
        customGoodsInf.setIfShowPhone(ifShowPhone); 
        customGoodsInf.setGoods();
    } else { // �ҵĻ�Դ
        //�����ӶԻ���ߴ粢�ƶ���ָ��λ��
		//ResumeThread(hThread);
		showtype = MyGood;
// 		KillTimer(AUTO_REFRESH_TIMER_ID);
// 		DWORD dip = 0;
// 		if (hThread != NULL)
// 		{
// 			while(1)
// 			{
// 				dip = ResumeThread(hThread);
// 				if (dip == 0)
// 				{
// 					break;
// 				}
// 				Sleep(100);
// 			}
// 		}
        myGoodsInf.MoveWindow(&rect);
        //�ֱ��������غ���ʾ
        myGoodsInf.ShowWindow(true); 
        // ��ʾ����
        myGoodsInf.svrIO = &svrIOMy;
		myGoodsInf.svrIONew = &svrIOMy;
        myGoodsInf.setIfShowPhone(ifShowPhone); 
        myGoodsInf.setData(0);
    }    

    //����Ĭ�ϵ�ѡ�
    mTabMain.SetCurSel(tabIndex);

    //mTabMain.UpdateData(false);

    return 0;
}
       
// �����㵣��Ϣ
int CWLRClientDlg::setBulkGoodsInf(int tabIndex)
{
    curTabType = BULKGOODS;
    hideAllWindows();

    mTabMain.DeleteAllItems();
    mTabMain.InsertItem(0,"�����㵣");
    mTabMain.InsertItem(1,"�ҵ��㵣");
    
    //���IDC_TABTEST�ͻ�����С
    CRect rect;
    mTabMain.GetClientRect(&rect);

    //�����ӶԻ����ڸ������е�λ��
    rect.top+=20; 
    rect.left+=1; 
    rect.right-=2;
    
    if (0 == tabIndex) {
		showtype = NewBulkGood;
        // �����ӶԻ���ߴ粢�ƶ���ָ��λ��
        newBulkGoodsInf.MoveWindow(&rect);
        // �ֱ��������غ���ʾ
        newBulkGoodsInf.ShowWindow(true);
        // ��ʾ����
        newBulkGoodsInf.svrIO = &svrIOMore;
		newBulkGoodsInf.svrIONew = &svrIONew;
        newBulkGoodsInf.setIfShowPhone(ifShowPhone); 
        newBulkGoodsInf.setData(1);
    } else {
		showtype = MyBulkGood;
        // �����ӶԻ���ߴ粢�ƶ���ָ��λ��
        myBulkGoodsInf.MoveWindow(&rect);
        // �ֱ��������غ���ʾ
        myBulkGoodsInf.ShowWindow(true);
        // ��ʾ����
        myBulkGoodsInf.svrIO = &svrIOMy; 
		myBulkGoodsInf.svrIONew = &svrIOMy; 
        myBulkGoodsInf.setIfShowPhone(ifShowPhone); 
        myBulkGoodsInf.setData(1);
    }   

    //����Ĭ�ϵ�ѡ�
    mTabMain.SetCurSel(tabIndex);

    return 0;
}    
     
// ���ó�Դ��Ϣ
int CWLRClientDlg::setCarsInf(int tabIndex)
{
    curTabType = CARS;
    hideAllWindows();

    mTabMain.DeleteAllItems();
    mTabMain.InsertItem(0,"���³�Դ");
    mTabMain.InsertItem(1,"������Ϣ");
    mTabMain.InsertItem(2,"�ҵĳ�Դ");
    
    //���IDC_TABTEST�ͻ�����С
    CRect rect;
    mTabMain.GetClientRect(&rect);

    //�����ӶԻ����ڸ������е�λ��
    rect.top+=20; 
    rect.left+=1; 
    rect.right-=2;
    
    if (0 == tabIndex) { // ���³�Դ    
        //�����ӶԻ���ߴ粢�ƶ���ָ��λ��
		//ResumeThread(hThread);
		showtype = NewCar;
// 		KillTimer(AUTO_REFRESH_TIMER_ID);
// 		DWORD dip = 0;
// 		if (hThread != NULL)
// 		{
// 			while(1)
// 			{
// 				dip = ResumeThread(hThread);
// 				if (dip == 0)
// 				{
// 					break;
// 				}
// 				Sleep(100);
// 			}
// 		}
        newCarsInf.MoveWindow(&rect);
        //�ֱ��������غ���ʾ
        newCarsInf.ShowWindow(true);
        // ��ʾ����
        newCarsInf.svrIO = &svrIOMore;
		newCarsInf.svrIONew = &svrIONew;
        newCarsInf.setIfShowPhone(ifShowPhone); 
        newCarsInf.setData(2);
    } else if (1 == tabIndex) { // ������Ϣ
		showtype = CustomCar;
		SetTimer(AUTO_REFRESH_TIMER_ID, 1500, NULL);
        //�����ӶԻ���ߴ粢�ƶ���ָ��λ��
		//Sleep(200);
		index = 0;
        customCarsInf.MoveWindow(&rect);
        //�ֱ��������غ���ʾ
        customCarsInf.ShowWindow(true);
        // ��ʾ����
        customCarsInf.svrIO = &svrIO;
		customCarsInf.svrIONew = &svrIOCustom;
        customCarsInf.setIfShowPhone(ifShowPhone); 
        customCarsInf.setCars();
    } else { // �ҵĳ�Դ
        //�����ӶԻ���ߴ粢�ƶ���ָ��λ��
		//ResumeThread(hThread);
		showtype = MyCar;
        myCarsInf.MoveWindow(&rect);
        //�ֱ��������غ���ʾ
        myCarsInf.ShowWindow(true); 
        // ��ʾ����
        myCarsInf.svrIO = &svrIOMy;
		myCarsInf.svrIONew = &svrIOMy;
        myCarsInf.setIfShowPhone(ifShowPhone); 
        myCarsInf.setData(2);
    }    

    //����Ĭ�ϵ�ѡ�
    mTabMain.SetCurSel(tabIndex);

    return 0;
}
    
// ����ר����Ϣ
int CWLRClientDlg::setSpecialLineInf(int tabIndex)
{
    curTabType = LINES;
    hideAllWindows();

    mTabMain.DeleteAllItems();
    mTabMain.InsertItem(0,"����ר��");
    mTabMain.InsertItem(1,"�ҵ�ר��");
    mTabMain.InsertItem(2,"�ҵ��ղ�");
    
    //���IDC_TABTEST�ͻ�����С
    CRect rect;
    mTabMain.GetClientRect(&rect);

    //�����ӶԻ����ڸ������е�λ��
    rect.top+=20; 
    rect.left+=1; 
    rect.right-=2;
    
    if (0 == tabIndex) { // ����ר��    
        //�����ӶԻ���ߴ粢�ƶ���ָ��λ��
		showtype = NewSpecial;
        allspecialLine.MoveWindow(&rect);
        //�ֱ��������غ���ʾ
        allspecialLine.ShowWindow(true);
        // ��ʾ����
        allspecialLine.svrIO = &svrIOSpecial;
		allspecialLine.svrIONew = &svrIOSpecial;
        allspecialLine.setIfShowPhone(ifShowPhone); 
        allspecialLine.setData(0);
    } else if (1 == tabIndex) { // �ҵ�ר��
         //�����ӶԻ���ߴ粢�ƶ���ָ��λ��
		showtype = MySpecial;
        mySpecialLine.MoveWindow(&rect);
        //�ֱ��������غ���ʾ
        mySpecialLine.ShowWindow(true);
        // ��ʾ����
        mySpecialLine.svrIO = &svrIOSpecial;
		mySpecialLine.svrIONew = &svrIOSpecial;
        mySpecialLine.setIfShowPhone(ifShowPhone); 
        mySpecialLine.setData(1);
    } else { // �ҵ��ղ�
        //�����ӶԻ���ߴ粢�ƶ���ָ��λ��
		showtype = MyFavoritesSpecial;
        favoriteSpecialLine.MoveWindow(&rect);
        //�ֱ��������غ���ʾ
        favoriteSpecialLine.ShowWindow(true);
        // ��ʾ����
        favoriteSpecialLine.svrIO = &svrIOSpecial; 
		favoriteSpecialLine.svrIONew = &svrIOSpecial;
        favoriteSpecialLine.setIfShowPhone(ifShowPhone); 
        favoriteSpecialLine.setData(2);
    }    

    //����Ĭ�ϵ�ѡ�
    mTabMain.SetCurSel(tabIndex);

    return 0;
}
    
void CWLRClientDlg::search(UINT8 nType, UINT8 nOption/* = 1*/)
{
	switch (nType) 
	{
	case eSearchType_Goods: // ������Դ 
		{
			CSearchMainDlg dlg;
			dlg.SetSearchType(eSearchType_Goods);
			if (dlg.DoModal() == IDOK)
			{
				const CSearchCriteria* pSearchCriteria = dlg.GetCurSearchCriteria();
				if( pSearchCriteria != NULL )
				{
					if( (pSearchCriteria->GetSearchType()&eSearchType_Goods) == eSearchType_Goods )
					{
						setSearchGoods(pSearchCriteria, nOption);
					}
					if( (pSearchCriteria->GetSearchType()&eSearchType_Car) == eSearchType_Car )
					{
						setSearchCars(pSearchCriteria, nOption);
					}
				}
				else if(  dlg.ShouldUseSearchFavorite() )
				{
					const CSearchFavorite* pFavorite = dlg.GetUsedSearchFavorite();
					if( pFavorite != NULL ) 
					{
						if( (pFavorite->GetSearchType()&eSearchType_Goods) == eSearchType_Goods )
						{
							setSearchGoods(pFavorite->GetSearchCriteria(), nOption);
						}
						if( (pFavorite->GetSearchType()&eSearchType_Car) == eSearchType_Car )
						{
							setSearchCars(pFavorite->GetSearchCriteria(), nOption);
						}
					}
				}

			}

			break;
		}
	case eSearchType_Car:	// ������Դ
		{                
			CSearchMainDlg dlg;
			dlg.SetSearchType(eSearchType_Car);
			if (dlg.DoModal() == IDOK)
			{
				const CSearchCriteria* pSearchCriteria = dlg.GetCurSearchCriteria();
				if( pSearchCriteria != NULL )
				{
					if( (pSearchCriteria->GetSearchType()&eSearchType_Goods) == eSearchType_Goods )
					{
						setSearchGoods(pSearchCriteria, nOption);
					}
					if( (pSearchCriteria->GetSearchType()&eSearchType_Car) == eSearchType_Car )
					{
						setSearchCars(pSearchCriteria, nOption);
					}
				}
				else if(  dlg.ShouldUseSearchFavorite() )
				{
					const CSearchFavorite* pFavorite = dlg.GetUsedSearchFavorite();
					if( pFavorite != NULL ) 
					{
						if( (pSearchCriteria->GetSearchType()&eSearchType_Goods) == eSearchType_Goods )
						{
							setSearchGoods(pFavorite->GetSearchCriteria(), nOption);
						}
						if( (pSearchCriteria->GetSearchType()&eSearchType_Car) == eSearchType_Car )
						{
							setSearchCars(pFavorite->GetSearchCriteria(), nOption);
						}
					}
				}

			}
			break;
		}
	case eSearchType_SpecialLine:	// ����ר��
		{

			if( nOption == 0 )
			{
				InSearchSpecail tmp;
				tmp.startProvince = user.province;
				tmp.startCity = user.city;
				tmp.startCounty = NO_LIMIT_STRING;
				tmp.endProvince = NO_LIMIT_STRING;
				tmp.endCity = NO_LIMIT_STRING;
				tmp.endCounty = NO_LIMIT_STRING;
				setSearchSpecail(tmp, nOption);
			}
			else if( nOption == 1 )
			{
				InSearchSpecail tmp;
				searchSpecialLine.GetStartAddr(tmp.startProvince, tmp.startCity, tmp.startCounty);
				tmp.endProvince = NO_LIMIT_STRING;
				tmp.endCity = NO_LIMIT_STRING;
				tmp.endCounty = NO_LIMIT_STRING;
				setSearchSpecail(tmp, nOption);
			}
			else
			{
				CSearchSpecialDlg ssDlg;
				ssDlg.myCR = &myCR;
				if (ssDlg.DoModal() == IDOK) {
					InSearchSpecail tmp;
					tmp.startProvince = (LPTSTR)(LPCTSTR)ssDlg.strStartProvince;
					tmp.startCity = (LPTSTR)(LPCTSTR)ssDlg.strStartCity;
					tmp.startCounty = (LPTSTR)(LPCTSTR)ssDlg.strStartCounty;
					tmp.endProvince = (LPTSTR)(LPCTSTR)ssDlg.strEndProvince;
					tmp.endCity = (LPTSTR)(LPCTSTR)ssDlg.strEndCity;
					tmp.endCounty = (LPTSTR)(LPCTSTR)ssDlg.strEndCounty;
					if( tmp.startProvince.empty() )
					{
						tmp.startProvince = NO_LIMIT_STRING;
					}
					if( tmp.startCity.empty() )
					{
						tmp.startCity = NO_LIMIT_STRING;
					}
					if( tmp.startCounty.empty() )
					{
						tmp.startCounty = NO_LIMIT_STRING;
					}
					if( tmp.endProvince.empty() )
					{
						tmp.endProvince = NO_LIMIT_STRING;
					}
					if( tmp.endCity.empty() )
					{
						tmp.endCity = NO_LIMIT_STRING;
					}
					if( tmp.endCounty.empty() )
					{
						tmp.endCounty = NO_LIMIT_STRING;
					}
					setSearchSpecail(tmp, nOption);
				}
			}
			break;
		}
	case eSearchType_BulkGoods:	// �����㵣
		{
			CSearchBulkGoodsDlg sbgDlg;
			sbgDlg.myCR = &myCR;
			if (sbgDlg.DoModal() == IDOK) {
				InSearchBulkGoods tmp;
				tmp.startProvince = (LPTSTR)(LPCTSTR)sbgDlg.strStartProvince;
				tmp.startCity = (LPTSTR)(LPCTSTR)sbgDlg.strStartCity;
				tmp.startCounty = (LPTSTR)(LPCTSTR)sbgDlg.strStartCounty;
				tmp.endProvince = (LPTSTR)(LPCTSTR)sbgDlg.strEndProvince;
				tmp.endCity = (LPTSTR)(LPCTSTR)sbgDlg.strEndCity;
				tmp.endCounty = (LPTSTR)(LPCTSTR)sbgDlg.strEndCounty;
				setSearchBulkGoods(tmp, 2);
			}
			break;
		}
	default:
		//faBuHuoYuan();
		break;
	}
}
// ������Դ
int CWLRClientDlg::setSearchGoods(const CSearchCriteria* pSearchCriteria, UINT8 nOption)
{
	string sSearchCriteria;
	pSearchCriteria->FormatSearchString(sSearchCriteria);
	setSearchGoods(sSearchCriteria, nOption);
    return 0;
}
int CWLRClientDlg::setSearchGoods(const string& sSearchCriteria, UINT8 nOption)
{
    curTabType = SEARCH_GOODS;
    hideAllWindows();

    mTabMain.DeleteAllItems();
    mTabMain.InsertItem(0,"������Դ���");
    
    //���IDC_TABTEST�ͻ�����С
    CRect rect;
    mTabMain.GetClientRect(&rect);

    //�����ӶԻ����ڸ������е�λ��
    rect.top+=20; 
    rect.left+=1; 
    rect.right-=2;    
  
    //�����ӶԻ���ߴ粢�ƶ���ָ��λ��
    searchGoodsInf.MoveWindow(&rect);
    //�ֱ��������غ���ʾ
    searchGoodsInf.ShowWindow(true);
    // ��ʾ����
    searchGoodsInf.svrIO = &svrIO; 
    searchGoodsInf.svrIONew = &svrIONew; 
	//searchGoodsInf.goodsKeyword = input;
	searchGoodsInf.sSearchCriteria = sSearchCriteria;
	//FillGoodsSearchCriteria(pSearchCriteria, searchGoodsInf.goodsKeyword);
    searchGoodsInf.setIfShowPhone(ifShowPhone); 
    searchGoodsInf.setData(3);

	//option:0�����أ�1��ȡ����2����������
	/*searchGoodsInf.SetStartAddr(input.startProvince, input.startCity, input.startCounty, true);
	searchGoodsInf.SetDestAddr(input.endProvince, input.endCity, input.endCounty, nOption==2?true:false);

	newGoodsInf.SetStartAddr(input.startProvince, input.startCity, input.startCounty, true);
	newGoodsInf.SetDestAddr(input.endProvince, input.endCity, input.endCounty, nOption==2?true:false);*/
    return 0;
}
    
// �����㵣
int CWLRClientDlg::setSearchBulkGoods(const InSearchBulkGoods& input, UINT8 nOption)
{
    curTabType = SEARCH_BULKGOODS;
    hideAllWindows();

    mTabMain.DeleteAllItems();
    mTabMain.InsertItem(0,"�����㵣���");
    
    //���IDC_TABTEST�ͻ�����С
    CRect rect;
    mTabMain.GetClientRect(&rect);

    //�����ӶԻ����ڸ������е�λ��
    rect.top+=20; 
    rect.left+=1; 
    rect.right-=2;    
  
    //�����ӶԻ���ߴ粢�ƶ���ָ��λ��
    searchBulkGoodsInf.MoveWindow(&rect);
    //�ֱ��������غ���ʾ
    searchBulkGoodsInf.ShowWindow(true);
    // ��ʾ����
    searchBulkGoodsInf.svrIO = &svrIO; 
    searchBulkGoodsInf.svrIONew = &svrIONew;
    searchBulkGoodsInf.setIfShowPhone(ifShowPhone); 
    searchBulkGoodsInf.bulkGoodsKeyword = input;
    searchBulkGoodsInf.setData(4);
    return 0;
}
    
// ������Դ
int CWLRClientDlg::setSearchCars(const CSearchCriteria* pSearchCriteria, UINT8 nOption)
{   
	string sSearchCriteria;
	pSearchCriteria->FormatSearchString(sSearchCriteria);
	setSearchCars(sSearchCriteria, nOption);
    return 0;
}

int CWLRClientDlg::setSearchCars(const string& sSearchCriteria, UINT8 nOption)
{   
    curTabType = SEARCH_CARS;
    hideAllWindows();

    mTabMain.DeleteAllItems();
    mTabMain.InsertItem(0,"������Դ���");
    
    //���IDC_TABTEST�ͻ�����С
    CRect rect;
    mTabMain.GetClientRect(&rect);

    //�����ӶԻ����ڸ������е�λ��
    rect.top+=20; 
    rect.left+=1; 
    rect.right-=2;    
  
    //�����ӶԻ���ߴ粢�ƶ���ָ��λ��
    searchCarsInf.MoveWindow(&rect);
    //�ֱ��������غ���ʾ
    searchCarsInf.ShowWindow(true);
    // ��ʾ����
    searchCarsInf.svrIO = &svrIO; 
	searchCarsInf.svrIONew = &svrIONew; 
	searchCarsInf.sSearchCriteria = sSearchCriteria;
    searchCarsInf.setIfShowPhone(ifShowPhone); 
    searchCarsInf.setData(5);

	/*searchCarsInf.SetStartAddr(input.startProvince, input.startCity, input.startCounty, true);
	searchCarsInf.SetDestAddr(input.endProvince, input.endCity, input.endCounty, nOption==2?true:false);

	newCarsInf.SetStartAddr(input.startProvince, input.startCity, input.startCounty, true);
	newCarsInf.SetDestAddr(input.endProvince, input.endCity, input.endCounty, nOption==2?true:false);*/
    return 0;
}
    
// ����ר��
int CWLRClientDlg::setSearchSpecail(const InSearchSpecail& input, UINT8 nOption)
{
    curTabType = SEARCH_SPECIAL;
    hideAllWindows();

    mTabMain.DeleteAllItems();
    mTabMain.InsertItem(0,"����ר�߽��");
    
    //���IDC_TABTEST�ͻ�����С
    CRect rect;
    mTabMain.GetClientRect(&rect);

    //�����ӶԻ����ڸ������е�λ��
    rect.top+=20; 
    rect.left+=1; 
    rect.right-=2;    
  
    searchSpecialLine.MoveWindow(&rect);
    //�ֱ��������غ���ʾ
    searchSpecialLine.ShowWindow(true);
    // ��ʾ����
    searchSpecialLine.svrIO = &svrIO; 
	searchSpecialLine.svrIONew = &svrIONew;
	searchSpecialLine.specialKeyword = input;
    searchSpecialLine.setIfShowPhone(ifShowPhone);
    searchSpecialLine.setData(3);

	searchSpecialLine.SetStartAddr(input.startProvince, input.startCity, input.startCounty, true);
	searchSpecialLine.SetDestAddr(input.endProvince, input.endCity, input.endCounty, nOption==2?true:false);

	allspecialLine.SetStartAddr(input.startProvince, input.startCity, input.startCounty, true);
	allspecialLine.SetDestAddr(input.endProvince, input.endCity, input.endCounty, nOption==2?true:false);

    return 0;
}
    
// ���õ��������Ϣ����Դ
int CWLRClientDlg::clickSearchGoods(InClickSearch input)
{
    curTabType = CLICK_SEARCH_GOODS;

    hideAllWindows();

    mTabMain.DeleteAllItems();
    mTabMain.InsertItem(0,"������Դ���");
    
    //���IDC_TABTEST�ͻ�����С
    CRect rect;
    mTabMain.GetClientRect(&rect);

    //�����ӶԻ����ڸ������е�λ��
    rect.top+=20; 
    rect.left+=1; 
    rect.right-=2;

    //�����ӶԻ���ߴ粢�ƶ���ָ��λ��
    searchGoodsInf.MoveWindow(&rect);
    //�ֱ��������غ���ʾ
    searchGoodsInf.ShowWindow(true);
    // ��ʾ����
    searchGoodsInf.svrIO = &svrIO;
	searchGoodsInf.svrIONew = &svrIONew;
    searchGoodsInf.setIfShowPhone(ifShowPhone); 
    searchGoodsInf.clickKeyWord = input;
    searchGoodsInf.setData(6);

    //����Ĭ�ϵ�ѡ�
    mTabMain.SetCurSel(0);

    return 0;
}
    
// ���õ��������Ϣ���㵣
int CWLRClientDlg::clickSearchBulkGoods(InClickSearch input)
{
    curTabType = CLICK_SEARCH_BULKGOODS;
    hideAllWindows();

    mTabMain.DeleteAllItems();
    mTabMain.InsertItem(0,"�����㵣���");
    
    //���IDC_TABTEST�ͻ�����С
    CRect rect;
    mTabMain.GetClientRect(&rect);

    //�����ӶԻ����ڸ������е�λ��
    rect.top+=20; 
    rect.left+=1; 
    rect.right-=2;    
  
    // �����ӶԻ���ߴ粢�ƶ���ָ��λ��
    searchBulkGoodsInf.MoveWindow(&rect);
    // �ֱ��������غ���ʾ
    searchBulkGoodsInf.ShowWindow(true);
    // ��ʾ����
    searchBulkGoodsInf.svrIO = &svrIO;
	searchBulkGoodsInf.svrIONew = &svrIONew;
    searchBulkGoodsInf.setIfShowPhone(ifShowPhone); 
    searchBulkGoodsInf.clickKeyWord = input;
    searchBulkGoodsInf.setData(7);

    //����Ĭ�ϵ�ѡ�
    mTabMain.SetCurSel(0);
    return 0;
}   
    
// ���õ��������Ϣ����Դ
int CWLRClientDlg::clickSearchCars(InClickSearch input)
{
    curTabType = CLICK_SEARCH_CARS;
    hideAllWindows();

    mTabMain.DeleteAllItems();
    mTabMain.InsertItem(0,"������Դ���");
    
    //���IDC_TABTEST�ͻ�����С
    CRect rect;
    mTabMain.GetClientRect(&rect);

    //�����ӶԻ����ڸ������е�λ��
    rect.top+=20; 
    rect.left+=1; 
    rect.right-=2;
  
    //�����ӶԻ���ߴ粢�ƶ���ָ��λ��
    searchCarsInf.MoveWindow(&rect);
    //�ֱ��������غ���ʾ
    searchCarsInf.ShowWindow(true);
    // ��ʾ����
    searchCarsInf.svrIO = &svrIO; 
	searchCarsInf.svrIONew = &svrIONew;
    searchCarsInf.setIfShowPhone(ifShowPhone); 
    searchCarsInf.clickKeyWord = input;
    searchCarsInf.setData(8);

    //����Ĭ�ϵ�ѡ�
    mTabMain.SetCurSel(0);
    return 0;
}
    
// ���õ��������Ϣ��ר��
int CWLRClientDlg::clickSearchSpecialLine(InClickSearch input)
{
    curTabType = CLICK_SEARCH_SPECIAL;
    hideAllWindows();

    mTabMain.DeleteAllItems();
    mTabMain.InsertItem(0,"����ר�߽��");
    
    //���IDC_TABTEST�ͻ�����С
    CRect rect;
    mTabMain.GetClientRect(&rect);

    //�����ӶԻ����ڸ������е�λ��
    rect.top+=20; 
    rect.left+=1; 
    rect.right-=2;
  
    //�����ӶԻ���ߴ粢�ƶ���ָ��λ��
    searchSpecialLine.MoveWindow(&rect);
    //�ֱ��������غ���ʾ
    searchSpecialLine.ShowWindow(true);
    // ��ʾ����
    searchSpecialLine.svrIO = &svrIO; 
	searchSpecialLine.svrIONew = &svrIONew;
    searchSpecialLine.clickKeyWord = input;
    searchSpecialLine.setIfShowPhone(ifShowPhone); 
    searchSpecialLine.setData(4);

    //����Ĭ�ϵ�ѡ�
    mTabMain.SetCurSel(0);

    return 0;
}
        
// ������Դ
int CWLRClientDlg::pubGoodsInf()
{
	//SuspendThread(hThread);
	//Sleep(100);
	curTabType = GOODS;
	curTabIndex = 0;
    CPubGoodsDlg dlg;
    dlg.myCR = &myCR;
    dlg.userInfo = svrIOPub.userInf;
    if (dlg.DoModal() == IDOK) {
		string result;
		try
		{
			 result = svrIOPub.setPubGoodsInf(dlg.pubInf);
		}
		catch(...)
		{
			//goto HH;
		}
        if ("TRUE" !=  result) {
            MessageBox(result.c_str());
        } else {
            MessageBox("��Դ�����ɹ���");
			//Sleep(2000);
            // ˢ����ʾ
			try
			{
				setGoodsInf();
			}
			catch (...)
			{
				
			}

            
        }
    }    
	//DWORD dip = 0;
	//dip = ResumeThread(hThread);

    return 0;
}
    
// �����㵣
int CWLRClientDlg::pubBulkGoodsInf()
{
	//SuspendThread(hThread);
	curTabType =BULKGOODS;
	curTabIndex = 0;
	//Sleep(100);
    CPubBulkGoodsDlg dlg;
    dlg.myCR = &myCR;
    dlg.userInfo = svrIOPub.userInf;
    if (dlg.DoModal() == IDOK) {
		string result;
		try
		{
			result = svrIOPub.setPubBulkGoodsInf(dlg.pubInf);
		}
		catch(...)
		{
			//goto HH;
		}
        //string result = svrIO.setPubBulkGoodsInf(dlg.pubInf);
        if ("TRUE" !=  result) {
            MessageBox(result.c_str());
        } else {
            MessageBox("�㵣�����ɹ���");
			//Sleep(2000);
            // ˢ����ʾ
			try
			{
				setBulkGoodsInf();
			}
			catch (...)
			{

			}
            
        }
    }
	//DWORD dip = 0;

	//dip = ResumeThread(hThread);

    return 0;
}
    
// ������Դ
int CWLRClientDlg::pubCarsInf()
{
	//SuspendThread(hThread);
	curTabType = CARS;
	curTabIndex = 0;
	//Sleep(100);
    CPubCarsDlg dlg;
    dlg.myCR = &myCR;
    dlg.userInfo = svrIOPub.userInf;
    if (dlg.DoModal() == IDOK) {  
		string result;
		try
		{
			result = svrIOPub.setPubCarsInf(dlg.pubInf);
		}
		catch(...)
		{
			//goto HH;
		}
        //string result = svrIO.setPubCarsInf(dlg.pubInf);
        if ("TRUE" !=  result) {
            MessageBox(result.c_str());
        } else {
            MessageBox("��Դ�����ɹ���");
			//Sleep(2000);
            // ˢ����ʾ
			try
			{
				 setCarsInf();
			}
			catch (...)
			{

			}
           
        }
    }
	//DWORD dip = 0;

	//dip = ResumeThread(hThread);

    return 0;
}
    
// ����ר��
int CWLRClientDlg::pubSpecialLineInf()
{
	//SuspendThread(hThread);
	curTabType = LINES;
	//Sleep(100);
	curTabIndex = 0;
    CPubSpecialDlg dlg;
    dlg.myCR = &myCR;
    dlg.userInfo = svrIOPub.userInf;
    if (dlg.DoModal() == IDOK) {   
		string result;
		try
		{
			result = svrIOPub.setPubSpecialLineInf(dlg.pubInf);
		}
		catch(...)
		{
			//goto HH;
		}
       // string result = svrIO.setPubSpecialLineInf(dlg.pubInf);
        if ("TRUE" !=  result) {
            MessageBox(result.c_str());
        } else {
            MessageBox("ר�߷����ɹ���");
			//Sleep(2000);
            // ˢ����ʾ
			try
			{
				setSpecialLineInf();
			}
			catch (...)
			{
			}
            
        }
    }
	//DWORD dip = 0;

	//dip = ResumeThread(hThread);

    return 0;
}
    
// ˢ�µ�ǰ��ʾ
void CWLRClientDlg::refreshShow()
{
	//return;
	try 
	{
		//EnterCriticalSection(&csPrintFresh);
		if (curTabType == GOODS) { // ��Դ 
			switch(curTabIndex) { 
		case 0:
			newGoodsInf.setData(0, -1);
			break;
		case 1:
			if (!customGoodsInf.m_bFresh)
			{
				customGoodsInf.setGoods(-1);
			}
			break; 
		case 2:
			myGoodsInf.setData(0, -1);
			break; 
		default: 
			break;
			}
		} else if (curTabType == BULKGOODS) { // �㵣 
			switch(curTabIndex) { 
		case 0:
			newBulkGoodsInf.setData(1, -1);
			break;
		case 1:
			myBulkGoodsInf.setData(1, -1);
			break; 
		default: 
			break;
			}
		} else if (curTabType == CARS) {      // ��Դ
			switch(curTabIndex) { 
		case 0:
			newCarsInf.setData(2, -1);
			break;
		case 1:
			if (!customCarsInf.m_bFresh)
			{
				customCarsInf.setCars(-1);
			}
			break; 
		case 2:
			myCarsInf.setData(2, -1);
			break; 
		default: 
			break;
			}
		} else if (curTabType == LINES) { // ר��
			switch(curTabIndex) { 
		case 0:
			allspecialLine.setData(0, -1);
			break;
		case 1:
			mySpecialLine.setData(1, -1);
			break; 
		case 2:
			favoriteSpecialLine.setData(2, -1);
			break; 
		default: 
			break;
			}
		} else { 
			;
		} 
		//LeaveCriticalSection(&csPrintFresh);
	}
	catch (...)
	{
		//AfxMessageBox("1");
	}

}
    
// ��ʱ��
void CWLRClientDlg::OnTimer(UINT_PTR nIDEvent)
{
    // TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (nIDEvent == 1)
	{
		//KillTimer(1);

		/**/static int i=0;
		if (i%2 == 0)
		{
			OnBnClickedBtnCars();
		}
		else
		{
			OnBnClickedBtnLine();

		}
		i++;
		//CProgressDlg dlg;
		//dlg.DoModal();
	}
	if (nIDEvent == AUTO_REFRESH_TIMER_ID) {  // ˢ����ʾ
		//EnterCriticalSection(&csPrint);
		//TRACE("1\n");
        //refreshShow();
		//LeaveCriticalSection(&csPrint);
	}

	if (nIDEvent == CHECK_NOTICE_TIMER_ID) { // ��鹫��
		//EnterCriticalSection(&csPrint);
		try
		{
			if (!GLB::ifMiniSize)//��С����ʱ�򲻵�������
			{
				KillTimer(CHECK_NOTICE_TIMER_ID);
				checkNotice();
			}
			
		}
		catch (...)
		{
		}
        //checkNotice();
		//LeaveCriticalSection(&csPrint);
	}

	if (nIDEvent == START_CHAT_CLIENT) {  // �����������
        startChatClient();
		KillTimer(START_CHAT_CLIENT);
	}

	if (nIDEvent == SEND_ACCOUNT_MSG_TO_CHAT) { // �����������Ϣ
        sendAcountMsgToChat();
	}

    CDialog::OnTimer(nIDEvent);
}
    
// ������������
void CWLRClientDlg::startShowAD()
{
    pubAD.Create(this, &svrIO);//������洴��
}
        
// ���ڻ���Ӧ�ó�����ֹʱ����
void CWLRClientDlg::OnClose()
{
    // TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	SetEvent(hEvent);
	m_break = TRUE;
	m_bClose = TRUE;
	if(::WaitForSingleObject(hThread,1000)!=WAIT_OBJECT_0)
		TerminateThread(hThread,0x111);


    CDialog::OnOK();
}
    
// ���ٴ���
BOOL CWLRClientDlg::DestroyWindow()
{
    // TODO: �ڴ����ר�ô����/����û���
    //�˳�skinfeature����⣬�ͷ��ڴ���Դ�� 
    //UnLoadSkin();

    return CDialog::DestroyWindow();
}
    
// ��鹫��
int CWLRClientDlg::checkNotice()
{
     //string result1 = svrIO.getSystemScrollAd();
     //string result2 = svrIO.getAgentPopAd();
	if (GLB::ifMiniSize)
	{
		return -1;
	}
    //if ("TRUE" != result1 && "TRUE" != result2)
    //    return -1;

    string showMsg(""),showMsgag("");
    showMsg += "\n��ϵͳ��" + svrIO.sysScrollAd.inf + "\n";
    showMsg += "\n�������̡�" + svrIO.agPopAd.inf + "\n";
    
    CRect rect;
    GetWindowRect(&rect);

    // ������ģ̬�Ի���
    CPopNoticeDlg *dlg = new CPopNoticeDlg;
    dlg->setPos(rect.right, rect.bottom);
    dlg->showMsg = showMsg.c_str();
	dlg->showMsgAG = showMsgag.c_str();
    dlg->Create(IDD_POP_NOTICE, this);
    dlg->ShowWindow(SW_SHOW);
    //dlg.DoModal();
	result1 = "";
	result2 = "";

    return 0;
}

// ���水ť
void CWLRClientDlg::OnBnClickedBtnNotice()
{
    // TODO: �ڴ���ӿؼ�֪ͨ���������롢
    string showMsg(""),showMsgag("");
    //svrIO.getSystemScrollAd();
    showMsg += "\n��ϵͳ��" + svrIO.sysScrollAd.inf + "\n";

    //svrIO.getAgentPopAd();
    showMsg += "\n�������̡�" + svrIO.agPopAd.inf + "\n";

    CRect rect;
    GetWindowRect(&rect);

    // ������ģ̬�Ի���
    CPopNoticeDlg *dlg = new CPopNoticeDlg;
    dlg->setPos(rect.right, rect.bottom);
    dlg->showMsg = showMsg.c_str();
	//dlg->showMsgAG = showMsgag.c_str();
    dlg->Create(IDD_POP_NOTICE, this);
    dlg->ShowWindow(SW_SHOW);
}

// �������ƿؼ�
HBRUSH CWLRClientDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

    // TODO:  �ڴ˸��� DC ���κ�����
   /* if(nCtlColor == CTLCOLOR_DLG) { // ���öԻ��򱳾�ɫ        
        bgBrush.DeleteObject();
        bgBrush.CreateSolidBrush(GLB::mainDlgBgColor);
        return bgBrush;  
    }
    */
    //pDC->SetBkColor(svrIO.myColor.sysBKClr);    
   
    // TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
    return hbr;
}
    
// ��������ͻ���
int CWLRClientDlg::startChatClient()
{	// start chat

	TCHAR szStylesPath[_MAX_PATH];

	VERIFY(::GetModuleFileName(
		AfxGetApp()->m_hInstance, szStylesPath, _MAX_PATH));		

	CString csStylesPath(szStylesPath);
	int nIndex  = csStylesPath.ReverseFind(_T('\\'));
	if (nIndex > 0) {
		csStylesPath = csStylesPath.Left(nIndex);
	}
	else {
		csStylesPath.Empty();
	}
	CString path;
	path = csStylesPath;
	path += "\\chat.exe";
	ShellExecute(this->m_hWnd, "open", path, "", "", SW_SHOW);

	// ���������˺���Ϣ������ͻ��˶�ʱ��
    SetTimer(SEND_ACCOUNT_MSG_TO_CHAT, 1000, NULL);
	return 0;
}
    
// ������ͻ��˷��˺���Ϣ
int CWLRClientDlg::sendAcountMsgToChat()
{	
	CWnd * pWnd = NULL;
	pWnd = CWnd::FindWindow(NULL, "560����ͻ���");
	if (pWnd == NULL) {
		return 0;
	}
	
	// �رն�ʱ��
	KillTimer(SEND_ACCOUNT_MSG_TO_CHAT);
	
	//CString data = "first;test10;wlr";
	CString data = "first;";
	data = data + svrIO.userInf.loginName.c_str();
	data = data + ";";
	data = data + svrIO.userInf.province.c_str();
	data = data + ";";
	data = data + svrIO.userInf.city.c_str();
	data = data + ";wlr";
	COPYDATASTRUCT cpd;                     // ��COPYDATASTRUCT�ṹ��ֵ
	cpd.dwData = 0;
	cpd.cbData = data.GetLength();
	cpd.lpData = (void*)data.GetBuffer(cpd.cbData);
	if (pWnd != NULL)
	{
		pWnd->SendMessage(WM_COPYDATA,NULL,(LPARAM)&cpd);   // ����
	}
	return 0;
}


// ������ͻ��˷�λ����Ϣ
void CWLRClientDlg::OnMove(int x, int y)
{
	CDialog::OnMove(x, y);

	// TODO: �ڴ˴������Ϣ����������

	/*CWnd * pWnd = CWnd ::FindWindow(NULL, "560����ͻ���");

	if(pWnd==NULL)
	{
		return;
	}
	static int g=0;
	if (g ==0)
	{
		GetWindowRect(&rectw);
	}
	CRect rect1,rect;
	GetWindowRect(&rect);
	g++;

	CString data;
	data.Format("pixel;%d;%d;%d;%d;",rect.left-rectw.left,rect.top-rectw.top,rect.right-rectw.right,rect.bottom-rectw.right);

	COPYDATASTRUCT cpd;                     // ��COPYDATASTRUCT�ṹ��ֵ

	cpd.dwData = 0;

	cpd.cbData = data.GetLength();

	cpd.lpData = (void*)data.GetBuffer(cpd.cbData);
	CRect r;
	pWnd->GetWindowRect(&r);
	static int fir = 0;
	//�жϵ�ǰҪ�����Ĵ����Ƿ��ڷ�Χ������
	if (abs(r.left - rect.right) < 10 && !m_dock)//��������״̬
	{
		CString data1 = "move;";
		
		COPYDATASTRUCT cpd1;                     // ��COPYDATASTRUCT�ṹ��ֵ

		cpd1.dwData = 0;

		cpd1.cbData = data1.GetLength();

		cpd1.lpData = (void*)data1.GetBuffer(cpd1.cbData);

		pWnd->SendMessage(WM_COPYDATA,NULL,(LPARAM)&cpd1);   // ����
		m_dock = TRUE;
	} 

	if (m_dock)
	{
		pWnd->SendMessage(WM_COPYDATA,NULL,(LPARAM)&cpd);   // ����
	}
	rectw = rect;*/
}


// ��������ͻ�����Ϣ
BOOL CWLRClientDlg::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
{
	USES_CONVERSION;
	CString m_strCopyData;
	m_strCopyData.Format("%s", (LPCSTR)pCopyDataStruct->lpData);
	m_strCopyData=m_strCopyData.Left(pCopyDataStruct->cbData);
	if (m_strCopyData == "true")
	{
		m_dock = TRUE;
	} 
	else
	{
		m_dock = FALSE;
	}
	return 0;
}
//������찴ť
void CWLRClientDlg::OnBnClickedBtnChat()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	startChatClient();
}

//��ʱ��ȡ����
DWORD CWLRClientDlg::Proc(LPVOID lpVoid)
{
	
	CoInitialize(NULL);
	CWLRClientDlg *pDlg=(CWLRClientDlg*)lpVoid;
	DWORD dwWait;
	inputParam curInput;
	curInput.curpage =1;
	curInput.record = RECORD_NUM;
	curInput.customid = "0";

	while((dwWait=::WaitForSingleObject(pDlg->hEvent,1000))!=WAIT_OBJECT_0)
	{	
		EnterCriticalSection(&csPrint);
		while(1)//���»�Դ
		{
			int i = 90;//��ʼ����С�������ж��Ƿ���ȡ��ȫ���߶���
			try 
			{
				inputParam curInput;
				curInput.curpage =1;
				curInput.record = RECORD_NUM;//��¼����+nnewhy
				curInput.customid = "0";
				i = pDlg->svrIO.getNewGoodsInf(contentDataHY, curInput);
				while (1)
				{
					if (i==0)//���ݽ�����ȫ
					{
						retValue = pDlg->svrIO.getAgentScrollAd();//���������

						result1 = pDlg->svrIO.getSystemScrollAd();//��������

						result2 = pDlg->svrIO.getAgentPopAd();

						if ("TRUE" == result1 || "TRUE" == result2)
							::SendMessage(pDlg->GetSafeHwnd(),WM_TCGG,0,0);//֪ͨ��Ϣ���������溯��
						string s = pDlg->svrIO.getUserCustomInfHY();
						
						
						if (s == "TRUE")
						{
							zoneInfHY = pDlg->svrIO.hyZoneInf;								
						}
						else
							zoneInfHY.clear();

						s = "";
						s = pDlg->svrIO.getUserCustomInfCY();
						if (s == "TRUE")
						{
							zoneInfCY = pDlg->svrIO.cyZoneInf;
						}
						else
							zoneInfCY.clear();
						//��Դ ��Դ���ư�ʱ������ ����

						sort(zoneInfHY.begin(),zoneInfHY.end(),greatermark);
						sort(zoneInfCY.begin(),zoneInfCY.end(),greatermark);

						if(showtype == NewGood)
						::SendMessage(pDlg->GetSafeHwnd(),WM_SENDFRESH,0,0);
						break;
					}
					if (i == -1)//�������
					{
						//���µ�½
						string result = pDlg->svrIO.usrLogin(user.loginName, user.passWord);
						if (result != "TRUE") {//��½���ɹ�������½

							if (pDlg->m_break)//�ر�ʱ������ѭ��
							{
								break;
							}
						} else {//��½�ɹ�������ѭ��
							break;
						}
					}
					Sleep(100);
				}
				break;
			}
			catch (...)
			{
			}
		}
		LeaveCriticalSection(&csPrint);

		EnterCriticalSection(&csPrint);//������Ϣ��Դ

		while(1)
		{
start1:
			if (nCysize > zoneInfCY.size())
			{
				nCysize = 1;
				if(showtype == CustomCar)
					::SendMessage(pDlg->GetSafeHwnd(),WM_SENDFRESH,0,0);
				break;

			}
			//for (int j = 0;j<zoneInfHY.size();j++)
			{
				int i = 90;//��ʼ����С�������ж��Ƿ���ȡ��ȫ���߶���
				try 
				{
					inputParam curInput;
					curInput.curpage =1;
					curInput.record = RECORD_NUM;
					curInput.customid = zoneInfCY.at(nCysize-1).id;
					//AfxMessageBox(curInput.customid.c_str());
					i = pDlg->svrIO.getCustomCarsInf(contentDataDZCY[nCysize-1], curInput);
					while (1)
					{
						if (i==0)//���ݽ�����ȫ
						{
							if(showtype == CustomCar)
							::SendMessage(pDlg->GetSafeHwnd(),WM_SENDFRESH,0,0);
							nCysize++;
							goto start1;
							//continue;
						}
						if (i == -1)//�������
						{
							//���µ�½
							string result = pDlg->svrIO.usrLogin(user.loginName, user.passWord);
							if (result != "TRUE") {//��½���ɹ�������½
								if (pDlg->m_break)//�ر�ʱ������ѭ��
								{
									break;
								}

							} else {//��½�ɹ�������ѭ��
								break;
							}
						}
						Sleep(100);
					}
					break;
				}
				catch (...)
				{

				}
			}
			break;
		}

		LeaveCriticalSection(&csPrint);
		EnterCriticalSection(&csPrint);//������Ϣ��Դ
		while(1)
		{
			start:
			if (nHysize > zoneInfHY.size())
			{
				nHysize = 1;
				if(showtype == CustomGood)
					::SendMessage(pDlg->GetSafeHwnd(),WM_SENDFRESH,0,0);
				break;
				
			}
			//for (int j = 0;j<zoneInfHY.size();j++)
			{
				int i = 90;//��ʼ����С�������ж��Ƿ���ȡ��ȫ���߶���
				try 
				{
					inputParam curInput;
					curInput.curpage =1;
					curInput.record = RECORD_NUM;
					curInput.customid = zoneInfHY.at(nHysize-1).id;
					//
					i = pDlg->svrIO.getCustomGoodsInf(contentDataDZHY[nHysize-1], curInput);
					while (1)
					{
						if (i==0)//���ݽ�����ȫ
						{
							if(showtype == CustomGood)
							::SendMessage(pDlg->GetSafeHwnd(),WM_SENDFRESH,0,0);
							nHysize++;
							goto start;
						}
						if (i == -1)//�������
						{
							//���µ�½
							string result = pDlg->svrIO.usrLogin(user.loginName, user.passWord);
							if (result != "TRUE") {//��½���ɹ�������½
								if (pDlg->m_break)//�ر�ʱ������ѭ��
								{
									break;
								}

							} else {//��½�ɹ�������ѭ��
								break;
							}
						}
						Sleep(100);
					}
					break;
				}
				catch (...)
				{
				}
			}
			break;
		}
		LeaveCriticalSection(&csPrint);




		EnterCriticalSection(&csPrint);//�����㵣
		while(1)
		{
			int i = 90;//��ʼ����С�������ж��Ƿ���ȡ��ȫ���߶���
			try 
			{
				inputParam curInput;
				curInput.curpage =1;
				curInput.record = RECORD_NUM;
				curInput.customid = "0";
				i = pDlg->svrIO.getNewBulkGoodsInf(contentDataLD, curInput);
				while (1)
				{
					if (i==0)//���ݽ�����ȫ
					{
						if(showtype == NewBulkGood)
						::SendMessage(pDlg->GetSafeHwnd(),WM_SENDFRESH,0,0);
						break;
					}
					if (i == -1)//�������
					{
						//���µ�½
						string result = pDlg->svrIO.usrLogin(user.loginName, user.passWord);
						if (result != "TRUE") {//��½���ɹ�������½
							if (pDlg->m_break)//�ر�ʱ������ѭ��
							{
								break;
							}

						} else {//��½�ɹ�������ѭ��
							break;
						}
					}
					Sleep(100);
				}
				break;
			}
			catch (...)
			{
			}
		}
		LeaveCriticalSection(&csPrint);
		EnterCriticalSection(&csPrint);//���³�Դ
		while(1)
		{

			int i = 90;//��ʼ����С�������ж��Ƿ���ȡ��ȫ���߶���
			try 
			{
				inputParam curInput;
				curInput.curpage =1;
				curInput.record = RECORD_NUM;
				curInput.customid = "0";
				i = pDlg->svrIO.getNewCarsInf(contentDataCY, curInput);
				while (1)
				{
					if (i==0)//���ݽ�����ȫ
					{
						if(showtype == NewCar)
						::SendMessage(pDlg->GetSafeHwnd(),WM_SENDFRESH,0,0);
						break;
					}
					if (i == -1)//�������
					{
						//���µ�½
						string result = pDlg->svrIO.usrLogin(user.loginName, user.passWord);
						if (result != "TRUE") {//��½���ɹ�������½
							if (pDlg->m_break)//�ر�ʱ������ѭ��
							{
								break;
							}

						} else {//��½�ɹ�������ѭ��
							break;
						}
					}
					Sleep(100);
				}
				break;
			}
			catch (...)
			{
			}
		}
		LeaveCriticalSection(&csPrint);

		EnterCriticalSection(&csPrint);//�ҵĻ�Դ
		while(1)
		{

			int i = 90;//��ʼ����С�������ж��Ƿ���ȡ��ȫ���߶���
			try 
			{
				i = pDlg->svrIO.getMyGoodsInf(contentDataMYHY, curInput);
				while (1)
				{
					if (i==0)//���ݽ�����ȫ
					{
						if(showtype == MyGood)
						::SendMessage(pDlg->GetSafeHwnd(),WM_SENDFRESH,0,0);
						break;
					}
					if (i == -1)//�������
					{
						//���µ�½
						string result = pDlg->svrIO.usrLogin(user.loginName, user.passWord);
						if (result != "TRUE") {//��½���ɹ�������½
							if (pDlg->m_break)//�ر�ʱ������ѭ��
							{
								break;
							}

						} else {//��½�ɹ�������ѭ��
							break;
						}
					}
					Sleep(100);
				}
				break;
			}
			catch (...)
			{
			}
		}
		LeaveCriticalSection(&csPrint);
		EnterCriticalSection(&csPrint);//�ҵ��㵣
		while(1)
		{
			int i = 90;//��ʼ����С�������ж��Ƿ���ȡ��ȫ���߶���
			try 
			{
				i = pDlg->svrIO.getMyBulkGoodsInf(contentDataMYLD, curInput);
				while (1)
				{
					if (i==0)//���ݽ�����ȫ
					{
						//������Ϣ֪ͨ����ˢ��
						if(showtype == MyBulkGood)
						::SendMessage(pDlg->GetSafeHwnd(),WM_SENDFRESH,0,0);
						break;
					}
					if (i == -1)//�������
					{
						//���µ�½
						string result = pDlg->svrIO.usrLogin(user.loginName, user.passWord);
						if (result != "TRUE") {//��½���ɹ�������½
							if (pDlg->m_break)//�ر�ʱ������ѭ��
							{
								break;
							}

						} else {//��½�ɹ�������ѭ��
							break;
						}
					}
					Sleep(100);//��ʱ100����
				}
				break;
			}
			catch (...)
			{
			}
		}
		LeaveCriticalSection(&csPrint);
		EnterCriticalSection(&csPrint);//�ҵĳ�Դ
		while(1)
		{
			int i = 90;//��ʼ����С�������ж��Ƿ���ȡ��ȫ���߶���
			try 
			{
				i = pDlg->svrIO.getMyCarsInf(contentDataMYCY, curInput);
				while (1)
				{
					if (i==0)//���ݽ�����ȫ
					{
						if(showtype == MyCar)
						::SendMessage(pDlg->GetSafeHwnd(),WM_SENDFRESH,0,0);
						break;
					}
					if (i == -1)//�������
					{
						//���µ�½
						string result = pDlg->svrIO.usrLogin(user.loginName, user.passWord);
						if (result != "TRUE") {//��½���ɹ�������½
							if (pDlg->m_break)//�ر�ʱ������ѭ��
							{
								break;
							}

						} else {//��½�ɹ�������ѭ��
							break;
						}
					}
					Sleep(100);
				}
				break;
			}
			catch (...)
			{
			}
		}
		LeaveCriticalSection(&csPrint);
		EnterCriticalSection(&csPrint);//����ר��
		while(1)
		{
			int i = 90;//��ʼ����С�������ж��Ƿ���ȡ��ȫ���߶���
			try 
			{
				i = pDlg->svrIO.getAllSpecialLineInf(contentDataALL, curInput);
				while (1)
				{
					if (i==0)//���ݽ�����ȫ
					{
						if(showtype == NewSpecial)
						::SendMessage(pDlg->GetSafeHwnd(),WM_SENDFRESH,0,0);
						break;
					}
					if (i == -1)//�������
					{
						//���µ�½
						string result = pDlg->svrIO.usrLogin(user.loginName, user.passWord);
						if (result != "TRUE") {//��½���ɹ�������½
							if (pDlg->m_break)//�ر�ʱ������ѭ��
							{
								break;
							}

						} else {//��½�ɹ�������ѭ��
							break;
						}
					}
					Sleep(100);
				}
				break;
			}
			catch (...)
			{
			}
		}
		LeaveCriticalSection(&csPrint);
		EnterCriticalSection(&csPrint);//�ҵ�ר��
		while(1)
		{
			int i = 90;//��ʼ����С�������ж��Ƿ���ȡ��ȫ���߶���
			try 
			{
				i = pDlg->svrIO.getMySpecialLineInf(contentDataMY, curInput);
				while (1)
				{
					if (i==0)//���ݽ�����ȫ
					{
						if(showtype == MySpecial)
						::SendMessage(pDlg->GetSafeHwnd(),WM_SENDFRESH,0,0);
						break;
					}
					if (i == -1)//�������
					{
						//���µ�½
						string result = pDlg->svrIO.usrLogin(user.loginName, user.passWord);
						if (result != "TRUE") {//��½���ɹ�������½
							if (pDlg->m_break)//�ر�ʱ������ѭ��
							{
								break;
							}

						} else {//��½�ɹ�������ѭ��
							break;
						}
					}
					Sleep(100);
				}
				break;
			}
			catch (...)
			{
			}
		}
		LeaveCriticalSection(&csPrint);
		EnterCriticalSection(&csPrint);//�ղ�ר��
		while(1)
		{
			int i = 90;//��ʼ����С�������ж��Ƿ���ȡ��ȫ���߶���
			try 
			{
				i = pDlg->svrIO.getFavoriteSpecialLineInf(contentDataSAVE, curInput);
				while (1)
				{
					if (i==0)//���ݽ�����ȫ
					{
						if(showtype == MyFavoritesSpecial)
						::SendMessage(pDlg->GetSafeHwnd(),WM_SENDFRESH,0,0);
						break;
					}
					if (i == -1)//�������
					{
						//���µ�½
						string result = pDlg->svrIO.usrLogin(user.loginName, user.passWord);
						if (result != "TRUE") {//��½���ɹ�������½
							if (pDlg->m_break)//�ر�ʱ������ѭ��
							{
								break;
							}

						} else {//��½�ɹ�������ѭ��
							break;
						}
					}
					Sleep(100);
				}
				break;
			}
			catch (...)
			{
			}
		}
		LeaveCriticalSection(&csPrint);

		//AfxMessageBox(str);
	}
	CoUninitialize();
	return 0;
}
//��ʱˢ�� ��������� ����
DWORD CWLRClientDlg::ProcTimer(LPVOID lpVoid)
{
	CoInitialize(NULL);
	CWLRClientDlg *pDlg=(CWLRClientDlg*)lpVoid;
	//DWORD dwWait;
	/*while((dwWait=::WaitForSingleObject(pDlg->hEvent,6000))!=WAIT_OBJECT_0)
	{
		EnterCriticalSection(&csPrint);
		try 
		{
			//retValue = pDlg->svrIO.getAgentScrollAd();//���������
		}
		catch (...)
		{
		}
		LeaveCriticalSection(&csPrint);
		
	}*/
	CoUninitialize();
 	return 0;
}
//��ʱˢ�� �������� ����
DWORD CWLRClientDlg::ProcCY(LPVOID lpVoid)
{
	CoInitialize(NULL);
	CWLRClientDlg *pDlg=(CWLRClientDlg*)lpVoid;
	//DWORD dwWait;
	/*while((dwWait=::WaitForSingleObject(pDlg->hEvent,60000))!=WAIT_OBJECT_0)
	{
		EnterCriticalSection(&csPrint);
		try 
		{
			result1 = pDlg->svrIO.getSystemScrollAd();//��������
			result2 = pDlg->svrIO.getAgentPopAd();
			if ("TRUE" == result1 || "TRUE" == result2)
				::SendMessage(pDlg->GetSafeHwnd(),WM_TCGG,0,0);//֪ͨ��Ϣ���������溯��
		}
		catch (...)
		{
		}
		LeaveCriticalSection(&csPrint);
	}*/
	CoUninitialize();
	return 0;
}
//����վ
void CWLRClientDlg::OnBnClickedBtnServer()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//MessageBox("����վ���ڳｨ�У������ڴ���","560");
	CDlgService dlg;
	dlg.svrIO = &svrIOService;
	dlg.DoModal();
}
//560��
void CWLRClientDlg::OnBnClickedBtnWlr()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//string url = "http://www.wibang.com";
	//string url = "http://192.168.10.212";
	string str = WEB_SERVICE_ADDRESS + "/fmp/user.login.action?user.name=" + svrIO.userInf.loginName
	+ "&user.pwd=" + svrIO.userInf.passWord; 

//string str ="http://218.108.51.235:8888/UserLogin.aspx";
	HWND pwnd = ::FindWindow(NULL,"560��վ");
	if (pwnd)
	{
		::ShowWindow(pwnd, SW_SHOWNORMAL); //������ʾ�ҵ��������еĳ���
		::SetForegroundWindow(pwnd);       //�������еĳ�������Ϊ��ǰ����
	} 
	else
	{
		CWebHTTP * dlg = new CWebHTTP;
		dlg->url = str;
		dlg->Create(IDD_DLGWEB,GetDesktopWindow());
		dlg->SetWindowText("560��վ");
		int nFullWidth=GetSystemMetrics(SM_CXSCREEN);     
		int nFullHeight=GetSystemMetrics(SM_CYSCREEN);
		dlg->ShowWindow(TRUE);
		dlg->SetWindowPos(NULL,0,0,nFullWidth,nFullHeight-29,SWP_SHOWWINDOW);
	}
}

//�û�����
void CWLRClientDlg::OnBnClickedCenter()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	string str = WEB_SERVICE_ADDRESS + "/fmp/user.login.action?user.name=" + svrIO.userInf.loginName
		+ "&user.pwd=" + svrIO.userInf.passWord; 
	//string str = "www.baidu.com";
	HWND pwnd = ::FindWindow(NULL,"560�û�����");
	if (pwnd)
	{
		::ShowWindow(pwnd, SW_SHOWNORMAL); //������ʾ�ҵ��������еĳ���
		::SetForegroundWindow(pwnd);       //�������еĳ�������Ϊ��ǰ����
	} 
	else
	{
		CUserCenter * dlg = new CUserCenter;
		dlg->url = str;
		dlg->Create(IDD_USERCENTER,GetDesktopWindow());
		dlg->SetWindowText("560�û�����");
		int nFullWidth=GetSystemMetrics(SM_CXSCREEN);     
		int nFullHeight=GetSystemMetrics(SM_CYSCREEN);
		dlg->ShowWindow(TRUE);
		dlg->SetWindowPos(NULL,0,0,nFullWidth,nFullHeight-29,SWP_SHOWWINDOW);
	}
}

//
//������Ϣˢ��
LONG CWLRClientDlg::OnFresh(WPARAM w, LPARAM l)
{
	try
	{
		refreshShow();
	}
	catch (...)
	{

	}
	return 0;
}
//��������
LONG CWLRClientDlg::OnTCGG(WPARAM w, LPARAM l)
{
	try
	{
		SetTimer(CHECK_NOTICE_TIMER_ID, 10000, NULL);
		//checkNotice();
	}
	catch (...)
	{

	}
	return 0;
}

//��ʼ������ɫ
void CWLRClientDlg::SetInitColor(ServerIO &svrIO)
{
	svrIO.myColor.sysBKClr = myConfig.colorSetting.sysBKClr;
	svrIO.myColor.gridClr  = myConfig.colorSetting.gridClr;
	svrIO.myColor.oddRowBKClr  = myConfig.colorSetting.oddRowBKClr;
	svrIO.myColor.oddRowFgClr  = myConfig.colorSetting.oddRowFgClr;
	svrIO.myColor.evenRowBKClr = myConfig.colorSetting.evenRowBKClr;
	svrIO.myColor.evenRowFgClr = myConfig.colorSetting.evenRowFgClr;

	svrIO.oddFont.lfFaceName = myConfig.oddFont.lfFaceName;
	svrIO.oddFont.lfWeight = myConfig.oddFont.lfWeight; 
	svrIO.oddFont.lfWidth = myConfig.oddFont.lfWidth; 
	svrIO.oddFont.lfHeight = myConfig.oddFont.lfHeight;  
	svrIO.oddFont.lfEscapement = myConfig.oddFont.lfEscapement; 
	svrIO.oddFont.lfUnderline = myConfig.oddFont.lfUnderline; 
	svrIO.oddFont.lfItalic = myConfig.oddFont.lfItalic; 
	svrIO.oddFont.lfStrikeOut = myConfig.oddFont.lfStrikeOut; 
	svrIO.oddFont.lfCharSet = myConfig.oddFont.lfCharSet;

	svrIO.evenFont.lfFaceName = myConfig.evenFont.lfFaceName;
	svrIO.evenFont.lfWeight = myConfig.evenFont.lfWeight; 
	svrIO.evenFont.lfWidth = myConfig.evenFont.lfWidth; 
	svrIO.evenFont.lfHeight = myConfig.evenFont.lfHeight;  
	svrIO.evenFont.lfEscapement = myConfig.evenFont.lfEscapement; 
	svrIO.evenFont.lfUnderline = myConfig.evenFont.lfUnderline; 
	svrIO.evenFont.lfItalic = myConfig.evenFont.lfItalic; 
	svrIO.evenFont.lfStrikeOut = myConfig.evenFont.lfStrikeOut; 
	svrIO.evenFont.lfCharSet = myConfig.evenFont.lfCharSet;
}
void CWLRClientDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//OnOK();
	AfxMessageBox("OK");
}

void CWLRClientDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//OnCancel();
}

//������Դ
void CWLRClientDlg::OnBnClickedBtnReleasegoods()
{
	CPublishWayOneDlg dlg;
	dlg.DoModal();
	// TODO: Add your control notification handler code here
	if ( is_funcs_enabled ) 
		pubGoodsInf();
	else
		AfxMessageBox("ֻ�����շѺ������û����ܹ�������Դ");
}

//������Դ
void CWLRClientDlg::OnBnClickedBtnReleasetruckinfo()
{
	// TODO: Add your control notification handler code here
	// TODO: Add your control notification handler code here
	if ( is_funcs_enabled ) 
		pubCarsInf();
	else
		AfxMessageBox("ֻ�����շѺ������û����ܹ�������Դ");
}

void CWLRClientDlg::OnBnClickedBtnReleasespecialline()
{
	// TODO: Add your control notification handler code here
	if ( is_funcs_enabled ) 
		pubSpecialLineInf();
	else
		AfxMessageBox("ֻ�����շѺ������û����ܹ�����ר��");
}


//����ҳ
void CWLRClientDlg::OpenWebPage(string & url,string &title)
{	
	TCHAR * wndTitle = (TCHAR*)title.c_str();

	HWND pwnd = ::FindWindow(NULL,wndTitle);
	if (pwnd)
	{
		::ShowWindow(pwnd, SW_SHOWNORMAL); //������ʾ�ҵ��������еĳ���
		::SetForegroundWindow(pwnd);       //�������еĳ�������Ϊ��ǰ����
	} 
	else
	{
		CWebHTTP * dlg = new CWebHTTP;
		dlg->url = url;
		dlg->Create(IDD_DLGWEB,GetDesktopWindow());
		dlg->SetWindowText(wndTitle);
		int nFullWidth=GetSystemMetrics(SM_CXSCREEN);     
		int nFullHeight=GetSystemMetrics(SM_CYSCREEN);
		dlg->ShowWindow(TRUE);
		dlg->SetWindowPos(NULL,0,0,nFullWidth,nFullHeight-29,SWP_SHOWWINDOW);
	}
}

//�ҵ��˻�
void CWLRClientDlg::OnBnClickedBtnMyaccountant()
{
	// TODO: Add your control notification handler code here
	string url = WEB_SERVICE_ADDRESS+"/fmp/user.login.action?username=" + svrIO.userInf.loginName
		+ "&password=" + svrIO.userInf.passWord+"&target=accountant";
	string title = "�ҵ��˻�";
	OpenWebPage(url,title);
}

//�����̳�
void CWLRClientDlg::OnBnClickedBtnShoppingMall()
{
	// TODO: Add your control notification handler code here
	string url = WEB_SERVICE_ADDRESS+"/fmp/user.login.action?username=" + svrIO.userInf.loginName
		+ "&password=" + svrIO.userInf.passWord+"&target=mall";
	string title = "�����̳�";
	OpenWebPage(url,title);
}


//GPS��λ
void CWLRClientDlg::OnBnClickedBtnGpsLocating()
{
	// TODO: Add your control notification handler code here
	string url = WEB_SERVICE_ADDRESS+"/fmp/user.login.action?username=" + svrIO.userInf.loginName
		+ "&password=" + svrIO.userInf.passWord+"&target=gps";
	string title = "GPS��λ";
	OpenWebPage(url,title);
}

//����Ӧ��
void CWLRClientDlg::OnBnClickedBtnMyApp()
{
	// TODO: Add your control notification handler code here
	string url = WEB_SERVICE_ADDRESS+"/fmp/user.login.action?username=" + svrIO.userInf.loginName
		+ "&password=" + svrIO.userInf.passWord+"&target=app";
	string title = "����Ӧ��";
	OpenWebPage(url,title);
}

//���ҵ����״̬
bool CWLRClientDlg::get_funcs_status( string user_name )
{
		//��ȡ�û��շ�״̬
		string ret = svrIO.check_charge_user( user_name );
		//ҵ����״̬
		bool is_enabled = false;
		
		if ( "����" == ret )		{
			is_enabled = true;
		}else if ( "�շ�" == ret ) {
			is_enabled = true;
		}else if ( "����" == ret ) {
			is_enabled = false;
		}else if ( "���" == ret ) {
			is_enabled = false;
		}else {
			is_enabled = false;
		}

		return is_enabled;	
}



LRESULT CWLRClientDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
	case WM_TNI_START_SEARCH:
		search(wParam, lParam);
		break;
	case WM_TNI_CANCEL_SEARCH:
		search(wParam, lParam);
		break;
	case WM_TNI_STOP_REFRESH:
		stopTimer();
		break;
	case WM_TNI_SECRECY:
		OnBnClickedBtnHidetel();
		break;
	default:
		break;
	}
	return CDialog::WindowProc(message, wParam, lParam);
}

void CWLRClientDlg::OnBnClickedButtonPubWayOne()
{
	curTabIndex = 0;
	CPublishWayOneDlg dlg;
	dlg.myCR = &myCR;
	dlg.userInfo = svrIOPub.userInf;
	if( dlg.DoModal() == IDOK )
	{
		string result;
		try                                                   
		{
			if ( dlg.publishKind == 0 )
			{
				curTabType = GOODS;
				result = svrIOPub.setPubGoodsInf(dlg.pubInf);
			}
			else
			{
				curTabType = CARS;
				result = svrIOPub.setPubCarsInf(dlg.pubInf);        
			}
		}
		catch(...)                                            
		{                                                     
			//goto HH;                                          
		}
		if ("TRUE" !=  result) {                          
			MessageBox(result.c_str());                   
		} else {
			if ( dlg.publishKind == 0 )
			{
				MessageBox("��Դ�����ɹ���");
				try
				{
					setGoodsInf();
				}
				catch (...)
				{

				}
			}
			else
			{
				MessageBox("��Դ�����ɹ���");                               
				try                                                               
				{                                                                 
					setCarsInf();                                                  
				}                                                                 
				catch (...)                                                       
				{                                                                 

				}                                                                 
			}
		}
	}
}

void CWLRClientDlg::OnBnClickedButtonPubWayTwo()
{
	curTabIndex = 0;
	CPublishWayTwoDlg dlg;
	dlg.myCR = &myCR;
	dlg.userInfo = svrIOPub.userInf;
	if( dlg.DoModal() == IDOK )
	{
		string result;
		try                                                   
		{
			if ( dlg.publishKind == 0 )
			{
				curTabType = GOODS;
				result = svrIOPub.setPubGoodsInf(dlg.pubInf);
			}
			else
			{
				curTabType = CARS;
				result = svrIOPub.setPubCarsInf(dlg.pubInf);        
			}
		}
		catch(...)                                            
		{                                                     
			//goto HH;                                          
		}
		if ("TRUE" !=  result) {                          
			MessageBox(result.c_str());                   
		} else {
			if ( dlg.publishKind == 0 )
			{
				MessageBox("��Դ�����ɹ���");
				try
				{
					setGoodsInf();
				}
				catch (...)
				{

				}
			}
			else
			{
				MessageBox("��Դ�����ɹ���");                               
				try                                                               
				{                                                                 
					setCarsInf();                                                  
				}                                                                 
				catch (...)                                                       
				{                                                                 

				}                                                                 
			}
		}
	}
}

void CWLRClientDlg::FillGoodsSearchCriteria(const CSearchCriteria* pSearchCriteria, InSearchGoods& goodsSearch)
{
	goodsSearch.lstStartAddr = pSearchCriteria->GetStartAddrList();
	goodsSearch.lstEndAddr = pSearchCriteria->GetEndAddrList();
	goodsSearch.lstCarLength = pSearchCriteria->GetCarLengthList();
	goodsSearch.lstCarType = pSearchCriteria->GetCarTypeList();
	goodsSearch.lstGoods = pSearchCriteria->GetGoodsList();
	goodsSearch.lstGoodsType = pSearchCriteria->GetGoodsTypeList();
	goodsSearch.lstPublisher = pSearchCriteria->GetPublisherList();
	goodsSearch.lstPhoneNum = pSearchCriteria->GetPhoneNumList();
	goodsSearch.sKeyword = pSearchCriteria->GetKeyword();
	goodsSearch.bMatchAll = pSearchCriteria->IsMatchAll();

}

void CWLRClientDlg::FillCarSearchCriteria(const CSearchCriteria* pSearchCriteria, InSearchCars& carsSearch)
{
	carsSearch.lstStartAddr = pSearchCriteria->GetStartAddrList();
	carsSearch.lstEndAddr = pSearchCriteria->GetEndAddrList();
	carsSearch.lstCarLength = pSearchCriteria->GetCarLengthList();
	carsSearch.lstCarType = pSearchCriteria->GetCarTypeList();
	carsSearch.lstGoods = pSearchCriteria->GetGoodsList();
	carsSearch.lstGoodsType = pSearchCriteria->GetGoodsTypeList();
	carsSearch.lstPublisher = pSearchCriteria->GetPublisherList();
	carsSearch.lstPhoneNum = pSearchCriteria->GetPhoneNumList();
	carsSearch.sKeyword = pSearchCriteria->GetKeyword();
	carsSearch.bMatchAll = pSearchCriteria->IsMatchAll();
}