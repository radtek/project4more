#pragma once

#include "GridCtrl_src/GridCtrl.h"

#include "HoverButton.h"

#include "GLB.h"
#include "ServerIO.h"
#include "afxwin.h"

// CTabMyInfDlg �Ի���

class CTabMyInfDlg : public CDialog
{
    DECLARE_EASYSIZE // ��̬�ı�ؼ�λ�ô�С

	DECLARE_DYNAMIC(CTabMyInfDlg)

public:
	CTabMyInfDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTabMyInfDlg();

// �Ի�������
	enum { IDD = IDD_TAB_MY_INF };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// { my define
public:
    // ������ͨ��
    ServerIO *svrIO;
	ServerIO *svrIONew;
public:
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
    /*��������
        type  0:��Դ��
              1:�㵣��
              2:��Դ��
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
    TabMyInfRecord titleData;
    // ����
    vector<TabMyInfRecord> contentData;
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
    int setGrid(vector<TabMyInfRecord> * pcontentData);
    // ��������
    int calRow();

public:
    CGridCtrl m_Grid;
	static DWORD WINAPI ThreadFuncMy(LPVOID p); //�߳�
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
    // ǰҳ
    CHoverButton btnPrev;
public:
    // ��ҳ
    CHoverButton btnNext;
};
