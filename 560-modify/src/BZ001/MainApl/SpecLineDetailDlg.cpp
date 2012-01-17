// SpecLineDetailDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SpecLineDetailDlg.h"
#include "GLB.h"


// CSpecLineDetailDlg �Ի���

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


// CSpecLineDetailDlg ��Ϣ�������

BOOL CSpecLineDetailDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitSpecialLineDetail();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
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
			strncpy(logFont.lfFaceName,"����",LF_FACESIZE);
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
	GetDlgItem(IDC_STATIC_SPEC_ADDR_INFO)->SetWindowText((m_pSpecLineDetail->startPlace + "<����>" + m_pSpecLineDetail->endPlace).c_str());
	GetDlgItem(IDC_STATIC_SPEC_HIGHT_PRICE)->SetWindowText( ("�ػ��� ��"+m_pSpecLineDetail->weightPrice + "Ԫ/��").c_str());
	GetDlgItem(IDC_STATIC_SPEC_LIGHT_PRICE)->SetWindowText(("�ݻ��� ��"+m_pSpecLineDetail->lightPrice + "Ԫ/��").c_str());
	GetDlgItem(IDC_STATIC_SPEC_SCHEDULE)->SetWindowText(("������Σ�"+m_pSpecLineDetail->schedules).c_str());
	GetDlgItem(IDC_STATIC_SPEC_NEED_TIME)->SetWindowText((";��ʱ�䣺"+m_pSpecLineDetail->needTime).c_str());
	GetDlgItem(IDC_STATIC_SPEC_PUBLISHER_INFO)->SetWindowText(m_pSpecLineDetail->tel.c_str());

	if( m_pSpecLineDetail->startAddr != "NULL" )
	{
		GetDlgItem(IDC_STATIC_SPEC_START_ADDR)->SetWindowText(("��ַ ��"+m_pSpecLineDetail->startAddr).c_str());
	}
	else
	{
		GetDlgItem(IDC_STATIC_SPEC_START_ADDR)->SetWindowText("��ַ ��");
	}
	
	if( m_pSpecLineDetail->startContact != "NULL" )
	{
		GetDlgItem(IDC_STATIC_SPEC_START_CONTACT)->SetWindowText(("��ϵ�ˣ�"+m_pSpecLineDetail->startContact).c_str());
	}
	else
	{
		GetDlgItem(IDC_STATIC_SPEC_START_CONTACT)->SetWindowText("��ϵ�ˣ�");
	}
	
	if( m_pSpecLineDetail->startPhone != "NULL" )
	{
		GetDlgItem(IDC_STATIC_SPEC_START_PHONE)->SetWindowText(("�绰��"+m_pSpecLineDetail->startPhone).c_str());
	}
	else
	{
		GetDlgItem(IDC_STATIC_SPEC_START_PHONE)->SetWindowText("�绰��");
	}

	if( m_pSpecLineDetail->destAddr != "NULL" )
	{
		GetDlgItem(IDC_STATIC_SPEC_END_ADDR)->SetWindowText(("��ַ ��"+m_pSpecLineDetail->destAddr).c_str());
	}
	else
	{
		GetDlgItem(IDC_STATIC_SPEC_END_ADDR)->SetWindowText("��ַ ��");
	}
	
	if(m_pSpecLineDetail->destContact != "NULL")
	{
		GetDlgItem(IDC_STATIC_SPEC_END_CONTACT)->SetWindowText(("��ϵ�ˣ�"+m_pSpecLineDetail->destContact).c_str());
	}
	else
	{
		GetDlgItem(IDC_STATIC_SPEC_END_CONTACT)->SetWindowText("��ϵ�ˣ�");
	}

	if(m_pSpecLineDetail->destPhone != "NULL")
	{
		GetDlgItem(IDC_STATIC_SPEC_END_PHONE)->SetWindowText(("�绰 ��"+m_pSpecLineDetail->destPhone).c_str());
	}
	else
	{
		GetDlgItem(IDC_STATIC_SPEC_END_PHONE)->SetWindowText("�绰 ��");
	}
}
void CSpecLineDetailDlg::OnBnClickedButtonClose()
{
	CDialog::OnCancel();
}
