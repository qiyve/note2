
#include <iostream>
using namespace std;

int main()
{
	//ָ����ռ���ڴ�ռ�
	int a = 0;
	// int* p ;
	//p = &a;

	int* p = &a;
	// ��32λ����ϵͳ�£�ռ4���ֽڣ� ������ʲô���ݶ��� 4 ���ֽ�
	//64λ��վ8���ֽ�
	
	cout << "sizeof(int) = " << sizeof(int *) << endl;
	cout << "sizeof(int) = " << sizeof(float*) << endl;
	cout << "sizeof(int) = " << sizeof(double*) << endl;
	cout << "sizeof(int) = " << sizeof(char*) << endl;
	system("pause");
	return 0;
}
