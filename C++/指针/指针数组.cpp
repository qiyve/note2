
#include <iostream>
using namespace std;

int main()
{
	//ָ������
	//����ָ�������������е�Ԫ��
	int arr[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	int* p = arr;  //arr����������׵�ַ
	cout << "����ָ����������е�һ��Ԫ�� " << *p << endl;

	p++;//��ָ�����ƫ���ĸ��ֽ�
	cout << "����ָ����������еڶ���Ԫ�� " << *p << endl;

	cout << "����ָ���������" << endl;

	int* p1 = arr;
	for (int i = 0; i < 9; i++)
	{
		cout << *p1 << endl;
		p1++;
	}
	system("pause");
	return 0;
}
