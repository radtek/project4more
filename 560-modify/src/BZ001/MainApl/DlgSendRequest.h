#pragma once
#include "ServerIO.h"
#include "afxwin.h"

// CDlgSendRequest �Ի���

class CDlgSendRequest : public CDialog
{
	DECLARE_DYNAMIC(CDlgSendRequest)

public:
	CDlgSendRequest(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgSendRequest();

// �Ի�������
	enum { IDD = IDD_MSG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	ServerIO *svrIO;
	CString m_number;
	CString m_strmsg;
	afx_msg void OnBnClickedButton1();
	static DWORD WINAPI ThreadFunc(LPVOID p); //�����������ܵ��߳�
	string recordID;//
	virtual BOOL OnInitDialog();
	CEdit m_msgedit;
	afx_msg void OnEnChangeEdit1();
};
