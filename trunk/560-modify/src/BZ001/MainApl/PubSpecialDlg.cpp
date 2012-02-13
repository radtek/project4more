// PubSpecialDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WLRClient.h"
#include "PubSpecialDlg.h"


// CPubSpecialDlg �Ի���

IMPLEMENT_DYNAMIC(CPubSpecialDlg, CDialog)

CPubSpecialDlg::CPubSpecialDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPubSpecialDlg::IDD, pParent)
    , stProvince(_T(""))
    , stCity(_T(""))
    , stCounty(_T(""))
    , enProvince(_T(""))
    , enCity(_T(""))
    , enCounty(_T(""))
    , weightPrice(_T(""))
    , lightPrice(_T(""))
    , type(0)
    , transport(1)
    , send(_T(""))
    , time(0)
    , information(_T(""))
    , stName(_T(""))
    , stAddress(_T(""))
    , stTel(_T(""))
    , enName(_T(""))
    , enAddress(_T(""))
    , enTel(_T(""))
    , ifUp(FALSE)
{

}

CPubSpecialDlg::~CPubSpecialDlg()
{
}

void CPubSpecialDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_PUB_SPECIAL_STPROVINCE, combStProvince);
    DDX_CBString(pDX, IDC_PUB_SPECIAL_STPROVINCE, stProvince);
    DDX_Control(pDX, IDC_PUB_SPECIAL_STCITY, combStCity);
    DDX_CBString(pDX, IDC_PUB_SPECIAL_STCITY, stCity);
    DDX_Control(pDX, IDC_PUB_SPECIAL_STCOUNTY, combStCounty);
    DDX_CBString(pDX, IDC_PUB_SPECIAL_STCOUNTY, stCounty);
    DDX_Control(pDX, IDC_PUB_SPECIAL_ENPROVINCE, combEnProvince);
    DDX_CBString(pDX, IDC_PUB_SPECIAL_ENPROVINCE, enProvince);
    DDX_Control(pDX, IDC_PUB_SPECIAL_ENCITY, combEnCity);
    DDX_CBString(pDX, IDC_PUB_SPECIAL_ENCITY, enCity);
    DDX_Control(pDX, IDC_PUB_SPECIAL_ENCOUNTY, combEnCounty);
    DDX_CBString(pDX, IDC_PUB_SPECIAL_ENCOUNTY, enCounty);
    DDX_Text(pDX, IDC_PUB_SPECIAL_WEIGHT_PRICE, weightPrice);
	DDX_Text(pDX, IDC_PUB_SPECIAL_LIGHT_PRICE, lightPrice);
    DDX_Radio(pDX, IDC_PUB_SPECIAL_TYPE1, type);
    DDX_Radio(pDX, IDC_PUB_SPECIAL_TRANSPORT1, transport);
    DDX_Control(pDX, IDC_PUB_SPECIAL_SEND, combSend);
    DDX_CBString(pDX, IDC_PUB_SPECIAL_SEND, send);
    DDX_Radio(pDX, IDC_PUB_SPECIAL_TIME1, time);
    DDX_Text(pDX, IDC_PUB_SPECIAL_INF, information);
    DDX_Text(pDX, IDC_PUB_SPECIAL_ST_NAME, stName);
    DDX_Text(pDX, IDC_PUB_SPECIAL_ST_ADDRESS, stAddress);
    DDX_Text(pDX, IDC_PUB_SPECIAL_ST_TEL, stTel);
    DDX_Text(pDX, IDC_PUB_SPECIAL_EN_NAME, enName);
    DDX_Text(pDX, IDC_PUB_SPECIAL_EN_ADDRESS, enAddress);
    DDX_Text(pDX, IDC_PUB_SPECIAL_TEL, enTel);
    DDX_Check(pDX, IDC_PUB_SPECIAL_IFUP, ifUp);
}


