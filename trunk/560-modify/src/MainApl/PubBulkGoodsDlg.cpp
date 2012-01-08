// PubBulkGoodsDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WLRClient.h"
#include "PubBulkGoodsDlg.h"


// CPubBulkGoodsDlg �Ի���

IMPLEMENT_DYNAMIC(CPubBulkGoodsDlg, CDialog)

CPubBulkGoodsDlg::CPubBulkGoodsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPubBulkGoodsDlg::IDD, pParent)
    , stProvince(_T(""))
    , stCity(_T(""))
    , stCounty(_T(""))
    , enProvince(_T(""))
    , enCity(_T(""))
    , enCounty(_T(""))
    , name(_T(""))
    , weight(_T(""))
    , weightUnit(_T(""))
    , carType(_T(""))
    , tel(_T(""))
    , preview(_T(""))
    , syProvince(_T(""))
    , syCity(_T(""))
    , rePubType(_T(""))
    , ifRemRePub(FALSE)
    , ifLongTime(FALSE)
    , ifUp(FALSE)
	, bPreview(FALSE)
{

}

CPubBulkGoodsDlg::~CPubBulkGoodsDlg()
{
}

void CPubBulkGoodsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PUB_BULKGOODS_STPROVINCE, combStProvince);
	DDX_CBString(pDX, IDC_PUB_BULKGOODS_STPROVINCE, stProvince);
	DDX_Control(pDX, IDC_PUB_BULKGOODS_STCITY, combStCity);
	DDX_CBString(pDX, IDC_PUB_BULKGOODS_STCITY, stCity);
	DDX_Control(pDX, IDC_PUB_BULKGOODS_STCOUNTY, combStCounty);
	DDX_CBString(pDX, IDC_PUB_BULKGOODS_STCOUNTY, stCounty);
	DDX_Control(pDX, IDC_PUB_BULKGOODS_ENPROVINCE, combEnProvince);
	DDX_CBString(pDX, IDC_PUB_BULKGOODS_ENPROVINCE, enProvince);
	DDX_Control(pDX, IDC_PUB_BULKGOODS_ENCITY, combEnCity);
	DDX_CBString(pDX, IDC_PUB_BULKGOODS_ENCITY, enCity);
	DDX_Control(pDX, IDC_PUB_BULKGOODS_ENCOUNTY, combEnCounty);
	DDX_CBString(pDX, IDC_PUB_BULKGOODS_ENCOUNTY, enCounty);
	DDX_Control(pDX, IDC_PUB_BULKGOODS_NAME, combName);
	DDX_CBString(pDX, IDC_PUB_BULKGOODS_NAME, name);
	DDX_Text(pDX, IDC_PUB_BULKGOODS_WEIGHT, weight);
	DDX_Control(pDX, IDC_PUB_BULKGOODS_WEIGHTUNIT, combWeightUnit);
	DDX_CBString(pDX, IDC_PUB_BULKGOODS_WEIGHTUNIT, weightUnit);
	DDX_Control(pDX, IDC_PUB_BULKGOODS_CARTYPE, combCarType);
	DDX_CBString(pDX, IDC_PUB_BULKGOODS_CARTYPE, carType);
	DDX_Text(pDX, IDC_PUB_BULKGOODS_TEL, tel);
	DDX_Text(pDX, IDC_PUB_BULKGOODS_PREVIEW_EDIT, preview);
	DDX_Control(pDX, IDC_PUB_BULKGOODS_SYPROVINCE, combSyProvince);
	DDX_CBString(pDX, IDC_PUB_BULKGOODS_SYPROVINCE, syProvince);
	DDX_Control(pDX, IDC_PUB_BULKGOODS_SYCITY, combSyCity);
	DDX_CBString(pDX, IDC_PUB_BULKGOODS_SYCITY, syCity);
	DDX_Control(pDX, IDC_PUB_BULKGOODS_REPUBTYPE, combRePubType);
	DDX_CBString(pDX, IDC_PUB_BULKGOODS_REPUBTYPE, rePubType);
	DDX_Check(pDX, IDC_PUB_BULKGOODS_IFREMREPUB, ifRemRePub);
	DDX_Check(pDX, IDC_PUB_BULKGOODS_IFLONGTIME, ifLongTime);
	DDX_Check(pDX, IDC_PUB_BULKGOODS_IFUP, ifUp);
	DDX_Control(pDX, IDC_PUB_BULKGOODS_PREVIEW_EDIT, m_msgedit);
}


