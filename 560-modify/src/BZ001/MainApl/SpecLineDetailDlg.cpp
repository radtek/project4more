// SpecLineDetailDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SpecLineDetailDlg.h"
#include "GLB.h"


// CSpecLineDetailDlg 对话框

IMPLEMENT_DYNAMIC(CSpecLineDetailDlg, CDialog)

CSpecLineDetailDlg::CSpecLineDetailDlg(const TabSpecialLineRecord* pSpecLineDetail, CWnd* pParent /*=NULL*/)
	: CDialog(CSpecLineDetailDlg::IDD, pParent), m_pSpecLineDetail(pSpecLineDetail)
{

}

CSpecLineDetailDlg::~CSpecLineDetailDlg()
{
}

void CSpecLineDetailDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_STATIC_GOAL_GROUP, m_goalGroup);
	//DDX_Control(pDX, IDC_STATIC_GROUP_CONTACT, m_contactGroup);
}


BEGIN_MESSAGE_MAP(CSpecLineDetailDlg, CDialog)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CSpecLineDetailDlg::OnBnClickedButtonClose)
END_MESSAGE_MAP()


// CSpecLineDetailDlg 消息处理程序

BOOL CSpecLineDetailDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitSpecialLineDetail();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

HBRUSH CSpecLineDetailDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if( nCtlColor == CTLCOLOR_DLG )
	{
		return (HBRUSH)CreateSolidBrush(RGB(235,242,251));; 
	}
	else if( nCtlColor == CTLCOLOR_STATIC )
	{
		int nCtrlID = pWnd->GetDlgCtrlID();
		
		if( nCtrlID != IDC_STATIC_GROUP_CONTACT && nCtrlID != IDC_STATIC_GOAL_GROUP )
		{
			pDC->SetBkMode(TRANSPARENT);
		}

		if( nCtrlID == IDC_STATIC_SPEC_PUBLISHER_INFO )
		{
			pDC->SetTextColor(RGB(188,51,58));
		}
		else if( nCtrlID == IDC_STATIC_SPEC_ADDR_INFO || nCtrlID == IDC_STATIC_SPEC_START_ADDR_INFO ||
			nCtrlID == IDC_STATIC_SPEC_END_ADDR_INFO || nCtrlID == IDC_STATIC_SPEC_PUBLISHER)
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

			if( nCtrlID == IDC_STATIC_SPEC_PUBLISHER )
			{
				pDC->SetTextColor(RGB(188,51,58));
			}
		}

		return (HBRUSH)GetStockObject(WHITE_BRUSH); 
	}

	return hbr;
}


void CSpecLineDetailDlg::InitSpecialLineDetail()
{
	GetDlgItem(IDC_STATIC_SPEC_ADDR_INFO)->SetWindowText((m_pSpecLineDetail->startPlace + "<——>" + m_pSpecLineDetail->endPlace).c_str());
	GetDlgItem(IDC_STATIC_SPEC_HIGHT_PRICE)->SetWindowText( ("重货价 ："+m_pSpecLineDetail->weightPrice + "元/吨").c_str());
	GetDlgItem(IDC_STATIC_SPEC_LIGHT_PRICE)->SetWindowText(("泡货价 ："+m_pSpecLineDetail->lightPrice + "元/方").c_str());
	GetDlgItem(IDC_STATIC_SPEC_SCHEDULE)->SetWindowText(("发车班次："+m_pSpecLineDetail->schedules).c_str());
	GetDlgItem(IDC_STATIC_SPEC_NEED_TIME)->SetWindowText(("途中时间："+m_pSpecLineDetail->needTime).c_str());
	GetDlgItem(IDC_STATIC_SPEC_PUBLISHER_INFO)->SetWindowText(m_pSpecLineDetail->tel.c_str());

	if( m_pSpecLineDetail->startAddr != "NULL" )
	{
		GetDlgItem(IDC_STATIC_SPEC_START_ADDR)->SetWindowText(("地址 ："+m_pSpecLineDetail->startAddr).c_str());
	}
	else
	{
		GetDlgItem(IDC_STATIC_SPEC_START_ADDR)->SetWindowText("地址 ：");
	}
	
	if( m_pSpecLineDetail->startContact != "NULL" )
	{
		GetDlgItem(IDC_STATIC_SPEC_START_CONTACT)->SetWindowText(("联系人："+m_pSpecLineDetail->startContact).c_str());
	}
	else
	{
		GetDlgItem(IDC_STATIC_SPEC_START_CONTACT)->SetWindowText("联系人：");
	}
	
	if( m_pSpecLineDetail->startPhone != "NULL" )
	{
		GetDlgItem(IDC_STATIC_SPEC_START_PHONE)->SetWindowText(("电话："+m_pSpecLineDetail->startPhone).c_str());
	}
	else
	{
		GetDlgItem(IDC_STATIC_SPEC_START_PHONE)->SetWindowText("电话：");
	}

	if( m_pSpecLineDetail->destAddr != "NULL" )
	{
		GetDlgItem(IDC_STATIC_SPEC_END_ADDR)->SetWindowText(("地址 ："+m_pSpecLineDetail->destAddr).c_str());
	}
	else
	{
		GetDlgItem(IDC_STATIC_SPEC_END_ADDR)->SetWindowText("地址 ：");
	}
	
	if(m_pSpecLineDetail->destContact != "NULL")
	{
		GetDlgItem(IDC_STATIC_SPEC_END_CONTACT)->SetWindowText(("联系人："+m_pSpecLineDetail->destContact).c_str());
	}
	else
	{
		GetDlgItem(IDC_STATIC_SPEC_END_CONTACT)->SetWindowText("联系人：");
	}

	if(m_pSpecLineDetail->destPhone != "NULL")
	{
		GetDlgItem(IDC_STATIC_SPEC_END_PHONE)->SetWindowText(("电话 ："+m_pSpecLineDetail->destPhone).c_str());
	}
	else
	{
		GetDlgItem(IDC_STATIC_SPEC_END_PHONE)->SetWindowText("电话 ：");
	}
}
void CSpecLineDetailDlg::OnBnClickedButtonClose()
{
	CDialog::OnCancel();
}
