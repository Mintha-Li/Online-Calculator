#include "pch.h"
#include "NumEdit.h"


BEGIN_MESSAGE_MAP(CNumEdit, CEdit)
	ON_WM_CHAR()
	ON_WM_CREATE()
END_MESSAGE_MAP()

CNumEdit::CNumEdit(void)
{
	maxValue = INFTY;
	minValue = -INFTY;
}


CNumEdit::~CNumEdit(void)
{
}


void CNumEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CString str;
	GetWindowText(str);

	int nSource, nDestination;
	GetSel(nSource, nDestination);

	// ��֤С�������ֻ�ܳ���һ��
	if (nChar == '.')
	{
		//��ԭ�����ַ������Ѿ���һ��С����,�򲻽�С��������,��֤�����ֻ������һ��С����
		if (str.Find('.') != -1)
		{
		}
		// ������������С����
		else
		{
			CEdit::OnChar(nChar, nRepCnt, nFlags);
		}
	}
	// ��֤����ֻ�ܳ���һ��,����ֻ�ܳ����ڵ�һ���ַ�
	else if (nChar == '-')
	{
		// ��û�������κ��ַ���
		if (str.IsEmpty())
		{
			CEdit::OnChar(nChar, nRepCnt, nFlags);
		}
		else
		{
			// ��ʱѡ����ȫ��������
			if (nSource == 0 && nDestination == str.GetLength() || nSource == 0 && nDestination == 0 && str.Left(1).Compare(L"-"))
			{
				CEdit::OnChar(nChar, nRepCnt, nFlags);
			}
			else
			{
			}
		}
	}
	// ����С����͸���,��������������,Backspace,Delete
	else if ((nChar >= '0' && nChar <= '9') || (nChar == 0x08) || (nChar == 0x10))
	{
		//����ǵ�һ���ַ������룬������'-'������
		if (nSource == 0 && nDestination == 0 && !str.IsEmpty() && str.Find('-') != -1)
		{
		}
		else
		{
			CEdit::OnChar(nChar, nRepCnt, nFlags);
		}

	}
	// �����ļ�,������Ӧ
	else
	{
	}

	GetWindowText(str);
	if (_ttof(str) > maxValue)
	{
		CString msg;
		msg.Format(L"�������ֵ���ܴ��� %0.1f", maxValue);
		MessageBox(msg, L"��������");
		SetWindowText(L"");
	}
	else if (_ttof(str) < minValue)
	{
		CString msg;
		msg.Format(L"�������ֵ����С�� %0.1f", minValue);
		MessageBox(msg, L"��������");
		SetWindowText(L"");
	}
}

void CNumEdit::setRange(double min, double max)
{
	maxValue = max;
	minValue = min;
}