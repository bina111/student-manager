#pragma once


// LoginDlg 对话框

class LoginDlg : public CDialogEx
{
	DECLARE_DYNAMIC(LoginDlg)

public:
	LoginDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~LoginDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = DIALOG_LOGIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	afx_msg void OnBnClickedCancel();
	CString m_user;
	CString m_pwd;
	CButton m_manger;
	CButton m_student;
	afx_msg void OnBnClickedButtonLogin();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	bool flag;				//用于记录是点了学生还是管理员，0为学生，1为管理员
	CString stuname;		//记录是哪位学生登陆
	CFont m_editFont;		//用于调整字体
	CStatic m_Static;
};
