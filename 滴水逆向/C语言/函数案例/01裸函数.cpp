#include<iostream>
using namespace std;

//�㺯�� �ؼ��� __declspec(naked)  
//ע�⣺�����������Զ������κδ�����Ҫ��д�� ����� __asm {ret}�����޷�����
int __declspec(naked)Plus(int x, int y)
{
	__asm
	{
		//�������ǰջ��
		push ebp
		//������ջ
		mov ebp, esp
		sub esp, 0x40
		//�����ֳ�
		push ebx
		push esi
		push edi
		//��仺��ռ�
		mov eax, 0xcccccccc
		mov ecx, 0x10
		lea edi, dword ptr ds:[ebp - 0x40]
		rep stosd
		//��������
		mov eax, dword ptr ds : [ebp + 0x8]
		add eax, dword ptr ds : [ebp + 0xc]
		//�ָ��ֳ�  ��ջ �Ƚ����
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
	Plus(1, 2);


	return 0;
}
