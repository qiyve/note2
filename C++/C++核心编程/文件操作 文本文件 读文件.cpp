#include<iostream>
using namespace std;
#include<fstream> //����ͷ�ļ�
#include<string>

//�ı��ļ� ���ļ�

void test01()
{

	// 1. ����ͷ�ļ�   #include<fstream>

	// 2. ����������   ifstream ifs;
	ifstream ifs;

	//  3. ���ļ� ���ж��ļ��Ƿ�򿪳ɹ�       ifs.open("�ļ�·����,  �򿪷�ʽ)
	ifs.open("д�ļ�.txt", ios::in);

	if (!ifs.is_open()) //�ж��ļ��Ƿ�򿪳ɹ�
	{
		cout << "�ļ���ʧ��" << endl;
		return;
	}

 //  4. ������          ���ַ�ʽ��ȡ
  
	//��һ��
	//char buf[1024] = { 0 };
	//while (ifs >> buf)
	//{
	//	cout << buf << endl;
	//}

	//�ڶ���
	//char buf[1024] = { 0 };
	//while (ifs.getline(buf, sizeof(buf)))
	//{
	//	cout << buf << endl;
	//}

    //������
	//string buf;

	//while (getline(ifs, buf))
	//{
	//	cout << buf << endl;
	//}

	//������
	char c;
	while( (c=ifs.get()) !=EOF)
	{
		cout << c;
	}

 //  5. �ر��ļ�       ifs.close()��
	ifs.close();
}


int main()
{

	test01();

	system("pause");
	return 0;
}