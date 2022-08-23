#pragma once


// CStuMsgAdd 对话框

class CStuMsgAdd : public CDialogEx
{
	DECLARE_DYNAMIC(CStuMsgAdd)

public:
	CStuMsgAdd(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CStuMsgAdd();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ADD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_number;
	CString m_name;
	CString m_sex;
	CString m_acadamy;
	CString m_major;
	CString m_grade;
	bool flag = 1;						//为即点了确定，为0即点击了上面的×
	afx_msg void OnBnClickedButton1();
	afx_msg void OnClose();
};
