#include<iostream>
using namespace std;
#include"Identity.h"
#include<string>
#include<fstream>
#include"globalFile.h"
#include"Student.h"
#include"Manager.h"
#include"Teacher.h"

//�����ʦ�Ӳ˵�ҳ��
void teacherMenu(Identity* teacher)
{
	while (true)
	{
		teacher->operMenu(); //���ò˵�����

	//������ָ�� תΪ����ָ�� �������� �����ӿ�
		Teacher* tea = (Teacher*)teacher;

		int select = 0;
		cin >> select;
		if (select == 1)  //�鿴����ԤԼ
		{
			tea->showAllOrder();
		}
		else if (select == 2) //���ԤԼ
		{
			tea->validOrder();
		}
		else if (select == 0)
		{
			delete teacher; //�������
			cout << "ע���ɹ�" << endl;
			system("pause");
			system("cls");
			break;
		}
		else
		{
			cout << "�����������������룡" << endl;
			system("pause");
			system("cls");
		}
	}
	

}

//����ѧ���Ӳ˵�����
void studentMenu(Identity* student)
{
	while (true)
	{
		//������ѧ���Ӳ˵�
		student->operMenu();

		//������ָ�� ת������ָ��  ���Ե��������������ӿ�
		Student* stu = (Student*)student;

		int select = 0;
		cin >> select; //�����û�ѡ��

		if (select == 1) //����ԤԼ
		{
			stu->applyOrder();
		}
		else if (select == 2)//�鿴����ԤԼ
		{
			stu->showMyOrder();
		}
		else if (select == 3)//�鿴������ԤԼ
		{
			stu->showAllOrder();
		}
		else if (select == 4)//ȡ��ԤԼ
		{
			stu->cancelOrder();
		}
		else if (select == 0)
		{
			delete student;
			cout << "ע���ɹ�" << endl;
			system("pause");
			system("cls");
			return;
		}
		else
		{
			cout << "������������������" << endl;
			system("pause");
			system("cls");
		}
	}
}

//�������Ա�Ӳ˵�����
void managerMenu(Identity* manager)
{
	while (true)
	{
		//���ù���Ա�Ӳ˵�
		manager->operMenu();

		//������ָ��  תΪ����ָ��  ���Ե��������������ӿ�
		Manager* man = (Manager*)manager; 

		int select = 0;
		//�����û�ѡ��
		cin >> select;   

		if (select == 1) //����˺�
		{
			//cout << "����˺�" << endl;
			man->addPerson();
		}
		else if (select == 2) //�鿴�˺�
		{
			//cout << "�鿴�˺�" << endl;
			man->showPerson();
		}
		else if(select == 3) //�鿴����
		{
			//cout << "�鿴����" << endl;
			man->showComputer();
		}
		else if (select == 4) //���ԤԼ
		{
			//cout << "���ԤԼ" << endl;
			man->cleanFile();
		}
		else
		{
			delete manager; //���ٵ���������
			cout << "ע���ɹ�" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}



//��¼����  ����1 �������ļ���   ����2�������������
void LoginIn(string fileName, int type)
{
	//����ָ�� ����ָ���������
	Identity* person = NULL;

	//���ļ�
	ifstream ifs;
	ifs.open(fileName, ios::in);

	//�ж��ļ��Ƿ����
	if (!ifs.is_open())
	{
		cout << "�ļ�������" << endl;
		ifs.close();
		return;
	}

	//׼�������û�����Ϣ
	int id = 0;
	string name;
	string pwd;

	//�ж����
	if (type == 1)
	{
		cout << "���������ѧ��:" << endl;
		cin >> id;
	}
	else if (type == 2)
	{
		cout << "����������ְ�����:" << endl;
		cin >> id;
	}

	cout << "�������û�����" << endl;
	cin >> name;

	cout << "���������룺" << endl;
	cin >> pwd;

	if (type == 1)
	{
		//ѧ�������֤
		int fId;  //���ļ��ж�ȡ��id��
		string fName; //���ļ��л�ȡ������
		string fPwd;  //���ļ��л�ȡ������

		while (ifs >> fId && ifs >> fName && ifs >> fPwd)
		{
		/*	cout << fId << endl;   ����
			cout << fName << endl;
			cout << fPwd << endl;
			cout << endl*/;

			//���û��������Ϣ���Ա�
			if (id == fId && name == fName && pwd == fPwd)
			{
				cout << "ѧ����֤��¼�ɹ���" << endl;

				//��½�ɹ��� ������� �����Ӳ˵�
				system("pause");
				system("cls");

				person = new Student(id, name, pwd); //����ѧ���Ķ���

				//����ѧ����ݵ��Ӳ˵�
				studentMenu(person);

				return;
			}
		}
	}
	else if (type == 2)
	{
		//��ʦ�����֤
		int fId;  //���ļ��ж�ȡ��id��
		string fName; //���ļ��л�ȡ������
		string fPwd;  //���ļ��л�ȡ������

		while (ifs >> fId && ifs >> fName && ifs >> fPwd)
		{
			if (fId == id && fName == name && fPwd == pwd) 
			{
				cout << "��ʦ��֤��¼�ɹ���" << endl;

				//��½�ɹ��� ������� �����Ӳ˵�
				system("pause");
				system("cls");

				person = new Teacher(id, name, pwd);//������ʦ�Ķ���

				//�����ʦ����Ӳ˵�
				teacherMenu(person);

				return;
			}
		}
	}
	else if (type == 3)
	{
		//����Ա�����֤
		string fName;
		string fPwd;

		while (ifs >> fName && ifs >> fPwd)
		{
			if (fName == name && fPwd == pwd)
			{
				cout << "����Ա��֤��¼�ɹ���" << endl;

				//��½�ɹ��� ������� �����Ӳ˵�
				system("pause");
				system("cls");

				person = new Manager(name, pwd); //��������Ա����

				//�������Ա�Ӳ˵�
				managerMenu(person);

				return;
			}

		}
	}

	cout << "��֤��¼ʧ��" << endl;
	system("pause");
	system("cls");

	return;
}

int main()
{
	int select = 0;//���ڽ����û���ѡ��

	while (true)
	{
		cout << "=================== ��ӭ�������ǲ��ͻ���ԤԼϵͳ ================" << endl;
		cout << endl << "�������������" << endl;
		cout << "\t\t ------------------------------\n";
		cout << "\t\t|                              |\n";
		cout << "\t\t|         1��ѧ������          |\n";
		cout << "\t\t|                              |\n";
		cout << "\t\t|         2����    ʦ          |\n";
		cout << "\t\t|                              |\n";
		cout << "\t\t|         3���� �� Ա          |\n";
		cout << "\t\t|                              |\n";
		cout << "\t\t|         0����    ��          |\n";
		cout << "\t\t|                              |\n";
		cout << "\t\t ------------------------------\n";
		cout << "����������ѡ��" << endl;

		cin >> select; //�����û�����

		switch (select) //�����û�����ʵ�ֲ�ͬ�ӿ�
		{
		case 1:  //ѧ�����
			LoginIn(STUDENT_FILE, 1);
			break;
		case 2:  //��ʦ���
			LoginIn(TEACHER_FILE, 2);
			break;
		case 3:  //����Ա���
			LoginIn(ADMIN_FILE, 3);
			break;
		case 0:  //�˳�ϵͳ
			cout << "��ӭ�´�ʹ��" << endl;
			system("pause");
			return 0;
			break;
		default:
			cout << "�����������������룡" << endl;
			system("pause");
			system("cls");
			break;
			
		}
		
	}

	system("pause");
	return 0;
}
