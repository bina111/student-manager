// CAddCourse.cpp: 实现文件
//

#include "pch.h"
#include "StudentStatusSystem.h"
#include "CAddCourse.h"
#include "afxdialogex.h"


// CAddCourse 对话框

IMPLEMENT_DYNAMIC(CAddCourse, CDialogEx)

CAddCourse::CAddCourse(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_ADDCS, pParent)
	, m_courseTitle(_T(""))
	, m_teacher(_T(""))
	, m_college(_T(""))
	, m_courseCode(_T(""))
	, m_score(_T(""))
	, m_time(_T(""))
{

}

CAddCourse::~CAddCourse()
{
}

void CAddCourse::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_courseTitle);
	DDX_Text(pDX, IDC_EDIT2, m_teacher);
	DDX_Text(pDX, IDC_EDIT3, m_college);
	DDX_Text(pDX, IDC_EDIT4, m_courseCode);
	DDX_Text(pDX, IDC_EDIT5, m_score);
	DDX_Text(pDX, IDC_EDIT6, m_time);
}


BEGIN_MESSAGE_MAP(CAddCourse, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CAddCourse::OnBnClickedButton1)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CAddCourse 消息处理程序


void CAddCourse::OnBnClickedButton1()						//确定按钮
{
	// TODO: 在此添加控件通知处理程序代码

	UpdateData(TRUE);						//获取编辑框数据
	EndDialog(0);							//退出
}


void CAddCourse::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	flag = 0;
	CDialogEx::OnClose();
}
