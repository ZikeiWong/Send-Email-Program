// Tell.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "sendmail.h"
#include "Tell.h"
#include "afxdialogex.h"


// CTell �Ի���

IMPLEMENT_DYNAMIC(CTell, CDialogEx)

CTell::CTell(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTell::IDD, pParent)
{

}

CTell::~CTell()
{
}

void CTell::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTell, CDialogEx)
END_MESSAGE_MAP()


// CTell ��Ϣ�������
