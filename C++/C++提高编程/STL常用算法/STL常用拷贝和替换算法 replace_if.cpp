#include <iostream>
using namespace std;
#include<vector>
#include<algorithm>

//���ÿ������滻�㷨  replace

//replace_if(iterator beg, iteraor end, _pred, newvalue);
//�������滻Ԫ�أ� �����������滻��ָ��Ԫ��
//beg ��ʼ������
//end ����������
//_Pred ν��
// newvalue  �滻����Ԫ��

class MyPrint
{
public:

    void operator()(int val)
    {
        cout << val << " ";
    }
};

class Greater30
{
public:
    bool operator()(int val)
    {
        return val >= 20;
    }
};

void test01()
{
    vector<int>v1;
    v1.push_back(10);
    v1.push_back(20);
    v1.push_back(30);
    v1.push_back(40);
    v1.push_back(50);
    v1.push_back(30);

    cout << "�滻ǰ" << endl;
    for_each(v1.begin(), v1.end(), MyPrint());
    cout << endl;

    //�����ڵ���20 �滻Ϊ2000
    replace_if(v1.begin(), v1.end(),Greater30(),2000);

    cout << "�滻��" << endl;
    for_each(v1.begin(), v1.end(), MyPrint());
    cout << endl;

  
}

int main()
{

    test01();



    system("pause");
    return 0;
}