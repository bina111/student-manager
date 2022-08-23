#pragma once



// CStuManger 窗体视图

class CStuManger : public CFormView
{
	DECLARE_DYNCREATE(CStuManger)

protected:
	CStuManger();           // 动态创建所使用的受保护的构造函数
	virtual ~CStuManger();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_STUMANGER };
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
	// 这是一个学生信息列表
	afx_msg void OnBnClickedButton1();
	virtual void OnInitialUpdate();
	CListCtrl m_List;
	afx_msg void OnBnClickedButton7();
	CString m_num;
	CString m_select;
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	CString m_number;
	afx_msg void OnBnClickedButton5();
};


