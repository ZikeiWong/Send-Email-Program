// SetServerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "sendmail.h"
#include "SetServerDlg.h"
#include "afxdialogex.h"


// CSetServerDlg �Ի���

IMPLEMENT_DYNAMIC(CSetServerDlg, CDialogEx)

CSetServerDlg::CSetServerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetServerDlg::IDD, pParent)
{

}

CSetServerDlg::~CSetServerDlg()
{
}

void CSetServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSetServerDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CSetServerDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CSetServerDlg::OnBnClickedButton2)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CSetServerDlg ��Ϣ�������


void CSetServerDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_EDIT1)->GetWindowText(m_severadd);
	GetDlgItem(IDC_EDIT2)->GetWindowText(m_port);
	::SendMessage(this->m_hWnd, WM_CLOSE, 0, 0);
}


void CSetServerDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_EDIT1)->SetWindowText("");
	GetDlgItem(IDC_EDIT2)->SetWindowText("");
}


void CSetServerDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
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


HBRUSH CSetServerDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
