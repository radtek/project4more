// PubGoodsDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WLRClient.h"
#include "PubGoodsDlg.h"
#include "CommDef.h"


// CPubGoodsDlg �Ի���

IMPLEMENT_DYNAMIC(CPubGoodsDlg, CDialog)

CPubGoodsDlg::CPubGoodsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPubGoodsDlg::IDD, pParent)
    , stProvince(_T(""))
    , stCity(_T(""))
    , stCounty(_T(""))
    , enProvince(_T(""))
    , enCity(_T(""))
    , enCounty(_T(""))
    , name(_T(""))
    , weight(_T(""))
    //, weightUnit(_T(""))
	, cubage(_T(""))
    , type(_T(""))
    , price(_T(""))
    , priceUnit(_T(""))
    , ifYzdx(FALSE)
    , carLength(_T(""))
    , carType(_T(""))
    , carNum(_T("1"))
    , tel(_T(""))
    , preview(_T(""))
    //, syProvince(_T(""))
    //, syCity(_T(""))
    , ldgTime(_T(""))
    , rePubType(_T(""))
    , ifRemRePub(FALSE)
    , ifLongTime(FALSE)
	, bPreview(FALSE)
    //, ifUp(FALSE)
{

}

CPubGoodsDlg::~CPubGoodsDlg()
{
}

void CPubGoodsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PUB_GOODS_STPROVINCE, combStProvince);
	DDX_CBString(pDX, IDC_PUB_GOODS_STPROVINCE, stProvince);
	DDX_Control(pDX, IDC_PUB_GOODS_STCITY, combStCity);
	DDX_CBString(pDX, IDC_PUB_GOODS_STCITY, stCity);
	DDX_Control(pDX, IDC_PUB_GOODS_STCOUNTY, combStCounty);
	DDX_CBString(pDX, IDC_PUB_GOODS_STCOUNTY, stCounty);
	DDX_Control(pDX, IDC_PUB_GOODS_ENPROVINCE, combEnProvince);
	DDX_CBString(pDX, IDC_PUB_GOODS_ENPROVINCE, enProvince);
	DDX_Control(pDX, IDC_PUB_GOODS_ENCITY, combEnCity);
	DDX_CBString(pDX, IDC_PUB_GOODS_ENCITY, enCity);
	DDX_Control(pDX, IDC_PUB_GOODS_ENCOUNTY, combEnCounty);
	DDX_CBString(pDX, IDC_PUB_GOODS_ENCOUNTY, enCounty);
	DDX_Control(pDX, IDC_PUB_GOODS_NAME, combName);
	DDX_CBString(pDX, IDC_PUB_GOODS_NAME, name);
	DDX_Text(pDX, IDC_PUB_GOODS_WEIGHT, weight);
	//DDX_Control(pDX, IDC_PUB_GOODS_WEIGHTUNIT, combWeightUnit);
	//DDX_CBString(pDX, IDC_PUB_GOODS_WEIGHTUNIT, weightUnit);
	DDX_Control(pDX, IDC_PUB_GOODS_TYPE, combType);
	DDX_CBString(pDX, IDC_PUB_GOODS_TYPE, type);
	DDX_Text(pDX, IDC_PUB_GOODS_PRICE, price);
	DDX_Control(pDX, IDC_PUB_GOODS_PRICEUNIT, combPriceUnit);
	DDX_CBString(pDX, IDC_PUB_GOODS_PRICEUNIT, priceUnit);
	DDX_Check(pDX, IDC_PUB_GOODS_IFYZDX, ifYzdx);
	DDX_Control(pDX, IDC_PUB_GOODS_CARLENGTH, combCarLength);
	DDX_CBString(pDX, IDC_PUB_GOODS_CARLENGTH, carLength);
	DDX_Control(pDX, IDC_PUB_GOODS_CARTYPE, combCarType);
	DDX_CBString(pDX, IDC_PUB_GOODS_CARTYPE, carType);
	DDX_Text(pDX, IDC_PUB_GOODS_CARNUM, carNum);
	DDX_Text(pDX, IDC_PUB_GOODS_TEL, tel);
	DDX_Text(pDX, IDC_PUB_GOODS_PREVIEW_EDIT, preview);
	//DDX_Control(pDX, IDC_PUB_GOODS_SYPROVINCE, combSyProvince);
	//DDX_CBString(pDX, IDC_PUB_GOODS_SYPROVINCE, syProvince);
	//DDX_Control(pDX, IDC_PUB_GOODS_SYCITY, combSyCity);
	//DDX_CBString(pDX, IDC_PUB_GOODS_SYCITY, syCity);
	DDX_Control(pDX, IDC_PUB_GOODS_LDGTIME, combLdgTime);
	DDX_CBString(pDX, IDC_PUB_GOODS_LDGTIME, ldgTime);
	DDX_Control(pDX, IDC_PUB_GOODS_REPUBTYPE, combRePubType);
	DDX_CBString(pDX, IDC_PUB_GOODS_REPUBTYPE, rePubType);
	DDX_Check(pDX, IDC_PUB_GOODS_IFREMREPUB, ifRemRePub);
	DDX_Check(pDX, IDC_PUB_GOODS_IFLONGTIME, ifLongTime);
	//DDX_Check(pDX, IDC_PUB_GOODS_IFUP, ifUp);
	DDX_Text(pDX, IDC_PUB_GOODS_CUBAGE, cubage);
	//DDV_MaxChars(pDX, preview, 100);
	DDX_Control(pDX, IDC_PUB_GOODS_PREVIEW_EDIT, m_msgedit);
	//DDV_MaxChars(pDX, weight, 8);
	//DDV_MaxChars(pDX, cubage, 8);
	//DDV_MaxChars(pDX, price, 8);
}


