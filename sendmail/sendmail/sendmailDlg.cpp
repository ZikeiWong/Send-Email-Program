
// sendmailDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "sendmail.h"
#include "sendmailDlg.h"
#include "afxdialogex.h"
CFont newFont
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CsendmailDlg 对话框

;CsendmailDlg::CsendmailDlg(CWnd* pParent /*=NULL*/): CDialogEx(CsendmailDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CsendmailDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CsendmailDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON3, &CsendmailDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON2, &CsendmailDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CsendmailDlg::OnBnClickedButton1)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CsendmailDlg 消息处理程序

BOOL CsendmailDlg::OnInitDialog()
{
	
    CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	GetDlgItem(IDC_BUTTON3)->EnableWindow(FALSE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CsendmailDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
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
		 CPaintDC   dc(this);  
         CRect   rect;  
         GetClientRect(&rect);    //获取对话框长宽      
         CDC   dcBmp;             //定义并创建一个内存设备环境
         dcBmp.CreateCompatibleDC(&dc);             //创建兼容性DC
         CBitmap   bmpBackground;   
         bmpBackground.LoadBitmap(IDB_BITMAP_BACKGROUND);    //载入资源中图片
         BITMAP   m_bitmap;                         //图片变量               
         bmpBackground.GetBitmap(&m_bitmap);       //将图片载入位图中
         //将位图选入临时内存设备环境
         CBitmap  *pbmpOld=dcBmp.SelectObject(&bmpBackground);
         //调用函数显示图片StretchBlt显示形状可变
         dc.StretchBlt(0,0,rect.Width(),rect.Height(),&dcBmp,0,0,m_bitmap.bmWidth,m_bitmap.bmHeight,SRCCOPY);    
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CsendmailDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

static const char base64Char[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

class SmtpMail
{private:
      char SmtpSrvName[32];
      char Port[7];
      char UserName[32];
      char Password[16];
      char From[32];
      char To[32];
      char Subject[32];
      char Msg[64];
      void Base64(unsigned char *chasc,unsigned char *chuue); 
      int Talk(SOCKET sockid, const char *OkCode, char *pSend);
   public:
      SmtpMail(const char* s,const char* p,const char* u,const char* w,
                 const char* f,const char* t,const char* j,const char* m)
      {   strcpy(SmtpSrvName,s);
          strcpy(Port,p);
          strcpy(UserName,u);
          strcpy(Password,w);
          strcpy(From,f);
          strcpy(To,t);
          strcpy(Subject,j);
          strcpy(Msg,m);	}
      int SendMail();
};
//---------------------------------------------------------------------
int SmtpMail::SendMail()
{     const int buflen = 256;
      char buf[buflen];
      int i,userlen,passlen;
      //(1)初始化网络环境
      WSADATA wsadata;
      if (WSAStartup(MAKEWORD(2,2),&wsadata) != 0)
      {
            printf("WSAStartup() error : %d\n", GetLastError());
            return 1;
      }
      //(2)创建套接字
      SOCKET sockid;
      if ((sockid = socket(AF_INET,SOCK_STREAM,0)) == INVALID_SOCKET)
      {
             printf("socket() error : %d\n", GetLastError());
             WSACleanup();
             return 1;
      }
      //(3)得到SMTP服务器IP
      struct hostent *phostent = gethostbyname(SmtpSrvName);
      struct sockaddr_in addr;
      CopyMemory(&addr.sin_addr.S_un.S_addr,
              phostent->h_addr_list[0],
              sizeof(addr.sin_addr.S_un.S_addr));
      struct in_addr srvaddr;
      CopyMemory(&srvaddr,&addr.sin_addr.S_un.S_addr,sizeof(struct in_addr));
      printf("Smtp server name is %s\n", SmtpSrvName);
      printf("Smtp server ip is %s\n", inet_ntoa(srvaddr));
      addr.sin_family = AF_INET;
      addr.sin_port = htons(atoi(Port));
      ZeroMemory(&addr.sin_zero, 8);
      //(4)连接服务器
      if (connect(sockid, (struct sockaddr *)&addr, sizeof(struct sockaddr_in)) == SOCKET_ERROR)
      { 
         printf("connect() error : %d\n", GetLastError());
          goto STOP;
      }
	  //(5)按照SMTP收发信息
      if (Talk(sockid, "220", "HELO asdf"))
      {        goto STOP;
      }
      if (Talk(sockid, "250", "AUTH LOGIN"))
      {        goto STOP;
      }
      ZeroMemory(buf, buflen);
      userlen = lstrlen(UserName);
      passlen = lstrlen(Password);
      for(i = 0; i < (userlen%3?userlen/3+1:userlen/3); i++)
      { Base64((unsigned char * )(UserName + i * 3),(unsigned char * )( buf + i * 4));
      }
      if (Talk(sockid, "334", buf))
      {     goto STOP;
      }
      ZeroMemory(buf, buflen);
      for(i = 0; i < (passlen%3?passlen/3+1:passlen/3); i++)
      { Base64((unsigned char *)(Password + i * 3),(unsigned char * ) (buf + i * 4));
      }
      if (Talk(sockid, "334", buf))
      {   goto STOP;
      }
      ZeroMemory(buf, buflen);
      wsprintf(buf, "MAIL FROM:<%s>", From);
      if (Talk(sockid, "235", buf))
      {      goto STOP;
      }
      ZeroMemory(buf, buflen);
      wsprintf(buf, "RCPT TO:<%s>", To);
      if (Talk(sockid, "250", buf))
      {        goto STOP;
      }
      if (Talk(sockid, "250", "DATA"))
      {     goto STOP;
      }
      ZeroMemory(buf, buflen);
      wsprintf(buf, "TO: %s\r\nFROM: %s\r\nSUBJECT: %s\r\n%s\r\n\r\n.",
                             To,From,Subject,Msg);
      if (Talk(sockid, "354", buf))
      {      goto STOP;
      }
      if (Talk(sockid, "250", "QUIT"))
      {      goto STOP;
      }
      if (Talk(sockid, "221", ""))
      {      goto STOP;
      }
      else
      {     closesocket(sockid);
            WSACleanup();
            return 0;
      }
STOP://(6)关闭socket，释放网络资源
      closesocket(sockid);
      WSACleanup();
      return 1;
}
//---------------------------------------------------------------------
int SmtpMail::Talk(SOCKET sockid, const char *OkCode, char *pSend)
{     const int buflen = 256;
      char buf[buflen];
      ZeroMemory(buf, buflen);
      //接收返回信息
      if (recv(sockid, buf, buflen, 0) == SOCKET_ERROR)
      {      
             printf("recv() error : %d\n", GetLastError());
             return 1;
      }
	  else
			printf("%s\n", buf);
      if (strstr(buf, OkCode) == NULL)
      {
              printf("Error: recv code != %s\n", OkCode);
      }
      //发送命令
      if (lstrlen(pSend))
      {       ZeroMemory(buf, buflen);
              wsprintf(buf, "%s\r\n", pSend);
              if (send(sockid, buf, lstrlen(buf), 0) == SOCKET_ERROR)
              {
                     printf("send() error : %d\n", GetLastError());
                     return 1;
              }
      }
      return 0;
}
//Base64编码，chasc：未编码的二进制代码，chuue：编码过的Base64代码
void SmtpMail::Base64(unsigned char *chasc,unsigned char *chuue)
{
	unsigned origLength = lstrlen((char *)chasc);

	unsigned char const* orig = (unsigned char const*)chasc; // in case any input bytes have the MSB set  

	unsigned const numOrig24BitValues = origLength / 3;
	bool havePadding = origLength > numOrig24BitValues * 3;
	bool havePadding2 = origLength == numOrig24BitValues * 3 + 2;
	unsigned const numResultBytes = 4 * (numOrig24BitValues + havePadding);
	char* result = new char[numResultBytes + 3]; // allow for trailing '/0'  

	// Map each full group of 3 input bytes into 4 output base-64 characters:  
	unsigned i;
	for (i = 0; i < numOrig24BitValues; ++i)
	{
		chuue[4 * i + 0] = base64Char[(orig[3 * i] >> 2) & 0x3F];
		chuue[4 * i + 1] = base64Char[(((orig[3 * i] & 0x3) << 4) | (orig[3 * i + 1] >> 4)) & 0x3F];
		chuue[4 * i + 2] = base64Char[((orig[3 * i + 1] << 2) | (orig[3 * i + 2] >> 6)) & 0x3F];
		chuue[4 * i + 3] = base64Char[orig[3 * i + 2] & 0x3F];
	}

	// Now, take padding into account.  (Note: i == numOrig24BitValues)  
	if (havePadding)
	{
		chuue[4 * i + 0] = base64Char[(orig[3 * i] >> 2) & 0x3F];
		if (havePadding2)
		{
			chuue[4 * i + 1] = base64Char[(((orig[3 * i] & 0x3) << 4) | (orig[3 * i + 1] >> 4)) & 0x3F];
			chuue[4 * i + 2] = base64Char[(orig[3 * i + 1] << 2) & 0x3F];
		}
		else
		{
			chuue[4 * i + 1] = base64Char[((orig[3 * i] & 0x3) << 4) & 0x3F];
			chuue[4 * i + 2] = '=';
		}
		chuue[4 * i + 3] = '=';
	}

	chuue[numResultBytes] = '\0';
}

CString s, p, u, w, f, t, j, m;

void CsendmailDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_EDIT1)->GetWindowText(u);
	GetDlgItem(IDC_EDIT2)->GetWindowText(w);
	GetDlgItem(IDC_EDIT3)->GetWindowText(f);
	GetDlgItem(IDC_EDIT4)->GetWindowText(t);
	GetDlgItem(IDC_EDIT5)->GetWindowText(j);
	GetDlgItem(IDC_EDIT6)->GetWindowText(m);
	SmtpMail mail(s,p, u, w,f, t, j, m);
	//SmtpMail mail("smtp.163.com", "25", "abc123", "123456", "abc123@163.com", "123456789@qq.com", "hello,周毅", "来信收到，谢谢！");
	mail.SendMail();
}


void CsendmailDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_BUTTON3)->EnableWindow(TRUE);
	set.DoModal();
	s = set.m_severadd;//得到服务器地址
	p = set.m_port;//得到端口
}


void CsendmailDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	tell.DoModal();

}


HBRUSH CsendmailDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if((pWnd->GetDlgCtrlID() == IDC_STATIC))
 {
  pDC->SetTextColor(RGB(0,0,0));//设置静态文本框字体颜色
  pDC->SetBkMode(TRANSPARENT);//设置为透明
   CFont font;
        font.CreatePointFont(90,"黑体");
         pDC->SelectObject(&font);//设置字体   
  return HBRUSH(GetStockObject(HOLLOW_BRUSH));//设置透明这句话不能掉
 }
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}
