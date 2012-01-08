// ScrollerCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "ScrollerCtrl.h"
#include "header.h"

// CScrollerCtrl
string retValue;
IMPLEMENT_DYNAMIC(CScrollerCtrl, CWnd)

CScrollerCtrl::CScrollerCtrl()
{
    bgColor =RGB(229,243,254); // 背景色
    fgColor = RGB(64, 74, 83); // 文字色

    svrIO = NULL;

    //CString tmp = "";
    //showMsg.push_back(tmp);
}

CScrollerCtrl::~CScrollerCtrl()
{
}


BEGIN_MESSAGE_MAP(CScrollerCtrl, CWnd)
    ON_WM_TIMER()
END_MESSAGE_MAP()


DWORD WINAPI ThreadScroll(LPVOID lpVoid)
{
	CScrollerCtrl * dlg = (CScrollerCtrl*)lpVoid;
	while(1)
	{
		if(m_bClose)
			break;
		dlg->DrawScrollerText();
		Sleep(15);
	}
	return 0;
}
// CScrollerCtrl 消息处理程序
       
// create the window.
BOOL CScrollerCtrl::Create(CWnd* pParentWnd, ServerIO *pSvrIO, UINT nID)
{
    bgColor = GLB::scrollBarBgColor; // 背景色
    fgColor = GLB::scrollBarFgColor; // 文字色

    svrIO = pSvrIO;
    parentWnd = pParentWnd;

    CRect rect;
    //mShow.GetWindowRect(&rect);
    GetClientRect(&rect);

    showWidth = rect.right;
    showHeight = rect.bottom;

    strCurrentPos = rect.right;
	curShowMsgIndex = 0;

	mTimer = 0;
	bgBrush.CreateSolidBrush(bgColor); //改变背景
	ifPause = FALSE;

    mTimer = SetTimer(nID, 20, NULL);
	//showWidth   =   GetSystemMetrics(SM_CXSCREEN);   
	//showHeight   =   GetSystemMetrics(SM_CYSCREEN); 
	
	//this->MoveWindow(0,(int)(showHeight/10 * 9),showWidth,(int)(showHeight/10 * 1 +10),TRUE);

	int iFontSize = showHeight*2/3;
	
	curFont.CreateFont(iFontSize-2, iFontSize/2-1, 0, 0, FW_THIN, FALSE, FALSE, 0, ANSI_CHARSET,
                      OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, 
                      DEFAULT_PITCH|FF_MODERN, "新宋体");
	
	curFont.GetLogFont(&logFont);
	
	//设置在Bar里面显示坐标的位置
    showYLocation = (int)(showHeight/2 - logFont.lfHeight / 2); 

    //showMsg = msg;
    getShowMsg();


	HANDLE hThread = CreateThread(NULL, 0, ThreadScroll, this, 0, NULL);
    return TRUE;
}
        
// 获取信息
int CScrollerCtrl::getShowMsg()
{    
    //string retValue = svrIO->getAgentScrollAd();
	//retValue = svrIO->getAgentScrollAd();
    if (retValue != "TRUE" && !(showMsg.empty())) {
        return -1;
    }

    vector<AdMsg>::iterator iterAg = svrIO->agScrollAd.begin();
    while (iterAg != svrIO->agScrollAd.end()) {
        showMsg.push_back((*iterAg).inf.c_str());
        ++iterAg;
    }

    // 如果超过10条信息，则删除前面多余的信息。
    int retNum = showMsg.size() - 10; 
    retNum = (retNum < 0) ? 0 : retNum;    
    showMsg.erase(showMsg.begin(), showMsg.begin()+retNum);

    return 0;
}
    
// 滚动显示
void CScrollerCtrl::DrawScrollerText() 
{
    if (!showMsg.size())
	{
		Invalidate();
		return;
	}

	if(strCurrentPos < - (showMsg[curShowMsgIndex].GetLength()* \
		logFont.lfWidth + logFont.lfWidth))
	{
		//curShowMsgIndex = (++ curShowMsgIndex) % showMsg.size();
        if (++ curShowMsgIndex == showMsg.size() )  // 最后一条记录显示完成后，重新获取信息。
        {
            getShowMsg();
            curShowMsgIndex = 0;
        }
		strCurrentPos = showWidth;  //回到起始位置
	}
	if(!ifPause)
		strCurrentPos = strCurrentPos - 1;  //每步向左移动距离

	 
	CDC *pDc; //屏幕绘图设备
	CDC memDC; //内存绘图设备
	
    CRect rectClient; // 在客户区坐标系下的RECT坐标,可以得到窗口的大小
    GetClientRect(&rectClient);
    
    CRect rect1, rect2; // 在屏幕坐标系下的RECT坐标
    parentWnd->GetClientRect(&rect1); // 父窗口对话框坐标
    parentWnd->ClientToScreen(rect1); // 把客户区坐标系下的RECT坐标转换为屏幕坐标系下的RECT坐标.
    GetWindowRect(&rect2);

    // 相对坐标
    int relX = rect2.left - rect1.left;
    int relY = rect2.top - rect1.top;

    pDc = parentWnd->GetDC();// 指针
	CBitmap memBitmap;
	//创建内存绘图设备	
	memDC.CreateCompatibleDC(NULL);               
	memBitmap.CreateCompatibleBitmap(pDc, rectClient.right, rectClient.bottom);
	memDC.SelectObject(&memBitmap);
	
	//自定义绘图函数
	
	memDC.FillSolidRect(&rectClient, RGB(0, 0, 255));
	memDC.SelectObject(&curFont);
	memDC.SetTextColor(fgColor);
	memDC.SetBkMode(TRANSPARENT);
	
	memDC.Rectangle(&rectClient);
	memDC.FillRect(&rectClient, &bgBrush);
 	memDC.TextOut(strCurrentPos, showYLocation, showMsg[curShowMsgIndex]);    
	
	
	//把内存绘图拷贝到屏幕
    pDc->BitBlt(relX, relY, rectClient.Width(), rectClient.Height(), &memDC, 0, 0, SRCCOPY); 
		
	//清理释放
	parentWnd->ReleaseDC(pDc);
	memDC.DeleteDC();
	memBitmap.DeleteObject();
}
        
// 定时器消息处理
void CScrollerCtrl::OnTimer(UINT_PTR nIDEvent)
{
    // TODO: 在此添加消息处理程序代码和/或调用默认值
	//EnterCriticalSection(&csPrint);
    //DrawScrollerText();
	//LeaveCriticalSection(&csPrint);
    CWnd::OnTimer(nIDEvent);
}
    
// destroy the window.
int CScrollerCtrl::Resize()
{
    KillTimer(mTimer); 

    CRect rect;
    //mShow.GetWindowRect(&rect);
    GetClientRect(&rect);

    showWidth = rect.right;
    showHeight = rect.bottom;

    strCurrentPos = rect.right;
	curShowMsgIndex = 0;

    ifPause = FALSE;   
	
	//设置在Bar里面显示坐标的位置
    showYLocation = (int)(showHeight/2 - logFont.lfHeight / 2); 
    
    mTimer = SetTimer(mTimer, 20, NULL);

    return 0;
}