#pragma once


// CAddCourse 对话框

class CAddCourse : public CDialogEx
{
	DECLARE_DYNAMIC(CAddCourse)

public:
	CAddCourse(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CAddCourse();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ADDCS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CString m_courseTitle;
	CString m_teacher;
	CString m_college;
	CString m_courseCode;
	CString m_score;
	CString m_time;
	bool flag = 1;						//为即点了确定，为0即点击了上面的×
	afx_msg void OnClose();
};
