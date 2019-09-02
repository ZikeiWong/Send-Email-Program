// ChatClientDlg.h : 头文件
//

#pragma once

#include "MySocket.h" //使主界面程序能够访问Socket类的代码文件

// CChatClientDlg 对话框
class CChatClientDlg : public CDialog
{
// 构造
public:
	CChatClientDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CHATCLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListBox m_list;
	CEdit m_input;
	afx_msg void OnBnClickedConnect();
	afx_msg void OnBnClickedDisconnect();
	afx_msg void OnBnClickedSend();

	CMySocket* m_client;
	char buff[200];
	CTime m_tm;
	afx_msg void OnBnClickedtime();
	afx_msg void OnBnClickedtime2();
	afx_msg void OnBnClickedButton2();
	bool bbb;
};
