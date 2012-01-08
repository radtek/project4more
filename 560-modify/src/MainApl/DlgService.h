#pragma once
#include "reportctrl.h"
#include "afxcmn.h"
#include "CountryRegion.h"
#include "header.h"
#include "ServerIO.h"
#include "pictureex.h"
// CDlgService 对话框

class CDlgService : public CXTResizeDialog
{
	DECLARE_DYNAMIC(CDlgService)

public:
	CDlgService(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgService();
	int initTreeCtrl();
	 CountryRegion myCR;

	 LRESULT OnRequest(WPARAM wParam, LPARAM lParam);

	

	 vector<ServiceInfo> input;
	 ServerIO *svrIO;

	 static DWORD WINAPI ThreadFunc(LPVOID p); //处理搜索功能的线程
	 LONG OnFresh(WPARAM w, LPARAM l);
// 对话框数据
	enum { IDD = IDD_SERVICE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CReportCtrl m_list;
	virtual BOOL OnInitDialog();
	CTreeCtrl mTreeMain;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult);
	CPictureEx m_Picture;
};
