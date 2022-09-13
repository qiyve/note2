#include"workerManager.h"


//���캯��
WorkerManager::WorkerManager()
{

	//1���ļ�������
	ifstream ifs;
	ifs.open(FILENAME, ios::in); //���ļ�

	if (!ifs.is_open())
	{
		//��ʼ������
		
		//��ʼ����¼����
		this->m_EmpNum = 0;
		//��ʼ������ָ��
		this->m_EmpArray = NULL;
		//��ʼ���ļ��Ƿ�Ϊ��
		this->m_FileIsEmpty = true;

		ifs.close();//�ر��ļ�
		return;
	}
	//2. �ļ����ڣ�����Ϊ��
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//�ļ�Ϊ��

		//��ʼ����¼����
		this->m_EmpNum = 0;
		//��ʼ������ָ��
		this->m_EmpArray = NULL;
		//��ʼ���ļ��Ƿ�Ϊ��
		this->m_FileIsEmpty = true;

		ifs.close();//�ر��ļ�
		return;
	}

	//3�����ļ����ڣ����Ҽ�¼����
	int num = this->get_EmpNum();
    //cout << "ְ������Ϊ��" << num << endl;
	this->m_EmpNum = num; // ���³�Ա����

	//���ٿռ�
	this->m_EmpArray = new Worker * [this->m_EmpNum];
	//���ļ��е����ݣ��浽������
	init_Emp();


}

//�˵�����ʵ��
//��ʾ�˵�
void WorkerManager::Show_Menu()
{

	cout << "**************************************" << endl;
	cout << "*******  ��ӭʹ��ְ������ϵͳ!  ******" << endl;
	cout << "***********0���˳�������� ***********" << endl;
	cout << "***********1������ְ����Ϣ ***********" << endl;
	cout << "***********2����ʾְ����Ϣ ***********" << endl;
	cout << "***********3��ɾ����ְְ�� ***********" << endl;
	cout << "***********4���޸�ְ����Ϣ ***********" << endl;
	cout << "***********5������ְ����Ϣ ***********" << endl;
	cout << "***********6�����ձ������ ***********" << endl;
	cout << "***********7����������ĵ� ***********" << endl;
	cout << "**************************************" << endl;

	cout << endl;
}

//�˳�ϵͳ
void WorkerManager::exitSystem()
{
	cout << "��ӭ�´�ʹ��" << endl;

	system("pause");//�밴���������

	exit(0);
}

//��ӹ��ܺ���
void WorkerManager::Add_Emp()
{
	cout << "���������ְ��������:" << endl;

	int addNum = 0;//����������������
	cin >> addNum;

	if (addNum > 0)//�ж��Ƿ���Ч����
	{
		//���
		//��������¿ռ��С
		int newSize = this->m_EmpNum + addNum;//�¿ռ����� = ԭ����¼������ + ��������

		//���ٿռ�
		Worker** newSpace= new Worker * [newSize];

		//��ԭ���Ŀռ������ݣ��������¿ռ���
		if (this->m_EmpArray!= NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}

		//���������
		for (int i = 0; i < addNum; i++)
		{
			int id;//ְ�����
			string name;//ְ������
			int dSelect;//����ѡ��


			cout << "������� " << i + 1 << " ����ְ�����" << endl;
			cin >> id;

			cout << "������� " << i + 1 << " ����ְ������" << endl;
			cin >> name;

			cout << "��ѡ���ְ���ĸ�λ " << endl;
			cout << "1����ְͨ��" << endl;
			cout << "2������" << endl;
			cout << "3���ϰ�" << endl;
			cin >> dSelect;

			Worker* worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(id, name, 1);
				break;
			case 2:
				worker = new Manager(id, name, 2);
				break;
			case 3:
				worker = new Boos(id, name, 3);
				break;
			default:
				break;
			}
			//��������ְ��ָ�룬���浽������
			newSpace[this->m_EmpNum + i] = worker;

		}
		
		//�ͷ�ԭ�пռ�
		delete[]this->m_EmpArray;

		//�����¿ռ��ָ��
		this->m_EmpArray = newSpace;

		//�����µ�ְ������
		this->m_EmpNum = newSize;

		//����ְ����Ϊ�յı�־
		this->m_FileIsEmpty = false;

		//��ʾ��ӳɹ�
		cout << "�ɹ����" << addNum << "����ְ����" << endl;

		//����ְ����Ϣ
		this->Save();
	}
	else
	{    
		cout << "������������" << endl;
	}

	//��������� �����ص��ϼ�Ŀ¼
	system("pause");
	system("cls");

}

//�����ļ�
void WorkerManager:: Save()
{
	ofstream ofs; //����������
	ofs.open(FILENAME, ios::out);//���ļ�

	//��������
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_Id << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_DeptID << " " << endl;
	}

	ofs.close();//�ر��ļ�
}


