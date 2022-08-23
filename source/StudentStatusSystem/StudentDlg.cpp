// StudentDlg.cpp: 实现文件
//

#include "pch.h"
#include "StudentStatusSystem.h"
#include "StudentDlg.h"
#include "afxdialogex.h"
#include"CInfoFile.h"


// StudentDlg 对话框

IMPLEMENT_DYNAMIC(StudentDlg, CDialogEx)

StudentDlg::StudentDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_STUDENT, pParent)
	, m_number(_T(""))
	, m_name(_T(""))
	, m_sex(_T(""))
	, m_academy(_T(""))
	, m_major(_T(""))
	, m_gpa(_T(""))
	, m_gradeRanked(_T(""))
	, m_grade(_T(""))
	, m_newpwd(_T(""))
	, m_surepwd(_T(""))
{
}

StudentDlg::~StudentDlg()
{
}

void StudentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_number);
	DDX_Text(pDX, IDC_EDIT2, m_name);
	DDX_Text(pDX, IDC_EDIT3, m_sex);
	DDX_Text(pDX, IDC_EDIT4, m_academy);
	DDX_Text(pDX, IDC_EDIT5, m_major);
	DDX_Text(pDX, IDC_EDIT7, m_gpa);
	DDX_Text(pDX, IDC_EDIT8, m_gradeRanked);
	DDX_Text(pDX, IDC_EDIT6, m_grade);
	DDX_Text(pDX, IDC_EDIT9, m_newpwd);
	DDX_Text(pDX, IDC_EDIT10, m_surepwd);
	DDX_Control(pDX, IDC_STATIC_STU, m_Static);
}


BEGIN_MESSAGE_MAP(StudentDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON3, &StudentDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON_SURE, &StudentDlg::OnBnClickedButtonSure)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &StudentDlg::OnBnClickedButtonCancel)
END_MESSAGE_MAP()


// StudentDlg 消息处理程序


void StudentDlg::OnBnClickedButton3()					//退出系统按钮
{
	exit(0);
	// TODO: 在此添加控件通知处理程序代码
}


BOOL StudentDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	
	//设置静态文本字体大小
	m_editFont.CreatePointFont(180, _T("宋体"));
	m_Static.SetFont(&m_editFont);

	//创建图标
	HICON icon;
	//加载图标
	icon = AfxGetApp()->LoadIcon(IDI_ICON_STUDENT);
	SetIcon(icon, true);
	SetIcon(icon, false);

	CInfoFile file;
	CString number;
	file.ReadStu(number);
	file.ReadStudMsg();
	for (list<stumsg>::iterator it = file.ls2.begin(); it != file.ls2.end(); it++)
	{
		if ((CString)it->number.c_str() == number)	//用户名一致
		{
			SetDlgItemText(IDC_EDIT1, (CString)it->number.c_str());
			SetDlgItemText(IDC_EDIT2, (CString)it->name.c_str());
			SetDlgItemText(IDC_EDIT3, (CString)it->sex.c_str());
			SetDlgItemText(IDC_EDIT4, (CString)it->academy.c_str());
			SetDlgItemText(IDC_EDIT5, (CString)it->major.c_str());
			SetDlgItemText(IDC_EDIT6, (CString)it->grade.c_str());
			break;
		}
	}

	file.ReadScore();
	for (list<stuscore>::iterator it = file.ls4.begin(); it != file.ls4.end(); it++)
	{
		if ((CString)it->number.c_str() == number)	//用户名一致
		{
			SetDlgItemText(IDC_EDIT7, (CString)it->GPA.c_str());
			SetDlgItemText(IDC_EDIT8, (CString)it->gradeRanked.c_str());
		}
	}
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void StudentDlg::OnBnClickedButtonSure()				//确定按钮
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE); //拿到最新值

	if (m_newpwd.IsEmpty() || m_surepwd.IsEmpty())
	{
		MessageBox(_T("输入内容不能为空！"));
		return;
	}

	//新密码和确定密码要一致
	if (m_newpwd != m_surepwd)
	{
		MessageBox(_T("新密码与确定密码要一致！"));
		return;
	}
	
	CInfoFile file;
	CString number;
	file.ReadStu(number);
	file.ReadStuLogin();
	CStringA pwd;
	for (list<stulogin>::iterator it = file.ls1.begin(); it != file.ls1.end(); it++)
	{
		if ((CString)it->number.c_str() == number)	//用户名一致
		{
			if ((CString)it->pwd.c_str() == m_newpwd)
			{
				//新密码与旧密码不能一致
				MessageBox(_T("新密码与旧密码不能一致！"));
				return;
			}
			else
			{
				pwd = m_newpwd;
				file.WriteStuPwd(pwd.GetBuffer());
				MessageBox(_T("密码修改成功！"));
			}
			break;
		}
	}

	//清空内容
	m_newpwd.Empty();
	m_surepwd.Empty();
	UpdateData(FALSE);
			
}


void StudentDlg::OnBnClickedButtonCancel()					//取消按钮
{
	// TODO: 在此添加控件通知处理程序代码

	//清空内容
	m_newpwd.Empty();
	m_surepwd.Empty();
	UpdateData(FALSE);						//将数据更新到控件

}
