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
// CTabNewInfDlg �Ի���
struct MSGCREATE
{
	char cData[1024];
	int fontsize;
	char rgb[20];
};
class CTabNewInfDlg : public CDialog
{
    DECLARE_EASYSIZE // ��̬�ı�ؼ�λ�ô�С

	DECLARE_DYNAMIC(CTabNewInfDlg)

public:
	CTabNewInfDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTabNewInfDlg();
	CArray<MSGCREATE,MSGCREATE> m_msg;
	void AddListItem(LPCTSTR lpszMarkup);
	void SetMsg();


	HANDLE MyThread;
	HANDLE MyEvent;
// �Ի�������
	enum { IDD = IDD_TAB_NEW_INF };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);

// { my define
public:
    // ������ͨ��
    ServerIO *svrIO;

	 ServerIO *svrIONew;
    // ��������
	string sSearchCriteria;
    InSearchGoods goodsKeyword;
    InSearchBulkGoods bulkGoodsKeyword;
    InSearchCars carsKeyword;
    // �����������
    InClickSearch clickKeyWord;

	static DWORD WINAPI ThreadFuncSS(LPVOID p); //�����������ܵ��߳�

	static DWORD WINAPI ProcMore(LPVOID p); //�����������ܵ��߳�

	LONG OnFresh(WPARAM w, LPARAM l);
	BOOL m_bStart;//�Ƿ����߳�
	BOOL m_bEnd;//�رմ���
public:
    // set grid content font
    int setCridContentFont(SettingFont& font);
    // ������ʾ�绰����
    int setIfShowPhone(bool ifShow) 
	{
        ifShowPhone = ifShow;
		m_btnHidePhoneNum.LoadBitmap(ifShowPhone?IDB_HIDE_PHONE_NUM:IDB_SHOWPHONE);
		return setData(curType, curInput.curpage);
    }
	
    /*��������
        type  0:��Դ��
              1:�㵣��
              2:��Դ��
              3:������Դ��
              4:�����㵣��
              5:������Դ��
              6:���������Դ��
              7:��������㵣��
              8:���������Դ
        curpage -1: ������ǰcurpage
    */
    int setData(int type, int curpage = 1);
	string sphonetext;
	string sphonenum;
private:
    // ��ʼ����־
    bool isInit;
    // �Ƿ���ʾ�绰
    bool ifShowPhone;
    // ��Ϣ����
    int curType;
    // ����
    TabNewInfRecord titleData;
    // ����
    vector<TabNewInfRecord> contentData;
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
    // set grid title and content
    int setGrid(vector<TabNewInfRecord> *pcontentData);
    // ��������
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
		if( sCity != sProvince && sCity != "����" )
		{
			sAddr += "+"+sCity;
		}
		if( !sCounty.empty() && sCounty != "����" )
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
		if( sCity != sProvince && sCity != "����" )
		{
			sAddr += "+"+sCity;
		}
		if( !sCounty.empty() && sCounty != "����" )
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
	// ǰҳ
	CHoverButton btnPrev;
	// ��ҳ
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
