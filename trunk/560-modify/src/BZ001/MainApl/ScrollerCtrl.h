#pragma once

#include "GLB.h"
#include "ServerIO.h"

//#include <vector>

// CScrollerCtrl

class CScrollerCtrl : public CWnd
{
	DECLARE_DYNAMIC(CScrollerCtrl)

public:
	CScrollerCtrl();
	virtual ~CScrollerCtrl();

// {
public:
    // create the window.
	BOOL Create(CWnd* pParentWnd, ServerIO *pSvrIO, UINT nID = 100);

    // resize the window.
    int Resize();

    // 设置背景色
    void SetBgColor(COLORREF clrBg) {
        bgColor = clrBg;
    };
    // 设置文字颜色
    void SetFgColor(COLORREF clrBg) {
        fgColor = clrBg;
    };
	// 滚动显示
	void DrawScrollerText();
private:
    // 服务器通信
    ServerIO *svrIO;

    CWnd*   parentWnd;    // 父窗口指针
    CRect	repaintRect;  // 重绘的区域
	CFont	curFont;	  // 当前显示的字体
	CBrush	bgBrush;	  // 改变显示区背景颜色

    COLORREF bgColor; // 背景色
    COLORREF fgColor; // 文字色

	int	curShowMsgIndex; // 当前显示的语句

	int showHeight;	// 当前显示区域的高度
	int	showWidth;	// 当前显示区域的宽度

	LOGFONT logFont; // 系统显示的字体	
    UINT_PTR	mTimer;
	BOOL	ifPause;

	int	showYLocation; // 当前显示的字符串相对垂直位置
	int	strCurrentPos; // 字符显示起始水平位置	

	std::vector<CString> showMsg; // 当前要显示的消息

private:


    // 获取信息
    int getShowMsg();
// }

protected:
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnTimer(UINT_PTR nIDEvent);
};


