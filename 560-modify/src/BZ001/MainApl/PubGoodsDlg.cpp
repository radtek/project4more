// PubGoodsDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "WLRClient.h"
#include "PubGoodsDlg.h"
#include "CommDef.h"


// CPubGoodsDlg 对话框

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
    
// 初始化
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
    // TODO:  在此添加额外的初始化
    // 初始化货物名称
	combName.AddString("请选择");	
	//--------------------------
	for ( n = 0; n < g_goodsType.size(); n++ )
	{
		combName.AddString(g_goodsType[n]);
	}

	/*combName.AddString("机械设备");
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
	combName.AddString("其他");*/
	combName.SetCurSel(0); 

	// 货物单位


	// 货物类型
	combType.AddString("请选择");
	//combType.AddString("重货");
	//combType.AddString("泡货");
	//combType.AddString("重泡");
	//--------------------------
	combType.AddString("整车");
	combType.AddString("零担");
	combType.AddString("重货");
	combType.AddString("泡货");
	combType.AddString("漂货");
	combType.AddString("普货");
	combType.SetCurSel(0);

	// 价格单位
	for ( n = 0; n < g_priceType.size(); n++ )
	{
		combPriceUnit.AddString(g_priceType[n]);
	}
	combPriceUnit.SetCurSel(0);

	/*combPriceUnit.AddString("元/吨");
	combPriceUnit.AddString("元/方");
	combPriceUnit.AddString("元");
	combPriceUnit.AddString("元/车");
	combPriceUnit.AddString("元/件");
	combPriceUnit.AddString("元/公斤");
	combPriceUnit.AddString("面议");
	combPriceUnit.AddString("高价急走");
	combPriceUnit.AddString("价格好说");
	combPriceUnit.AddString("给钱就走");*/
	//combPriceUnit.SetCurSel(0);

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
	for ( n = 0; n < g_truckType.size(); n++ )
	{
		combCarType.AddString(g_truckType[n]);
	}
	//combCarType.AddString("前四后十");
	//combCarType.AddString("前四后八");
	//combCarType.AddString("前四后四");
	//combCarType.AddString("半封闭车");
	//combCarType.AddString("敞篷车");
	//combCarType.AddString("平板车");
	//combCarType.AddString("高栏车");
	//combCarType.AddString("集装箱");
	//combCarType.AddString("冷藏车");
	//combCarType.AddString("后八轮");
	//combCarType.AddString("单桥车");
	//combCarType.AddString("自卸车");
	//combCarType.AddString("半挂车");
	//combCarType.AddString("保温车");
	//combCarType.AddString("双桥车");
	//combCarType.AddString("高低板");
	combCarType.SetCurSel(0);

	// 装货时间
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
	//
	//combLdgTime.AddString("明天");
	//combLdgTime.AddString("后天");
	//combLdgTime.AddString("3天以后");
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

// CPubGoodsDlg 消息处理程序
    
// 点击预览按钮
void CPubGoodsDlg::OnBnClickedPubGoodsPreviewBtn()
{
    // TODO: 在此添加控件通知处理程序代码
	UpdateData();

	CString cname,ctype,clen,ccartype,cprice;//货物种类，货物类型，车辆长度，车辆类型，价格类型

	combName.GetWindowText(cname);
	combType.GetWindowText(ctype);
	combCarLength.GetWindowText(clen);
	combCarType.GetWindowText(ccartype);
	combPriceUnit.GetWindowText(cprice);

	if (cname == "请选择")
	{
		MessageBox("请选择货物种类", "发布货源");
		return;
	}

	if (ctype == "请选择")
	{
		//MessageBox("请选择货物类型", "发布货源");
		//return;
		type = "";
	}

	if (clen == "请选择")
	{
		carLength = "";
		//MessageBox("请选择车辆长度", "发布货源");
		//return;
	}

	if (ccartype == "请选择")
	{
		//MessageBox("请选择车辆类型", "发布货源");
		//return;
		carType = "";
	}
	if (cprice == "" && price != "")
	{
		MessageBox("请选择价格类型", "发布货源");
		return;
	}

	if (cprice != "" && price == "")
	{
		MessageBox("价格不能为空", "发布货源");
		return;
	}
	/*if (price != "")
	{
		//if(cprice != "")
		{
			if (cprice == "给钱就走" || cprice == "价格好说" || cprice == "面议" || cprice == "高价急走" || cprice == "")
			{
				MessageBox("请选择价格类型", "发布货源");
				return;
			}
		}

	}

	if ( price == "")
	{
		if(cprice != "")
		{
			if (cprice != "给钱就走" && cprice != "价格好说" && cprice != "面议" && cprice != "高价急走")
			{
				MessageBox("价格不能为空", "发布货源");
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
		MessageBox("目的地不能为空", "发布货源");
		return;
	}

	/*
	//2011-12-28 取消重量非空限制
	if (weight == "" && cubage == "") {
		MessageBox("重量不能为空", "发布货源");
		return;
	}*/

	if (carNum == "") {
		//MessageBox("需车数量不能为空", "发布货源");
		//return;
	}

	if (tel == "") {
		MessageBox("联系电话不能为空", "发布货源");
		return;
	} 
	bPreview = TRUE;

	//preview = "【" + stProvince + stCity + stCounty
	//	    + "→" + enProvince + enCity + enCounty
	//		+ "】有货：" + name;
	preview = "有货：" + name;

	if (type != "")
	{
		 preview = preview + "（" + type + "），";
	}
	else
		preview = preview + "，";

	if (weight != "") {
		preview = preview + "重量：" + weight + "吨，";
	}
	if (cubage != "") {
		preview = preview + "体积：" + cubage + "方，";
	}
	if (priceUnit == "" && price == "")
	{
		//preview = preview + "价格：" + price + priceUnit + "，"
	} 
	else
	{
		preview = preview + "价格：" + price + priceUnit + "，";
	}

	preview = preview + "需要：" + carLength;

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
	UpdateData(FALSE);
}
    
