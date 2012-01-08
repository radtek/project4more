#pragma once
#include "embedded_ie_browser.h"
#include <string>

// CEmbeddedIeDlg �Ի���

class CEmbeddedIeDlg : public CDialog
{
	DECLARE_DYNAMIC(CEmbeddedIeDlg)

public:
	CEmbeddedIeDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CEmbeddedIeDlg();

// �Ի�������
	enum { IDD = IDD_EMBEDDED_IE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
// { �Զ���
public:
	std::string url;
	BOOL m_flag;
	std::string urll;

	void SetDrump(BOOL bflag,std::string strl);
	void GoTo( CString url );
// }
public:
    // ie�����
    CEmbedded_ie_browser mWebBrowser;
public:
    virtual BOOL OnInitDialog();
public:
    afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_EVENTSINK_MAP()
	void DocumentCompleteEmbeddedIeBrowser(LPDISPATCH pDisp, VARIANT* URL);
	afx_msg void OnClose();
	afx_msg void OnBnClickedOk();
	void NewWindow3EmbeddedIeBrowser(LPDISPATCH* ppDisp, BOOL* Cancel, unsigned long dwFlags, LPCTSTR bstrUrlContext, LPCTSTR bstrUrl);
};
