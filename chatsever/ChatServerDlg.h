// ChatServerDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "ChatSocket.h"
#include "ServerSocket.h"


// CChatServerDlg �Ի���
class CChatServerDlg : public CDialog
{
// ����
public:
	CChatServerDlg(CWnd* pParent = NULL);	// ��׼���캯��
	

// �Ի�������
	enum { IDD = IDD_CHATSERVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
