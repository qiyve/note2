#include<iostream>
using namespace std;
#include"speechManager.h"
#include<string>
#include<ctime>

int main()
{
	//���������
	srand((unsigned int)time(NULL));

	//�������������
	SpeechManager sm;

	//���Դ���12��ѡ��
	//for (map<int, Speaker>::iterator it = sm.m_Speaker.begin(); it != sm.m_Speaker.end(); it++)
	//{
	//	cout << "��ţ�" << it->first 
	//		<< " ������" << it->second.m_Name 
	//		<< " ������" << it->second.m_Score[1] << endl;
 //   }
	
	int choice = 0; //�����û�����

	
	while (true)
	{
		sm.show_Menu(); //���ò˵�

		cout << "����������ѡ��" << endl;
		cin >> choice;//�����û�����

		switch (choice)
		{
		case 1:     //��ʼ����
			sm.startSpeech();
			break;
		case 2:     //�鿴�����¼
			sm.showRecord();
			break;
		case 3:     //��ռ�¼
			sm.clearRecord();
			break;
		case 0:     //�˳�����
			sm.exitSystem();
			break;

		default:
			system("cls");   //����
			break;
		}
	}
	




	system("pause");
	return 0;
}