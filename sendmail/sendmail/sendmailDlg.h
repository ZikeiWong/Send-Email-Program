
// sendmailDlg.h : 头文件
//

#pragma once
#include "SetServerDlg.h"
#include "Tell.h"


// CsendmailDlg 对话框
class CsendmailDlg : public CDialogEx
{
// 构造
public:
	CsendmailDlg(CWnd* pParent = NULL);	// 标准构造函数
	CSetServerDlg set;
	CTell tell;

// 对话框数据
	enum { IDD = IDD_SENDMAIL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
