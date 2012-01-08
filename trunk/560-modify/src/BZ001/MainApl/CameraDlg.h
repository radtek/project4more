#pragma once

#include <highgui.h>
#include "afxwin.h"

// CCameraDlg 对话框

class CCameraDlg : public CDialog
{
	DECLARE_DYNAMIC(CCameraDlg)

public:
	CCameraDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCameraDlg();

// 对话框数据
	enum { IDD = IDD_CAMERA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
public:
	afx_msg void OnBnClickedGetpic();
public:
	int searchDevice();
public:
	CvvImage img[10];//显示到控件
    int nCameraNum;//当前选中摄像头序号
	BOOL m_bL[10];//用于跳出线程while
	BOOL m_bOpen[10];//是否断开连接
	IplImage *pFrame[10];//当前图像数据
	
public:
	virtual BOOL OnInitDialog();
public:
	afx_msg void OnDestroy();
};
