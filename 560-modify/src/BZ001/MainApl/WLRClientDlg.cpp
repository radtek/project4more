// WLRClientDlg.cpp : 实现文件
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
// 美化外观插件
//#include "SkinFeature.h"
//#pragma comment(lib,"SkinFeature.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define WM_SENDFRESH WM_USER+100//刷新页面
#define WM_TCGG WM_USER+101//弹出公告
//最新信息（货源、零担、车源）
vector<TabNewInfRecord> contentDataHY;
vector<TabNewInfRecord> contentDataLD;
vector<TabNewInfRecord> contentDataCY;
//我的信息（货源、零担、车源）
vector<TabMyInfRecord> contentDataMYHY;
vector<TabMyInfRecord> contentDataMYLD;
vector<TabMyInfRecord> contentDataMYCY;
//专线
vector<TabSpecialLineRecord> contentDataALL;//所有专线
vector<TabSpecialLineRecord> contentDataMY;//我的专线
vector<TabSpecialLineRecord> contentDataSAVE;//收藏专线

vector<CustomZoneInf> zoneInfHY;//定制
vector<CustomZoneInf> zoneInfCY;

vector<TabCustomInfRecord> contentDataDZHY[5];
vector<TabCustomInfRecord> contentDataDZCY[5];

UserInfo user; // 用户信息
HANDLE hThread;
HANDLE hThreadTimer;
HANDLE hThreadCY;
HANDLE hThreadLD;


CRITICAL_SECTION csPrint; //临界区
CRITICAL_SECTION csPrintMore; //临界区
CRITICAL_SECTION csPrintOther;
CRITICAL_SECTION csPrintSpecial;
CRITICAL_SECTION csPrintMy;
CRITICAL_SECTION csPrintCustom;

CRITICAL_SECTION csClick;//防止点击过快导致vector崩溃

CRITICAL_SECTION csPrintFresh;

CRITICAL_SECTION csService;

string result1;
string result2;

unsigned int nHysize =1;//判断定制货源选项卡
unsigned int nCysize =1;//判断定制车源选项卡

BOOL m_bClose = FALSE;//程序关闭

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
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框


class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CWLRClientDlg 对话框




CWLRClientDlg::CWLRClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWLRClientDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

    // 初始化变量
    //curTabType = GOODS;
	
    ifInit = false;
    ifShowPhone = true;
    ifAutoRefresh = false;
	
	m_dock = FALSE;
	m_break = FALSE;

	m_bgColor = RGB(229,243,254);
	m_textColor = RGB(64, 74, 83); // 文字色

	// 调用皮肤
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
	//xqh:删除快速发布功能
	//DDX_Control(pDX, IDC_BTN_Pub, btnQuickPub);
	DDX_Control(pDX, IDC_BTN_NOTICE, btnNotice);
	//	DDX_Control(pDX, IDC_BTN_CHAT, btnChat);
	DDX_Control(pDX, IDC_BTN_SERVER, m_btnserver);
	DDX_Control(pDX, IDC_BTN_WLR, m_btnwlr);
	//DDX_Control(pDX, IDC_CEMTER, m_btnuser);

	//发布货源
	DDX_Control(pDX, IDC_BTN_ReleaseGoods, m_btnReleaseGoods);
	//发布车源
	DDX_Control(pDX, IDC_BTN_ReleaseTruckInfo, m_btnReleaseTruckInfo);
	//发布专线
	DDX_Control(pDX, IDC_BTN_ReleaseSpecialLine, m_btnReleaseSpecialLine);

	//我的账户
	DDX_Control(pDX, IDC_BTN_MyAccountant, m_btnMyAccountant);
	//功能应用
	DDX_Control(pDX, IDC_BTN_MY_APP, m_btnMyApp);
	//GPS 定位
	DDX_Control(pDX, IDC_BTN_GPS_LOCATING, m_btnGPSLocating);
	//积分商城
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

	//xqh:删除快速发布功能
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
	//我的账户
	EASYSIZE(IDC_BTN_MyAccountant, ES_KEEPSIZE, ES_BORDER, ES_BORDER, ES_BORDER, 0)
	//首页
	EASYSIZE(IDC_BTN_WLR, ES_KEEPSIZE, ES_BORDER, ES_BORDER, ES_BORDER, 0)
	//GPS定位
	EASYSIZE(IDC_BTN_GPS_LOCATING, ES_KEEPSIZE, ES_BORDER, ES_BORDER, ES_BORDER, 0)
	//功能应用
	EASYSIZE(IDC_BTN_MY_APP, ES_KEEPSIZE, ES_BORDER, ES_BORDER, ES_BORDER, 0)
	//积分商城
	EASYSIZE(IDC_BTN_SHOPPING_MALL, ES_KEEPSIZE, ES_BORDER, ES_BORDER, ES_BORDER, 0)
	//服务站
	EASYSIZE(IDC_BTN_SERVER, ES_KEEPSIZE, ES_BORDER, ES_BORDER, ES_BORDER, 0)
	//用户中心
	EASYSIZE(IDC_CEMTER, ES_KEEPSIZE, ES_BORDER, ES_BORDER, ES_BORDER, 0)
	//自动刷新 IDC_BTN_AutoUpdate
	EASYSIZE(IDC_BTN_AutoUpdate, ES_KEEPSIZE, ES_BORDER, ES_BORDER, ES_BORDER, 0)
	//增值服务 IDC_BTN_PayService
	EASYSIZE(IDC_BTN_PayService, ES_KEEPSIZE, ES_BORDER, ES_BORDER, ES_BORDER, 0)
	//隐藏电话 IDC_BTN_HideTel
	EASYSIZE(IDC_BTN_HideTel, ES_KEEPSIZE, ES_BORDER, ES_BORDER, ES_BORDER, 0)*/
	

END_EASYSIZE_MAP
// CWLRClientDlg 消息处理程序

BOOL CWLRClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	//SetIcon(m_hIcon, TRUE);			// 设置大图标
	//SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

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


    // 检查更新-----徐清华取消检查更新
    //checkUpate();
	

    // 加载设置
    loadConfig();

    // 初始化设置
    initConfig();

    // 加载地区信息
	if ( -1 == CountryRegion::loadData(myCR, "RegionInfo.bin") ) {
		AfxMessageBox("加载程序配置文件失败，请重新安装应用程序！");
		exit(0);
	}

	g_pCountryRegion = &myCR;
    // 区域信息指针赋值
    svrIO.myCR = &myCR;
	svrIONew.myCR = &myCR;
	svrIOMore.myCR = &myCR;
	svrIOMy.myCR = &myCR;
	svrIOCustom.myCR = &myCR;
	svrIOSpecial.myCR = &myCR;
	svrIOService.myCR = &myCR;
	svrIOPub.myCR = &myCR;

    // 用户登录
    userLogin();
   
	
	//xqh:客户端的标题设置
	string welcome(",欢迎使用560配货软件");
	if ( "男" == svrIO.userInf.sex )
		welcome=svrIO.userInf.realName+"先生您好" + welcome;
	else if ( "女" == svrIO.userInf.sex ) 
		welcome=svrIO.userInf.realName+"女士您好" + welcome;
	else
		welcome=svrIO.userInf.realName+"您好" + welcome;
    
	this->SetWindowText(welcome.c_str());
    
	//取得用户类型
	this->is_funcs_enabled = this->get_funcs_status(svrIO.userInf.loginName);

	//
	InitCommData();

                                         
    // 初始化按钮
    initButton();

    // 初始化TAB控件
    initTabCtrl();
    
    // 初始化Tree控件
    initTreeCtrl();

    // 开启广告滚动条
    startShowAD();   

    // 开启自动刷新
    startTimer();

    // 开启检查公告定时器
    //SetTimer(CHECK_NOTICE_TIMER_ID, checkNoticeGap, NULL);

	// 开启聊天客户端定时器
    SetTimer(START_CHAT_CLIENT, 1000, NULL);
    
    //bgBrush.CreateSolidBrush(svrIO.myColor.sysBKClr); 

    // 初始化自动调整控件位置
    INIT_EASYSIZE;

	// 设置窗口位置
	//int cxScreen = ::GetSystemMetrics(SM_CXSCREEN);//获得屏幕宽 
 //   int cyScreen = ::GetSystemMetrics(SM_CYSCREEN); //获得屏幕高
	//int xPos = ((cxScreen-1024)/2) > 0 ? ((cxScreen-1024)/2) : 0 ;
	//::MoveWindow(m_hWnd, xPos, (cyScreen-600)/2, 800, 600, TRUE);

	//定时采集
	DWORD PID;
	hEvent=CreateEvent(NULL,TRUE,FALSE,NULL);
	hThread=CreateThread(NULL,0,Proc,this,0,&PID);//定时刷新的数据采集

	/*DWORD PIDTIMER;//定时刷新 滚动条广告
	hThreadTimer=CreateThread(NULL,0,ProcTimer,this,0,&PIDTIMER);

	DWORD PIDTIMER1;//定时刷新 弹出公告
	hThreadCY=CreateThread(NULL,0,ProcCY,this,0,&PIDTIMER1);*/
		
	//SetTimer(1,50,NULL);
	//svrIONew = svrIO;
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CWLRClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR CWLRClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
    
