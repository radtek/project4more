#pragma once
#include "afxwin.h"

#include "CountryRegion.h"
#include "GLB.h"

// CPubSpecialDlg �Ի���

class CPubSpecialDlg : public CDialog
{
	DECLARE_DYNAMIC(CPubSpecialDlg)

public:
	CPubSpecialDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPubSpecialDlg();

// �Ի�������
	enum { IDD = IDD_PUB_SPECIAL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
// { �Զ���
public:
    // ������Ϣ
    string pubInf;

public:
    // ������Ϣ
    CountryRegion *myCR;
    // �û���Ϣ
    UserInfo userInfo;

private:
	int initStartPoint();
	int initEndPoint();
// } 
public:
    // ������ʡ
    CComboBox combStProvince;
    CString stProvince;
    // ��������
    CComboBox combStCity;
    CString stCity;
    // ��������
    CComboBox combStCounty;
    CString stCounty;
    // Ŀ�ĵ�ʡ
    CComboBox combEnProvince;
    CString enProvince;
    // Ŀ�ĵ���
    CComboBox combEnCity;
    CString enCity;
    // Ŀ�ĵ���
    CComboBox combEnCounty;
    CString enCounty;
    // �ػ��۸�
    CString weightPrice;
    // �ݻ��۸�
    CString lightPrice;
    // ����
    int type;
    // ����
    int transport;
    // ������ʽ
    CComboBox combSend;
    CString send;
    // ��;ʱ��
    int time;
    // ��Ϣ����
    CString information;
    // ��������ϵ��
    CString stName;
    // �����ص�ַ
    CString stAddress;
    // �����ص绰
    CString stTel;
    // Ŀ�ĵ���ϵ��
    CString enName;
    // Ŀ�ĵص�ַ
    CString enAddress;
    // Ŀ�ĵص绰
    CString enTel;
    // �Ƿ��ö�
    BOOL ifUp;
public:
    afx_msg void OnCbnSelchangePubSpecialStprovince();
public:
    afx_msg void OnCbnSelchangePubSpecialStcity();
public:
    afx_msg void OnCbnSelchangePubSpecialEnprovince();
public:
    afx_msg void OnCbnSelchangePubSpecialEncity();
public:
    afx_msg void OnBnClickedOk();
public:
    virtual BOOL OnInitDialog();
	afx_msg void OnEnChangePubSpecialWeightPrice();
};
