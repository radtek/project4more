#pragma once

#include <highgui.h>
#include "afxwin.h"

// CCameraDlg �Ի���

class CCameraDlg : public CDialog
{
	DECLARE_DYNAMIC(CCameraDlg)

public:
	CCameraDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCameraDlg();

// �Ի�������
	enum { IDD = IDD_CAMERA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
public:
	afx_msg void OnBnClickedGetpic();
public:
	int searchDevice();
public:
	CvvImage img[10];//��ʾ���ؼ�
    int nCameraNum;//��ǰѡ������ͷ���
	BOOL m_bL[10];//���������߳�while
	BOOL m_bOpen[10];//�Ƿ�Ͽ�����
	IplImage *pFrame[10];//��ǰͼ������
	
public:
	virtual BOOL OnInitDialog();
public:
	afx_msg void OnDestroy();
};
