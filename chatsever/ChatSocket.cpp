// ChatSocket.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ChatServer.h"
#include "ChatSocket.h"
#include "ChatServerDlg.h"


// CChatSocket

CChatSocket::CChatSocket()
{
}

CChatSocket::~CChatSocket()
{
}


// CChatSocket ��Ա����

void CChatSocket::OnReceive(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
CChatServerDlg* dlg=(CChatServerDlg*)AfxGetApp()->GetMainWnd(); 
	//��ȡʱ�� 
	dlg->m_tm=CTime::GetCurrentTime(); 
	CString str; 
	str=dlg->m_tm.Format("%X "); 
	//�������� 
	Receive(dlg->buff,200,0); 
	CString temp1=dlg->buff; 
	//���룬�յ������� 
	int index=0; 
	for (int i=0;i<3;i++) 
	{ 
		index=temp1.Find('#',index); 
		index++; 
	} 
	int sum=temp1.GetLength(); 
	int count=sum-index; 
	CString message=temp1.Mid(index,count); 
	CString temp2=" �ͻ��� : "; 
	temp2=str+temp2; 
	temp2+=message; 

	CString a = "time";
	CString b = "on";

	if (message != a && message != b)
	{
		dlg->m_list.AddString(temp2);
	}
	
	CAsyncSocket::OnReceive(nErrorCode);
	_sleep(1 * 1000);
	
	char *_message = message.GetBuffer(0);
	char *if_hello = strstr(_message, "hello");
	
	if (message == a)
	{
		Send(str, 200);
	}

	if (message == b)
	{(dlg->aaa)=(!(dlg->aaa));}

	if((dlg->aaa)==1)
	{
	
	
	if (if_hello != NULL)
	{
		Send("hey! ���Զ��ظ���", 200);
	}
	else if (message == b)
	{
		
	}
	else
	{
		Send(" hey~���Զ��ظ���", 200);
	}
	}
	
	
}
