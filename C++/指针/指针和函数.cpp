
#include <iostream>
using namespace std;

//ָ��ͺ���
void swap(int* p1, int* p2)
{
	int temp = *p1;
	*p1 = *p2;
	*p2 = temp;
}
int main()
{
	int a = 20;
	int b = 10;
	//��ַ����  ����ǵ�ַ���ݿ�������ʵ��
	//��������޸�ʵ�ξ���ֵ���� �����޸�ʵ�ξ��õ�ַ����
<<<<<<< HEAD
	swap(&a,& b);
=======
	::swap(&a, &b);
>>>>>>> 9195916e9e49c10b31a2cd51f7d8bb159d71ba96
	
	cout << "a= " << a << endl;
	cout << "b= " << b << endl;

	system("pause");
	return 0;
}
