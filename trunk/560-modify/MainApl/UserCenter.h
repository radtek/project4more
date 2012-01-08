#pragma once
#include "embedded_ie_browser.h"
#include <string>

// CUserCenter �Ի���

class CUserCenter : public CDialog
{
	DECLARE_DYNAMIC(CUserCenter)

public:
	CUserCenter(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUserCenter();

	std::string url;

	void GoTo( CString url );
// �Ի�������
	enum { IDD = IDD_USERCENTER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	DECLARE_EVENTSINK_MAP()
	void DocumentCompleteExplorer1(LPDISPATCH pDisp, VARIANT* URL);
	CEmbedded_ie_browser mWebBrowser;
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClose();
	afx_msg void OnBnClickedOk();
};