BEGIN_MESSAGE_MAP(CPubBulkGoodsDlg, CDialog)
    ON_BN_CLICKED(IDC_PUB_BULKGOODS_PREVIEW_BTN, &CPubBulkGoodsDlg::OnBnClickedPubGoodsPreviewBtn)
    ON_CBN_SELCHANGE(IDC_PUB_BULKGOODS_STPROVINCE, &CPubBulkGoodsDlg::OnCbnSelchangePubGoodsStprovince)
    ON_CBN_SELCHANGE(IDC_PUB_BULKGOODS_STCITY, &CPubBulkGoodsDlg::OnCbnSelchangePubGoodsStcity)
    ON_CBN_SELCHANGE(IDC_PUB_BULKGOODS_ENPROVINCE, &CPubBulkGoodsDlg::OnCbnSelchangePubGoodsEnprovince)
    ON_CBN_SELCHANGE(IDC_PUB_BULKGOODS_ENCITY, &CPubBulkGoodsDlg::OnCbnSelchangePubGoodsEncity)
    ON_CBN_SELCHANGE(IDC_PUB_BULKGOODS_SYPROVINCE, &CPubBulkGoodsDlg::OnCbnSelchangePubGoodsSyprovince)
    ON_BN_CLICKED(IDOK, &CPubBulkGoodsDlg::OnBnClickedOk)
END_MESSAGE_MAP()
    
// ��ʼ��
BOOL CPubBulkGoodsDlg::OnInitDialog()
{
    CDialog::OnInitDialog();
	m_msgedit.LimitText(100);
    // TODO:  �ڴ���Ӷ���ĳ�ʼ��
    // ��ʼ����������
	combName.AddString("��ѡ��");
	combName.AddString("����");
	combName.AddString("�Ҿ�ľ��");
	combName.AddString("��ʳ");
	combName.AddString("�߲�");
	combName.AddString("ˮ��");
	combName.AddString("ũ����Ʒ");
	combName.AddString("ʳƷ");
	combName.AddString("��Ʒ");
	combName.AddString("ֽƷ");
	combName.AddString("����");
	combName.AddString("�ٻ�");
	combName.AddString("��ʯ");
	combName.AddString("ú");
	combName.AddString("����");
	combName.AddString("ҽҩ");
	combName.AddString("��е�豸");
	combName.AddString("Σ��Ʒ");
	combName.AddString("����");
	combName.SetCurSel(0);

	// ���ﵥλ
    combWeightUnit.AddString("����");
	combWeightUnit.AddString("��");
	combWeightUnit.AddString("����");
	combWeightUnit.AddString("��");
	combWeightUnit.AddString("��");
	combWeightUnit.SetCurSel(0);

	// ������
	combCarType.AddString("��ѡ��");
	//combCarType.AddString("��ͨ��");
	combCarType.AddString("ǰ�ĺ�ʮ");
	combCarType.AddString("ǰ�ĺ��");
	combCarType.AddString("ǰ�ĺ���");
	combCarType.AddString("���ճ�");
	combCarType.AddString("����");
	combCarType.AddString("ƽ�峵");
	combCarType.AddString("������");
	combCarType.AddString("��װ��");
	combCarType.AddString("��س�");
//	combCarType.AddString("���س�");
	combCarType.AddString("�����");
	combCarType.AddString("���ų�");
	combCarType.AddString("��ж��");

	combCarType.AddString("��ҳ�");
	combCarType.AddString("���³�");
	combCarType.AddString("˫�ų�");
//	combCarType.AddString("�ӳ��ҳ�");
//	combCarType.AddString("�ޱ���");
//	combCarType.AddString("�����ӳ�");
	combCarType.AddString("�ߵͰ�");
//	combCarType.AddString("������");
	combCarType.SetCurSel(0);

	// �ط�����
	combRePubType.AddString("���Զ��ط�");
	combRePubType.AddString("10����2��");
	combRePubType.AddString("30����5��");
	combRePubType.AddString("2Сʱ10��");
	combRePubType.SetCurSel(0);

    // ��ϵ��ʽ
    tel = userInfo.tel.c_str();
    UpdateData(false);

	initStartPoint();
	initEndPoint();
	initSynPoint();

    return TRUE;  // return TRUE unless you set the focus to a control
    // �쳣: OCX ����ҳӦ���� FALSE
}