BEGIN_MESSAGE_MAP(CPubGoodsDlg, CDialog)
    ON_BN_CLICKED(IDC_PUB_GOODS_PREVIEW_BTN, &CPubGoodsDlg::OnBnClickedPubGoodsPreviewBtn)
    ON_CBN_SELCHANGE(IDC_PUB_GOODS_STPROVINCE, &CPubGoodsDlg::OnCbnSelchangePubGoodsStprovince)
    ON_CBN_SELCHANGE(IDC_PUB_GOODS_STCITY, &CPubGoodsDlg::OnCbnSelchangePubGoodsStcity)
    ON_CBN_SELCHANGE(IDC_PUB_GOODS_ENPROVINCE, &CPubGoodsDlg::OnCbnSelchangePubGoodsEnprovince)
    ON_CBN_SELCHANGE(IDC_PUB_GOODS_ENCITY, &CPubGoodsDlg::OnCbnSelchangePubGoodsEncity)
    //ON_CBN_SELCHANGE(IDC_PUB_GOODS_SYPROVINCE, &CPubGoodsDlg::OnCbnSelchangePubGoodsSyprovince)
    ON_BN_CLICKED(IDOK, &CPubGoodsDlg::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_PUB_GOODS_NAME, &CPubGoodsDlg::OnCbnSelchangePubGoodsName)
END_MESSAGE_MAP()
    
