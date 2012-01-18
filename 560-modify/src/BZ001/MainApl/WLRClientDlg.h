// WLRClientDlg.h : 头文件
//
#pragma once
#include "afxcmn.h"

#include "HoverButton.h"

#include "TabNewInfDlg.h"
#include "TabMyInfDlg.h"
#include "TabCustomInfDlg.h"
#include "TabSpecialLineDlg.h"

#include "ServerIO.h"
#include "CountryRegion.h"

#include "ScrollerCtrl.h"
#include "Config.h"
#include "entabCtrl.h"

#include "afxwin.h"
#include "ProgressDlg.h"
#include "DlgService.h"

class CSearchCriteria;

// CWLRClientDlg 对话框
class CWLRClientDlg : public CDialog
{
    DECLARE_EASYSIZE
// 构造
public:
	CWLRClientDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_WLRCLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	virtual BOOL DestroyWindow();

	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnSize(UINT nType, int cx, int cy);
// { 自定义
public:
    // tab控件显示数据类型
    enum TabType {
        GOODS,     // 货源
        BULKGOODS, // 零担 
        CARS,      // 车源
        LINES,     // 专线
        SEARCH_GOODS,     // 搜索货源
        SEARCH_BULKGOODS, // 搜索零担
        SEARCH_CARS,      // 搜索车源
        SEARCH_SPECIAL,   // 搜索专线
        CLICK_SEARCH_GOODS,      // 点击搜索货源
        CLICK_SEARCH_BULKGOODS,  // 点击搜索零担
        CLICK_SEARCH_CARS,       // 点击搜索车源
        CLICK_SEARCH_SPECIAL,    // 点击搜索专线
    };

public:
	LONG OnFresh(WPARAM w, LPARAM l);
	LONG OnTCGG(WPARAM w, LPARAM l);
	void SetInitColor(ServerIO &svrIO);
    // 货源
    CTabNewInfDlg    newGoodsInf;    // 最新货源
    CTabCustomInfDlg customGoodsInf; // 定制信息
    CTabMyInfDlg     myGoodsInf;     // 我的货源
	CTabNewInfDlg    longGoodsInf;    // 长期货源

	CDlgService service;
    // 设置货源信息
    int setGoodsInf(int tabIndex = 0);
    // 设置点击搜索信息
    int clickSearchGoods(InClickSearch input);

    // 零担
    CTabNewInfDlg  newBulkGoodsInf;  // 最新零担
    CTabMyInfDlg   myBulkGoodsInf;   // 我的零担 
    // 设置零担信息
    int setBulkGoodsInf(int tabIndex = 0);
    // 设置点击搜索信息
    int clickSearchBulkGoods(InClickSearch input);

    // 车源
    CTabNewInfDlg    newCarsInf;     // 最新车源
    CTabCustomInfDlg customCarsInf;  // 定制信息 
    CTabMyInfDlg     myCarsInf;      // 我的车源
	CTabNewInfDlg    longCarsInf;     // 长期车源
    // 设置车源信息
    int setCarsInf(int tabIndex = 0);
    // 设置点击搜索信息
    int clickSearchCars(InClickSearch input);

    // 专线
    CTabSpecialLineDlg allspecialLine;      // 所有专线
    CTabSpecialLineDlg mySpecialLine;       // 我的专线
    CTabSpecialLineDlg favoriteSpecialLine; // 我的收藏
    // 设置专线信息
    int setSpecialLineInf(int tabIndex = 0);
    // 设置点击搜索信息
    int clickSearchSpecialLine(InClickSearch input);

    // 搜索
    CTabNewInfDlg searchGoodsInf;         // 搜索货源
    CTabNewInfDlg searchBulkGoodsInf;     // 搜索零担
    CTabNewInfDlg searchCarsInf;          // 搜索车源
    CTabSpecialLineDlg searchSpecialLine; // 搜索专线

