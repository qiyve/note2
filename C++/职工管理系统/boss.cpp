
#include"boos.h"



	//���캯��
Boos::Boos(int id, string name, int did)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_DeptID = did;
}

	//��ʾ������Ϣ
void Boos::ShowInfo()
{
	cout << "ְ����ţ�" << this->m_Id
		<< "\tְ��������" << this->m_Name
		<< "\t��λ���ƣ�" << this->GetDeptName()
		<< "\t��λְ�� ����˾��������" << endl;
 }

	//��ȡ��λ����
string Boos::GetDeptName()
{
	return string("�ܲ�");
}

