// CSystemDlg.cpp: 实现文件
//

#include "pch.h"
#include "StudentStatusSystem.h"
#include "CSystemDlg.h"
#include"CInfoFile.h"

// CSystemDlg

IMPLEMENT_DYNCREATE(CSystemDlg, CFormView)

CSystemDlg::CSystemDlg()
	: CFormView(IDD_DIALOG_SYSTEM)
	, m_user(_T(""))
	, m_name(_T(""))
	, m_newPwd(_T(""))
	, m_surePwd(_T(""))
	, m_user1(_T(""))
	, m_Inpwd(_T(""))
	, m_user2(_T(""))
	, m_user3(_T(""))
	, m_Inuser(_T(""))
{

}

CSystemDlg::~CSystemDlg()
{
}

void CSystemDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_user);
	DDX_Text(pDX, IDC_EDIT2, m_name);
	DDX_Text(pDX, IDC_EDIT3, m_newPwd);
	DDX_Text(pDX, IDC_EDIT5, m_surePwd);
	DDX_Text(pDX, IDC_EDIT4, m_user1);
	DDX_Text(pDX, IDC_EDIT8, m_Inpwd);
	DDX_Text(pDX, IDC_EDIT9, m_user2);
	DDX_Text(pDX, IDC_EDIT11, m_user3);
	DDX_Control(pDX, IDC_STATIC_SYS, m_Static);
	DDX_Text(pDX, IDC_EDIT10, m_Inuser);
}

BEGIN_MESSAGE_MAP(CSystemDlg, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CSystemDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CSystemDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CSystemDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON6, &CSystemDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON4, &CSystemDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CSystemDlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// CSystemDlg 诊断

#ifdef _DEBUG
void CSystemDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CSystemDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CSystemDlg 消息处理程序


void CSystemDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	//初始化
	m_user = TEXT("管理员");

	CInfoFile file;
	CString name, pwd;
	file.ReadLogin(name, pwd);

	m_name = name;

	//设置静态文本字体大小
	m_editFont.CreatePointFont(180, _T("宋体"));
	m_Static.SetFont(&m_editFont);

	UpdateData(FALSE);

}


void CSystemDlg::OnBnClickedButton1()				//修改密码里面的确定按钮
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE); //拿到最新值

	if (m_newPwd.IsEmpty() || m_surePwd.IsEmpty())
	{
		MessageBox(TEXT("输入内容不能为空！"));
		return;
	}

	//新密码和确定密码要一致
	if (m_newPwd != m_surePwd)
	{
		MessageBox(TEXT("新密码与确定密码要一致！"));
		return;
	}

	//新密码与旧密码不能一致
	CInfoFile file;
	CString name, pwd;
	file.ReadLogin(name, pwd);
	if (pwd == m_newPwd)
	{
		MessageBox(TEXT("新密码与旧密码不能一致！"));
		return;
	}

	//CString 转  char *
	CStringA tmp;
	CStringA tmp2;
	tmp = name;
	tmp2 = m_newPwd;
	file.WritePwd(tmp.GetBuffer(), tmp2.GetBuffer());
	MessageBox(TEXT("修改成功"));

	//清空内容
	m_newPwd.Empty();
	m_surePwd.Empty();
	UpdateData(FALSE);

}




void CSystemDlg::OnBnClickedButton2()			//修改密码里面的取消按钮，用于清空编辑框内容
{
	// TODO: 在此添加控件通知处理程序代码

	//清空内容
	m_newPwd.Empty();
	m_surePwd.Empty();
	UpdateData(FALSE);

}




void CSystemDlg::OnBnClickedButton3()			//添加学生用户
{
	// TODO: 在此添加控件通知处理程序代码

	//拿到最新数据
	UpdateData(TRUE);

	if (m_user1.IsEmpty() || m_Inpwd.IsEmpty())
	{
		MessageBox(_T("输入不能为空！"));
		m_user1.Empty();
		m_Inpwd.Empty();
		UpdateData(FALSE);
		return;
	}
	stulogin temp;
	CStringA number, pwd;
	number = m_user1;
	pwd = m_Inpwd;
	temp.number = number;
	temp.pwd = pwd;
	CInfoFile file;
	file.ReadStuLogin();				//读取学生登录数据
	for (list<stulogin>::iterator it = file.ls1.begin(); it != file.ls1.end(); it++)
	{
		if ((CString)it->number.c_str() == m_user1)	//寻找用户名一致
		{
			MessageBox(_T("用户名已存在！"));
			m_user1.Empty();
			m_Inpwd.Empty();
			UpdateData(FALSE);
			return;
		}
	}
	file.ls1.push_back(temp);
	file.WriteStuPwdd();
	MessageBox(_T("添加成功！"));
	m_user1.Empty();
	m_Inpwd.Empty();
	UpdateData(FALSE);

}


void CSystemDlg::OnBnClickedButton6()				//退出系统
{
	// TODO: 在此添加控件通知处理程序代码
	exit(0);
}


void CSystemDlg::OnBnClickedButton4()				//删除学生账号
{
	// TODO: 在此添加控件通知处理程序代码
	//拿到最新数据
	UpdateData(TRUE);

	CInfoFile file;
	bool flag = 0;							//为0删除失败，为1删除成功
	file.ReadStuLogin();
	for (list<stulogin>::iterator it = file.ls1.begin(); it != file.ls1.end(); it++)
	{
		if ((CString)it->number.c_str() == m_user2)	//用户名一致
		{
			file.ls1.erase(it);						//删除结点
			flag = 1;
			break;
		}
	}
	if (flag)
	{
		file.WriteStuPwdd();
		MessageBox(_T("删除成功！"));
	}
	else
		MessageBox(_T("不存在该用户！"));
	m_user2.Empty();								//清空编辑框
	UpdateData(FALSE);

}


void CSystemDlg::OnBnClickedButton5()					//更改学生用户名
{
	// TODO: 在此添加控件通知处理程序代码

	//拿到最新数据
	UpdateData(TRUE);

	if (m_user3 == m_Inuser)
	{
		MessageBox(_T("原用户名与更改后的一致！"));
		m_user3.Empty();
		m_Inuser.Empty();
		UpdateData(FALSE);
		return;
	}

	bool flag = 0;					//为0要更改用户不存在，反之则反
	CInfoFile file;
	file.ReadStuLogin();
	for (list<stulogin>::iterator it = file.ls1.begin(); it != file.ls1.end(); it++)
	{
		if ((CString)it->number.c_str() == m_user3)	//用户名一致
		{
			CStringA number;
			number = m_Inuser;
			it->number = number;
			flag = 1;
			break;
		}
	}
	if (flag == 1)
	{
		file.WriteStuPwdd();				//将更改后的信息重新写入文件
		MessageBox(_T("更改成功！"));
	}
	else
		MessageBox(_T("要更改的用户名不存在！"));
	
	m_user3.Empty();
	m_Inuser.Empty();
	UpdateData(FALSE);

}
