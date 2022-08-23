// CScoreDlg.cpp: 实现文件
//

#include "pch.h"
#include "StudentStatusSystem.h"
#include "CScoreDlg.h"
#include"CInfoFile.h"
#include"CAddScore.h"

// CScoreDlg

IMPLEMENT_DYNCREATE(CScoreDlg, CFormView)

CScoreDlg::CScoreDlg()
	: CFormView(IDD_DIALOG_SCORE)
	, m_diaplay(_T(""))
	, m_number(_T(""))
	, m_number1(_T(""))
{

}

CScoreDlg::~CScoreDlg()
{
}

void CScoreDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_List);
	DDX_Text(pDX, IDC_EDIT3, m_diaplay);
	DDX_Text(pDX, IDC_EDIT1, m_number);
	DDX_Text(pDX, IDC_EDIT2, m_number1);
}

BEGIN_MESSAGE_MAP(CScoreDlg, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CScoreDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CScoreDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON7, &CScoreDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON4, &CScoreDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON3, &CScoreDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON5, &CScoreDlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// CScoreDlg 诊断

#ifdef _DEBUG
void CScoreDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CScoreDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CScoreDlg 消息处理程序


void CScoreDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	
	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_CHECKBOXES);
	m_List.InsertColumn(0, _T("学号"), 0, 150);
	m_List.InsertColumn(1, _T("姓名"), 0, 150);
	m_List.InsertColumn(5, _T("绩点"), 0, 150);
	m_List.InsertColumn(6, _T("年级排名"), 0, 150);

	CInfoFile file;
	file.ReadScore();
	int i = 0;
	for (list<stuscore>::iterator it = file.ls4.begin(); it != file.ls4.end(); it++)  //将文件数据写入列表
	{
		m_List.InsertItem(i, (CString)it->number.c_str());
		m_List.SetItemText(i, 1, (CString)it->name.c_str());
		m_List.SetItemText(i, 2, (CString)it->GPA.c_str());
		m_List.SetItemText(i, 3, (CString)it->gradeRanked.c_str());
		i++;

	}
	
}


void CScoreDlg::OnBnClickedButton1()			//添加学生成绩
{
	// TODO: 在此添加控件通知处理程序代码
	CAddScore dlg;
	dlg.DoModal();

	if (dlg.flag == 1)
	{
		if (dlg.m_number.IsEmpty() || dlg.m_name.IsEmpty() || dlg.m_GPA.IsEmpty() || dlg.m_gradeRanked.IsEmpty())
		{
			MessageBox(_T("输入学生成绩信息不能为空！"));
			return;
		}

		int nCount = m_List.GetItemCount();
		m_List.InsertItem(nCount, dlg.m_number);
		m_List.SetItemText(nCount, 1, dlg.m_name);
		m_List.SetItemText(nCount, 2, dlg.m_GPA);
		m_List.SetItemText(nCount, 3, dlg.m_gradeRanked);

		stuscore temp;
		CStringA number, name, GPA, gradeRanked;
		number = dlg.m_number;
		name = dlg.m_name;
		GPA = dlg.m_GPA;
		gradeRanked = dlg.m_gradeRanked;

		temp.number = number;
		temp.name = name;
		temp.GPA = GPA;
		temp.gradeRanked = gradeRanked;


		CInfoFile file;
		file.ReadScore();
		file.ls4.push_back(temp);
		file.WriteScore();
	}

}


void CScoreDlg::OnBnClickedButton2()						//删除学生成绩
{
	// TODO: 在此添加控件通知处理程序代码

	CInfoFile file;
	file.ReadScore();
	int i = 0;
	for (list<stuscore>::iterator it = file.ls4.begin(); it != file.ls4.end(); it++)
	{
		bool state = m_List.GetCheck(i);
		if (state)
		{
			m_List.DeleteItem(i);
			file.ls4.erase(it);
			break;
		}
		i++;
	}
	file.WriteScore();
	MessageBox(_T("删除成功！"));
}


