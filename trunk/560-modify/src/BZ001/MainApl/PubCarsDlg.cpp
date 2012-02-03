// PubCarsDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WLRClient.h"
#include "PubCarsDlg.h"


// CPubCarsDlg �Ի���
// CPubCarsDlg �Ի���

IMPLEMENT_DYNAMIC(CPubCarsDlg, CDialog)

CPubCarsDlg::CPubCarsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPubCarsDlg::IDD, pParent)
    , stProvince(_T(""))
    , stCity(_T(""))
    , stCounty(_T(""))
    , enProvince(_T(""))
    , enCity(_T(""))
    , enCounty(_T(""))
    , enProvince2(_T(""))
    , enCity2(_T(""))
    , enCounty2(_T(""))
    , enProvince3(_T(""))
    , enCity3(_T(""))
    , enCounty3(_T(""))
    , name(_T(""))
    , weight(_T(""))
    , type(_T(""))
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
    //, ifUp(FALSE)
	, cubage(_T(""))
	, bPreview(FALSE)
{

}

CPubCarsDlg::~CPubCarsDlg()
{
}

void CPubCarsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PUB_CARS_STPROVINCE, combStProvince);
	DDX_CBString(pDX, IDC_PUB_CARS_STPROVINCE, stProvince);
	DDX_Control(pDX, IDC_PUB_CARS_STCITY, combStCity);
	DDX_CBString(pDX, IDC_PUB_CARS_STCITY, stCity);
	DDX_Control(pDX, IDC_PUB_CARS_STCOUNTY, combStCounty);
	DDX_CBString(pDX, IDC_PUB_CARS_STCOUNTY, stCounty);
	DDX_Control(pDX, IDC_PUB_CARS_ENPROVINCE, combEnProvince);
	DDX_CBString(pDX, IDC_PUB_CARS_ENPROVINCE, enProvince);
	DDX_Control(pDX, IDC_PUB_CARS_ENCITY, combEnCity);
	DDX_CBString(pDX, IDC_PUB_CARS_ENCITY, enCity);
	DDX_Control(pDX, IDC_PUB_CARS_ENCOUNTY, combEnCounty);
	DDX_CBString(pDX, IDC_PUB_CARS_ENCOUNTY, enCounty);
	DDX_Control(pDX, IDC_PUB_CARS_ENPROVINCE2, combEnProvince2);
	DDX_CBString(pDX, IDC_PUB_CARS_ENPROVINCE2, enProvince2);
	DDX_Control(pDX, IDC_PUB_CARS_ENCITY2, combEnCity2);
	DDX_CBString(pDX, IDC_PUB_CARS_ENCITY2, enCity2);
	DDX_Control(pDX, IDC_PUB_CARS_ENCOUNTY2, combEnCounty2);
	DDX_CBString(pDX, IDC_PUB_CARS_ENCOUNTY2, enCounty2);
	DDX_Control(pDX, IDC_PUB_CARS_ENPROVINCE3, combEnProvince3);
	DDX_CBString(pDX, IDC_PUB_CARS_ENPROVINCE3, enProvince3);
	DDX_Control(pDX, IDC_PUB_CARS_ENCITY3, combEnCity3);
	DDX_CBString(pDX, IDC_PUB_CARS_ENCITY3, enCity3);
	DDX_Control(pDX, IDC_PUB_CARS_ENCOUNTY3, combEnCounty3);
	DDX_CBString(pDX, IDC_PUB_CARS_ENCOUNTY3, enCounty3);
	DDX_Control(pDX, IDC_PUB_CARS_NAME, combName);
	DDX_CBString(pDX, IDC_PUB_CARS_NAME, name);
	DDX_Text(pDX, IDC_PUB_CARS_WEIGHT, weight);
	DDX_Control(pDX, IDC_PUB_CARS_TYPE, combType);
	DDX_CBString(pDX, IDC_PUB_CARS_TYPE, type);
	DDX_Control(pDX, IDC_PUB_CARS_CARLENGTH, combCarLength);
	DDX_CBString(pDX, IDC_PUB_CARS_CARLENGTH, carLength);
	DDX_Control(pDX, IDC_PUB_CARS_CARTYPE, combCarType);
	DDX_CBString(pDX, IDC_PUB_CARS_CARTYPE, carType);
	DDX_Text(pDX, IDC_PUB_CARS_CARNUM, carNum);
	DDX_Text(pDX, IDC_PUB_CARS_TEL, tel);
	DDX_Text(pDX, IDC_PUB_CARS_PREVIEW_EDIT, preview);
	//DDX_Control(pDX, IDC_PUB_CARS_SYPROVINCE, combSyProvince);
	//DDX_CBString(pDX, IDC_PUB_CARS_SYPROVINCE, syProvince);
	//DDX_Control(pDX, IDC_PUB_CARS_SYCITY, combSyCity);
	//DDX_CBString(pDX, IDC_PUB_CARS_SYCITY, syCity);
	DDX_Control(pDX, IDC_PUB_CARS_LDGTIME, combLdgTime);
	DDX_CBString(pDX, IDC_PUB_CARS_LDGTIME, ldgTime);
	DDX_Control(pDX, IDC_PUB_CARS_REPUBTYPE, combRePubType);
	DDX_CBString(pDX, IDC_PUB_CARS_REPUBTYPE, rePubType);
	DDX_Check(pDX, IDC_PUB_CARS_IFREMREPUB, ifRemRePub);
	DDX_Check(pDX, IDC_PUB_CARS_IFLONGTIME, ifLongTime);
	//DDX_Check(pDX, IDC_PUB_CARS_IFUP, ifUp);
	DDX_Text(pDX, IDC_PUB_CARS_CUBAGE, cubage);
	DDX_Control(pDX, IDC_PUB_CARS_PREVIEW_EDIT, m_msgedit);
}


