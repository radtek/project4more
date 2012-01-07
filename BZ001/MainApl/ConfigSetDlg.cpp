// ConfigSetDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "WLRClient.h"
#include "ConfigSetDlg.h"


// CConfigSetDlg 对话框

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

    // TODO:  在此添加额外的初始化
    sysBkClr.SetColor(myColor.sysBKClr);
    gridClr.SetColor(myColor.gridClr);
    oddFgClr.SetColor(myColor.oddRowFgClr);
    oddBkClr.SetColor(myColor.oddRowBKClr);
    evenFgClr.SetColor(myColor.evenRowFgClr);
    evenBkClr.SetColor(myColor.evenRowBKClr);

    // 初始化显示样例：奇数
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

    // 初始化显示样例：偶数行
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
    // 异常: OCX 属性页应返回 FALSE
}
    
// CConfigSetDlg 消息处理程序
    
// 系统颜色
void CConfigSetDlg::OnBnClickedConfigSetSysbkclr()
{
    // TODO: 在此添加控件通知处理程序代码
    myColor.sysBKClr = sysBkClr.GetColor();
}
    
// 网格颜色
void CConfigSetDlg::OnBnClickedConfigSetGridclr()
{
    // TODO: 在此添加控件通知处理程序代码
    myColor.gridClr = gridClr.GetColor();
}
    
// 奇数文字色
void CConfigSetDlg::OnBnClickedConfigSetOddfgclr()
{
    // TODO: 在此添加控件通知处理程序代码
    myColor.oddRowFgClr = oddFgClr.GetColor();
    //CStatic* m_pStatic=(CStatic*)GetDlgItem(IDC_CONFIG_SET_ODDSTATIC); 
    //m_pStatic->RedrawWindow();
}
    
// 偶数文字色
void CConfigSetDlg::OnBnClickedConfigSetEvenfgclr()
{
    // TODO: 在此添加控件通知处理程序代码
    myColor.evenRowFgClr = evenFgClr.GetColor();
    //CStatic* m_pStatic=(CStatic*)GetDlgItem(IDC_CONFIG_SET_EVENSTATIC); 
    //m_pStatic->RedrawWindow();
}
    
// 奇数背景色
void CConfigSetDlg::OnBnClickedConfigSetOddbkclr()
{
    // TODO: 在此添加控件通知处理程序代码
    myColor.oddRowBKClr = oddBkClr.GetColor();
    //CStatic* m_pStatic=(CStatic*)GetDlgItem(IDC_CONFIG_SET_ODDSTATIC); 
    //m_pStatic->RedrawWindow();
}
    
// 偶数背景色
void CConfigSetDlg::OnBnClickedConfigSetEvenbkclr()
{
    // TODO: 在此添加控件通知处理程序代码
    myColor.evenRowBKClr = evenBkClr.GetColor();
    //CStatic* m_pStatic=(CStatic*)GetDlgItem(IDC_CONFIG_SET_EVENSTATIC); 
    //m_pStatic->RedrawWindow();
}
    
// 奇数行字体
void CConfigSetDlg::OnBnClickedConfigSetOddfont()
{
    // TODO: 在此添加控件通知处理程序代码
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

    // 初始化字体对话框
    CFontDialog dlgFontDlg(&oldLF);
    dlgFontDlg.m_cf.Flags ^= CF_EFFECTS;
    //显示字体选择对话框
    if (dlgFontDlg.DoModal() == IDOK)
    {
        //如果用户在字体选择对话框中单击了“确定”按钮
        dlgFontDlg.GetCurrentFont(&newLF);
        // 更新字体
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
        
        // 更新显示文字
        /*CFont fontOddStatic;
        fontOddStatic.DeleteObject();
        fontOddStatic.CreateFontIndirect(&newLF);
        CStatic* m_pStatic=(CStatic*)GetDlgItem(IDC_CONFIG_SET_ODDSTATIC);
        m_pStatic->SetFont(&fontOddStatic);
        m_pStatic->RedrawWindow();
        */
    }
}
    
// 偶数行字体
void CConfigSetDlg::OnBnClickedConfigSetEvenfont()
{
    // TODO: 在此添加控件通知处理程序代码
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
 
    // 初始化字体对话框
    CFontDialog dlgFontDlg(&oldLF);
    dlgFontDlg.m_cf.Flags ^= CF_EFFECTS;
    //显示字体选择对话框
    if (dlgFontDlg.DoModal() == IDOK)
    {
        //如果用户在字体选择对话框中单击了“确定”按钮
        dlgFontDlg.GetCurrentFont(&newLF);
        // 更新字体
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

        // 更新显示文字
        /*CFont fontOddStatic;
        fontOddStatic.DeleteObject();
        fontOddStatic.CreateFontIndirect(&newLF);
        CStatic* m_pStatic=(CStatic*)GetDlgItem(IDC_CONFIG_SET_EVENSTATIC);
        m_pStatic->SetFont(&fontOddStatic);
        m_pStatic->RedrawWindow(); */
    }
}
        
// 绘制控件颜色
HBRUSH CConfigSetDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

    // TODO:  在此更改 DC 的任何属性
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
    // TODO:  如果默认的不是所需画笔，则返回另一个画笔
    return hbr;
}
    
// OK
void CConfigSetDlg::OnBnClickedOk()
{
    // TODO: 在此添加控件通知处理程序代码
    OnOK();
}



void CConfigSetDlg::OnBnClickedDefault()
{
	// TODO: 在此添加控件通知处理程序代码

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
