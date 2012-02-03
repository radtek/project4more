// PubCarsDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "WLRClient.h"
#include "PubCarsDlg.h"


// CPubCarsDlg 对话框
// CPubCarsDlg 对话框

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
    
// 初始化
BOOL CPubCarsDlg::OnInitDialog()
{
    CDialog::OnInitDialog();
	m_msgedit.LimitText(100);
	((CEdit*)GetDlgItem(IDC_PUB_CARS_CARNUM))->LimitText(8);
	((CEdit*)GetDlgItem(IDC_PUB_CARS_WEIGHT))->LimitText(8);
	((CEdit*)GetDlgItem(IDC_PUB_CARS_CUBAGE))->LimitText(8);
    // TODO:  在此添加额外的初始化
    // 初始化货物名称
	combName.AddString("请选择");
	combName.AddString("机械设备");
	combName.AddString("电子产品");
	combName.AddString("日用百货");
	combName.AddString("衣料布匹");
	combName.AddString("农副产品");
	combName.AddString("水果蔬菜");
	combName.AddString("危险品");
	combName.AddString("家具");
	combName.AddString("建材");
	combName.AddString("冻品");
	combName.AddString("煤");
	combName.AddString("其他");
	combName.SetCurSel(0);

	// 货物类型
	combType.AddString("请选择");
	combType.AddString("重货");
	combType.AddString("泡货");
	combType.AddString("重泡");
	combType.SetCurSel(0);

	// 车长	
	combCarLength.AddString("请选择");
	combCarLength.AddString("17.5米");
	combCarLength.AddString("13.5米");
	combCarLength.AddString("13米");
	combCarLength.AddString("12.5米");
	combCarLength.AddString("9.6米");
	combCarLength.AddString("9米");
	combCarLength.AddString("8.8米");
	combCarLength.AddString("8.7米");
	combCarLength.AddString("8米");
	combCarLength.AddString("7.8米");
	combCarLength.AddString("7.4米");
	combCarLength.AddString("7.2米");
	combCarLength.AddString("7米");
	combCarLength.AddString("6.8米");
	combCarLength.AddString("6.2米");
	combCarLength.AddString("6米");
	combCarLength.AddString("5.8米");
	combCarLength.AddString("5米");
	combCarLength.AddString("4.8米");
	combCarLength.AddString("4.5米");
	combCarLength.AddString("4.3米");
	combCarLength.AddString("4.2米");
	combCarLength.AddString("4米");
	combCarLength.SetCurSel(0);

	// 车类型
	combCarType.AddString("请选择");
	combCarType.AddString("前四后十");
	combCarType.AddString("前四后八");
	combCarType.AddString("前四后四");
	combCarType.AddString("半封闭车");
	combCarType.AddString("敞篷车");
	combCarType.AddString("平板车");
	combCarType.AddString("高栏车");
	combCarType.AddString("集装箱");
	combCarType.AddString("冷藏车");
	combCarType.AddString("后八轮");
	combCarType.AddString("单桥车");
	combCarType.AddString("自卸车");
	combCarType.AddString("半挂车");
	combCarType.AddString("保温车");
	combCarType.AddString("双桥车");
	combCarType.AddString("高低板");
	combCarType.SetCurSel(0);

	// 发车时间
	combLdgTime.AddString("随时");
	CString str;
	//获取系统时间
	CTime tm = CTime::GetCurrentTime();
	for(int i=0; i<15; ++i) {
		//str=tm.Format("现在时间是%Y年%m月%d日 %X");
		//CTimeSpan( LONG lDays, int nHours, int nMins, int nSecs );
		CTime t2 = tm + CTimeSpan( i, 0, 0, 0 );
		str=t2.Format("%Y-%m-%d");
		combLdgTime.AddString(str);
	}
	combLdgTime.SetCurSel(0);

	// 重发设置
	combRePubType.AddString("不自动重发");
	combRePubType.AddString("10分钟2次");
	combRePubType.AddString("30分钟5次");
	combRePubType.AddString("2小时10次");
	combRePubType.SetCurSel(0);
    
    // 联系方式
    tel = userInfo.tel.c_str();
    UpdateData(false);

	initStartPoint();
	initEndPoint();
	//initSynPoint();

    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常: OCX 属性页应返回 FALSE
}

