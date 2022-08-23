#pragma once
#include <list>
#include <fstream>
#include <iostream>
#include <string>

#define _F_ADMINISTRATORLOGIN "./administratorLogin.txt"
#define _F_STUDENTLOGIN "./studentLogin.txt"
#define _F_STUDENTMESSAGE "./studentMessage.txt"
#define _F_COURSE "./course.txt"
#define _F_STU "./stu.txt"
#define _F_SCORE "./score.txt"

using namespace std;

struct stulogin			//学生登录结构体
{
	string number;		//学号
	string pwd;			//密码
};

struct stumsg			//学生信息结构体
{
	string number;		//学号
	string name;		//姓名
	string sex;			//性别
	string academy;		//学院
	string major;		//专业
	string grade;		//年级
};

struct coursemsg		//课程信息结构体
{
	string courseTitle;		//课程名称
	string teacher;			//搜课老师
	string college;			//开课学院
	string courseCode;		//课程代码
	string score;			//课程学分
	string time;			//课程学时
};

struct stuscore
{
	string number;		    //学号
	string name;			//姓名
	string GPA;				//绩点
	string gradeRanked;		//年级排名
};

class CInfoFile
{
public:
	CInfoFile();
	~CInfoFile();

	//读取管理员登陆信息
	void ReadLogin(CString& name, CString& pwd);

	//修改管理员登录密码
	void WritePwd(char* name, char* pwd);

	//读取学生登录信息
	void ReadStuLogin();

	//修改学生登录密码
	void WriteStuPwd(char* pwd);

	//将学生登录信息写入文件
	void WriteStuPwdd();

	//读取登陆的某个学生的学号
	void ReadStu(CString& number);

	//将登陆的某个学生的学号写入文件
	void WriteStu(char* number);

	//读取学生个人信息
	void ReadStudMsg();

	//学生个人信息写入文件
	void WirteStuMsg();

	//读取课程信息
	void ReadCourse();

	//课程信息写入文件
	void WriteCourse();

	//读取成绩信息
	void ReadScore();

	//成绩信息写入文件
	void WriteScore();
	
	list<stulogin> ls1;	//存储学生登录信息容器
	list<stumsg> ls2;	//存储学生基本信息容器
	list<coursemsg> ls3;//存储课程信息容器
	list<stuscore> ls4;	//存储成绩信息容器
	int num1;			//用来记录学生人数
	int num2;			//用来记录课程门数
};