// CPubBulkGoodsDlg ��Ϣ�������
    
// ���Ԥ����ť
void CPubBulkGoodsDlg::OnBnClickedPubGoodsPreviewBtn()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	CString cname,ctype,clen,ccartype,cprice;//�������࣬�������ͣ��������ȣ��������ͣ��۸�����

	combName.GetWindowText(cname);
	combCarType.GetWindowText(ccartype);
	if (cname == "��ѡ��")
	{
		MessageBox("��ѡ���������", "�����㵣");
		return;
	}
	if (ccartype == "��ѡ��")
	{
		MessageBox("��ѡ��������", "�����㵣");
		return;
		//carType = "NULL";
	}
	// �жϱ����ֶ�
	if (enProvince == "" || enCity == "" || enCounty == "") {
		MessageBox("Ŀ�ĵز���Ϊ��", "�����㵣");
		return;
	}
	
	if (weight == "") {
		MessageBox("��������Ϊ��", "�����㵣");
		
		return;
	}

	if (tel == "") {
		MessageBox("��ϵ�绰����Ϊ��", "�����㵣");
		return;
	} 
 	bPreview = TRUE;
// 
// 	preview = stProvince + stCity + stCounty	
// 			+ "����" + enProvince + enCity + enCounty
// 			+ "����" + name + weight + weightUnit			
// 			+ "���裺" + carType;

	preview = "�л���" + name +"��������"+ weight + weightUnit			
		+ "����Ҫ" + carType;

	UpdateData(FALSE);
}
    
// ��Ӧ��������򣺳�����ʡ
void CPubBulkGoodsDlg::OnCbnSelchangePubGoodsStprovince()
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
void CPubBulkGoodsDlg::OnCbnSelchangePubGoodsStcity()
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
void CPubBulkGoodsDlg::OnCbnSelchangePubGoodsEnprovince()
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
void CPubBulkGoodsDlg::OnCbnSelchangePubGoodsEncity()
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
    
// ��Ӧ���������ͬ������ʡ
void CPubBulkGoodsDlg::OnCbnSelchangePubGoodsSyprovince()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
	int index = combSyProvince.GetCurSel();

    // Delete every other item from the combo box.
	while (combSyCity.GetCount() > 0) {
		combSyCity.DeleteString( 0 );
	}

	vector<City>::iterator iter = myCR->govProvince.at(index).govCity.begin();
	while (iter != myCR->govProvince.at(index).govCity.end()) {
		combSyCity.AddString((*iter).name.c_str());
		++iter;
	}

	combSyCity.SetCurSel(0);
	combSyCity.UpdateData(FALSE);
}
    
