// PublishWayTwoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PublishWayTwoDlg.h"
#include "CommDef.h"
#include "ContentDlg.h"

extern int g_repubOption;

// CPublishWayTwoDlg dialog

IMPLEMENT_DYNAMIC(CPublishWayTwoDlg, CDialog)

CPublishWayTwoDlg::CPublishWayTwoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPublishWayTwoDlg::IDD, pParent)
	, m_strProvinceFrom(_T(""))
	, m_strCityFrom(_T(""))
	, m_strCountyFrom(_T(""))
	, m_strProvinceTo(_T(""))
	, m_strCityTo(_T(""))
	, m_strCountyTo(_T(""))
	, preview(_T(""))
	, mobile(_T(""))
	, mobile2(_T(""))
	, shipTimeValue(_T(""))
	, repubSettingValue(_T(""))
	, autoClose(FALSE)
	, withoutFrom(FALSE)
	, withMobile(FALSE)
	, withMobile2(FALSE)
	, longTimeAvailable(FALSE)
	, rememberRepubSetting(FALSE)
{
	publishKind = 0;
}

CPublishWayTwoDlg::~CPublishWayTwoDlg()
{
}

void CPublishWayTwoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_W1_FROM_PROVINCE, m_btnFromProvince);
	DDX_Control(pDX, IDC_BUTTON_W1_FROM_CITY, m_btnFromCity);
	DDX_Control(pDX, IDC_BUTTON_W1_FROM_COUNTY, m_btnFromCounty);
	DDX_Control(pDX, IDC_BUTTON_W1_TO_PROVINCE, m_btnToProvince);
	DDX_Control(pDX, IDC_BUTTON_W1_TO_CITY, m_btnToCity);
	DDX_Control(pDX, IDC_BUTTON_W1_TO_COUNTY, m_btnToCounty);
	DDX_Control(pDX, IDC_COMBO_INFO_TYPE, msgType);
	DDX_Control(pDX, IDC_COMBO_PW2_LDGOODS_DT, shipTime);
	DDX_Control(pDX, IDC_COMBO_PW2_REPUB_SETTING, repubSetting);
	DDX_Text(pDX, IDC_EDIT_PW1_FROM_PROVINCE, m_strProvinceFrom);
	DDX_Text(pDX, IDC_EDIT_PW1_FROM_CITY, m_strCityFrom);
	DDX_Text(pDX, IDC_EDIT_PW1_FROM_COUNTY, m_strCountyFrom);
	DDX_Text(pDX, IDC_EDIT_PW1_TO_PROVINCE, m_strProvinceTo);
	DDX_Text(pDX, IDC_EDIT_PW1_TO_CITY, m_strCityTo);
	DDX_Text(pDX, IDC_EDIT_PW1_TO_COUNTY, m_strCountyTo);
	DDX_Text(pDX, IDC_EDIT_PW2_PREVIEW, preview);
	DDX_Text(pDX, IDC_EDIT_PW2_CONTACT_NAME, mobile);
	DDX_Text(pDX, IDC_EDIT_PW2_CONTACT_PHONE, mobile2);
	DDX_CBString(pDX, IDC_COMBO_PW2_LDGOODS_DT, shipTimeValue);
	DDX_CBString(pDX, IDC_COMBO_PW2_REPUB_SETTING, repubSettingValue);
	DDX_Check(pDX, IDC_CHECK_CLOSE, autoClose);
	DDX_Check(pDX, IDC_CHECK_NO_FROM_ADDR, withoutFrom);
	DDX_Check(pDX, IDC_CHECK_PW2_CONTACT_NAME, withMobile);
	DDX_Check(pDX, IDC_CHECK_PW2_CONTACT_PHONE, withMobile2);
	DDX_Check(pDX, IDC_CHECK_PW2_LONGTIME, longTimeAvailable);
	DDX_Check(pDX, IDC_CHECK_PW2_REM_REPUB_SETTING, rememberRepubSetting);
}


