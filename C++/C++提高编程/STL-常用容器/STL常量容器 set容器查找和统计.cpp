#include<iostream>
using namespace std;
#include<set>

//set����  ���Һ�ͳ��


//find(key);            //����key�Ƿ���ڣ����ظü���Ԫ�صĵ��������������ڣ�����set.end()��
//count(key);           //ͳ��key��Ԫ�ظ���



//��С
void test01()
{
	//����
	set<int>s1;
	
	//��������  ֻ��insert��ʽ
	s1.insert(10);
	s1.insert(40);
	s1.insert(20);
	s1.insert(30);

	set<int>::iterator pos = s1.find(50);

	if (pos != s1.end())//�ж��������ֵ ������end ���ҵ���Ԫ�� 
	{
		cout << "�ҵ�Ԫ��" << *pos << endl;
	}
	else
	{
		cout << "δ�ҵ�Ԫ��" << endl;
	}
}

//ͳ��
void test02()
{
	set<int>s;
	s.insert(10);
	s.insert(30);
	s.insert(20);
	s.insert(40);
	s.insert(30);
	s.insert(30);


	//ͳ��30�ĸ���   //set�����в��������ظ���Ԫ��
	int num1 = s.count(30);
	cout << "num1 = " << num1 << endl;

	int num2 = s.count(300);
	cout << "num2 = " << num2 << endl;
}

int main()
{
	//test01();
	
	test02();

	system("pause");
	return 0;
}