//ͳ���ļ�������
int WorkerManager:: get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);//���ļ�    ���ļ�

	int id;
	string name;
	int dId;

	int num = 0;

	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		//��¼����
		num++;
	}
	ifs.close();

	return num;
}

//��ʼ��Ա��
void WorkerManager::init_Emp()
{
	ifstream ifs; 
	ifs.open(FILENAME, ios::in);//���ļ� ���ļ�

		int id;
		string name;
		int dId;

		int index = 0;

		//���ݲ���id ������ͬ�Ķ���
		while (ifs>>id && ifs>>name && ifs>>dId)
		{
			Worker* worker = NULL;

			if (dId == 1)//��ͨԱ��
			{
				worker = new Employee(id, name, dId);
			}
			else if (dId == 2)	//����
			{
				worker = new Manager(id, name, dId);
			}
			else//�ϰ�
			{
				worker = new Boos(id, name, dId);
			}
			//�����������
			this->m_EmpArray[index] = worker;
			index++;
			
		}
		
}

//��ʾְ��
void WorkerManager::Show_Emp()
{
	//�ж��ļ��Ƿ�Ϊ��
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
	}
	else
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			//���ö�̬���ó���ӿ�
			this->m_EmpArray[i]->ShowInfo();
		}
	}
	//����������� ����
	system("pause");
	system("cls");

}

//ɾ��ְ��
void WorkerManager::Del_Emp()
{
	//�ж��ļ��Ƿ����
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
	}
	else
	{
		//����ְ�����ɾ��ְ��
		cout << "��������Ҫɾ����ְ�����" << endl;
		int id = 0;
		cin >> id;
	
		int index = this->IsExist(id);

		if (index != -1)//˵��ְ�����ڣ�����Ҫɾ�� indexλ���ϵ�ְ��
		{
			//����ǰ��
			for (int i = index; i < this->m_EmpNum - 1; i++)
			{
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}

			cout << "ɾ���ɹ�" << endl;
			this->m_EmpNum--;//���¼�¼����
			this->Save();//ͬ�����ļ���
		}
		else
		{
			cout << "ɾ��ʧ�ܣ�δ�ҵ���ְ��" << endl;
		}
	}
	//�����������  ��������
	system("pause");
	system("cls");

}


//�ж�ְ���Ƿ����
int  WorkerManager::IsExist(int id)
{
	int index = -1;//Ĭ�ϲ�����

	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpArray[i]->m_Id == id)
		{
			//�ҵ�ְ��  ���˳�ѭ��
			index = i;
			break;
		}
	}

	return index;
}

//�޸�ְ��
void WorkerManager::Mod_Emp()
{
	//���ж��ļ��Ƿ����
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
	}
	else
	{
		//����ְ������޸�ְ����Ϣ
		cout << "��������Ҫ�޸ĵ�ְ�����" << endl;
		int id;//�����û�����
		cin >> id;

		//�ж�ְ���Ƿ����

		int ret = this->IsExist(id);
		if (ret != -1)
		{
			//���ҵ���ŵ�ְ��

			delete this->m_EmpArray[ret];//���ͷ�ԭ������

			int newId = 0;
			string newName = "";
			int dSelect = 0;

			cout << "�鵽 ��" << id << "��ְ������������ְ�����" << endl;
			cin >> newId;

			cout << "������Ҫ�޸ĵ�����" << endl;
			cin >> newName;

			cout << "�������µĸ�λ" << endl;
			cout << "1����ͨԱ��" << endl;
			cout << "2������" << endl;
			cout << "3���ϰ�" << endl;

			cin >> dSelect;

			Worker* worker = NULL;

			switch (dSelect)
			{
			case 1:  //��ͨԱ��
				worker = new Employee(newId, newName, dSelect);
				break;
			case 2:  //����
				worker = new Manager(newId, newName, dSelect);
				break;
			case 3:  //�ϰ�
				worker = new Boos(newId, newName, dSelect);
				break;

			default:
				break;
			}

			//�������� ��������
			this->m_EmpArray[ret] = worker;

			cout << "�޸ĳɹ�" << endl;

			//���浽�ļ���
			this->Save();

		}
		else
		{
			cout << "�޸�ʧ�ܣ�δ�ҵ���ְ��" << endl;
		}
	}

	system("pause");
	system("cls");//����

}

