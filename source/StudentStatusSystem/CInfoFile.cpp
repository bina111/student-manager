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


//��ȡ����Ա��½��Ϣ
void CInfoFile::ReadLogin(CString& name, CString& pwd)
{
	ifstream ifs; //�����ļ��������
	ifs.open(_F_ADMINISTRATORLOGIN);  //���ļ�

	char buf[1024] = { 0 };

	ifs.getline(buf, sizeof(buf));   //��ȡһ������
	name = CString(buf);			 //char *ת��ΪCString

	ifs.getline(buf, sizeof(buf));
	pwd = CString(buf);

	ifs.close(); //�ر��ļ�
}


//�޸Ĺ���Ա��¼����
void CInfoFile::WritePwd(char* name, char* pwd)
{
	ofstream ofs;					 //�����ļ��������
	ofs.open(_F_ADMINISTRATORLOGIN); //���ļ�

	ofs << name << endl;			 //nameд���ļ�
	ofs << pwd << endl;				 //pwdд���ļ�

	ofs.close();					//�ر��ļ�
}

//��ȡѧ����¼��Ϣ
void CInfoFile::ReadStuLogin()
{
	ifstream ifs;				//�����ļ��������
	ifs.open(_F_STUDENTLOGIN);  //���ļ�
	char buf[1024] = { 0 };
	num1 = 0;					//��ʼ��ѧ������Ϊ0
	ls1.clear();				
	ifs.getline(buf, sizeof(buf));	//ȡ����ͷ

	while (!ifs.eof())				//û���ļ���β
	{
		stulogin tmp;

		ifs.getline(buf, sizeof(buf));  //��ȡһ��
		num1++;							//ѧ��������һ

		char* sst = strtok(buf, "|"); //�ԡ�|���и�
		if (sst != NULL)
		{
			tmp.number =sst;		  //ѧ��ѧ��
		}
		else
		{
			break;
		}

		sst = strtok(NULL, "|");
		tmp.pwd = sst;					//�˺�����

		ls1.push_back(tmp);             //��������ĺ���
	}

	ifs.close(); //�ر��ļ�
}