// CPubCarsDlg 消息处理程序
    
// 点击预览按钮
void CPubCarsDlg::OnBnClickedPubGoodsPreviewBtn()
{
    // TODO: 在此添加控件通知处理程序代码
	UpdateData();
	CString cname,ctype,clen,ccartype,cprice;//货物种类，货物类型，车辆长度，车辆类型，价格类型

	combName.GetWindowText(cname);
	combType.GetWindowText(ctype);
	combCarLength.GetWindowText(clen);
	combCarType.GetWindowText(ccartype);
	//combPriceUnit.GetWindowText(cprice);

	if (cname == "请选择")
	{
		MessageBox("请选择货物种类", "发布车源");
		return;
	}

	if (ctype == "请选择")
	{
		//MessageBox("请选择货物类型", "发布车源");
		//return;
		type = "";
	}

	if (clen == "请选择")
	{
		carLength = "";
		//MessageBox("请选择车辆长度", "发布车源");
		//return;
	}
	if (ccartype == "请选择")
	{
		//MessageBox("请选择车辆类型", "发布车源");
		//return;
		carType = "";
	}

	// 判断必填字段
	if (enProvince == "" || enCity == "" || enCounty == "") {
		MessageBox("目的地不能为空", "发布车源");
		return;
	}

	if (carNum == "") {
		//MessageBox("车数量不能为空", "发布车源");
		//return;
	}

	if (tel == "") {
		MessageBox("联系电话不能为空", "发布车源");
		return;
	} 
	if (weight == "" && cubage == "")
	{
		MessageBox("载重不能为空", "发布车源");
		return;
	}
	bPreview = TRUE;
// 
// 	preview = "【" + stProvince + stCity + stCounty
// 		    + "→" + enProvince + enCity + enCounty+"  "+ enProvince2 + enCity2 + enCounty2 +"  "+ enProvince3 + enCity3 + enCounty3 
// 			+"】有" + carLength;

	preview = "有" + carLength;

	if (carType != "")//车辆类型没填
	{
		preview+= "“" + carType + "”车";
	}
	else
		preview+= "车";

	if (carNum != "")//车辆数没填
	{
		preview += carNum + "辆。";
	}
	else
		preview += "。";


	if (weight != "") {
		preview = preview + "载重：" + weight + "吨。";
	}
	if (cubage != "") {
		preview = preview + "体积：" + cubage + "方。";
	}            
    
	preview = preview + "求货：" + name ;
	
	if (type != "")
	{
		preview = preview + "（" + type + "）。";
	}
	else
		preview = preview + "。";
	
	UpdateData(FALSE);
}
    
