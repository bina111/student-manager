// LoginDlg.cpp: 实现文件
//

#include "pch.h"
#include "StudentStatusSystem.h"
#include "LoginDlg.h"
#include "afxdialogex.h"
#include"CInfoFile.h"


// LoginDlg 对话框

IMPLEMENT_DYNAMIC(LoginDlg, CDialogEx)

LoginDlg::LoginDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(DIALOG_LOGIN, pParent)
	, m_user(_T(""))
	, m_pwd(_T(""))
{
	flag = 1;
}

LoginDlg::~LoginDlg()
{
}

void LoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_user);
	DDX_Text(pDX, IDC_EDIT2, m_pwd);
	DDX_Control(pDX, IDC_CHECK1, m_manger);
	DDX_Control(pDX, IDC_CHECK2, m_student);
	DDX_Control(pDX, IDC_STATIC_TITLE, m_Static);
}


BEGIN_MESSAGE_MAP(LoginDlg, CDialogEx)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_CANCEL, &LoginDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_LOGIN, &LoginDlg::OnBnClickedButtonLogin)
END_MESSAGE_MAP()


// LoginDlg 消息处理程序


void LoginDlg::OnClose()					//点击窗口的关闭符号时退出程序
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	exit(0);			//退出程序
}


void LoginDlg::OnBnClickedCancel()			//取消按钮的功能是退出程序
{
	// TODO: 在此添加控件通知处理程序代码
	exit(0);			//退出程序
}


void LoginDlg::OnBnClickedButtonLogin()						//登录按钮
{
	// TODO: 在此添加控件通知处理程序代码

	UpdateData(TRUE);										//获取编辑框的数据

	if (m_user.IsEmpty() || m_pwd.IsEmpty())				//若编辑框的数据为空则报警
	{
		MessageBox(_T("输入内容不能为空"));
		return;
	}

	if (m_manger.GetCheck() && m_student.GetCheck())		//两个复选框只能选一个
	{
		MessageBox(_T("管理员和学生只能选一个！"));
		return;
	}

	if (!m_manger.GetCheck() && !m_student.GetCheck())		//两个复选框必须选一个
	{
		MessageBox(_T("管理员和学生必须选一个！"));
		return;
	}

	//获取正确的值
	CInfoFile file;
	CString name, pwd;
	file.ReadLogin(name, pwd);								//读取管理员信息
	if (m_manger.GetCheck())
	{
		flag = 1;
		if (name == m_user) //用户名一致
		{
			if (pwd == m_pwd) //密码一致
			{
				//关闭当前对话框
				CDialog::OnCancel();
				return;
			}
			else
			{
				MessageBox(_T("密码有误"));
			}
		}
		else
		{
			MessageBox(_T("用户名有误"));
		}
	}
	else if (m_student.GetCheck())					
	{
		flag = 0;
		file.ReadStuLogin();						//读取学生登录信息
		for (list<stulogin>::iterator it = file.ls1.begin(); it != file.ls1.end(); it++)
		{
			if ((CString)it->number.c_str() == m_user)	//用户名一致
			{
				if ((CString)it->pwd.c_str() == m_pwd) //密码一致
				{
					//CString 转成char*
					CStringA number;
					number = m_user;
					file.WriteStu(number.GetBuffer());
					//关闭当前对话框
					CDialog::OnCancel();
					return;
				}
				else
				{
					MessageBox(_T("密码有误"));
					return;
				}
			}
		}
		MessageBox(_T("用户名有误"));
	}
	
}


BOOL LoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	
	
	//设置静态文本字体大小
	m_editFont.CreatePointFont(180, _T("宋体"));
	m_Static.SetFont(&m_editFont);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void LoginDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();				//将其注释掉使它按回车键后不进入
}
