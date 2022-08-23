#pragma once


// StudentDlg 对话框

class StudentDlg : public CDialogEx
{
	DECLARE_DYNAMIC(StudentDlg)

public:
	StudentDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~StudentDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_STUDENT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton3();
	CString m_number;
	CString m_name;
	CString m_sex;
	CString m_academy;
	CString m_major;
	CString m_gpa;
	CString m_gradeRanked;
	CString m_grade;
	virtual BOOL OnInitDialog();
	CString m_newpwd;
	CString m_surepwd;
	afx_msg void OnBnClickedButtonSure();
	afx_msg void OnBnClickedButtonCancel();
	CStatic m_Static;
	CFont m_editFont;		//用于调整字体
};
