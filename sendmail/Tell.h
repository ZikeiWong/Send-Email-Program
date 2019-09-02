#pragma once


// CTell 对话框

class CTell : public CDialogEx
{
	DECLARE_DYNAMIC(CTell)

public:
	CTell(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTell();

// 对话框数据
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
