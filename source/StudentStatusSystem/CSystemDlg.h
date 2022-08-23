#pragma once



// CSystemDlg 窗体视图

class CSystemDlg : public CFormView
{
	DECLARE_DYNCREATE(CSystemDlg)

protected:
	CSystemDlg();           // 动态创建所使用的受保护的构造函数
	virtual ~CSystemDlg();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SYSTEM };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_user;
	CString m_name;
	CString m_newPwd;
	CString m_surePwd;
	CString m_user1;
	CString m_Inpwd;
	CString m_user2;
	CString m_user3;
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();

private:
	CFont m_editFont;		//用于调整字体
public:
	CStatic m_Static;
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	CString m_Inuser;
};


