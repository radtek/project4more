#pragma once
#include "afxwin.h"
#include "GridCtrl_src/GridCtrl.h"

#include "HoverButton.h"

#include "GLB.h"
#include "ServerIO.h"

// CTabCustomInfDlg 对话框

class CTabCustomInfDlg : public CDialog
{
    DECLARE_EASYSIZE // 动态改变控件位置大小

	DECLARE_DYNAMIC(CTabCustomInfDlg)

public:
	CTabCustomInfDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTabCustomInfDlg();

// 对话框数据
	enum { IDD = IDD_TAB_CUSTOM_INF };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// { my define
public:
    // 服务器通信
    ServerIO *svrIO;
	ServerIO *svrIONew;
	//是否刷新定制的列表
	BOOL m_bFresh;
	CString m_NewAddGoods;
	CString m_NewAddCars;

	string sphonetext;
	string sphonenum;
public:    
	static DWORD WINAPI ThreadFuncMy(LPVOID p); //线程
	LONG OnFresh(WPARAM w, LPARAM l);
    // set grid content font
    int setCridContentFont(SettingFont& font);    
    // 设置显示电话开关
    int setIfShowPhone(bool ifShow) {
        ifShowPhone = ifShow;
		//try
		{
			return 0;
		}
		//catch (...)
		{

		}
    };
    // 设置货源
    int setGoods(int curpage = 1);
    // 设置车源
    int setCars(int curpage = 1);

private:
    // 初始化标志
    bool isInit;
    // 是否显示电话
    bool ifShowPhone;
    // 定制信息类型(0:货源 1:车源)
    int curType;
    // 定制地区信息
    vector<CustomZoneInf> zoneInf;
    // 标题
    TabCustomInfRecord titleData;
    // 内容
    vector<TabCustomInfRecord> contentData;
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
    int setGrid(vector<TabCustomInfRecord> * pcontentData);
    // 计算行数
    int calRow();

public:
    CGridCtrl m_Grid;
    // Grid右键消息
    afx_msg void OnGridRClick(NMHDR *pNotifyStruct, LRESULT* pResult);
// }

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnSize(UINT nType, int cx, int cy);
public:
    virtual BOOL OnInitDialog();
public:
    // 定制信息
    CComboBox combCustomInf;
    CString customInf;
public:
    afx_msg void OnCbnSelchangeTabCustomComb();
public:
    afx_msg void OnBnClickedTabCustomAdd();
public:
    afx_msg void OnBnClickedTabCustomDelete();
public:
    afx_msg void OnMenuSendmsgSendmsg();
public:
    afx_msg void OnBnClickedTabCustomPrev();
public:
    afx_msg void OnBnClickedTabCustomNext();
public:
    // 前页
    CHoverButton btnPrev;
public:
    // 后页
    CHoverButton btnNext;
public:
    // 增加定制
    CHoverButton btnAddCustom;
public:
    // 删除定制
    CHoverButton btnDelCustom;
	afx_msg void OnCbnDropdownTabCustomComb();
	afx_msg void OnCbnCloseupTabCustomComb();
};
