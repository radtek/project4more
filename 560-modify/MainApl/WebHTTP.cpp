// WebHTTP.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WLRClient.h"
#include "WebHTTP.h"
#include "GLB.h"

// CWebHTTP �Ի���

IMPLEMENT_DYNAMIC(CWebHTTP, CDialog)

CWebHTTP::CWebHTTP(CWnd* pParent /*=NULL*/)
	: CDialog(CWebHTTP::IDD, pParent)
{

}

CWebHTTP::~CWebHTTP()
{
}

void CWebHTTP::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EXPLORER1, mWebBrowser);
}


BEGIN_MESSAGE_MAP(CWebHTTP, CDialog)
	ON_WM_SIZE()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDOK, &CWebHTTP::OnBnClickedOk)
END_MESSAGE_MAP()


// CWebHTTP ��Ϣ�������

BOOL CWebHTTP::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	int cxScreen = ::GetSystemMetrics(SM_CXSCREEN);//�����Ļ�� 
	int cyScreen = ::GetSystemMetrics(SM_CYSCREEN); //�����Ļ�� 
	int x = (cxScreen - 800)/2;  // ����λ��x����
	int y = (cyScreen - 600)/2;  // ����λ��y����
	int w = 800;    //���ڿ�Ϊ800
	int h = 600;    //���ڸ�Ϊ600

	//SetWindowPos(this->m_hWnd,HWND_BOTTOM,x,y,w,h,SWP_NOZORDER);
	SetWindowPos(this,x,y,w,h,SWP_NOZORDER);
	CenterWindow(this);
	//m_flag = FALSE;
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	mWebBrowser.Navigate(url.c_str(), NULL, NULL, NULL, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CWebHTTP::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	CWnd* pCBtn= GetDlgItem(IDC_EXPLORER1);
	if( pCBtn != NULL) {
		RECT rct;
		GetClientRect(&rct);

		pCBtn->MoveWindow(rct.left, rct.top, rct.right - rct.left, rct.bottom - rct.top);
	}
	// TODO: �ڴ˴������Ϣ����������
}

void CWebHTTP::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	DestroyWindow();
	CDialog::OnClose();
}

void CWebHTTP::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//OnOK();
}
