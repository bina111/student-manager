// CAddScore.cpp: 实现文件
//

#include "pch.h"
#include "StudentStatusSystem.h"
#include "CAddScore.h"
#include "afxdialogex.h"


// CAddScore 对话框

IMPLEMENT_DYNAMIC(CAddScore, CDialogEx)

CAddScore::CAddScore(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_ADDSCORE, pParent)
	, m_number(_T(""))
	, m_name(_T(""))
	, m_GPA(_T(""))
	, m_gradeRanked(_T(""))
{

}

CAddScore::~CAddScore()
{
}

void CAddScore::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_number);
	DDX_Text(pDX, IDC_EDIT2, m_name);
	DDX_Text(pDX, IDC_EDIT3, m_GPA);
	DDX_Text(pDX, IDC_EDIT4, m_gradeRanked);
}


BEGIN_MESSAGE_MAP(CAddScore, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CAddScore::OnBnClickedButton1)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CAddScore 消息处理程序


void CAddScore::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

	UpdateData(TRUE);						//获取编辑框数据
	EndDialog(0);							//退出
}


void CAddScore::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	flag = 0;
	CDialogEx::OnClose();
}