BEGIN_MESSAGE_MAP(CPublishWayTwoDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_W1_FROM_PROVINCE, &CPublishWayTwoDlg::OnBnClickedButtonW1FromProvince)
	ON_BN_CLICKED(IDC_BUTTON_W1_FROM_CITY, &CPublishWayTwoDlg::OnBnClickedButtonW1FromCity)
	ON_BN_CLICKED(IDC_BUTTON_W1_FROM_COUNTY, &CPublishWayTwoDlg::OnBnClickedButtonW1FromCounty)
	ON_BN_CLICKED(IDC_BUTTON_W1_TO_PROVINCE, &CPublishWayTwoDlg::OnBnClickedButtonW1ToProvince)
	ON_BN_CLICKED(IDC_BUTTON_W1_TO_CITY, &CPublishWayTwoDlg::OnBnClickedButtonW1ToCity)
	ON_BN_CLICKED(IDC_BUTTON_W1_TO_COUNTY, &CPublishWayTwoDlg::OnBnClickedButtonW1ToCounty)
	ON_BN_CLICKED(IDC_BUTTON_NUM_ONE, &CPublishWayTwoDlg::OnBnClickedButtonNumOne)
	ON_BN_CLICKED(IDC_BUTTON_NUM_TWO, &CPublishWayTwoDlg::OnBnClickedButtonNumTwo)
	ON_BN_CLICKED(IDC_BUTTON_NUM_THREE, &CPublishWayTwoDlg::OnBnClickedButtonNumThree)
	ON_BN_CLICKED(IDC_BUTTON_NUM_FOUR, &CPublishWayTwoDlg::OnBnClickedButtonNumFour)
	ON_BN_CLICKED(IDC_BUTTON_NUM_FIVE, &CPublishWayTwoDlg::OnBnClickedButtonNumFive)
	ON_BN_CLICKED(IDC_BUTTON_NUM_SIX, &CPublishWayTwoDlg::OnBnClickedButtonNumSix)
	ON_BN_CLICKED(IDC_BUTTON_NUM_SEVEN, &CPublishWayTwoDlg::OnBnClickedButtonNumSeven)
	ON_BN_CLICKED(IDC_BUTTON_NUM_EIGHT, &CPublishWayTwoDlg::OnBnClickedButtonNumEight)
	ON_BN_CLICKED(IDC_BUTTON_NUM_NINE, &CPublishWayTwoDlg::OnBnClickedButtonNumNine)
	ON_BN_CLICKED(IDC_BUTTON_NUM_ZERO, &CPublishWayTwoDlg::OnBnClickedButtonNumZero)
	ON_BN_CLICKED(IDC_BUTTON_NUM_D_ZERO, &CPublishWayTwoDlg::OnBnClickedButtonNumDZero)
	ON_BN_CLICKED(IDC_BUTTON_NUM_PERIOD, &CPublishWayTwoDlg::OnBnClickedButtonNumPeriod)
	ON_BN_CLICKED(IDC_BUTTON_NUM_COMMA, &CPublishWayTwoDlg::OnBnClickedButtonNumComma)
	ON_BN_CLICKED(IDC_BUTTON_NUM_DOT, &CPublishWayTwoDlg::OnBnClickedButtonNumDot)
	ON_BN_CLICKED(IDC_BUTTON_NUM_SEMICOLON, &CPublishWayTwoDlg::OnBnClickedButtonNumSemicolon)
	ON_BN_CLICKED(IDC_BUTTON_NUM_HYPHEN, &CPublishWayTwoDlg::OnBnClickedButtonNumHyphen)
	ON_BN_CLICKED(IDC_BUTTON_NUM_SLASH, &CPublishWayTwoDlg::OnBnClickedButtonNumSlash)
	ON_BN_CLICKED(IDC_BUTTON_NUM_R_BRACKET, &CPublishWayTwoDlg::OnBnClickedButtonNumRBracket)
	ON_BN_CLICKED(IDC_BUTTON_NUM_ARROW, &CPublishWayTwoDlg::OnBnClickedButtonNumArrow)
	ON_BN_CLICKED(IDC_BUTTON_JI, &CPublishWayTwoDlg::OnBnClickedButtonJi)
	ON_BN_CLICKED(IDC_BUTTON_XU, &CPublishWayTwoDlg::OnBnClickedButtonXu)
	ON_BN_CLICKED(IDC_BUTTON_YAO, &CPublishWayTwoDlg::OnBnClickedButtonYao)
	ON_BN_CLICKED(IDC_BUTTON_QIU, &CPublishWayTwoDlg::OnBnClickedButtonQiu)
	ON_BN_CLICKED(IDC_BUTTON_FA, &CPublishWayTwoDlg::OnBnClickedButtonFa)
	ON_BN_CLICKED(IDC_BUTTON_DAO, &CPublishWayTwoDlg::OnBnClickedButtonDao)
	ON_BN_CLICKED(IDC_BUTTON_HUI, &CPublishWayTwoDlg::OnBnClickedButtonHui)
	ON_BN_CLICKED(IDC_BUTTON_QU, &CPublishWayTwoDlg::OnBnClickedButtonQu)
	ON_BN_CLICKED(IDC_BUTTON_CHE, &CPublishWayTwoDlg::OnBnClickedButtonChe)
	ON_BN_CLICKED(IDC_BUTTON_HUO, &CPublishWayTwoDlg::OnBnClickedButtonHuo)
	ON_BN_CLICKED(IDC_BUTTON_DIAN, &CPublishWayTwoDlg::OnBnClickedButtonDian)
	ON_BN_CLICKED(IDC_BUTTON_DUN, &CPublishWayTwoDlg::OnBnClickedButtonDun)
	ON_BN_CLICKED(IDC_BUTTON_MI, &CPublishWayTwoDlg::OnBnClickedButtonMi)
	ON_BN_CLICKED(IDC_BUTTON_YUAN, &CPublishWayTwoDlg::OnBnClickedButtonYuan)
	ON_BN_CLICKED(IDC_BUTTON_YUAN_DUN, &CPublishWayTwoDlg::OnBnClickedButtonYuanDun)
	ON_BN_CLICKED(IDC_BUTTON_UNIT, &CPublishWayTwoDlg::OnBnClickedButtonUnit)
	ON_BN_CLICKED(IDC_BUTTON_BACKSPACE, &CPublishWayTwoDlg::OnBnClickedButtonBackspace)
	ON_BN_CLICKED(IDC_BUTTON_GOOD1, &CPublishWayTwoDlg::OnBnClickedButtonGood1)
	ON_BN_CLICKED(IDC_BUTTON_GOOD2, &CPublishWayTwoDlg::OnBnClickedButtonGood2)
	ON_BN_CLICKED(IDC_BUTTON_GOOD3, &CPublishWayTwoDlg::OnBnClickedButtonGood3)
	ON_BN_CLICKED(IDC_BUTTON_CAR_SIZE, &CPublishWayTwoDlg::OnBnClickedButtonCarSize)
	ON_BN_CLICKED(IDC_BUTTON_CAR_TYPE, &CPublishWayTwoDlg::OnBnClickedButtonCarType)
	ON_BN_CLICKED(IDC_BUTTON_PRICE, &CPublishWayTwoDlg::OnBnClickedButtonPrice)
	ON_BN_CLICKED(IDC_BUTTON_PHRASE, &CPublishWayTwoDlg::OnBnClickedButtonPhrase)
	ON_BN_CLICKED(IDC_BUTTON_SPECIAL, &CPublishWayTwoDlg::OnBnClickedButtonSpecial)
	ON_BN_CLICKED(IDC_BUTTON_CHARACTER, &CPublishWayTwoDlg::OnBnClickedButtonCharacter)
	ON_BN_CLICKED(IDC_BUTTON_WORD, &CPublishWayTwoDlg::OnBnClickedButtonWord)
	ON_BN_CLICKED(IDC_BUTTON_PW2_HISTORY, &CPublishWayTwoDlg::OnBnClickedButtonPw2History)
	ON_BN_CLICKED(IDC_BUTTON_PW2_PUB, &CPublishWayTwoDlg::OnBnClickedButtonPw2Pub)
	ON_BN_CLICKED(IDC_BUTTON_PW2_CLEAN, &CPublishWayTwoDlg::OnBnClickedButtonPw2Clean)
	ON_BN_CLICKED(IDC_BUTTON_PW2_CLOSE, &CPublishWayTwoDlg::OnBnClickedButtonPw2Close)
	ON_CBN_SELCHANGE(IDC_COMBO_INFO_TYPE, &CPublishWayTwoDlg::OnCbnSelchangeComboInfoType)