	//option:0，本地；1，取消；2，正常搜索
	void search(UINT8 nType,UINT8 nOption);
    // 设置搜索信息    
    int setSearchGoods(const CSearchCriteria* pSearchCriteria, UINT8 nOption); // 搜索货源
	int setSearchGoods(const string& sSearchCriteria, UINT8 nOption); // 搜索货源
	int setSearchCars(const CSearchCriteria* pSearchCriteria, UINT8 nOption); // 搜索车源
	int setSearchCars(const string& sSearchCriteria, UINT8 nOption); // 搜索车源
	int setSearchSpecail(const InSearchSpecail& input, UINT8 nOption); // 搜索专线    
    int setSearchBulkGoods(const InSearchBulkGoods& input, UINT8 nOption); // 搜索零担
    

    // 用户登录        
    int userLogin(); 

    // 发布
    int pubGoodsInf();       // 发布货源
    int pubBulkGoodsInf();   // 发布零担
    int pubCarsInf();        // 发布车源
    int pubSpecialLineInf(); // 发布专线

    // 系统是否初始化
    bool ifInit;
    // 初始化按钮
    int initButton();
    // 初始化TAB控件
    int initTabCtrl();
    // 初始化Tree控件
    int initTreeCtrl();
    // 隐藏所有的窗口
    int hideAllWindows();
    //
    int ShowTabDlgs();

    // 区域信息
    CountryRegion myCR;

    // 设置tab控件
    //int setTabCtrl();


public:
    // Tab控件变量
    CTabCtrl mTabMain;
    //CEnTabCtrl mTabMain;
    // Tree控件变量
    CTreeCtrl mTreeMain;
	// 获取服务器数据
	ServerIO svrIO;
	ServerIO svrIONew;
	ServerIO svrIOMore;
	ServerIO svrIOMy;
	ServerIO svrIOCustom;
	ServerIO svrIOSpecial;
	ServerIO svrIOService;
	ServerIO svrIOPub;
	// 刷新当前显示
	void refreshShow();
private:

    // 是否显示电话
    bool ifShowPhone;
    // 当前显示的TAB内容
    TabType m_curTabType;
    TabType m_curSearchType;
    // 当前TAB索引
    int m_curTabIndex;
    // 是否自动刷新
    bool ifAutoRefresh;
    // 自动刷新间隔时间
    UINT autoRefreshGap;
    // 检查公告间隔时间
    UINT checkNoticeGap;
    // 背景画刷
    CBrush bgBrush;

	// for chat client 
	CRect rectw;
	BOOL m_dock;


private:
    // 检查更新
    bool checkUpate();

    // 保存设置
    int saveConfig();

    // 加载设置
    int loadConfig();

    // 初始化设置
    int initConfig();
    
    // 切换电话显示
    bool switchShowPhone() {
        if (ifShowPhone) {
            //showPhone.SetWindowTextA("显示电话");
            ifShowPhone = false;
        } else {
            //showPhone.SetWindowTextA("隐藏电话");
            ifShowPhone = true;
        }
        return ifShowPhone;
    };


    // 开启自动刷新定时器
    void startTimer() {
       // SetTimer(AUTO_REFRESH_TIMER_ID, autoRefreshGap, NULL);
        ifAutoRefresh = true;
    };

    // 停止自动刷新定时器
    void stopTimer() {
        KillTimer(AUTO_REFRESH_TIMER_ID);
        ifAutoRefresh = false;
    };

    // 开启广告滚动条
    void startShowAD();

    // 检查公告
    int checkNotice();

	// 开启聊天客户端
	int startChatClient();

	// 向聊天客户端发账号信息
	int sendAcountMsgToChat();

	//定时收取数据
	static DWORD WINAPI  Proc(LPVOID lpVoid);
	static DWORD WINAPI  ProcTimer(LPVOID lpVoid);

	static DWORD WINAPI  ProcCY(LPVOID lpVoid);

	//事件
	HANDLE hEvent;
	HANDLE hEventTimer;
	

	
	HANDLE hThreadMYCY;
	HANDLE hThreadMYHY;
	HANDLE hThreadMYLD;

