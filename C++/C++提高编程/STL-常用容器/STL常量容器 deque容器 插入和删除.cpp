#include<iostream>
using namespace std;
#include<deque>

//deque���������ɾ��

//���˲���
//push_back(elem);    // ������β�����һ������
//push_front(elem);      //������ͷ������һ������
//pop_back();              //ɾ���������һ������
//pop_front()��           //ɾ��������һ������


//ָ��λ�ò���
//insert(pos, elem);      //��posλ�ò���һ��elemԪ�صĿ���������������λ��
//insert(pos, n, elem)  //��posλ�ò���n��elem���ݣ��޷���ֵ
//insert(pos, beg, end); //��posλ�ò��루beg ��end����������ݣ��޷���ֵ
//clear();                        //�����������������
//erase(brg, end);         //ɾ����beg ��end����������ݣ�������һ�����ݵ�λ��
//erase(pos);                //ɾ��posλ�õ����ݣ�������һ�����ݵ�λ��     

void printDeque(const deque<int>& d)
{ 
	  //������޶�����ֻ��״̬    ���� const_iterator ֻ��������   
	for (deque<int>::const_iterator it = d.begin(); it != d.end(); it++)
	{
		//*it=100; ���������ݲ������޸���
		
		cout << *it << " ";
	}
	cout << endl;
}

//���˲���
void test01()
{
	deque<int>d1;
	
	//β��
	d1.push_back(10);
	d1.push_back(20);

	//ͷ��
	d1.push_front(100);
	d1.push_front(200);

	printDeque(d1);

	//βɾ
	d1.pop_back();
	// 200 100 10
	printDeque(d1);

	//ͷɾ
	d1.pop_front();
	//100 10
	printDeque(d1);
	
}

//ָ��λ�ò���
void test02()
{
	deque<int>d1;

	d1.push_back(10);
	d1.push_back(20);
	d1.push_front(100);
	d1.push_front(200);
	//200 100  10 20
	printDeque(d1);

	//insert����
	d1.insert(d1.begin(), 1000);
	// 1000 200 100 10 20
	printDeque(d1);

	d1.insert(d1.begin(), 3, 2000);
	printDeque(d1);
	// 2000 2000 2000 1000 200 100 10 20
	
    //����������в���
	deque<int>d2;
	d2.push_front(1);
	d2.push_front(2);
	d2.push_front(3);
	
	d1.insert(d1.begin(), d2.begin(), d2.end());
	// 3 2 1 2000 2000 2000 1000 200 100 10 20
	printDeque(d1);
}

//ָ��λ��ɾ��
void test03()
{
	deque<int>d1;
	d1.push_back(10);
	d1.push_back(20);
	d1.push_front(100);
	d1.push_front(200);

	//200 100 10 20
	printDeque(d1);
	
	//ɾ��
	deque<int>::iterator it = d1.begin();
	it++;
	// 200 10 20
	d1.erase(it);
	printDeque(d1);

	//���䷽ʽ
	d1.erase(d1.begin(), d1.end());
	//���
	d1.clear();
	printDeque(d1);

}


int main()
{

	//test01();
	//test02();
	test03();

	system("pause");
	return 0;
}