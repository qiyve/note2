#pragma once
#include<iostream>
using namespace std;
#include"worker.h"

//������ͨԱ����
//��ͨԱ����̳�ְ�������࣬����д�����д��麯��
//��ͷ�ļ���Դ�ļ����ļ��·ֱ𴴽� employee.h ��employee.cpp �ļ� 

class Employee : public Worker
{
public:

	//���캯��
	Employee(int id, string name, int did);

	//չʾ������Ϣ
	virtual void ShowInfo();

	//��ȡԱ����λ����
	virtual string  GetDeptName();
};
