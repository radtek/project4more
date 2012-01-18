#pragma once

#include "GridCtrl_src/GridCtrl.h"

#include "HoverButton.h"

#include "GLB.h"
#include "ServerIO.h"
#include "afxwin.h"
#include "pictureex.h"
#include "mouserspedit.h"

// CTabSpecialLineDlg �Ի���

class CTabSpecialLineDlg : public CDialog
{
    DECLARE_EASYSIZE // ��̬�ı�ؼ�λ�ô�С

	DECLARE_DYNAMIC(CTabSpecialLineDlg)

public:
	CTabSpecialLineDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTabSpecialLineDlg();
	static DWORD WINAPI ThreadFuncZX(LPVOID p); //�����������ܵ��߳�
	LONG OnFresh(WPARAM w, LPARAM l);
// �Ի�������
	enum { IDD = IDD_TAB_SPECIAL_LINE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// { my define
public:
    // ������ͨ��
    ServerIO *svrIO;
	ServerIO *svrIONew;
    // ��������
    InSearchSpecail specialKeyword;
    // �����������
    InClickSearch clickKeyWord;
public:
    // set grid content font
    int setCridContentFont(SettingFont& font);
    // ������ʾ�绰����
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
    /*��������
        type  0:����ר�ߣ�
              1:�ҵ�ר�ߣ�
              2:�ҵ��ղأ�
              3:����ר�ߣ�
              4:�������ר�ߣ�
    */
    int setData(int type, int curpage = 1);

private:
    // ��ʼ����־
    bool isInit;
    // �Ƿ���ʾ�绰
    bool ifShowPhone;
    // ��Ϣ����
    int curType;
    // ����
    TabSpecialLineRecord titleData;
    // ����
    vector<TabSpecialLineRecord> contentData;
    // ��������
    LOGFONT titleFont;
    // ��������
    LOGFONT contentFont;
    // ���������Ϣ
    inputParam curInput;
    // ��ǰѡ�����
    int curSelRow;
    // ���ҳ��
    int maxPageNum;
private:
    // ��ʼ�����
    int initGrid();

    // set this grid title
    int setThisGridTitle(int m_nCols);

    // set this grid content
    int setThisGridContent(int m_nCols,vector<TabSpecialLineRecord> * pcontentData);

    // set grid title and content
    int setGrid(vector<TabSpecialLineRecord> * pcontentData);
        
    // ��������
    int calRow();

public:
    enum { MAX_COL_NUM = 20, MIN_ROW_HEIGHT = 28 };  // ����������

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
		if( sCity != sProvince && sCity != "����" )
		{
			sAddr += "+"+sCity;
		}
		if( !sCounty.empty() && sCounty != "����" )
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
		if( sCity != sProvince && sCity != "����" )
		{
			sAddr += "+"+sCity;
		}
		if( !sCounty.empty() && sCounty != "����" )
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
