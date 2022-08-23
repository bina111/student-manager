// CStuManger.cpp: 实现文件
//

#include "pch.h"
#include "StudentStatusSystem.h"
#include "CStuManger.h"
#include"CInfoFile.h"
#include"CStuMsgAdd.h"


// CStuManger

IMPLEMENT_DYNCREATE(CStuManger, CFormView)

CStuManger::CStuManger()
	: CFormView(IDD_DIALOG_STUMANGER)
	, m_num(_T(""))
	, m_select(_T(""))
	, m_number(_T(""))
{

}

CStuManger::~CStuManger()
{
}

void CStuManger::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_List);
	DDX_Text(pDX, IDC_EDIT1, m_num);
	DDX_Text(pDX, IDC_EDIT3, m_select);
	DDX_Text(pDX, IDC_EDIT2, m_number);
}

BEGIN_MESSAGE_MAP(CStuManger, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CStuManger::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON7, &CStuManger::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON4, &CStuManger::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON2, &CStuManger::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CStuManger::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON5, &CStuManger::OnBnClickedButton5)
END_MESSAGE_MAP()


// CStuManger 诊断

#ifdef _DEBUG
void CStuManger::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CStuManger::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CStuManger 消息处理程序


void CStuManger::OnBnClickedButton1()						//添加学生信息
{
	// TODO: 在此添加控件通知处理程序代码

	CStuMsgAdd dlg;
	dlg.DoModal();

	if (dlg.flag == 1)
	{
		if (dlg.m_number.IsEmpty() || dlg.m_name.IsEmpty() || dlg.m_sex.IsEmpty() || 
			dlg.m_acadamy.IsEmpty() || dlg.m_major.IsEmpty() || dlg.m_grade.IsEmpty() || dlg.m_number.IsEmpty())
		{
			MessageBox(_T("输入学生信息不能为空！"));
			return;
		}

	    int nCount = m_List.GetItemCount();
		m_List.InsertItem(nCount, dlg.m_number);
		m_List.SetItemText(nCount, 1, dlg.m_name);
		m_List.SetItemText(nCount, 2, dlg.m_sex);
		m_List.SetItemText(nCount, 3, dlg.m_acadamy);
		m_List.SetItemText(nCount, 4, dlg.m_major);
		m_List.SetItemText(nCount, 5, dlg.m_grade);

		stumsg temp;
		CStringA number, name, sex, acadamy, major, grade;
		number = dlg.m_number;
		name = dlg.m_name;
		sex = dlg.m_sex;
		acadamy = dlg.m_acadamy;
		major = dlg.m_major;
		grade = dlg.m_grade;

		temp.number = number;
		temp.name = name;
		temp.sex = sex;
		temp.academy = acadamy;
		temp.major = major;
		temp.grade = grade;

		CInfoFile file;
		file.ReadStudMsg();
		file.ls2.push_back(temp);
		file.WirteStuMsg();
		MessageBox(_T("添加成功！"));
	}

}


void CStuManger::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_CHECKBOXES);
	m_List.InsertColumn(0, _T("学号"), 0, 100);
	m_List.InsertColumn(1, _T("姓名"), 0, 100);
	m_List.InsertColumn(2, _T("性别"), 0, 80);
	m_List.InsertColumn(3, _T("学院"), 0, 150);
	m_List.InsertColumn(4, _T("专业"), 0, 150);
	m_List.InsertColumn(5, _T("年级"), 0, 100);
	
	CInfoFile file;
	file.ReadStudMsg();
	int i = 0;
	for (list<stumsg>::iterator it = file.ls2.begin(); it != file.ls2.end(); it++)  //将文件数据写入列表
	{
		m_List.InsertItem(i, (CString)it->number.c_str());
		m_List.SetItemText(i, 1, (CString)it->name.c_str());
		m_List.SetItemText(i, 2, (CString)it->sex.c_str());
		m_List.SetItemText(i, 3, (CString)it->academy.c_str());
		m_List.SetItemText(i, 4, (CString)it->major.c_str());
		m_List.SetItemText(i, 5, (CString)it->grade.c_str());
		
		i++;

	}
	
		// TODO: 在此添加专用代码和/或调用基类


}

void CStuManger::OnBnClickedButton7()						//查询学生信息
{
	// TODO: 在此添加控件通知处理程序代码

	UpdateData(TRUE);					//获取数据

	bool flag = 0;						//为0查询失败，为1成功
	CInfoFile file;
	file.ReadStudMsg();
	for (list<stumsg>::iterator it = file.ls2.begin(); it != file.ls2.end(); it++)
	{
		if ((CString)it->number.c_str() == m_num)				//学号一致
		{
			flag = 1;
			CString str;
			str = _T("学号:") + (CString)it->number.c_str() + "\r\n" + _T("姓名:") + (CString)it->name.c_str() + "\r\n" +
				_T("性别:") + (CString)it->sex.c_str() + "\r\n" + _T("学院:") + (CString)it->academy.c_str() + "\r\n" +
				_T("专业:") + (CString)it->major.c_str() + "\r\n" + _T("年级:") + (CString)it->grade.c_str() ;
			m_select = str;
			UpdateData(FALSE);
			MessageBox(_T("查询成功！"));
			break;
		}
	}
	if (!flag)
		MessageBox(_T("查询失败！"));
	m_num.Empty();
	UpdateData(FALSE);
}


