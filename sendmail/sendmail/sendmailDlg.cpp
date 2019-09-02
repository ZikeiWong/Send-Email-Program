
// sendmailDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "sendmail.h"
#include "sendmailDlg.h"
#include "afxdialogex.h"
CFont newFont
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CsendmailDlg �Ի���

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


// CsendmailDlg ��Ϣ�������

BOOL CsendmailDlg::OnInitDialog()
{
	
    CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	GetDlgItem(IDC_BUTTON3)->EnableWindow(FALSE);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CsendmailDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
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
		 CPaintDC   dc(this);  
         CRect   rect;  
         GetClientRect(&rect);    //��ȡ�Ի��򳤿�      
         CDC   dcBmp;             //���岢����һ���ڴ��豸����
         dcBmp.CreateCompatibleDC(&dc);             //����������DC
         CBitmap   bmpBackground;   
         bmpBackground.LoadBitmap(IDB_BITMAP_BACKGROUND);    //������Դ��ͼƬ
         BITMAP   m_bitmap;                         //ͼƬ����               
         bmpBackground.GetBitmap(&m_bitmap);       //��ͼƬ����λͼ��
         //��λͼѡ����ʱ�ڴ��豸����
         CBitmap  *pbmpOld=dcBmp.SelectObject(&bmpBackground);
         //���ú�����ʾͼƬStretchBlt��ʾ��״�ɱ�
         dc.StretchBlt(0,0,rect.Width(),rect.Height(),&dcBmp,0,0,m_bitmap.bmWidth,m_bitmap.bmHeight,SRCCOPY);    
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
      //(1)��ʼ�����绷��
      WSADATA wsadata;
      if (WSAStartup(MAKEWORD(2,2),&wsadata) != 0)
      {
            printf("WSAStartup() error : %d\n", GetLastError());
            return 1;
      }
      //(2)�����׽���
      SOCKET sockid;
      if ((sockid = socket(AF_INET,SOCK_STREAM,0)) == INVALID_SOCKET)
      {
             printf("socket() error : %d\n", GetLastError());
             WSACleanup();
             return 1;
      }
      //(3)�õ�SMTP������IP
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
      //(4)���ӷ�����
      if (connect(sockid, (struct sockaddr *)&addr, sizeof(struct sockaddr_in)) == SOCKET_ERROR)
      { 
         printf("connect() error : %d\n", GetLastError());
          goto STOP;
      }
	  //(5)����SMTP�շ���Ϣ
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
STOP://(6)�ر�socket���ͷ�������Դ
      closesocket(sockid);
      WSACleanup();
      return 1;
}
//---------------------------------------------------------------------
int SmtpMail::Talk(SOCKET sockid, const char *OkCode, char *pSend)
{     const int buflen = 256;
      char buf[buflen];
      ZeroMemory(buf, buflen);
      //���շ�����Ϣ
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
      //��������
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
//Base64���룬chasc��δ����Ķ����ƴ��룬chuue���������Base64����
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_EDIT1)->GetWindowText(u);
	GetDlgItem(IDC_EDIT2)->GetWindowText(w);
	GetDlgItem(IDC_EDIT3)->GetWindowText(f);
	GetDlgItem(IDC_EDIT4)->GetWindowText(t);
	GetDlgItem(IDC_EDIT5)->GetWindowText(j);
	GetDlgItem(IDC_EDIT6)->GetWindowText(m);
	SmtpMail mail(s,p, u, w,f, t, j, m);
	//SmtpMail mail("smtp.163.com", "25", "abc123", "123456", "abc123@163.com", "123456789@qq.com", "hello,����", "�����յ���лл��");
	mail.SendMail();
}


void CsendmailDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_BUTTON3)->EnableWindow(TRUE);
	set.DoModal();
	s = set.m_severadd;//�õ���������ַ
	p = set.m_port;//�õ��˿�
}


void CsendmailDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	tell.DoModal();

}


HBRUSH CsendmailDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	if((pWnd->GetDlgCtrlID() == IDC_STATIC))
 {
  pDC->SetTextColor(RGB(0,0,0));//���þ�̬�ı���������ɫ
  pDC->SetBkMode(TRANSPARENT);//����Ϊ͸��
   CFont font;
        font.CreatePointFont(90,"����");
         pDC->SelectObject(&font);//��������   
  return HBRUSH(GetStockObject(HOLLOW_BRUSH));//����͸����仰���ܵ�
 }
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}
