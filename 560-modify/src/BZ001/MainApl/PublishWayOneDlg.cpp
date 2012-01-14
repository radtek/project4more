// PublishWayOne.cpp : implementation file
//

#include "stdafx.h"
#include "PublishWayOneDlg.h"
#include "CommDef.h"
#include "ContentDlg.h"
#include "NumberDlg.h"

#include "PubHistoryDlg.h"


// CPublishWayOne dialog

IMPLEMENT_DYNAMIC(CPublishWayOneDlg, CDialog)

CPublishWayOneDlg::CPublishWayOneDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPublishWayOneDlg::IDD, pParent)
	, autoClose(FALSE)
	, rememberRepubSetting(FALSE)
	, longTimeAvailable(FALSE)
	, withMobile(FALSE)
	, withName(FALSE)
	, mobile(_T(""))
	, name(_T(""))
{

}

CPublishWayOneDlg::~CPublishWayOneDlg()
{
}

void CPublishWayOneDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PW1_FROM_PROVINCE, m_strProvinceFrom);
	DDX_Text(pDX, IDC_EDIT_PW1_FROM_CITY, m_strCityFrom);
	DDX_Text(pDX, IDC_EDIT_PW1_FROM_COUNTY, m_strCountyFrom);
	DDX_Text(pDX, IDC_EDIT_PW1_TO_PROVINCE, m_strProvinceTo);
	DDX_Text(pDX, IDC_EDIT_PW1_TO_CITY, m_strCityTo);
	DDX_Text(pDX, IDC_EDIT_PW1_TO_COUNTY, m_strCountyTo);
	DDX_Control(pDX, IDC_BUTTON_PW1_FROM_PROVINCE, m_btnFromProv);
	DDX_Control(pDX, IDC_BUTTON_PW1_FROM_CITY, m_btnFromCity);
	DDX_Control(pDX, IDC_BUTTON_PW1_FROM_COUNTY, m_btnFromCounty);
	DDX_Control(pDX, IDC_BUTTON_W1_TO_PROVINCE, m_btnToProvince);
	DDX_Control(pDX, IDC_BUTTON_W1_TO_CITY, m_btnToCity);
	DDX_Control(pDX, IDC_BUTTON_W1_TO_COUNTY, m_btnToCounty);
	DDX_Control(pDX, IDC_BUTTON_PRIACE_NUM, m_bntPrice);
	DDX_Control(pDX, IDC_BUTTON_GOODS_NUM, m_btnGoodsNum);
	DDX_Control(pDX, IDC_BUTTON_CAR_NUM, m_btnCarNum);
	DDX_Control(pDX, IDC_COMBO_PW1_INFO_TYPE, msgType);
	DDX_Control(pDX, IDC_COMBO_PW1_LDGOODS_DT, shipTime);
	DDX_Control(pDX, IDC_COMBO_PW1_REPUB_SETTING, repubSetting);
	DDX_Check(pDX, IDC_CHECK_W1_CLOSE, autoClose);
	DDX_Check(pDX, IDC_CHECK_PW1_REM_REPUB_SETTING, rememberRepubSetting);
	DDX_Check(pDX, IDC_CHECK_PW1_LONGTIME, longTimeAvailable);
	DDX_Check(pDX, IDC_CHECK_PW1_CONTACT_NAME, withMobile);
	DDX_Check(pDX, IDC_CHECK_PW1_CONTACT_PHONE, withName);
	DDX_Text(pDX, IDC_EDIT_PW1_CONTACT_NAME, mobile);
	DDX_Text(pDX, IDC_EDIT_PW1_CONTACT_PHONE, name);
	DDX_Control(pDX, IDC_STATIC_GP_GOODS, firstPanel);
	DDX_Control(pDX, IDC_STATIC_GP_CAR, secondPanel);
	DDX_Control(pDX, IDC_LIST_GOODS, goodsList);
	DDX_Control(pDX, IDC_EDIT_GOODS_NUM, goodsCount);
	DDX_Control(pDX, IDC_COMBO_GOOD_UNIT, goodsUnit);
	DDX_Control(pDX, IDC_LIST_CAR_SIZE, truckLength);
	DDX_Control(pDX, IDC_LIST_CAR_TYPE, truckType);
	DDX_Control(pDX, IDC_EDIT_CAR_NUM, truckCount);
	DDX_Control(pDX, IDC_STATIC_CAR_UNIT, truckUnit);
	DDX_Control(pDX, IDC_LIST_PRIACE, priceList);
}


