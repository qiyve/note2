#pragma once
#pragma once
#include<iostream>
using namespace std;
#include<string>

// ����ְ��������
// ְ���ķ���Ϊ����ͨԱ�� �� ���� ���ϰ�
// ������ְ������һ���� ��worker���У������ö�̬����ְͬ������
// ְ��������Ϊ�� ְ�����  ְ������  ְ�����ڲ��ű��
// ְ������ΪΪ�� ��λְ����Ϣ��������ȡ��λ����

//ְ��������
class Worker
{
public:

	//չʾ������Ϣ
	virtual void ShowInfo() = 0;

	//��ȡ��λ����
	virtual string GetDeptName() = 0;

	//ְ�����
	int m_Id;
	//ְ������
	string m_Name;
	//���ű��
	int m_DeptID;

};