//����ְ��
void WorkerManager::Find_Emp()
{
	//���ж��ļ��Ƿ����
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
    }
	else
	{
		//��ʾ�û������ֲ��ҷ�ʽ

		cout << "��ѡ����Ҫ���ҵķ�ʽ" << endl;
		cout << "1��ͨ��ְ����Ų���" << endl;
		cout << "2��ͨ��ְ����������" << endl;
		
		int select = 0;//�û�ѡ��
		cin >> select;

		if (select == 1)//��ְ����Ų���
		{
			int id;
			cout << "��������ҵ�ְ�����" << endl;//��ʾ�û�
			cin >> id;

			int ret = IsExist(id);
			if (ret != -1)
			{
				 //�ҵ�ְ��
				cout << "���ҳɹ�����ְ����Ϣ���£�" << endl;
				this->m_EmpArray[ret]->ShowInfo();//����չʾ��Ϣ����
			}
			else
			{
				cout << "����ʧ�ܣ�δ�ҵ���ְ��" << endl;
			}
		}
		//����������
		else if (select == 2)
		{
			string name;
			cout << "��������ҵ�ְ������" << endl;
			cin >> name;

			//�����ж��Ƿ���ҵ��ı�־
			bool flag = false;//Ĭ��δ�ҵ�ְ��
			
			for (int i = 0; i < m_EmpNum; i++)
			{
				//�ж��Ƿ��и�������ְ��
				if (this->m_EmpArray[i]->m_Name == name)
				{
					cout << "���ҳɹ���ְ�����Ϊ��"
						<<this->m_EmpArray[i]->m_Id
						<<"�ŵ���Ϣ����"<< endl;
				
					flag = true;

					//������ʾ��Ϣ�ӿ�
					this->m_EmpArray[i]->ShowInfo();
					
				}
			}
			if (flag == false)
			{
				//���޴���
				cout << "δ�ҵ���������ְ��" << endl;
			}
		}
		else 
		{
			cout << "������������������" << endl;
		}
	}
	

	system("pause");
	system("cls");//����
}

//ְ������
void WorkerManager::Sort_Emp()
{
	//���ж��ļ��Ƿ����
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ�����Ϊ��" << endl;

		system("pause");//����������� ������
		system("cls");
	}
	else
	{
		//��ʾ�û����������򷽷�
		cout << "��ѡ������ķ�ʽ" << endl;
		cout << "1����ְ���������" << endl;
		cout << "2����ְ����Ž���" << endl;

		int select = 0;
		cin >> select;
		for (int i = 0; i < m_EmpNum; i++)
		{
			int minOMax = i;//������Сֵ �� ���ֵ�±�
			for (int j = i + 1; j < this->m_EmpNum; j++)
			{
			   if (select == 1)//����
			   {
				
					if (this->m_EmpArray[minOMax]->m_Id > this->m_EmpArray[j]->m_Id)
					{
						//����϶�����Сֵ�±� min0Max > j �±�  ������Сֵ�±�
						minOMax = j;
					}
			   }
			   else //����
			   {
				   if (this->m_EmpArray[minOMax]->m_Id < this->m_EmpArray[j]->m_Id)
				   {
					   //����϶������ֵ�±� min0Max < j �±�  �������ֵ�±�
					   minOMax = j;
				   }
			   }
			}

			/*�ж�һ��ʼ�϶��� ��Сֵ�����ֵ �ǲ��Ǽ���� ��Сֵ�����ֵ
			 ������ǽ�������*/
			if (i != minOMax)
			{
				Worker* temp = this->m_EmpArray[i];
				this->m_EmpArray[i] = this->m_EmpArray[minOMax];
				this->m_EmpArray[minOMax] = temp;
			}
	    }
	}
	cout << "����ɹ�,�����Ľ��Ϊ: " << endl;
	this->Save();//����������浽�ļ���

	this->Show_Emp();//���ýӿ���ʾ��Ա
}

//����ļ�
void WorkerManager::Cleam_File()
{
	//��ʾ�û��Ƿ�ȷ������ļ�
	cout << "��ȷ���ļ��Ƿ���գ�" << endl;
	cout << "1��ȷ��" << endl;
	cout << "2���˳�" << endl;

	int select = 0;
	cin >> select;

	if (select == 1)
	{
	   //����ļ�
		ofstream ofs(FILENAME, ios::trunc);  //ɾ���ļ������´���
		ofs.close();//�ر��ļ�

		if (this->m_EmpArray != NULL)
		{
			//ɾ��������ÿ������
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				delete this->m_EmpArray[i];
				this->m_EmpArray == NULL;
			}

			//ɾ����������ָ��
			delete[]this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_EmpNum = 0;
			this->m_FileIsEmpty = true;
		}
	
		cout << "��ճɹ�" << endl;
	}

	system("pause");
	system("cls");

}

//��������
WorkerManager::~WorkerManager()
{
	  //�ж������Ƿ�Ϊ�� ��Ϊ�հ����ͷŵ�  �����ڴ��ֶ��ͷ�
	if (this->m_EmpArray != NULL)
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			if (this->m_EmpArray[i] != NULL)
			{
				delete this->m_EmpArray[i];
			}
		
		}
		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;
	}

}
