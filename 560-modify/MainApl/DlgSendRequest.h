#pragma once
#include "ServerIO.h"
#include "afxwin.h"

// CDlgSendRequest 对话框

class CDlgSendRequest : public CDialog
{
	DECLARE_DYNAMIC(CDlgSendRequest)

public:
	CDlgSendRequest(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgSendRequest();

// 对话框数据
	enum { IDD = IDD_MSG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	ServerIO *svrIO;
	CString m_number;
	CString m_strmsg;
	afx_msg void OnBnClickedButton1();
	static DWORD WINAPI ThreadFunc(LPVOID p); //处理搜索功能的线程
	string recordID;//
	virtual BOOL OnInitDialog();
	CEdit m_msgedit;
	afx_msg void OnEnChangeEdit1();
};
