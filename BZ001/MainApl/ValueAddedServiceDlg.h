#pragma once


// CValueAddedServiceDlg �Ի���

class CValueAddedServiceDlg : public CDialog
{
	DECLARE_DYNAMIC(CValueAddedServiceDlg)

public:
	CValueAddedServiceDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CValueAddedServiceDlg();

// �Ի�������
	enum { IDD = IDD_VALUE_ADDED_SERVICE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedValueAddedServiceIdcard();
public:
    afx_msg void OnBnClickedValueAddedServiceRegistration();
public:
    afx_msg void OnBnClickedValueAddedServiceDrivinglicense();
};
