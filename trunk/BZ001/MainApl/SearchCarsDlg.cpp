// SearchCarsDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "WLRClient.h"
#include "SearchCarsDlg.h"


// CSearchCarsDlg 对话框

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


// CSearchCarsDlg 消息处理程序

BOOL CSearchCarsDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  在此添加额外的初始化
    // 初始化出发地
	if (-1 == initStartPoint()) {
        return false;
    }
    // 初始化到达地
    if (-1 == initEndPoint()) {
        return false;
    }

    // 车长
    carLength.AddString("不限");
	carLength.AddString("4米");
	carLength.AddString("4.2米");
	carLength.AddString("4.3米");
	carLength.AddString("4.5米");
	carLength.AddString("4.8米");
	carLength.AddString("5米");
	carLength.AddString("5.8米");
	carLength.AddString("6米");
	carLength.AddString("6.2米");
	carLength.AddString("6.8米");
	carLength.AddString("7米");
	carLength.AddString("7.2米");
	carLength.AddString("7.4米");
	carLength.AddString("7.8米");
	carLength.AddString("8米");
	carLength.AddString("8.7米");
	carLength.AddString("8.8米");
	carLength.AddString("9米");
	carLength.AddString("9.6米");
	carLength.AddString("12.5米");
	carLength.AddString("13米");
	carLength.AddString("13.5米");
	carLength.AddString("17.5米");
	carLength.SetCurSel(0);

	// 车类型
    carType.AddString("不限");
	carType.AddString("前四后十");
	carType.AddString("前四后八");
	carType.AddString("前四后四");
	carType.AddString("半封闭车");
	carType.AddString("敞篷车");
	carType.AddString("平板车");
	carType.AddString("高栏车");
	carType.AddString("集装箱");
	carType.AddString("冷藏车");
	carType.AddString("后八轮");
	carType.AddString("单桥车");
	carType.AddString("自卸车");
	carType.AddString("半挂车");
	carType.AddString("保温车");
	carType.AddString("双桥车");
	carType.AddString("高低板");
	carType.SetCurSel(0);

    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常: OCX 属性页应返回 FALSE
}
    
// 初始化出发地
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
    
// 初始化到达地
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

// 响应出发省列表框点击消息
void CSearchCarsDlg::OnCbnSelchangeStartProvince()
{
    // TODO: 在此添加控件通知处理程序代码
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
    
// 响应出发市列表框点击消息
void CSearchCarsDlg::OnCbnSelchangeStartCity()
{
    // TODO: 在此添加控件通知处理程序代码
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
    
// 响应到达省列表框点击消息
void CSearchCarsDlg::OnCbnSelchangeEndProvince()
{
    // TODO: 在此添加控件通知处理程序代码
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
    
// 响应到达市列表框点击消息
void CSearchCarsDlg::OnCbnSelchangeEndCity()
{
    // TODO: 在此添加控件通知处理程序代码
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
    // TODO: 在此添加控件通知处理程序代码
    UpdateData();
    bool ifOK = true;

    // 判断必填字段
    if (strStartProvince == "" && strEndProvince == "") {
        MessageBox("出发地和到达地至少填写一项", "搜索车源");
        ifOK = false;
        return;
    }

    // 设置未填字段为 "NULL"
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
