#include<iostream>
using namespace std;

//1��new�Ļ����﷨
int *func()
{
	//�ڶ�������һ����������
	//new���ص��� ���������͵�ָ��
	int*p=new int(10);
	return p;
}

void test01()
{
	int* p = func();

	cout << *p << endl;
	cout << *p << endl;
	cout << *p << endl;

	//���������� �ɳ���Ա�����٣�����Ա�����ͷ�
	//������ͷŶ��������ݣ����ùؼ��� delete 
	delete p;

	//cout << *p << endl; //�ڴ��Ѿ����ͷţ��ٴη��ʾ��ǷǷ��������ᱨ��
}
//2���ڶ�������new��������
void test02()
{
	//����10�����ε����飬�ڶ���.   ��������Ҫ�� []
	int* arr = new int [10]; //[10]������������10��Ԫ��

	for (int i = 0; i < 10; i++)
	{
		arr[i] = i + 10;//��10��Ԫ�ظ�ֵ 10~19
	}
	for (int i = 0; i < 10; i++)
	{
		cout << arr[i] << endl;
	}

   //�ͷŶ�������
	//�ͷ������ʱ��Ҫ��[]�ſ���
	delete []arr; 
}

int main()
{
	//����
	test01();

	//����
	test02();


	system("pause");
	return 0;
}