BEGIN_MESSAGE_MAP(CPubSpecialDlg, CDialog)
    ON_CBN_SELCHANGE(IDC_PUB_SPECIAL_STPROVINCE, &CPubSpecialDlg::OnCbnSelchangePubSpecialStprovince)
    ON_CBN_SELCHANGE(IDC_PUB_SPECIAL_STCITY, &CPubSpecialDlg::OnCbnSelchangePubSpecialStcity)
    ON_CBN_SELCHANGE(IDC_PUB_SPECIAL_ENPROVINCE, &CPubSpecialDlg::OnCbnSelchangePubSpecialEnprovince)
    ON_CBN_SELCHANGE(IDC_PUB_SPECIAL_ENCITY, &CPubSpecialDlg::OnCbnSelchangePubSpecialEncity)
    ON_BN_CLICKED(IDOK, &CPubSpecialDlg::OnBnClickedOk)
	ON_EN_CHANGE(IDC_PUB_SPECIAL_WEIGHT_PRICE, &CPubSpecialDlg::OnEnChangePubSpecialWeightPrice)
END_MESSAGE_MAP()

BOOL CPubSpecialDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  �ڴ���Ӷ���ĳ�ʼ��
    // ������ʽ

	((CEdit*)GetDlgItem(IDC_PUB_SPECIAL_WEIGHT_PRICE))->LimitText(8);
	((CEdit*)GetDlgItem(IDC_PUB_SPECIAL_LIGHT_PRICE))->LimitText(8);
	((CEdit*)GetDlgItem(IDC_PUB_SPECIAL_ST_NAME))->LimitText(32);
	((CEdit*)GetDlgItem(IDC_PUB_SPECIAL_ST_ADDRESS))->LimitText(128);
	((CEdit*)GetDlgItem(IDC_PUB_SPECIAL_ST_TEL))->LimitText(32);
	((CEdit*)GetDlgItem(IDC_PUB_SPECIAL_EN_NAME))->LimitText(32);
	((CEdit*)GetDlgItem(IDC_PUB_SPECIAL_EN_ADDRESS))->LimitText(128);
	((CEdit*)GetDlgItem(IDC_PUB_SPECIAL_TEL))->LimitText(32);
	((CEdit*)GetDlgItem(IDC_PUB_SPECIAL_INF))->LimitText(100);

	combSend.AddString("���̶�");
	combSend.AddString("��1��һ��");
	combSend.AddString("��2��һ��");
	combSend.AddString("��3��һ��");
    combSend.AddString("��4��һ��");
    combSend.AddString("��5��һ��");
	combSend.SetCurSel(0);

    // ��ϵ��ʽ
    information = userInfo.company.c_str();
	if (information == "NULL")
	{
		information = "";
		information=userInfo.realName.c_str();
	}
    information += " ";
    information += userInfo.tel.c_str();
    UpdateData(false);
    	
    initStartPoint();
	initEndPoint();
    return TRUE;  // return TRUE unless you set the focus to a control
    // �쳣: OCX ����ҳӦ���� FALSE
}

// CPubSpecialDlg ��Ϣ�������
    
// ��Ӧ��������򣺳�����ʡ
void CPubSpecialDlg::OnCbnSelchangePubSpecialStprovince()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
	int index = combStProvince.GetCurSel();

    // Delete every other item from the combo box.
	while (combStCity.GetCount() > 0) {
		combStCity.DeleteString( 0 );
	}

	vector<City>::iterator iter = myCR->govProvince.at(index).govCity.begin();
	while (iter != myCR->govProvince.at(index).govCity.end()) {
		combStCity.AddString((*iter).name.c_str());
		++iter;
	}

	combStCity.SetCurSel(0);
	combStCity.UpdateData(FALSE);

	while (combStCounty.GetCount() > 0) {
		combStCounty.DeleteString( 0 );
	}
	vector<County>::iterator iter2 = myCR->govProvince.at(index).govCity.front().govCounty.begin();
	while (iter2 != myCR->govProvince.at(index).govCity.front().govCounty.end()) {
		combStCounty.AddString((*iter2).name.c_str());
		++iter2;
	}
	combStCounty.SetCurSel(0);
	combStCounty.UpdateData(FALSE);
}
    
