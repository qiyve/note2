#include"Manager.h"

//Ĭ�Ϲ���
Manager::Manager()
{

}

//�вι���
Manager::Manager(string name, string pwd)
{
	//��ʼ������Ա��Ϣ
	this->m_Name = name;
	this->m_Pwd = pwd;

	//��ʼ������  ��ȡ�������ļ��� ѧ������ʦ����Ϣ
	this->initVector();

	//��ȡ������Ϣ
	this->initComputer();

	//ifstream ifs;
	//ifs.open(COMPUTER_FILE, ios::in);  //���ļ�
	//ComputerRoom c;
	//while (ifs >> c.m_ComId && ifs >> c.m_MaxNum)
	//{
	//	vCom.push_back(c); //��������
	//}
	//cout << "��ǰ����������" << vCom.size() << endl;
	//ifs.close(); //�ر��ļ�
}

//�˵�����
void Manager::operMenu()
{
	cout << "��ӭ����Ա:" << this->m_Name << "��¼��" << endl;
	cout << "\t\t-------------------------------\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|         1������˺�          |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|         2���鿴�˺�          |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|         3���鿴����          |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|         4�����ԤԼ          |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|         0��ע����¼          |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t-------------------------------\n";
	cout << "��ѡ�����Ĳ���" << endl;
}

//����˺�
void Manager::addPerson()
{
	cout << "��ѡ������˺ŵ�����" << endl;
	cout << "1�����ѧ��" << endl;
	cout << "2����ӽ�ʦ" << endl;

	string fileName;  //�����ļ���
	string tip;       //��ʾid��
	string errorTip;  //�ظ�������ʾ

	ofstream ofs;   //�ļ���������

	int select = 0;
	cin >> select; //�����û�ѡ��

	while (true)
	{
		if (select == 1)
		{
			//��ӵ���ѧ��
			fileName = STUDENT_FILE;
			tip = "������ѧ�ţ�";
			errorTip = "ѧ���ظ�������������";
			break;
		}
		else if (select == 2) 
		{
			//��ӵ���ʦ
			fileName = TEACHER_FILE;
			tip = "������ְ����ţ�";
			errorTip = "ְ������ظ�������������";
			break;
		}
		else
		{
			cout << "������������������" << endl;
			system("pause");
			system("cls");
			return;
		}
	}

	//����׷�ӵķ�ʽ д�ļ�
	ofs.open(fileName, ios::out | ios::app);

	int id;  //ѧ�� /ְ����
	string name; //����
	string pwd;  //����

	cout << tip << endl;

	while (true)  //���id�Ƿ��ظ�
	{
		cin >> id;
		bool ret = checkRepeat(id, select);
		if (ret) //���ظ�
		{
			cout << errorTip << endl;
		}
		else
		{
			break;
		}
	}

	cout << "������������" << endl;
	cin >> name;

	cout << "���������룺" << endl;
	cin >> pwd;

	//���ļ����������
	ofs << id << " " << name << " " << pwd << " " << endl;
	cout << "��ӳɹ�" << endl;

	system("pause");
	system("cls");

	ofs.close(); //�ر��ļ�

	//���ó�ʼ�������Ľӿڣ����»�ȡ�ļ��е�����
	this->initVector();

}

//��ӡѧ����Ϣ
void printStudent(Student& s)
{
	cout << " ѧ�ţ�" << s.m_Id << " ������" << s.m_Name 
		 << " ���룺" << s.m_Pwd << endl;
}

//��ӡ��ʦ��Ϣ
void printTeacher(Teacher& t)
{
	cout << "ְ����ţ�" << t.m_EmpId << " ������" << t.m_Name
		 << " ���룺" << t.m_Pwd << endl;
}

//�鿴�˺�
void Manager::showPerson()
{
	cout << "��ѡ��鿴����" << endl;
	cout << "1���鿴����ѧ��" << endl;
	cout << "2���鿴���н�ʦ" << endl;

	int select = 0;

	cin >> select;  //�����û�ѡ��

	if (select == 1)
	{
		//��ʾѧ����Ϣ
		cout << "����ѧ����Ϣ���£�" << endl;
		for_each(vStu.begin(), vStu.end(), printStudent);
		
	}
	else if (select == 2)
	{
		//��ʾ��ʦ��Ϣ
		cout << "���н�ʦ��Ϣ���£�" << endl;
		for_each(vTea.begin(), vTea.end(), printTeacher);
		
	}
	else
	{
		cout << "���������������" << endl;
		system("pause");
		system("cls");
		return;
	}

	system("pause");
	system("cls");

}

//�鿴������Ϣ
void Manager::showComputer()
{
	cout << "������Ϣ���£�" << endl;
	for (vector<ComputerRoom>::iterator it = vCom.begin(); it != vCom.end(); it++)
	{
		cout << "������ţ�" << it->m_ComId <<"��"
			<< " ����������" << (*it).m_MaxNum << "��" << endl;
	}
	system("pause");
	system("cls");
	
}

//��ջ�������
void Manager::cleanFile()
{
	cout << "�Ƿ�ȷ����գ�" << endl;
	cout << "1���� " << endl;
	cout << "2���� " << endl; 

	int select = 0;
	cin >> select;

	if (select == 1)
	{
		ofstream ofs(ORDER_FILE, ios::trunc);
		ofs.close();

		cout << "��ճɹ�" << endl;
	}

	system("pause");
	system("cls");
}


//��ʼ������
void Manager::initVector()
{
	//ȷ���������״̬
	vStu.clear();
	vTea.clear();

	//��ȡ��Ϣ ѧ��
	ifstream ifs;

	ifs.open(STUDENT_FILE, ios::in); //���ļ�

	if (!ifs.is_open())
	{
		cout << "�ļ���ȡʧ��" << endl;
		return;
	}

	Student s;  //��������

	while (ifs >> s.m_Id && ifs >> s.m_Name && ifs >> s.m_Pwd)
	{
		vStu.push_back(s);
	}
	//cout << "��ǰѧ������Ϊ��" << vStu.size() << endl;
	ifs.close();


	//��ȡ��Ϣ ��ʦ
	ifs.open(TEACHER_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "�ļ���ȡʧ��" << endl;
		return;
	}

	Teacher t;

	while (ifs >> t.m_EmpId && ifs >> t.m_Name && ifs >> t.m_Pwd)
	{
		vTea.push_back(t);
	}
	//cout << "��ǰ��ʦ������Ϊ��" << vTea.size() << endl;
	ifs.close();

}

//����ظ� ����1�����ѧ��/ְ����  ����2���������
bool Manager::checkRepeat(int id, int type)
{
	if (type == 1)
	{
		//���ѧ��
		for (vector<Student>::iterator it = vStu.begin(); it != vStu.end(); it++)
		{
			if (id == it->m_Id)
			{
				return true;
			}
		}
	}
	else
	{
		//�����ʦ
		for (vector<Teacher>::iterator it = vTea.begin(); it != vTea.end(); it++)
		{
			if (id == it->m_EmpId)
			{
				return true;
			}
		}
	}

	return false;
}

//��ʼ����������
void Manager::initComputer()
{
	vCom.clear(); //ȷ������Ϊ���״̬

	//ifstream ifs(COMPUTER_FILE, ios::in);
	ifstream ifs;

	ifs.open(COMPUTER_FILE, ios::in);

	ComputerRoom c;

	while (ifs >> c.m_ComId && ifs >> c.m_MaxNum)
	{
		vCom.push_back(c);
	}
	ifs.close();

	cout << "��ǰ����������" << vCom.size() << endl;
}