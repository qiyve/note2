#pragma once
#include<iostream>
using namespace std;
#include"worker.h"

//������������


class Manager : public Worker
{
public:

	//���캯��
	Manager(int id, string name, int did);

	//չʾ������Ϣ
	virtual void ShowInfo();  //���ﲻ�� = 0 ���������޷�ʵ��������

	//��ȡԱ����λ����
	virtual string  GetDeptName();
};
