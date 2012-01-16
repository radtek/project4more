#pragma once

#include "GridCtrl_src/GridCtrl.h"

#include "HoverButton.h"

#include "GLB.h"
#include "ServerIO.h"
#include "afxwin.h"

// CTabMyInfDlg 对话框

class CTabMyInfDlg : public CDialog
{
    DECLARE_EASYSIZE // 动态改变控件位置大小

	DECLARE_DYNAMIC(CTabMyInfDlg)

public:
	CTabMyInfDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTabMyInfDlg();

// 对话框数据
	enum { IDD = IDD_TAB_MY_INF };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// { my define
public:
    // 服务器通信
    ServerIO *svrIO;
	ServerIO *svrIONew;
public:
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
    /*设置数据
        type  0:货源；
              1:零担；
              2:车源；
    */
    int setData(int type, int curpage = 1);

private:
    // 初始化标志
    bool isInit;
    // 是否显示电话
    bool ifShowPhone;
    // 信息类型
    int curType;
    // 标题
    TabMyInfRecord titleData;
    // 内容
    vector<TabMyInfRecord> contentData;
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
    int setGrid(vector<TabMyInfRecord> * pcontentData);
    // 计算行数
    int calRow();

public:
    CGridCtrl m_Grid;
	static DWORD WINAPI ThreadFuncMy(LPVOID p); //线程
	LONG OnFresh(WPARAM w, LPARAM l);
    afx_msg void OnGridRClick(NMHDR *pNotifyStruct, LRESULT* pResult);
	afx_msg void OnGridDBLClick(NMHDR *pNotifyStruct, LRESULT* pResult);
// }

	DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnInitDialog();
public:
    afx_msg void OnSize(UINT nType, int cx, int cy);
public:
    afx_msg void OnMenuOperationDelete();
public:
    afx_msg void OnBnClickedTabMyPrev();
public:
    afx_msg void OnBnClickedTabMyNext();
public:
    // 前页
    CHoverButton btnPrev;
public:
    // 后页
    CHoverButton btnNext;
};
