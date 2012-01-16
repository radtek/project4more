// PublishWayOne.cpp : implementation file
//

#include "stdafx.h"
#include "PublishWayOneDlg.h"
#include "CommDef.h"
#include "ContentDlg.h"
#include "NumberDlg.h"



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
	repubSetting.SetCurSel(0);

	mobile = userInfo.tel.c_str();
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

	if (!bPreview)
	{
		MessageBox("在发布前请先预览！", "发布");
		return;
	}
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
	CPublishRecord*		pRecord = new CPublishRecord();
	CString				v;

	// publish type
	v.Format("%d", msgType.GetCurSel());
	pRecord->set("msgType", v);

	// from to
	pRecord->set("strProvinceFrom", m_strProvinceFrom);
	pRecord->set("strCityFrom", m_strCityFrom);
	pRecord->set("strCountyFrom", m_strCountyFrom);
	pRecord->set("strProvinceTo", m_strProvinceTo);
	pRecord->set("strCityTo", m_strCityTo);
	pRecord->set("strCountyTo", m_strCountyTo);

	// goods info
	v.Format("%d", goodsList.GetCurSel());
	pRecord->set("goodsList", v);

	pRecord->set("goodsCountValue", goodsCountValue);

	v.Format("%d", goodsUnit.GetCurSel());
	pRecord->set("goodsUnit", v);

	// truck info
	v.Format("%d", truckLength.GetCurSel());
	pRecord->set("truckLength", v);

	v.Format("%d", truckType.GetCurSel());
	pRecord->set("truckType", v);

	pRecord->set("truckCountValue", truckCountValue);

	// price info
	pRecord->set("priceCountValue", priceCountValue);

	v.Format("%d", priceList.GetCurSel());
	pRecord->set("priceList", v);

	// preview
	pRecord->set("preview", preview);

	// others
	v.Format("%d", shipTime.GetCurSel());
	pRecord->set("shipTime", v);

	v.Format("%d", repubSetting.GetCurSel());
	pRecord->set("repubSetting", v);

	v.Format("%d", rememberRepubSetting);
	pRecord->set("rememberRepubSetting", v);

	v.Format("%d", longTimeAvailable);
	pRecord->set("longTimeAvailable", v);

	// publish string
	pRecord->set("pubInf", pubInf.c_str());

	CHistoryManager::getInstance()->addPublish(pRecord);
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

	m_strProvinceFrom = pRecord->get("strProvinceFrom");
	m_strCityFrom = pRecord->get("strCityFrom");
	m_strCountyFrom = pRecord->get("strCountyFrom");
	m_strProvinceTo = pRecord->get("strProvinceTo");
	m_strCityTo = pRecord->get("strCityTo");
	m_strCountyTo = pRecord->get("strCountyTo");

	SetListSection(goodsList, "goodsList");
	goodsCountValue = pRecord->get("goodsCountValue");
	SetComboSection(goodsUnit, "goodsUnit");

	SetListSection(truckLength, "truckLength");
	SetListSection(truckType, "truckType");

	truckCountValue = pRecord->get("truckCountValue");

	priceCountValue = pRecord->get("priceCountValue");
	SetListSection(priceList, "priceList");

	preview = pRecord->get("preview");

	SetComboSection(shipTime, "shipTime");
	SetComboSection(repubSetting, "repubSetting");

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

	UpdateData(FALSE);
}

void CPublishWayOneDlg::OnBnClickedButtonPw1Clean()
{
	preview.Empty();
	UpdateData(FALSE);
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
		MessageBox("请选择货物种类", "发布货源");
		return FALSE;
	}

	if (priceListValue == "" && priceCountValue != "")
	{
		MessageBox("请选择价格类型", "发布货源");
		return FALSE;
	}

	if (priceListValue != "" && priceCountValue == "")
	{
		MessageBox("价格不能为空", "发布货源");
		return FALSE;
	}

	if (m_strProvinceTo == "")
	{
		MessageBox("目的地：一级地址不能为空", "发布车源");
		return FALSE;
	}

	if( m_strCityTo == "" )
	{
		MessageBox("目的地：二级地址不能为空", "发布车源");
		return FALSE;
	}
	if( m_strCountyTo == "" )
	{
		MessageBox("目的地：三级地址不能为空", "发布车源");
		return FALSE;
	}

	return TRUE;
}

void CPublishWayOneDlg::BuildGoodsPreview()
{
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
		MessageBox("请选择货物种类", "发布车源");
		return FALSE;
	}

	if (m_strProvinceTo == "")
	{
		MessageBox("目的地：一级地址不能为空", "发布车源");
		return FALSE;
	}

	if( m_strCityTo == "" )
	{
		MessageBox("目的地：二级地址不能为空", "发布车源");
		return FALSE;
	}
	if( m_strCountyTo == "" )
	{
		MessageBox("目的地：三级地址不能为空", "发布车源");
		return FALSE;
	}

	if ( truckLengthValue == "" )
	{
		MessageBox("请选择车辆长度", "发布车源");
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
	if (CheckGoodsInfo() == FALSE)
	{
		return FALSE;
	}

	if (mobile == "") {
		MessageBox("联系电话不能为空", "发布货源");
		return FALSE;
	}

	CString		p, pu;

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

	if ( w == "" )
		w = "NULL";

	if ( tl == "" )
		tl = "NULL";

	if ( tt == "" )
		tt = "NULL";

	if ( tc == "" )
		tc = "NULL";

	CString tmp = m_strProvinceFrom + "|" + m_strCityFrom + "|" + m_strCountyFrom
		+ "|" + m_strProvinceTo + "|" + m_strCityTo + "|" + m_strCountyTo
		+ "|" + goodsValue + "|" + goodsCountValue + "|" + "NULL"
		+ "|" + "普货" + "|" + p + "|" + pu + "|NULL|" + tl + "|" + tt + "|"
		+ tc + "|" + mobile + "|" + shipTimeValue + "|" + repubSettingValue;

	if (rememberRepubSetting)
	{
		tmp = tmp + "|" + "1"; 
	}
	else
	{
		tmp = tmp + "|" + "0";
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

	if (mobile == "") {
		MessageBox("联系电话不能为空", "发布货源");
		return FALSE;
	}

	CString	tc = truckCountValue;
	CString w = goodsCountValue;
	CString tl = truckLengthValue;
	CString tt = truckTypeValue;

	if ( tc == "" )
		tc = "NULL";

	if ( w == "" )
		w = "NULL";

	if ( tl == "" )
		tl = "NULL";

	if ( tt == "" )
		tt = "NULL";

	CString tmp = m_strProvinceFrom + "|" + m_strCityFrom + "|" + m_strCountyFrom
		+ "|" + m_strProvinceTo + "|" + m_strCityTo + "|" + m_strCountyTo
		+ "|||||||"
		+ tc + "|" + w + "|NULL|" + tl + "|" + tt 
		+ "|" + goodsValue + "|普货|" + mobile + "|" + shipTimeValue + "|" + repubSettingValue;
	
	if (rememberRepubSetting)
	{
		tmp = tmp + "|" + "1"; 
	}
	else
	{
		tmp = tmp + "|" + "0";
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

