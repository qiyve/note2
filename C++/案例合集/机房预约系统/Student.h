#pragma once
#include<iostream>
using namespace std;
#include"Identity.h"
#include<string>
#include"computerRoom.h"
#include<vector>
#include<fstream>
#include"globalFile.h"
#include"orderFile.h"
#include<stdlib.h>

//ѧ����
class Student :public Identity
{
public:

	//Ĭ�Ϲ���
	Student();

	//�вι���  ������ѧ�� ���� ����
	Student(int id,string name ,string pwd);

	//�˵�����
	virtual void operMenu();

	//����ԤԼ
	void applyOrder();

	//�鿴����ԤԼ
	void showMyOrder();

	//�鿴����ԤԼ
	void showAllOrder();

	//��������
	vector<ComputerRoom>vCom;

	 //ȡ��ԤԼ
	void cancelOrder();
	
	//ѧ�����
	int m_Id;
};