BEGIN_MESSAGE_MAP(CPublishWayOneDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_PW1_FROM_PROVINCE, &CPublishWayOneDlg::OnBnClickedButtonPw1FromProvince)
	ON_BN_CLICKED(IDC_BUTTON_PW1_FROM_CITY, &CPublishWayOneDlg::OnBnClickedButtonPw1FromCity)
	ON_BN_CLICKED(IDC_BUTTON_PW1_FROM_COUNTY, &CPublishWayOneDlg::OnBnClickedButtonPw1FromCounty)
	ON_BN_CLICKED(IDC_BUTTON_W1_TO_PROVINCE, &CPublishWayOneDlg::OnBnClickedButtonW1ToProvince)
	ON_BN_CLICKED(IDC_BUTTON_W1_TO_CITY, &CPublishWayOneDlg::OnBnClickedButtonW1ToCity)
	ON_BN_CLICKED(IDC_BUTTON_W1_TO_COUNTY, &CPublishWayOneDlg::OnBnClickedButtonW1ToCounty)
	ON_BN_CLICKED(IDC_BUTTON_GOODS_NUM, &CPublishWayOneDlg::OnBnClickedButtonGoodsNum)
	ON_BN_CLICKED(IDC_BUTTON_CAR_NUM, &CPublishWayOneDlg::OnBnClickedButtonCarNum)
	ON_BN_CLICKED(IDC_BUTTON_PW1_HISTORY, &CPublishWayOneDlg::OnBnClickedButtonPw1History)
	ON_BN_CLICKED(IDC_BUTTON_PREVIEW, &CPublishWayOneDlg::OnBnClickedButtonPreview)
	ON_BN_CLICKED(IDC_BUTTON_PW1_PUB, &CPublishWayOneDlg::OnBnClickedButtonPw1Pub)
	ON_BN_CLICKED(IDC_BUTTON_PW1_CLEAN, &CPublishWayOneDlg::OnBnClickedButtonPw1Clean)
	ON_BN_CLICKED(IDC_BUTTON_PW1_CLOSE, &CPublishWayOneDlg::OnBnClickedButtonPw1Close)
	ON_CBN_SELCHANGE(IDC_COMBO_PW1_INFO_TYPE, &CPublishWayOneDlg::OnCbnSelchangeComboPw1InfoType)
END_MESSAGE_MAP()


// CPublishWayOne message handlers

BOOL CPublishWayOneDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_btnFromProv.LoadBitmap(IDB_BITMAP_COMMON_BTN);
	m_btnFromCity.LoadBitmap(IDB_BITMAP_COMMON_BTN);
	m_btnFromCounty.LoadBitmap(IDB_BITMAP_COMMON_BTN);
	m_btnToProvince.LoadBitmap(IDB_BITMAP_COMMON_BTN);
	m_btnToCity.LoadBitmap(IDB_BITMAP_COMMON_BTN);
	m_btnToCounty.LoadBitmap(IDB_BITMAP_COMMON_BTN);
	m_bntPrice.LoadBitmap(IDB_BITMAP_COMMON_BTN);
	m_btnGoodsNum.LoadBitmap(IDB_BITMAP_COMMON_BTN);
	m_btnCarNum.LoadBitmap(IDB_BITMAP_COMMON_BTN);

	initControlValue();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CPublishWayOneDlg::initControlValue()
{
	msgType.AddString("发布货源");
	msgType.AddString("发布车源");
	msgType.SetCurSel(0);

	unsigned int n;

	goodsList.SetColumnWidth(110);
	for ( n = 0; n < g_goodsType.size(); n++ )
	{
		goodsList.AddString(g_goodsType[n].c_str());
	}

	for ( n = 0; n < g_goodsUnit.size(); n++ )
	{
		goodsUnit.AddString(g_goodsUnit[n].c_str());
	}
	goodsUnit.SetCurSel(0);

	truckLength.SetColumnWidth(50);
	for ( n = 0; n < g_truckLength.size(); n++ )
	{
		truckLength.AddString(g_truckLength[n].c_str());
	}

	truckType.SetColumnWidth(50);
	for ( n = 0; n < g_truckType.size(); n++ )
	{
		truckType.AddString(g_truckType[n].c_str());
	}

	priceList.SetColumnWidth(110);
	for ( n = 0; n < g_priceType.size(); n++ )
	{
		priceList.AddString(g_priceType[n].c_str());
	}
}


void CPublishWayOneDlg::OnBnClickedButtonPw1FromProvince()
{
	// TODO: Add your control notification handler code here
	vector<CString> vecItems;
	GetProvincesName(vecItems);

	CContentDlg dlgContent(this, GetDlgItem(IDC_EDIT_PW1_FROM_PROVINCE), &vecItems, &m_strProvinceFrom);
	dlgContent.DoModal();

	UpdateData(FALSE);
}

