#pragma once
#include "afxwin.h"

#include "CountryRegion.h"
#include "GLB.h"

// CPubCarsDlg �Ի���

class CPubCarsDlg : public CDialog
{
	DECLARE_DYNAMIC(CPubCarsDlg)

public:
	CPubCarsDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPubCarsDlg();

// �Ի�������
	enum { IDD = IDD_PUB_CARS };

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
	//int initSynPoint();
// }   

public:
    // ������ʡ
    CComboBox combStProvince;
    CString stProvince;
    // ��������
    CComboBox combStCity;
    CString stCity;
    // ��������/��
    CComboBox combStCounty;
    CString stCounty;
    // Ŀ�ĵ�ʡ
    CComboBox combEnProvince;
    CString enProvince;
    // Ŀ�ĵ���
    CComboBox combEnCity;
    CString enCity;
    // Ŀ�ĵ���/��
    CComboBox combEnCounty;
    CString enCounty;
    // Ŀ�ĵ�ʡ2
    CComboBox combEnProvince2;
    CString enProvince2;
    // Ŀ�ĵ���2
    CComboBox combEnCity2;
    CString enCity2;
    // Ŀ�ĵ���/��2
    CComboBox combEnCounty2;
    CString enCounty2;
    // Ŀ�ĵ�ʡ3
    CComboBox combEnProvince3;
    CString enProvince3;
    // Ŀ�ĵ���3
    CComboBox combEnCity3;
    CString enCity3;
    // Ŀ�ĵ���/��3
    CComboBox combEnCounty3;
    CString enCounty3;
    // ��Դ����
    CComboBox combName;
    CString name;
    // ������
    CString weight;
	// ������
	CString cubage;
    // ��Դ����
    CComboBox combType;
    CString type;
    // ����
    CComboBox combCarLength;
    CString carLength;
    // ������
    CComboBox combCarType;
    CString carType;
    // �賵����
    CString carNum;
    // ��ϵ�绰
    CString tel;
    // Ԥ����Ϣ
    CString preview;
    // ͬʱ������ʡ
    //CComboBox combSyProvince;
    //CString syProvince;
    // ͬʱ��������
    //CComboBox combSyCity;
    //CString syCity;
    // ����ʱ��
    CComboBox combLdgTime;
    CString ldgTime;
    // �ط�����
    CComboBox combRePubType;
    CString rePubType;
    // �Ƿ��ס�ط����á���1����  0����Ĭ��Ϊ0��
    BOOL ifRemRePub;
    // �Ƿ�����Ч����Ĭ�ϣ�24Сʱ��72Сʱ��������Ч��
    BOOL ifLongTime;
    // �Ƿ��ö�����1����  0����Ĭ��Ϊ0��
    //BOOL ifUp;
	//�Ƿ�Ԥ��
	BOOL bPreview;
public:
    afx_msg void OnBnClickedPubGoodsPreviewBtn();
    afx_msg void OnCbnSelchangePubGoodsStprovince();
    afx_msg void OnCbnSelchangePubGoodsStcity();
    afx_msg void OnCbnSelchangePubGoodsEnprovince();
    afx_msg void OnCbnSelchangePubGoodsEncity();
    afx_msg void OnCbnSelchangePubGoodsEnprovince2();
    afx_msg void OnCbnSelchangePubGoodsEncity2();
    afx_msg void OnCbnSelchangePubGoodsEnprovince3();
    afx_msg void OnCbnSelchangePubGoodsEncity3();
    //afx_msg void OnCbnSelchangePubGoodsSyprovince();
public:
    virtual BOOL OnInitDialog();
public:
    afx_msg void OnBnClickedOk();
public:

	CEdit m_msgedit;
};
