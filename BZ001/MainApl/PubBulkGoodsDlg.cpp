// PubBulkGoodsDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "WLRClient.h"
#include "PubBulkGoodsDlg.h"


// CPubBulkGoodsDlg 对话框

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
    
// 初始化
BOOL CPubBulkGoodsDlg::OnInitDialog()
{
    CDialog::OnInitDialog();
	m_msgedit.LimitText(100);
    // TODO:  在此添加额外的初始化
    // 初始化货物名称
	combName.AddString("请选择");
	combName.AddString("建材");
	combName.AddString("家具木材");
	combName.AddString("粮食");
	combName.AddString("蔬菜");
	combName.AddString("水果");
	combName.AddString("农副产品");
	combName.AddString("食品");
	combName.AddString("冻品");
	combName.AddString("纸品");
	combName.AddString("衣料");
	combName.AddString("百货");
	combName.AddString("矿石");
	combName.AddString("煤");
	combName.AddString("化工");
	combName.AddString("医药");
	combName.AddString("机械设备");
	combName.AddString("危险品");
	combName.AddString("其它");
	combName.SetCurSel(0);

	// 货物单位
    combWeightUnit.AddString("公斤");
	combWeightUnit.AddString("吨");
	combWeightUnit.AddString("立方");
	combWeightUnit.AddString("车");
	combWeightUnit.AddString("件");
	combWeightUnit.SetCurSel(0);

	// 车类型
	combCarType.AddString("请选择");
	//combCarType.AddString("普通车");
	combCarType.AddString("前四后十");
	combCarType.AddString("前四后八");
	combCarType.AddString("前四后四");
	combCarType.AddString("半封闭车");
	combCarType.AddString("敞篷车");
	combCarType.AddString("平板车");
	combCarType.AddString("高栏车");
	combCarType.AddString("集装箱");
	combCarType.AddString("冷藏车");
//	combCarType.AddString("起重车");
	combCarType.AddString("后八轮");
	combCarType.AddString("单桥车");
	combCarType.AddString("自卸车");

	combCarType.AddString("半挂车");
	combCarType.AddString("保温车");
	combCarType.AddString("双桥车");
//	combCarType.AddString("加长挂车");
//	combCarType.AddString("棉被车");
//	combCarType.AddString("大笼子车");
	combCarType.AddString("高低板");
//	combCarType.AddString("翻斗车");
	combCarType.SetCurSel(0);

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
	initSynPoint();

    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常: OCX 属性页应返回 FALSE
}

// CPubBulkGoodsDlg 消息处理程序
    
// 点击预览按钮
void CPubBulkGoodsDlg::OnBnClickedPubGoodsPreviewBtn()
{
    // TODO: 在此添加控件通知处理程序代码
	UpdateData();
	CString cname,ctype,clen,ccartype,cprice;//货物种类，货物类型，车辆长度，车辆类型，价格类型

	combName.GetWindowText(cname);
	combCarType.GetWindowText(ccartype);
	if (cname == "请选择")
	{
		MessageBox("请选择货物种类", "发布零担");
		return;
	}
	if (ccartype == "请选择")
	{
		MessageBox("请选择车辆类型", "发布零担");
		return;
		//carType = "NULL";
	}
	// 判断必填字段
	if (enProvince == "" || enCity == "" || enCounty == "") {
		MessageBox("目的地不能为空", "发布零担");
		return;
	}
	
	if (weight == "") {
		MessageBox("重量不能为空", "发布零担");
		
		return;
	}

	if (tel == "") {
		MessageBox("联系电话不能为空", "发布零担");
		return;
	} 
 	bPreview = TRUE;
// 
// 	preview = stProvince + stCity + stCounty	
// 			+ "→〖" + enProvince + enCity + enCounty
// 			+ "〗有" + name + weight + weightUnit			
// 			+ "，需：" + carType;

	preview = "有货：" + name +"，重量："+ weight + weightUnit			
		+ "，需要" + carType;

	UpdateData(FALSE);
}
    
// 响应点击下拉框：出发地省
void CPubBulkGoodsDlg::OnCbnSelchangePubGoodsStprovince()
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
void CPubBulkGoodsDlg::OnCbnSelchangePubGoodsStcity()
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
void CPubBulkGoodsDlg::OnCbnSelchangePubGoodsEnprovince()
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
void CPubBulkGoodsDlg::OnCbnSelchangePubGoodsEncity()
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
void CPubBulkGoodsDlg::OnCbnSelchangePubGoodsSyprovince()
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
    
// 出发地列表框初始化
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
    
// 初始化同时发布地
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
    
// 确定按钮
void CPubBulkGoodsDlg::OnBnClickedOk()
{
    // TODO: 在此添加控件通知处理程序代码
    UpdateData();
    bool ifOK = true;
	if (!bPreview)
	{
		MessageBox("在发布前请先预览！", "发布零担");
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
	combCarType.GetWindowText(ccartype);
	if (cname == "请选择")
	{
		MessageBox("请选择货物种类", "发布零担");
		ifOK = false;
		return;
	}
	if (ccartype == "请选择")
	{
		MessageBox("请选择车辆类型", "发布零担");
		ifOK = false;
		return;
		//carType = "NULL";
	}
    // 判断必填字段
    if (enProvince == "" || enCity == "" || enCounty == "") {
        MessageBox("目的地不能为空", "发布零担");
        ifOK = false;
        return;
    }

    if (weight == "") {
        MessageBox("重量不能为空", "发布零担");
        ifOK = false;
        return;
    }

    if (tel == "") {
        MessageBox("联系电话不能为空", "发布零担");
        ifOK = false;
        return;
    }   

    // 设置未填字段为 "NULL"    
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
        tmp = tmp + "|" + "长期有效|"; 
    } else {
        tmp = tmp + "|" + "24小时|";
    }

    /*if (ifUp) {
        tmp = tmp + "|" + "1"; 
    } else {
        tmp = tmp + "|" + "0";
    }*/
	//发送内容（添加到末尾）

	CString sText = preview;

	sText.Replace("|","");

	tmp += sText;
	
    if (ifOK) {    
        pubInf = (LPTSTR)(LPCTSTR)tmp;    
        OnOK();
    }
}
