// ChatClientDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ChatClient.h"
#include "ChatClientDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CChatClientDlg 对话框




CChatClientDlg::CChatClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChatClientDlg::IDD, pParent)
	, bbb(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChatClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_HISTORY, m_list);
	DDX_Control(pDX, IDC_INPUT, m_input);
}

BEGIN_MESSAGE_MAP(CChatClientDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_CONNECT, &CChatClientDlg::OnBnClickedConnect)
	ON_BN_CLICKED(IDC_DISCONNECT, &CChatClientDlg::OnBnClickedDisconnect)
	ON_BN_CLICKED(IDC_SEND, &CChatClientDlg::OnBnClickedSend)
	ON_BN_CLICKED(IDC_time, &CChatClientDlg::OnBnClickedtime)
	ON_BN_CLICKED(IDC_time2, &CChatClientDlg::OnBnClickedtime2)
	ON_BN_CLICKED(IDC_BUTTON2, &CChatClientDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CChatClientDlg 消息处理程序

BOOL CChatClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
GetDlgItem(IDC_DISCONNECT)->EnableWindow(FALSE);
GetDlgItem(IDC_SEND)->EnableWindow(FALSE); 
GetDlgItem(IDC_INPUT)->EnableWindow(FALSE); 
GetDlgItem(IDC_IPADDRESS)->SetWindowText((LPCTSTR)"127.0.0.1"); 
GetDlgItem(IDC_PORT)->SetWindowText((LPCTSTR)"5000");
GetDlgItem(IDC_time2)->EnableWindow(FALSE);

bbb=0;
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CChatClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CChatClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR CChatClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CChatClientDlg::OnBnClickedConnect()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_CONNECT)->EnableWindow(FALSE); 
	GetDlgItem(IDC_DISCONNECT)->EnableWindow(TRUE); 
	GetDlgItem(IDC_SEND)->EnableWindow(TRUE); 
	GetDlgItem(IDC_time2)->EnableWindow(TRUE);
	CString temp1,temp2; 
	GetDlgItem(IDC_IPADDRESS)->GetWindowText(temp1); 
	CString m_IPAddress=temp1.GetBuffer(temp1.GetLength() ); 
	GetDlgItem(IDC_PORT)->GetWindowText(temp2); 
	int m_Port=atoi(temp2); 
	m_client=new CMySocket; 
	if ((*m_client).Create()==0) 
	{ 
		CString errcode; 
		errcode.Format("%d",GetLastError()); 
		m_list.AddString(errcode); 
		UpdateData(FALSE); 
	} 
	m_client->Connect(m_IPAddress,m_Port);
	GetDlgItem(IDC_IPADDRESS)->EnableWindow(FALSE); 
	GetDlgItem(IDC_PORT)->EnableWindow(FALSE); 
	GetDlgItem(IDC_INPUT)->EnableWindow(TRUE); 
}

void CChatClientDlg::OnBnClickedDisconnect()
{
	// TODO: 在此添加控件通知处理程序代码
	(*m_client).Close(); 
	delete m_client; 
	GetDlgItem(IDC_IPADDRESS)->EnableWindow(TRUE); 
	GetDlgItem(IDC_PORT)->EnableWindow(TRUE); 
	GetDlgItem(IDC_INPUT)->EnableWindow(FALSE); 
	GetDlgItem(IDC_CONNECT)->EnableWindow(TRUE);
	GetDlgItem(IDC_SEND)->EnableWindow(FALSE); 
	GetDlgItem(IDC_DISCONNECT)->EnableWindow(FALSE); 
	GetDlgItem(IDC_time2)->EnableWindow(FALSE);
	CString str; 
	m_tm=CTime::GetCurrentTime(); 
	str=m_tm.Format("%X "); 
	str+="从服务器断开!"; 
	m_list.AddString(str); 
	UpdateData(FALSE);

}

void CChatClientDlg::OnBnClickedSend()
{
	// TODO: 在此添加控件通知处理程序代码
	m_input.GetWindowText(buff,200); 
	CString temp1="我："; 
	CString temp2=buff; 
	CString formatbuff="#c#s#"+(CString)buff;
	(*m_client).Send(formatbuff,200,0); 
	CString str; 
	m_tm=CTime::GetCurrentTime(); 
	str=m_tm.Format("%X "); 
	temp1=str+temp1; 
	temp1+=temp2; 
	m_list.AddString(temp1); 
	UpdateData(FALSE); 
	m_input.SetWindowText("");
}



void CChatClientDlg::OnBnClickedtime()
{
	// TODO: 在此添加控件通知处理程序代码
	CString temp3 = "(current time)";
	
	CString str;
	m_tm = CTime::GetCurrentTime();
	str = m_tm.Format("%X ");
	temp3 = str + temp3;
	
	m_list.AddString(temp3);
	UpdateData(FALSE);
}


void CChatClientDlg::OnBnClickedtime2()
{
	// TODO: 在此添加控件通知处理程序代码
	
	CString formatbuff = "#c#s#" + (CString)"time";
	(*m_client).Send(formatbuff, 200, 0);
}




void CChatClientDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CString formatbuff = "#c#s#" + (CString)"on";
	(*m_client).Send(formatbuff, 200, 0);
}
