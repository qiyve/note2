#include<iostream>
using namespace std;

//1����__declspec(naked)�㺯��ʵ������Ĺ���
//��ϰĿ�ģ�
//(1) ��Ϥ��ջ�ṹ
//(2) �������ֲ�������λ��
//(3) ����ֵ�洢��λ��

//int plus(int x, int y, int z)					010101010
//{
//	int a = 2;
//	int b = 3;
//	int c = 4;
//	return x + y + z + a + b + c;
//}
int __declspec(naked)Plus(int x, int y, int z)
{
	__asm
	{
		//����ջ��
		push ebp
		//������ջ
		mov ebp, esp
		sub esp, 0x40
		//�����ֳ�
		push ebx
		push esi
		push edi
		//��仺����
		mov eax, 0xCCCCCCCC
		mov ecx, 0x10
		lea edi, dword ptr ds : [ebp - 0x40]
		rep stosd		
		//�÷�������Ҫִ�еĹ���

		//�ֲ����� ebp-4      ����ebp+8
		mov dword ptr ds : [ebp - 0x4] , 2
		mov dword ptr ds : [ebp - 0x8] , 3
		mov dword ptr ds : [ebp - 0xc] , 4		

		mov eax, dword ptr ds : [ebp + 0x8]
		add eax, dword ptr ds : [ebp + 0xc]
		add eax, dword ptr ds : [ebp + 0x10]

		add eax, dword ptr ds : [ebp - 0x4]
		add eax, dword ptr ds : [ebp - 0x8]
		add eax, dword ptr ds : [ebp - 0xc]

		//�ָ��ֳ�
		pop edi
		pop esi
		pop ebx
		//���Ͷ�ջ
		mov esp, ebp
		pop ebp

		ret
	}

}

int main()
{
	int a = Plus(1, 2, 3);
	cout << a;

	return 0;
}