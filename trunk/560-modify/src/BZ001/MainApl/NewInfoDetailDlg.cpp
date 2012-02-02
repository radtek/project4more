// DetailInfoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "NewInfoDetailDlg.h"
#include "TabCustomInfDlg.h"
#include "TabNewInfDlg.h"
#include "TabMyInfDlg.h"
#include "GLB.h"

extern UserInfo user;


// CNewInfoDetailDlg 对话框

IMPLEMENT_DYNAMIC(CNewInfoDetailDlg, CDialog)

CNewInfoDetailDlg::CNewInfoDetailDlg(const void* pInfoDetail, int nInfoType, CWnd* pParent /*=NULL*/)
	: CDialog(CNewInfoDetailDlg::IDD, pParent), m_pInfoDetail(pInfoDetail), m_nInfoType(nInfoType)
{
}

CNewInfoDetailDlg::~CNewInfoDetailDlg()
{
}

void CNewInfoDetailDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_PUBLISHER, m_publisher);
}


BEGIN_MESSAGE_MAP(CNewInfoDetailDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CNewInfoDetailDlg::OnBnClickedButtonClose)
	ON_BN_CLICKED(IDC_BUTTON_SEND_SMS, &CNewInfoDetailDlg::OnBnClickedButtonSendSms)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CNewInfoDetailDlg 消息处理程序

BOOL CNewInfoDetailDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_publisher.SetBackgroundColor(RGB(235,242,251));

	if( m_nInfoType == eInfoType_Goods || m_nInfoType == eInfoType_Cars )
	{
		InitNewInfoDetail((const TabNewInfRecord*)m_pInfoDetail);
	}
	else if( m_nInfoType == eInfoType_CustomGoods || m_nInfoType == eInfoType_MyCars)
	{
		InitCustomInfoDetail((const TabCustomInfRecord*)m_pInfoDetail);
	}
	else
	{
		InitMyInfoDetail((const TabMyInfRecord*)m_pInfoDetail);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CNewInfoDetailDlg::OnBnClickedButtonClose()
{
	CDialog::OnOK();
}

void CNewInfoDetailDlg::OnBnClickedButtonSendSms()
{
	if( m_nInfoType == eInfoType_Goods || m_nInfoType == eInfoType_Cars )
	{
		((CTabNewInfDlg*)m_pParentWnd)->SendSMS(*(const TabNewInfRecord*)m_pInfoDetail);
	}
	else if( m_nInfoType == eInfoType_CustomGoods || m_nInfoType == eInfoType_MyCars)
	{
		((CTabCustomInfDlg*)m_pParentWnd)->SendSMS(*(const TabCustomInfRecord*)m_pInfoDetail);
	}
	else
	{
		((CTabMyInfDlg*)m_pParentWnd)->SendSMS(*(const TabMyInfRecord*)m_pInfoDetail);
	}
}

HBRUSH CNewInfoDetailDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if( nCtlColor == CTLCOLOR_DLG )
	{
		return (HBRUSH)CreateSolidBrush(RGB(235,242,251));
	}
	if( nCtlColor == CTLCOLOR_STATIC )
	{
		pDC->SetBkMode(TRANSPARENT);
		
		int nCtrlID = pWnd->GetDlgCtrlID();
		if( nCtrlID == IDC_STATIC_CONTACT_INFO || nCtrlID == IDC_STATIC_INFO_ID )
		{
			pDC->SetTextColor(RGB(188,51,58));
		}
		else if( nCtrlID == IDC_STATIC_ADDR_INFO )
		{
			LOGFONT logFont;
			memset(&logFont,0,sizeof(logFont));
			strncpy(logFont.lfFaceName,"黑体",LF_FACESIZE);
			logFont.lfPitchAndFamily = FF_SWISS;
			logFont.lfQuality = ANTIALIASED_QUALITY;
			logFont.lfWeight = 6000;
			logFont.lfHeight = 110;

			CFont font;
			// actually create the font; if for some reason this fails, use a default
			if ( !font.CreatePointFontIndirect(&logFont) )
			{
				font.CreateStockObject(SYSTEM_FONT);
			}
			CFont* pOldFont = pDC->SelectObject(&font);
		}
		
		if( nCtrlID == IDC_STATIC_CONTACT_INFO || nCtrlID == IDC_STATIC_INFO_DESC || nCtrlID == IDC_STATIC_ADDR_INFO)
		{
			return (HBRUSH)GetStockObject(WHITE_BRUSH); 
		}
		return   (HBRUSH)GetStockObject(HOLLOW_BRUSH); 
	}
	
	return hbr;
}


