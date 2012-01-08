// ConfigSetDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WLRClient.h"
#include "ConfigSetDlg.h"


// CConfigSetDlg �Ի���

IMPLEMENT_DYNAMIC(CConfigSetDlg, CDialog)

CConfigSetDlg::CConfigSetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigSetDlg::IDD, pParent)
{
    myColor.oddRowBKClr = RGB(38, 109, 59);
    myColor.oddRowFgClr = RGB(240, 239, 230);
    myColor.evenRowBKClr = RGB(75, 155, 62);
    myColor.evenRowFgClr = RGB(33, 53, 41);
    myColor.gridClr = RGB(186, 185, 176);
    myColor.sysBKClr = RGB(186, 185, 176);
}

CConfigSetDlg::~CConfigSetDlg()
{
}

void CConfigSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CONFIG_SET_SYSBKCLR, sysBkClr);
	DDX_Control(pDX, IDC_CONFIG_SET_GRIDCLR, gridClr);
    DDX_Control(pDX, IDC_CONFIG_SET_ODDFGCLR, oddFgClr);
	DDX_Control(pDX, IDC_CONFIG_SET_ODDBKCLR, oddBkClr);
    DDX_Control(pDX, IDC_CONFIG_SET_EVENFGCLR, evenFgClr);
	DDX_Control(pDX, IDC_CONFIG_SET_EVENBKCLR, evenBkClr);
}


BEGIN_MESSAGE_MAP(CConfigSetDlg, CDialog)
    ON_BN_CLICKED(IDC_CONFIG_SET_SYSBKCLR, &CConfigSetDlg::OnBnClickedConfigSetSysbkclr)
    ON_BN_CLICKED(IDC_CONFIG_SET_GRIDCLR, &CConfigSetDlg::OnBnClickedConfigSetGridclr)
    ON_BN_CLICKED(IDC_CONFIG_SET_ODDBKCLR, &CConfigSetDlg::OnBnClickedConfigSetOddbkclr)
    ON_BN_CLICKED(IDC_CONFIG_SET_EVENBKCLR, &CConfigSetDlg::OnBnClickedConfigSetEvenbkclr)
    ON_BN_CLICKED(IDC_CONFIG_SET_ODDFONT, &CConfigSetDlg::OnBnClickedConfigSetOddfont)
    ON_BN_CLICKED(IDC_CONFIG_SET_EVENFONT, &CConfigSetDlg::OnBnClickedConfigSetEvenfont)
    ON_BN_CLICKED(IDOK, &CConfigSetDlg::OnBnClickedOk)
    ON_WM_CTLCOLOR()
    ON_BN_CLICKED(IDC_CONFIG_SET_ODDFGCLR, &CConfigSetDlg::OnBnClickedConfigSetOddfgclr)
    ON_BN_CLICKED(IDC_CONFIG_SET_EVENFGCLR, &CConfigSetDlg::OnBnClickedConfigSetEvenfgclr)
	ON_BN_CLICKED(IDC_DEFAULT, &CConfigSetDlg::OnBnClickedDefault)
END_MESSAGE_MAP()
    
// OnInitDialog
BOOL CConfigSetDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  �ڴ���Ӷ���ĳ�ʼ��
    sysBkClr.SetColor(myColor.sysBKClr);
    gridClr.SetColor(myColor.gridClr);
    oddFgClr.SetColor(myColor.oddRowFgClr);
    oddBkClr.SetColor(myColor.oddRowBKClr);
    evenFgClr.SetColor(myColor.evenRowFgClr);
    evenBkClr.SetColor(myColor.evenRowBKClr);

    // ��ʼ����ʾ����������
