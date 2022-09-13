#include<iostream>
using namespace std;
#include<string>    //string ͷ�ļ�
#define MAX   1000  //���ֵ1000
//�����ϵ�˽ṹ��
struct person
{
	// ����
	string m_Name;
	// �Ա�  1 ��   2Ů
	int m_Sex;
	//����
	int m_Age;
	//��ϵ�绰
	string m_Phone;
	//��ͥ��ַ
	string m_Address;
};

//���ͨѶ¼�Ľṹ��
struct Addressbooks
{
	//ͨѶ¼�б������ϵ������
	struct person personArray[MAX];

	//ͨѶ¼�е�ǰ��¼��ϵ�˸���
	int m_Size;
};
//1�������ϵ��
void addPerson(Addressbooks* ads)
{
	//�ж�ͨѶ¼�Ƿ�������������˾Ͳ������
	if (ads->m_Size == MAX)
	{
		cout << "ͨѶ¼�������޷���ӣ�" << endl;
		return;
	}
	else
	{
	    //��Ӿ�����ϵ��
		
		//����
		string name;
		cout << "����������" << endl;
		cin >> name;
		ads->personArray[ads->m_Size].m_Name = name;

		//�Ա�
		cout << "�������Ա�" << endl;
		cout << "1---��" << endl;
		cout << "2---Ů" << endl;
		int sex = 0;

		while (true)
		{
			//���������� 1 ���� 2 �����˳�ѭ������Ϊ���������ȷֵ
			//�������������������
 			cin >> sex;
			if (sex == 1 || sex == 2)
			{
				ads->personArray[ads->m_Size].m_Sex = sex;
				break;
			}
			cout << "������������������" << endl;
		}
		//����
		cout << "����������" << endl;
		int age=0;
		cin >> age;
		ads->personArray[ads->m_Size].m_Age = age;

		//�绰
		cout << "��������ϵ�绰��" << endl;
		string phone;
		cin >> phone;
		ads->personArray[ads->m_Size].m_Phone = phone;

		//��ַ
		cout << "�������ͥ��ַ " << endl;
		string address;
		cin >> address;
		ads->personArray[ads->m_Size].m_Address = address;
		
		//����ͨѶ¼����
		ads->m_Size++;

		cout << "��ӳɹ�" << endl;

	   
		system("pause"); //�밴���������
		system("cls");  // ��������
	} 
}
//2����ʾ������ϵ��
void showperson(Addressbooks* ads)
{
	//�жϵ�ǰͨѶ¼��û����Ա������ʾ��¼Ϊ��
	// ����������� 0 ��ʾͨѶ¼����Ϣ
	if (ads->m_Size == 0)
	{
		cout << "��ǰ��¼Ϊ��" << endl;
	}
	else
	{        
		for (int i = 0; i < ads->m_Size; i++)
		{
			cout << "������" << ads->personArray[i].m_Name << "\t";
			                  //������ľ����� 
			cout << "�Ա�" <<(ads->personArray[i].m_Sex == 1 ? "��" : "Ů") << "\t";
			cout << "���䣺" << ads->personArray[i].m_Age << "\t";
			cout << "�绰����" << ads->personArray[i].m_Phone << "\t";
			cout << "��ͥ��ַ" << ads->personArray[i].m_Address << endl;
		}
	}
	system("pause");// �밴���������
	system("cls");//  ����

}
//�����ϵ���Ƿ���� ������ڣ����������ϵ����ͨѶ¼�е�λ�á������ڷ��� - 1
//����1�� ͨѶ¼  ����2�� �Ա�����
int isExist(Addressbooks* ads, string name)
{
	for (int i = 0; i < ads->m_Size; i++)
	{
		//�ҵ��û������������
		if (ads->personArray[i].m_Name == name)
		{
			return i;//�ҵ��ˣ�������������������±���
		}
	}
		return -1;//�������������û�ҵ�������-1
}
//3��ɾ��ָ����ϵ��
void deleteperson(Addressbooks* ads)
{
	cout << "��������ϵ�˵�������" << endl;

	string name;
	cin >> name;

	// ret==-1  δ�鵽  
	//ret!=-1 �鵽��
	int ret=isExist(ads, name);

	if (ret != -1)
	{
      //���ҵ�����ɾ������
		for (int i = ret; i < ads->m_Size; i++)
		{
			//����ǰ��
			ads->personArray[i] = ads->personArray[i + 1];
		}
		ads->m_Size--;//����ͨѶ¼���� 
		cout << "ɾ���ɹ�" << endl;
	}
	else
	{
		cout << "���޴���" << endl;
	}
	system("pause");//�밴���������
	system("cls");//����
}