END_MESSAGE_MAP()


// CPublishWayTwoDlg message handlers

BOOL CPublishWayTwoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_btnFromProvince.LoadBitmap(IDB_BITMAP_COMMON_BTN);
	m_btnFromCity.LoadBitmap(IDB_BITMAP_COMMON_BTN);
	m_btnFromCounty.LoadBitmap(IDB_BITMAP_COMMON_BTN);
	m_btnToProvince.LoadBitmap(IDB_BITMAP_COMMON_BTN);
	m_btnToCity.LoadBitmap(IDB_BITMAP_COMMON_BTN);
	m_btnToCounty.LoadBitmap(IDB_BITMAP_COMMON_BTN);


	((CEdit*)GetDlgItem(IDC_EDIT_PW2_PREVIEW))->SetLimitText(256);

	initControlValue();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CPublishWayTwoDlg::initControlValue()
{
	pRecord = NULL;
	pPublishRecord = NULL;

	msgType.AddString("发布货源");
	msgType.AddString("发布车源");
	msgType.SetCurSel(0);

	mobile = userInfo.tel.c_str();
	
	withMobile = TRUE;

	goodsValue = "";
	goodsCountValue = "";
	truckLengthValue = "";
	truckTypeValue = "";
	truckCountValue = "";
	priceListValue = "";

	m_strProvinceFrom = userInfo.province.c_str();
	if( IsSpecialProvince(m_strProvinceFrom) )
	{
		m_strCityFrom = m_strProvinceFrom;
	}
	if( userInfo.province != userInfo.city )
	{
		m_strCountyFrom = userInfo.city.c_str();
	}
	else
	{
		m_strCountyFrom = NO_LIMIT_STRING;
	}

	truckCountValue = "1";

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

void CPublishWayTwoDlg::OnBnClickedButtonW1FromProvince()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	vector<CString> vecItems;
	GetProvincesName(vecItems);

	CContentDlg dlgContent(this, GetDlgItem(IDC_EDIT_PW1_FROM_PROVINCE), &vecItems, &m_strProvinceFrom);
	if( dlgContent.DoModal() == IDOK && !m_strProvinceFrom.IsEmpty() )
	{
		m_strCityFrom = m_strCountyFrom = NO_LIMIT_STRING;
	}

	UpdateData(FALSE);
}