//�޸�ѧ����¼����
void CInfoFile::WriteStuPwd(char* pwd)
{
	ofstream ofs(_F_STUDENTLOGIN);//�����ʽ���ļ�

	ifstream ifs(_F_STU);		//���ļ�
	char buf[1024] = { 0 };
	ifs.getline(buf, sizeof(buf));	//ȡ����¼ѧ����ѧ��
	ifs.close();					//�ر��ļ�

	if (ls1.size() > 0)	          //��ѧ���˺Ų�ִ��
	{
		ofs << "�û���|����" << endl;		  //д���ͷ

		//ͨ��������ȡ���������ݣ�д���ļ����ԡ�|���ָ�����β�ӻ���
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

	ofs.close();				 //�ر��ļ�

}

//��ѧ����¼��Ϣд���ļ�
void CInfoFile::WriteStuPwdd()
{
	ofstream ofs(_F_STUDENTLOGIN);					//�����ʽ���ļ�

	if (ls1.size() > 0)								//��ѧ����¼��Ϣ��ִ��
	{
		ofs << "�û���|����" << endl; //д���ͷ

		//ͨ��������ȡ���������ݣ�д���ļ����ԡ�|���ָ�����β�ӻ���
		for (list<stulogin>::iterator it = ls1.begin(); it != ls1.end(); it++)
		{
			ofs << it->number << "|";
			ofs << it->pwd << endl;
		}
	}

	ofs.close();//�ر��ļ�
}

//��ȡ��½��ĳ��ѧ����ѧ��
void CInfoFile::ReadStu(CString& number)
{
	ifstream ifs; //�����ļ��������
	ifs.open(_F_STU); //���ļ�

	char buf[1024] = { 0 };

	ifs.getline(buf, sizeof(buf)); //��ȡһ������
	number = CString(buf);			 //char *ת��ΪCString

	ifs.close(); //�ر��ļ�
}

//����½��ĳ��ѧ����ѧ��д���ļ�
void CInfoFile::WriteStu(char* number)
{
	ofstream ofs(_F_STU);//�����ʽ���ļ�
	ofs << number << endl; //nameд���ļ�

	ofs.close();	//�ر��ļ�

}

//��ȡѧ��������Ϣ
void CInfoFile::ReadStudMsg()
{
	ifstream ifs(_F_STUDENTMESSAGE); //���뷽ʽ���ļ�

	char buf[1024] = { 0 };
	num1 = 0;						//��ʼ��ѧ������Ϊ0
	ls2.clear();
	//ȡ����ͷ
	ifs.getline(buf, sizeof(buf));

	while (!ifs.eof())				//û���ļ���β
	{
		stumsg tmp;

		ifs.getline(buf, sizeof(buf)); //��ȡһ��
		num1++;							//ѧ��������һ

		char* sst = strtok(buf, "|"); //�ԡ�|���и�
		if (sst != NULL)
		{
			tmp.number = sst;			//ѧ��ѧ��
		}
		else
		{
			break;
		}

		sst = strtok(NULL, "|");
		tmp.name = sst;					//ѧ������

		sst = strtok(NULL, "|");
		tmp.sex = sst;					//�Ա�

		sst = strtok(NULL, "|");
		tmp.academy = sst;				//ѧԺ

		sst = strtok(NULL, "|");
		tmp.major = sst;				//רҵ

		sst = strtok(NULL, "|");
		tmp.grade = sst;				//�꼶


		ls2.push_back(tmp); //��������ĺ���
	}

	ifs.close(); //�ر��ļ�
}

//ѧ��������Ϣд���ļ�
void CInfoFile::WirteStuMsg()
{
	ofstream ofs(_F_STUDENTMESSAGE);			//�����ʽ���ļ�

	if (ls2.size() > 0)							//��ѧ����Ϣ��ִ��
	{
		ofs << "ѧ��|����|�Ա�|ѧԺ|רҵ|�꼶" << endl; //д���ͷ

		//ͨ��������ȡ���������ݣ�д���ļ����ԡ�|���ָ�����β�ӻ���
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

	ofs.close();//�ر��ļ�
}


//��ȡ�γ���Ϣ
void CInfoFile::ReadCourse()
{
	ifstream ifs(_F_COURSE);		//���뷽ʽ���ļ�

	char buf[1024] = { 0 };
	num2 = 0;						//��ʼ���γ�����Ϊ0
	ls3.clear();
	//ȡ����ͷ
	ifs.getline(buf, sizeof(buf));

	while (!ifs.eof())				//û���ļ���β
	{
		coursemsg tmp;

		ifs.getline(buf, sizeof(buf)); //��ȡһ��
		num2++;							//ѧ��������һ

		char* sst = strtok(buf, "|"); //�ԡ�|���и�
		if (sst != NULL)
		{
			tmp.courseTitle = sst;			//�γ�����
		}
		else
		{
			break;
		}

		sst = strtok(NULL, "|");
		tmp.teacher = sst;					//�ѿ���ʦ

		sst = strtok(NULL, "|");
		tmp.college = sst;					//����ѧԺ

		sst = strtok(NULL, "|");
		tmp.courseCode = sst;				//�γ̴���

		sst = strtok(NULL, "|");
		tmp.score = sst;				    //�γ�ѧ��

		sst = strtok(NULL, "|");
		tmp.time = sst;						//�γ�ѧʱ

		ls3.push_back(tmp); //��������ĺ���
	}

	ifs.close(); //�ر��ļ�
}

//�γ���Ϣд���ļ�
void CInfoFile::WriteCourse()
{
	ofstream ofs(_F_COURSE);					//�����ʽ���ļ�

	if (ls3.size() > 0)							//�пγ���Ϣ��ִ��
	{
		ofs << "�γ�����|�ڿν�ʦ|����ѧԺ|�γ̴���|�γ�ѧ��|�γ�ѧʱ" << endl; //д���ͷ

		//ͨ��������ȡ���������ݣ�д���ļ����ԡ�|���ָ�����β�ӻ���
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

	ofs.close();//�ر��ļ�
}

//��ȡ�ɼ���Ϣ
void CInfoFile::ReadScore()
{
	ifstream ifs(_F_SCORE); //���뷽ʽ���ļ�

	char buf[1024] = { 0 };
	ls4.clear();
	//ȡ����ͷ
	ifs.getline(buf, sizeof(buf));

	while (!ifs.eof())				//û���ļ���β
	{
		stuscore tmp;

		ifs.getline(buf, sizeof(buf)); //��ȡһ��

		char* sst = strtok(buf, "|"); //�ԡ�|���и�
		if (sst != NULL)
		{
			tmp.number = sst;			//ѧ��ѧ��
		}
		else
		{
			break;
		}

		sst = strtok(NULL, "|");
		tmp.name = sst;					//ѧ������

		sst = strtok(NULL, "|");
		tmp.GPA = sst;					//����

		sst = strtok(NULL, "|");
		tmp.gradeRanked = sst;			//�꼶����


		ls4.push_back(tmp); //��������ĺ���
	}

	ifs.close(); //�ر��ļ�
}

//�ɼ���Ϣд���ļ�
void CInfoFile::WriteScore()
{
	ofstream ofs(_F_SCORE);					//�����ʽ���ļ�

	if (ls4.size() > 0)							//�пγ���Ϣ��ִ��
	{
		ofs << "ѧ��|����|����|�꼶����" << endl; //д���ͷ

		//ͨ��������ȡ���������ݣ�д���ļ����ԡ�|���ָ�����β�ӻ���
		for (list<stuscore>::iterator it = ls4.begin(); it != ls4.end(); it++)
		{
			ofs << it->number << "|";
			ofs << it->name << "|";
			ofs << it->GPA << "|";
			ofs << it->gradeRanked << endl;
		}
	}

	ofs.close();//�ر��ļ�
}