//4������ָ����ϵ����Ϣ
void findperson(Addressbooks* ads)
{
	cout << "��������Ҫ���ҵ���ϵ�ˣ�" << endl;
	string name;
	cin >> name;

	//�ж���ϵ���Ƿ����  ������ʾ����   ��������ʾ���޴���
	int ret = isExist(ads, name);

	if (ret != -1)//ret!=-1 �鵽��
	{
		//�ҵ���ϵ�� ����ӡ����
		cout << "������" << ads->personArray[ret].m_Name << "\t";
		cout << "�Ա�" << ads->personArray[ret].m_Sex << "\t";
		cout << "���䣺" << ads->personArray[ret].m_Age << "\t";
		cout << "�绰���룺" << ads->personArray[ret].m_Phone << "\t";
		cout << "��ͥ��ַ��" << ads->personArray[ret].m_Address << endl;
	}
	else// ret==-1  δ�鵽  
	{
		cout << "���޴���" << endl;
	}

	system("pause");//�����������
	system("cls");//  ����
}

//5���޸�ָ����ϵ��
void modifyperson(Addressbooks* ads)
{
	cout << "��������Ҫ�޸ĵ���ϵ�ˣ�" << endl;
	string name;
	cin >> name;
	int ret = isExist(ads, name);

	//�ж��û��������ϵ���Ƿ���� ���ڽ����޸���Ϣ  ��������ʾ���޴���
	if (ret!=-1) // �鵽��
	{
		//�޸���ϵ����Ϣ

		//����
		string name;
		cout << "������������" << endl;
		cin >> name;
		ads->personArray[ret].m_Name = name;

		//�Ա�
		cout << "�������Ա�" << endl;
		cout << "1---��" << endl;
		cout << "2---Ů" << endl;
		int sex = 0;

		while (true)
		{
			cin >> sex;
			if (sex == 1 || sex == 2)
			{
				//������ȷ �޸���Ϣ  ���˳�ѭ��
				ads->personArray[ret].m_Sex = sex;
				break;
			}
			else
			{
				cout << "�����������������룺" << endl;
			}
		}

		//���� 
		int age= 0;
		cout << "���������䣺" << endl;
		cin >> age;
		ads->personArray[ret].m_Age = age;
	 
		// ��ϵ�绰
		cout << "��������ϵ�绰��" << endl;
		string phone;
		cin >> phone;
		ads->personArray[ret].m_Phone = phone;

		// ��ͥ��ַ
		cout << "�������ͥ��ַ��" << endl;
		string address;
		cin >> address;
		ads->personArray[ret].m_Address = address;

	}
	else
	{   // ret== -1 δ�鵽
		cout << "���޴���" << endl;
	}

	system("pause"); //�����������
	system("cls");  //����

}

//6�������ϵ��
void cleanperson(Addressbooks*ads)
{
	//��ͨѶ¼������ϵ����Ϣ�������ֻҪ��ͨѶ¼��¼����ϵ��������Ϊ0��
	ads->m_Size = 0;
	cout << "ͨѶ¼�����" << endl;

	system("pause");//�����������
	system("cls");  //����
}

//�˵�����
void showMenu()
{
	cout << "***********************" << endl;
	cout << "*****1�������ϵ��*****" << endl;
	cout << "*****2����ʾ��ϵ��*****" << endl;
	cout << "*****3��ɾ����ϵ��*****" << endl;
	cout << "*****4��������ϵ��*****" << endl;
	cout << "*****5���޸���ϵ��*****" << endl;
	cout << "*****6�������ϵ��*****" << endl;
	cout << "*****0���˳�ͨѶ¼*****" << endl;
	cout << "***********************" << endl;
}

int main()
{
	//����ͨѶ¼�ṹ�����
	Addressbooks ads;
	//��ʼ��ͨѶ¼�е�ǰ��Ա����
	ads.m_Size = 0;

	int select = 0; //�����û�ѡ������ı���
	//����һ��ѭ�� 
	while (true)
	{
		//�˵�����
		showMenu();
		
		cin >> select; //�����û���������

		switch (select)
		{
		case 1://�����ϵ��
			addPerson(&ads);//���õ�ַ���� ����ʵ��
			break;

		case 2://��ʾ��ϵ��
			showperson(&ads);
			break;

		case 3://ɾ����ϵ��
			deleteperson(&ads);
			break;

		case 4://������ϵ��
			findperson(&ads);
			break;

		case 5://�޸���ϵ��
			modifyperson(&ads);
			break;

		case 6://�����ϵ��
			cleanperson(&ads);
			break;

		case 0://�˳�ͨѶ¼
			cout << "��ӭ�´�ʹ��" << endl;

			system("pause");
			return 0;
			break;
		default:
			break;
		}
	}

	system("pause");
	return 0;
}





