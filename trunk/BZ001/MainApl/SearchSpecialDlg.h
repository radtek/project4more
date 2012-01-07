#pragma once

#include "CountryRegion.h"

// CSearchSpecialDlg �Ի���

class CSearchSpecialDlg : public CDialog
{
	DECLARE_DYNAMIC(CSearchSpecialDlg)

public:
	CSearchSpecialDlg(CWnd* pParent = NULL);   // ��׼���캯��  
	virtual ~CSearchSpecialDlg();

// �Ի�������
	enum { IDD = IDD_SEARCH_SPECIAL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
// { �Զ���
public:
    // ������Ϣ
    CountryRegion *myCR;
private:    
    // ��ʼ��������
	int initStartPoint();
    // ��ʼ�������
	int initEndPoint();
// }
public:
    // ����ʡ
    CComboBox startProvince;
    CString strStartProvince;
    // ������
    CComboBox startCity;
    CString strStartCity;
    // ������
    CComboBox startCounty;
    CString strStartCounty;
    // ����ʡ
    CComboBox endProvince;
    CString strEndProvince;
    // ������
    CComboBox endCity;
    CString strEndCity;
    // ������
    CComboBox endCounty;
    CString strEndCounty;

public:
    virtual BOOL OnInitDialog();
public:
    afx_msg void OnCbnSelchangeStartProvince();
    afx_msg void OnCbnSelchangeStartCity();
    afx_msg void OnCbnSelchangeEndProvince();
    afx_msg void OnCbnSelchangeEndCity();

    
public:
    afx_msg void OnBnClickedOk();
};