void CScoreDlg::OnBnClickedButton7()					//查询学生成绩
{
	// TODO: 在此添加控件通知处理程序代码

	UpdateData(TRUE);					//获取数据

	bool flag = 0;						//为0查询失败，为1成功
	CInfoFile file;
	file.ReadScore();
	for (list<stuscore>::iterator it = file.ls4.begin(); it != file.ls4.end(); it++)
	{
		if ((CString)it->number.c_str() == m_number)				//学号一致
		{
			flag = 1;
			CString str;
			str = _T("学号:") + (CString)it->number.c_str() + "\r\n" + _T("姓名:") + (CString)it->name.c_str() + "\r\n" +
				_T("性别:") + (CString)it->GPA.c_str() + "\r\n" + _T("学院:") + (CString)it->gradeRanked.c_str() ;
			m_diaplay = str;
			UpdateData(FALSE);
			MessageBox(_T("查询成功！"));
			break;
		}
	}
	if (!flag)
		MessageBox(_T("查询失败！"));
	m_number.Empty();
	UpdateData(FALSE);
}


void CScoreDlg::OnBnClickedButton4()						//清空编辑框中学生成绩内容
{
	// TODO: 在此添加控件通知处理程序代码

	m_diaplay.Empty();
	UpdateData(FALSE);

}


void CScoreDlg::OnBnClickedButton3()						//更改学生成绩
{
	// TODO: 在此添加控件通知处理程序代码

	UpdateData(TRUE);										//获取编辑框数据

	CInfoFile file;
	file.ReadScore();
	bool flag = 0;
	for (list<stuscore>::iterator it = file.ls4.begin(); it != file.ls4.end(); it++)
	{
		if ((CString)it->number.c_str() == m_number1)				//学号一致
		{
			flag = 1;
			break;
		}
	}

	if (flag == 0)
	{
		MessageBox(_T("更改失败，没有该学号！"));
		m_number1.Empty();
		UpdateData(FALSE);
		return;
	}

	else
	{
		CAddScore dlg;
		dlg.DoModal();


		if (dlg.flag == 1)
		{
			if (dlg.m_number.IsEmpty() || dlg.m_name.IsEmpty() || dlg.m_GPA.IsEmpty() || dlg.m_gradeRanked.IsEmpty())
			{
				MessageBox(_T("输入学生成绩信息不能为空！"));
				m_number1.Empty();
				UpdateData(FALSE);
				return;
			}

			CStringA number, name, GPA, gradeRanked;
			number = dlg.m_number;
			name = dlg.m_name;
			GPA = dlg.m_GPA;
			gradeRanked = dlg.m_gradeRanked;

			for (list<stuscore>::iterator it = file.ls4.begin(); it != file.ls4.end(); it++)
			{
				if ((CString)it->number.c_str() == m_number1)				//学号一致
				{
					if (it->number == number.GetBuffer() && it->name == name.GetBuffer() && it->GPA == GPA.GetBuffer() && it->gradeRanked == gradeRanked.GetBuffer())
					{
						MessageBox(_T("输入学生成绩信息与原来一样，不用更改！"));
						m_number.Empty();
						UpdateData(FALSE);
						return;
					}
					it->number = number;
					it->name = name;
					it->GPA = GPA;
					it->gradeRanked = gradeRanked;

					break;
				}
			}
			file.WriteScore();
			int i = 0;
			m_List.DeleteAllItems();
			for (list<stuscore>::iterator it = file.ls4.begin(); it != file.ls4.end(); it++)  //将文件数据写入列表
			{
				m_List.InsertItem(i, (CString)it->number.c_str());
				m_List.SetItemText(i, 1, (CString)it->name.c_str());
				m_List.SetItemText(i, 2, (CString)it->GPA.c_str());
				m_List.SetItemText(i, 3, (CString)it->gradeRanked.c_str());

				i++;

			}
			MessageBox(_T("更改成功！"));
			m_number1.Empty();
			UpdateData(FALSE);
			return;
		}
	}
	
	
}


void CScoreDlg::OnBnClickedButton5()						//打印学生成绩
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
				pageHead.Format(_T("学生成绩信息统计表"));
				printed.TextOutW(1900, 100, pageHead);
				CString title;
				title.Format(_T("姓名||学号||绩点||年级排名"));
				printed.TextOutW(1200, 300, title);

				for (i = 1; (i < 40) && (row < count); i++)
				{
					CString record(_T(""));
					record += this->m_List.GetItemText(row, 0) + _T("||");
					record += this->m_List.GetItemText(row, 1) + _T("||");
					record += this->m_List.GetItemText(row, 2) + _T("||");
					record += this->m_List.GetItemText(row, 3);
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
