#include"Student.h"

//Ĭ�Ϲ���
Student::Student()
{

}

//�вι���  ������ѧ�� ���� ����
Student::Student(int id, string name, string pwd)
{
	//��ʼ����
	this->m_Id = id;
	this->m_Name = name;
	this->m_Pwd = pwd;

	//��ȡ������Ϣ
	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);

	ComputerRoom c;
	while (ifs >> c.m_ComId && ifs >> c.m_MaxNum)
	{
		vCom.push_back(c);
	}
	ifs.close();
	

}

//�˵�����
void Student::operMenu()
{
	cout << "��ӭѧ������:" << this->m_Name << "��¼��" << endl;
	cout << "\t\t -------------------------------\n";
	cout << "\t\t|                               |\n";
	cout << "\t\t|         1������ԤԼ           |\n";
	cout << "\t\t|                               |\n";
	cout << "\t\t|         2���鿴�ҵ�ԤԼ       |\n";
	cout << "\t\t|                               |\n";
	cout << "\t\t|         3���鿴����ԤԼ       |\n";
	cout << "\t\t|                               |\n";
	cout << "\t\t|         4��ȡ��ԤԼ           |\n";
	cout << "\t\t|                               |\n";
	cout << "\t\t|         0��ע����¼           |\n";
	cout << "\t\t|                               |\n";
	cout << "\t\t -------------------------------\n";
	cout << "��ѡ�����Ĳ���" << endl;

}

//����ԤԼ
void Student::applyOrder()
{
	int date = 0;  //�����û�ѡ�������
	int interval = 0; //�����û�ѡ���ʱ���
	int room = 0;//�û�ѡ�񼸺Ż���

	cout << "��������ʱ��Ϊ��һ����!" << endl;
	cout << "����������ԤԼ��ʱ�䣺" << endl;
	cout << "1����һ" << endl;
	cout << "2���ܶ�" << endl;
	cout << "3������" << endl;
	cout << "4������" << endl;
	cout << "5������" << endl;


	while (true)  //ѡ���ܼ�
	{
		cin >> date;
		//�޶���СΪ1 ���Ϊ5
		if (date >= 1 && date <= 5)
		{
			break;
		}
		cout << "������������������" << endl;
	}

	cout << "����������ԤԼ��ʱ���" << endl;
	cout << "1������" << endl;
	cout << "2������" << endl;

	while (true) //ѡ�����������
	{
		cin >> interval;
		//�޶���СΪ1 ���Ϊ2
		if (interval >= 1 && interval <= 2)
		{
			break;
		}
		cout << "������������������" << endl;
	}

	//cout << "����������ԤԼ�Ļ���" << endl;
	//cout << "1��һ�Ż���������" << vCom[0].m_MaxNum << "��" << endl;
	//cout << "2�����Ż���������" << vCom[1].m_MaxNum << "��" << endl;
	//cout << "3�����Ż���������" << vCom[2].m_MaxNum << "��" << endl;
	cout << "��ѡ�����" << endl;
	for (int i = 0;i < vCom.size(); i++)
	{
		cout << vCom[i].m_ComId << "�Ż�������Ϊ��" << vCom[i].m_MaxNum << endl;
	}

	while (true) //ѡ�����
	{
		cin >> room;
		//�޶���СΪ1 ���Ϊ3
		if (room >= 1 && room <= 3)
		{
			break;
		}
		cout << "������������������" << endl;
	}

	cout << "ԤԼ�ɹ�,�����" << endl;

	ofstream ofs(ORDER_FILE, ios::app);//����׷�ӷ�ʽд�ļ�
	ofs << "date:" << date << " ";              //����
	ofs << "interval:" << interval << " ";      //ʱ���
	ofs << "stuId:" << this->m_Id << " ";       //ѧ��id
	ofs << "stuName:" << this->m_Name << " ";   //ѧ������
	ofs << "roomId:" << room << " ";            //�������
	ofs << "status:" << 1 << endl;              //1�������״̬

	ofs.close();

	::system("pause");
	system("cls");

}

