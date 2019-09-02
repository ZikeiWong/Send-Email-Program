// Tell.cpp : 实现文件
//

#include "stdafx.h"
#include "sendmail.h"
#include "Tell.h"
#include "afxdialogex.h"


// CTell 对话框

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


// CTell 消息处理程序
