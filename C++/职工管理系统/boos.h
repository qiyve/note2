#pragma once
#include<iostream>
using namespace std;
#include<string>

#include"Worker.h"//����ͷ�ļ�

class Boos :public Worker
{
public:

	//���캯��
	Boos(int id, string name, int did);
	
	//��ʾ������Ϣ
	virtual void ShowInfo() ;

	//��ȡ��λ����
	virtual string GetDeptName();


};