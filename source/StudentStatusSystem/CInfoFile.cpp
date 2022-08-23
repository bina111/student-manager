#include "pch.h"
#include "CInfoFile.h"

CInfoFile::CInfoFile()
{
	num1 = 0;
	num2 = 0;
}


CInfoFile::~CInfoFile()
{
}


//读取管理员登陆信息
void CInfoFile::ReadLogin(CString& name, CString& pwd)
{
	ifstream ifs; //创建文件输入对象
	ifs.open(_F_ADMINISTRATORLOGIN);  //打开文件

	char buf[1024] = { 0 };

	ifs.getline(buf, sizeof(buf));   //读取一行内容
	name = CString(buf);			 //char *转换为CString

	ifs.getline(buf, sizeof(buf));
	pwd = CString(buf);

	ifs.close(); //关闭文件
}


//修改管理员登录密码
void CInfoFile::WritePwd(char* name, char* pwd)
{
	ofstream ofs;					 //创建文件输出对象
	ofs.open(_F_ADMINISTRATORLOGIN); //打开文件

	ofs << name << endl;			 //name写入文件
	ofs << pwd << endl;				 //pwd写入文件

	ofs.close();					//关闭文件
}

//读取学生登录信息
void CInfoFile::ReadStuLogin()
{
	ifstream ifs;				//创建文件输入对象
	ifs.open(_F_STUDENTLOGIN);  //打开文件
	char buf[1024] = { 0 };
	num1 = 0;					//初始化学生人数为0
	ls1.clear();				
	ifs.getline(buf, sizeof(buf));	//取出表头

	while (!ifs.eof())				//没到文件结尾
	{
		stulogin tmp;

		ifs.getline(buf, sizeof(buf));  //读取一行
		num1++;							//学生人数加一

		char* sst = strtok(buf, "|"); //以“|”切割
		if (sst != NULL)
		{
			tmp.number =sst;		  //学生学号
		}
		else
		{
			break;
		}

		sst = strtok(NULL, "|");
		tmp.pwd = sst;					//账号密码

		ls1.push_back(tmp);             //放在链表的后面
	}

	ifs.close(); //关闭文件
}

//修改学生登录密码
void CInfoFile::WriteStuPwd(char* pwd)
{
	ofstream ofs(_F_STUDENTLOGIN);//输出方式打开文件

	ifstream ifs(_F_STU);		//打开文件
	char buf[1024] = { 0 };
	ifs.getline(buf, sizeof(buf));	//取出登录学生的学号
	ifs.close();					//关闭文件

	if (ls1.size() > 0)	          //有学生账号才执行
	{
		ofs << "用户名|密码" << endl;		  //写入表头

		//通过迭代器取出链表内容，写入文件，以“|”分隔，结尾加换行
		for (list<stulogin>::iterator it = ls1.begin(); it != ls1.end(); it++)
		{
			if (it->number == buf)
			{
				it->pwd = pwd;
			}
			ofs << it->number << "|";
			ofs << it->pwd<< endl;
		}
	}

	ofs.close();				 //关闭文件

}

//将学生登录信息写入文件
void CInfoFile::WriteStuPwdd()
{
	ofstream ofs(_F_STUDENTLOGIN);					//输出方式打开文件

	if (ls1.size() > 0)								//有学生登录信息才执行
	{
		ofs << "用户名|密码" << endl; //写入表头

		//通过迭代器取出链表内容，写入文件，以“|”分隔，结尾加换行
		for (list<stulogin>::iterator it = ls1.begin(); it != ls1.end(); it++)
		{
			ofs << it->number << "|";
			ofs << it->pwd << endl;
		}
	}

	ofs.close();//关闭文件
}

//读取登陆的某个学生的学号
void CInfoFile::ReadStu(CString& number)
{
	ifstream ifs; //创建文件输入对象
	ifs.open(_F_STU); //打开文件

	char buf[1024] = { 0 };

	ifs.getline(buf, sizeof(buf)); //读取一行内容
	number = CString(buf);			 //char *转换为CString

	ifs.close(); //关闭文件
}

//将登陆的某个学生的学号写入文件
void CInfoFile::WriteStu(char* number)
{
	ofstream ofs(_F_STU);//输出方式打开文件
	ofs << number << endl; //name写入文件

	ofs.close();	//关闭文件

}

//读取学生个人信息
void CInfoFile::ReadStudMsg()
{
	ifstream ifs(_F_STUDENTMESSAGE); //输入方式打开文件

	char buf[1024] = { 0 };
	num1 = 0;						//初始化学生人数为0
	ls2.clear();
	//取出表头
	ifs.getline(buf, sizeof(buf));

	while (!ifs.eof())				//没到文件结尾
	{
		stumsg tmp;

		ifs.getline(buf, sizeof(buf)); //读取一行
		num1++;							//学生人数加一

		char* sst = strtok(buf, "|"); //以“|”切割
		if (sst != NULL)
		{
			tmp.number = sst;			//学生学号
		}
		else
		{
			break;
		}

		sst = strtok(NULL, "|");
		tmp.name = sst;					//学生姓名

		sst = strtok(NULL, "|");
		tmp.sex = sst;					//性别

		sst = strtok(NULL, "|");
		tmp.academy = sst;				//学院

		sst = strtok(NULL, "|");
		tmp.major = sst;				//专业

		sst = strtok(NULL, "|");
		tmp.grade = sst;				//年级


		ls2.push_back(tmp); //放在链表的后面
	}

	ifs.close(); //关闭文件
}