void CPublishWayTwoDlg::OnBnClickedButtonW1FromCity()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	vector<CString> vecItems;
	GetCitiesNameByProvince(vecItems, m_strProvinceFrom);

	CContentDlg dlgContent(this, GetDlgItem(IDC_EDIT_PW1_FROM_CITY), &vecItems, &m_strCityFrom);
	if( dlgContent.DoModal() == IDOK && !m_strCityFrom.IsEmpty())
	{
		m_strCountyFrom = NO_LIMIT_STRING;
	}

	UpdateData(FALSE);
}

void CPublishWayTwoDlg::OnBnClickedButtonW1FromCounty()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	vector<CString> vecItems;
	GetCountiesNameByProvinceAndCity(vecItems, m_strProvinceFrom, m_strCityFrom);

	CContentDlg dlgContent(this, GetDlgItem(IDC_EDIT_PW1_FROM_COUNTY), &vecItems, &m_strCountyFrom);
	dlgContent.DoModal();

	UpdateData(FALSE);
}

void CPublishWayTwoDlg::OnBnClickedButtonW1ToProvince()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	vector<CString> vecItems;
	GetProvincesName(vecItems);

	CContentDlg dlgContent(this, GetDlgItem(IDC_EDIT_PW1_TO_PROVINCE), &vecItems, &m_strProvinceTo);
	if( dlgContent.DoModal() == IDOK && !m_strProvinceTo.IsEmpty() )
	{
		m_strCityTo = m_strCountyTo = NO_LIMIT_STRING;
	}

	UpdateData(FALSE);
}

void CPublishWayTwoDlg::OnBnClickedButtonW1ToCity()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	vector<CString> vecItems;
	GetCitiesNameByProvince(vecItems, m_strProvinceTo);

	CContentDlg dlgContent(this, GetDlgItem(IDC_EDIT_PW1_TO_CITY), &vecItems, &m_strCityTo);
	if( dlgContent.DoModal() == IDOK && !m_strCityTo.IsEmpty())
	{
		m_strCountyTo = NO_LIMIT_STRING;
	}

	/*if ( m_strCityTo == "不限" )
	{
		m_strCountyTo = "";
	}*/

	UpdateData(FALSE);
}

void CPublishWayTwoDlg::OnBnClickedButtonW1ToCounty()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	vector<CString> vecItems;
	GetCountiesNameByProvinceAndCity(vecItems, m_strProvinceTo, m_strCityTo);

	CContentDlg dlgContent(this, GetDlgItem(IDC_EDIT_PW1_TO_COUNTY), &vecItems, &m_strCountyTo);
	dlgContent.DoModal();

	UpdateData(FALSE);
}

