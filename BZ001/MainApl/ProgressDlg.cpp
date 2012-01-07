// ProgressDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WLRClient.h"
#include "ProgressDlg.h"


// CProgressDlg �Ի���
HWND m_progress;
IMPLEMENT_DYNAMIC(CProgressDlg, CDialog)

CProgressDlg::CProgressDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProgressDlg::IDD, pParent)
{

}

CProgressDlg::~CProgressDlg()
{
}

void CProgressDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS1, m_wndProgHorz);
}


BEGIN_MESSAGE_MAP(CProgressDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CProgressDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CProgressDlg::OnBnClickedCancel)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CProgressDlg ��Ϣ�������

BOOL CProgressDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_progress = m_hWnd;
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_wndProgHorz.SetRange(0, 100);
	m_wndProgHorz.SetStep(1);
	m_wndProgHorz.SetPos(0);
	int piAlpha[5] = { 25, 50, 75, 100, 100 };
	m_wndProgHorz.SetMarquee(TRUE, 50, 2, 12, piAlpha);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CProgressDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//OnOK();
}

void CProgressDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//OnCancel();
}

void CProgressDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialog::OnClose();
}
