// PubSpecialDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "WLRClient.h"
#include "PubSpecialDlg.h"


// CPubSpecialDlg 对话框

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

    // TODO:  在此添加额外的初始化
    // 发车方式

	((CEdit*)GetDlgItem(IDC_PUB_SPECIAL_WEIGHT_PRICE))->LimitText(8);
	((CEdit*)GetDlgItem(IDC_PUB_SPECIAL_LIGHT_PRICE))->LimitText(8);
	((CEdit*)GetDlgItem(IDC_PUB_SPECIAL_ST_NAME))->LimitText(32);
	((CEdit*)GetDlgItem(IDC_PUB_SPECIAL_ST_ADDRESS))->LimitText(128);
	((CEdit*)GetDlgItem(IDC_PUB_SPECIAL_ST_TEL))->LimitText(32);
	((CEdit*)GetDlgItem(IDC_PUB_SPECIAL_EN_NAME))->LimitText(32);
	((CEdit*)GetDlgItem(IDC_PUB_SPECIAL_EN_ADDRESS))->LimitText(128);
	((CEdit*)GetDlgItem(IDC_PUB_SPECIAL_TEL))->LimitText(32);
	((CEdit*)GetDlgItem(IDC_PUB_SPECIAL_INF))->LimitText(100);

	combSend.AddString("不固定");
	combSend.AddString("隔1天一班");
	combSend.AddString("隔2天一班");
	combSend.AddString("隔3天一班");
    combSend.AddString("隔4天一班");
    combSend.AddString("隔5天一班");
	combSend.SetCurSel(0);

    // 联系方式
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
    // 异常: OCX 属性页应返回 FALSE
}

// CPubSpecialDlg 消息处理程序
    
// 响应点击下拉框：出发地省
void CPubSpecialDlg::OnCbnSelchangePubSpecialStprovince()
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
void CPubSpecialDlg::OnCbnSelchangePubSpecialStcity()
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
void CPubSpecialDlg::OnCbnSelchangePubSpecialEnprovince()
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
void CPubSpecialDlg::OnCbnSelchangePubSpecialEncity()
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
    
// 出发地列表框初始化
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
    
// 确定按钮
void CPubSpecialDlg::OnBnClickedOk()
{
    // TODO: 在此添加控件通知处理程序代码
    UpdateData();
	//MessageBox (information);
    bool ifOK = true;
    // 判断必填字段
    if (enProvince == "" || enCity == "" || enCounty == "") {
        MessageBox("目的地不能为空");
        ifOK = false;
        return;
    }

    if (weightPrice == "") {
        MessageBox("重货价格不能为空");
        ifOK = false;
        return;
    }
	if( !CheckNumberString(weightPrice) )
	{
		MessageBox("重货价格应为数字");
		ifOK = false;
		return;
	}

    if (lightPrice == "") {
        MessageBox("泡货价格不能为空");
        ifOK = false;
        return;
    }
	if( !CheckNumberString(lightPrice) )
	{
		MessageBox("泡货价格应为数字");
		ifOK = false;
		return;
	}

    if (information == "") {
        MessageBox("信息发布不能为空", "发布专线");
        ifOK = false;
        return;
    } 

    if (stTel == "") {
        MessageBox("出发地电话不能为空", "发布专线");
        ifOK = false;
        return;
    } 

    if (enTel == "") {
        MessageBox("目的地电话不能为空", "发布专线");
        ifOK = false;
        return;
    } 

    // 设置未填字段为 "NULL"    
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
        tmp = tmp + "|" + "单程"; 
    } else {
        tmp = tmp + "|" + "往返";
    }
                    
    tmp = tmp + "|" + lightPrice ;
                    
    if (0 == transport) {
        tmp = tmp + "|" + "中转"; 
    } else {
        tmp = tmp + "|" + "直达";
    }

    tmp = tmp + "|" + send ;
                    
    if (0 == time) {
        tmp = tmp + "|" + "1天"; 
    } else if (1 == time) {
        tmp = tmp + "|" + "2天";
    } else if (2 == time) {
        tmp = tmp + "|" + "3天";
    } else if (3 == time) {
        tmp = tmp + "|" + "4天";
    } else {
        tmp = tmp + "|" + "5天";
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
