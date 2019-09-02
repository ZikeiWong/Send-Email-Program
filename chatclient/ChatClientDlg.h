// ChatClientDlg.h : ͷ�ļ�
//

#pragma once

#include "MySocket.h" //ʹ����������ܹ�����Socket��Ĵ����ļ�

// CChatClientDlg �Ի���
class CChatClientDlg : public CDialog
{
// ����
public:
	CChatClientDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CHATCLIENT_DIALOG };

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
