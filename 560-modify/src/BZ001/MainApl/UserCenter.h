#pragma once
#include "embedded_ie_browser.h"
#include <string>

// CUserCenter 对话框

class CUserCenter : public CDialog
{
	DECLARE_DYNAMIC(CUserCenter)

public:
	CUserCenter(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUserCenter();

	std::string url;

	void GoTo( CString url );
// 对话框数据
	enum { IDD = IDD_USERCENTER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