//学生个人信息写入文件
void CInfoFile::WirteStuMsg()
{
	ofstream ofs(_F_STUDENTMESSAGE);			//输出方式打开文件

	if (ls2.size() > 0)							//有学生信息才执行
	{
		ofs << "学号|姓名|性别|学院|专业|年级" << endl; //写入表头

		//通过迭代器取出链表内容，写入文件，以“|”分隔，结尾加换行
		for (list<stumsg>::iterator it = ls2.begin(); it != ls2.end(); it++)
		{
			ofs << it->number << "|";
			ofs << it->name << "|";
			ofs << it->sex << "|";
			ofs << it->academy << "|";
			ofs << it->major << "|";
			ofs << it->grade << endl;
		}
	}

	ofs.close();//关闭文件
}


//读取课程信息
void CInfoFile::ReadCourse()
{
	ifstream ifs(_F_COURSE);		//输入方式打开文件

	char buf[1024] = { 0 };
	num2 = 0;						//初始化课程门数为0
	ls3.clear();
	//取出表头
	ifs.getline(buf, sizeof(buf));

	while (!ifs.eof())				//没到文件结尾
	{
		coursemsg tmp;

		ifs.getline(buf, sizeof(buf)); //读取一行
		num2++;							//学生人数加一

		char* sst = strtok(buf, "|"); //以“|”切割
		if (sst != NULL)
		{
			tmp.courseTitle = sst;			//课程名称
		}
		else
		{
			break;
		}

		sst = strtok(NULL, "|");
		tmp.teacher = sst;					//搜课老师

		sst = strtok(NULL, "|");
		tmp.college = sst;					//开课学院

		sst = strtok(NULL, "|");
		tmp.courseCode = sst;				//课程代码

		sst = strtok(NULL, "|");
		tmp.score = sst;				    //课程学分

		sst = strtok(NULL, "|");
		tmp.time = sst;						//课程学时

		ls3.push_back(tmp); //放在链表的后面
	}

	ifs.close(); //关闭文件
}

//课程信息写入文件
void CInfoFile::WriteCourse()
{
	ofstream ofs(_F_COURSE);					//输出方式打开文件

	if (ls3.size() > 0)							//有课程信息才执行
	{
		ofs << "课程名称|授课教师|开课学院|课程代码|课程学分|课程学时" << endl; //写入表头

		//通过迭代器取出链表内容，写入文件，以“|”分隔，结尾加换行
		for (list<coursemsg>::iterator it = ls3.begin(); it != ls3.end(); it++)
		{
			ofs << it->courseTitle << "|";
			ofs << it->teacher << "|";
			ofs << it->college << "|";
			ofs << it->courseCode << "|";
			ofs << it->score << "|";
			ofs << it->time  << endl;
		}
	}

	ofs.close();//关闭文件
}

//读取成绩信息
void CInfoFile::ReadScore()
{
	ifstream ifs(_F_SCORE); //输入方式打开文件

	char buf[1024] = { 0 };
	ls4.clear();
	//取出表头
	ifs.getline(buf, sizeof(buf));

	while (!ifs.eof())				//没到文件结尾
	{
		stuscore tmp;

		ifs.getline(buf, sizeof(buf)); //读取一行

		char* sst = strtok(buf, "|"); //以“|”切割
		if (sst != NULL)
		{
			tmp.number = sst;			//学生学号
		}
		else
		{
			break;
		}

		sst = strtok(NULL, "|");
		tmp.name = sst;					//学生姓名

		sst = strtok(NULL, "|");
		tmp.GPA = sst;					//绩点

		sst = strtok(NULL, "|");
		tmp.gradeRanked = sst;			//年级排名


		ls4.push_back(tmp); //放在链表的后面
	}

	ifs.close(); //关闭文件
}

//成绩信息写入文件
void CInfoFile::WriteScore()
{
	ofstream ofs(_F_SCORE);					//输出方式打开文件

	if (ls4.size() > 0)							//有课程信息才执行
	{
		ofs << "学号|姓名|绩点|年级排名" << endl; //写入表头

		//通过迭代器取出链表内容，写入文件，以“|”分隔，结尾加换行
		for (list<stuscore>::iterator it = ls4.begin(); it != ls4.end(); it++)
		{
			ofs << it->number << "|";
			ofs << it->name << "|";
			ofs << it->GPA << "|";
			ofs << it->gradeRanked << endl;
		}
	}

	ofs.close();//关闭文件
}