// ��Ӧ��������򣺳�������
void CPubSpecialDlg::OnCbnSelchangePubSpecialStcity()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
	int indexSheng = combStProvince.GetCurSel();
	int indexShi = combStCity.GetCurSel();

	while (combStCounty.GetCount() > 0) {
		combStCounty.DeleteString( 0 );
	}
	vector<County>::iterator iter = 
		myCR->govProvince.at(indexSheng).govCity.at(indexShi).govCounty.begin();
	while (iter != myCR->govProvince.at(indexSheng).govCity.at(indexShi).govCounty.end()) {
		combStCounty.AddString((*iter).name.c_str());
		++iter;
	}

	combStCounty.SetCurSel(0);
	combStCounty.UpdateData(FALSE);
}
    
// ��Ӧ��������򣺵����ʡ
void CPubSpecialDlg::OnCbnSelchangePubSpecialEnprovince()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
	int index = combEnProvince.GetCurSel();

	// Delete every other item from the combo box.
	while (combEnCity.GetCount() > 0) {
		combEnCity.DeleteString( 0 );
	}

	vector<City>::iterator iter = myCR->govProvince.at(index).govCity.begin();
	while (iter != myCR->govProvince.at(index).govCity.end()) {
		combEnCity.AddString((*iter).name.c_str());
		++iter;
	}

	combEnCity.SetCurSel(0);
	combEnCity.UpdateData(FALSE);

	while (combEnCounty.GetCount() > 0) {
		combEnCounty.DeleteString( 0 );
	}
	vector<County>::iterator iter2 = myCR->govProvince.at(index).govCity.front().govCounty.begin();
	while (iter2 != myCR->govProvince.at(index).govCity.front().govCounty.end()) {
		combEnCounty.AddString((*iter2).name.c_str());
		++iter2;
	}
	combEnCounty.SetCurSel(0);
	combEnCounty.UpdateData(FALSE);
}
    
// ��Ӧ��������򣺵������
void CPubSpecialDlg::OnCbnSelchangePubSpecialEncity()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
	int indexSheng = combEnProvince.GetCurSel();
	int indexShi = combEnCity.GetCurSel();

	while (combEnCounty.GetCount() > 0) {
		combEnCounty.DeleteString( 0 );
	}
	vector<County>::iterator iter = 
		myCR->govProvince.at(indexSheng).govCity.at(indexShi).govCounty.begin();
	while (iter != myCR->govProvince.at(indexSheng).govCity.at(indexShi).govCounty.end()) {
		combEnCounty.AddString((*iter).name.c_str());
		++iter;
	}

	combEnCounty.SetCurSel(0);
	combEnCounty.UpdateData(FALSE);
}
    
// �������б���ʼ��
int CPubSpecialDlg::initStartPoint()
{
    if (myCR == NULL) {
        return -1;
    }
	
	string sStartProv = provSelected.IsEmpty()?userInfo.province:(LPCTSTR)provSelected;
	string sStartCity = citySelected.IsEmpty()?userInfo.city:(LPCTSTR)citySelected;

    vector<Province>::iterator iter = myCR->govProvince.begin();
	int i = 0;
	int defaultShengSel = 0;
	int defaultShiSel = 0;
    while (iter != myCR->govProvince.end()) {
		combStProvince.AddString((*iter).name.c_str());
		if(0 == (*iter).name.compare(sStartProv)) { // �ҵ���ǰ�û�����ʡ
			int j = 0;
			vector<City>::iterator iter2 = (*iter).govCity.begin();
			while (iter2 != (*iter).govCity.end()) {
				combStCity.AddString((*iter2).name.c_str());
				if(0 == (*iter2).name.compare(sStartCity)) { // �ҵ���ǰ�û�������
					vector<County>::iterator iter3 = (*iter2).govCounty.begin();
					while (iter3 != (*iter2).govCounty.end()) {
						combStCounty.AddString((*iter3).name.c_str());
						++iter3;
					}
					defaultShiSel = j;
				}
				++iter2;
				++j;
			}

			defaultShengSel = i;
		}
        ++iter;
		++i;
    }
	combStProvince.SetCurSel(defaultShengSel);
	combStCity.SetCurSel(defaultShiSel);
	combStCounty.SetCurSel(0);

	return 0;
}
    
