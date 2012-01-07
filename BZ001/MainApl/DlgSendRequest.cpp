// DlgSendRequest.cpp : 实现文件
//

#include "stdafx.h"
#include "WLRClient.h"
#include "DlgSendRequest.h"
#include "header.h"

// CDlgSendRequest 对话框

IMPLEMENT_DYNAMIC(CDlgSendRequest, CDialog)

CDlgSendRequest::CDlgSendRequest(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSendRequest::IDD, pParent)
	, m_number(_T(""))
	, m_strmsg(_T(""))
{
	// 初始化svrIO
	svrIO = NULL;
}

CDlgSendRequest::~CDlgSendRequest()
{
}

void CDlgSendRequest::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_FWZ, m_number);
	DDX_Text(pDX, IDC_EDIT1, m_strmsg);
	//DDV_MaxChars(pDX, m_strmsg, 200);
	DDX_Control(pDX, IDC_EDIT1, m_msgedit);
}


BEGIN_MESSAGE_MAP(CDlgSendRequest, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgSendRequest::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT1, &CDlgSendRequest::OnEnChangeEdit1)
END_MESSAGE_MAP()


// CDlgSendRequest 消息处理程序

void CDlgSendRequest::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	
	UpdateData(TRUE);

	if (m_strmsg == "")
	{
		MessageBox("发送消息不能为空！","560");
	} 
	else
	{
		//开辟线程处理发送消息

//		SuspendThread(hThread);

		DWORD PID;
		HANDLE Main_Thread;
		Main_Thread=CreateThread(NULL,0,ThreadFunc,this,0,&PID);

// 		DWORD dip = 0;
// 		if (hThread != NULL)
// 		{
// 			while(1)
// 			{
// 				dip = ResumeThread(hThread);
// 				if (dip == 0)
// 				{
// 					break;
// 				}
// 				Sleep(100);
// 			}
// 		}
	}
}
DWORD CDlgSendRequest::ThreadFunc(LPVOID p)
{
	CoInitialize(NULL);
	CDlgSendRequest * dlg = (CDlgSendRequest*)p;
	EnterCriticalSection(&csPrint);
	string s = (LPTSTR)(LPCTSTR)dlg->m_strmsg;
	string  result =dlg->svrIO->setServicesMsg(dlg->recordID,s);//给服务站发送消息
	
	//AfxMessageBox(result.c_str());
	
	LeaveCriticalSection(&csPrint);
	CoUninitialize();
	//::MessageBox(result.c_str());
	if (result == "TRUE")
	{
		::MessageBoxA(dlg->GetSafeHwnd(),"请求发送成功！","560",MB_OK);
	}
	else
		::MessageBoxA(dlg->GetSafeHwnd(),result.c_str(),"560",MB_OK);

	::SendMessage(dlg->GetSafeHwnd(),WM_CLOSE,0,0);//关闭界面
	return 0 ;
}
BOOL CDlgSendRequest::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//m_msgedit.SetLimitText(201);
	m_msgedit.LimitText(200);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDlgSendRequest::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	/*CString str;
	GetDlgItemText(IDC_EDIT1,str);
	if(str.GetLength()>200)
	{
		//AfxMessageBox(L"输入内容长度大于200！",0,0);
		CString cs;
		cs = str.Left(200);
		SetDlgItemText(IDC_EDIT1,cs);
	}*/
	// TODO:  在此添加控件通知处理程序代码
}
