#pragma once

#include "GridCtrl_src/GridCtrl.h"

#include "HoverButton.h"

#include "GLB.h"
#include "ServerIO.h"
#include "afxwin.h"
#include "pictureex.h"
#include "PictureEx.h"
#include "MouseRspEdit.h"

//#include "markuplistctrl.h"
// CTabNewInfDlg 对话框
struct MSGCREATE
{
	char cData[1024];
	int fontsize;
	char rgb[20];
};
class CTabNewInfDlg : public CDialog
{
    DECLARE_EASYSIZE // 动态改变控件位置大小

	DECLARE_DYNAMIC(CTabNewInfDlg)

public:
	CTabNewInfDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTabNewInfDlg();
	CArray<MSGCREATE,MSGCREATE> m_msg;
	void AddListItem(LPCTSTR lpszMarkup);
	void SetMsg();


	HANDLE MyThread;
	HANDLE MyEvent;
// 对话框数据
	enum { IDD = IDD_TAB_NEW_INF };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);

// { my define
public:
    // 服务器通信
    ServerIO *svrIO;

	 ServerIO *svrIONew;
    // 搜索条件
	string sSearchCriteria;
    InSearchGoods goodsKeyword;
    InSearchBulkGoods bulkGoodsKeyword;
    InSearchCars carsKeyword;
    // 点击搜索条件
    InClickSearch clickKeyWord;

	static DWORD WINAPI ThreadFuncSS(LPVOID p); //处理搜索功能的线程

	static DWORD WINAPI ProcMore(LPVOID p); //处理搜索功能的线程

	LONG OnFresh(WPARAM w, LPARAM l);
	BOOL m_bStart;//是否开启线程
	BOOL m_bEnd;//关闭窗口
public:
    // set grid content font
    int setCridContentFont(SettingFont& font);
    // 设置显示电话开关
    int setIfShowPhone(bool ifShow) 
	{
        ifShowPhone = ifShow;
		m_btnHidePhoneNum.LoadBitmap(ifShowPhone?IDB_HIDE_PHONE_NUM:IDB_SHOWPHONE);
		return setData(curType, curInput.curpage);
    }
	
    /*设置数据
        type  0:货源；
              1:零担；
              2:车源；
              3:搜索货源；
              4:搜索零担；
              5:搜索车源；
              6:点击搜索货源；
              7:点击搜索零担；
              8:点击搜索车源
        curpage -1: 保留当前curpage
    */
    int setData(int type, int curpage = 1);
	string sphonetext;
	string sphonenum;
private:
    // 初始化标志
    bool isInit;
    // 是否显示电话
    bool ifShowPhone;
    // 信息类型
    int curType;
    // 标题
    TabNewInfRecord titleData;
    // 内容
    vector<TabNewInfRecord> contentData;
    // 标题字体
    LOGFONT titleFont;
    // 内容字体
    LOGFONT contentFont;
    // 输入参数信息
    inputParam curInput;
    // 当前选择的行
    int curSelRow;
    // 最大页数
    int maxPageNum;
private:
    // 初始化表格
    int initGrid();
    // set grid title and content
    int setGrid(vector<TabNewInfRecord> *pcontentData);
    // 计算行数
    int calRow();

public:
    CGridCtrl m_Grid;
	afx_msg void OnGridDBLClick(NMHDR *pNotifyStruct, LRESULT* pResult);
    afx_msg void OnGridRClick(NMHDR *pNotifyStruct, LRESULT* pResult);
// }

	DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnInitDialog();
public:
    afx_msg void OnSize(UINT nType, int cx, int cy);
public:
    afx_msg void OnMenuSendmsgSendmsg();
public:
    afx_msg void OnBnClickedTabNewPrev();
public:
    afx_msg void OnBnClickedTabNewNext();
public:

	afx_msg void OnTimer(UINT_PTR nIDEvent);