	BOOL m_break;//用于跳出线程

public:
	// 接收聊天客户端消息
	BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);

//}
public:
    afx_msg void OnTcnSelchangeTabMain(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnBnClickedBtnMainpage();
    afx_msg void OnBnClickedBtnGoods();
    afx_msg void OnBnClickedBtnBulkgoods();
    afx_msg void OnBnClickedBtnCars();
    afx_msg void OnBnClickedBtnLine();
    afx_msg void OnBnClickedBtnSearch();
    afx_msg void OnBnClickedBtnSetting();
    afx_msg void OnBnClickedBtnPayservice();
    afx_msg void OnBnClickedBtnAutoupdate();
    afx_msg void OnBnClickedBtnHidetel();
    //afx_msg void OnBnClickedBtnPub();
    afx_msg void OnTvnSelchangedTreeMain(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg void OnClose();
    afx_msg void OnBnClickedBtnNotice();

    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    
	// 向聊天客户端发位置信息
	afx_msg void OnMove(int x, int y);

	afx_msg void OnBnClickedBtnChat();
	afx_msg void OnBnClickedBtnServer();
	afx_msg void OnBnClickedBtnWlr();
	afx_msg void OnBnClickedCenter();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedBtnReleasegoods();
	afx_msg void OnBnClickedBtnReleasetruckinfo();
	afx_msg void OnBnClickedBtnReleasespecialline();
	afx_msg void OnBnClickedBtnMyaccountant();
	afx_msg void OnBnClickedBtnShoppingMall();
	afx_msg void OnBnClickedBtnGpsLocating();
	afx_msg void OnBnClickedBtnMyApp();

	//xqh:需求对应
	void OpenWebPage(string & url,string &wndTitle);
	//是否 业务：发布货源，车源 开通
	bool is_funcs_enabled;
	//取得业务：发布货源，车源的使用状态
	bool get_funcs_status( string user_name );

private:
	// 货源按钮
	CHoverButton btnGoods;
	// 车源按钮
	CHoverButton btnCars;
	// 专线按钮
	CHoverButton btnSpecial;
	// 发布货源功能按钮
	CHoverButton m_btnReleaseGoods;
	//发布车源
	CHoverButton m_btnReleaseTruckInfo;
	//发布专线
	CHoverButton m_btnReleaseSpecialLine;
	// 拍照按钮
	CHoverButton btnTakePhoto;
	//我的账户
	CHoverButton m_btnMyAccountant;
	//积分商城
	CHoverButton m_btnShoppingMall;
	//功能应用
	CHoverButton m_btnMyApp;
	// 系统设置按钮
	CHoverButton btnSysSetting;
	// 服务站
	CHoverButton m_btnserver;
	// 登录网站
	CHoverButton m_btnwlr;
	//GPS定位
	CHoverButton m_btnGPSLocating;
	// 公告按钮
	CHoverButton btnNotice;

	CHoverButton m_btnPubWayOne;
	CHoverButton m_btnPubWayTwo;

	CScrollerCtrl pubAD;

	COLORREF	m_bgColor;
	COLORREF	m_textColor;

	

	// 增值服务
	//CHoverButton btnAddValued;
	// 自动刷新按钮
	//CHoverButton autoRefresh;
	// 显示电话
	//CHoverButton showPhone;
	// 快速发布按钮
	//CHoverButton btnQuickPub;
	// 聊天按钮
	//CHoverButton btnChat;
	// 零担按钮
	//CHoverButton btnBulkGoods;
	// 搜索按钮
	//CHoverButton btnSearch;
	//用户中心
	//CHoverButton m_btnuser;

	//xqh:add the following code
protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnBnClickedButtonPubWayOne();
	afx_msg void OnBnClickedButtonPubWayTwo();
private:
	void  FillGoodsSearchCriteria(const CSearchCriteria*, InSearchGoods& goodsSearch);
	void  FillCarSearchCriteria(const CSearchCriteria*, InSearchCars& goodsSearch);
};