// 检查更新
bool CWLRClientDlg::checkUpate()
{
	CString updateURL = WEB_SERVICE_ADDRESS.c_str();
    updateURL = updateURL + "/fmp/pc_client/update/";
    CAutoUpdater updater;

	// 检查update文件是否需要更新，如果需要更新，则更新 update 文件
	if (CAutoUpdater::UpdateRequired == updater.CheckUpdate(updateURL, "update_file.txt")) {
		updater.RunUpdate(updateURL, "update_file.txt");
	} 

	// 检查程序主文件是否需要更新，如果需要更新，则启动 update 文件
	if (CAutoUpdater::UpdateRequired == updater.CheckUpdate(updateURL, "updates.txt")) {
		MessageBox("程序有新版本发布，点击确定，开始更新。", "自动更新", MB_ICONINFORMATION|MB_OK);
        // 运行更新程序
        WinExec("update.exe", SW_SHOW);
        exit(0);
	} 

    return true;
}
        
// 保存设置
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
    
// 加载设置
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
    
// 初始化设置
int CWLRClientDlg::initConfig()
{
    // 主对话框背景色
    GLB::mainDlgBgColor = /*RGB(238, 238, 238);*/RGB(238, 238, 238);//RGB(199, 230, 196);

    // TAB控件背景色
    GLB::tabCtrlBgColor = RGB(238, 238, 238);

    // 滚动条文字色
    GLB::scrollBarFgColor = m_textColor;//RGB(0, 0, 0);
    // 滚动条背景色
    GLB::scrollBarBgColor = m_bgColor;

    // 自动刷新时间间隔
    autoRefreshGap = 1000;  // 10秒
    // 检查公告间隔时间
    checkNoticeGap = 30000;  // 30秒

	return 0;
}
    
