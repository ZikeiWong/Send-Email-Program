// SetServerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "sendmail.h"
#include "SetServerDlg.h"
#include "afxdialogex.h"


// CSetServerDlg 对话框

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


// CSetServerDlg 消息处理程序


void CSetServerDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_EDIT1)->GetWindowText(m_severadd);
	GetDlgItem(IDC_EDIT2)->GetWindowText(m_port);
	::SendMessage(this->m_hWnd, WM_CLOSE, 0, 0);
}


void CSetServerDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_EDIT1)->SetWindowText("");
	GetDlgItem(IDC_EDIT2)->SetWindowText("");
}


void CSetServerDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
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


HBRUSH CSetServerDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
