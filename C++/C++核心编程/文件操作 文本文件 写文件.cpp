#include<iostream>
using namespace std;
#include<fstream> //����ͷ�ļ�

//д�ļ�

void test01()
{
	//1. ����ͷ�ļ�     #include<fstream>

	//2. ����������     ofstream ofs;
	ofstream ofs;

	//3. ���ļ�       ofs.open("�ļ�·����,  �򿪷�ʽ)
	ofs.open("д�ļ�.txt", ios::out);

	//4. д����         ofs << "д�������";
	ofs << "����������" << endl;
	ofs << "�Ա���" << endl;

	//5. �ر��ļ�       ofs.close()
	ofs.close();
}

   
   
  
  
   

int main()
{

	test01();

	system("pause");
	return 0;
}