void CPublishWayTwoDlg::appendToPreview(CString str)
{
	UpdateData();
	preview += str;
	UpdateData(FALSE);
}

void CPublishWayTwoDlg::OnBnClickedButtonNumOne()
{
	// TODO: Add your control notification handler code here
	appendToPreview("1");
}

void CPublishWayTwoDlg::OnBnClickedButtonNumTwo()
{
	// TODO: Add your control notification handler code here
	appendToPreview("2");
}

void CPublishWayTwoDlg::OnBnClickedButtonNumThree()
{
	// TODO: Add your control notification handler code here
	appendToPreview("3");
}

void CPublishWayTwoDlg::OnBnClickedButtonNumFour()
{
	// TODO: Add your control notification handler code here
	appendToPreview("4");
}

void CPublishWayTwoDlg::OnBnClickedButtonNumFive()
{
	// TODO: Add your control notification handler code here
	appendToPreview("5");
}

void CPublishWayTwoDlg::OnBnClickedButtonNumSix()
{
	// TODO: Add your control notification handler code here
	appendToPreview("6");
}

void CPublishWayTwoDlg::OnBnClickedButtonNumSeven()
{
	// TODO: Add your control notification handler code here
	appendToPreview("7");
}

void CPublishWayTwoDlg::OnBnClickedButtonNumEight()
{
	// TODO: Add your control notification handler code here
	appendToPreview("8");
}

void CPublishWayTwoDlg::OnBnClickedButtonNumNine()
{
	// TODO: Add your control notification handler code here
	appendToPreview("9");
}

void CPublishWayTwoDlg::OnBnClickedButtonNumZero()
{
	// TODO: Add your control notification handler code here
	appendToPreview("0");
}

void CPublishWayTwoDlg::OnBnClickedButtonNumDZero()
{
	// TODO: Add your control notification handler code here
	appendToPreview("00");
}

void CPublishWayTwoDlg::OnBnClickedButtonNumPeriod()
{
	// TODO: Add your control notification handler code here
	appendToPreview("。");
}

void CPublishWayTwoDlg::OnBnClickedButtonNumComma()
{
	// TODO: Add your control notification handler code here
	appendToPreview("，");
}

void CPublishWayTwoDlg::OnBnClickedButtonNumDot()
{
	// TODO: Add your control notification handler code here
	appendToPreview(".");
}

void CPublishWayTwoDlg::OnBnClickedButtonNumSemicolon()
{
	// TODO: Add your control notification handler code here
	appendToPreview("；");
}

void CPublishWayTwoDlg::OnBnClickedButtonNumHyphen()
{
	// TODO: Add your control notification handler code here
	appendToPreview("-");
}

void CPublishWayTwoDlg::OnBnClickedButtonNumSlash()
{
	// TODO: Add your control notification handler code here
	appendToPreview("/");
}

void CPublishWayTwoDlg::OnBnClickedButtonNumRBracket()
{
	// TODO: Add your control notification handler code here
	appendToPreview(">");
}

void CPublishWayTwoDlg::OnBnClickedButtonNumArrow()
{
	// TODO: Add your control notification handler code here
	appendToPreview("-->");
}

void CPublishWayTwoDlg::OnBnClickedButtonJi()
{
	// TODO: Add your control notification handler code here
	appendToPreview("急");
}

void CPublishWayTwoDlg::OnBnClickedButtonXu()
{
	// TODO: Add your control notification handler code here
	appendToPreview("需");
}

void CPublishWayTwoDlg::OnBnClickedButtonYao()
{
	// TODO: Add your control notification handler code here
	appendToPreview("要");
}

void CPublishWayTwoDlg::OnBnClickedButtonQiu()
{
	// TODO: Add your control notification handler code here
	appendToPreview("求");
}

void CPublishWayTwoDlg::OnBnClickedButtonFa()
{
	// TODO: Add your control notification handler code here
	appendToPreview("发");
}

void CPublishWayTwoDlg::OnBnClickedButtonDao()
{
	// TODO: Add your control notification handler code here
	appendToPreview("到");
}

