// PublishWayOne.cpp : implementation file
//

#include "stdafx.h"
#include "PublishWayOneDlg.h"
#include "CommDef.h"
#include "ContentDlg.h"
#include "NumberDlg.h"
#include "header.h"

int g_repubOption = 0;


// CPublishWayOne dialog

IMPLEMENT_DYNAMIC(CPublishWayOneDlg, CDialog)

CPublishWayOneDlg::CPublishWayOneDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPublishWayOneDlg::IDD, pParent)
	, autoClose(FALSE)
	, rememberRepubSetting(FALSE)
	, longTimeAvailable(FALSE)
	, withMobile(FALSE)
	, withMobile2(FALSE)
	, mobile(_T(""))
	, mobile2(_T(""))
	, goodsValue(_T(""))
	, goodsCountValue(_T(""))
	, goodsUnitValue(_T(""))
	, truckLengthValue(_T(""))
	, truckTypeValue(_T(""))
	, truckCountValue(_T(""))
	, priceCountValue(_T(""))
	, priceListValue(_T(""))
	, preview(_T(""))
	, shipTimeValue(_T(""))
	, repubSettingValue(_T(""))
	, provSelected("")
	, citySelected("")
{
	publishKind = 0;
	pRecord = NULL;
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
	DDX_Check(pDX, IDC_CHECK_PW1_CONTACT_PHONE, withMobile2);
	DDX_Text(pDX, IDC_EDIT_PW1_CONTACT_NAME, mobile);
	DDX_Text(pDX, IDC_EDIT_PW1_CONTACT_PHONE, mobile2);
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
	DDX_LBString(pDX, IDC_LIST_GOODS, goodsValue);
	DDX_Text(pDX, IDC_EDIT_GOODS_NUM, goodsCountValue);
	DDX_CBString(pDX, IDC_COMBO_GOOD_UNIT, goodsUnitValue);
	DDX_LBString(pDX, IDC_LIST_CAR_SIZE, truckLengthValue);
	DDX_LBString(pDX, IDC_LIST_CAR_TYPE, truckTypeValue);
	DDX_Text(pDX, IDC_EDIT_CAR_NUM, truckCountValue);
	DDX_Text(pDX, IDC_EDIT_PRICE_NUM, priceCountValue);
	DDX_LBString(pDX, IDC_LIST_PRIACE, priceListValue);
	DDX_Text(pDX, IDC_EDIT_PW1_PREVIEW, preview);
	DDX_CBString(pDX, IDC_COMBO_PW1_LDGOODS_DT, shipTimeValue);
	DDX_CBString(pDX, IDC_COMBO_PW1_REPUB_SETTING, repubSettingValue);
	DDV_MaxChars(pDX, goodsCountValue, 8);
	DDV_MaxChars(pDX, truckCountValue, 8);
	DDV_MaxChars(pDX, priceCountValue, 8);
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
	ON_BN_CLICKED(IDC_BUTTON_PRIACE_NUM, &CPublishWayOneDlg::OnBnClickedButtonPriaceNum)
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

	((CEdit*)GetDlgItem(IDC_EDIT_GOODS_NUM))->SetLimitText(8);
	((CEdit*)GetDlgItem(IDC_EDIT_CAR_NUM))->SetLimitText(8);
	((CEdit*)GetDlgItem(IDC_EDIT_PRICE_NUM))->SetLimitText(8);

	((CEdit*)GetDlgItem(IDC_EDIT_PW1_PREVIEW))->SetLimitText(100);
	((CEdit*)GetDlgItem(IDC_EDIT_PW1_CONTACT_NAME))->SetLimitText(32);
	((CEdit*)GetDlgItem(IDC_EDIT_PW1_CONTACT_PHONE))->SetLimitText(32);

	initControlValue();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CPublishWayOneDlg::initControlValue()
{
	pRecord = NULL;
	pPublishRecord = NULL;

	msgType.AddString("发布货源");
	msgType.AddString("发布车源");
	msgType.SetCurSel(publishKind==0?0:1);
	if( publishKind == 1 )
	{
		MoveAllControl();
	}

	withMobile = TRUE;

	unsigned int n;

	goodsList.SetColumnWidth(100);
	for ( n = 0; n < g_goodsType.size(); n++ )
	{
		goodsList.AddString(g_goodsType[n]);
	}

	for ( n = 0; n < g_goodsUnit.size(); n++ )
	{
		goodsUnit.AddString(g_goodsUnit[n]);
	}
	goodsUnit.SetCurSel(0);

	truckLength.SetColumnWidth(60);
	for ( n = 0; n < g_truckLength.size(); n++ )
	{
		truckLength.AddString(g_truckLength[n]);
	}

	truckType.SetColumnWidth(60);
	for ( n = 0; n < g_truckType.size(); n++ )
	{
		truckType.AddString(g_truckType[n]);
	}

	priceList.SetColumnWidth(100);
	for ( n = 0; n < g_priceType.size(); n++ )
	{
		priceList.AddString(g_priceType[n]);
	}
	mobile = mobile.IsEmpty()?userInfo.tel.c_str():mobile;

	withMobile2 = mobile2.IsEmpty()?FALSE:TRUE;

	if ( provSelected != "" /*&& citySelected != "" */)
	{
		m_strProvinceFrom = provSelected;
		m_strCityFrom = citySelected.IsEmpty()?NO_LIMIT_STRING:citySelected;
		m_strCountyFrom = NO_LIMIT_STRING;
	}
	else
	{
		m_strProvinceFrom = userInfo.province.c_str();
		if( IsSpecialProvince(m_strProvinceFrom) )
		{
			m_strCityFrom = m_strProvinceFrom;
			if( userInfo.province != userInfo.city )
			{
				m_strCountyFrom = userInfo.city.c_str();
			}
			else
			{
				m_strCountyFrom = NO_LIMIT_STRING;
			}
		}
		else
		{
			m_strCityFrom = user.city.c_str();
			m_strCountyFrom = NO_LIMIT_STRING;
		}
		
	}

	truckCountValue = "1";
	goodsList.SetCurSel(5);

	UpdateData(FALSE);

	shipTime.AddString("随时");
	CString str;
	//获取系统时间
	CTime tm = CTime::GetCurrentTime();
	for(int i=0; i<15; ++i) {
		CTime t2 = tm + CTimeSpan( i, 0, 0, 0 );
		str=t2.Format("%Y-%m-%d");
		shipTime.AddString(str);
	}
	shipTime.SetCurSel(0);

	repubSetting.AddString("不自动重发");
	repubSetting.AddString("10分钟2次");
	repubSetting.AddString("30分钟5次");
	repubSetting.AddString("2小时10次");
	repubSetting.SetCurSel(g_repubOption);
}


void CPublishWayOneDlg::OnBnClickedButtonPw1FromProvince()
{
	// TODO: Add your control notification handler code here
	UpdateData();

	GetProvincesName(m_vecContent);
	ShowContentDialog(IDC_EDIT_PW1_FROM_PROVINCE, &m_vecContent, &m_strProvinceFrom);
}

void CPublishWayOneDlg::OnBnClickedButtonPw1FromCity()
{
	// TODO: Add your control notification handler code here
	UpdateData();

	GetCitiesNameByProvince(m_vecContent, m_strProvinceFrom);
	ShowContentDialog(IDC_EDIT_PW1_FROM_CITY, &m_vecContent, &m_strCityFrom);
}

void CPublishWayOneDlg::OnBnClickedButtonPw1FromCounty()
{
	// TODO: Add your control notification handler code here
	UpdateData();

	GetCountiesNameByProvinceAndCity(m_vecContent, m_strProvinceFrom, m_strCityFrom);
	ShowContentDialog(IDC_EDIT_PW1_FROM_COUNTY, &m_vecContent, &m_strCountyFrom);
}

void CPublishWayOneDlg::OnBnClickedButtonW1ToProvince()
{
	// TODO: Add your control notification handler code here
	UpdateData();

	GetProvincesName(m_vecContent);
	ShowContentDialog(IDC_EDIT_PW1_TO_PROVINCE, &m_vecContent, &m_strProvinceTo);
}

void CPublishWayOneDlg::OnBnClickedButtonW1ToCity()
{
	// TODO: Add your control notification handler code here
	UpdateData();

	GetCitiesNameByProvince(m_vecContent, m_strProvinceTo);
	ShowContentDialog(IDC_EDIT_PW1_TO_CITY, &m_vecContent, &m_strCityTo);
}

void CPublishWayOneDlg::OnBnClickedButtonW1ToCounty()
{
	// TODO: Add your control notification handler code here
	UpdateData();

	GetCountiesNameByProvinceAndCity(m_vecContent, m_strProvinceTo, m_strCityTo);
	ShowContentDialog(IDC_EDIT_PW1_TO_COUNTY, &m_vecContent, &m_strCountyTo);
}

void CPublishWayOneDlg::OnBnClickedButtonGoodsNum()
{
	// TODO: Add your control notification handler code here
	ShowNumberDialog(IDC_EDIT_GOODS_NUM);
}

void CPublishWayOneDlg::OnBnClickedButtonCarNum()
{
	// TODO: Add your control notification handler code here
	ShowNumberDialog(IDC_EDIT_CAR_NUM);
}

void CPublishWayOneDlg::OnBnClickedButtonPriaceNum()
{
	ShowNumberDialog(IDC_EDIT_PRICE_NUM);
}


void CPublishWayOneDlg::OnBnClickedButtonPw1History()
{
	// TODO: Add your control notification handler code here
	CPubHistoryDlg	dlg;

	if ( dlg.DoModal() == IDOK )
	{
		pRecord = dlg.pSelectedRecord;
		FromHistory();
		if ( dlg.autoPublish )
		{
			OnOK();
		}
	}
}

void CPublishWayOneDlg::OnBnClickedButtonPreview()
{
	// TODO: Add your control notification handler code here
	UpdateData();

	if ( msgType.GetCurSel() == 0 )
	{
		BuildGoodsPreview();
	}
	else
	{
		BuildTruckPreview();
	}
}

void CPublishWayOneDlg::OnBnClickedButtonPw1Pub()
{
	// TODO: Add your control notification handler code here
	UpdateData();

	/*if (!bPreview)
	{
		MessageBox("在发布前请先预览！", "发布");
		return;
	}*/
	if (preview == "")
	{
		MessageBox("预览不能为空！", "发布");
		return;
	}
	bPreview = FALSE;

	BOOL	result;

	if ( msgType.GetCurSel() == 0 )
	{
		result = PublishGoodsInfo();
	}
	else
	{
		result = PublishTruckInfo();
	}

	if ( result )
	{
		ToHistory();
		OnOK();
	}
}

void CPublishWayOneDlg::ToHistory()
{
	pPublishRecord = new CPublishRecord();
	CString				v;

	// publish type
	v.Format("%d", msgType.GetCurSel());
	pPublishRecord->set("msgType", v);

	// from to
	pPublishRecord->set("strProvinceFrom", m_strProvinceFrom);
	pPublishRecord->set("strCityFrom", m_strCityFrom);
	pPublishRecord->set("strCountyFrom", m_strCountyFrom);
	pPublishRecord->set("strProvinceTo", m_strProvinceTo);
	pPublishRecord->set("strCityTo", m_strCityTo);
	pPublishRecord->set("strCountyTo", m_strCountyTo);

	// goods info
	v.Format("%d", goodsList.GetCurSel());
	pPublishRecord->set("goodsList", v);

	pPublishRecord->set("goodsCountValue", goodsCountValue);

	v.Format("%d", goodsUnit.GetCurSel());
	pPublishRecord->set("goodsUnit", v);

	// truck info
	v.Format("%d", truckLength.GetCurSel());
	pPublishRecord->set("truckLength", v);

	v.Format("%d", truckType.GetCurSel());
	pPublishRecord->set("truckType", v);

	pPublishRecord->set("truckCountValue", truckCountValue);

	// price info
	pPublishRecord->set("priceCountValue", priceCountValue);

	v.Format("%d", priceList.GetCurSel());
	pPublishRecord->set("priceList", v);

	// preview
	pPublishRecord->set("preview", preview);

	// others
	v.Format("%d", shipTime.GetCurSel());
	pPublishRecord->set("shipTime", v);

	v.Format("%d", repubSetting.GetCurSel());
	pPublishRecord->set("repubSetting", v);

	v.Format("%d", rememberRepubSetting);
	pPublishRecord->set("rememberRepubSetting", v);

	v.Format("%d", longTimeAvailable);
	pPublishRecord->set("longTimeAvailable", v);

	// publish string
	pPublishRecord->set("pubInf", pubInf.c_str());

	pPublishRecord->set("withMobile1", withMobile?"1":"0");
	pPublishRecord->set("mobile1", mobile);
	pPublishRecord->set("withMobile2", withMobile2?"1":"0");
	pPublishRecord->set("mobile2", mobile2);
	
	//CHistoryManager::getInstance()->addPublish(pPublishRecord);
}

void CPublishWayOneDlg::SaveHistory()
{
	if ( pPublishRecord == NULL )
	{
		return;
	}
	CHistoryManager::getInstance()->addPublish(pPublishRecord);
}

void CPublishWayOneDlg::SetComboSection(CComboBox& b, string k)
{
	CString v = pRecord->get(k);
	
	if ( v == "" )
	{
		return;
	}

	int n = atoi((LPSTR)(LPCTSTR)v);
	b.SetCurSel(n);
}

void CPublishWayOneDlg::SetListSection(CListBox& b, string k)
{
	CString v = pRecord->get(k);

	if ( v == "" )
	{
		return;
	}

	int n = atoi((LPSTR)(LPCTSTR)v);
	b.SetCurSel(n);
}

void CPublishWayOneDlg::FromHistory()
{
	if ( pRecord == NULL )
	{
		return;
	}

	int nOldSel = msgType.GetCurSel();
	SetComboSection(msgType, "msgType");

	if ( msgType.GetCurSel() == 0 )
	{
		firstPanel.SetWindowText("有货");
		secondPanel.SetWindowText("求车");

		publishKind = 0;
	}
	else
	{
		firstPanel.SetWindowText("有车");
		secondPanel.SetWindowText("求货");

		publishKind = 1;
	}
	if( nOldSel != msgType.GetCurSel() )
	{
		MoveAllControl();
	}


	m_strProvinceFrom = pRecord->get("strProvinceFrom");
	m_strCityFrom = pRecord->get("strCityFrom");
	m_strCountyFrom = pRecord->get("strCountyFrom");
	m_strProvinceTo = pRecord->get("strProvinceTo");
	m_strCityTo = pRecord->get("strCityTo");
	m_strCountyTo = pRecord->get("strCountyTo");

	SetListSection(goodsList, "goodsList");
	goodsCountValue = pRecord->get("goodsCountValue");
	
	SetListSection(truckLength, "truckLength");
	SetListSection(truckType, "truckType");

	truckCountValue = pRecord->get("truckCountValue");

	priceCountValue = pRecord->get("priceCountValue");
	SetListSection(priceList, "priceList");

	preview = pRecord->get("preview");

	CString	v;

	v = pRecord->get("rememberRepubSetting");
	if ( v == "0" )
	{
		rememberRepubSetting = FALSE;
	}
	else
	{
		rememberRepubSetting = TRUE;
	}

	v = pRecord->get("longTimeAvailable");
	if ( v == "0" )
	{
		longTimeAvailable = FALSE;
	}
	else
	{
		longTimeAvailable = TRUE;
	}

	v = pRecord->get("pubInf");
	pubInf = v.GetBuffer();
	v.ReleaseBuffer();

	v = pRecord->get("withMobile1");
	withMobile = v =="1"?TRUE:FALSE;

	v = pRecord->get("withMobile2");
	withMobile2 = v =="1"?TRUE:FALSE;

	mobile = pRecord->get("mobile1");
	mobile2 = pRecord->get("mobile2");

	UpdateData(FALSE);

	SetComboSection(goodsUnit, "goodsUnit");
	SetComboSection(shipTime, "shipTime");
	SetComboSection(repubSetting, "repubSetting");

	UpdateData();
}

void CPublishWayOneDlg::OnBnClickedButtonPw1Clean()
{
	m_strProvinceFrom="";
	m_strCityFrom="";
	m_strCountyFrom="";
	m_strProvinceTo="";
	m_strCityTo="";
	m_strCountyTo="";

	rememberRepubSetting = FALSE;
	longTimeAvailable = FALSE;

	goodsCountValue="";
	truckCountValue="";
	priceCountValue="";

	preview.Empty();

	repubSetting.SetWindowText("");
	shipTime.SetWindowText("");
	UpdateData(FALSE);
}

void CPublishWayOneDlg::OnBnClickedButtonPw1Close()
{
	// TODO: Add your control notification handler code here
	OnCancel();
}

void CPublishWayOneDlg::OnCbnSelchangeComboPw1InfoType()
{
	if(publishKind==msgType.GetCurSel())
	{
		return;
	}

	MoveAllControl();
}
void CPublishWayOneDlg::MoveAllControl()
{
	// TODO: Add your control notification handler code here
	int		dx = 0;

	if ( msgType.GetCurSel() == 0 )
	{
		firstPanel.SetWindowText("有货");
		secondPanel.SetWindowText("求车");

		dx = -229;
		publishKind = 0;
	}
	else
	{
		firstPanel.SetWindowText("有车");
		secondPanel.SetWindowText("求货");

		dx = 229;
		publishKind = 1;
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

BOOL CPublishWayOneDlg::CheckGoodsInfo()
{
	if ( goodsValue == "" )
	{
		MessageBox("请选择货物种类");//, "发布货源");
		return FALSE;
	}

	if (priceListValue == "" && priceCountValue != "")
	{
		MessageBox("请选择价格类型");//, "发布货源");
		return FALSE;
	}

	if (priceListValue != "" && priceCountValue == "")
	{
		MessageBox("价格不能为空");//, "发布货源");
		return FALSE;
	}

	if (m_strProvinceFrom == "")
	{
		MessageBox("始发地：一级地址不能为空");//, "发布货源");
		return FALSE;
	}

	if( m_strCityFrom == "" )
	{
		MessageBox("始发地：二级地址不能为空");//, "发布货源");
		return FALSE;
	}

	if( CheckAddress(m_strProvinceFrom, m_strCityFrom, m_strCountyFrom) != 0 )
	{
		MessageBox("始发地：地址信息不合法");//, "发布货源");
		return FALSE;
	}

	if (m_strProvinceTo == "")
	{
		MessageBox("目的地：一级地址不能为空");//, "发布货源");
		return FALSE;
	}

	if( m_strCityTo == "" )
	{
		MessageBox("目的地：二级地址不能为空");//, "发布货源");
		return FALSE;
	}

	if( CheckAddress(m_strProvinceTo, m_strCityTo, m_strCountyTo) != 0 )
	{
		MessageBox("目的地：地址信息不合法");//, "发布货源");
		return FALSE;
	}

	if ( !CheckNumberString(goodsCountValue) )
	{
		MessageBox("货物数量应为数字");//, "发布货源");
		return FALSE;
	}

	if ( !CheckNumberString(truckCountValue) )
	{
		MessageBox("车辆数量应为数字");//, "发布货源");
		return FALSE;
	}

	if ( !CheckNumberString(priceCountValue) )
	{
		MessageBox("价格应为数字");//, "发布货源");
		return FALSE;
	}

	return TRUE;
}

void CPublishWayOneDlg::BuildGoodsPreview()
{
	UpdateData();
	if ( CheckGoodsInfo() == FALSE )
	{
		return;
	}

	bPreview = TRUE;

	preview = "有货：" + goodsValue + "，";

	if ( goodsCountValue != "" )
	{
		preview = preview + goodsCountValue + goodsUnitValue + "，";
	}

	if ( priceCountValue != ""  )
	{
		preview = preview + "价格：" + priceCountValue + priceListValue + "，";
	}

	preview = preview + "需要：";

	if ( truckLengthValue != "" )
	{
		preview = preview + truckLengthValue;
	}
	if ( truckTypeValue != "" )
	{
		preview = preview + "“" + truckTypeValue + "”";
	}
	preview += "车";
	if ( truckCountValue != "" )
	{
		preview += truckCountValue + "辆";
	}
	preview += "。";
	UpdateData(FALSE);
}

BOOL CPublishWayOneDlg::CheckTruckInfo()
{
	if ( goodsValue == "" )
	{
		MessageBox("请选择货物种类");//, "发布车源");
		return FALSE;
	}


	if (m_strProvinceFrom == "")
	{
		MessageBox("始发地：一级地址不能为空");//, "发布车源");
		return FALSE;
	}

	if( m_strCityFrom == "" )
	{
		MessageBox("始发地：二级地址不能为空");//, "发布车源");
		return FALSE;
	}

	if( CheckAddress(m_strProvinceFrom, m_strCityFrom, m_strCountyFrom) != 0 )
	{
		MessageBox("始发地：地址信息不合法");//, "发布车源");
		return FALSE;
	}

	if (m_strProvinceTo == "")
	{
		MessageBox("目的地：一级地址不能为空");//, "发布车源");
		return FALSE;
	}

	if( m_strCityTo == "" )
	{
		MessageBox("目的地：二级地址不能为空");//, "发布车源");
		return FALSE;
	}

	if( CheckAddress(m_strProvinceTo, m_strCityTo, m_strCountyTo) != 0 )
	{
		MessageBox("目的地：地址信息不合法");//, "发布车源");
		return FALSE;
	}

	if ( truckLengthValue == "" )
	{
		MessageBox("请选择车辆长度");//, "发布车源");
		return FALSE;
	}

	if ( !CheckNumberString(goodsCountValue) )
	{
		MessageBox("货物数量应为数字");//, "发布货源");
		return FALSE;
	}

	if ( !CheckNumberString(truckCountValue) )
	{
		MessageBox("车辆数量应为数字");//, "发布货源");
		return FALSE;
	}

	if ( !CheckNumberString(priceCountValue) )
	{
		MessageBox("价格应为数字");//, "发布货源");
		return FALSE;
	}

	return TRUE;
}

void CPublishWayOneDlg::BuildTruckPreview()
{
	if ( CheckTruckInfo() == FALSE )
	{
		return;
	}

	bPreview = TRUE;

	preview = "有" + truckLengthValue;
	if ( truckTypeValue != "" )
	{
		preview = preview + "“" + truckTypeValue + "”";
	}
	preview += "车";
	if ( truckCountValue != "" )
	{
		preview += truckCountValue + "辆";
	}

	preview = preview + "求货：" + goodsValue + "。";

	UpdateData(FALSE);
}

BOOL CPublishWayOneDlg::PublishGoodsInfo()
{
	UpdateData();

	if (CheckGoodsInfo() == FALSE)
	{
		return FALSE;
	}

	if( !withMobile && !withMobile2 )
	{
		MessageBox("请至少选择一个联系电话");//, "发布货源");
		return FALSE;
	}


	if ( (withMobile && mobile.IsEmpty() ) ) 
	{
		MessageBox("联系电话1不能为空");//, "发布货源");
		return FALSE;
	}

	if ( (withMobile2 && mobile2.IsEmpty() ) ) 
	{
		MessageBox("联系电话2不能为空");//, "发布货源");
		return FALSE;
	}

	if( mobile.IsEmpty() && mobile2.IsEmpty() )
	{
		MessageBox("联系电话不能为空");//, "发布货源");
		return FALSE;
	}

	CString	p, pu;

	if ( priceCountValue == "" && priceListValue == "" )
	{
		p = pu = "NULL";
	}
	else
	{
		p = priceCountValue;
		pu = priceListValue;
	}

	CString w = goodsCountValue;
	CString tl = truckLengthValue;
	CString tt = truckTypeValue;
	CString tc = truckCountValue;
	CString ct = m_strCountyTo;
	CString cf = m_strCountyFrom;

	if ( w == "" )
		w = "NULL";

	if ( tl == "" )
		tl = "NULL";

	if ( tt == "" )
		tt = "NULL";

	if ( tc == "" )
		tc = "NULL";

	if ( ct == "" )
		ct = "不限";

	if ( cf == "" )
		cf = "不限";

	CString tmp = m_strProvinceFrom + "|" + m_strCityFrom + "|" + cf
		+ "|" + m_strProvinceTo + "|" + m_strCityTo + "|" + ct
		+ "|" + goodsValue + "|" + goodsCountValue + "|" + "NULL"
		+ "|" + "普货" + "|" + p + "|" + pu + "|NULL|" + tl + "|" + tt + "|"
		+ tc + "|" + (withMobile?mobile:"") + ((withMobile2&&!mobile2.IsEmpty())?(" "+mobile2):"") + "|" + shipTimeValue + "|" + repubSettingValue;

	if (rememberRepubSetting)
	{
		tmp = tmp + "|" + "1"; 
		g_repubOption = repubSetting.GetCurSel();
	}
	else
	{
		tmp = tmp + "|" + "0";
		g_repubOption = 0;
	}

	if (longTimeAvailable)
	{
		tmp = tmp + "|" + "长期有效|"; 
	}
	else
	{
		tmp = tmp + "|" + "24小时|";
	}

	CString sText = preview;

	sText.Replace("|","");	
	tmp += sText;

	pubInf = (LPTSTR)(LPCTSTR)tmp;

	return TRUE;
}

BOOL CPublishWayOneDlg::PublishTruckInfo()
{
	if (CheckTruckInfo() == FALSE)
	{
		return FALSE;
	}

	if( !withMobile && !withMobile2 )
	{
		MessageBox("请至少选择一个联系电话");//, "发布货源");
		return FALSE;
	}

	if ( withMobile && mobile.IsEmpty() ) 
	{
		MessageBox("联系电话1不能为空");//, "发布车源");
		return FALSE;
	}

	if ( withMobile2 && mobile2.IsEmpty()) 
	{
		MessageBox("联系电话2不能为空");//, "发布车源");
		return FALSE;
	}

	if( mobile.IsEmpty() && mobile2.IsEmpty())
	{
		MessageBox("联系电话不能为空");//, "发布车源");
		return FALSE;
	}

	CString	tc = truckCountValue;
	CString w = goodsCountValue;
	CString tl = truckLengthValue;
	CString tt = truckTypeValue;
	CString ct = m_strCountyTo;
	CString cf = m_strCountyFrom;

	if ( tc == "" )
		tc = "NULL";

	if ( w == "" )
		w = "NULL";

	if ( tl == "" )
		tl = "NULL";

	if ( tt == "" )
		tt = "NULL";

	if ( ct == "" )
		ct = "不限";

	if ( cf == "" )
		cf = "不限";

	CString tmp = m_strProvinceFrom + "|" + m_strCityFrom + "|" + cf
		+ "|" + m_strProvinceTo + "|" + m_strCityTo + "|" + ct
		+ "|||||||"
		+ tc + "|" + w + "|NULL|" + tl + "|" + tt 
		+ "|" + goodsValue + "|普货|" + (withMobile?mobile:"") + ((withMobile2&&!mobile2.IsEmpty())?(" "+mobile2):"") + "|" + shipTimeValue + "|" + repubSettingValue;
	
	if (rememberRepubSetting)
	{
		tmp = tmp + "|" + "1"; 
		g_repubOption = repubSetting.GetCurSel();
	}
	else
	{
		tmp = tmp + "|" + "0";
		g_repubOption = 0;
	}

	if (longTimeAvailable)
	{
		tmp = tmp + "|" + "长期有效|"; 
	}
	else
	{
		tmp = tmp + "|" + "24小时|";
	}

	CString sText = preview;

	sText.Replace("|","");

	tmp += sText;

	pubInf = (LPTSTR)(LPCTSTR)tmp; 

	return TRUE;
}

LRESULT CPublishWayOneDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	CDialog *pChildDlg = NULL;

	switch (message)
	{
	case WM_CLOSE_CONTENT_DLG:
		if (pChildDlg = (CDialog *)wParam)
			delete pChildDlg;
		switch ((int)lParam)
		{
		case IDC_EDIT_PW1_FROM_PROVINCE:
			m_strCityFrom = NO_LIMIT_STRING;
		case IDC_EDIT_PW1_FROM_CITY:
			m_strCountyFrom = NO_LIMIT_STRING;
			break;
		case IDC_EDIT_PW1_TO_PROVINCE:
			m_strCityTo = NO_LIMIT_STRING;
		case IDC_EDIT_PW1_TO_CITY:
			m_strCountyTo = NO_LIMIT_STRING;
			break;
		default:
			break;
		}
		UpdateData(FALSE);
		break;
	case WM_CLOSE_NUMBER_DLG:
		if (pChildDlg = (CDialog *)wParam)
			delete pChildDlg;
		UpdateData();
		break;
	default:
		break;
	}
	
	return CDialog::WindowProc(message, wParam, lParam);
}

void CPublishWayOneDlg::ShowContentDialog(int nCtrlID, const vector<CString> *pVec, CString *pStrOut)
{
	if (pVec && !pVec->empty() && pStrOut)
	{
		CContentDlg *pDlgContent = new CContentDlg(this, GetDlgItem(nCtrlID), pVec, pStrOut);
		if (pDlgContent && pDlgContent->Create(IDD_DIALOG_CONTENT_LIST, this))
		{
			pDlgContent->ShowWindow(SW_SHOW);
			pDlgContent->BringWindowToTop();
		}
	}
}

void CPublishWayOneDlg::ShowNumberDialog(int nCtrlID)
{
	CNumberDlg *pDlgNumber = new CNumberDlg(this, GetDlgItem(nCtrlID));
	if (pDlgNumber && pDlgNumber->Create(IDD_DIALOG_NUMBER, this))
	{
		pDlgNumber->ShowWindow(SW_SHOW);
		pDlgNumber->BringWindowToTop();
	}
}