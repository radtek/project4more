#pragma once

#include "ColorPicker.h"
#include "GLB.h"
// CConfigSetDlg 对话框

class CConfigSetDlg : public CDialog
{
	DECLARE_DYNAMIC(CConfigSetDlg)

public:
	CConfigSetDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CConfigSetDlg();

// 对话框数据
	enum { IDD = IDD_CONFIG_SET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
// { 自定义
public:
    CColorPicker  sysBkClr;
	CColorPicker  gridClr;
    CColorPicker  oddFgClr;
	CColorPicker  oddBkClr;
    CColorPicker  evenFgClr;
	CColorPicker  evenBkClr;

    SettingColor myColor; // 颜色信息
    SettingFont oddFont; // 奇数行字体信息
    SettingFont evenFont; // 偶数行字体信息

// }
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedConfigSetSysbkclr();
public:
    afx_msg void OnBnClickedConfigSetGridclr();
public:
    afx_msg void OnBnClickedConfigSetOddbkclr();
public:
    afx_msg void OnBnClickedConfigSetEvenbkclr();
public:
    afx_msg void OnBnClickedConfigSetOddfont();
public:
    afx_msg void OnBnClickedConfigSetEvenfont();
public:
    afx_msg void OnBnClickedOk();
public:
    virtual BOOL OnInitDialog();
public:
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
public:
    afx_msg void OnBnClickedConfigSetOddfgclr();
public:
    afx_msg void OnBnClickedConfigSetEvenfgclr();
	afx_msg void OnBnClickedDefault();
};