void CPublishWayTwoDlg::OnBnClickedButtonHui()
{
	// TODO: Add your control notification handler code here
	appendToPreview("回");
}

void CPublishWayTwoDlg::OnBnClickedButtonQu()
{
	// TODO: Add your control notification handler code here
	appendToPreview("去");
}

void CPublishWayTwoDlg::OnBnClickedButtonChe()
{
	// TODO: Add your control notification handler code here
	appendToPreview("车");
}

void CPublishWayTwoDlg::OnBnClickedButtonHuo()
{
	// TODO: Add your control notification handler code here
	appendToPreview("货");
}

void CPublishWayTwoDlg::OnBnClickedButtonDian()
{
	// TODO: Add your control notification handler code here
	appendToPreview("电");
}

void CPublishWayTwoDlg::OnBnClickedButtonDun()
{
	// TODO: Add your control notification handler code here
	appendToPreview("吨");
}

void CPublishWayTwoDlg::OnBnClickedButtonMi()
{
	// TODO: Add your control notification handler code here
	appendToPreview("米");
}

void CPublishWayTwoDlg::OnBnClickedButtonYuan()
{
	// TODO: Add your control notification handler code here
	appendToPreview("元");
}

void CPublishWayTwoDlg::OnBnClickedButtonYuanDun()
{
	// TODO: Add your control notification handler code here
	appendToPreview("元/吨");
}

void CPublishWayTwoDlg::OnBnClickedButtonUnit()
{
	// TODO: Add your control notification handler code here
	appendToPreview("[单位]");
}

void CPublishWayTwoDlg::OnBnClickedButtonBackspace()
{
	// TODO: Add your control notification handler code here
	int		l = preview.GetLength();
	if( l == 0 )
	{
		return ;
	}
	wchar_t *pwszPreview = NULL;
	int nWideCharLen = ::MultiByteToWideChar(CP_ACP, 0, preview, l+1, NULL, 0);
	pwszPreview = new wchar_t[nWideCharLen+1];
	::MultiByteToWideChar(CP_ACP, 0, preview, l+1, pwszPreview, nWideCharLen+1);
	int nLength = wcslen(pwszPreview);
	pwszPreview[nLength-1] = L'\0';

	int nMultiByteLen = nWideCharLen*2+2;
	char *pszPreview = new char[nMultiByteLen];
	memset(pszPreview, 0, nMultiByteLen);
	WideCharToMultiByte(CP_ACP, 0, pwszPreview, nWideCharLen-1, pszPreview, nMultiByteLen, NULL, NULL);

	preview = pszPreview;
	delete []pwszPreview;
	delete []pszPreview;
	UpdateData(FALSE);
}

void CPublishWayTwoDlg::OnBnClickedButtonGood1()
{
	RECT rc;
	GetDlgItem(IDC_BUTTON_GOOD1)->GetWindowRect(&rc);
	int nItem = g_menuGoods1.TrackPopupMenu(TPM_LEFTALIGN |TPM_RIGHTBUTTON|TPM_RETURNCMD, rc.left, rc.bottom, this);
	if( nItem != 0 )
	{
		CString sGoods;
		g_menuGoods1.GetMenuString(nItem, sGoods, MF_BYCOMMAND);
		appendToPreview(sGoods);
		goodsValue = sGoods;
	}
}

void CPublishWayTwoDlg::OnBnClickedButtonGood2()
{
	RECT rc;
	GetDlgItem(IDC_BUTTON_GOOD2)->GetWindowRect(&rc);
	int nItem = g_menuGoods2.TrackPopupMenu(TPM_LEFTALIGN |TPM_RIGHTBUTTON|TPM_RETURNCMD, rc.left, rc.bottom, this);
	if( nItem != 0 )
	{
		CString sGoods;
		g_menuGoods2.GetMenuString(nItem, sGoods, MF_BYCOMMAND);
		appendToPreview(sGoods);
		goodsValue = sGoods;
	}
}

void CPublishWayTwoDlg::OnBnClickedButtonGood3()
{
	RECT rc;
	GetDlgItem(IDC_BUTTON_GOOD3)->GetWindowRect(&rc);
	int nItem = g_menuGoods3.TrackPopupMenu(TPM_LEFTALIGN |TPM_RIGHTBUTTON|TPM_RETURNCMD, rc.left, rc.bottom, this);
	if( nItem != 0 )
	{
		CString sGoods;
		g_menuGoods3.GetMenuString(nItem, sGoods, MF_BYCOMMAND);
		appendToPreview(sGoods);
		goodsValue = sGoods;
	}
}

