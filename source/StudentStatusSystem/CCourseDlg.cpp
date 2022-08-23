// CCourseDlg.cpp: 实现文件
//

#include "pch.h"
#include "StudentStatusSystem.h"
#include "CCourseDlg.h"
#include"CInfoFile.h"
#include"CAddCourse.h"


// CCourseDlg

IMPLEMENT_DYNCREATE(CCourseDlg, CFormView)

CCourseDlg::CCourseDlg()
	: CFormView(IDD_DIALOG_COURSE)
	, m_display(_T(""))
	, m_coursecode(_T(""))
	, m_coursecode1(_T(""))
{

}

CCourseDlg::~CCourseDlg()
{
}

void CCourseDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_List);
	DDX_Text(pDX, IDC_EDIT3, m_display);
	DDX_Text(pDX, IDC_EDIT2, m_coursecode);
	DDX_Text(pDX, IDC_EDIT1, m_coursecode1);
}

BEGIN_MESSAGE_MAP(CCourseDlg, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CCourseDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CCourseDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON7, &CCourseDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON4, &CCourseDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON3, &CCourseDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON5, &CCourseDlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// CCourseDlg 诊断

#ifdef _DEBUG
void CCourseDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CCourseDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CCourseDlg 消息处理程序


void CCourseDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类

	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_CHECKBOXES);
	m_List.InsertColumn(0, _T("课程名称"), 0, 150);
	m_List.InsertColumn(1, _T("授课教师"), 0, 100);
	m_List.InsertColumn(2, _T("开课学院"), 0, 150);
	m_List.InsertColumn(3, _T("课程代码"), 0, 100);
	m_List.InsertColumn(4, _T("课程学分"), 0, 100);
	m_List.InsertColumn(5, _T("课程学时"), 0, 100);


	CInfoFile file;
	file.ReadCourse();
	int i = 0;
	for (list<coursemsg>::iterator it = file.ls3.begin(); it != file.ls3.end(); it++)  //将文件数据写入列表
	{
		m_List.InsertItem(i, (CString)it->courseTitle.c_str());
		m_List.SetItemText(i, 1, (CString)it->teacher.c_str());
		m_List.SetItemText(i, 2, (CString)it->college.c_str());
		m_List.SetItemText(i, 3, (CString)it->courseCode.c_str());
		m_List.SetItemText(i, 4, (CString)it->score.c_str());
		m_List.SetItemText(i, 5, (CString)it->time.c_str());
		i++;
	}

}


void CCourseDlg::OnBnClickedButton1()						//添加课程信息
{
	// TODO: 在此添加控件通知处理程序代码
	CAddCourse dlg;
	dlg.DoModal();
	
	if (dlg.flag == 1)
	{
		if (dlg.m_courseTitle.IsEmpty() || dlg.m_teacher.IsEmpty() || dlg.m_college.IsEmpty() || dlg.m_courseCode.IsEmpty() || dlg.m_score.IsEmpty() || dlg.m_time.IsEmpty())
		{
			MessageBox(_T("输入课程信息不能为空！"));
			return;
		}

		int nCount = m_List.GetItemCount();
		m_List.InsertItem(nCount, dlg.m_courseTitle);
		m_List.SetItemText(nCount, 1, dlg.m_teacher);
		m_List.SetItemText(nCount, 2, dlg.m_college);
		m_List.SetItemText(nCount, 3, dlg.m_courseCode);
		m_List.SetItemText(nCount, 4, dlg.m_score);
		m_List.SetItemText(nCount, 5, dlg.m_time);

		coursemsg temp;
		CStringA courseTitle, teacher, college, courseCode, score, time;
		courseTitle = dlg.m_courseTitle;
		teacher = dlg.m_teacher;
		college = dlg.m_college;
		courseCode = dlg.m_courseCode;
		score = dlg.m_score;
		time = dlg.m_time;
		
		temp.courseTitle = courseTitle;
		temp.teacher = teacher;
		temp.college = college;
		temp.courseCode = courseCode;
		temp.score = score;
		temp.time = time;

		CInfoFile file;
		file.ReadCourse();
		file.ls3.push_back(temp);
		file.WriteCourse();
	}
}


