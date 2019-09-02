// ChatSocket.cpp : 实现文件
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


// CChatSocket 成员函数

void CChatSocket::OnReceive(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
CChatServerDlg* dlg=(CChatServerDlg*)AfxGetApp()->GetMainWnd(); 
	//获取时间 
	dlg->m_tm=CTime::GetCurrentTime(); 
	CString str; 
	str=dlg->m_tm.Format("%X "); 
	//接收数据 
	Receive(dlg->buff,200,0); 
	CString temp1=dlg->buff; 
	//解码，收到的数据 
	int index=0; 
	for (int i=0;i<3;i++) 
	{ 
		index=temp1.Find('#',index); 
		index++; 
	} 
	int sum=temp1.GetLength(); 
	int count=sum-index; 
	CString message=temp1.Mid(index,count); 
	CString temp2=" 客户端 : "; 
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
		Send("hey! （自动回复）", 200);
	}
	else if (message == b)
	{
		
	}
	else
	{
		Send(" hey~（自动回复）", 200);
	}
	}
	
	
}
