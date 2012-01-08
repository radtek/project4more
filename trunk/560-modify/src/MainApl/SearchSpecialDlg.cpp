// SearchSpecialDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WLRClient.h"
#include "SearchSpecialDlg.h"


// CSearchSpecialDlg �Ի���

IMPLEMENT_DYNAMIC(CSearchSpecialDlg, CDialog)

CSearchSpecialDlg::CSearchSpecialDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSearchSpecialDlg::IDD, pParent)
    , strStartProvince(_T(""))
    , strStartCity(_T(""))
    , strStartCounty(_T(""))
    , strEndProvince(_T(""))
    , strEndCity(_T(""))
    , strEndCounty(_T(""))
{
    myCR = NULL;
}

CSearchSpecialDlg::~CSearchSpecialDlg()
{
}
    
//
void CSearchSpecialDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_START_PROVINCE, startProvince);
    DDX_Control(pDX, IDC_START_CITY, startCity);
    DDX_Control(pDX, IDC_START_COUNTY, startCounty);
    DDX_Control(pDX, IDC_END_PROVINCE, endProvince);
    DDX_Control(pDX, IDC_END_CITY, endCity);
    DDX_Control(pDX, IDC_END_COUNTY, endCounty);
    DDX_CBString(pDX, IDC_START_PROVINCE, strStartProvince);
    DDX_CBString(pDX, IDC_START_CITY, strStartCity);
    DDX_CBString(pDX, IDC_START_COUNTY, strStartCounty);
    DDX_CBString(pDX, IDC_END_PROVINCE, strEndProvince);
    DDX_CBString(pDX, IDC_END_CITY, strEndCity);
    DDX_CBString(pDX, IDC_END_COUNTY, strEndCounty);
}


BEGIN_MESSAGE_MAP(CSearchSpecialDlg, CDialog)
    ON_CBN_SELCHANGE(IDC_START_PROVINCE, &CSearchSpecialDlg::OnCbnSelchangeStartProvince)
    ON_CBN_SELCHANGE(IDC_START_CITY, &CSearchSpecialDlg::OnCbnSelchangeStartCity)
    ON_CBN_SELCHANGE(IDC_END_PROVINCE, &CSearchSpecialDlg::OnCbnSelchangeEndProvince)
    ON_CBN_SELCHANGE(IDC_END_CITY, &CSearchSpecialDlg::OnCbnSelchangeEndCity)
    ON_BN_CLICKED(IDOK, &CSearchSpecialDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CSearchSpecialDlg ��Ϣ�������

BOOL CSearchSpecialDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  �ڴ���Ӷ���ĳ�ʼ��
    // ��ʼ��������
	if (-1 == initStartPoint()) {
        return false;
    }
    // ��ʼ�������
    if (-1 == initEndPoint()) {
        return false;
    } 

    return TRUE;  // return TRUE unless you set the focus to a control
    // �쳣: OCX ����ҳӦ���� FALSE
}
    
// ��ʼ��������
int CSearchSpecialDlg::initStartPoint()
{
    if (myCR == NULL) {
        return -1;
    }

    vector<Province>::iterator iter = myCR->govProvince.begin();
    while (iter != myCR->govProvince.end()) {
		startProvince.AddString((*iter).name.c_str());
        ++iter;
    }
    return 0;
}
    
// ��ʼ�������
int CSearchSpecialDlg::initEndPoint()
{
    if (myCR == NULL) {
        return -1;
    }

    vector<Province>::iterator iter = myCR->govProvince.begin();
    while (iter != myCR->govProvince.end()) {
		endProvince.AddString((*iter).name.c_str());
        ++iter;
    }
    return 0;
}

