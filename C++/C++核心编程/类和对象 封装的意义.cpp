#include<iostream>
using namespace std;

//Բ����
const double PI = 3.14;

//���һ��Բ�࣬��Բ���ܳ�
//Բ���ܳ��Ĺ�ʽ ��2 * PI * �뾶

//class �������һ���࣬���������ŵľ���������
class Yuan
{
	//����Ȩ��
	//����Ȩ��
public:

	//����
	//�뾶
	int m_r;

	//��Ϊ
	//��ȡԲ���ܳ�
	double calculateZC()
	{
		return 2 * PI * m_r;
	}
};
int main()
{
	//ͨ�����Բ�࣬����һ�������Բ(����)
	//ʵ���� ��ͨ��һ���� ����һ������Ĺ��̣�
	Yuan y1;
	//��Բ���� �����Ը�ֵ
	y1.m_r = 10;

	// 2 * PI *10 = 62.8
	cout << "Բ���ܳ�Ϊ��" << y1.calculateZC() << endl;


	system("pause");
	return 0;
}