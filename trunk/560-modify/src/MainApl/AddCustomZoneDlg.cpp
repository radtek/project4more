// AddCustomZoneDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "WLRClient.h"
#include "AddCustomZoneDlg.h"


// CAddCustomZoneDlg 对话框

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


// CAddCustomZoneDlg 消息处理程序

BOOL CAddCustomZoneDlg::OnInitDialog()
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

    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常: OCX 属性页应返回 FALSE
}
    
// 初始化出发地
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
    
// 初始化到达地
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

// 响应出发省列表框点击消息
void CAddCustomZoneDlg::OnCbnSelchangeStartProvince()
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
}
    
// 响应到达省列表框点击消息
void CAddCustomZoneDlg::OnCbnSelchangeEndProvince()
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
}    
    
// 点击OK
void CAddCustomZoneDlg::OnBnClickedOk()
{
    // TODO: 在此添加控件通知处理程序代码
    UpdateData();
    bool ifOK = true;
    // 判断必填字段
    if (strStartProvince == "" || strStartCity == "") {
        MessageBox("出发地不能为空", "增加定制区域");
        ifOK = false;
        return;
    }

    if (strEndProvince == "" || strEndCity == "") {
        MessageBox("到达地不能为空", "增加定制区域");
        ifOK = false;
        return;
    }

    if (ifOK) {       
        OnOK();
    }
}
