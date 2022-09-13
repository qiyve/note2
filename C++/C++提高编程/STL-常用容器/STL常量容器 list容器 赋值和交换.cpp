#include<iostream>
using namespace std;
#include<list>

//list���� ��ֵ�ͽ���

//assign(beg, end);     //����beg ��eng�������е����ݿ�����ֵ������
//assign(n, elem);      //��n��elem������ֵ������
//list& operator=��const list& lst���� //���صȺŲ���Ա
//swap��lst����            //��lst�뱾���Ԫ�ػ���

void printList(const list<int>&L)
{    //�޶�ֻ��
	for (list<int>::const_iterator it = L.begin(); it != L.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}

//��ֵ
void test01()
{
	list<int>L1; 

	//�������
	L1.push_back(10);
	L1.push_back(20);
	L1.push_back(30);
	L1.push_back(40);

	printList(L1);

	//operator= ��ֵ
	list<int>L2;
	L2 = L1;
	printList(L2);

	//assign ���丳ֵ
	list<int>L3;
	L3.assign(L2.begin(), L2.end());
	printList(L3);

	//assign n��elem
	list<int>L4;
	L4.assign(5, 100);
	printList(L4);

	
}

//����
void test02()
{
	list<int>L1;

	L1.push_back(10);
	L1.push_back(20);
	L1.push_back(30);
	L1.push_back(40);

	list<int>L2;
	L2.assign(5, 100);
	cout << "����ǰ��" << endl;
	printList(L1);
	printList(L2);

	cout << "������" << endl;
	L2.swap(L1);
	printList(L1);
	printList(L2);


}


int main()
{
	//test01();
	
	test02();

	system("pause");
	return 0;
}