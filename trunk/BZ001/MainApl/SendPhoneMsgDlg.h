#pragma once
#include "MyEdit.h"

// CSendPhoneMsgDlg 对话框

class CSendPhoneMsgDlg : public CDialog
{
	DECLARE_DYNAMIC(CSendPhoneMsgDlg)

public:
	CSendPhoneMsgDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSendPhoneMsgDlg();

// 对话框数据
	enum { IDD = IDD_SEND_PHONEMSG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    // 短信内容
    CString phoneMsg;

    // 手机号码
    CString phoneNumber;
public:
    afx_msg void OnBnClickedOk();
	CMyEdit myedit;
};
