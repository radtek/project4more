// WLRClientDlg.h : ͷ�ļ�
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

// CWLRClientDlg �Ի���
class CWLRClientDlg : public CDialog
{
    DECLARE_EASYSIZE
// ����
public:
	CWLRClientDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_WLRCLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	virtual BOOL DestroyWindow();

	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnSize(UINT nType, int cx, int cy);
// { �Զ���
public:
    // tab�ؼ���ʾ��������
    enum TabType {
        GOODS,     // ��Դ
        BULKGOODS, // �㵣 
        CARS,      // ��Դ
        LINES,     // ר��
        SEARCH_GOODS,     // ������Դ
        SEARCH_BULKGOODS, // �����㵣
        SEARCH_CARS,      // ������Դ
        SEARCH_SPECIAL,   // ����ר��
        CLICK_SEARCH_GOODS,      // ���������Դ
        CLICK_SEARCH_BULKGOODS,  // ��������㵣
        CLICK_SEARCH_CARS,       // ���������Դ
        CLICK_SEARCH_SPECIAL,    // �������ר��
    };

public:
	LONG OnFresh(WPARAM w, LPARAM l);
	LONG OnTCGG(WPARAM w, LPARAM l);
	void SetInitColor(ServerIO &svrIO);
    // ��Դ
    CTabNewInfDlg    newGoodsInf;    // ���»�Դ
    CTabCustomInfDlg customGoodsInf; // ������Ϣ
    CTabMyInfDlg     myGoodsInf;     // �ҵĻ�Դ
	CTabNewInfDlg    longGoodsInf;    // ���ڻ�Դ

	CDlgService service;
    // ���û�Դ��Ϣ
    int setGoodsInf(int tabIndex = 0);
    // ���õ��������Ϣ
    int clickSearchGoods(InClickSearch input);

    // �㵣
    CTabNewInfDlg  newBulkGoodsInf;  // �����㵣
    CTabMyInfDlg   myBulkGoodsInf;   // �ҵ��㵣 
    // �����㵣��Ϣ
    int setBulkGoodsInf(int tabIndex = 0);
    // ���õ��������Ϣ
    int clickSearchBulkGoods(InClickSearch input);

    // ��Դ
    CTabNewInfDlg    newCarsInf;     // ���³�Դ
    CTabCustomInfDlg customCarsInf;  // ������Ϣ 
    CTabMyInfDlg     myCarsInf;      // �ҵĳ�Դ
	CTabNewInfDlg    longCarsInf;     // ���ڳ�Դ
    // ���ó�Դ��Ϣ
    int setCarsInf(int tabIndex = 0);
    // ���õ��������Ϣ
    int clickSearchCars(InClickSearch input);

    // ר��
    CTabSpecialLineDlg allspecialLine;      // ����ר��
    CTabSpecialLineDlg mySpecialLine;       // �ҵ�ר��
    CTabSpecialLineDlg favoriteSpecialLine; // �ҵ��ղ�
    // ����ר����Ϣ
    int setSpecialLineInf(int tabIndex = 0);
    // ���õ��������Ϣ
    int clickSearchSpecialLine(InClickSearch input);

    // ����
    CTabNewInfDlg searchGoodsInf;         // ������Դ
    CTabNewInfDlg searchBulkGoodsInf;     // �����㵣
    CTabNewInfDlg searchCarsInf;          // ������Դ
    CTabSpecialLineDlg searchSpecialLine; // ����ר��

	//option:0�����أ�1��ȡ����2����������
	void search(UINT8 nType,UINT8 nOption);
    // ����������Ϣ    
    int setSearchGoods(const CSearchCriteria* pSearchCriteria, UINT8 nOption); // ������Դ
	int setSearchGoods(const string& sSearchCriteria, UINT8 nOption); // ������Դ
	int setSearchCars(const CSearchCriteria* pSearchCriteria, UINT8 nOption); // ������Դ
	int setSearchCars(const string& sSearchCriteria, UINT8 nOption); // ������Դ
	int setSearchSpecail(const InSearchSpecail& input, UINT8 nOption); // ����ר��    
    int setSearchBulkGoods(const InSearchBulkGoods& input, UINT8 nOption); // �����㵣
    

    // �û���¼        
    int userLogin(); 

    // ����
    int pubGoodsInf();       // ������Դ
    int pubBulkGoodsInf();   // �����㵣
    int pubCarsInf();        // ������Դ
    int pubSpecialLineInf(); // ����ר��

    // ϵͳ�Ƿ��ʼ��
    bool ifInit;
    // ��ʼ����ť
    int initButton();
    // ��ʼ��TAB�ؼ�
    int initTabCtrl();
    // ��ʼ��Tree�ؼ�
    int initTreeCtrl();
    // �������еĴ���
    int hideAllWindows();
    //
    int ShowTabDlgs();

    // ������Ϣ
    CountryRegion myCR;

