// UserCenter.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WLRClient.h"
#include "UserCenter.h"
#include "GLB.h"

// CUserCenter �Ի���
static int j = 0;
IMPLEMENT_DYNAMIC(CUserCenter, CDialog)

CUserCenter::CUserCenter(CWnd* pParent /*=NULL*/)
	: CDialog(CUserCenter::IDD, pParent)
{

}

CUserCenter::~CUserCenter()
{
}

void CUserCenter::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EXPLORER1, mWebBrowser);
}


BEGIN_MESSAGE_MAP(CUserCenter, CDialog)
	ON_WM_SIZE()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDOK, &CUserCenter::OnBnClickedOk)
END_MESSAGE_MAP()


// CUserCenter ��Ϣ�������
BEGIN_EVENTSINK_MAP(CUserCenter, CDialog)
	ON_EVENT(CUserCenter, IDC_EXPLORER1, 259, CUserCenter::DocumentCompleteExplorer1, VTS_DISPATCH VTS_PVARIANT)
END_EVENTSINK_MAP()

void CUserCenter::DocumentCompleteExplorer1(LPDISPATCH pDisp, VARIANT* URL)
{
	// TODO: �ڴ˴������Ϣ����������
	CString strUrl;
	strUrl = URL->bstrVal;
	CString myUrl(WEB_SERVICE_ADDRESS.c_str());
	myUrl += "/fmp/menu.toIndex.action";
	CString cUrl(WEB_SERVICE_ADDRESS.c_str());
	cUrl += "/fmp/user.toUserCenter.action?page=personaldata";
	if (!strUrl.CompareNoCase(myUrl))
	{
		if ( j == 0)
		{
		GoTo(cUrl);
		j++;
		}
	}
	
}
void CUserCenter::GoTo( CString url )
{
	try
	{
		mWebBrowser.Navigate2(&CComVariant(url),NULL,NULL,NULL,NULL);
	}
	catch (...)
	{
		GoTo(url);
	}
}
BOOL CUserCenter::OnInitDialog()
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
	j=0;
	//m_flag = FALSE;
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	mWebBrowser.Navigate(url.c_str(), NULL, NULL, NULL, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CUserCenter::OnSize(UINT nType, int cx, int cy)
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

void CUserCenter::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	DestroyWindow();
	CDialog::OnClose();
}

void CUserCenter::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//OnOK();
}
