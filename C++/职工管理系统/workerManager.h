#pragma once        //��ֹͷ�ļ��ظ�����
#include<iostream>   //������������� ͷ�ļ�
using namespace std; //��׼�������ռ�
#include"Worker.h"   //ְ��������
#include"employee.h" //��ͨԱ����
#include"manager.h"  //������
#include"boos.h"     //�ϰ�

#include<fstream>    //��дͷ�ļ�
#define FILENAME "empFile.txt"


//������
class WorkerManager
{
public:

	//���캯��
	WorkerManager();

	//չʾ�˵�
	void Show_Menu();

	//�˳�ϵͳ
	void exitSystem();

    //��¼ְ������
	int m_EmpNum;

	//��ӹ��ܺ���
	void Add_Emp();

	//ְ������ָ��
	Worker** m_EmpArray;

	//�����ļ�
	void Save();

	//��־�ļ��Ƿ�Ϊ��
	bool m_FileIsEmpty;

	//ͳ���ļ�������
	int get_EmpNum();

	//��ʼ��Ա��
	void init_Emp();

	//��ʾְ��
	void Show_Emp();  

	//ɾ��ְ��
	void Del_Emp();

    //�ж�ְ���Ƿ����
	int IsExist(int id);

	//�޸�ְ��
	void Mod_Emp();

	//����ְ��
	void Find_Emp();

	//ְ������
	void Sort_Emp();

	//����ļ�
	void Cleam_File();

	//��������
	~WorkerManager();
};