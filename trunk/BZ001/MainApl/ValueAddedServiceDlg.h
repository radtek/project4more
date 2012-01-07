#pragma once


// CValueAddedServiceDlg 对话框

class CValueAddedServiceDlg : public CDialog
{
	DECLARE_DYNAMIC(CValueAddedServiceDlg)

public:
	CValueAddedServiceDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CValueAddedServiceDlg();

// 对话框数据
	enum { IDD = IDD_VALUE_ADDED_SERVICE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedValueAddedServiceIdcard();
public:
    afx_msg void OnBnClickedValueAddedServiceRegistration();
public:
    afx_msg void OnBnClickedValueAddedServiceDrivinglicense();
};