void CStuManger::OnBnClickedButton4()				//清空编辑框内容
{
	// TODO: 在此添加控件通知处理程序代码
	m_select.Empty();
	UpdateData(FALSE);
}


void CStuManger::OnBnClickedButton2()				//删除学生信息
	// TODO: 在此添加控件通知处理程序代码
{
	CInfoFile file;
	file.ReadStudMsg();
	int i = 0;
	for (list<stumsg>::iterator it = file.ls2.begin(); it != file.ls2.end();it++ )
	{
		bool state = m_List.GetCheck(i);
		if (state)
		{
			m_List.DeleteItem(i);
			file.ls2.erase(it);
			break;
		}
		i++;
	}
	file.WirteStuMsg();
	MessageBox(_T("删除成功！"));
}


void CStuManger::OnBnClickedButton3()						//更改学生信息
{
	// TODO: 在此添加控件通知处理程序代码
	
	UpdateData(TRUE);								//获取编辑框数据

	CInfoFile file;
	file.ReadStudMsg();
	bool flag = 0;									//判断学号是否存在
	for (list<stumsg>::iterator it = file.ls2.begin(); it != file.ls2.end(); it++)
	{
		if ((CString)it->number.c_str() == m_number)				//学号一致
		{
			flag = 1;
			break;
		}
	}
	if (flag == 0)
	{
		MessageBox(_T("更改失败，没有该学号！"));
		m_number.Empty();
		UpdateData(FALSE);
		return;
	}
	
	else
	{
		CStuMsgAdd dlg;
		dlg.DoModal();

		if (dlg.flag == 1)
		{
			if (dlg.m_number.IsEmpty() || dlg.m_name.IsEmpty() || dlg.m_sex.IsEmpty() || dlg.m_acadamy.IsEmpty()
				|| dlg.m_major.IsEmpty() || dlg.m_grade.IsEmpty())
			{
				MessageBox(_T("输入学生信息不能为空！"));
				m_number.Empty();
				UpdateData(FALSE);
				return;
			}
			CStringA number, name, sex, acadamy, major, grade;
			number = dlg.m_number;
			name = dlg.m_name;
			sex = dlg.m_sex;
			acadamy = dlg.m_acadamy;
			major = dlg.m_major;
			grade = dlg.m_grade;
			number = dlg.m_number;
		
			for (list<stumsg>::iterator it = file.ls2.begin(); it != file.ls2.end(); it++)
			{
				if ((CString)it->number.c_str() == m_number)				//学号一致
				{
					if (it->number == number.GetBuffer() && it->name == name.GetBuffer() && 
						it->sex == sex.GetBuffer() && it->academy == acadamy.GetBuffer() && 
						it->major == major.GetBuffer() && it->grade == grade.GetBuffer())
					{
						MessageBox(_T("更改的学生的信息与原来一致，无需更改！"));
						m_number.Empty();
						UpdateData(FALSE);
						return;
					}
					it->number = number;
					it->name = name;
					it->sex = sex;
					it->academy = acadamy;
					it->major = major;
					it->grade = grade;
				
					break;
				}
			}
			file.WirteStuMsg();
			int i = 0;
			m_List.DeleteAllItems();
			for (list<stumsg>::iterator it = file.ls2.begin(); it != file.ls2.end(); it++)  //将文件数据写入列表
			{
				m_List.InsertItem(i, (CString)it->number.c_str());
				m_List.SetItemText(i, 1, (CString)it->name.c_str());
				m_List.SetItemText(i, 2, (CString)it->sex.c_str());
				m_List.SetItemText(i, 3, (CString)it->academy.c_str());
				m_List.SetItemText(i, 4, (CString)it->major.c_str());
				m_List.SetItemText(i, 5, (CString)it->grade.c_str());

				i++;

			}
			MessageBox(_T("更改成功！"));
			m_number.Empty();
			UpdateData(FALSE);
		
		}
	}
	
}


void CStuManger::OnBnClickedButton5()							//打印学生基本信息
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
				pageHead.Format(_T("学生基本信息统计表"));
				printed.TextOutW(1900, 100, pageHead);
				CString title;
				title.Format(_T("学号||姓名||性别||学院||专业||年级"));
				printed.TextOutW(1200, 300, title);

				for (i = 1; (i < 40) && (row < count); i++)
				{
					CString record(_T(""));
					record += this->m_List.GetItemText(row, 0) + _T("||");
					record += this->m_List.GetItemText(row, 1) + _T("||");
					record += this->m_List.GetItemText(row, 2) + _T("||");
					record += this->m_List.GetItemText(row, 3) + _T("||");
					record += this->m_List.GetItemText(row, 4) + _T("||");
					record += this->m_List.GetItemText(row, 5);
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
