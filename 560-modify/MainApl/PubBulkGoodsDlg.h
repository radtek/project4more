#pragma once
#include "afxwin.h"

#include "CountryRegion.h"
#include "GLB.h"

// CPubBulkGoodsDlg �Ի���

class CPubBulkGoodsDlg : public CDialog
{
	DECLARE_DYNAMIC(CPubBulkGoodsDlg)

public:
	CPubBulkGoodsDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPubBulkGoodsDlg();

// �Ի�������
	enum { IDD = IDD_PUB_BULKGOODS };

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
	int initSynPoint();
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
    // ��Դ����
    CComboBox combName;
    CString name;
    // ��Դ����
    CString weight;
    // ������λ
    CComboBox combWeightUnit;
    CString weightUnit;
    // ������
    CComboBox combCarType;
    CString carType; 
    // ��ϵ�绰
    CString tel;
    // Ԥ����Ϣ
    CString preview;
    // ͬʱ������ʡ
    CComboBox combSyProvince;
    CString syProvince;
    // ͬʱ��������
    CComboBox combSyCity;
    CString syCity;
    // �ط�����
    CComboBox combRePubType;
    CString rePubType;
    // �Ƿ��ס�ط����á���1����  0����Ĭ��Ϊ0��
    BOOL ifRemRePub;
    // �Ƿ�����Ч����Ĭ�ϣ�24Сʱ��72Сʱ��������Ч��
    BOOL ifLongTime;
    // �Ƿ��ö�����1����  0����Ĭ��Ϊ0��
    BOOL ifUp;
	//�Ƿ�Ԥ��
	BOOL bPreview;
public:
    afx_msg void OnBnClickedPubGoodsPreviewBtn();
    afx_msg void OnCbnSelchangePubGoodsStprovince();
    afx_msg void OnCbnSelchangePubGoodsStcity();
    afx_msg void OnCbnSelchangePubGoodsEnprovince();
    afx_msg void OnCbnSelchangePubGoodsEncity();
    afx_msg void OnCbnSelchangePubGoodsSyprovince();
public:
    virtual BOOL OnInitDialog();
public:
    afx_msg void OnBnClickedOk();
	CEdit m_msgedit;
};