void CPublishWayTwoDlg::OnBnClickedButtonCarSize()
{
	// TODO: Add your control notification handler code here
	CString  result;
	CContentDlg dlgContent(this, GetDlgItem(IDC_BUTTON_CAR_SIZE), &g_truckLength, &result);
	if (dlgContent.DoModal() == IDOK)
	{
		appendToPreview(result);
	}
	truckLengthValue = result;
}

void CPublishWayTwoDlg::OnBnClickedButtonCarType()
{
	// TODO: Add your control notification handler code here
	CString  result;
	CContentDlg dlgContent(this, GetDlgItem(IDC_BUTTON_CAR_TYPE), &g_truckType, &result);
	if (dlgContent.DoModal() == IDOK)
	{
		appendToPreview(result);
	}
	truckTypeValue = result;
}

void CPublishWayTwoDlg::OnBnClickedButtonPrice()
{
	// TODO: Add your control notification handler code here
	CString  result;
	CContentDlg dlgContent(this, GetDlgItem(IDC_BUTTON_PRICE), &g_priceTypeFor3, &result);
	if (dlgContent.DoModal() == IDOK)
	{
		appendToPreview(result);
	}

	priceListValue = result;
}

void CPublishWayTwoDlg::OnBnClickedButtonPhrase()
{
	// TODO: Add your control notification handler code here
	CString  result;
	CContentDlg dlgContent(this, GetDlgItem(IDC_BUTTON_PHRASE), &g_commonDuanyu, &result);
	if (dlgContent.DoModal() == IDOK)
	{
		appendToPreview(result);
	}
}

void CPublishWayTwoDlg::OnBnClickedButtonSpecial()
{
	// TODO: Add your control notification handler code here
}

void CPublishWayTwoDlg::OnBnClickedButtonCharacter()
{
	// TODO: Add your control notification handler code here
	CString  result;
	CContentDlg dlgContent(this, GetDlgItem(IDC_BUTTON_CHARACTER), &g_commonZi, &result);
	if (dlgContent.DoModal() == IDOK)
	{
		appendToPreview(result);
	}
}

void CPublishWayTwoDlg::OnBnClickedButtonWord()
{
	// TODO: Add your control notification handler code here
	CString  result;
	CContentDlg dlgContent(this, GetDlgItem(IDC_BUTTON_WORD), &g_commonCi, &result);
	if (dlgContent.DoModal() == IDOK)
	{
		appendToPreview(result);
	}
}

void CPublishWayTwoDlg::OnBnClickedButtonPw2History()
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