BEGIN_MESSAGE_MAP(CPubCarsDlg, CDialog)
    ON_BN_CLICKED(IDC_PUB_CARS_PREVIEW_BTN, &CPubCarsDlg::OnBnClickedPubGoodsPreviewBtn)
    ON_CBN_SELCHANGE(IDC_PUB_CARS_STPROVINCE, &CPubCarsDlg::OnCbnSelchangePubGoodsStprovince)
    ON_CBN_SELCHANGE(IDC_PUB_CARS_STCITY, &CPubCarsDlg::OnCbnSelchangePubGoodsStcity)
    ON_CBN_SELCHANGE(IDC_PUB_CARS_ENPROVINCE, &CPubCarsDlg::OnCbnSelchangePubGoodsEnprovince)
    ON_CBN_SELCHANGE(IDC_PUB_CARS_ENCITY, &CPubCarsDlg::OnCbnSelchangePubGoodsEncity)
    ON_CBN_SELCHANGE(IDC_PUB_CARS_ENPROVINCE2, &CPubCarsDlg::OnCbnSelchangePubGoodsEnprovince2)
    ON_CBN_SELCHANGE(IDC_PUB_CARS_ENCITY2, &CPubCarsDlg::OnCbnSelchangePubGoodsEncity2)
    ON_CBN_SELCHANGE(IDC_PUB_CARS_ENPROVINCE3, &CPubCarsDlg::OnCbnSelchangePubGoodsEnprovince3)
    ON_CBN_SELCHANGE(IDC_PUB_CARS_ENCITY3, &CPubCarsDlg::OnCbnSelchangePubGoodsEncity3)
    //ON_CBN_SELCHANGE(IDC_PUB_CARS_SYPROVINCE, &CPubCarsDlg::OnCbnSelchangePubGoodsSyprovince)
    ON_BN_CLICKED(IDOK, &CPubCarsDlg::OnBnClickedOk)
END_MESSAGE_MAP()
    
