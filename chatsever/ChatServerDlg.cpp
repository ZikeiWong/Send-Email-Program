// ChatServerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ChatServer.h"
#include "ChatServerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CChatServerDlg �Ի���




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


// CChatServerDlg ��Ϣ�������

BOOL CChatServerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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


	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
GetDlgItem(IDC_PORT)->SetWindowText("5000"); 
GetDlgItem(IDC_DISCONNECT)->EnableWindow(FALSE); 
GetDlgItem(IDC_INPUT)->EnableWindow(FALSE); 
GetDlgItem(IDC_SEND)->EnableWindow(FALSE);
	aaa=0;

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CChatServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
//
HCURSOR CChatServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CChatServerDlg::OnBnClickedStart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	str=m_tm.Format("%X "); str+="��������!"; 
	m_list.AddString(str); 
	UpdateData(FALSE);
}

void CChatServerDlg::OnBnClickedDisconnect()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	(*m_server).Close(); 
	delete m_server; 
	delete m_chat; 
	CString str; 
	m_tm=CTime::GetCurrentTime(); 
	str=m_tm.Format("%X"); 
	str+=" �����ж�!"; 
	m_list.AddString(str); 
	UpdateData(FALSE); 
	GetDlgItem(IDC_START)->EnableWindow(TRUE); 
	GetDlgItem(IDC_INPUT)->EnableWindow(FALSE);
	GetDlgItem(IDC_SEND)->EnableWindow(FALSE); 
	GetDlgItem(IDC_DISCONNECT)->EnableWindow(FALSE);
}

void CChatServerDlg::OnBnClickedSend()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_input.GetWindowText(buff,200); 
	(*m_chat).Send(buff,200); 
	CString temp1=" �ң�"; 
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	aaa=(!aaa);
}




void CChatServerDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_list.ResetContent();
	
   
	
}
