#include"manager.h"



	//���캯��
Manager::Manager(int id, string name, int did)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_DeptID = did;
}

	//չʾ������Ϣ
void Manager::ShowInfo()
{
	cout << "ְ����ţ�" << this->m_Id
		<< "\tְ��������" << this->m_Name
		<< "\t��λ���ƣ�" << this->GetDeptName() 
		<<"\t��λְ�� ����ϰ彻�������񣬲��·���Ա��" << endl;
}

	//��ȡԱ����λ����
string  Manager::GetDeptName()
{
	return string("����");
}