void CPublishWayOneDlg::OnBnClickedButtonPw1FromCity()
{
	// TODO: Add your control notification handler code here
	vector<CString> vecItems;
	GetCitiesNameByProvince(vecItems, m_strProvinceFrom);

	CContentDlg dlgContent(this, GetDlgItem(IDC_EDIT_PW1_FROM_CITY), &vecItems, &m_strCityFrom);
	dlgContent.DoModal();

	UpdateData(FALSE);
}

void CPublishWayOneDlg::OnBnClickedButtonPw1FromCounty()
{
	// TODO: Add your control notification handler code here
	vector<CString> vecItems;
	GetCountiesNameByProvinceAndCity(vecItems, m_strProvinceFrom, m_strCityFrom);

	CContentDlg dlgContent(this, GetDlgItem(IDC_EDIT_PW1_FROM_COUNTY), &vecItems, &m_strCountyFrom);
	dlgContent.DoModal();

	UpdateData(FALSE);
}

void CPublishWayOneDlg::OnBnClickedButtonW1ToProvince()
{
	// TODO: Add your control notification handler code here
	vector<CString> vecItems;
	GetProvincesName(vecItems);

	CContentDlg dlgContent(this, GetDlgItem(IDC_EDIT_PW1_TO_PROVINCE), &vecItems, &m_strProvinceTo);
	dlgContent.DoModal();

	UpdateData(FALSE);
}

void CPublishWayOneDlg::OnBnClickedButtonW1ToCity()
{
	// TODO: Add your control notification handler code here
	vector<CString> vecItems;
	GetCitiesNameByProvince(vecItems, m_strProvinceTo);

	CContentDlg dlgContent(this, GetDlgItem(IDC_EDIT_PW1_TO_CITY), &vecItems, &m_strCityTo);
	dlgContent.DoModal();

	UpdateData(FALSE);
}

void CPublishWayOneDlg::OnBnClickedButtonW1ToCounty()
{
	// TODO: Add your control notification handler code here
	vector<CString> vecItems;
	GetCountiesNameByProvinceAndCity(vecItems, m_strProvinceTo, m_strCityTo);

	CContentDlg dlgContent(this, GetDlgItem(IDC_EDIT_PW1_TO_COUNTY), &vecItems, &m_strCountyTo);
	dlgContent.DoModal();

	UpdateData(FALSE);
}

void CPublishWayOneDlg::OnBnClickedButtonGoodsNum()
{
	// TODO: Add your control notification handler code here
	CNumberDlg dlgNumber(this, IDC_EDIT_GOODS_NUM);
	dlgNumber.DoModal();
}

void CPublishWayOneDlg::OnBnClickedButtonCarNum()
{
	// TODO: Add your control notification handler code here
	CNumberDlg dlgNumber(this, IDC_EDIT_CAR_NUM);
	dlgNumber.DoModal();
}

void CPublishWayOneDlg::OnBnClickedButtonPw1History()
{
	// TODO: Add your control notification handler code here
	CPubHistoryDlg	dlg;

	dlg.DoModal();
}

void CPublishWayOneDlg::OnBnClickedButtonPreview()
{
	// TODO: Add your control notification handler code here
}

void CPublishWayOneDlg::OnBnClickedButtonPw1Pub()
{
	// TODO: Add your control notification handler code here
	if ( autoClose )
	{
		OnOK();
	}
}

void CPublishWayOneDlg::OnBnClickedButtonPw1Clean()
{
	// TODO: Add your control notification handler code here
}

void CPublishWayOneDlg::OnBnClickedButtonPw1Close()
{
	// TODO: Add your control notification handler code here
	OnCancel();
}

void CPublishWayOneDlg::OnCbnSelchangeComboPw1InfoType()
{
	// TODO: Add your control notification handler code here
	int		dx = 0;

	if ( msgType.GetCurSel() == 0 )
	{
		firstPanel.SetWindowText("有货");
		secondPanel.SetWindowText("求车");
		
		dx = -229;
	}
	else
	{
		firstPanel.SetWindowText("有车");
		secondPanel.SetWindowText("求货");

		dx = 229;
	}

	MoveControl(goodsList, dx, 0);
	MoveControl(goodsCount, dx, 0);
	MoveControl(goodsUnit, dx, 0);
	MoveControl(m_btnGoodsNum, dx, 0);

	MoveControl(truckLength, -dx, 0);
	MoveControl(truckType, -dx, 0);
	MoveControl(truckCount, -dx, 0);
	MoveControl(truckUnit, -dx, 0);
	MoveControl(m_btnCarNum, -dx, 0);
}

void CPublishWayOneDlg::MoveControl(CWnd& control, int dx, int dy)
{
	CRect	rect;
	control.GetWindowRect(&rect);
	ScreenToClient(&rect);

	rect.left += dx;
	rect.right += dx;
	rect.top += dy;
	rect.bottom += dy;

	control.MoveWindow(rect);
}
