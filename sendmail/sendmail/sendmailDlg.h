
// sendmailDlg.h : ͷ�ļ�
//

#pragma once
#include "SetServerDlg.h"
#include "Tell.h"


// CsendmailDlg �Ի���
class CsendmailDlg : public CDialogEx
{
// ����
public:
	CsendmailDlg(CWnd* pParent = NULL);	// ��׼���캯��
	CSetServerDlg set;
	CTell tell;

// �Ի�������
	enum { IDD = IDD_SENDMAIL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
