// DlgSendRequest.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WLRClient.h"
#include "DlgSendRequest.h"
#include "header.h"

// CDlgSendRequest �Ի���

IMPLEMENT_DYNAMIC(CDlgSendRequest, CDialog)

CDlgSendRequest::CDlgSendRequest(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSendRequest::IDD, pParent)
	, m_number(_T(""))
	, m_strmsg(_T(""))
{
	// ��ʼ��svrIO
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


// CDlgSendRequest ��Ϣ�������

void CDlgSendRequest::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	UpdateData(TRUE);

	if (m_strmsg == "")
	{
		MessageBox("������Ϣ����Ϊ�գ�","560");
	} 
	else
	{
		//�����̴߳�������Ϣ

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
	string  result =dlg->svrIO->setServicesMsg(dlg->recordID,s);//������վ������Ϣ
	
	//AfxMessageBox(result.c_str());
	
	LeaveCriticalSection(&csPrint);
	CoUninitialize();
	//::MessageBox(result.c_str());
	if (result == "TRUE")
	{
		::MessageBoxA(dlg->GetSafeHwnd(),"�����ͳɹ���","560",MB_OK);
	}
	else
		::MessageBoxA(dlg->GetSafeHwnd(),result.c_str(),"560",MB_OK);

	::SendMessage(dlg->GetSafeHwnd(),WM_CLOSE,0,0);//�رս���
	return 0 ;
}
BOOL CDlgSendRequest::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//m_msgedit.SetLimitText(201);
	m_msgedit.LimitText(200);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CDlgSendRequest::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
	/*CString str;
	GetDlgItemText(IDC_EDIT1,str);
	if(str.GetLength()>200)
	{
		//AfxMessageBox(L"�������ݳ��ȴ���200��",0,0);
		CString cs;
		cs = str.Left(200);
		SetDlgItemText(IDC_EDIT1,cs);
	}*/
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
