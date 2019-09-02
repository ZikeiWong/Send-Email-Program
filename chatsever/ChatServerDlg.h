// ChatServerDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "ChatSocket.h"
#include "ServerSocket.h"


// CChatServerDlg 对话框
class CChatServerDlg : public CDialog
{
// 构造
public:
	CChatServerDlg(CWnd* pParent = NULL);	// 标准构造函数
	

// 对话框数据
	enum { IDD = IDD_CHATSERVER_DIALOG };

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
	afx_msg void OnBnClickedStart();
	afx_msg void OnBnClickedDisconnect();
	afx_msg void OnBnClickedSend();

	CTime m_tm;
	char buff[200];
	CChatSocket * m_chat;
	CServerSocket * m_server;
	afx_msg void OnBnClickedButton1();
	bool aaa;
	afx_msg void OnBnClickedButton2();
};
