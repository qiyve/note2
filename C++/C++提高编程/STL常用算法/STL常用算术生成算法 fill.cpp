#include <iostream>
using namespace std;
#include<vector>
#include<numeric>
#include<algorithm>


//�������������㷨  fill
//�ܽ᣺����fill ���Խ�����������Ԫ�����Ϊ ָ����ֵ

//fill(iterator  beg, iterator  end, value);
//�����������Ԫ��
//beg ��ʼ������
//end ����������
//value ����ֵ

class MyPrint
{
public:

    void operator()(int val)
    {
        cout << val << " ";
    }
};
void test01()
{
    vector<int>v;
    v.resize(10);

    cout << "���ǰ��" << endl;
    for_each(v.begin(), v.end(), MyPrint());
    cout << endl;

    //�����������
    
    fill(v.begin(), v.end(), 100);
    cout << "����" << endl;
    for_each(v.begin(), v.end(), MyPrint());
    cout << endl;
}

int main()
{
    test01();

    system("pause");
    return 0;
}