void CCourseDlg::OnBnClickedButton2()									//删除课程信息
{
	// TODO: 在此添加控件通知处理程序代码

	CInfoFile file;
	file.ReadCourse();
	int i = 0;
	for (list<coursemsg>::iterator it = file.ls3.begin(); it != file.ls3.end(); it++)
	{
		bool state = m_List.GetCheck(i);
		if (state)
		{
			m_List.DeleteItem(i);
			file.ls3.erase(it);
			break;
		}
		i++;
	}
	file.WriteCourse();
	MessageBox(_T("删除成功！"));
}


void CCourseDlg::OnBnClickedButton7()						//查询课程信息
{
	// TODO: 在此添加控件通知处理程序代码

	UpdateData(TRUE);					//获取数据

	bool flag = 0;						//为0查询失败，为1成功
	CInfoFile file;
	file.ReadCourse();
	for (list<coursemsg>::iterator it = file.ls3.begin(); it != file.ls3.end(); it++)
	{
		if ((CString)it->courseCode.c_str() == m_coursecode1)				//学号一致
		{
			flag = 1;
			CString str;
			str = _T("课程名称:") + (CString)it->courseTitle.c_str() + "\r\n" + _T("授课教师:") + (CString)it->teacher.c_str() + "\r\n" +
				_T("开课学院:") + (CString)it->college.c_str() + "\r\n" + _T("课程代码:") + (CString)it->courseCode.c_str() + "\r\n" +
				_T("课程学分:") + (CString)it->score.c_str() + "\r\n" + _T("课程学时:") + (CString)it->time.c_str();
			m_display = str;
			UpdateData(FALSE);
			MessageBox(_T("查询成功！"));
			break;
		}
	}
	if (!flag)
		MessageBox(_T("查询失败！"));
	m_coursecode1.Empty();
	UpdateData(FALSE);
}


void CCourseDlg::OnBnClickedButton4()					//清空课程查询结果的编辑框
{
	// TODO: 在此添加控件通知处理程序代码
	m_display.Empty();
	UpdateData(FALSE);
}


void CCourseDlg::OnBnClickedButton3()					//更改课程信息
{
	// TODO: 在此添加控件通知处理程序代码

	UpdateData(TRUE);									//获取编辑框内容

	CInfoFile file;
	file.ReadCourse();
	bool flag = 0;										//判断课程代码是否存在
	for (list<coursemsg>::iterator it = file.ls3.begin(); it != file.ls3.end(); it++)
	{
		if ((CString)it->courseCode.c_str() == m_coursecode)				//学号一致
		{
			flag = 1;
			break;
		}
	}
	if (flag == 0)
	{
		MessageBox(_T("更改失败，没有该课程代码！"));
		m_coursecode.Empty();
		UpdateData(FALSE);
		return;
	}

	else
	{
		CAddCourse dlg;;
		dlg.DoModal();

		if (dlg.flag == 1)
		{
			if (dlg.m_courseTitle.IsEmpty() || dlg.m_teacher.IsEmpty() || dlg.m_college.IsEmpty() || dlg.m_courseCode.IsEmpty() || dlg.m_score.IsEmpty() || dlg.m_time.IsEmpty())
			{
				MessageBox(_T("输入课程信息不能为空！"));
				m_coursecode.Empty();
				UpdateData(FALSE);
				return;
			}

			CStringA courseTitle, teacher, college, courseCode, score, time;
			courseTitle = dlg.m_courseTitle;
			teacher = dlg.m_teacher;
			college = dlg.m_college;
			courseCode = dlg.m_courseCode;
			score = dlg.m_score;
			time = dlg.m_time;

			for (list<coursemsg>::iterator it = file.ls3.begin(); it != file.ls3.end(); it++)
			{
				if ((CString)it->courseCode.c_str() == m_coursecode)				//学号一致
				{
					if (it->courseTitle == courseTitle.GetBuffer() && it->courseCode == courseCode.GetBuffer() && it->college == college.GetBuffer() && it->teacher == teacher.GetBuffer() && it->score == score.GetBuffer() && it->time == time.GetBuffer())
					{
						MessageBox(_T("更改的课程信息与原来一致，无需更改！"));
						m_coursecode.Empty();
						UpdateData(FALSE);
						return;
					}
					it->courseTitle = courseTitle;
					it->teacher = teacher;
					it->college = college;
					it->courseCode = courseCode;
					it->score = score;
					it->time = time;
					break;
				}
			}

			if (flag == 1)
			{
				file.WriteCourse();

				int i = 0;
				m_List.DeleteAllItems();
				for (list<coursemsg>::iterator it = file.ls3.begin(); it != file.ls3.end(); it++)
				{
					m_List.InsertItem(i, (CString)it->courseTitle.c_str());
					m_List.SetItemText(i, 1, (CString)it->teacher.c_str());
					m_List.SetItemText(i, 2, (CString)it->college.c_str());
					m_List.SetItemText(i, 3, (CString)it->courseCode.c_str());
					m_List.SetItemText(i, 4, (CString)it->score.c_str());
					m_List.SetItemText(i, 5, (CString)it->time.c_str());
					i++;

				}
				MessageBox(_T("更改成功！"));
				m_coursecode.Empty();
				UpdateData(FALSE);
			}
		}

	}
	
}
		
	