public:
	afx_msg void OnPaint();
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	/*afx_msg void OnBnClickedButtonLocal();
	afx_msg void OnBnClickedButtonCancelSearch();
	afx_msg void OnBnClickedButtonSecrecy();
	afx_msg void OnBnClickedButtonStopRefresh();*/

	afx_msg void OnBnClickedButtonSearch();
	afx_msg void OnBnClickedButtonStopRefresh();
	afx_msg void OnBnClickedButtonHidePhoneNum();
public:
	void SendSMS(const TabNewInfRecord& content);
public:
	void GetStartAddr(string& sProvince, string& sCity, string& sCounty)const
	{
		sProvince = m_sStartProvince;
		sCity = m_sStartCity;
		sCounty = m_sStartCounty;
	}
	void SetStartAddr(const string& sProvince, const string& sCity, const string& sCounty, bool bShow)
	{
	//	m_editStartAddr.SetWindowText(_T(""));

		m_sStartProvince = sProvince;
		m_sStartCity = sCity;
		m_sStartCounty = sCounty;
		if( !bShow )
		{
			return ;
		}
		string sAddr(sProvince);
		if( sCity != sProvince && sCity != "不限" )
		{
			sAddr += "+"+sCity;
		}
		if( !sCounty.empty() && sCounty != "不限" )
		{
			sAddr += "+"+sCounty;
		}
	//	m_editStartAddr.SetWindowText(sAddr.c_str());
	}
	CString GetDestAddr(string& sProvince, string& sCity, string& sCounty)const
	{
		sProvince = m_sDestProvince;
		sCity = m_sDestCity;
		sCounty = m_sDestCounty;
	}
	void SetDestAddr(const string& sProvince, const string& sCity, const string& sCounty, bool bShow)
	{
		//m_editDestAddr.SetWindowText(_T(""));

		m_sDestProvince = sProvince;
		m_sDestCity = sCity;
		m_sDestCounty = sCounty;

		if( !bShow )
		{
			return ;
		}
		string sAddr(sProvince);
		if( sCity != sProvince && sCity != "不限" )
		{
			sAddr += "+"+sCity;
		}
		if( !sCounty.empty() && sCounty != "不限" )
		{
			sAddr += "+"+sCounty;
		}
		//m_editDestAddr.SetWindowText(sAddr.c_str());
	}
	UINT8 GetCurType()const
	{
		return curType;
	}

	void SetSearchType(int nType)
	{
		m_nSearchType = nType;
	}

	void SetLongTimeFlag(bool bLongTime)
	{
		m_bLongTimeInfo = bLongTime;
	}
	void SetSearchTabFlag(bool bSearchTab)
	{
		m_bSearchTab = bSearchTab;
	}


private:
	void ShowDetailInfo(const TabNewInfRecord* pContent);

private:
	// 前页
	CHoverButton btnPrev;
	// 后页
	CHoverButton btnNext;
	CHoverButton m_btnTopPage;
	CHoverButton m_btnBottomPage;
	CHoverButton m_btnSearch;
	CHoverButton m_btnStopRefresh;
	CHoverButton m_btnHidePhoneNum;
	CHoverButton m_btnPubWayOne;
	CHoverButton m_btnPubWayTwo;
	CHoverButton m_btnClose;
	//CPictureEx m_Picture;
	CPictureEx m_Picture;

	//CHoverButton m_btnLocal;
	//CHoverButton m_btnCancelSearch;
	//CHoverButton m_btnSecrecy;
	//CHoverButton m_btnStopRefresh;

	//CMouseRspEdit m_editStartAddr;
	//CMouseRspEdit m_editDestAddr;
	string		  m_sStartProvince;
	string		  m_sStartCity;
	string		  m_sStartCounty;
	string		  m_sDestProvince;
	string		  m_sDestCity;
	string		  m_sDestCounty;
	int			  m_nSearchType;

	bool		  m_bLongTimeInfo;
	bool		  m_bAutoRefresh;
	bool		  m_bSearchTab;
public:
	afx_msg void OnBnClickedButtonPubWayOne();
	afx_msg void OnBnClickedButtonPubWayTwo();
	afx_msg void OnBnClickedTabNewUptop();
	afx_msg void OnBnClickedTabNewBottomDown();
	afx_msg void OnBnClickedButtonSearchClose();
};
