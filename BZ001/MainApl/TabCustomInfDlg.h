#pragma once
#include "afxwin.h"
#include "GridCtrl_src/GridCtrl.h"

#include "HoverButton.h"

#include "GLB.h"
#include "ServerIO.h"

// CTabCustomInfDlg �Ի���

class CTabCustomInfDlg : public CDialog
{
    DECLARE_EASYSIZE // ��̬�ı�ؼ�λ�ô�С

	DECLARE_DYNAMIC(CTabCustomInfDlg)

public:
	CTabCustomInfDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTabCustomInfDlg();

// �Ի�������
	enum { IDD = IDD_TAB_CUSTOM_INF };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// { my define
public:
    // ������ͨ��
    ServerIO *svrIO;
	ServerIO *svrIONew;
	//�Ƿ�ˢ�¶��Ƶ��б�
	BOOL m_bFresh;
	CString m_NewAddGoods;
	CString m_NewAddCars;

	string sphonetext;
	string sphonenum;
public:    
	static DWORD WINAPI ThreadFuncMy(LPVOID p); //�߳�
	LONG OnFresh(WPARAM w, LPARAM l);
    // set grid content font
    int setCridContentFont(SettingFont& font);    
    // ������ʾ�绰����
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
    // ���û�Դ
    int setGoods(int curpage = 1);
    // ���ó�Դ
    int setCars(int curpage = 1);

private:
    // ��ʼ����־
    bool isInit;
    // �Ƿ���ʾ�绰
    bool ifShowPhone;
    // ������Ϣ����(0:��Դ 1:��Դ)
    int curType;
    // ���Ƶ�����Ϣ
    vector<CustomZoneInf> zoneInf;
    // ����
    TabCustomInfRecord titleData;
    // ����
    vector<TabCustomInfRecord> contentData;
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
    int setGrid(vector<TabCustomInfRecord> * pcontentData);
    // ��������
    int calRow();

public:
    CGridCtrl m_Grid;
    // Grid�Ҽ���Ϣ
    afx_msg void OnGridRClick(NMHDR *pNotifyStruct, LRESULT* pResult);
// }

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnSize(UINT nType, int cx, int cy);
public:
    virtual BOOL OnInitDialog();
public:
    // ������Ϣ
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
    // ǰҳ
    CHoverButton btnPrev;
public:
    // ��ҳ
    CHoverButton btnNext;
public:
    // ���Ӷ���
    CHoverButton btnAddCustom;
public:
    // ɾ������
    CHoverButton btnDelCustom;
	afx_msg void OnCbnDropdownTabCustomComb();
	afx_msg void OnCbnCloseupTabCustomComb();
};
