// SearchCarsDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WLRClient.h"
#include "SearchCarsDlg.h"


// CSearchCarsDlg �Ի���

IMPLEMENT_DYNAMIC(CSearchCarsDlg, CDialog)

CSearchCarsDlg::CSearchCarsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSearchCarsDlg::IDD, pParent)
    , strStartProvince(_T(""))
    , strStartCity(_T(""))
    , strStartCounty(_T(""))
    , strEndProvince(_T(""))
    , strEndCity(_T(""))
    , strEndCounty(_T(""))
    , strCarLength(_T(""))
    , strCarType(_T(""))
{
    myCR = NULL;
}

CSearchCarsDlg::~CSearchCarsDlg()
{
}
    
//
void CSearchCarsDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_START_PROVINCE, startProvince);
    DDX_Control(pDX, IDC_START_CITY, startCity);
    DDX_Control(pDX, IDC_START_COUNTY, startCounty);
    DDX_Control(pDX, IDC_END_PROVINCE, endProvince);
    DDX_Control(pDX, IDC_END_CITY, endCity);
    DDX_Control(pDX, IDC_END_COUNTY, endCounty);
    DDX_Control(pDX, IDC_CAR_LENGTH, carLength);
    DDX_Control(pDX, IDC_CAR_TYPE, carType);
    DDX_CBString(pDX, IDC_START_PROVINCE, strStartProvince);
    DDX_CBString(pDX, IDC_START_CITY, strStartCity);
    DDX_CBString(pDX, IDC_START_COUNTY, strStartCounty);
    DDX_CBString(pDX, IDC_END_PROVINCE, strEndProvince);
    DDX_CBString(pDX, IDC_END_CITY, strEndCity);
    DDX_CBString(pDX, IDC_END_COUNTY, strEndCounty);
    DDX_CBString(pDX, IDC_CAR_LENGTH, strCarLength);
    DDX_CBString(pDX, IDC_CAR_TYPE, strCarType);
}


BEGIN_MESSAGE_MAP(CSearchCarsDlg, CDialog)
    ON_CBN_SELCHANGE(IDC_START_PROVINCE, &CSearchCarsDlg::OnCbnSelchangeStartProvince)
    ON_CBN_SELCHANGE(IDC_START_CITY, &CSearchCarsDlg::OnCbnSelchangeStartCity)
    ON_CBN_SELCHANGE(IDC_END_PROVINCE, &CSearchCarsDlg::OnCbnSelchangeEndProvince)
    ON_CBN_SELCHANGE(IDC_END_CITY, &CSearchCarsDlg::OnCbnSelchangeEndCity)
    ON_BN_CLICKED(IDOK, &CSearchCarsDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CSearchCarsDlg ��Ϣ�������

BOOL CSearchCarsDlg::OnInitDialog()
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

    // ����
    carLength.AddString("����");
	carLength.AddString("4��");
	carLength.AddString("4.2��");
	carLength.AddString("4.3��");
	carLength.AddString("4.5��");
	carLength.AddString("4.8��");
	carLength.AddString("5��");
	carLength.AddString("5.8��");
	carLength.AddString("6��");
	carLength.AddString("6.2��");
	carLength.AddString("6.8��");
	carLength.AddString("7��");
	carLength.AddString("7.2��");
	carLength.AddString("7.4��");
	carLength.AddString("7.8��");
	carLength.AddString("8��");
	carLength.AddString("8.7��");
	carLength.AddString("8.8��");
	carLength.AddString("9��");
	carLength.AddString("9.6��");
	carLength.AddString("12.5��");
	carLength.AddString("13��");
	carLength.AddString("13.5��");
	carLength.AddString("17.5��");
	carLength.SetCurSel(0);

	// ������
    carType.AddString("����");
	carType.AddString("ǰ�ĺ�ʮ");
	carType.AddString("ǰ�ĺ��");
	carType.AddString("ǰ�ĺ���");
	carType.AddString("���ճ�");
	carType.AddString("����");
	carType.AddString("ƽ�峵");
	carType.AddString("������");
	carType.AddString("��װ��");
	carType.AddString("��س�");
	carType.AddString("�����");
	carType.AddString("���ų�");
	carType.AddString("��ж��");
	carType.AddString("��ҳ�");
	carType.AddString("���³�");
	carType.AddString("˫�ų�");
	carType.AddString("�ߵͰ�");
	carType.SetCurSel(0);

    return TRUE;  // return TRUE unless you set the focus to a control
    // �쳣: OCX ����ҳӦ���� FALSE
}
    
// ��ʼ��������
int CSearchCarsDlg::initStartPoint()
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
int CSearchCarsDlg::initEndPoint()
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
void CSearchCarsDlg::OnCbnSelchangeStartProvince()
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
void CSearchCarsDlg::OnCbnSelchangeStartCity()
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
void CSearchCarsDlg::OnCbnSelchangeEndProvince()
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
void CSearchCarsDlg::OnCbnSelchangeEndCity()
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

void CSearchCarsDlg::OnBnClickedOk()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    UpdateData();
    bool ifOK = true;

    // �жϱ����ֶ�
    if (strStartProvince == "" && strEndProvince == "") {
        MessageBox("�����غ͵����������дһ��", "������Դ");
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
