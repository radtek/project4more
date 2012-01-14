// PublishWayTwoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PublishWayTwoDlg.h"
#include "CommDef.h"
#include "ContentDlg.h"

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
	, name(_T(""))
	, shipTimeValue(_T(""))
	, repubSettingValue(_T(""))
	, autoClose(FALSE)
	, withoutFrom(FALSE)
	, withMobile(FALSE)
	, withName(FALSE)
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
	DDX_Text(pDX, IDC_EDIT_PW2_CONTACT_PHONE, name);
	DDX_CBString(pDX, IDC_COMBO_PW2_LDGOODS_DT, shipTimeValue);
	DDX_CBString(pDX, IDC_COMBO_PW2_REPUB_SETTING, repubSettingValue);
	DDX_Check(pDX, IDC_CHECK_CLOSE, autoClose);
	DDX_Check(pDX, IDC_CHECK_NO_FROM_ADDR, withoutFrom);
	DDX_Check(pDX, IDC_CHECK_PW2_CONTACT_NAME, withMobile);
	DDX_Check(pDX, IDC_CHECK_PW2_CONTACT_PHONE, withName);
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

	initControlValue();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CPublishWayTwoDlg::initControlValue()
{
	msgType.AddString("发布货源");
	msgType.AddString("发布车源");
	msgType.SetCurSel(0);

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

	goodsValue = "冻货";
	goodsCountValue = "";
	truckLengthValue = "";
	truckTypeValue = "";
	truckCountValue = "";
	priceListValue = "";
}

void CPublishWayTwoDlg::OnBnClickedButtonW1FromProvince()
{
	// TODO: Add your control notification handler code here
	vector<CString> vecItems;
	GetProvincesName(vecItems);

	CContentDlg dlgContent(this, GetDlgItem(IDC_EDIT_PW1_FROM_PROVINCE), &vecItems, &m_strProvinceFrom);
	dlgContent.DoModal();

	UpdateData(FALSE);
}

void CPublishWayTwoDlg::OnBnClickedButtonW1FromCity()
{
	// TODO: Add your control notification handler code here
	vector<CString> vecItems;
	GetCitiesNameByProvince(vecItems, m_strProvinceFrom);

	CContentDlg dlgContent(this, GetDlgItem(IDC_EDIT_PW1_FROM_CITY), &vecItems, &m_strCityFrom);
	dlgContent.DoModal();

	UpdateData(FALSE);
}

void CPublishWayTwoDlg::OnBnClickedButtonW1FromCounty()
{
	// TODO: Add your control notification handler code here
	vector<CString> vecItems;
	GetCountiesNameByProvinceAndCity(vecItems, m_strProvinceFrom, m_strCityFrom);

	CContentDlg dlgContent(this, GetDlgItem(IDC_EDIT_PW1_FROM_COUNTY), &vecItems, &m_strCountyFrom);
	dlgContent.DoModal();

	UpdateData(FALSE);
}

void CPublishWayTwoDlg::OnBnClickedButtonW1ToProvince()
{
	// TODO: Add your control notification handler code here
	vector<CString> vecItems;
	GetProvincesName(vecItems);

	CContentDlg dlgContent(this, GetDlgItem(IDC_EDIT_PW1_TO_PROVINCE), &vecItems, &m_strProvinceTo);
	dlgContent.DoModal();

	UpdateData(FALSE);
}

void CPublishWayTwoDlg::OnBnClickedButtonW1ToCity()
{
	// TODO: Add your control notification handler code here
	vector<CString> vecItems;
	GetCitiesNameByProvince(vecItems, m_strProvinceTo);

	CContentDlg dlgContent(this, GetDlgItem(IDC_EDIT_PW1_TO_CITY), &vecItems, &m_strCityTo);
	dlgContent.DoModal();

	UpdateData(FALSE);
}

void CPublishWayTwoDlg::OnBnClickedButtonW1ToCounty()
{
	// TODO: Add your control notification handler code here
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
	// TODO: Add your control notification handler code here
}

void CPublishWayTwoDlg::OnBnClickedButtonGood2()
{
	// TODO: Add your control notification handler code here
}

void CPublishWayTwoDlg::OnBnClickedButtonGood3()
{
	// TODO: Add your control notification handler code here
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
}

void CPublishWayTwoDlg::OnBnClickedButtonPw2Pub()
{
	// TODO: Add your control notification handler code here
	UpdateData();

	if ( goodsValue == "" )
	{
		MessageBox("请选择货物种类", "发布");
		return;
	}
	CString w = goodsCountValue;
	CString tl = truckLengthValue;
	CString tt = truckTypeValue;
	CString tc = truckCountValue;
	CString pu = priceListValue;

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

	CString tmp = m_strProvinceFrom + "|" + m_strCityFrom + "|" + m_strCountyFrom
		+ "|" + m_strProvinceTo + "|" + m_strCityTo + "|" + m_strCountyTo
		+ "|" + goodsValue + "|" + "1" + "|" + "NULL"
		+ "|" + "普货" + "|" + "1" + "|" + pu + "|NULL|" + tl + "|" + tt + "|"
		+ "1" + "|" + mobile + "|" + shipTimeValue + "|" + repubSettingValue;

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

	OnOK();
}

void CPublishWayTwoDlg::OnBnClickedButtonPw2Clean()
{
	// TODO: Add your control notification handler code here
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
