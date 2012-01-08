// AddCustomZoneDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WLRClient.h"
#include "AddCustomZoneDlg.h"


// CAddCustomZoneDlg �Ի���

IMPLEMENT_DYNAMIC(CAddCustomZoneDlg, CDialog)

CAddCustomZoneDlg::CAddCustomZoneDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddCustomZoneDlg::IDD, pParent)
    , strStartProvince(_T(""))
    , strStartCity(_T(""))
    , strEndProvince(_T(""))
    , strEndCity(_T(""))
{
    myCR = NULL;
}

CAddCustomZoneDlg::~CAddCustomZoneDlg()
{
}
    
//
void CAddCustomZoneDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_START_PROVINCE, startProvince);
    DDX_Control(pDX, IDC_START_CITY, startCity);
    DDX_Control(pDX, IDC_END_PROVINCE, endProvince);
    DDX_Control(pDX, IDC_END_CITY, endCity);
    DDX_CBString(pDX, IDC_START_PROVINCE, strStartProvince);
    DDX_CBString(pDX, IDC_START_CITY, strStartCity);
    DDX_CBString(pDX, IDC_END_PROVINCE, strEndProvince);
    DDX_CBString(pDX, IDC_END_CITY, strEndCity);
}


BEGIN_MESSAGE_MAP(CAddCustomZoneDlg, CDialog)
    ON_CBN_SELCHANGE(IDC_START_PROVINCE, &CAddCustomZoneDlg::OnCbnSelchangeStartProvince)
    ON_CBN_SELCHANGE(IDC_END_PROVINCE, &CAddCustomZoneDlg::OnCbnSelchangeEndProvince)
    ON_BN_CLICKED(IDOK, &CAddCustomZoneDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CAddCustomZoneDlg ��Ϣ�������

BOOL CAddCustomZoneDlg::OnInitDialog()
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
int CAddCustomZoneDlg::initStartPoint()
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
int CAddCustomZoneDlg::initEndPoint()
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
void CAddCustomZoneDlg::OnCbnSelchangeStartProvince()
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
}
    
// ��Ӧ����ʡ�б������Ϣ
void CAddCustomZoneDlg::OnCbnSelchangeEndProvince()
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
}    
    
// ���OK
void CAddCustomZoneDlg::OnBnClickedOk()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    UpdateData();
    bool ifOK = true;
    // �жϱ����ֶ�
    if (strStartProvince == "" || strStartCity == "") {
        MessageBox("�����ز���Ϊ��", "���Ӷ�������");
        ifOK = false;
        return;
    }

    if (strEndProvince == "" || strEndCity == "") {
        MessageBox("����ز���Ϊ��", "���Ӷ�������");
        ifOK = false;
        return;
    }

    if (ifOK) {       
        OnOK();
    }
}
