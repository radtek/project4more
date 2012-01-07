// SendPhoneMsgDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WLRClient.h"
#include "SendPhoneMsgDlg.h"
#include "MyLib.h"

// CSendPhoneMsgDlg �Ի���

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


// CSendPhoneMsgDlg ��Ϣ�������
CString sHead[26]= {"139","138","137","136","135","134","159","158","157","152","151","150","182","188","187","130","131","132","156","155","186","185","133","153","189","180"};
void CSendPhoneMsgDlg::OnBnClickedOk()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    UpdateData();
    bool ifOK = true;
    // �жϱ����ֶ�
    if (phoneMsg == "") {
        MessageBox("�������ݲ���Ϊ��", "���Ͷ���");
        ifOK = false;
        return;
    }	
    if (phoneNumber == "") {
        MessageBox("�ֻ����벻��Ϊ��", "���Ͷ���");
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
				MessageBox("�ֻ������ʽ����","�������");
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
						MessageBox("�ֻ������ʽ����","�������");
						return;
					}
					break;
				}
				else
					nSet++;
			}
			if (nSet == 26)
			{
				MessageBox("�ֻ������ʽ����","�������");
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
// 					MessageBox("�ֻ������ʽ���ԣ�", "���Ͷ���");
// 					return;
// 				}
// 				int nSum = index % 11;
// 				if (nSum != 0)
// 				{
// 					//if (phoneNumber.GetAt(index+1) != '\0')
// 					//MessageBox("�ֻ������ʽ���ԣ�", "���Ͷ���");
// 					//return;
// 				}
// 				else
// 				{
// 					if (phoneNumber.GetAt(index+1) == '\0')
// 					{
// 						MessageBox("�ֻ������ʽ���ԣ�", "���Ͷ���");
// 						return;
// 					}
// 				}
// 				//nstart = index +1;
// 			}
			CStringArray dest;
			Split(phoneNumber,dest,",");
			if (dest.GetSize() == 0)
			{
				MessageBox("�ֻ������ʽ����","�������");
				return;
			}
			for(int i=0;i<dest.GetSize();i++)
			{
				if (dest[i].GetLength() != 11)
				{
					MessageBox("�ֻ������ʽ����","�������");
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
								MessageBox("�ֻ������ʽ����","�������");
								return;
							}
							break;
						}
						else
							nSet++;
					}
					if (nSet == 26)
					{
						MessageBox("�ֻ������ʽ����","�������");
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