// ��ʼ��
BOOL CPubCarsDlg::OnInitDialog()
{
    CDialog::OnInitDialog();
	m_msgedit.LimitText(100);
	((CEdit*)GetDlgItem(IDC_PUB_CARS_CARNUM))->LimitText(8);
	((CEdit*)GetDlgItem(IDC_PUB_CARS_WEIGHT))->LimitText(8);
	((CEdit*)GetDlgItem(IDC_PUB_CARS_CUBAGE))->LimitText(8);
    // TODO:  �ڴ���Ӷ���ĳ�ʼ��
    // ��ʼ����������
	combName.AddString("��ѡ��");
	combName.AddString("��е�豸");
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
	combName.AddString("����");
	combName.SetCurSel(0);

	// ��������
	combType.AddString("��ѡ��");
	combType.AddString("�ػ�");
	combType.AddString("�ݻ�");
	combType.AddString("����");
	combType.SetCurSel(0);

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
	combCarType.AddString("ǰ�ĺ�ʮ");
	combCarType.AddString("ǰ�ĺ��");
	combCarType.AddString("ǰ�ĺ���");
	combCarType.AddString("���ճ�");
	combCarType.AddString("����");
	combCarType.AddString("ƽ�峵");
	combCarType.AddString("������");
	combCarType.AddString("��װ��");
	combCarType.AddString("��س�");
	combCarType.AddString("�����");
	combCarType.AddString("���ų�");
	combCarType.AddString("��ж��");
	combCarType.AddString("��ҳ�");
	combCarType.AddString("���³�");
	combCarType.AddString("˫�ų�");
	combCarType.AddString("�ߵͰ�");
	combCarType.SetCurSel(0);

	// ����ʱ��
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

// CPubCarsDlg ��Ϣ�������
    
// ���Ԥ����ť
void CPubCarsDlg::OnBnClickedPubGoodsPreviewBtn()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	CString cname,ctype,clen,ccartype,cprice;//�������࣬�������ͣ��������ȣ��������ͣ��۸�����

	combName.GetWindowText(cname);
	combType.GetWindowText(ctype);
	combCarLength.GetWindowText(clen);
	combCarType.GetWindowText(ccartype);
	//combPriceUnit.GetWindowText(cprice);

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

	// �жϱ����ֶ�
	if (enProvince == "" || enCity == "" || enCounty == "") {
		MessageBox("Ŀ�ĵز���Ϊ��", "������Դ");
		return;
	}

	if (carNum == "") {
		//MessageBox("����������Ϊ��", "������Դ");
		//return;
	}

	if (tel == "") {
		MessageBox("��ϵ�绰����Ϊ��", "������Դ");
		return;
	} 
	if (weight == "" && cubage == "")
	{
		MessageBox("���ز���Ϊ��", "������Դ");
		return;
	}
	bPreview = TRUE;
// 
// 	preview = "��" + stProvince + stCity + stCounty
// 		    + "��" + enProvince + enCity + enCounty+"  "+ enProvince2 + enCity2 + enCounty2 +"  "+ enProvince3 + enCity3 + enCounty3 
// 			+"����" + carLength;

	preview = "��" + carLength;

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


	if (weight != "") {
		preview = preview + "���أ�" + weight + "�֡�";
	}
	if (cubage != "") {
		preview = preview + "�����" + cubage + "����";
	}            
    
	preview = preview + "�����" + name ;
	
	if (type != "")
	{
		preview = preview + "��" + type + "����";
	}
	else
		preview = preview + "��";
	
	UpdateData(FALSE);
}
    
// ��Ӧ��������򣺳�����ʡ
void CPubCarsDlg::OnCbnSelchangePubGoodsStprovince()
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
void CPubCarsDlg::OnCbnSelchangePubGoodsStcity()
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
void CPubCarsDlg::OnCbnSelchangePubGoodsEnprovince()
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
void CPubCarsDlg::OnCbnSelchangePubGoodsEncity()
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
 
// ��Ӧ��������򣺵����ʡ2
void CPubCarsDlg::OnCbnSelchangePubGoodsEnprovince2()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
	int index = combEnProvince2.GetCurSel();

	// Delete every other item from the combo box.
	while (combEnCity2.GetCount() > 0) {
		combEnCity2.DeleteString( 0 );
	}

	vector<City>::iterator iter = myCR->govProvince.at(index).govCity.begin();
	while (iter != myCR->govProvince.at(index).govCity.end()) {
		combEnCity2.AddString((*iter).name.c_str());
		++iter;
	}

	combEnCity2.SetCurSel(0);
	combEnCity2.UpdateData(FALSE);

	while (combEnCounty2.GetCount() > 0) {
		combEnCounty2.DeleteString( 0 );
	}
	vector<County>::iterator iter2 = myCR->govProvince.at(index).govCity.front().govCounty.begin();
	while (iter2 != myCR->govProvince.at(index).govCity.front().govCounty.end()) {
		combEnCounty2.AddString((*iter2).name.c_str());
		++iter2;
	}
	combEnCounty2.SetCurSel(0);
	combEnCounty2.UpdateData(FALSE);
}
    
// ��Ӧ��������򣺵������2
void CPubCarsDlg::OnCbnSelchangePubGoodsEncity2()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
	int indexSheng = combEnProvince2.GetCurSel();
	int indexShi = combEnCity2.GetCurSel();

	while (combEnCounty2.GetCount() > 0) {
		combEnCounty2.DeleteString( 0 );
	}
	vector<County>::iterator iter = 
		myCR->govProvince.at(indexSheng).govCity.at(indexShi).govCounty.begin();
	while (iter != myCR->govProvince.at(indexSheng).govCity.at(indexShi).govCounty.end()) {
		combEnCounty2.AddString((*iter).name.c_str());
		++iter;
	}

	combEnCounty2.SetCurSel(0);
	combEnCounty2.UpdateData(FALSE);
}