// 响应点击下拉框：出发地省
void CPubGoodsDlg::OnCbnSelchangePubGoodsStprovince()
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
void CPubGoodsDlg::OnCbnSelchangePubGoodsStcity()
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
void CPubGoodsDlg::OnCbnSelchangePubGoodsEnprovince()
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
void CPubGoodsDlg::OnCbnSelchangePubGoodsEncity()
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
    
// 响应点击下拉框：同步发布省
/*void CPubGoodsDlg::OnCbnSelchangePubGoodsSyprovince()
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
}
*/
    
// 出发地列表框初始化
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
		if(0 == (*iter).name.compare(sStartProv)) { // 找到当前用户所在省
			int j = 0;
			vector<City>::iterator iter2 = (*iter).govCity.begin();
			while (iter2 != (*iter).govCity.end()) {
				combStCity.AddString((*iter2).name.c_str());
				if(0 == (*iter2).name.compare(sStartCity)) { // 找到当前用户所在市
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
    
// 初始化同时发布地
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
    
// 确定按钮
void CPubGoodsDlg::OnBnClickedOk()
{
    // TODO: 在此添加控件通知处理程序代码
    UpdateData();
    bool ifOK = true;

	if (!bPreview)
	{
		MessageBox("在发布前请先预览！", "发布货源");
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
    // 判断必填字段
	CString cname,ctype,clen,ccartype,cprice;//货物种类，货物类型，车辆长度，车辆类型，价格类型
		
	combName.GetWindowText(cname);
	combType.GetWindowText(ctype);
	combCarLength.GetWindowText(clen);
	combCarType.GetWindowText(ccartype);
	combPriceUnit.GetWindowText(cprice);

	if (cname == "请选择")
	{
		MessageBox("请选择货物种类", "发布货源");
		ifOK = false;
		return;
	}

	if (ctype == "请选择")
	{
		//MessageBox("请选择货物类型", "发布货源");
		//ifOK = false;
		//return;
		type = "普货";
	}

	if (clen == "请选择")
	{
		//MessageBox("请选择车辆长度", "发布货源");
		//ifOK = false;
		//return;
		carLength = "NULL";
	}

	if (ccartype == "请选择")
	{
		//MessageBox("请选择车辆类型", "发布货源");
		//ifOK = false;
		//return;
		carType = "NULL";
	}

	if (cprice == "")
	{
		//MessageBox("请选择价格类型", "发布货源");
		//ifOK = false;
		//return;
		priceUnit = "NULL";
	}

    if (enProvince == "" || enCity == "" || enCounty == "") {
        MessageBox("目的地不能为空", "发布货源");
        ifOK = false;
        return;
    }

	/*if (weight == "" && cubage == "") {
		//MessageBox("重量不能为空", "发布货源");
        //ifOK = false;
        //return;
    }*/

    if (carNum == "") {
		carNum = "NULL";
    }
	if (cprice == "" && price != "")
	{
		MessageBox("请选择价格类型");//, "发布货源");
		ifOK = false;
		return;
	}

	if (cprice != "" && price == "")
	{
		MessageBox("价格不能为空");//, "发布货源");
		ifOK = false;
		return;
	}

	if ( !CheckNumberString(weight) )
	{
		MessageBox("重量应为数字");
		ifOK = false;
		return;
	}

	if ( !CheckNumberString(cubage) )
	{
		MessageBox("体积应为数字");
		ifOK = false;
		return;
	}

	if ( !CheckNumberString(carNum) )
	{
		MessageBox("车辆数应为数字");
		ifOK = false;
		return;
	}

	/*if (price != "")
	{
		//if(cprice != "")
		{
			if (cprice == "给钱就走" || cprice == "价格好说" || cprice == "面议" || cprice == "高价急走" || cprice == "")
			{
				MessageBox("请选择价格类型", "发布货源");
				return;
			}
		}

	}

	if ( price == "")
	{
		if(cprice != "")
		{
			if (cprice != "给钱就走" && cprice != "价格好说" && cprice != "面议" && cprice != "高价急走")
			{
				MessageBox("价格不能为空", "发布货源");
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
        MessageBox("联系电话不能为空", "发布货源");
        ifOK = false;
        return;
    }   

    // 设置未填字段为 "NULL"    
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
        tmp = tmp + "|" + "一装多卸"; 
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
        tmp = tmp + "|" + "长期有效|"; 
    } else {
        tmp = tmp + "|" + "24小时|";
    }

	//发送内容
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
	// TODO: 在此添加控件通知处理程序代码
}