/*    LOGFONT oddLF;
    lstrcpy((LPSTR)oddLF.lfFaceName, (LPSTR)oddFont.lfFaceName.c_str()); 
    oddLF.lfWeight = oddFont.lfWeight; 
    oddLF.lfWidth = oddFont.lfWidth; 
    oddLF.lfHeight = oddFont.lfHeight;  
    oddLF.lfEscapement = oddFont.lfEscapement; 
    oddLF.lfUnderline = oddFont.lfUnderline; 
    oddLF.lfItalic = oddFont.lfItalic; 
    oddLF.lfStrikeOut = oddFont.lfStrikeOut; 
    oddLF.lfCharSet = oddFont.lfCharSet;

    static CFont fontOddStatic;
    fontOddStatic.DeleteObject();
    fontOddStatic.CreateFontIndirect(&oddLF);

    //CWnd *pWnd = GetDlgItem(IDC_CONFIG_SET_ODDSTATIC);
    CStatic* oddStatic=(CStatic*)GetDlgItem(IDC_CONFIG_SET_ODDSTATIC);
    oddStatic->SetFont(&fontOddStatic);
    //oddStatic->RedrawWindow();

    // ��ʼ����ʾ������ż����
    LOGFONT evenLF;
    lstrcpy((LPSTR)evenLF.lfFaceName, (LPSTR)evenFont.lfFaceName.c_str()); 
    evenLF.lfWeight = evenFont.lfWeight; 
    evenLF.lfWidth = evenFont.lfWidth; 
    evenLF.lfHeight = evenFont.lfHeight;  
    evenLF.lfEscapement = evenFont.lfEscapement; 
    evenLF.lfUnderline = evenFont.lfUnderline; 
    evenLF.lfItalic = evenFont.lfItalic; 
    evenLF.lfStrikeOut = evenFont.lfStrikeOut; 
    evenLF.lfCharSet = evenFont.lfCharSet;

    static CFont fontEvenStatic;
    fontEvenStatic.DeleteObject();
    fontEvenStatic.CreateFontIndirect(&evenLF);

    CStatic* evenStatic=(CStatic*)GetDlgItem(IDC_CONFIG_SET_EVENSTATIC);
    evenStatic->SetFont(&fontEvenStatic);
    //evenStatic->RedrawWindow();
    */

    return TRUE;  // return TRUE unless you set the focus to a control
    // �쳣: OCX ����ҳӦ���� FALSE
}
    
// CConfigSetDlg ��Ϣ�������
    
// ϵͳ��ɫ
void CConfigSetDlg::OnBnClickedConfigSetSysbkclr()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    myColor.sysBKClr = sysBkClr.GetColor();
}
    
// ������ɫ
void CConfigSetDlg::OnBnClickedConfigSetGridclr()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    myColor.gridClr = gridClr.GetColor();
}
    
// ��������ɫ
void CConfigSetDlg::OnBnClickedConfigSetOddfgclr()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    myColor.oddRowFgClr = oddFgClr.GetColor();
    //CStatic* m_pStatic=(CStatic*)GetDlgItem(IDC_CONFIG_SET_ODDSTATIC); 
    //m_pStatic->RedrawWindow();
}
    
// ż������ɫ
void CConfigSetDlg::OnBnClickedConfigSetEvenfgclr()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    myColor.evenRowFgClr = evenFgClr.GetColor();
    //CStatic* m_pStatic=(CStatic*)GetDlgItem(IDC_CONFIG_SET_EVENSTATIC); 
    //m_pStatic->RedrawWindow();
}
    
// ��������ɫ
void CConfigSetDlg::OnBnClickedConfigSetOddbkclr()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    myColor.oddRowBKClr = oddBkClr.GetColor();
    //CStatic* m_pStatic=(CStatic*)GetDlgItem(IDC_CONFIG_SET_ODDSTATIC); 
    //m_pStatic->RedrawWindow();
}
    
// ż������ɫ
void CConfigSetDlg::OnBnClickedConfigSetEvenbkclr()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    myColor.evenRowBKClr = evenBkClr.GetColor();
    //CStatic* m_pStatic=(CStatic*)GetDlgItem(IDC_CONFIG_SET_EVENSTATIC); 
    //m_pStatic->RedrawWindow();
}
    
// ����������
void CConfigSetDlg::OnBnClickedConfigSetOddfont()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    LOGFONT oldLF, newLF;
    lstrcpy((LPSTR)oldLF.lfFaceName, (LPSTR)oddFont.lfFaceName.c_str()); 
    oldLF.lfWeight = oddFont.lfWeight; 
    oldLF.lfWidth = oddFont.lfWidth; 
    oldLF.lfHeight = oddFont.lfHeight;  
    oldLF.lfEscapement = oddFont.lfEscapement; 
    oldLF.lfUnderline = oddFont.lfUnderline; 
    oldLF.lfItalic = oddFont.lfItalic; 
    oldLF.lfStrikeOut = oddFont.lfStrikeOut; 
    oldLF.lfCharSet = oddFont.lfCharSet;

    // ��ʼ������Ի���
    CFontDialog dlgFontDlg(&oldLF);
    dlgFontDlg.m_cf.Flags ^= CF_EFFECTS;
    //��ʾ����ѡ��Ի���
    if (dlgFontDlg.DoModal() == IDOK)
    {
        //����û�������ѡ��Ի����е����ˡ�ȷ������ť
        dlgFontDlg.GetCurrentFont(&newLF);
        // ��������
        //lstrcpy((LPSTR)oldLF.lfFaceName, (LPSTR)oddFont.lfFaceName.c_str()); 
        oddFont.lfFaceName = newLF.lfFaceName;
        oddFont.lfWeight = newLF.lfWeight; 
        oddFont.lfWidth = newLF.lfWidth; 
        oddFont.lfHeight = newLF.lfHeight;  
        oddFont.lfEscapement = newLF.lfEscapement; 
        oddFont.lfUnderline = newLF.lfUnderline; 
        oddFont.lfItalic = newLF.lfItalic; 
        oddFont.lfStrikeOut = newLF.lfStrikeOut; 
        oddFont.lfCharSet = newLF.lfCharSet;
        
        // ������ʾ����
        /*CFont fontOddStatic;
        fontOddStatic.DeleteObject();
        fontOddStatic.CreateFontIndirect(&newLF);
        CStatic* m_pStatic=(CStatic*)GetDlgItem(IDC_CONFIG_SET_ODDSTATIC);
        m_pStatic->SetFont(&fontOddStatic);
        m_pStatic->RedrawWindow();
        */
    }
}
    
