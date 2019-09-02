// SetServerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "sendmail.h"
#include "SetServerDlg.h"
#include "afxdialogex.h"


// CSetServerDlg �Ի���

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


// CSetServerDlg ��Ϣ�������


void CSetServerDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_EDIT1)->GetWindowText(m_severadd);
	GetDlgItem(IDC_EDIT2)->GetWindowText(m_port);
	::SendMessage(this->m_hWnd, WM_CLOSE, 0, 0);
}


void CSetServerDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_EDIT1)->SetWindowText("");
	GetDlgItem(IDC_EDIT2)->SetWindowText("");
}
