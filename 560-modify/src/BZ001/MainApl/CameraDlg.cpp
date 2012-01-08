// CameraDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "WLRClient.h"
#include "CameraDlg.h"

#include "camerads.h"

// CCameraDlg 对话框

// 摄像头线程
DWORD WINAPI Thread(LPVOID lpVoid)
{
	CCameraDlg * dlg = (CCameraDlg*)lpVoid;//AfxGetApp()->GetMainWnd();
	CCameraDS camera;
	int num = (int)lpVoid;
	dlg->m_bL[0] = FALSE;
	//打开第一个摄像头
	//if(!camera.OpenCamera(0, false, 320,240)) //false不弹出属性选择窗口，用代码制定图像宽和高
	if(!camera.OpenCamera(0)) 
	{
		//AfxMessageBox("无法打开当前摄像头！");
		return -1;
	}
	CRect rect;
	CDC *dc = dlg->GetDlgItem(IDC_PIC)->GetDC();
	CRect pic_rect;
	dlg->GetDlgItem(IDC_PIC)->GetClientRect(&pic_rect);
	while(1)
	{
		//获取一帧
		dlg->pFrame[0] = camera.QueryFrame();
		dlg->img[0].CopyOf(dlg->pFrame[0],3);
		//图片显示到控件
		dlg->img[0].DrawToHDC(dc->GetSafeHdc(),&pic_rect); // cvvimage类中的函数
		if (dlg->m_bL[0])
			break;
		Sleep(40);//控制帧率
	}
	camera.CloseCamera(); //可不调用此函数，CCameraDS析构时会自动关闭摄像头
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


// CCameraDlg 消息处理程序

void CCameraDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}

// 拍摄截图
void CCameraDlg::OnBnClickedGetpic()
{
	// TODO: 在此添加控件通知处理程序代码
	char BASED_CODE szFilter[] = "jpg文件 (*jpg)|*jpg||";
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
	//获取摄像头数目
	int cam_count = CCameraDS::CameraCount();
	if (cam_count <=0) {
		//MessageBox("没有找到摄像头设备！", "560");
		//AfxMessageBox("没有找到摄像头设备！",MB_OK);
		//::MessageBox(NULL,"没有找到摄像头设备！", "560",MB_OK);
		return -1;
	}

	//开启线程
	HANDLE hThread = CreateThread(NULL, 0, Thread, this, 0, NULL);
	return 0;
}



BOOL CCameraDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
    // 
	//searchDevice();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CCameraDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	for (int i=0; i<10; i++) {
		if (!m_bL[i]) {
			m_bL[i] = TRUE;
		}
	}
	
	Sleep(200);
}
