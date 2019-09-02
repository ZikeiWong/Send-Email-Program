// SetServerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "sendmail.h"
#include "SetServerDlg.h"
#include "afxdialogex.h"


// CSetServerDlg 对话框

IMPLEMENT_DYNAMIC(CSetServerDlg, CDialogEx)

CSetServerDlg::CSetServerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetServerDlg::IDD, pParent)
{

}

CSetServerDlg::~CSetServerDlg()
{
}

void CSetServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSetServerDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CSetServerDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CSetServerDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CSetServerDlg 消息处理程序


void CSetServerDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_EDIT1)->GetWindowText(m_severadd);
	GetDlgItem(IDC_EDIT2)->GetWindowText(m_port);
	::SendMessage(this->m_hWnd, WM_CLOSE, 0, 0);
}


void CSetServerDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_EDIT1)->SetWindowText("");
	GetDlgItem(IDC_EDIT2)->SetWindowText("");
}