//�鿴����ԤԼ
void Student::showMyOrder()
{
	OrderFile of;
	//of.updateOrder();

	if (of.m_Size == 0)
	{
		cout << "��ԤԼ��¼!" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0; i < of.m_Size; i++)
	{ 
		//string  ת  int
		//string  ���� .c_str  ת  const char *
		//���� atoi( const char *) תint
	
		//cout <<"ѧ����ţ�"<<of.m_orderData[i]["stuId"] << endl;

		if (this->m_Id == atoi(of.m_orderData[i]["stuId"].c_str()))//�ҵ�����ԤԼ
		{
			cout << "ԤԼ�����ڣ���" << of.m_orderData[i]["date"];
			cout << " ʱ��Σ�" << (of.m_orderData[i]["interval"] == "1" ? "����" : "����");
			cout << " ������:" << of.m_orderData[i]["roomId"];

			string status = " ״̬:";
			//1�������  2��ԤԼ�ɹ� -1��ԤԼʧ��  0��ȡ��ԤԼ
			if (of.m_orderData[i]["status"] == "1")
			{
				status += "�����";
			}
			else if (of.m_orderData[i]["status"] == "2")
			{
				status += "ԤԼ�ɹ�";
			}
			else if (of.m_orderData[i]["status"] == "-1")
			{
				status += "ԤԼʧ�ܣ����δͨ��";
			}
			else
			{
				status += "ԤԼ��ȡ��";
			}
			cout << status << endl;
		}
	}

	system("pause");
	system("cls");
}

//�鿴����ԤԼ
void Student::showAllOrder()
{
	OrderFile of; //��������

	if (of.m_Size == 0)
	{
		cout << "��ԤԼ��¼" << endl;
		system("pause");
		system("cls");
		return;
	}

	//��������
	for (int i = 0; i < of.m_Size; i++)
	{
		cout << i + 1 << "��";  //ƴ����ʾ�ڼ���ԤԼ


		cout << "ԤԼ���ڣ���" << of.m_orderData[i]["date"];
		cout << " ʱ��Σ�" << (of.m_orderData[i]["interval"] == "1" ? "����" : "����");
		cout << " ѧ�ţ�" << of.m_orderData[i]["stuId"];
		cout << " ������" << of.m_orderData[i]["stuName"];
		cout << " �����ţ�" << of.m_orderData[i]["roomId"];
		
		//1�������  2��ԤԼ�ɹ� -1��ԤԼʧ��  0��ȡ��ԤԼ
		string status = " ״̬��";

		if (of.m_orderData[i]["status"] == "1")
		{
			status += "�����";
	    }

		else if (of.m_orderData[i]["status"] == "2")
		{
			status += "ԤԼͨ��";
		}	

		else if (of.m_orderData[i]["status"] == "-1")
		{
			status += "ԤԼʧ�ܣ����δͨ��";
		}	

		else
		{
			status += "ԤԼ��ȡ��";
		}

		cout << status << endl;
	
	}

	system("pause");
	system("cls");

}

//ȡ��ԤԼ
void Student::cancelOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "ԤԼ��¼Ϊ��!" << endl;
		system("pause");
		system("cls");
		return;
	}

	cout << "����л�ԤԼ�ɹ��ļ�¼����ȡ����������ȡ���ļ�¼" << endl;
	vector<int>v; //���������������±���
	int index = 1; 
	
	for (int i = 0; i < of.m_Size; i++)
	{
		//���ж�����ѧ�� 
		if (this->m_Id == atoi(of.m_orderData[i]["stuId"].c_str()))
		{
			//��ɸѡ״̬  ����л�ԤԼ�ɹ�
			if (of.m_orderData[i]["status"] == "1" || of.m_orderData[i]["status"] == "2")
			{
				v.push_back(i);
				cout << index++ <<"��" << endl; //��ʾ�û��ڼ�����¼
				cout << "ԤԼ�����ڣ���" << of.m_orderData[i]["date"];
				cout << " ʱ��Σ�" << (of.m_orderData[i]["interval"] == "1" ? "����" : "����");
				cout << " �����ţ�" << of.m_orderData[i]["roomId"];

				string status = " ״̬��";
				if (of.m_orderData[i]["status"] == "1")
				{
					status += "�����";
				}
				else if (of.m_orderData[i]["status"] == "2")
				{
					status += "ԤԼ�ɹ�";
				}
				cout << status << endl;
			}
		}
	}
	//��ʼȡ��ԤԼ
	cout << "������ȡ���ļ�¼,0������" << endl;
	int select = 0;
	
	while (true)
	{
		cin >> select;
	
		if (select >= 0 && select <= v.size())
		{
			if (select == 0)
			{
				break;
			}
			else
			{
				//�±� = �û������ select-1   ��Ϊ0 ȡ��ԤԼ
				of.m_orderData[v[select - 1]]["status"] = "0";

				of.updateOrder(); //�����ļ�

				cout << "��ȡ��ԤԼ��" << endl;
				break;
			}

		}
		
		cout << "������������������" << endl;
	}

	system("pause");
	system("cls");
}