// ��ʼ��Ŀ�ĵ�
int CPubSpecialDlg::initEndPoint()
{
    if (myCR == NULL) {
        return -1;
    }

    vector<Province>::iterator iter = myCR->govProvince.begin();
    while (iter != myCR->govProvince.end()) {
		combEnProvince.AddString((*iter).name.c_str());
        ++iter;
    }
	return 0;
}
    
// ȷ����ť
void CPubSpecialDlg::OnBnClickedOk()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    UpdateData();
	//MessageBox (information);
    bool ifOK = true;
    // �жϱ����ֶ�
    if (enProvince == "" || enCity == "" || enCounty == "") {
        MessageBox("Ŀ�ĵز���Ϊ��");
        ifOK = false;
        return;
    }

    if (weightPrice == "") {
        MessageBox("�ػ��۸���Ϊ��");
        ifOK = false;
        return;
    }
	if( !CheckNumberString(weightPrice) )
	{
		MessageBox("�ػ��۸�ӦΪ����");
		ifOK = false;
		return;
	}

    if (lightPrice == "") {
        MessageBox("�ݻ��۸���Ϊ��");
        ifOK = false;
        return;
    }
	if( !CheckNumberString(lightPrice) )
	{
		MessageBox("�ݻ��۸�ӦΪ����");
		ifOK = false;
		return;
	}

    if (information == "") {
        MessageBox("��Ϣ��������Ϊ��", "����ר��");
        ifOK = false;
        return;
    } 

    if (stTel == "") {
        MessageBox("�����ص绰����Ϊ��", "����ר��");
        ifOK = false;
        return;
    } 

    if (enTel == "") {
        MessageBox("Ŀ�ĵص绰����Ϊ��", "����ר��");
        ifOK = false;
        return;
    } 

    // ����δ���ֶ�Ϊ "NULL"    
    if (stName == "") {
        stName = "NULL";
    } 

    if (stAddress == "") {
        stAddress = "NULL";
    } 

    if (enName == "") {
        enName = "NULL";
    } 

    if (enAddress == "") {
        enAddress = "NULL";
    } 

    CString tmp = stProvince + "|" + stCity + "|" + stCounty
                + "|" + enProvince + "|" + enCity + "|" + enCounty
                + "|" + weightPrice;    

    if (0 == type) {
        tmp = tmp + "|" + "����"; 
    } else {
        tmp = tmp + "|" + "����";
    }
                    
    tmp = tmp + "|" + lightPrice ;
                    
    if (0 == transport) {
        tmp = tmp + "|" + "��ת"; 
    } else {
        tmp = tmp + "|" + "ֱ��";
    }

    tmp = tmp + "|" + send ;
                    
    if (0 == time) {
        tmp = tmp + "|" + "1��"; 
    } else if (1 == time) {
        tmp = tmp + "|" + "2��";
    } else if (2 == time) {
        tmp = tmp + "|" + "3��";
    } else if (3 == time) {
        tmp = tmp + "|" + "4��";
    } else {
        tmp = tmp + "|" + "5��";
    }

    tmp = tmp + "|" + information 
        + "|" + stName + "|" + stAddress + "|" + stTel
        + "|" + enName + "|" + enAddress + "|" + enTel;

    if (ifUp) {
        tmp = tmp + "|" + "1"; 
    } else {
        tmp = tmp + "|" + "0";
    }    

    if (ifOK) {    
        pubInf = (LPTSTR)(LPCTSTR)tmp;    
        OnOK();
    }
}


void CPubSpecialDlg::OnEnChangePubSpecialWeightPrice()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}