void CNewInfoDetailDlg::InitNewInfoDetail(const TabNewInfRecord* pInfoDetail)
{
	GetDlgItem(IDC_STATIC_INFO_ID)->SetWindowText(CString("信息编号： ") + pInfoDetail->recordID.c_str());
	GetDlgItem(IDC_STATIC_PUB_ADDR)->SetWindowText(CString("发布地区： ") + pInfoDetail->pubAddress.c_str());
	GetDlgItem(IDC_STATIC_PUB_DT)->SetWindowText(CString("发布时间： ") + pInfoDetail->pubTime.c_str());
	GetDlgItem(IDC_STATIC_DT_SCHEDULE)->SetWindowText((m_nInfoType==eInfoType_Goods?CString("装货日期： "):CString("发车日期： ")) + pInfoDetail->dateTime.c_str());
	GetDlgItem(IDC_STATIC_INFO_STATUS)->SetWindowText(CString("信息状态： ") + pInfoDetail->state.c_str());
	GetDlgItem(IDC_STATIC_ADDR_INFO)->SetWindowText( (pInfoDetail->startPlace + "→" + pInfoDetail->endPlace).c_str() );
	GetDlgItem(IDC_STATIC_INFO_DESC)->SetWindowText(pInfoDetail->record.c_str());
	GetDlgItem(IDC_STATIC_CONTACT_INFO)->SetWindowText(pInfoDetail->tel.c_str());

	 //"/fmp/user.login.action?username="+$当前用户登录名+"&password="+$当前用户登录密码+"&userid="+$发布者ID+"&target=userCenter";
	string sUrl = WEB_SERVICE_ADDRESS+"/fmp/user.login.action?username="+user.loginName+"&password="+user.passWord+"&userid="+pInfoDetail->pubUID+"&target=userCenter";
	m_publisher.SetLinkText(pInfoDetail->pubName.c_str());
	m_publisher.SetMultiline(TRUE);
	m_publisher.SetLinkUrl(sUrl.c_str());
}
void CNewInfoDetailDlg::InitCustomInfoDetail(const TabCustomInfRecord* pInfoDetail)
{
	GetDlgItem(IDC_STATIC_INFO_ID)->SetWindowText(CString("信息编号： ") + pInfoDetail->recordID.c_str());
	GetDlgItem(IDC_STATIC_PUB_ADDR)->SetWindowText(CString("发布地区： ") + pInfoDetail->pubAddress.c_str());
	GetDlgItem(IDC_STATIC_PUB_DT)->SetWindowText(CString("发布时间： ") + pInfoDetail->pubTime.c_str());
	GetDlgItem(IDC_STATIC_DT_SCHEDULE)->SetWindowText((m_nInfoType==eInfoType_CustomGoods?CString("装货日期： "):CString("发车日期： ")) + pInfoDetail->dateTime.c_str());
	GetDlgItem(IDC_STATIC_INFO_STATUS)->SetWindowText(CString("信息状态： ") + pInfoDetail->state.c_str());
	GetDlgItem(IDC_STATIC_ADDR_INFO)->SetWindowText( (pInfoDetail->startPlace + "→" + pInfoDetail->endPlace).c_str() );
	GetDlgItem(IDC_STATIC_INFO_DESC)->SetWindowText(pInfoDetail->record.c_str());
	GetDlgItem(IDC_STATIC_CONTACT_INFO)->SetWindowText(pInfoDetail->tel.c_str());

	string sUrl = WEB_SERVICE_ADDRESS+"/fmp/user.login.action?username="+user.loginName+"&password="+user.passWord+"&userid="+pInfoDetail->pubUID+"&target=userCenter";
	m_publisher.SetLinkText(pInfoDetail->pubName.c_str());
	m_publisher.SetMultiline(TRUE);
	m_publisher.SetLinkUrl(sUrl.c_str());
}
void CNewInfoDetailDlg::InitMyInfoDetail(const TabMyInfRecord* pInfoDetail)
{
	GetDlgItem(IDC_STATIC_INFO_ID)->SetWindowText(CString("信息编号： ") + pInfoDetail->recordID.c_str());
	GetDlgItem(IDC_STATIC_PUB_ADDR)->SetWindowText(CString("发布地区： ") + pInfoDetail->pubAddress.c_str());
	GetDlgItem(IDC_STATIC_PUB_DT)->SetWindowText(CString("发布时间： ") + pInfoDetail->pubTime.c_str());
	GetDlgItem(IDC_STATIC_DT_SCHEDULE)->SetWindowText((m_nInfoType==eInfoType_MyGoods?CString("装货日期： "):CString("发车日期： ")) + pInfoDetail->dateTime.c_str());
	GetDlgItem(IDC_STATIC_INFO_STATUS)->SetWindowText(CString("信息状态： ") + pInfoDetail->state.c_str());
	GetDlgItem(IDC_STATIC_ADDR_INFO)->SetWindowText( (pInfoDetail->startPlace + "→" + pInfoDetail->endPlace).c_str() );
	GetDlgItem(IDC_STATIC_INFO_DESC)->SetWindowText(pInfoDetail->record.c_str());
	GetDlgItem(IDC_STATIC_CONTACT_INFO)->SetWindowText(pInfoDetail->tel.c_str());

	string sUrl = WEB_SERVICE_ADDRESS+"/fmp/user.login.action?username="+user.loginName+"&password="+user.passWord+"&userid="+pInfoDetail->pubUID+"&target=userCenter";
	m_publisher.SetLinkText(pInfoDetail->pubName.c_str());
	m_publisher.SetMultiline(TRUE);
	m_publisher.SetLinkUrl(sUrl.c_str());

//	GetDlgItem(IDC_BUTTON_SEND_SMS)->EnableWindow(FALSE);
}
