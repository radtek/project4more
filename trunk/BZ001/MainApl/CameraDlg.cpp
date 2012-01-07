// CameraDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WLRClient.h"
#include "CameraDlg.h"

#include "camerads.h"

// CCameraDlg �Ի���

// ����ͷ�߳�
DWORD WINAPI Thread(LPVOID lpVoid)
{
	CCameraDlg * dlg = (CCameraDlg*)lpVoid;//AfxGetApp()->GetMainWnd();
	CCameraDS camera;
	int num = (int)lpVoid;
	dlg->m_bL[0] = FALSE;
	//�򿪵�һ������ͷ
	//if(!camera.OpenCamera(0, false, 320,240)) //false����������ѡ�񴰿ڣ��ô����ƶ�ͼ���͸�
	if(!camera.OpenCamera(0)) 
	{
		//AfxMessageBox("�޷��򿪵�ǰ����ͷ��");
		return -1;
	}
	CRect rect;
	CDC *dc = dlg->GetDlgItem(IDC_PIC)->GetDC();
	CRect pic_rect;
	dlg->GetDlgItem(IDC_PIC)->GetClientRect(&pic_rect);
	while(1)
	{
		//��ȡһ֡
		dlg->pFrame[0] = camera.QueryFrame();
		dlg->img[0].CopyOf(dlg->pFrame[0],3);
		//ͼƬ��ʾ���ؼ�
		dlg->img[0].DrawToHDC(dc->GetSafeHdc(),&pic_rect); // cvvimage���еĺ���
		if (dlg->m_bL[0])
			break;
		Sleep(40);//����֡��
	}
	camera.CloseCamera(); //�ɲ����ô˺�����CCameraDS����ʱ���Զ��ر�����ͷ
	return 0;
}


IMPLEMENT_DYNAMIC(CCameraDlg, CDialog)

CCameraDlg::CCameraDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCameraDlg::IDD, pParent)
{

}

CCameraDlg::~CCameraDlg()
{
}

void CCameraDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCameraDlg, CDialog)
	ON_BN_CLICKED(IDCANCEL, &CCameraDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_GetPic, &CCameraDlg::OnBnClickedGetpic)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CCameraDlg ��Ϣ�������

void CCameraDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnCancel();
}

// �����ͼ
void CCameraDlg::OnBnClickedGetpic()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	char BASED_CODE szFilter[] = "jpg�ļ� (*jpg)|*jpg||";
	CFileDialog dlg(FALSE, "jpg", NULL, OFN_HIDEREADONLY,szFilter);
	if (dlg.DoModal() == IDOK) {
		CString m_path = dlg.GetPathName();
		if (pFrame[0] != NULL) {
			cvSaveImage(m_path,pFrame[0]);//jpg
		}
	}
}

int CCameraDlg::searchDevice()
{
	//��ȡ����ͷ��Ŀ
	int cam_count = CCameraDS::CameraCount();
	if (cam_count <=0) {
		//MessageBox("û���ҵ�����ͷ�豸��", "560");
		//AfxMessageBox("û���ҵ�����ͷ�豸��",MB_OK);
		//::MessageBox(NULL,"û���ҵ�����ͷ�豸��", "560",MB_OK);
		return -1;
	}

	//�����߳�
	HANDLE hThread = CreateThread(NULL, 0, Thread, this, 0, NULL);
	return 0;
}



BOOL CCameraDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
    // 
	//searchDevice();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CCameraDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
	for (int i=0; i<10; i++) {
		if (!m_bL[i]) {
			m_bL[i] = TRUE;
		}
	}
	
	Sleep(200);
}
