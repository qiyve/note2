#include <iostream>
using namespace std;
#include<vector>
#include<algorithm>

//���ü����㷨 set_intersection
//�����������Ľ���   �����������������ظ���Ԫ�س�Ϊ����

//set_intersection(iterator beg1, iterator end1, iterator beg2, iterator end2, iterator dest); 4
//ע�⣺�������ϱ�������������
//beg1  ����1 ��ʼ������
//end1  ����1 ����������
//beg2  ����2 ��ʼ������
//end2  ����2 ����������
//dest   Ŀ��������ʼ������

void myPrint(int val)
{
    cout << val << " ";
}

void test01()
{
    vector<int>v1;
    vector<int>v2;
    for (int i = 0; i < 10; i++)
    {
        v1.push_back(i); //0~9
        v2.push_back(i + 4); //4~13
    }


    vector<int>vTarget;
    //Ŀ��������Ҫ��ǰ���ٿռ�
    //��������� ����������С����  ���ٿռ� ȡС������size����
    vTarget.resize(min(v1.size(), v2.size()));

    //��ȡ����
    vector<int>::iterator itEnd = set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), vTarget.begin());

    for_each(vTarget.begin(), itEnd, myPrint);
    cout << endl;
}
//�ܽ᣺1.�󽻼����������ϱ�������������
//      2.Ŀ���������ٿռ���Ҫ����������ȡ��Сֵ
//      3.set_intersection����ֵ�ǽ��������һ��Ԫ�ص�λ��

int main()
{
    test01();

    system("pause");
    return 0;
}