// ��Ӧ����ʡ�б������Ϣ
void CSearchSpecialDlg::OnCbnSelchangeStartProvince()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    int index = startProvince.GetCurSel();

	// Delete every other item from the combo box.
	while (startCity.GetCount() > 0) {
		startCity.DeleteString( 0 );
	}

	vector<City>::iterator iter = myCR->govProvince.at(index).govCity.begin();
	while (iter != myCR->govProvince.at(index).govCity.end()) {
		startCity.AddString((*iter).name.c_str());
		++iter;
	}

	startCity.SetCurSel(0);
	startCity.UpdateData(FALSE);

	while (startCounty.GetCount() > 0) {
		startCounty.DeleteString( 0 );
	}
	vector<County>::iterator iter2 = myCR->govProvince.at(index).govCity.front().govCounty.begin();
	while (iter2 != myCR->govProvince.at(index).govCity.front().govCounty.end()) {
		startCounty.AddString((*iter2).name.c_str());
		++iter2;
	}
	startCounty.SetCurSel(0);
	startCounty.UpdateData(FALSE);
}
    
// ��Ӧ�������б������Ϣ
void CSearchSpecialDlg::OnCbnSelchangeStartCity()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    int indexSheng = startProvince.GetCurSel();
	int indexShi = startCity.GetCurSel();

	while (startCounty.GetCount() > 0) {
		startCounty.DeleteString( 0 );
	}
	vector<County>::iterator iter = 
		myCR->govProvince.at(indexSheng).govCity.at(indexShi).govCounty.begin();
	while (iter != myCR->govProvince.at(indexSheng).govCity.at(indexShi).govCounty.end()) {
		startCounty.AddString((*iter).name.c_str());
		++iter;
	}

	startCounty.SetCurSel(0);
	startCounty.UpdateData(FALSE);
}
    
// ��Ӧ����ʡ�б������Ϣ
void CSearchSpecialDlg::OnCbnSelchangeEndProvince()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    int index = endProvince.GetCurSel();

	// Delete every other item from the combo box.
	while (endCity.GetCount() > 0) {
		endCity.DeleteString( 0 );
	}

	vector<City>::iterator iter = myCR->govProvince.at(index).govCity.begin();
	while (iter != myCR->govProvince.at(index).govCity.end()) {
		endCity.AddString((*iter).name.c_str());
		++iter;
	}

	endCity.SetCurSel(0);
	endCity.UpdateData(FALSE);

	while (endCounty.GetCount() > 0) {
		endCounty.DeleteString( 0 );
	}
	vector<County>::iterator iter2 = myCR->govProvince.at(index).govCity.front().govCounty.begin();
	while (iter2 != myCR->govProvince.at(index).govCity.front().govCounty.end()) {
		endCounty.AddString((*iter2).name.c_str());
		++iter2;
	}
	endCounty.SetCurSel(0);
	endCounty.UpdateData(FALSE);
}
    
// ��Ӧ�������б������Ϣ
void CSearchSpecialDlg::OnCbnSelchangeEndCity()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    int indexSheng = endProvince.GetCurSel();
	int indexShi = endCity.GetCurSel();

	while (endCounty.GetCount() > 0) {
		endCounty.DeleteString( 0 );
	}
	vector<County>::iterator iter = 
		myCR->govProvince.at(indexSheng).govCity.at(indexShi).govCounty.begin();
	while (iter != myCR->govProvince.at(indexSheng).govCity.at(indexShi).govCounty.end()) {
		endCounty.AddString((*iter).name.c_str());
		++iter;
	}

	endCounty.SetCurSel(0);
	endCounty.UpdateData(FALSE);
}
void CSearchSpecialDlg::OnBnClickedOk()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    UpdateData();
    bool ifOK = true;

    // �жϱ����ֶ�
    if (strStartProvince == "" && strEndProvince == "") {
        MessageBox("�����غ͵����������дһ��", "����ר��");
        ifOK = false;
        return;
    }

    // ����δ���ֶ�Ϊ "NULL"
    if (strStartProvince == "") {
        strStartProvince = "NULL";
        strStartCity = "NULL";
        strStartCounty = "NULL";
    }

    if (strEndProvince == "") {
        strEndProvince = "NULL";
        strEndCity = "NULL";
        strEndCounty = "NULL";
    }

    if (ifOK) {       
        OnOK();
    }
}
