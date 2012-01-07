// UserLoginDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "WLRClient.h"
#include "UserLoginDlg.h"

#include "MyRSA.h"

// CUserLoginDlg 对话框

IMPLEMENT_DYNAMIC(CUserLoginDlg, CDialog)

CUserLoginDlg::CUserLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUserLoginDlg::IDD, pParent)
    , userName(_T(""))
    , passWord(_T(""))
    , ifRemUserName(FALSE)
    , ifRemPassWord(FALSE)
{
	m_bgColor = RGB(200,230,254);
	m_textColor = RGB(0, 66, 118);
}

CUserLoginDlg::~CUserLoginDlg()
{
}

void CUserLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_USER_LOGIN_USERNAME, userName);
	DDX_Text(pDX, IDC_USER_LOGIN_PASSWORD, passWord);
	//DDX_Check(pDX, IDC_USER_LOGIN_REM_USERNAME, ifRemUserName);
	//DDX_Check(pDX, IDC_USER_LOGIN_REM_PASSNAME, ifRemPassWord);
	DDX_Control(pDX, IDC_USER_LOGIN_REM_USERNAME, btnRemUserName);
	DDX_Control(pDX, IDC_USER_LOGIN_REM_PASSNAME, btnRemPassWord);
	DDX_Control(pDX, ID_REGNEWUSER, regNewUser);
	DDX_Control(pDX, IDOK, m_btnLogin);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, ID_RETRIEVE_PASSWORD, m_retrievePW);
	DDX_Control(pDX, IDC_BUTTON_CLOSE, m_btnClose);
}


BEGIN_MESSAGE_MAP(CUserLoginDlg, CDialog)
    ON_BN_CLICKED(IDOK, &CUserLoginDlg::OnBnClickedOk)
    ON_WM_CLOSE()
    ON_BN_CLICKED(IDC_USER_LOGIN_REM_USERNAME, &CUserLoginDlg::OnBnClickedUserLoginRemUsername)
    ON_BN_CLICKED(IDC_USER_LOGIN_REM_PASSNAME, &CUserLoginDlg::OnBnClickedUserLoginRemPassname)
    ON_WM_ERASEBKGND()
    ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CUserLoginDlg::OnBnClickedButtonClose)
END_MESSAGE_MAP()
    
BOOL CUserLoginDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  在此添加额外的初始化
    // 加载用户数据
    loadUserData();
	//InitExceptionCatch();
    // 初始化链接
    string url = WEB_SERVICE_ADDRESS + "/fmp/user.toRegister.action";
    regNewUser.SetLinkUrl((TCHAR *)url.c_str());
    regNewUser.SetBackgroundColor(m_bgColor);
	regNewUser.SetMultiline(TRUE);

	url = WEB_SERVICE_ADDRESS + "/fmp/user.getbackPwd.action";
	m_retrievePW.SetLinkUrl((char*)url.c_str());
	m_retrievePW.SetBackgroundColor(m_bgColor);
	m_retrievePW.SetMultiline(TRUE);

	m_btnLogin.LoadBitmap(IDB_LOGIN);
	m_btnCancel.LoadBitmap(IDB_LOGIN_CANCEL);
	m_btnClose.LoadBitmap(IDB_LOGIN_CLOSE);

	m_btnLogin.SetTextColor(m_textColor);
	m_btnCancel.SetTextColor(m_textColor);

	//MoveWindow(0, 0, 340, 247);
	CenterWindow();
	/*btnRemUserName.SetTextColor(m_textColor);
	btnRemPassWord.SetTextColor(m_textColor);*/
    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常: OCX 属性页应返回 FALSE
}

// CUserLoginDlg 消息处理程序

