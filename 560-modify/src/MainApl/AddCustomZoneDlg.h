#pragma once

#include "CountryRegion.h"

// CAddCustomZoneDlg �Ի���

class CAddCustomZoneDlg : public CDialog
{
	DECLARE_DYNAMIC(CAddCustomZoneDlg)

public:
	CAddCustomZoneDlg(CWnd* pParent = NULL);   // ��׼���캯��  
	virtual ~CAddCustomZoneDlg();

// �Ի�������
	enum { IDD = IDD_ADD_CUSTOM_ZONE };

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
    // ����ʡ
    CComboBox endProvince;
    CString strEndProvince;
    // ������
    CComboBox endCity;
    CString strEndCity;

public:
    virtual BOOL OnInitDialog();
public:
    afx_msg void OnCbnSelchangeStartProvince();
    afx_msg void OnCbnSelchangeEndProvince();
    
public:
    afx_msg void OnBnClickedOk();
};