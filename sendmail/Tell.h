#pragma once


// CTell �Ի���

class CTell : public CDialogEx
{
	DECLARE_DYNAMIC(CTell)

public:
	CTell(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTell();

// �Ի�������
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
