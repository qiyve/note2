#include"employee.h"


//���캯��
Employee::Employee(int id, string name, int did)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_DeptID = did;
}

//չʾ������Ϣ
void Employee::ShowInfo()
{
	cout << "ְ����ţ�" << this->m_Id
		<< "\tְ��������" << this->m_Name
		<< "\t��λ: " << this->GetDeptName()
		<< "\t��λְ�� ��ɾ�����������" << endl;
}

//��ȡԱ����λ����
string Employee::GetDeptName()
{
	return string("Ա��");
}