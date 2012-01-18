#pragma once

#include "GridCtrl_src/GridCtrl.h"

#include "HoverButton.h"

#include "GLB.h"
#include "ServerIO.h"
#include "afxwin.h"
#include "pictureex.h"
#include "mouserspedit.h"

// CTabSpecialLineDlg 对话框

class CTabSpecialLineDlg : public CDialog
{
    DECLARE_EASYSIZE // 动态改变控件位置大小

	DECLARE_DYNAMIC(CTabSpecialLineDlg)

public:
	CTabSpecialLineDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTabSpecialLineDlg();
	static DWORD WINAPI ThreadFuncZX(LPVOID p); //处理搜索功能的线程
	LONG OnFresh(WPARAM w, LPARAM l);
// 对话框数据
	enum { IDD = IDD_TAB_SPECIAL_LINE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// { my define
public:
    // 服务器通信
    ServerIO *svrIO;
	ServerIO *svrIONew;
    // 搜索条件
    InSearchSpecail specialKeyword;
    // 点击搜索条件
    InClickSearch clickKeyWord;
public:
    // set grid content font
    int setCridContentFont(SettingFont& font);
    // 设置显示电话开关
    int setIfShowPhone(bool ifShow) {
        ifShowPhone = ifShow;
		//try
		{
			return setData(curType, curInput.curpage);;
		}
		//catch (...)
		{

		}
        
    };
    /*设置数据
        type  0:所有专线；
              1:我的专线；
              2:我的收藏；
              3:搜索专线；
              4:点击搜索专线；
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
    TabSpecialLineRecord titleData;
    // 内容
    vector<TabSpecialLineRecord> contentData;
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

    // set this grid title
    int setThisGridTitle(int m_nCols);

    // set this grid content
    int setThisGridContent(int m_nCols,vector<TabSpecialLineRecord> * pcontentData);

    // set grid title and content
    int setGrid(vector<TabSpecialLineRecord> * pcontentData);
        
    // 计算行数
    int calRow();

public:
    enum { MAX_COL_NUM = 20, MIN_ROW_HEIGHT = 28 };  // 表格最大列数

    CGridCtrl m_Grid;
    afx_msg void OnGridRClick(NMHDR *pNotifyStruct, LRESULT* pResult);
	afx_msg void OnGridDBLClick(NMHDR *pNotifyStruct, LRESULT* pResult);
// }

	DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnInitDialog();
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
public:
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnMenuOperationCollect();
    afx_msg void OnMenuOperationDelete();
    afx_msg void OnMenuOperationDelfav();
    afx_msg void OnBnClickedTabSpecialLinePrev();
    afx_msg void OnBnClickedTabSpecialLineNext();
	afx_msg void OnBnClickedButtonLineLocal();
	afx_msg void OnBnClickedButtonLineCancelSearch();
	afx_msg void OnBnClickedButtonLineSecrecy();
	afx_msg void OnBnClickedButtonLineStopRefresh();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
public:
	void GetStartAddr(string& sProvince, string& sCity, string& sCounty)const
	{
		sProvince = m_sStartProvince;
		sCity = m_sStartCity;
		sCounty = m_sStartCounty;
	}
	void SetStartAddr(const string& sProvince, const string& sCity, const string& sCounty, bool bShow)
	{
		m_editStartAddr.SetWindowText(_T(""));

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
		m_editStartAddr.SetWindowText(sAddr.c_str());
	}
	CString GetDestAddr(string& sProvince, string& sCity, string& sCounty)const
	{
		sProvince = m_sDestProvince;
		sCity = m_sDestCity;
		sCounty = m_sDestCounty;
	}
	void SetDestAddr(const string& sProvince, const string& sCity, const string& sCounty, bool bShow)
	{
		m_editDestAddr.SetWindowText(_T(""));
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
		m_editDestAddr.SetWindowText(sAddr.c_str());
	}
	UINT8 GetCurType()const
	{
		return curType;
	}
	void ShowSearchControl(bool bShow);
private:
	CHoverButton btnPrev;
	CHoverButton btnNext;
	
	CHoverButton m_btnLocal;
	CHoverButton m_btnCancelSearch;
	CHoverButton m_btnSecrecy;
	CHoverButton m_btnStopRefresh;
	CMouseRspEdit m_editStartAddr;
	CMouseRspEdit m_editDestAddr;

	CPictureEx m_Picture;

	
	string		  m_sStartProvince;
	string		  m_sStartCity;
	string		  m_sStartCounty;
	string		  m_sDestProvince;
	string		  m_sDestCity;
	string		  m_sDestCounty;
	
public:
	afx_msg void OnPaint();
	void DeleteSpecLine(const TabSpecialLineRecord& content);
	void AddFavorite(const TabSpecialLineRecord& content);
	void RemoveFavorite(const TabSpecialLineRecord& content);
	void ShowDetail(const TabSpecialLineRecord& content);
};
