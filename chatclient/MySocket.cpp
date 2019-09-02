#include "stdafx.h"
#include "ChatClient.h"
#include "ChatClientDlg.h"
#include "MySocket.h"


// CMySocket

CMySocket::CMySocket()
{
}

CMySocket::~CMySocket()
{
}


// CMySocket 成员函数

void CMySocket::OnConnect(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	CChatClientDlg* dlg=(CChatClientDlg*)AfxGetApp()->GetMainWnd(); 
	CString str; 
	dlg->m_tm=CTime::GetCurrentTime(); 
	str=dlg->m_tm.Format("%X "); 
	str+="与服务器连接成功！"; 
	dlg->m_list.AddString(str); 
 
	CAsyncSocket::OnConnect(nErrorCode);
}

void CMySocket::OnReceive(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	CChatClientDlg* dlg=(CChatClientDlg*)AfxGetApp()->GetMainWnd(); 
Receive(dlg->buff,200,0);
CString temp1=" server ："; 
CString temp2=dlg->buff; 
CString str; 
dlg->m_tm=CTime::GetCurrentTime(); 
str=dlg->m_tm.Format("%X"); 
temp1=str+temp1; 
temp1+=temp2; 
dlg->m_list.AddString(temp1); 
dlg->m_list.UpdateData(FALSE);

	CAsyncSocket::OnReceive(nErrorCode);
}
