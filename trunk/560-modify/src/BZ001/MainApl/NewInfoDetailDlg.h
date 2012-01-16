#pragma once
#include "resource.h"
#include "afxwin.h"
#include "HyperLink/HyperLink.h"
#include "GLB.h"

// CNewInfoDetailDlg 对话框


class CNewInfoDetailDlg : public CDialog
{
	DECLARE_DYNAMIC(CNewInfoDetailDlg)

public:
	enum {eInfoType_Goods, eInfoType_Cars, eInfoType_SpecialLine, eInfoType_CustomGoods, eInfoType_CustomCars, eInfoType_MyGoods, eInfoType_MyCars};
	CNewInfoDetailDlg(const void* m_pNewInfoDetail, int nInfoType, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CNewInfoDetailDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_DETAIL_INFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonClose();
	afx_msg void OnBnClickedButtonSendSms();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
private:
	void InitNewInfoDetail(const TabNewInfRecord* pInfoDetail);
	void InitCustomInfoDetail(const TabCustomInfRecord* pInfoDetail);
	void InitMyInfoDetail(const TabMyInfRecord* pInfoDetail);
private:
	const void* m_pInfoDetail;
	int m_nInfoType;
	CHyperLink m_publisher;
};