BOOL CPublishWayTwoDlg::PublishGoodsInfo()
{
	//if ( goodsValue == "" )
	//{
	//	MessageBox("请选择货物种类");//, "发布货源");
	//	return FALSE;
	//}

	//if ( preview == "" )
	//{
	//	MessageBox("请先生成预览");//, "发布货源");
	//	return FALSE;
	//}

	if ( withMobile && mobile.IsEmpty() ) 
	{
		MessageBox("联系电话1不能为空");//, "发布货源");
		return FALSE;
	}

	if ( withMobile2 && mobile2.IsEmpty() ) 
	{
		MessageBox("联系电话2不能为空");//, "发布货源");
		return FALSE;
	}

	if( mobile.IsEmpty() && mobile2.IsEmpty() )
	{
		MessageBox("联系电话不能为空");//, "发布货源");
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

	CString w = goodsCountValue;
	CString tl = truckLengthValue;
	CString tt = truckTypeValue;
	CString tc = truckCountValue;
	CString pu = priceListValue;
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

	if ( pu == "" )
		pu = "NULL";

	if ( ct == "" )
		ct = "不限";

	if ( cf == "" )
		cf = "不限";

	CString tmp = m_strProvinceFrom + "|" + m_strCityFrom + "|" + cf
		+ "|" + m_strProvinceTo + "|" + m_strCityTo + "|" + ct
		+ "|" + goodsValue + "|" + "1" + "|" + "NULL"
		+ "|" + "普货" + "|" + "1" + "|" + pu + "|NULL|" + tl + "|" + tt + "|"
		+ "1" + "|" + (withMobile?mobile:"") + ((withMobile2&&!mobile2.IsEmpty())?(" "+mobile2):"") + "|" + shipTimeValue + "|" + repubSettingValue;

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

BOOL CPublishWayTwoDlg::PublishTruckInfo()
{
	//if ( goodsValue == "" )
	//{
	//	MessageBox("请选择货物种类");//, "发布车源");
	//	return FALSE;
	//}

	if ( preview == "" )
	{
		MessageBox("请先生成预览");//, "发布车源");
		return FALSE;
	}

	if ( withMobile && mobile.IsEmpty() ) 
	{
		MessageBox("联系电话1不能为空");//, "发布车源");
		return FALSE;
	}

	if ( withMobile2 && mobile2.IsEmpty() ) 
	{
		MessageBox("联系电话2不能为空");//, "发布车源");
		return FALSE;
	}

	if( mobile.IsEmpty() && mobile2.IsEmpty() )
	{
		MessageBox("联系电话不能为空");//, "发布车源");
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

	//if ( truckLengthValue == "" )
	//{
	//	MessageBox("请选择车辆长度");//, "发布车源");
	//	return FALSE;
	//}

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

void CPublishWayTwoDlg::OnBnClickedButtonPw2Pub()
{
	// TODO: Add your control notification handler code here
	UpdateData();

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

void CPublishWayTwoDlg::OnBnClickedButtonPw2Clean()
{
	preview.Empty();
	UpdateData(FALSE);
}

void CPublishWayTwoDlg::OnBnClickedButtonPw2Close()
{
	// TODO: Add your control notification handler code here
	OnCancel();
}

void CPublishWayTwoDlg::OnCbnSelchangeComboInfoType()
{
	// TODO: Add your control notification handler code here
	if ( msgType.GetCurSel() == 0 )
	{
		publishKind = 0;
	}
	else
	{
		publishKind = 1;
	}
}

void CPublishWayTwoDlg::SetComboSection(CComboBox& b, string k)
{
	CString v = pRecord->get(k);

	if ( v == "" )
	{
		return;
	}

	int n = atoi((LPSTR)(LPCTSTR)v);
	b.SetCurSel(n);
}

void CPublishWayTwoDlg::SetListSection(CListBox& b, string k)
{
	CString v = pRecord->get(k);

	if ( v == "" )
	{
		return;
	}

	int n = atoi((LPSTR)(LPCTSTR)v);
	b.SetCurSel(n);
}

void CPublishWayTwoDlg::ToHistory()
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
	pPublishRecord->set("goodsValue", goodsValue);
	pPublishRecord->set("goodsCountValue", goodsCountValue);

	// truck info
	pPublishRecord->set("truckLengthValue", truckLengthValue);
	pPublishRecord->set("truckTypeValue", truckTypeValue);
	pPublishRecord->set("truckCountValue", truckCountValue);

	// price info
	pPublishRecord->set("priceListValue", priceListValue);

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

	//CHistoryManager::getInstance()->addPublish(pPublishRecord);
}

void CPublishWayTwoDlg::SaveHistory()
{
	if ( pPublishRecord == NULL )
	{
		return;
	}
	CHistoryManager::getInstance()->addPublish(pPublishRecord);
}

void CPublishWayTwoDlg::FromHistory()
{
	if ( pRecord == NULL )
	{
		return;
	}

	SetComboSection(msgType, "msgType");

	if ( msgType.GetCurSel() == 0 )
	{
		publishKind = 0;
	}
	else
	{
		publishKind = 1;
	}

	m_strProvinceFrom = pRecord->get("strProvinceFrom");
	m_strCityFrom = pRecord->get("strCityFrom");
	m_strCountyFrom = pRecord->get("strCountyFrom");
	m_strProvinceTo = pRecord->get("strProvinceTo");
	m_strCityTo = pRecord->get("strCityTo");
	m_strCountyTo = pRecord->get("strCountyTo");

	goodsValue = pRecord->get("goodsValue");
	goodsCountValue = pRecord->get("goodsCountValue");

	truckLengthValue = pRecord->get("truckLengthValue");
	truckTypeValue = pRecord->get("truckTypeValue");
	truckCountValue = pRecord->get("truckCountValue");

	priceListValue = pRecord->get("priceListValue");

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

	UpdateData(FALSE);


	SetComboSection(shipTime, "shipTime");
	SetComboSection(repubSetting, "repubSetting");

	UpdateData();
}