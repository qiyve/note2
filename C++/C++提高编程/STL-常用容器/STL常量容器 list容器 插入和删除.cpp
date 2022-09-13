#include<iostream>
using namespace std;
#include<list>

//list���� �����ɾ��

//���˲���
//push_back(elem);         //������β������һ��Ԫ��
//pop_back();              //ɾ�����������һ��Ԫ��
//push_front(elem)��       //��������ͷ����һ��Ԫ��
//pop_front();             //��������ͷ�Ƴ���һ��Ԫ��

//ָ������
//insert(pos, elem);       //������posλ�ò�elemԪ�صĿ��������������ݵ�λ��
//insert(pos, n, elem);    //������posλ�ò�n��elem���ݣ��޷���ֵ
//insert(pos, beg, end);   //��posλ�ò��루beg �� end����������ݣ��޷���ֵ

//ָ��ɾ��
//clear( )��               //�Ƴ���������������
//erase��beg, end��;       //ɾ����beg �� end����������ݣ�������һ�����ݵ�λ��
//erase(pos);              //ɾ��posλ�õ����ݣ�������һ�����ݵ�λ��
//remove(elem);            //ɾ��������������elemֵƥ���Ԫ��

void printList(const list<int>&L)
{    //�޶�ֻ��
	for (list<int>::const_iterator it = L.begin(); it != L.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}


void test01()
{
	list<int>L1; 

	//β��
	L1.push_back(10);
	L1.push_back(20);
	L1.push_back(30);
	
	//ͷ��
	L1.push_front(1);
	L1.push_front(2);
	L1.push_front(3);
	// 3 2 1 10 20 30
	printList(L1);

	//βɾ
	L1.pop_back();
	// 3 2 1 10 20 
	printList(L1);

	//ͷɾ
	L1.pop_front();
	// 2 1 10 20 
	printList(L1);

	//insert����   // λ�ñ����ǵ�����
	//L1.insert(L1.begin(), 100);
	//100 2 1 10 20 
	list<int>::iterator it = L1.begin();
	L1.insert(++it, 100);  //����insert��ʽ ������λ���ǿ����ƶ���
	//2  100  1  10  20
	printList(L1);

	//ɾ��
	it = L1.begin();
	//L1.erase(it);
	//  100  1  10  20
	L1.erase(++it);
	//2 1 10 20
	printList(L1);

    //�Ƴ�
	L1.push_back(1000);
	L1.push_back(1000);
	L1.push_back(1000);
	printList(L1);

	L1.remove(1000); //ɾ��������������elemֵƥ���Ԫ��
	printList(L1);

	//���
	L1.clear();
	printList(L1);

}
 



int main()
{
	test01();
	


	system("pause");
	return 0;
}