// 响应点击下拉框：出发地省
void CPubCarsDlg::OnCbnSelchangePubGoodsStprovince()
{
    // TODO: 在此添加控件通知处理程序代码
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
    
// 响应点击下拉框：出发地市
void CPubCarsDlg::OnCbnSelchangePubGoodsStcity()
{
    // TODO: 在此添加控件通知处理程序代码
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
    
// 响应点击下拉框：到达地省
void CPubCarsDlg::OnCbnSelchangePubGoodsEnprovince()
{
    // TODO: 在此添加控件通知处理程序代码
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
    
// 响应点击下拉框：到达地市
void CPubCarsDlg::OnCbnSelchangePubGoodsEncity()
{
    // TODO: 在此添加控件通知处理程序代码
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
 
// 响应点击下拉框：到达地省2
void CPubCarsDlg::OnCbnSelchangePubGoodsEnprovince2()
{
    // TODO: 在此添加控件通知处理程序代码
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
    
// 响应点击下拉框：到达地市2
void CPubCarsDlg::OnCbnSelchangePubGoodsEncity2()
{
    // TODO: 在此添加控件通知处理程序代码
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

// 响应点击下拉框：到达地省3
void CPubCarsDlg::OnCbnSelchangePubGoodsEnprovince3()
{
    // TODO: 在此添加控件通知处理程序代码
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
    
// 响应点击下拉框：到达地市3
void CPubCarsDlg::OnCbnSelchangePubGoodsEncity3()
{
    // TODO: 在此添加控件通知处理程序代码
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
// 响应点击下拉框：同步发布省
/*void CPubCarsDlg::OnCbnSelchangePubGoodsSyprovince()
{
    // TODO: 在此添加控件通知处理程序代码
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
    
// 出发地列表框初始化
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
		if(0 == (*iter).name.compare(userInfo.province)) { // 找到当前用户所在省
			int j = 0;
			vector<City>::iterator iter2 = (*iter).govCity.begin();
			while (iter2 != (*iter).govCity.end()) {
				combStCity.AddString((*iter2).name.c_str());
				if(0 == (*iter2).name.compare(userInfo.city)) { // 找到当前用户所在市
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
    
// 初始化目的地
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
    
// 初始化同时发布地
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
    
// 确定按钮
void CPubCarsDlg::OnBnClickedOk()
{
    // TODO: 在此添加控件通知处理程序代码
    UpdateData();
    bool ifOK = true;
	if (!bPreview)
	{
		MessageBox("在发布前请先预览！", "发布车源");
		ifOK = false;
		return;
	}
	if (preview == "")
	{
		MessageBox("预览不能为空！", "发布货源");
		ifOK = false;
		return;
	}
	bPreview = FALSE;
	CString cname,ctype,clen,ccartype,cprice;//货物种类，货物类型，车辆长度，车辆类型，价格类型

	combName.GetWindowText(cname);
	combType.GetWindowText(ctype);
	combCarLength.GetWindowText(clen);
	combCarType.GetWindowText(ccartype);
	//combPriceUnit.GetWindowText(cprice);

	if (cname == "请选择")
	{
		MessageBox("请选择货物种类", "发布车源");
		ifOK = false;
		return;
	}

	if (ctype == "请选择")
	{

		type = "NULL";
	}

	if (clen == "请选择")
	{
		//MessageBox("请选择车辆长度", "发布车源");
		//ifOK = false;
		//return;
		carLength = "NULL";
	}
	if (ccartype == "请选择")
	{
		//MessageBox("请选择车辆类型", "发布车源");
		//ifOK = false;
		//return;
		carType = "NULL";
	}
    // 判断必填字段
    if (enProvince == "" || enCity == "" || enCounty == "") {
        MessageBox("目的地不能为空", "发布车源");
        ifOK = false;
        return;
    }

    if (carNum == "") {
        //MessageBox("车数量不能为空", "发布车源");
       // ifOK = false;
       // return;
		carNum = "NULL";
    }

    if (tel == "") {
        MessageBox("联系电话不能为空", "发布车源");
        ifOK = false;
        return;
    }   
	if (weight == "" && cubage == "")
	{
		MessageBox("载重不能为空", "发布车源");
		ifOK = false;
		return;
	}
    // 设置未填字段为 "NULL"  
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
        tmp = tmp + "|" + "长期有效|"; 
    } else {
        tmp = tmp + "|" + "24小时|";
    }

    /*if (ifUp) {
        tmp = tmp + "|" + "1"; 
    } else {
        tmp = tmp + "|" + "0";
    }*/    

	//发送内容
	CString sText = preview;

	sText.Replace("|","");

	tmp += sText;


    if (ifOK) {    
        pubInf = (LPTSTR)(LPCTSTR)tmp;    
        OnOK();
    }
}