    // ����tab�ؼ�
    //int setTabCtrl();


public:
    // Tab�ؼ�����
    CTabCtrl mTabMain;
    //CEnTabCtrl mTabMain;
    // Tree�ؼ�����
    CTreeCtrl mTreeMain;
	// ��ȡ����������
	ServerIO svrIO;
	ServerIO svrIONew;
	ServerIO svrIOMore;
	ServerIO svrIOMy;
	ServerIO svrIOCustom;
	ServerIO svrIOSpecial;
	ServerIO svrIOService;
	ServerIO svrIOPub;
	// ˢ�µ�ǰ��ʾ
	void refreshShow();
private:

    // �Ƿ���ʾ�绰
    bool ifShowPhone;
    // ��ǰ��ʾ��TAB����
    TabType m_curTabType;
    TabType m_curSearchType;
    // ��ǰTAB����
    int m_curTabIndex;
    // �Ƿ��Զ�ˢ��
    bool ifAutoRefresh;
    // �Զ�ˢ�¼��ʱ��
    UINT autoRefreshGap;
    // ��鹫����ʱ��
    UINT checkNoticeGap;
    // ������ˢ
    CBrush bgBrush;

	// for chat client 
	CRect rectw;
	BOOL m_dock;


private:
    // ������
    bool checkUpate();

    // ��������
    int saveConfig();

    // ��������
    int loadConfig();

    // ��ʼ������
    int initConfig();
    
    // �л��绰��ʾ
    bool switchShowPhone() {
        if (ifShowPhone) {
            //showPhone.SetWindowTextA("��ʾ�绰");
            ifShowPhone = false;
        } else {
            //showPhone.SetWindowTextA("���ص绰");
            ifShowPhone = true;
        }
        return ifShowPhone;
    };


    // �����Զ�ˢ�¶�ʱ��
    void startTimer() {
       // SetTimer(AUTO_REFRESH_TIMER_ID, autoRefreshGap, NULL);
        ifAutoRefresh = true;
    };

    // ֹͣ�Զ�ˢ�¶�ʱ��
    void stopTimer() {
        KillTimer(AUTO_REFRESH_TIMER_ID);
        ifAutoRefresh = false;
    };

    // ������������
    void startShowAD();

    // ��鹫��
    int checkNotice();

	// ��������ͻ���
	int startChatClient();

	// ������ͻ��˷��˺���Ϣ
	int sendAcountMsgToChat();

	//��ʱ��ȡ����
	static DWORD WINAPI  Proc(LPVOID lpVoid);
	static DWORD WINAPI  ProcTimer(LPVOID lpVoid);

	static DWORD WINAPI  ProcCY(LPVOID lpVoid);

	//�¼�
	HANDLE hEvent;
	HANDLE hEventTimer;
	

	
	HANDLE hThreadMYCY;
	HANDLE hThreadMYHY;
	HANDLE hThreadMYLD;

	BOOL m_break;//���������߳�

public:
	// ��������ͻ�����Ϣ
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
    
	// ������ͻ��˷�λ����Ϣ
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

	//xqh:�����Ӧ
	void OpenWebPage(string & url,string &wndTitle);
	//�Ƿ� ҵ�񣺷�����Դ����Դ ��ͨ
	bool is_funcs_enabled;
	//ȡ��ҵ�񣺷�����Դ����Դ��ʹ��״̬
	bool get_funcs_status( string user_name );

private:
	// ��Դ��ť
	CHoverButton btnGoods;
	// ��Դ��ť
	CHoverButton btnCars;
	// ר�߰�ť
	CHoverButton btnSpecial;
	// ������Դ���ܰ�ť
	CHoverButton m_btnReleaseGoods;
	//������Դ
	CHoverButton m_btnReleaseTruckInfo;
	//����ר��
	CHoverButton m_btnReleaseSpecialLine;
	// ���հ�ť
	CHoverButton btnTakePhoto;
	//�ҵ��˻�
	CHoverButton m_btnMyAccountant;
	//�����̳�
	CHoverButton m_btnShoppingMall;
	//����Ӧ��
	CHoverButton m_btnMyApp;
	// ϵͳ���ð�ť
	CHoverButton btnSysSetting;
	// ����վ
	CHoverButton m_btnserver;
	// ��¼��վ
	CHoverButton m_btnwlr;
	//GPS��λ
	CHoverButton m_btnGPSLocating;
	// ���水ť
	CHoverButton btnNotice;

	CHoverButton m_btnPubWayOne;
	CHoverButton m_btnPubWayTwo;

	CScrollerCtrl pubAD;

	COLORREF	m_bgColor;
	COLORREF	m_textColor;

	

	// ��ֵ����
	//CHoverButton btnAddValued;
	// �Զ�ˢ�°�ť
	//CHoverButton autoRefresh;
	// ��ʾ�绰
	//CHoverButton showPhone;
	// ���ٷ�����ť
	//CHoverButton btnQuickPub;
	// ���찴ť
	//CHoverButton btnChat;
	// �㵣��ť
	//CHoverButton btnBulkGoods;
	// ������ť
	//CHoverButton btnSearch;
	//�û�����
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
