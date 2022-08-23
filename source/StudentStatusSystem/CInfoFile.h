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

struct stulogin			//ѧ����¼�ṹ��
{
	string number;		//ѧ��
	string pwd;			//����
};

struct stumsg			//ѧ����Ϣ�ṹ��
{
	string number;		//ѧ��
	string name;		//����
	string sex;			//�Ա�
	string academy;		//ѧԺ
	string major;		//רҵ
	string grade;		//�꼶
};

struct coursemsg		//�γ���Ϣ�ṹ��
{
	string courseTitle;		//�γ�����
	string teacher;			//�ѿ���ʦ
	string college;			//����ѧԺ
	string courseCode;		//�γ̴���
	string score;			//�γ�ѧ��
	string time;			//�γ�ѧʱ
};

struct stuscore
{
	string number;		    //ѧ��
	string name;			//����
	string GPA;				//����
	string gradeRanked;		//�꼶����
};

class CInfoFile
{
public:
	CInfoFile();
	~CInfoFile();

	//��ȡ����Ա��½��Ϣ
	void ReadLogin(CString& name, CString& pwd);

	//�޸Ĺ���Ա��¼����
	void WritePwd(char* name, char* pwd);

	//��ȡѧ����¼��Ϣ
	void ReadStuLogin();

	//�޸�ѧ����¼����
	void WriteStuPwd(char* pwd);

	//��ѧ����¼��Ϣд���ļ�
	void WriteStuPwdd();

	//��ȡ��½��ĳ��ѧ����ѧ��
	void ReadStu(CString& number);

	//����½��ĳ��ѧ����ѧ��д���ļ�
	void WriteStu(char* number);

	//��ȡѧ��������Ϣ
	void ReadStudMsg();

	//ѧ��������Ϣд���ļ�
	void WirteStuMsg();

	//��ȡ�γ���Ϣ
	void ReadCourse();

	//�γ���Ϣд���ļ�
	void WriteCourse();

	//��ȡ�ɼ���Ϣ
	void ReadScore();

	//�ɼ���Ϣд���ļ�
	void WriteScore();
	
	list<stulogin> ls1;	//�洢ѧ����¼��Ϣ����
	list<stumsg> ls2;	//�洢ѧ��������Ϣ����
	list<coursemsg> ls3;//�洢�γ���Ϣ����
	list<stuscore> ls4;	//�洢�ɼ���Ϣ����
	int num1;			//������¼ѧ������
	int num2;			//������¼�γ�����
};

