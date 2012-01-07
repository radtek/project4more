// ScrollerCtrl.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ScrollerCtrl.h"
#include "header.h"

// CScrollerCtrl
string retValue;
IMPLEMENT_DYNAMIC(CScrollerCtrl, CWnd)

CScrollerCtrl::CScrollerCtrl()
{
    bgColor =RGB(229,243,254); // ����ɫ
    fgColor = RGB(64, 74, 83); // ����ɫ

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
// CScrollerCtrl ��Ϣ�������
       
// create the window.
BOOL CScrollerCtrl::Create(CWnd* pParentWnd, ServerIO *pSvrIO, UINT nID)
{
    bgColor = GLB::scrollBarBgColor; // ����ɫ
    fgColor = GLB::scrollBarFgColor; // ����ɫ

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
	bgBrush.CreateSolidBrush(bgColor); //�ı䱳��
	ifPause = FALSE;

    mTimer = SetTimer(nID, 20, NULL);
	//showWidth   =   GetSystemMetrics(SM_CXSCREEN);   
	//showHeight   =   GetSystemMetrics(SM_CYSCREEN); 
	
	//this->MoveWindow(0,(int)(showHeight/10 * 9),showWidth,(int)(showHeight/10 * 1 +10),TRUE);

	int iFontSize = showHeight*2/3;
	
	curFont.CreateFont(iFontSize-2, iFontSize/2-1, 0, 0, FW_THIN, FALSE, FALSE, 0, ANSI_CHARSET,
                      OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, 
                      DEFAULT_PITCH|FF_MODERN, "������");
	
	curFont.GetLogFont(&logFont);
	
	//������Bar������ʾ�����λ��
    showYLocation = (int)(showHeight/2 - logFont.lfHeight / 2); 

    //showMsg = msg;
    getShowMsg();


	HANDLE hThread = CreateThread(NULL, 0, ThreadScroll, this, 0, NULL);
    return TRUE;
}
        
// ��ȡ��Ϣ
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

    // �������10����Ϣ����ɾ��ǰ��������Ϣ��
    int retNum = showMsg.size() - 10; 
    retNum = (retNum < 0) ? 0 : retNum;    
    showMsg.erase(showMsg.begin(), showMsg.begin()+retNum);

    return 0;
}
    
// ������ʾ
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
        if (++ curShowMsgIndex == showMsg.size() )  // ���һ����¼��ʾ��ɺ����»�ȡ��Ϣ��
        {
            getShowMsg();
            curShowMsgIndex = 0;
        }
		strCurrentPos = showWidth;  //�ص���ʼλ��
	}
	if(!ifPause)
		strCurrentPos = strCurrentPos - 1;  //ÿ�������ƶ�����

	 
	CDC *pDc; //��Ļ��ͼ�豸
	CDC memDC; //�ڴ��ͼ�豸
	
    CRect rectClient; // �ڿͻ�������ϵ�µ�RECT����,���Եõ����ڵĴ�С
    GetClientRect(&rectClient);
    
    CRect rect1, rect2; // ����Ļ����ϵ�µ�RECT����
    parentWnd->GetClientRect(&rect1); // �����ڶԻ�������
    parentWnd->ClientToScreen(rect1); // �ѿͻ�������ϵ�µ�RECT����ת��Ϊ��Ļ����ϵ�µ�RECT����.
    GetWindowRect(&rect2);

    // �������
    int relX = rect2.left - rect1.left;
    int relY = rect2.top - rect1.top;

    pDc = parentWnd->GetDC();// ָ��
	CBitmap memBitmap;
	//�����ڴ��ͼ�豸	
	memDC.CreateCompatibleDC(NULL);               
	memBitmap.CreateCompatibleBitmap(pDc, rectClient.right, rectClient.bottom);
	memDC.SelectObject(&memBitmap);
	
	//�Զ����ͼ����
	
	memDC.FillSolidRect(&rectClient, RGB(0, 0, 255));
	memDC.SelectObject(&curFont);
	memDC.SetTextColor(fgColor);
	memDC.SetBkMode(TRANSPARENT);
	
	memDC.Rectangle(&rectClient);
	memDC.FillRect(&rectClient, &bgBrush);
 	memDC.TextOut(strCurrentPos, showYLocation, showMsg[curShowMsgIndex]);    
	
	
	//���ڴ��ͼ��������Ļ
    pDc->BitBlt(relX, relY, rectClient.Width(), rectClient.Height(), &memDC, 0, 0, SRCCOPY); 
		
	//�����ͷ�
	parentWnd->ReleaseDC(pDc);
	memDC.DeleteDC();
	memBitmap.DeleteObject();
}
        
// ��ʱ����Ϣ����
void CScrollerCtrl::OnTimer(UINT_PTR nIDEvent)
{
    // TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
	
	//������Bar������ʾ�����λ��
    showYLocation = (int)(showHeight/2 - logFont.lfHeight / 2); 
    
    mTimer = SetTimer(mTimer, 20, NULL);

    return 0;
}