void CUserLoginDlg::OnBnClickedOk()
{
    // TODO: 在此添加控件通知处理程序代码
    UpdateData();
    bool ifOK = true;
    // 判断必填字段
    if (userName == "") {
        MessageBox("用户名不能为空", "用户登录");
        ifOK = false;
        return;
    }

    if (passWord == "") {
        MessageBox("密码不能为空", "用户登录");
        ifOK = false;
        return;
    }

    if (ifOK) { 
        //int aaa = ((CButton*)GetDlgItem(IDC_USER_LOGIN_REM_USERNAME))->GetCheck();
        //userData.ifRemUserName = ifRemUserName;

        // 保存用户数据
        saveUserData();

        OnOK();
    }
}
        
// 保存用户数据
int CUserLoginDlg::saveUserData()
{
    userData.ifRemUserName = ifRemUserName;
    userData.ifRemPassWord = ifRemPassWord;
    
    UpdateData(true);

    if (ifRemUserName) 
        userData.userName = (LPTSTR)(LPCTSTR)userName;
    
    if (ifRemPassWord) {        
        CMyRSA myRSA;
        userData.passWord = myRSA.EncryptString("1", (LPTSTR)(LPCTSTR)passWord);
    }
	/**/TCHAR szStylesPath[_MAX_PATH];

	VERIFY(::GetModuleFileName(
		AfxGetApp()->m_hInstance, szStylesPath, _MAX_PATH));		

	CString csStylesPath(szStylesPath);
	int nIndex  = csStylesPath.ReverseFind(_T('\\'));
	if (nIndex > 0) {
		csStylesPath = csStylesPath.Left(nIndex);
	}
	else {
		csStylesPath.Empty();
	}
	CString path;
	path = csStylesPath;
	path += "\\user.data";
	string s(path.GetBuffer());
	
    WLRUserData::saveData(userData, s);
 
    return 0;
}
    
// 加载用户数据
int CUserLoginDlg::loadUserData()
{
    userData.userName = "";
    userData.passWord = "";
    userData.ifRemUserName = 0;
    userData.ifRemPassWord = 0;
	TCHAR szStylesPath[_MAX_PATH];

	VERIFY(::GetModuleFileName(
		AfxGetApp()->m_hInstance, szStylesPath, _MAX_PATH));		

	CString csStylesPath(szStylesPath);
	int nIndex  = csStylesPath.ReverseFind(_T('\\'));
	if (nIndex > 0) {
		csStylesPath = csStylesPath.Left(nIndex);
	}
	else {
		csStylesPath.Empty();
	}
	CString path;
	path = csStylesPath;
	path += "\\user.data";
	string s(path.GetBuffer());

    WLRUserData::loadData(userData, s);

    ifRemUserName = userData.ifRemUserName;
    ifRemPassWord = userData.ifRemPassWord;

    if (ifRemUserName) {
        userName = userData.userName.c_str();
        btnRemUserName.SetCheck(true);
    }
    
    if (ifRemPassWord) {
        // 解密
        CMyRSA myRSA;
        string decrypted = myRSA.DecryptString( userData.passWord);
        passWord = decrypted.c_str();
        btnRemPassWord.SetCheck(true);
    }

    UpdateData(false);

    return 0;
}
    
// 窗口关闭时调用
void CUserLoginDlg::OnClose()
{
    // TODO: 在此添加消息处理程序代码和/或调用默认值

    CDialog::OnClose();
}
    
// 单击记住帐户按钮
void CUserLoginDlg::OnBnClickedUserLoginRemUsername()
{
    // TODO: 在此添加控件通知处理程序代码
    if (ifRemUserName)
        ifRemUserName = false;
    else 
        ifRemUserName = true;
}
    
//  单击记住密码按钮
void CUserLoginDlg::OnBnClickedUserLoginRemPassname()
{
    // TODO: 在此添加控件通知处理程序代码
    if (ifRemPassWord) {
        ifRemPassWord = false;
    } else { 
        ifRemPassWord = true;
        // 记住密码，必须记住帐户
        btnRemUserName.SetCheck(true);
        ifRemUserName = true;
    }
}
    