// �������б���ʼ��
int CPubBulkGoodsDlg::initStartPoint()
{
    if (myCR == NULL) {
        return -1;
    }

    vector<Province>::iterator iter = myCR->govProvince.begin();
	int i = 0;
	int defaultShengSel = 0;
	int defaultShiSel = 0;
    while (iter != myCR->govProvince.end()) {
		combStProvince.AddString((*iter).name.c_str());
		if(0 == (*iter).name.compare(userInfo.province)) { // �ҵ���ǰ�û�����ʡ
			int j = 0;
			vector<City>::iterator iter2 = (*iter).govCity.begin();
			while (iter2 != (*iter).govCity.end()) {
				combStCity.AddString((*iter2).name.c_str());
				if(0 == (*iter2).name.compare(userInfo.city)) { // �ҵ���ǰ�û�������
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
int CPubBulkGoodsDlg::initEndPoint()
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
    
// ��ʼ��ͬʱ������
int CPubBulkGoodsDlg::initSynPoint()
{
    if (myCR == NULL) {
        return -1;
    }

    vector<Province>::iterator iter = myCR->govProvince.begin();
    while (iter != myCR->govProvince.end()) {
		combSyProvince.AddString((*iter).name.c_str());
        ++iter;
    }

	return 0;
}
    
// ȷ����ť
void CPubBulkGoodsDlg::OnBnClickedOk()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    UpdateData();
    bool ifOK = true;
	if (!bPreview)
	{
		MessageBox("�ڷ���ǰ����Ԥ����", "�����㵣");
		ifOK = false;
		return;
	}
	if (preview == "")
	{
		MessageBox("Ԥ������Ϊ�գ�", "������Դ");
		ifOK = false;
		return;
	}
	bPreview = FALSE;
	CString cname,ctype,clen,ccartype,cprice;//�������࣬�������ͣ��������ȣ��������ͣ��۸�����

	combName.GetWindowText(cname);
	combCarType.GetWindowText(ccartype);
	if (cname == "��ѡ��")
	{
		MessageBox("��ѡ���������", "�����㵣");
		ifOK = false;
		return;
	}
	if (ccartype == "��ѡ��")
	{
		MessageBox("��ѡ��������", "�����㵣");
		ifOK = false;
		return;
		//carType = "NULL";
	}
    // �жϱ����ֶ�
    if (enProvince == "" || enCity == "" || enCounty == "") {
        MessageBox("Ŀ�ĵز���Ϊ��", "�����㵣");
        ifOK = false;
        return;
    }

    if (weight == "") {
        MessageBox("��������Ϊ��", "�����㵣");
        ifOK = false;
        return;
    }

    if (tel == "") {
        MessageBox("��ϵ�绰����Ϊ��", "�����㵣");
        ifOK = false;
        return;
    }   

    // ����δ���ֶ�Ϊ "NULL"    
    if (syProvince == "") {
        syProvince = "NULL";
    } 

    if (syCity == "") {
        syCity = "NULL";
    } 

    CString tmp = stProvince + "|" + stCity + "|" + stCounty
            + "|" + enProvince + "|" + enCity + "|" + enCounty
            + "|" + name + "|" + weight + "|" + weightUnit
            + "|" + carType + "|" + tel + "|" + syProvince + "|" + syCity
            + "|" + rePubType;
                    
    if (ifRemRePub) {
        tmp = tmp + "|" + "1"; 
    } else {
        tmp = tmp + "|" + "0";
    }
                    
    if (ifLongTime) {
        tmp = tmp + "|" + "������Ч|"; 
    } else {
        tmp = tmp + "|" + "24Сʱ|";
    }

    /*if (ifUp) {
        tmp = tmp + "|" + "1"; 
    } else {
        tmp = tmp + "|" + "0";
    }*/
	//�������ݣ���ӵ�ĩβ��

	CString sText = preview;

	sText.Replace("|","");

	tmp += sText;
	
    if (ifOK) {    
        pubInf = (LPTSTR)(LPCTSTR)tmp;    
        OnOK();
    }
}
