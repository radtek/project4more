#pragma once
#include "reportctrl.h"
#include "afxcmn.h"
#include "CountryRegion.h"
#include "header.h"
#include "ServerIO.h"
#include "pictureex.h"
// CDlgService �Ի���

class CDlgService : public CXTResizeDialog
{
	DECLARE_DYNAMIC(CDlgService)

public:
	CDlgService(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgService();
	int initTreeCtrl();
	 CountryRegion myCR;

	 LRESULT OnRequest(WPARAM wParam, LPARAM lParam);

	

	 vector<ServiceInfo> input;
	 ServerIO *svrIO;

	 static DWORD WINAPI ThreadFunc(LPVOID p); //�����������ܵ��߳�
	 LONG OnFresh(WPARAM w, LPARAM l);
// �Ի�������
	enum { IDD = IDD_SERVICE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CReportCtrl m_list;
	virtual BOOL OnInitDialog();
	CTreeCtrl mTreeMain;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult);
	CPictureEx m_Picture;
};