// 擦除背景时调用
BOOL CUserLoginDlg::OnEraseBkgnd(CDC* pDC)
{
    // TODO: 在此添加消息处理程序代码和/或调用默认值

    return TRUE;
    //return CDialog::OnEraseBkgnd(pDC);
}

void BltBitmap(CWnd* pWnd, CDC* pDC, int x, int y, UINT32 nBitmapId)
{
	CBitmap bmp;
	if (bmp.LoadBitmap(nBitmapId))
	{
		// Get the size of the bitmap
		BITMAP bmpInfo;
		bmp.GetBitmap(&bmpInfo);

		CDC dcMemory;
		dcMemory.CreateCompatibleDC(pDC);

		CBitmap* pOldBitmap = dcMemory.SelectObject(&bmp);

		CRect rect;
		pWnd->GetClientRect(&rect);
		pDC->BitBlt(x, y, bmpInfo.bmWidth, bmpInfo.bmHeight, &dcMemory, 0, 0, SRCCOPY);

		dcMemory.SelectObject(pOldBitmap);
	}
}
void CUserLoginDlg::OnPaint()
{
    CPaintDC dc(this); // device context for painting
    // TODO: 在此处添加消息处理程序代码
    // 画背景色
    CRect rect;
    GetWindowRect(&rect);
    int nWidth = rect.Width();
    int nHeight= rect.Height();

    CDC MemDC;
    CBitmap MemBitmap;

    MemDC.CreateCompatibleDC (NULL);
    MemBitmap.CreateCompatibleBitmap(&dc,nWidth,nHeight);

    CBitmap *pOldBit=MemDC.SelectObject(&MemBitmap);	
    MemDC.FillSolidRect(0,0,nWidth,nHeight,m_bgColor);
	//MemDC.FillSolidRect(0,0,nWidth,nHeight,RGB(0, 0, 255));
	//MemDC.FillSolidRect(0,0,nWidth,nHeight,RGB(204,255,204));

	BltBitmap(this, &dc, 0, 0, IDB_LOGIN_BACKGROUND);

    // 画背景图
    CBitmap m_bmp;
    VERIFY(m_bmp.LoadBitmap(IDB_LOGINBKPIC));
    GetClientRect(rect);
    BITMAP bm;
    CDC dcMem;
    VERIFY(m_bmp.GetObject(sizeof(bm), (LPVOID)&bm));
    dcMem.CreateCompatibleDC(&dc);
    CBitmap *pOldBMP =( CBitmap *)dcMem.SelectObject(&m_bmp);
    //MemDC.BitBlt( (rect.right - bm.bmWidth)/2, (rect.bottom - bm.bmHeight)/2, 
    //    bm.bmWidth, bm.bmHeight, &dcMem, 0, 0, SRCCOPY);
    MemDC.StretchBlt(0, 0, rect.Width(), bm.bmHeight, &dcMem, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);
    dcMem.SelectObject(pOldBMP);
    // 从内存绘制到程序界面
    dc.BitBlt(0, 29, nWidth, nHeight, &MemDC, 0, 0, SRCCOPY);

    MemBitmap.DeleteObject();
    MemDC.DeleteDC();
    // 不为绘图消息调用 CDialog::OnPaint()
}

HBRUSH CUserLoginDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	if( nCtlColor == CTLCOLOR_STATIC )
	{
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(m_textColor); 
		return   (HBRUSH)GetStockObject(HOLLOW_BRUSH); 
	}
	/*else if( nCtlColor == CTLCOLOR_BTN )
	{
		pDC->SetTextColor(RGB(0,66,118)); 
		return   (HBRUSH)GetStockObject(HOLLOW_BRUSH); 
	}*/
	// TODO:  在此更改 DC 的任何属性
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

void CUserLoginDlg::OnBnClickedButtonClose()
{
	PostMessage(WM_CLOSE);
}
