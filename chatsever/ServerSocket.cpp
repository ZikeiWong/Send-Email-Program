// ServerSocket.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ChatServer.h"
#include "ServerSocket.h"
#include "ChatServerDlg.h"

// CServerSocket

CServerSocket::CServerSocket()
{
}

CServerSocket::~CServerSocket()
{
}


// CServerSocket ��Ա����

void CServerSocket::OnAccept(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
CChatServerDlg* dlg=(CChatServerDlg*)AfxGetApp()->GetMainWnd(); 
dlg->m_chat=new CChatSocket; 
Accept(*(dlg->m_chat)); 
CString str; 
dlg->m_tm=CTime::GetCurrentTime(); 
str=dlg->m_tm.Format("%X "); 
str+="�ͻ������ӳɹ�!"; 
dlg->m_list.AddString(str); 
dlg->m_list.UpdateData(FALSE); 

	CAsyncSocket::OnAccept(nErrorCode);
}