// ��ʼ��
BOOL CPubGoodsDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

	((CEdit*)GetDlgItem(IDC_PUB_GOODS_WEIGHT))->SetLimitText(8);
	((CEdit*)GetDlgItem(IDC_PUB_GOODS_CUBAGE))->SetLimitText(8);
	((CEdit*)GetDlgItem(IDC_PUB_GOODS_PRICE))->SetLimitText(8);

	((CEdit*)GetDlgItem(IDC_PUB_GOODS_CARNUM))->SetLimitText(8);
	((CEdit*)GetDlgItem(IDC_PUB_GOODS_PREVIEW_EDIT))->SetLimitText(100);


	int n = 0;
	m_msgedit.SetLimitText(100);
    // TODO:  �ڴ���Ӷ���ĳ�ʼ��
    // ��ʼ����������
	combName.AddString("��ѡ��");	
	//--------------------------
	for ( n = 0; n < g_goodsType.size(); n++ )
	{
		combName.AddString(g_goodsType[n]);
	}

	/*combName.AddString("��е�豸");
	combName.AddString("���Ӳ�Ʒ");
	combName.AddString("���ðٻ�");
	combName.AddString("���ϲ�ƥ");
	combName.AddString("ũ����Ʒ");
	combName.AddString("ˮ���߲�");
	combName.AddString("Σ��Ʒ");
	combName.AddString("�Ҿ�");
	combName.AddString("����");
	combName.AddString("��Ʒ");
	combName.AddString("ú");
	combName.AddString("����");*/
	combName.SetCurSel(0); 

	// ���ﵥλ


	// ��������
	combType.AddString("��ѡ��");
	//combType.AddString("�ػ�");
	//combType.AddString("�ݻ�");
	//combType.AddString("����");
	//--------------------------
	combType.AddString("����");
	combType.AddString("�㵣");
	combType.AddString("�ػ�");
	combType.AddString("�ݻ�");
	combType.AddString("Ư��");
	combType.AddString("�ջ�");
	combType.SetCurSel(0);

	// �۸�λ
	for ( n = 0; n < g_priceType.size(); n++ )
	{
		combPriceUnit.AddString(g_priceType[n]);
	}
	combPriceUnit.SetCurSel(0);

	/*combPriceUnit.AddString("Ԫ/��");
	combPriceUnit.AddString("Ԫ/��");
	combPriceUnit.AddString("Ԫ");
	combPriceUnit.AddString("Ԫ/��");
	combPriceUnit.AddString("Ԫ/��");
	combPriceUnit.AddString("Ԫ/����");
	combPriceUnit.AddString("����");
	combPriceUnit.AddString("�߼ۼ���");
	combPriceUnit.AddString("�۸��˵");
	combPriceUnit.AddString("��Ǯ����");*/
	//combPriceUnit.SetCurSel(0);

	// ����	
	combCarLength.AddString("��ѡ��");
	combCarLength.AddString("17.5��");
	combCarLength.AddString("13.5��");
	combCarLength.AddString("13��");
	combCarLength.AddString("12.5��");
	combCarLength.AddString("9.6��");
	combCarLength.AddString("9��");
	combCarLength.AddString("8.8��");
	combCarLength.AddString("8.7��");
	combCarLength.AddString("8��");
	combCarLength.AddString("7.8��");
	combCarLength.AddString("7.4��");
	combCarLength.AddString("7.2��");
	combCarLength.AddString("7��");
	combCarLength.AddString("6.8��");
	combCarLength.AddString("6.2��");
	combCarLength.AddString("6��");
	combCarLength.AddString("5.8��");
	combCarLength.AddString("5��");
	combCarLength.AddString("4.8��");
	combCarLength.AddString("4.5��");
	combCarLength.AddString("4.3��");
	combCarLength.AddString("4.2��");
	combCarLength.AddString("4��");
	combCarLength.SetCurSel(0);

	// ������
	combCarType.AddString("��ѡ��");
	for ( n = 0; n < g_truckType.size(); n++ )
	{
		combCarType.AddString(g_truckType[n]);
	}
	//combCarType.AddString("ǰ�ĺ�ʮ");
	//combCarType.AddString("ǰ�ĺ��");
	//combCarType.AddString("ǰ�ĺ���");
	//combCarType.AddString("���ճ�");
	//combCarType.AddString("����");
	//combCarType.AddString("ƽ�峵");
	//combCarType.AddString("������");
	//combCarType.AddString("��װ��");
	//combCarType.AddString("��س�");
	//combCarType.AddString("�����");
	//combCarType.AddString("���ų�");
	//combCarType.AddString("��ж��");
	//combCarType.AddString("��ҳ�");
	//combCarType.AddString("���³�");
	//combCarType.AddString("˫�ų�");
	//combCarType.AddString("�ߵͰ�");
	combCarType.SetCurSel(0);

	// װ��ʱ��
	combLdgTime.AddString("��ʱ");
	CString str;
	//��ȡϵͳʱ��
	CTime tm = CTime::GetCurrentTime();
	for(int i=0; i<15; ++i) {
		//str=tm.Format("����ʱ����%Y��%m��%d�� %X");
		//CTimeSpan( LONG lDays, int nHours, int nMins, int nSecs );
		CTime t2 = tm + CTimeSpan( i, 0, 0, 0 );
		str=t2.Format("%Y-%m-%d");
		combLdgTime.AddString(str);
	}
	//
	//combLdgTime.AddString("����");
	//combLdgTime.AddString("����");
	//combLdgTime.AddString("3���Ժ�");
	combLdgTime.SetCurSel(0);

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
	//initSynPoint();

    return TRUE;  // return TRUE unless you set the focus to a control
    // �쳣: OCX ����ҳӦ���� FALSE
}

// CPubGoodsDlg ��Ϣ�������
    
