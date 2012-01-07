// SendPhoneMsgDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "WLRClient.h"
#include "SendPhoneMsgDlg.h"
#include "MyLib.h"

// CSendPhoneMsgDlg 对话框

IMPLEMENT_DYNAMIC(CSendPhoneMsgDlg, CDialog)

CSendPhoneMsgDlg::CSendPhoneMsgDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSendPhoneMsgDlg::IDD, pParent)
    , phoneMsg(_T(""))
    , phoneNumber(_T(""))
{

}

CSendPhoneMsgDlg::~CSendPhoneMsgDlg()
{
}

void CSendPhoneMsgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_SEND_PHONEMSG_MSG, phoneMsg);
	DDX_Text(pDX, IDC_SEND_PHONEMSG_PHONE, phoneNumber);
	DDX_Control(pDX, IDC_SEND_PHONEMSG_PHONE, myedit);
}


BEGIN_MESSAGE_MAP(CSendPhoneMsgDlg, CDialog)
    ON_BN_CLICKED(IDOK, &CSendPhoneMsgDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CSendPhoneMsgDlg 消息处理程序
CString sHead[26]= {"139","138","137","136","135","134","159","158","157","152","151","150","182","188","187","130","131","132","156","155","186","185","133","153","189","180"};
void CSendPhoneMsgDlg::OnBnClickedOk()
{
    // TODO: 在此添加控件通知处理程序代码
    UpdateData();
    bool ifOK = true;
    // 判断必填字段
    if (phoneMsg == "") {
        MessageBox("短信内容不能为空", "发送短信");
        ifOK = false;
        return;
    }	
    if (phoneNumber == "") {
        MessageBox("手机号码不能为空", "发送短信");
        ifOK = false;
        return;
    }
	else
	{
		int len = phoneNumber.GetLength();
		if (len <= 11)
		{
			if (len < 11)
			{
				MessageBox("手机号码格式错误！","号码错误！");
				return;
			}
			CString tmp;
			tmp = phoneNumber.Left(3);
			int nSet = 0;
			for (int i=0;i<26;i++)
			{
				if (tmp == sHead[i])
				{
					CString s;
					s = phoneNumber.Left(11);
					int ndex = s.Find(',');
					if (ndex == -1)
					{
						break;
					}
					else
					{
						MessageBox("手机号码格式错误！","号码错误！");
						return;
					}
					break;
				}
				else
					nSet++;
			}
			if (nSet == 26)
			{
				MessageBox("手机号码格式错误！","号码错误！");
				return;
			}
		}
		else
		{
// 			int nstart = 0;
// 			while(1)
// 			{
// 				int index = phoneNumber.Find(',',nstart);
// 				if (index == -1)
// 				{
// 					MessageBox("手机号码格式不对！", "发送短信");
// 					return;
// 				}
// 				int nSum = index % 11;
// 				if (nSum != 0)
// 				{
// 					//if (phoneNumber.GetAt(index+1) != '\0')
// 					//MessageBox("手机号码格式不对！", "发送短信");
// 					//return;
// 				}
// 				else
// 				{
// 					if (phoneNumber.GetAt(index+1) == '\0')
// 					{
// 						MessageBox("手机号码格式不对！", "发送短信");
// 						return;
// 					}
// 				}
// 				//nstart = index +1;
// 			}
			CStringArray dest;
			Split(phoneNumber,dest,",");
			if (dest.GetSize() == 0)
			{
				MessageBox("手机号码格式错误！","号码错误！");
				return;
			}
			for(int i=0;i<dest.GetSize();i++)
			{
				if (dest[i].GetLength() != 11)
				{
					MessageBox("手机号码格式错误！","号码错误！");
					return;
				}
				else
				{
					int nSet = 0;
					for (int k=0;k<26;k++)
					{
						if (dest[i].Left(3) == sHead[k])
						{
							CString s;
							s = phoneNumber.Left(11);
							int ndex = s.Find(',');
							if (ndex == -1)
							{
								break;
							}
							else
							{
								MessageBox("手机号码格式错误！","号码错误！");
								return;
							}
							break;
						}
						else
							nSet++;
					}
					if (nSet == 26)
					{
						MessageBox("手机号码格式错误！","号码错误！");
						return;
					}
				}
			}
		}

	}
    if (ifOK) {      
        OnOK();
    }
}