// ż��������
void CConfigSetDlg::OnBnClickedConfigSetEvenfont()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    LOGFONT oldLF, newLF;
    lstrcpy((LPSTR)oldLF.lfFaceName, (LPSTR)evenFont.lfFaceName.c_str()); 
    oldLF.lfWeight = evenFont.lfWeight; 
    oldLF.lfWidth = evenFont.lfWidth; 
    oldLF.lfHeight = evenFont.lfHeight;  
    oldLF.lfEscapement = evenFont.lfEscapement; 
    oldLF.lfUnderline = evenFont.lfUnderline; 
    oldLF.lfItalic = evenFont.lfItalic; 
    oldLF.lfStrikeOut = evenFont.lfStrikeOut; 
    oldLF.lfCharSet = evenFont.lfCharSet;
 
    // ��ʼ������Ի���
    CFontDialog dlgFontDlg(&oldLF);
    dlgFontDlg.m_cf.Flags ^= CF_EFFECTS;
    //��ʾ����ѡ��Ի���
    if (dlgFontDlg.DoModal() == IDOK)
    {
        //����û�������ѡ��Ի����е����ˡ�ȷ������ť
        dlgFontDlg.GetCurrentFont(&newLF);
        // ��������
        //lstrcpy((LPSTR)oldLF.lfFaceName, (LPSTR)evenFont.lfFaceName.c_str()); 
        evenFont.lfFaceName = newLF.lfFaceName;
        evenFont.lfWeight = newLF.lfWeight; 
        evenFont.lfWidth = newLF.lfWidth; 
        evenFont.lfHeight = newLF.lfHeight;  
        evenFont.lfEscapement = newLF.lfEscapement; 
        evenFont.lfUnderline = newLF.lfUnderline; 
        evenFont.lfItalic = newLF.lfItalic; 
        evenFont.lfStrikeOut = newLF.lfStrikeOut; 
        evenFont.lfCharSet = newLF.lfCharSet;

        // ������ʾ����
        /*CFont fontOddStatic;
        fontOddStatic.DeleteObject();
        fontOddStatic.CreateFontIndirect(&newLF);
        CStatic* m_pStatic=(CStatic*)GetDlgItem(IDC_CONFIG_SET_EVENSTATIC);
        m_pStatic->SetFont(&fontOddStatic);
        m_pStatic->RedrawWindow(); */
    }
}
        
// ���ƿؼ���ɫ
HBRUSH CConfigSetDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

    // TODO:  �ڴ˸��� DC ���κ�����
 /*   if (pWnd->GetDlgCtrlID() == IDC_CONFIG_SET_ODDSTATIC)
    { 
        pDC->SetBkColor(myColor.oddRowBKClr);
        pDC->SetTextColor(myColor.oddRowFgClr); 
    } 

    if (pWnd->GetDlgCtrlID() == IDC_CONFIG_SET_EVENSTATIC)
    { 
        pDC->SetBkColor(myColor.evenRowBKClr);
        pDC->SetTextColor(myColor.evenRowFgClr); 
    } 
*/
    // TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
    return hbr;
}
    
// OK
void CConfigSetDlg::OnBnClickedOk()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    OnOK();
}



void CConfigSetDlg::OnBnClickedDefault()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	myColor.oddRowBKClr = 16777215;
	myColor.oddRowFgClr = 0;
	myColor.evenRowBKClr = 15921906;
	myColor.evenRowFgClr = 3368448;
	myColor.gridClr = 13750737;
	myColor.sysBKClr = 12904135;

	sysBkClr.SetColor(myColor.sysBKClr);
	gridClr.SetColor(myColor.gridClr);
	oddFgClr.SetColor(myColor.oddRowFgClr);
	oddBkClr.SetColor(myColor.oddRowBKClr);
	evenFgClr.SetColor(myColor.evenRowFgClr);
	evenBkClr.SetColor(myColor.evenRowBKClr);
}
