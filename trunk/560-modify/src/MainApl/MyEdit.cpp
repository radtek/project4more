// MyEdit.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WLRClient.h"
#include "MyEdit.h"


// CMyEdit

IMPLEMENT_DYNAMIC(CMyEdit, CEdit)

CMyEdit::CMyEdit()
{

}

CMyEdit::~CMyEdit()
{
}


BEGIN_MESSAGE_MAP(CMyEdit, CEdit)
	ON_WM_CHAR()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()



// CMyEdit ��Ϣ�������


CString sHeader[26]= {"139","138","137","136","135","134","159","158","157","152","151","150","182","188","187","130","131","132","156","155","186","185","133","153","189","180"};
void CMyEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (nChar == ',')
	{
		CString str;
		GetWindowText(str);
		int len = str.GetLength();
		if (len / 12 < 1)
		{
			if (len == 11)
			{
				CString tmp;
				tmp = str.Left(3);
				int nSet = 0;
				for (int i=0;i<26;i++)
				{
					if (tmp == sHeader[i])
					{
						CString s;
						s = str.Left(11);
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
				MessageBox("�ֻ������ʽ����","�������");
				return;
			}

		}
		else
		{
			int nright = str.ReverseFind(',');
			if (len - nright == 12)
			{
				CString tmp;
				tmp = str.Mid(nright+1,3);
				int nSet = 0;
				for (int i=0;i<26;i++)
				{
					if (tmp == sHeader[i])
					{
						CString s;
						s = str.Mid(nright+1,11);
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
				MessageBox("�ֻ������ʽ����","�������");
				return;
			}
		}
	}
	if (nChar != VK_BACK&& nChar != ',' && ( nChar > '9' || nChar < '0' ) )
		return;
	CEdit::OnChar(nChar, nRepCnt, nFlags);
}

BOOL CMyEdit::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (pMsg->message == WM_PASTE)
	{
		return 0;
	}
	return CEdit::PreTranslateMessage(pMsg);
}

void CMyEdit::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	return;
	CEdit::OnRButtonDown(nFlags, point);
}
