// CStuMsgAdd.cpp: 实现文件
//

#include "pch.h"
#include "StudentStatusSystem.h"
#include "CStuMsgAdd.h"
#include "afxdialogex.h"


// CStuMsgAdd 对话框

IMPLEMENT_DYNAMIC(CStuMsgAdd, CDialogEx)

CStuMsgAdd::CStuMsgAdd(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_ADD, pParent)
	, m_number(_T(""))
	, m_name(_T(""))
	, m_sex(_T(""))
	, m_acadamy(_T(""))
	, m_major(_T(""))
	, m_grade(_T(""))
{

}

CStuMsgAdd::~CStuMsgAdd()
{
}

void CStuMsgAdd::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_number);
	DDX_Text(pDX, IDC_EDIT2, m_name);
	DDX_Text(pDX, IDC_EDIT3, m_sex);
	DDX_Text(pDX, IDC_EDIT4, m_acadamy);
	DDX_Text(pDX, IDC_EDIT5, m_major);
	DDX_Text(pDX, IDC_EDIT6, m_grade);
}


BEGIN_MESSAGE_MAP(CStuMsgAdd, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CStuMsgAdd::OnBnClickedButton1)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CStuMsgAdd 消息处理程序


void CStuMsgAdd::OnBnClickedButton1()					//确定按钮
{
	// TODO: 在此添加控件通知处理程序代码

	UpdateData(TRUE);						//获取编辑框数据
	EndDialog(0);							//退出
}


void CStuMsgAdd::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	flag = 0;
	CDialogEx::OnClose();
}
