#pragma once
#include<iostream>
using namespace std;
#include"Identity.h"
#include<string>
#include<fstream>
#include"globalFile.h"
#include"Student.h"
#include"Teacher.h"
#include<vector>
#include<algorithm>
#include"computerRoom.h"

//����Ա�����
class Manager :public Identity
{
public:

	//Ĭ�Ϲ���
	Manager();

	//�вι���
	Manager(string name, string pwd);

	//�˵�����
	virtual void operMenu();

	//����˺�
	void addPerson();

	//�鿴�˺�
	void showPerson();

	//�鿴������Ϣ
	void showComputer();

	//��ջ�������
	void cleanFile();

	//��ʼ������
	void initVector();

	//����ظ� ����1�����ѧ��/ְ����  ����2���������
	bool checkRepeat(int id,int type);

	//��ʼ����������
	void initComputer();

	//��������
	vector<ComputerRoom>vCom;

	//ѧ������
	vector<Student>vStu;

	//��ʦ����
	vector<Teacher>vTea;
};