// ���Ԥ����ť
void CPubGoodsDlg::OnBnClickedPubGoodsPreviewBtn()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();

	CString cname,ctype,clen,ccartype,cprice;//�������࣬�������ͣ��������ȣ��������ͣ��۸�����

	combName.GetWindowText(cname);
	combType.GetWindowText(ctype);
	combCarLength.GetWindowText(clen);
	combCarType.GetWindowText(ccartype);
	combPriceUnit.GetWindowText(cprice);

	if (cname == "��ѡ��")
	{
		MessageBox("��ѡ���������", "������Դ");
		return;
	}

	if (ctype == "��ѡ��")
	{
		//MessageBox("��ѡ���������", "������Դ");
		//return;
		type = "";
	}

	if (clen == "��ѡ��")
	{
		carLength = "";
		//MessageBox("��ѡ��������", "������Դ");
		//return;
	}

	if (ccartype == "��ѡ��")
	{
		//MessageBox("��ѡ��������", "������Դ");
		//return;
		carType = "";
	}
	if (cprice == "" && price != "")
	{
		MessageBox("��ѡ��۸�����", "������Դ");
		return;
	}

	if (cprice != "" && price == "")
	{
		MessageBox("�۸���Ϊ��", "������Դ");
		return;
	}
	/*if (price != "")
	{
		//if(cprice != "")
		{
			if (cprice == "��Ǯ����" || cprice == "�۸��˵" || cprice == "����" || cprice == "�߼ۼ���" || cprice == "")
			{
				MessageBox("��ѡ��۸�����", "������Դ");
				return;
			}
		}

	}

	if ( price == "")
	{
		if(cprice != "")
		{
			if (cprice != "��Ǯ����" && cprice != "�۸��˵" && cprice != "����" && cprice != "�߼ۼ���")
			{
				MessageBox("�۸���Ϊ��", "������Դ");
				return;
			}
		}
	}*/

	if (cprice == "" && price == "")
	{
		priceUnit = "";
		price = "";
	}
	if (enProvince == "" || enCity == "" || enCounty == "") {
		MessageBox("Ŀ�ĵز���Ϊ��", "������Դ");
		return;
	}

	/*
	//2011-12-28 ȡ�������ǿ�����
	if (weight == "" && cubage == "") {
		MessageBox("��������Ϊ��", "������Դ");
		return;
	}*/

	if (carNum == "") {
		//MessageBox("�賵��������Ϊ��", "������Դ");
		//return;
	}

	if (tel == "") {
		MessageBox("��ϵ�绰����Ϊ��", "������Դ");
		return;
	} 
	bPreview = TRUE;

	//preview = "��" + stProvince + stCity + stCounty
	//	    + "��" + enProvince + enCity + enCounty
	//		+ "���л���" + name;
	preview = "�л���" + name;

	if (type != "")
	{
		 preview = preview + "��" + type + "����";
	}
	else
		preview = preview + "��";

	if (weight != "") {
		preview = preview + "������" + weight + "�֣�";
	}
	if (cubage != "") {
		preview = preview + "�����" + cubage + "����";
	}
	if (priceUnit == "" && price == "")
	{
		//preview = preview + "�۸�" + price + priceUnit + "��"
	} 
	else
	{
		preview = preview + "�۸�" + price + priceUnit + "��";
	}

	preview = preview + "��Ҫ��" + carLength;

	if (carType != "")//��������û��
	{
		preview+= "��" + carType + "����";
	}
	else
		preview+= "��";

	if (carNum != "")//������û��
	{
		preview += carNum + "����";
	}
	else
		preview += "��";
	UpdateData(FALSE);
}
    
// ��Ӧ��������򣺳�����ʡ
void CPubGoodsDlg::OnCbnSelchangePubGoodsStprovince()
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
void CPubGoodsDlg::OnCbnSelchangePubGoodsStcity()
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
void CPubGoodsDlg::OnCbnSelchangePubGoodsEnprovince()
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
void CPubGoodsDlg::OnCbnSelchangePubGoodsEncity()
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
/*void CPubGoodsDlg::OnCbnSelchangePubGoodsSyprovince()
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
*/
    
// �������б���ʼ��
int CPubGoodsDlg::initStartPoint()
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
int CPubGoodsDlg::initEndPoint()
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
/*int CPubGoodsDlg::initSynPoint()
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
}*/
    