//  用户登录
int CWLRClientDlg::userLogin()
{
#ifdef _AUTO_LOGIN_
    string username("dot");
    string password("123456");    
    string result = svrIO.usrLogin(username, password);
    svrIO.userInf.loginName = username;
    svrIO.userInf.passWord = password;
    if (result != "TRUE") {
        MessageBox(result.c_str(), "用户登录");
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
		//徐清华调试改写
		//------------------------
		
        if (result != "TRUE") {
            MessageBox(result.c_str(), "用户登录");
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
    
// 初始化按钮
int CWLRClientDlg::initButton()
{
    // 货源按钮
    btnGoods.LoadBitmap(IDB_GOODS);

    // 车源按钮
    btnCars.LoadBitmap(IDB_CARS);

    // 专线按钮
    btnSpecial.LoadBitmap(IDB_SPECIAL);

	//发布货源
	this->m_btnReleaseGoods.LoadBitmap(IDB_RELEASE_GOODS);

	//发布车源
	this->m_btnReleaseTruckInfo.LoadBitmap(IDB_RELEASE_TRUCK_INFO);

	//发布专线
	this->m_btnReleaseSpecialLine.LoadBitmap(IDB_RELEASE_SPECIAL_LINE);

	// 拍照按钮
	btnTakePhoto.LoadBitmap(IDB_TAKE_PHOTO);

	//我的账户
	this->m_btnMyAccountant.LoadBitmap(IDB_MY_ACCOUNTANT);


	//积分商城
	this->m_btnShoppingMall.LoadBitmap(IDB_SHOPPING_MALL);

	//功能应用
	this->m_btnMyApp.LoadBitmap(IDB_MY_APP);

    // 系统设置按钮
    btnSysSetting.LoadBitmap(IDB_SYSSETTING);

	// 服务站
	m_btnserver.LoadBitmap(IDB_SERVER);

	// 登录网站
	m_btnwlr.LoadBitmap(IDB_WLR);

	//GPS定位
	this->m_btnGPSLocating.LoadBitmap(IDB_GPS_LOCATING);

	// 公告按钮    
	btnNotice.LoadBitmap(IDB_NOTICE);

	m_btnPubWayOne.LoadBitmap(IDB_PUBLISH_ONE);
	m_btnPubWayTwo.LoadBitmap(IDB_PUBLISH_TWO);
	m_btnPubWayOne.ShowWindow(SW_HIDE);
	m_btnPubWayTwo.ShowWindow(SW_HIDE);

    // 增值服务
    //btnAddValued.LoadBitmap(IDB_ADDVALUED);
    // 自动刷新按钮
    //autoRefresh.LoadBitmap(IDB_NOREFRESH);
    // 显示电话
    //showPhone.LoadBitmap(IDB_SHOWPHONE);
	// 搜索按钮
	//btnSearch.LoadBitmap(IDB_SEARCH);
	//用户中心
	//m_btnuser.LoadBitmap(IDB_CENTER);
    // 快速发布按钮 xqh:删除快速发布功能
    //btnQuickPub.LoadBitmap(IDB_QUICKPUB);
	// 聊天按钮    
	//btnChat.LoadBitmap(IDB_CHAT);
    return 0;
}
    
// 初始化TAB控件
int CWLRClientDlg::initTabCtrl()
{
    // 初始化TAB控件样式
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
    //关联对话框,并且将IDC_TAB_Main控件设为父窗口：货源
    newGoodsInf.Create(IDD_TAB_NEW_INF, GetDlgItem(IDC_TAB_Main));
    customGoodsInf.Create(IDD_TAB_CUSTOM_INF, GetDlgItem(IDC_TAB_Main));
    myGoodsInf.Create(IDD_TAB_MY_INF, GetDlgItem(IDC_TAB_Main));  

    //关联对话框,并且将IDC_TAB_Main控件设为父窗口：零担
    newBulkGoodsInf.Create(IDD_TAB_NEW_INF, GetDlgItem(IDC_TAB_Main));
    myBulkGoodsInf.Create(IDD_TAB_MY_INF, GetDlgItem(IDC_TAB_Main)); 

    //关联对话框,并且将IDC_TAB_Main控件设为父窗口：车源
    newCarsInf.Create(IDD_TAB_NEW_INF, GetDlgItem(IDC_TAB_Main));
    customCarsInf.Create(IDD_TAB_CUSTOM_INF, GetDlgItem(IDC_TAB_Main));
    myCarsInf.Create(IDD_TAB_MY_INF, GetDlgItem(IDC_TAB_Main));

    //关联对话框,并且将IDC_TAB_Main控件设为父窗口：专线
    allspecialLine.Create(IDD_TAB_SPECIAL_LINE, GetDlgItem(IDC_TAB_Main));
    mySpecialLine.Create(IDD_TAB_SPECIAL_LINE, GetDlgItem(IDC_TAB_Main));
    favoriteSpecialLine.Create(IDD_TAB_SPECIAL_LINE, GetDlgItem(IDC_TAB_Main));

    //关联对话框,并且将IDC_TAB_Main控件设为父窗口：搜索
    searchGoodsInf.Create(IDD_TAB_NEW_INF, GetDlgItem(IDC_TAB_Main));
    searchBulkGoodsInf.Create(IDD_TAB_NEW_INF, GetDlgItem(IDC_TAB_Main));
    searchCarsInf.Create(IDD_TAB_NEW_INF, GetDlgItem(IDC_TAB_Main));
    searchSpecialLine.Create(IDD_TAB_SPECIAL_LINE, GetDlgItem(IDC_TAB_Main)); 

    setGoodsInf();
    ifInit = true;
    curTabIndex = 0;

    return 0;
}
    
// 初始化Tree控件
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
	tvInsert.item.pszText = _T("中国");

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
    // TODO: 在此处添加消息处理程序代码
	UPDATE_EASYSIZE;  // 自动改变控件位置大小

    if (!ifInit) {
        return;
    }

	//if( nType != SIZE_MAXIMIZED )
	//{
	//	// 货源按钮
	//	btnGoods.LoadBitmap(IDB_GOODS_MIN);

	//	// 车源按钮
	//	btnCars.LoadBitmap(IDB_CARS_MIN);

	//	// 专线按钮
	//	btnSpecial.LoadBitmap(IDB_SPECIAL_MIN);

	//	// 搜索按钮
	//	btnSearch.LoadBitmap(IDB_SEARCH_MIN);

	//	//拍照按钮
	//	btnMainPage.LoadBitmap(IDB_MAINPAGE_MIN);

	//	// 零担按钮
	//	//btnBulkGoods.LoadBitmap(IDB_BULKGOODS);

	//	//发布货源
	//	this->m_btnReleaseGoods.LoadBitmap(IDB_RELEASE_GOODS_MIN);
	//	//发布车源
	//	this->m_btnReleaseTruckInfo.LoadBitmap(IDB_RELEASE_TRUCK_INFO_MIN);
	//	//发布专线
	//	this->m_btnReleaseSpecialLine.LoadBitmap(IDB_RELEASE_SPECIAL_LINE_MIN);
	//}
	//else
	//{
	//	// 货源按钮
	//	btnGoods.LoadBitmap(IDB_GOODS);

	//	// 车源按钮
	//	btnCars.LoadBitmap(IDB_CARS);

	//	// 专线按钮
	//	btnSpecial.LoadBitmap(IDB_SPECIAL);

	//	// 搜索按钮
	//	btnSearch.LoadBitmap(IDB_SEARCH);

	//	//拍照按钮
	//	btnMainPage.LoadBitmap(IDB_MAINPAGE);
	//	
	//	// 零担按钮
	//	//btnBulkGoods.LoadBitmap(IDB_BULKGOODS);

	//	//发布货源
	//	this->m_btnReleaseGoods.LoadBitmap(IDB_RELEASE_GOODS);
	//	//发布车源
	//	this->m_btnReleaseTruckInfo.LoadBitmap(IDB_RELEASE_TRUCK_INFO);
	//	//发布专线
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
        //获得IDC_TABTEST客户区大小
    CRect rect;
    mTabMain.GetClientRect(&rect);

    //调整子对话框在父窗口中的位置
    rect.top+=20; 
    rect.left+=1; 
    rect.right-=2;

    //设置子对话框尺寸并移动到指定位置
    // 货源                
    newGoodsInf.MoveWindow(&rect);
    customGoodsInf.MoveWindow(&rect);
    myGoodsInf.MoveWindow(&rect);

    // 零担 
    newBulkGoodsInf.MoveWindow(&rect);
    myBulkGoodsInf.MoveWindow(&rect);
 
    // 车源
    newCarsInf.MoveWindow(&rect);
    customCarsInf.MoveWindow(&rect);
    myCarsInf.MoveWindow(&rect);

    // 专线

    // 搜索
*/

/*
    switch (curTabType) {
    case GOODS:  // 货源                
        setGoodsInf();
        break;
    case BULKGOODS: // 零担 
        setBulkGoodsInf();
        break;
    case CARS:      // 车源
        break;
    case LINES:     // 专线
        break;
    case SEARCH:     // 搜索
        break;
    default:
        ;
    }
    */
//*
    //获得IDC_TABTEST客户区大小
    CRect rect;
    mTabMain.GetClientRect(&rect);
	
	GLB::ifMiniSize = false;
    // 当最小化时
    if(rect.Width() < 1 || rect.Height() < 1) {
		GLB::ifMiniSize = true;
		//SuspendThread(hThread);
		KillTimer(AUTO_REFRESH_TIMER_ID);//停止刷新（主要是定制页时候的刷新）
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
    //调整子对话框在父窗口中的位置
    rect.top+=20; 
    rect.left+=1; 
    rect.right-=2;

    //设置子对话框尺寸并移动到指定位置
	//EnterCriticalSection(&csPrint);
    switch (curTabType) {
    case GOODS:  // 货源                
        newGoodsInf.MoveWindow(&rect);
        customGoodsInf.MoveWindow(&rect);
        myGoodsInf.MoveWindow(&rect);
        setGoodsInf(curTabIndex);
        break;
    case BULKGOODS: // 零担 
        newBulkGoodsInf.MoveWindow(&rect);
        myBulkGoodsInf.MoveWindow(&rect);
        setBulkGoodsInf(curTabIndex);
        break;
    case CARS:      // 车源
        newCarsInf.MoveWindow(&rect);
        customCarsInf.MoveWindow(&rect);
        myCarsInf.MoveWindow(&rect);
        setCarsInf(curTabIndex);
        break;
    case LINES:     // 专线
        allspecialLine.MoveWindow(&rect);
        mySpecialLine.MoveWindow(&rect);
        favoriteSpecialLine.MoveWindow(&rect);
        setSpecialLineInf(curTabIndex);
        break;
    case SEARCH_GOODS:     // 搜索货源
        searchGoodsInf.MoveWindow(&rect);
        searchGoodsInf.ShowWindow(false);
        searchGoodsInf.ShowWindow(true);
        break;
    case SEARCH_BULKGOODS: // 搜索零担
        searchBulkGoodsInf.MoveWindow(&rect);
        searchBulkGoodsInf.ShowWindow(false);
        searchBulkGoodsInf.ShowWindow(true);
        break;
    case SEARCH_CARS:      // 搜索车源
        searchCarsInf.MoveWindow(&rect);
        searchCarsInf.ShowWindow(false);
        searchCarsInf.ShowWindow(true);
        break;
    case SEARCH_SPECIAL:   // 搜索专线
        searchSpecialLine.MoveWindow(&rect);
        searchSpecialLine.ShowWindow(false);
        searchSpecialLine.ShowWindow(true);
        break;
    case CLICK_SEARCH_GOODS:      // 点击搜索货源
        searchGoodsInf.MoveWindow(&rect);
        searchGoodsInf.ShowWindow(false);
        searchGoodsInf.ShowWindow(true);
        break;
    case CLICK_SEARCH_BULKGOODS:  // 点击搜索零担
        searchBulkGoodsInf.MoveWindow(&rect);
        searchBulkGoodsInf.ShowWindow(false);
        searchBulkGoodsInf.ShowWindow(true);
        break;
    case CLICK_SEARCH_CARS:       // 点击搜索车源
        searchCarsInf.MoveWindow(&rect);
        searchCarsInf.ShowWindow(false);
        searchCarsInf.ShowWindow(true);
        break;
    case CLICK_SEARCH_SPECIAL:    // 点击搜索专线
        searchSpecialLine.MoveWindow(&rect);
        searchSpecialLine.ShowWindow(false);
        searchSpecialLine.ShowWindow(true);
        break;
    default:
        ;
    }
    //*/

    // 重置广告滚动条
	//LeaveCriticalSection(&csPrint);
    pubAD.Resize();
}
    
// 点击TAB控件，切换不同的标签
void CWLRClientDlg::OnTcnSelchangeTabMain(NMHDR *pNMHDR, LRESULT *pResult)
{
    // TODO: 在此添加控件通知处理程序代码
	KillTimer(AUTO_REFRESH_TIMER_ID);
    int CurSel = mTabMain.GetCurSel();
    curTabIndex = CurSel;
    if (curTabType == GOODS) { // 货源 
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
    } else if (curTabType == BULKGOODS) { // 零担 
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
    } else if (curTabType == CARS) {      // 车源
        setCarsInf(CurSel);
    } else if (curTabType == LINES) {     // 专线
        setSpecialLineInf(CurSel);;
    } else { // 搜索
        //setSearchInf(CurSel);;
    }

    *pResult = 0;
}
    
// 点击树状控件
void CWLRClientDlg::OnTvnSelchangedTreeMain(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
    // TODO: 在此添加控件通知处理程序代码
	//得到选项句柄
    HTREEITEM selectHtm = mTreeMain.GetSelectedItem();
    CString strSelect = mTreeMain.GetItemText(selectHtm);
	KillTimer(AUTO_REFRESH_TIMER_ID);
    //得到父节点句柄
	HTREEITEM parentHtm = mTreeMain.GetParentItem(selectHtm);
    CString parStr = mTreeMain.GetItemText(parentHtm);

    if (parStr==_T("中国")||parStr==_T(""))
        return;

	//MessageBox("您选中的是:" + parStr + " " + strSelect);
    
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
       
// 隐藏所有的窗口
int CWLRClientDlg::hideAllWindows() {
    // 货源
    newGoodsInf.ShowWindow(false);
    customGoodsInf.ShowWindow(false);
    myGoodsInf.ShowWindow(false); 

    // 零担
    newBulkGoodsInf.ShowWindow(false);
    myBulkGoodsInf.ShowWindow(false);

    // 车源
    newCarsInf.ShowWindow(false);
    customCarsInf.ShowWindow(false);
    myCarsInf.ShowWindow(false);

    // 专线
    allspecialLine.ShowWindow(false);
    mySpecialLine.ShowWindow(false);
    favoriteSpecialLine.ShowWindow(false);

    // 搜索
    searchGoodsInf.ShowWindow(false);
    searchBulkGoodsInf.ShowWindow(false);
    searchCarsInf.ShowWindow(false);
    searchSpecialLine.ShowWindow(false);

    return 0;
}
    
// 点击“拍照”按钮
void CWLRClientDlg::OnBnClickedBtnMainpage()
{
    // TODO: 在此添加控件通知处理程序代码
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
		//MessageBox("没有找到摄像头设备！", "560");
	}
	MessageBox("没有找到摄像头设备！", "560");
}
    
// 点击“货源”按钮
void CWLRClientDlg::OnBnClickedBtnGoods()
{
    // TODO: 在此添加控件通知处理程序代码
	EnterCriticalSection(&csClick);
	curTabIndex = 0;
    setGoodsInf();
	LeaveCriticalSection(&csClick);
}
    
// 点击“零担”按钮
void CWLRClientDlg::OnBnClickedBtnBulkgoods()
{
    // TODO: 在此添加控件通知处理程序代码
	EnterCriticalSection(&csClick);
	curTabIndex = 0;
    setBulkGoodsInf();
	LeaveCriticalSection(&csClick);
}
    
// 点击“车源”按钮
void CWLRClientDlg::OnBnClickedBtnCars()
{
    // TODO: 在此添加控件通知处理程序代码
	EnterCriticalSection(&csClick);
	curTabIndex = 0;
    setCarsInf();
	LeaveCriticalSection(&csClick);
}
    
// 点击“专线”按钮
void CWLRClientDlg::OnBnClickedBtnLine()
{
    // TODO: 在此添加控件通知处理程序代码
	EnterCriticalSection(&csClick);
	curTabIndex = 0;
    setSpecialLineInf();
	LeaveCriticalSection(&csClick);
}
    
// 点击“搜索”按钮
void CWLRClientDlg::OnBnClickedBtnSearch()
{
    // TODO: 在此添加控件通知处理程序代码
	KillTimer(AUTO_REFRESH_TIMER_ID);
    CSearchSelectDlg dlg;
	if (dlg.DoModal() == IDOK) { 
		search(dlg.selectValue, 2);

		//switch (dlg.selectValue) {
		//	case 0: // 搜索货源 
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
		//	case 1:	// 搜索零担
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
		//	case 2:	// 搜索车源
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
		//	case 3:	// 搜索专线
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
    
// 点击“系统设置”按钮
void CWLRClientDlg::OnBnClickedBtnSetting()
{
    // TODO: 在此添加控件通知处理程序代码
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
    // 保存配置
    saveConfig();

    // 刷新当前显示内容
    refreshShow();

    // 更新界面
	//LeaveCriticalSection(&csPrint);
    //Invalidate();    
    //mTabMain.Invalidate();
    //RedrawWindow(NULL,NULL,RDW_ERASENOW);
}
    
// 点击“增值服务”按钮
void CWLRClientDlg::OnBnClickedBtnPayservice()
{
    // TODO: 在此添加控件通知处理程序代码
    CValueAddedServiceDlg dlg;
    dlg.DoModal();
}
    
// 点击“自动刷新”按钮
void CWLRClientDlg::OnBnClickedBtnAutoupdate()
{
    // TODO: 在此添加控件通知处理程序代码
    if (ifAutoRefresh) {
	//	autoRefresh.LoadBitmap(IDB_AUTOREFRESH);
        stopTimer();
      //  autoRefresh.SetWindowTextA("自动刷新");
        //ifAutoRefresh = false;
        //MessageBox("自动刷新已关闭！", "自动刷新");
    } else {
		//autoRefresh.LoadBitmap(IDB_NOREFRESH);
        startTimer();
       // autoRefresh.SetWindowTextA("停止刷新");
        //ifAutoRefresh = true;
        //MessageBox("自动刷新已开启！", "自动刷新");
    }
}
    
// 点击“隐藏电话”按钮
void CWLRClientDlg::OnBnClickedBtnHidetel()
{
    // TODO: 在此添加控件通知处理程序代码
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
    if (curTabType == GOODS) { // 货源 
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
    
    if (curTabType == BULKGOODS) { // 零担 
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
    
    if (curTabType == CARS) { // 车源
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
    
    if (curTabType == LINES) { // 专线
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
 
/*xqh:删除快速发布功能
// 点击“快速发布”按钮
void CWLRClientDlg::OnBnClickedBtnPub()
{
    // TODO: 在此添加控件通知处理程序代码
    CPubSelectDlg dlg;
	if (dlg.DoModal() == IDOK) { 
		switch (dlg.selectValue) {
			case 0: // 发布货源 
                pubGoodsInf();
				break;
			case 1:	// 发布零担
                pubBulkGoodsInf();
				break;
			case 2:	// 发布车源
                pubCarsInf();
				break;
			case 3:	// 发布专线
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
    
// 设置货源信息

int CWLRClientDlg::setGoodsInf(int tabIndex)
{
    curTabType = GOODS;
    hideAllWindows();

    mTabMain.DeleteAllItems();
    mTabMain.InsertItem(0,"最新货源");
    mTabMain.InsertItem(1,"定制信息");
    mTabMain.InsertItem(2,"我的货源");
    
    //获得IDC_TABTEST客户区大小
    CRect rect;
    mTabMain.GetClientRect(&rect);

    //调整子对话框在父窗口中的位置
    rect.top+=20; 
    rect.left+=1; 
    rect.right-=2;
    
    if (0 == tabIndex) { // 最新货源    
        //设置子对话框尺寸并移动到指定位置
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
        //分别设置隐藏和显示
        newGoodsInf.ShowWindow(true);
        // 显示数据
        newGoodsInf.svrIONew = &svrIONew; 
		newGoodsInf.svrIO = &svrIOMore;

        newGoodsInf.setIfShowPhone(ifShowPhone); 
        newGoodsInf.setData(0);
    } else if (1 == tabIndex) { // 定制信息
		showtype = CustomGood;
		index = 0;
		SetTimer(AUTO_REFRESH_TIMER_ID, 1500, NULL);
        //设置子对话框尺寸并移动到指定位置
        customGoodsInf.MoveWindow(&rect);
        //分别设置隐藏和显示
        customGoodsInf.ShowWindow(true);
        // 显示数据
        customGoodsInf.svrIO = &svrIO; 
		customGoodsInf.svrIONew = &svrIOCustom;
        customGoodsInf.setIfShowPhone(ifShowPhone); 
        customGoodsInf.setGoods();
    } else { // 我的货源
        //设置子对话框尺寸并移动到指定位置
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
        //分别设置隐藏和显示
        myGoodsInf.ShowWindow(true); 
        // 显示数据
        myGoodsInf.svrIO = &svrIOMy;
		myGoodsInf.svrIONew = &svrIOMy;
        myGoodsInf.setIfShowPhone(ifShowPhone); 
        myGoodsInf.setData(0);
    }    

    //设置默认的选项卡
    mTabMain.SetCurSel(tabIndex);

    //mTabMain.UpdateData(false);

    return 0;
}
       
// 设置零担信息
int CWLRClientDlg::setBulkGoodsInf(int tabIndex)
{
    curTabType = BULKGOODS;
    hideAllWindows();

    mTabMain.DeleteAllItems();
    mTabMain.InsertItem(0,"最新零担");
    mTabMain.InsertItem(1,"我的零担");
    
    //获得IDC_TABTEST客户区大小
    CRect rect;
    mTabMain.GetClientRect(&rect);

    //调整子对话框在父窗口中的位置
    rect.top+=20; 
    rect.left+=1; 
    rect.right-=2;
    
    if (0 == tabIndex) {
		showtype = NewBulkGood;
        // 设置子对话框尺寸并移动到指定位置
        newBulkGoodsInf.MoveWindow(&rect);
        // 分别设置隐藏和显示
        newBulkGoodsInf.ShowWindow(true);
        // 显示数据
        newBulkGoodsInf.svrIO = &svrIOMore;
		newBulkGoodsInf.svrIONew = &svrIONew;
        newBulkGoodsInf.setIfShowPhone(ifShowPhone); 
        newBulkGoodsInf.setData(1);
    } else {
		showtype = MyBulkGood;
        // 设置子对话框尺寸并移动到指定位置
        myBulkGoodsInf.MoveWindow(&rect);
        // 分别设置隐藏和显示
        myBulkGoodsInf.ShowWindow(true);
        // 显示数据
        myBulkGoodsInf.svrIO = &svrIOMy; 
		myBulkGoodsInf.svrIONew = &svrIOMy; 
        myBulkGoodsInf.setIfShowPhone(ifShowPhone); 
        myBulkGoodsInf.setData(1);
    }   

    //设置默认的选项卡
    mTabMain.SetCurSel(tabIndex);

    return 0;
}    
     
// 设置车源信息
int CWLRClientDlg::setCarsInf(int tabIndex)
{
    curTabType = CARS;
    hideAllWindows();

    mTabMain.DeleteAllItems();
    mTabMain.InsertItem(0,"最新车源");
    mTabMain.InsertItem(1,"定制信息");
    mTabMain.InsertItem(2,"我的车源");
    
    //获得IDC_TABTEST客户区大小
    CRect rect;
    mTabMain.GetClientRect(&rect);

    //调整子对话框在父窗口中的位置
    rect.top+=20; 
    rect.left+=1; 
    rect.right-=2;
    
    if (0 == tabIndex) { // 最新车源    
        //设置子对话框尺寸并移动到指定位置
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
        //分别设置隐藏和显示
        newCarsInf.ShowWindow(true);
        // 显示数据
        newCarsInf.svrIO = &svrIOMore;
		newCarsInf.svrIONew = &svrIONew;
        newCarsInf.setIfShowPhone(ifShowPhone); 
        newCarsInf.setData(2);
    } else if (1 == tabIndex) { // 定制信息
		showtype = CustomCar;
		SetTimer(AUTO_REFRESH_TIMER_ID, 1500, NULL);
        //设置子对话框尺寸并移动到指定位置
		//Sleep(200);
		index = 0;
        customCarsInf.MoveWindow(&rect);
        //分别设置隐藏和显示
        customCarsInf.ShowWindow(true);
        // 显示数据
        customCarsInf.svrIO = &svrIO;
		customCarsInf.svrIONew = &svrIOCustom;
        customCarsInf.setIfShowPhone(ifShowPhone); 
        customCarsInf.setCars();
    } else { // 我的车源
        //设置子对话框尺寸并移动到指定位置
		//ResumeThread(hThread);
		showtype = MyCar;
        myCarsInf.MoveWindow(&rect);
        //分别设置隐藏和显示
        myCarsInf.ShowWindow(true); 
        // 显示数据
        myCarsInf.svrIO = &svrIOMy;
		myCarsInf.svrIONew = &svrIOMy;
        myCarsInf.setIfShowPhone(ifShowPhone); 
        myCarsInf.setData(2);
    }    

    //设置默认的选项卡
    mTabMain.SetCurSel(tabIndex);

    return 0;
}
    
// 设置专线信息
int CWLRClientDlg::setSpecialLineInf(int tabIndex)
{
    curTabType = LINES;
    hideAllWindows();

    mTabMain.DeleteAllItems();
    mTabMain.InsertItem(0,"所有专线");
    mTabMain.InsertItem(1,"我的专线");
    mTabMain.InsertItem(2,"我的收藏");
    
    //获得IDC_TABTEST客户区大小
    CRect rect;
    mTabMain.GetClientRect(&rect);

    //调整子对话框在父窗口中的位置
    rect.top+=20; 
    rect.left+=1; 
    rect.right-=2;
    
    if (0 == tabIndex) { // 所有专线    
        //设置子对话框尺寸并移动到指定位置
		showtype = NewSpecial;
        allspecialLine.MoveWindow(&rect);
        //分别设置隐藏和显示
        allspecialLine.ShowWindow(true);
        // 显示数据
        allspecialLine.svrIO = &svrIOSpecial;
		allspecialLine.svrIONew = &svrIOSpecial;
        allspecialLine.setIfShowPhone(ifShowPhone); 
        allspecialLine.setData(0);
    } else if (1 == tabIndex) { // 我的专线
         //设置子对话框尺寸并移动到指定位置
		showtype = MySpecial;
        mySpecialLine.MoveWindow(&rect);
        //分别设置隐藏和显示
        mySpecialLine.ShowWindow(true);
        // 显示数据
        mySpecialLine.svrIO = &svrIOSpecial;
		mySpecialLine.svrIONew = &svrIOSpecial;
        mySpecialLine.setIfShowPhone(ifShowPhone); 
        mySpecialLine.setData(1);
    } else { // 我的收藏
        //设置子对话框尺寸并移动到指定位置
		showtype = MyFavoritesSpecial;
        favoriteSpecialLine.MoveWindow(&rect);
        //分别设置隐藏和显示
        favoriteSpecialLine.ShowWindow(true);
        // 显示数据
        favoriteSpecialLine.svrIO = &svrIOSpecial; 
		favoriteSpecialLine.svrIONew = &svrIOSpecial;
        favoriteSpecialLine.setIfShowPhone(ifShowPhone); 
        favoriteSpecialLine.setData(2);
    }    

    //设置默认的选项卡
    mTabMain.SetCurSel(tabIndex);

    return 0;
}
    
void CWLRClientDlg::search(UINT8 nType, UINT8 nOption/* = 1*/)
{
	switch (nType) 
	{
	case eSearchType_Goods: // 搜索货源 
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
	case eSearchType_Car:	// 搜索车源
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
	case eSearchType_SpecialLine:	// 搜索专线
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
	case eSearchType_BulkGoods:	// 搜索零担
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
// 搜索货源
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
    mTabMain.InsertItem(0,"搜索货源结果");
    
    //获得IDC_TABTEST客户区大小
    CRect rect;
    mTabMain.GetClientRect(&rect);

    //调整子对话框在父窗口中的位置
    rect.top+=20; 
    rect.left+=1; 
    rect.right-=2;    
  
    //设置子对话框尺寸并移动到指定位置
    searchGoodsInf.MoveWindow(&rect);
    //分别设置隐藏和显示
    searchGoodsInf.ShowWindow(true);
    // 显示数据
    searchGoodsInf.svrIO = &svrIO; 
    searchGoodsInf.svrIONew = &svrIONew; 
	//searchGoodsInf.goodsKeyword = input;
	searchGoodsInf.sSearchCriteria = sSearchCriteria;
	//FillGoodsSearchCriteria(pSearchCriteria, searchGoodsInf.goodsKeyword);
    searchGoodsInf.setIfShowPhone(ifShowPhone); 
    searchGoodsInf.setData(3);

	//option:0，本地；1，取消；2，正常搜索
	/*searchGoodsInf.SetStartAddr(input.startProvince, input.startCity, input.startCounty, true);
	searchGoodsInf.SetDestAddr(input.endProvince, input.endCity, input.endCounty, nOption==2?true:false);

	newGoodsInf.SetStartAddr(input.startProvince, input.startCity, input.startCounty, true);
	newGoodsInf.SetDestAddr(input.endProvince, input.endCity, input.endCounty, nOption==2?true:false);*/
    return 0;
}
    
// 搜索零担
int CWLRClientDlg::setSearchBulkGoods(const InSearchBulkGoods& input, UINT8 nOption)
{
    curTabType = SEARCH_BULKGOODS;
    hideAllWindows();

    mTabMain.DeleteAllItems();
    mTabMain.InsertItem(0,"搜索零担结果");
    
    //获得IDC_TABTEST客户区大小
    CRect rect;
    mTabMain.GetClientRect(&rect);

    //调整子对话框在父窗口中的位置
    rect.top+=20; 
    rect.left+=1; 
    rect.right-=2;    
  
    //设置子对话框尺寸并移动到指定位置
    searchBulkGoodsInf.MoveWindow(&rect);
    //分别设置隐藏和显示
    searchBulkGoodsInf.ShowWindow(true);
    // 显示数据
    searchBulkGoodsInf.svrIO = &svrIO; 
    searchBulkGoodsInf.svrIONew = &svrIONew;
    searchBulkGoodsInf.setIfShowPhone(ifShowPhone); 
    searchBulkGoodsInf.bulkGoodsKeyword = input;
    searchBulkGoodsInf.setData(4);
    return 0;
}
    
// 搜索车源
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
    mTabMain.InsertItem(0,"搜索车源结果");
    
    //获得IDC_TABTEST客户区大小
    CRect rect;
    mTabMain.GetClientRect(&rect);

    //调整子对话框在父窗口中的位置
    rect.top+=20; 
    rect.left+=1; 
    rect.right-=2;    
  
    //设置子对话框尺寸并移动到指定位置
    searchCarsInf.MoveWindow(&rect);
    //分别设置隐藏和显示
    searchCarsInf.ShowWindow(true);
    // 显示数据
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
    
// 搜索专线
int CWLRClientDlg::setSearchSpecail(const InSearchSpecail& input, UINT8 nOption)
{
    curTabType = SEARCH_SPECIAL;
    hideAllWindows();

    mTabMain.DeleteAllItems();
    mTabMain.InsertItem(0,"搜索专线结果");
    
    //获得IDC_TABTEST客户区大小
    CRect rect;
    mTabMain.GetClientRect(&rect);

    //调整子对话框在父窗口中的位置
    rect.top+=20; 
    rect.left+=1; 
    rect.right-=2;    
  
    searchSpecialLine.MoveWindow(&rect);
    //分别设置隐藏和显示
    searchSpecialLine.ShowWindow(true);
    // 显示数据
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
    
// 设置点击搜索信息：货源
int CWLRClientDlg::clickSearchGoods(InClickSearch input)
{
    curTabType = CLICK_SEARCH_GOODS;

    hideAllWindows();

    mTabMain.DeleteAllItems();
    mTabMain.InsertItem(0,"搜索货源结果");
    
    //获得IDC_TABTEST客户区大小
    CRect rect;
    mTabMain.GetClientRect(&rect);

    //调整子对话框在父窗口中的位置
    rect.top+=20; 
    rect.left+=1; 
    rect.right-=2;

    //设置子对话框尺寸并移动到指定位置
    searchGoodsInf.MoveWindow(&rect);
    //分别设置隐藏和显示
    searchGoodsInf.ShowWindow(true);
    // 显示数据
    searchGoodsInf.svrIO = &svrIO;
	searchGoodsInf.svrIONew = &svrIONew;
    searchGoodsInf.setIfShowPhone(ifShowPhone); 
    searchGoodsInf.clickKeyWord = input;
    searchGoodsInf.setData(6);

    //设置默认的选项卡
    mTabMain.SetCurSel(0);

    return 0;
}
    
// 设置点击搜索信息：零担
int CWLRClientDlg::clickSearchBulkGoods(InClickSearch input)
{
    curTabType = CLICK_SEARCH_BULKGOODS;
    hideAllWindows();

    mTabMain.DeleteAllItems();
    mTabMain.InsertItem(0,"搜索零担结果");
    
    //获得IDC_TABTEST客户区大小
    CRect rect;
    mTabMain.GetClientRect(&rect);

    //调整子对话框在父窗口中的位置
    rect.top+=20; 
    rect.left+=1; 
    rect.right-=2;    
  
    // 设置子对话框尺寸并移动到指定位置
    searchBulkGoodsInf.MoveWindow(&rect);
    // 分别设置隐藏和显示
    searchBulkGoodsInf.ShowWindow(true);
    // 显示数据
    searchBulkGoodsInf.svrIO = &svrIO;
	searchBulkGoodsInf.svrIONew = &svrIONew;
    searchBulkGoodsInf.setIfShowPhone(ifShowPhone); 
    searchBulkGoodsInf.clickKeyWord = input;
    searchBulkGoodsInf.setData(7);

    //设置默认的选项卡
    mTabMain.SetCurSel(0);
    return 0;
}   
    
// 设置点击搜索信息：车源
int CWLRClientDlg::clickSearchCars(InClickSearch input)
{
    curTabType = CLICK_SEARCH_CARS;
    hideAllWindows();

    mTabMain.DeleteAllItems();
    mTabMain.InsertItem(0,"搜索车源结果");
    
    //获得IDC_TABTEST客户区大小
    CRect rect;
    mTabMain.GetClientRect(&rect);

    //调整子对话框在父窗口中的位置
    rect.top+=20; 
    rect.left+=1; 
    rect.right-=2;
  
    //设置子对话框尺寸并移动到指定位置
    searchCarsInf.MoveWindow(&rect);
    //分别设置隐藏和显示
    searchCarsInf.ShowWindow(true);
    // 显示数据
    searchCarsInf.svrIO = &svrIO; 
	searchCarsInf.svrIONew = &svrIONew;
    searchCarsInf.setIfShowPhone(ifShowPhone); 
    searchCarsInf.clickKeyWord = input;
    searchCarsInf.setData(8);

    //设置默认的选项卡
    mTabMain.SetCurSel(0);
    return 0;
}
    
// 设置点击搜索信息：专线
int CWLRClientDlg::clickSearchSpecialLine(InClickSearch input)
{
    curTabType = CLICK_SEARCH_SPECIAL;
    hideAllWindows();

    mTabMain.DeleteAllItems();
    mTabMain.InsertItem(0,"搜索专线结果");
    
    //获得IDC_TABTEST客户区大小
    CRect rect;
    mTabMain.GetClientRect(&rect);

    //调整子对话框在父窗口中的位置
    rect.top+=20; 
    rect.left+=1; 
    rect.right-=2;
  
    //设置子对话框尺寸并移动到指定位置
    searchSpecialLine.MoveWindow(&rect);
    //分别设置隐藏和显示
    searchSpecialLine.ShowWindow(true);
    // 显示数据
    searchSpecialLine.svrIO = &svrIO; 
	searchSpecialLine.svrIONew = &svrIONew;
    searchSpecialLine.clickKeyWord = input;
    searchSpecialLine.setIfShowPhone(ifShowPhone); 
    searchSpecialLine.setData(4);

    //设置默认的选项卡
    mTabMain.SetCurSel(0);

    return 0;
}
        
// 发布货源
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
            MessageBox("货源发布成功！");
			//Sleep(2000);
            // 刷新显示
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
    
// 发布零担
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
            MessageBox("零担发布成功！");
			//Sleep(2000);
            // 刷新显示
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
    
// 发布车源
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
            MessageBox("车源发布成功！");
			//Sleep(2000);
            // 刷新显示
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
    
// 发布专线
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
            MessageBox("专线发布成功！");
			//Sleep(2000);
            // 刷新显示
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
    
// 刷新当前显示
void CWLRClientDlg::refreshShow()
{
	//return;
	try 
	{
		//EnterCriticalSection(&csPrintFresh);
		if (curTabType == GOODS) { // 货源 
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
		} else if (curTabType == BULKGOODS) { // 零担 
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
		} else if (curTabType == CARS) {      // 车源
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
		} else if (curTabType == LINES) { // 专线
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
    
// 定时器
void CWLRClientDlg::OnTimer(UINT_PTR nIDEvent)
{
    // TODO: 在此添加消息处理程序代码和/或调用默认值
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
	if (nIDEvent == AUTO_REFRESH_TIMER_ID) {  // 刷新显示
		//EnterCriticalSection(&csPrint);
		//TRACE("1\n");
        //refreshShow();
		//LeaveCriticalSection(&csPrint);
	}

	if (nIDEvent == CHECK_NOTICE_TIMER_ID) { // 检查公告
		//EnterCriticalSection(&csPrint);
		try
		{
			if (!GLB::ifMiniSize)//最小化的时候不弹出公告
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

	if (nIDEvent == START_CHAT_CLIENT) {  // 启动聊天程序
        startChatClient();
		KillTimer(START_CHAT_CLIENT);
	}

	if (nIDEvent == SEND_ACCOUNT_MSG_TO_CHAT) { // 向聊天程序发消息
        sendAcountMsgToChat();
	}

    CDialog::OnTimer(nIDEvent);
}
    
// 开启广告滚动条
void CWLRClientDlg::startShowAD()
{
    pubAD.Create(this, &svrIO);//滚动广告创建
}
        
// 窗口或者应用程序终止时调用
void CWLRClientDlg::OnClose()
{
    // TODO: 在此添加消息处理程序代码和/或调用默认值
	SetEvent(hEvent);
	m_break = TRUE;
	m_bClose = TRUE;
	if(::WaitForSingleObject(hThread,1000)!=WAIT_OBJECT_0)
		TerminateThread(hThread,0x111);


    CDialog::OnOK();
}
    
// 销毁窗口
BOOL CWLRClientDlg::DestroyWindow()
{
    // TODO: 在此添加专用代码和/或调用基类
    //退出skinfeature界面库，释放内存资源。 
    //UnLoadSkin();

    return CDialog::DestroyWindow();
}
    
// 检查公告
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
    showMsg += "\n【系统】" + svrIO.sysScrollAd.inf + "\n";
    showMsg += "\n【代理商】" + svrIO.agPopAd.inf + "\n";
    
    CRect rect;
    GetWindowRect(&rect);

    // 建立非模态对话框
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

// 公告按钮
void CWLRClientDlg::OnBnClickedBtnNotice()
{
    // TODO: 在此添加控件通知处理程序代码、
    string showMsg(""),showMsgag("");
    //svrIO.getSystemScrollAd();
    showMsg += "\n【系统】" + svrIO.sysScrollAd.inf + "\n";

    //svrIO.getAgentPopAd();
    showMsg += "\n【代理商】" + svrIO.agPopAd.inf + "\n";

    CRect rect;
    GetWindowRect(&rect);

    // 建立非模态对话框
    CPopNoticeDlg *dlg = new CPopNoticeDlg;
    dlg->setPos(rect.right, rect.bottom);
    dlg->showMsg = showMsg.c_str();
	//dlg->showMsgAG = showMsgag.c_str();
    dlg->Create(IDD_POP_NOTICE, this);
    dlg->ShowWindow(SW_SHOW);
}

// 即将绘制控件
HBRUSH CWLRClientDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

    // TODO:  在此更改 DC 的任何属性
   /* if(nCtlColor == CTLCOLOR_DLG) { // 设置对话框背景色        
        bgBrush.DeleteObject();
        bgBrush.CreateSolidBrush(GLB::mainDlgBgColor);
        return bgBrush;  
    }
    */
    //pDC->SetBkColor(svrIO.myColor.sysBKClr);    
   
    // TODO:  如果默认的不是所需画笔，则返回另一个画笔
    return hbr;
}
    
// 开启聊天客户端
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

	// 开启发送账号信息给聊天客户端定时器
    SetTimer(SEND_ACCOUNT_MSG_TO_CHAT, 1000, NULL);
	return 0;
}
    
// 向聊天客户端发账号信息
int CWLRClientDlg::sendAcountMsgToChat()
{	
	CWnd * pWnd = NULL;
	pWnd = CWnd::FindWindow(NULL, "560聊天客户端");
	if (pWnd == NULL) {
		return 0;
	}
	
	// 关闭定时器
	KillTimer(SEND_ACCOUNT_MSG_TO_CHAT);
	
	//CString data = "first;test10;wlr";
	CString data = "first;";
	data = data + svrIO.userInf.loginName.c_str();
	data = data + ";";
	data = data + svrIO.userInf.province.c_str();
	data = data + ";";
	data = data + svrIO.userInf.city.c_str();
	data = data + ";wlr";
	COPYDATASTRUCT cpd;                     // 给COPYDATASTRUCT结构赋值
	cpd.dwData = 0;
	cpd.cbData = data.GetLength();
	cpd.lpData = (void*)data.GetBuffer(cpd.cbData);
	if (pWnd != NULL)
	{
		pWnd->SendMessage(WM_COPYDATA,NULL,(LPARAM)&cpd);   // 发送
	}
	return 0;
}


// 向聊天客户端发位置信息
void CWLRClientDlg::OnMove(int x, int y)
{
	CDialog::OnMove(x, y);

	// TODO: 在此处添加消息处理程序代码

	/*CWnd * pWnd = CWnd ::FindWindow(NULL, "560聊天客户端");

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

	COPYDATASTRUCT cpd;                     // 给COPYDATASTRUCT结构赋值

	cpd.dwData = 0;

	cpd.cbData = data.GetLength();

	cpd.lpData = (void*)data.GetBuffer(cpd.cbData);
	CRect r;
	pWnd->GetWindowRect(&r);
	static int fir = 0;
	//判断当前要吸附的窗口是否在范围内吸附
	if (abs(r.left - rect.right) < 10 && !m_dock)//不在吸附状态
	{
		CString data1 = "move;";
		
		COPYDATASTRUCT cpd1;                     // 给COPYDATASTRUCT结构赋值

		cpd1.dwData = 0;

		cpd1.cbData = data1.GetLength();

		cpd1.lpData = (void*)data1.GetBuffer(cpd1.cbData);

		pWnd->SendMessage(WM_COPYDATA,NULL,(LPARAM)&cpd1);   // 发送
		m_dock = TRUE;
	} 

	if (m_dock)
	{
		pWnd->SendMessage(WM_COPYDATA,NULL,(LPARAM)&cpd);   // 发送
	}
	rectw = rect;*/
}


// 接收聊天客户端消息
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
//点击聊天按钮
void CWLRClientDlg::OnBnClickedBtnChat()
{
	// TODO: 在此添加控件通知处理程序代码
	startChatClient();
}

//定时收取数据
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
		while(1)//最新货源
		{
			int i = 90;//初始化大小，用于判断是否收取完全或者断线
			try 
			{
				inputParam curInput;
				curInput.curpage =1;
				curInput.record = RECORD_NUM;//记录总数+nnewhy
				curInput.customid = "0";
				i = pDlg->svrIO.getNewGoodsInf(contentDataHY, curInput);
				while (1)
				{
					if (i==0)//数据接收完全
					{
						retValue = pDlg->svrIO.getAgentScrollAd();//滚动条广告

						result1 = pDlg->svrIO.getSystemScrollAd();//弹出公告

						result2 = pDlg->svrIO.getAgentPopAd();

						if ("TRUE" == result1 || "TRUE" == result2)
							::SendMessage(pDlg->GetSafeHwnd(),WM_TCGG,0,0);//通知消息处理弹出公告函数
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
						//货源 车源定制按时间排序 排序

						sort(zoneInfHY.begin(),zoneInfHY.end(),greatermark);
						sort(zoneInfCY.begin(),zoneInfCY.end(),greatermark);

						if(showtype == NewGood)
						::SendMessage(pDlg->GetSafeHwnd(),WM_SENDFRESH,0,0);
						break;
					}
					if (i == -1)//网络断线
					{
						//重新登陆
						string result = pDlg->svrIO.usrLogin(user.loginName, user.passWord);
						if (result != "TRUE") {//登陆不成功继续登陆

							if (pDlg->m_break)//关闭时跳出死循环
							{
								break;
							}
						} else {//登陆成功跳出死循环
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

		EnterCriticalSection(&csPrint);//定制信息车源

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
				int i = 90;//初始化大小，用于判断是否收取完全或者断线
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
						if (i==0)//数据接收完全
						{
							if(showtype == CustomCar)
							::SendMessage(pDlg->GetSafeHwnd(),WM_SENDFRESH,0,0);
							nCysize++;
							goto start1;
							//continue;
						}
						if (i == -1)//网络断线
						{
							//重新登陆
							string result = pDlg->svrIO.usrLogin(user.loginName, user.passWord);
							if (result != "TRUE") {//登陆不成功继续登陆
								if (pDlg->m_break)//关闭时跳出死循环
								{
									break;
								}

							} else {//登陆成功跳出死循环
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
		EnterCriticalSection(&csPrint);//定制信息货源
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
				int i = 90;//初始化大小，用于判断是否收取完全或者断线
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
						if (i==0)//数据接收完全
						{
							if(showtype == CustomGood)
							::SendMessage(pDlg->GetSafeHwnd(),WM_SENDFRESH,0,0);
							nHysize++;
							goto start;
						}
						if (i == -1)//网络断线
						{
							//重新登陆
							string result = pDlg->svrIO.usrLogin(user.loginName, user.passWord);
							if (result != "TRUE") {//登陆不成功继续登陆
								if (pDlg->m_break)//关闭时跳出死循环
								{
									break;
								}

							} else {//登陆成功跳出死循环
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




		EnterCriticalSection(&csPrint);//最新零担
		while(1)
		{
			int i = 90;//初始化大小，用于判断是否收取完全或者断线
			try 
			{
				inputParam curInput;
				curInput.curpage =1;
				curInput.record = RECORD_NUM;
				curInput.customid = "0";
				i = pDlg->svrIO.getNewBulkGoodsInf(contentDataLD, curInput);
				while (1)
				{
					if (i==0)//数据接收完全
					{
						if(showtype == NewBulkGood)
						::SendMessage(pDlg->GetSafeHwnd(),WM_SENDFRESH,0,0);
						break;
					}
					if (i == -1)//网络断线
					{
						//重新登陆
						string result = pDlg->svrIO.usrLogin(user.loginName, user.passWord);
						if (result != "TRUE") {//登陆不成功继续登陆
							if (pDlg->m_break)//关闭时跳出死循环
							{
								break;
							}

						} else {//登陆成功跳出死循环
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
		EnterCriticalSection(&csPrint);//最新车源
		while(1)
		{

			int i = 90;//初始化大小，用于判断是否收取完全或者断线
			try 
			{
				inputParam curInput;
				curInput.curpage =1;
				curInput.record = RECORD_NUM;
				curInput.customid = "0";
				i = pDlg->svrIO.getNewCarsInf(contentDataCY, curInput);
				while (1)
				{
					if (i==0)//数据接收完全
					{
						if(showtype == NewCar)
						::SendMessage(pDlg->GetSafeHwnd(),WM_SENDFRESH,0,0);
						break;
					}
					if (i == -1)//网络断线
					{
						//重新登陆
						string result = pDlg->svrIO.usrLogin(user.loginName, user.passWord);
						if (result != "TRUE") {//登陆不成功继续登陆
							if (pDlg->m_break)//关闭时跳出死循环
							{
								break;
							}

						} else {//登陆成功跳出死循环
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

		EnterCriticalSection(&csPrint);//我的货源
		while(1)
		{

			int i = 90;//初始化大小，用于判断是否收取完全或者断线
			try 
			{
				i = pDlg->svrIO.getMyGoodsInf(contentDataMYHY, curInput);
				while (1)
				{
					if (i==0)//数据接收完全
					{
						if(showtype == MyGood)
						::SendMessage(pDlg->GetSafeHwnd(),WM_SENDFRESH,0,0);
						break;
					}
					if (i == -1)//网络断线
					{
						//重新登陆
						string result = pDlg->svrIO.usrLogin(user.loginName, user.passWord);
						if (result != "TRUE") {//登陆不成功继续登陆
							if (pDlg->m_break)//关闭时跳出死循环
							{
								break;
							}

						} else {//登陆成功跳出死循环
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
		EnterCriticalSection(&csPrint);//我的零担
		while(1)
		{
			int i = 90;//初始化大小，用于判断是否收取完全或者断线
			try 
			{
				i = pDlg->svrIO.getMyBulkGoodsInf(contentDataMYLD, curInput);
				while (1)
				{
					if (i==0)//数据接收完全
					{
						//发送消息通知进行刷新
						if(showtype == MyBulkGood)
						::SendMessage(pDlg->GetSafeHwnd(),WM_SENDFRESH,0,0);
						break;
					}
					if (i == -1)//网络断线
					{
						//重新登陆
						string result = pDlg->svrIO.usrLogin(user.loginName, user.passWord);
						if (result != "TRUE") {//登陆不成功继续登陆
							if (pDlg->m_break)//关闭时跳出死循环
							{
								break;
							}

						} else {//登陆成功跳出死循环
							break;
						}
					}
					Sleep(100);//延时100毫秒
				}
				break;
			}
			catch (...)
			{
			}
		}
		LeaveCriticalSection(&csPrint);
		EnterCriticalSection(&csPrint);//我的车源
		while(1)
		{
			int i = 90;//初始化大小，用于判断是否收取完全或者断线
			try 
			{
				i = pDlg->svrIO.getMyCarsInf(contentDataMYCY, curInput);
				while (1)
				{
					if (i==0)//数据接收完全
					{
						if(showtype == MyCar)
						::SendMessage(pDlg->GetSafeHwnd(),WM_SENDFRESH,0,0);
						break;
					}
					if (i == -1)//网络断线
					{
						//重新登陆
						string result = pDlg->svrIO.usrLogin(user.loginName, user.passWord);
						if (result != "TRUE") {//登陆不成功继续登陆
							if (pDlg->m_break)//关闭时跳出死循环
							{
								break;
							}

						} else {//登陆成功跳出死循环
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
		EnterCriticalSection(&csPrint);//所有专线
		while(1)
		{
			int i = 90;//初始化大小，用于判断是否收取完全或者断线
			try 
			{
				i = pDlg->svrIO.getAllSpecialLineInf(contentDataALL, curInput);
				while (1)
				{
					if (i==0)//数据接收完全
					{
						if(showtype == NewSpecial)
						::SendMessage(pDlg->GetSafeHwnd(),WM_SENDFRESH,0,0);
						break;
					}
					if (i == -1)//网络断线
					{
						//重新登陆
						string result = pDlg->svrIO.usrLogin(user.loginName, user.passWord);
						if (result != "TRUE") {//登陆不成功继续登陆
							if (pDlg->m_break)//关闭时跳出死循环
							{
								break;
							}

						} else {//登陆成功跳出死循环
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
		EnterCriticalSection(&csPrint);//我的专线
		while(1)
		{
			int i = 90;//初始化大小，用于判断是否收取完全或者断线
			try 
			{
				i = pDlg->svrIO.getMySpecialLineInf(contentDataMY, curInput);
				while (1)
				{
					if (i==0)//数据接收完全
					{
						if(showtype == MySpecial)
						::SendMessage(pDlg->GetSafeHwnd(),WM_SENDFRESH,0,0);
						break;
					}
					if (i == -1)//网络断线
					{
						//重新登陆
						string result = pDlg->svrIO.usrLogin(user.loginName, user.passWord);
						if (result != "TRUE") {//登陆不成功继续登陆
							if (pDlg->m_break)//关闭时跳出死循环
							{
								break;
							}

						} else {//登陆成功跳出死循环
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
		EnterCriticalSection(&csPrint);//收藏专线
		while(1)
		{
			int i = 90;//初始化大小，用于判断是否收取完全或者断线
			try 
			{
				i = pDlg->svrIO.getFavoriteSpecialLineInf(contentDataSAVE, curInput);
				while (1)
				{
					if (i==0)//数据接收完全
					{
						if(showtype == MyFavoritesSpecial)
						::SendMessage(pDlg->GetSafeHwnd(),WM_SENDFRESH,0,0);
						break;
					}
					if (i == -1)//网络断线
					{
						//重新登陆
						string result = pDlg->svrIO.usrLogin(user.loginName, user.passWord);
						if (result != "TRUE") {//登陆不成功继续登陆
							if (pDlg->m_break)//关闭时跳出死循环
							{
								break;
							}

						} else {//登陆成功跳出死循环
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
//定时刷新 滚动条广告 数据
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
			//retValue = pDlg->svrIO.getAgentScrollAd();//滚动条广告
		}
		catch (...)
		{
		}
		LeaveCriticalSection(&csPrint);
		
	}*/
	CoUninitialize();
 	return 0;
}
//定时刷新 弹出公告 数据
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
			result1 = pDlg->svrIO.getSystemScrollAd();//弹出公告
			result2 = pDlg->svrIO.getAgentPopAd();
			if ("TRUE" == result1 || "TRUE" == result2)
				::SendMessage(pDlg->GetSafeHwnd(),WM_TCGG,0,0);//通知消息处理弹出公告函数
		}
		catch (...)
		{
		}
		LeaveCriticalSection(&csPrint);
	}*/
	CoUninitialize();
	return 0;
}
//服务站
void CWLRClientDlg::OnBnClickedBtnServer()
{
	// TODO: 在此添加控件通知处理程序代码
	//MessageBox("服务站正在筹建中，敬请期待！","560");
	CDlgService dlg;
	dlg.svrIO = &svrIOService;
	dlg.DoModal();
}
//560网
void CWLRClientDlg::OnBnClickedBtnWlr()
{
	// TODO: 在此添加控件通知处理程序代码
	//string url = "http://www.wibang.com";
	//string url = "http://192.168.10.212";
	string str = WEB_SERVICE_ADDRESS + "/fmp/user.login.action?user.name=" + svrIO.userInf.loginName
	+ "&user.pwd=" + svrIO.userInf.passWord; 

//string str ="http://218.108.51.235:8888/UserLogin.aspx";
	HWND pwnd = ::FindWindow(NULL,"560网站");
	if (pwnd)
	{
		::ShowWindow(pwnd, SW_SHOWNORMAL); //激活显示找到的已运行的程序
		::SetForegroundWindow(pwnd);       //将已运行的程序设置为当前窗口
	} 
	else
	{
		CWebHTTP * dlg = new CWebHTTP;
		dlg->url = str;
		dlg->Create(IDD_DLGWEB,GetDesktopWindow());
		dlg->SetWindowText("560网站");
		int nFullWidth=GetSystemMetrics(SM_CXSCREEN);     
		int nFullHeight=GetSystemMetrics(SM_CYSCREEN);
		dlg->ShowWindow(TRUE);
		dlg->SetWindowPos(NULL,0,0,nFullWidth,nFullHeight-29,SWP_SHOWWINDOW);
	}
}

//用户中心
void CWLRClientDlg::OnBnClickedCenter()
{
	// TODO: 在此添加控件通知处理程序代码
	string str = WEB_SERVICE_ADDRESS + "/fmp/user.login.action?user.name=" + svrIO.userInf.loginName
		+ "&user.pwd=" + svrIO.userInf.passWord; 
	//string str = "www.baidu.com";
	HWND pwnd = ::FindWindow(NULL,"560用户中心");
	if (pwnd)
	{
		::ShowWindow(pwnd, SW_SHOWNORMAL); //激活显示找到的已运行的程序
		::SetForegroundWindow(pwnd);       //将已运行的程序设置为当前窗口
	} 
	else
	{
		CUserCenter * dlg = new CUserCenter;
		dlg->url = str;
		dlg->Create(IDD_USERCENTER,GetDesktopWindow());
		dlg->SetWindowText("560用户中心");
		int nFullWidth=GetSystemMetrics(SM_CXSCREEN);     
		int nFullHeight=GetSystemMetrics(SM_CYSCREEN);
		dlg->ShowWindow(TRUE);
		dlg->SetWindowPos(NULL,0,0,nFullWidth,nFullHeight-29,SWP_SHOWWINDOW);
	}
}

//
//处理消息刷新
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
//弹出公告
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

//初始设置颜色
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
	// TODO: 在此添加控件通知处理程序代码
	//OnOK();
	AfxMessageBox("OK");
}

void CWLRClientDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	//OnCancel();
}

//发布货源
void CWLRClientDlg::OnBnClickedBtnReleasegoods()
{
	CPublishWayOneDlg dlg;
	dlg.DoModal();
	// TODO: Add your control notification handler code here
	if ( is_funcs_enabled ) 
		pubGoodsInf();
	else
		AfxMessageBox("只是有收费和试用用户才能够发布货源");
}

//发布车源
void CWLRClientDlg::OnBnClickedBtnReleasetruckinfo()
{
	// TODO: Add your control notification handler code here
	// TODO: Add your control notification handler code here
	if ( is_funcs_enabled ) 
		pubCarsInf();
	else
		AfxMessageBox("只是有收费和试用用户才能够发布车源");
}

void CWLRClientDlg::OnBnClickedBtnReleasespecialline()
{
	// TODO: Add your control notification handler code here
	if ( is_funcs_enabled ) 
		pubSpecialLineInf();
	else
		AfxMessageBox("只是有收费和试用用户才能够发布专线");
}


//打开网页
void CWLRClientDlg::OpenWebPage(string & url,string &title)
{	
	TCHAR * wndTitle = (TCHAR*)title.c_str();

	HWND pwnd = ::FindWindow(NULL,wndTitle);
	if (pwnd)
	{
		::ShowWindow(pwnd, SW_SHOWNORMAL); //激活显示找到的已运行的程序
		::SetForegroundWindow(pwnd);       //将已运行的程序设置为当前窗口
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

//我的账户
void CWLRClientDlg::OnBnClickedBtnMyaccountant()
{
	// TODO: Add your control notification handler code here
	string url = WEB_SERVICE_ADDRESS+"/fmp/user.login.action?username=" + svrIO.userInf.loginName
		+ "&password=" + svrIO.userInf.passWord+"&target=accountant";
	string title = "我的账户";
	OpenWebPage(url,title);
}

//积分商城
void CWLRClientDlg::OnBnClickedBtnShoppingMall()
{
	// TODO: Add your control notification handler code here
	string url = WEB_SERVICE_ADDRESS+"/fmp/user.login.action?username=" + svrIO.userInf.loginName
		+ "&password=" + svrIO.userInf.passWord+"&target=mall";
	string title = "积分商城";
	OpenWebPage(url,title);
}


//GPS定位
void CWLRClientDlg::OnBnClickedBtnGpsLocating()
{
	// TODO: Add your control notification handler code here
	string url = WEB_SERVICE_ADDRESS+"/fmp/user.login.action?username=" + svrIO.userInf.loginName
		+ "&password=" + svrIO.userInf.passWord+"&target=gps";
	string title = "GPS定位";
	OpenWebPage(url,title);
}

//功能应用
void CWLRClientDlg::OnBnClickedBtnMyApp()
{
	// TODO: Add your control notification handler code here
	string url = WEB_SERVICE_ADDRESS+"/fmp/user.login.action?username=" + svrIO.userInf.loginName
		+ "&password=" + svrIO.userInf.passWord+"&target=app";
	string title = "功能应用";
	OpenWebPage(url,title);
}

//获得业务开启状态
bool CWLRClientDlg::get_funcs_status( string user_name )
{
		//获取用户收费状态
		string ret = svrIO.check_charge_user( user_name );
		//业务开启状态
		bool is_enabled = false;
		
		if ( "试用" == ret )		{
			is_enabled = true;
		}else if ( "收费" == ret ) {
			is_enabled = true;
		}else if ( "到期" == ret ) {
			is_enabled = false;
		}else if ( "免费" == ret ) {
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
				MessageBox("货源发布成功！");
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
				MessageBox("车源发布成功！");                               
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
				MessageBox("货源发布成功！");
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
				MessageBox("车源发布成功！");                               
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