#pragma once


// CSetServerDlg 对话框

class CSetServerDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSetServerDlg)

public:
	CSetServerDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSetServerDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };
	CString m_severadd, m_port;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