// ȷ����ť
void CPubGoodsDlg::OnBnClickedOk()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    UpdateData();
    bool ifOK = true;

	if (!bPreview)
	{
		MessageBox("�ڷ���ǰ����Ԥ����", "������Դ");
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
    // �жϱ����ֶ�
	CString cname,ctype,clen,ccartype,cprice;//�������࣬�������ͣ��������ȣ��������ͣ��۸�����
		
	combName.GetWindowText(cname);
	combType.GetWindowText(ctype);
	combCarLength.GetWindowText(clen);
	combCarType.GetWindowText(ccartype);
	combPriceUnit.GetWindowText(cprice);

	if (cname == "��ѡ��")
	{
		MessageBox("��ѡ���������", "������Դ");
		ifOK = false;
		return;
	}

	if (ctype == "��ѡ��")
	{
		//MessageBox("��ѡ���������", "������Դ");
		//ifOK = false;
		//return;
		type = "�ջ�";
	}

	if (clen == "��ѡ��")
	{
		//MessageBox("��ѡ��������", "������Դ");
		//ifOK = false;
		//return;
		carLength = "NULL";
	}

	if (ccartype == "��ѡ��")
	{
		//MessageBox("��ѡ��������", "������Դ");
		//ifOK = false;
		//return;
		carType = "NULL";
	}

	if (cprice == "")
	{
		//MessageBox("��ѡ��۸�����", "������Դ");
		//ifOK = false;
		//return;
		priceUnit = "NULL";
	}

    if (enProvince == "" || enCity == "" || enCounty == "") {
        MessageBox("Ŀ�ĵز���Ϊ��", "������Դ");
        ifOK = false;
        return;
    }

	/*if (weight == "" && cubage == "") {
		//MessageBox("��������Ϊ��", "������Դ");
        //ifOK = false;
        //return;
    }*/

    if (carNum == "") {
		carNum = "NULL";
    }
	if (cprice == "" && price != "")
	{
		MessageBox("��ѡ��۸�����");//, "������Դ");
		ifOK = false;
		return;
	}

	if (cprice != "" && price == "")
	{
		MessageBox("�۸���Ϊ��");//, "������Դ");
		ifOK = false;
		return;
	}

	if ( !CheckNumberString(weight) )
	{
		MessageBox("����ӦΪ����");
		ifOK = false;
		return;
	}

	if ( !CheckNumberString(cubage) )
	{
		MessageBox("���ӦΪ����");
		ifOK = false;
		return;
	}

	if ( !CheckNumberString(carNum) )
	{
		MessageBox("������ӦΪ����");
		ifOK = false;
		return;
	}

	/*if (price != "")
	{
		//if(cprice != "")
		{
			if (cprice == "��Ǯ����" || cprice == "�۸��˵" || cprice == "����" || cprice == "�߼ۼ���" || cprice == "")
			{
				MessageBox("��ѡ��۸�����", "������Դ");
				return;
			}
		}

	}

	if ( price == "")
	{
		if(cprice != "")
		{
			if (cprice != "��Ǯ����" && cprice != "�۸��˵" && cprice != "����" && cprice != "�߼ۼ���")
			{
				MessageBox("�۸���Ϊ��", "������Դ");
				return;
			}
			else
				price = "NULL";
		}
	}*/
	if (cprice == "" && price == "")
	{
		priceUnit = "NULL";
		price = "NULL";
	}


    if (tel == "") {
        MessageBox("��ϵ�绰����Ϊ��", "������Դ");
        ifOK = false;
        return;
    }   

    // ����δ���ֶ�Ϊ "NULL"    
    if (price == "") {
        price = "NULL";
    } 

	if (weight == "") {
        weight = "NULL";
    } 

    if (cubage == "") {
        cubage = "NULL";
    }

    CString tmp = stProvince + "|" + stCity + "|" + stCounty
                + "|" + enProvince + "|" + enCity + "|" + enCounty
                + "|" + name + "|" + weight + "|" + cubage
                + "|" + type + "|" + price + "|" + priceUnit;
                    
    if (ifYzdx) {
        tmp = tmp + "|" + "һװ��ж"; 
    } else {
        tmp = tmp + "|" + "NULL";
    }
                    
    tmp = tmp + "|" + carLength + "|" + carType + "|" + carNum
        + "|" + tel + "|" + ldgTime + "|" + rePubType;
                    
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

	//��������
	CString sText = preview;

	sText.Replace("|","");

	tmp += sText;

    if (ifOK) {    
        pubInf = (LPTSTR)(LPCTSTR)tmp;    
        OnOK();
    }
}

void CPubGoodsDlg::OnCbnSelchangePubGoodsName()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