void CCourseDlg::OnBnClickedButton5()								//打印课程信息
{
	// TODO: 在此添加控件通知处理程序代码

	int count = m_List.GetItemCount(), page, row = 0;
	int i, j;
	page = count / 40 + 1;

	CPrintDialog print(false);
	if (print.DoModal() == IDOK)
	{
		CDC printed;
		printed.Attach(print.GetPrinterDC());
		DOCINFO pdoc;
		pdoc.cbSize = sizeof(pdoc);
		pdoc.lpszDocName = _T("pdoc");
		pdoc.lpszDatatype = NULL;
		pdoc.lpszOutput = NULL;
		if (printed.StartDocW(&pdoc) >= 0)
		{
			LOGFONT logfont;
			memset(&logfont, 0, sizeof(LOGFONT));
			LOGFONT logFont;
			//内容字体设置
			logFont.lfHeight = (50);
			logFont.lfWidth = 0;
			logFont.lfEscapement = 0;
			logFont.lfOrientation = 0;
			logFont.lfWeight = 500;
			logFont.lfItalic = 0;
			logFont.lfUnderline = 0;
			logFont.lfStrikeOut = 0;
			logFont.lfCharSet = ANSI_CHARSET;
			logFont.lfOutPrecision = OUT_DEFAULT_PRECIS;
			logFont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
			logFont.lfQuality = PROOF_QUALITY;
			logFont.lfPitchAndFamily = VARIABLE_PITCH | FF_ROMAN;
			strcpy((char*)logFont.lfFaceName, "宋体");
			
			CFont font;
			CFont* oldfont = NULL;
			if (font.CreatePointFontIndirect(&logfont))
				oldfont = (CFont*)printed.SelectObject(&font);
			for (j = 1; j <= page; j++)
			{
				printed.StartPage();
				int x = 1200, y = 500;
				CString pageHead, pageBottom;
				pageHead.Format(_T("课程信息统计表"));
				printed.TextOutW(1900, 100, pageHead);
				CString title;
				title.Format(_T("课程名称||授课教师||开课学院||课程代码||课程学分||课程学时"));
				printed.TextOutW(1200, 300, title);

				for (i = 1; (i < 40) && (row < count); i++)
				{
					CString record(_T(""));
					record += this->m_List.GetItemText(row, 0) + _T("||");
					record += this->m_List.GetItemText(row, 1) + _T("||");
					record += this->m_List.GetItemText(row, 2) + _T("||");
					record += this->m_List.GetItemText(row, 3) + _T("||");
					record += this->m_List.GetItemText(row, 4) + _T("||");
					record += this->m_List.GetItemText(row, 5) ;
					printed.TextOutW(x, y, record);
					y += 150;
					row++;
				}
				pageBottom.Format(_T("共%d页    第%d页"), page, j);
				printed.TextOutW(2000, 6800, pageBottom);

				printed.EndPage();

			}
			font.DeleteObject();
			if (oldfont != NULL)
			{
				printed.SelectObject(oldfont);
				printed.EndDoc();
			}
			printed.DeleteDC();
		}
	}
}
