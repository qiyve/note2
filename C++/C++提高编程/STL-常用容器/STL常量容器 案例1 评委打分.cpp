#include<iostream>
using namespace std;
#include<deque>
#include<vector>
#include<string>
#include<algorithm>//��׼�㷨ͷ�ļ�
#include<ctime>  //�������Ӱ��� ctime ͷ�ļ�

//STL ���� ��ί���
//������ѡ�֣�ѡ��ABCDE,10����ί�ֱ��ÿ��ѡ�ִ�֣�ȥ����߷֣�ȥ����ί����ͷ֣�ȡƽ�ַ�

//ѡ����
class Person
{
public:

	Person(string name, int score)
	{
		this->m_Name = name;
		this->m_Score = score;
	}

	string m_Name; //����
	int m_Score;  //ƽ����
};

//����ѡ��
void createPerson(vector<Person>&v)
{

	string nameSeed = "ABCDE";
	for (int i = 0; i < 5; i++)
	{
		string name = "ѡ��";
		name += nameSeed[i];

		int score = 0;

		Person p(name, score);

		//��������Person���󣬷��뵽����
		v.push_back(p);
	}
}

//���
void setScore(vector<Person>&v)
{
	for (vector<Person>::iterator it = v.begin(); it != v.end(); it++)
	{
		//����ί�ķ��� ����deque������
		deque<int>d;
		for (int i = 0; i < 10; i++)
		{
			int score = rand() % 41 + 60;//60~100  ��������� rand����

			d.push_back(score);//����������
		}
		
		/*���Դ��
		cout << "ѡ�֣�" << it->m_Name << "�÷֣�" << endl;
		for (deque<int>::const_iterator dit = d.begin(); dit != d.end(); dit++)
		{
			cout << *dit << " ";
		}
		cout << endl;*/

		//����
		sort(d.begin(), d.end());
          
		d.pop_back(); //ȥ����߷�
		d.pop_front();//ȥ����ͷ�

		//ȡƽ����
		int sum = 0;
		for (deque<int>::iterator dit = d.begin(); dit != d.end(); dit++)
		{
			sum += *dit; //�ۼ�ÿ����ί����
		}
		int avg = sum / d.size();

		//��ƽ���ָ�ֵ��ѡ��
		it->m_Score = avg;

	}
}

//��ʾƽ����
void showScore(vector<Person>&v)
{
	for (vector<Person>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "ѡ�֣�" << (*it).m_Name << " ƽ���֣�" << (*it).m_Score << endl;
	}
}

void test01()
{
	//������������
	srand((unsigned int)time(NULL));

	//1������5��ѡ��
	vector<Person>v;
	createPerson(v);

	//����
	/*for (vector<Person>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "������" << (*it).m_Name << " ������" << (*it).m_Score << endl;
	}*/

	//2����5��ѡ�ִ��
	setScore(v);

	//3����ʾ���÷�
	showScore(v);
}

int main()
{
	test01();
	

	system("pause");
	return 0;
}