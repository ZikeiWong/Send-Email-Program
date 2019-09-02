// ChatServerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ChatServer.h"
#include "ChatServerDlg.h"

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


// CChatServerDlg 对话框




CChatServerDlg::CChatServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChatServerDlg::IDD, pParent)
	, aaa(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChatServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_INPUT, m_input);
}

BEGIN_MESSAGE_MAP(CChatServerDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_START, &CChatServerDlg::OnBnClickedStart)
	ON_BN_CLICKED(IDC_DISCONNECT, &CChatServerDlg::OnBnClickedDisconnect)
	ON_BN_CLICKED(IDC_SEND, &CChatServerDlg::OnBnClickedSend)
	ON_BN_CLICKED(IDC_BUTTON1, &CChatServerDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CChatServerDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CChatServerDlg 消息处理程序

BOOL CChatServerDlg::OnInitDialog()
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
GetDlgItem(IDC_PORT)->SetWindowText("5000"); 
GetDlgItem(IDC_DISCONNECT)->EnableWindow(FALSE); 
GetDlgItem(IDC_INPUT)->EnableWindow(FALSE); 
GetDlgItem(IDC_SEND)->EnableWindow(FALSE);
	aaa=0;

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CChatServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CChatServerDlg::OnPaint()
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
HCURSOR CChatServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CChatServerDlg::OnBnClickedStart()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_START)->EnableWindow(FALSE); 
	CString temp; 
	GetDlgItem(IDC_PORT)->GetWindowText(temp); 
	UINT port=atoi(temp.GetBuffer() ); 
	//1st Create 
	m_server=new CServerSocket; 
	if ((*m_server).Create(port)==0) 
	{ 
		static int code=(*m_server).GetLastError(); 
		CString err; err.Format("%d",code); 
		CString error="Create Error Code= "; 
		error+=err;
		MessageBox(error); 
		return; 
	} 
	
	//2nd Listen 
	if ((*m_server).Listen()==0) 
	{ 
		static int code=(*m_server).GetLastError(); 
		CString err; 
		err.Format("%d",code); 
		CString error="Create Error Code= "; 
		error+=err; 
		MessageBox(error); 
		return; 
	} 
	
	GetDlgItem(IDC_START)->EnableWindow(FALSE); 
	GetDlgItem(IDC_DISCONNECT)->EnableWindow(TRUE); 
	GetDlgItem(IDC_INPUT)->EnableWindow(TRUE); 
	GetDlgItem(IDC_SEND)->EnableWindow(TRUE); 
	CString str; m_tm=CTime::GetCurrentTime(); 
	str=m_tm.Format("%X "); str+="建立服务!"; 
	m_list.AddString(str); 
	UpdateData(FALSE);
}

void CChatServerDlg::OnBnClickedDisconnect()
{
	// TODO: 在此添加控件通知处理程序代码
	(*m_server).Close(); 
	delete m_server; 
	delete m_chat; 
	CString str; 
	m_tm=CTime::GetCurrentTime(); 
	str=m_tm.Format("%X"); 
	str+=" 服务中断!"; 
	m_list.AddString(str); 
	UpdateData(FALSE); 
	GetDlgItem(IDC_START)->EnableWindow(TRUE); 
	GetDlgItem(IDC_INPUT)->EnableWindow(FALSE);
	GetDlgItem(IDC_SEND)->EnableWindow(FALSE); 
	GetDlgItem(IDC_DISCONNECT)->EnableWindow(FALSE);
}

void CChatServerDlg::OnBnClickedSend()
{
	// TODO: 在此添加控件通知处理程序代码
	m_input.GetWindowText(buff,200); 
	(*m_chat).Send(buff,200); 
	CString temp1=" 我："; 
	CString temp2=buff; 
	CString str; 
	m_tm=CTime::GetCurrentTime(); 
	str=m_tm.Format("%X"); 
	temp1=str+temp1; 
	temp1+=temp2; 
	CChatServerDlg* dlg=(CChatServerDlg*)AfxGetApp()->GetMainWnd(); 
	m_list.AddString(temp1); 
	UpdateData(FALSE); 
	m_input.SetWindowText("");
}


void CChatServerDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	aaa=(!aaa);
}




void CChatServerDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_list.ResetContent();
	
   
	
}