// ��Ӧ��������򣺵����ʡ3
void CPubCarsDlg::OnCbnSelchangePubGoodsEnprovince3()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
	int index = combEnProvince3.GetCurSel();

	// Delete every other item from the combo box.
	while (combEnCity3.GetCount() > 0) {
		combEnCity3.DeleteString( 0 );
	}

	vector<City>::iterator iter = myCR->govProvince.at(index).govCity.begin();
	while (iter != myCR->govProvince.at(index).govCity.end()) {
		combEnCity3.AddString((*iter).name.c_str());
		++iter;
	}

	combEnCity3.SetCurSel(0);
	combEnCity3.UpdateData(FALSE);

	while (combEnCounty3.GetCount() > 0) {
		combEnCounty3.DeleteString( 0 );
	}
	vector<County>::iterator iter2 = myCR->govProvince.at(index).govCity.front().govCounty.begin();
	while (iter2 != myCR->govProvince.at(index).govCity.front().govCounty.end()) {
		combEnCounty3.AddString((*iter2).name.c_str());
		++iter2;
	}
	combEnCounty3.SetCurSel(0);
	combEnCounty3.UpdateData(FALSE);
}
    
// ��Ӧ��������򣺵������3
void CPubCarsDlg::OnCbnSelchangePubGoodsEncity3()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
	int indexSheng = combEnProvince3.GetCurSel();
	int indexShi = combEnCity3.GetCurSel();

	while (combEnCounty3.GetCount() > 0) {
		combEnCounty3.DeleteString( 0 );
	}
	vector<County>::iterator iter = 
		myCR->govProvince.at(indexSheng).govCity.at(indexShi).govCounty.begin();
	while (iter != myCR->govProvince.at(indexSheng).govCity.at(indexShi).govCounty.end()) {
		combEnCounty3.AddString((*iter).name.c_str());
		++iter;
	}

	combEnCounty3.SetCurSel(0);
	combEnCounty3.UpdateData(FALSE);
}
// ��Ӧ���������ͬ������ʡ
/*void CPubCarsDlg::OnCbnSelchangePubGoodsSyprovince()
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
}*/
    
// �������б���ʼ��
int CPubCarsDlg::initStartPoint()
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
int CPubCarsDlg::initEndPoint()
{
    if (myCR == NULL) {
        return -1;
    }

    vector<Province>::iterator iter = myCR->govProvince.begin();
    while (iter != myCR->govProvince.end()) {
		combEnProvince.AddString((*iter).name.c_str());
        ++iter;
    }

    iter = myCR->govProvince.begin();
    while (iter != myCR->govProvince.end()) {
		combEnProvince2.AddString((*iter).name.c_str());
        ++iter;
    }

    iter = myCR->govProvince.begin();
    while (iter != myCR->govProvince.end()) {
		combEnProvince3.AddString((*iter).name.c_str());
        ++iter;
    }

	return 0;
}
    
// ��ʼ��ͬʱ������
/*int CPubCarsDlg::initSynPoint()
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
void CPubCarsDlg::OnBnClickedOk()
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
	CString cname,ctype,clen,ccartype,cprice;//�������࣬�������ͣ��������ȣ��������ͣ��۸�����

	combName.GetWindowText(cname);
	combType.GetWindowText(ctype);
	combCarLength.GetWindowText(clen);
	combCarType.GetWindowText(ccartype);
	//combPriceUnit.GetWindowText(cprice);

	if (cname == "��ѡ��")
	{
		MessageBox("��ѡ���������", "������Դ");
		ifOK = false;
		return;
	}

	if (ctype == "��ѡ��")
	{

		type = "NULL";
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
    // �жϱ����ֶ�
    if (enProvince == "" || enCity == "" || enCounty == "") {
        MessageBox("Ŀ�ĵز���Ϊ��", "������Դ");
        ifOK = false;
        return;
    }

    if (carNum == "") {
        //MessageBox("����������Ϊ��", "������Դ");
       // ifOK = false;
       // return;
		carNum = "NULL";
    }

    if (tel == "") {
        MessageBox("��ϵ�绰����Ϊ��", "������Դ");
        ifOK = false;
        return;
    }   
	if (weight == "" && cubage == "")
	{
		MessageBox("���ز���Ϊ��", "������Դ");
		ifOK = false;
		return;
	}
    // ����δ���ֶ�Ϊ "NULL"  
    if (weight == "") {
        weight = "NULL";
    }
    if (cubage == "") {
        cubage = "NULL";
    }


    CString tmp = stProvince + "|" + stCity + "|" + stCounty
                + "|" + enProvince + "|" + enCity + "|" + enCounty
				+ "|" + enProvince2 + "|" + enCity2 + "|" + enCounty2
				+ "|" + enProvince3 + "|" + enCity3 + "|" + enCounty3
                + "|" + carNum + "|" + weight + "|" + cubage + "|" + carLength + "|" + carType 
                + "|" + name + "|" + type + "|" + tel + "|" + ldgTime + "|" + rePubType;
                    
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

	//��������
	CString sText = preview;

	sText.Replace("|","");

	tmp += sText;


    if (ifOK) {    
        pubInf = (LPTSTR)(LPCTSTR)tmp;    
        OnOK();
    }
}
