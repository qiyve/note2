#include <Windows.h>
#include <iostream>

void _declspec(naked)ShellCode()
{
	_asm
	{	//1. ��������ַ���
		// user32.dll     75 73 65 72 33 32 2E 64 6C 6C     00           ����0xB
		// hello 51hook   68 65 6C 6C 6F 20 35 31 68 6F 6F 6B 00		 ����0xD
		// ExitProcess     0x4FD18963
		// LoadLibraryA:   0XC917432
		// GetProcAddress: 0XBBAFDF85
		// MessageBoxA:    0x1E380A6A

		pushad
		sub esp, 0x30

		//kenerl32.dll
		mov byte ptr ds : [esp - 1] , 0x0
		sub esp, 0x1
		push 0x6C6C642E
		push 0x32336C65
		push 0x6E72656B

		// hello 51hook 
		mov byte ptr ds : [esp - 1] , 0x0
		sub esp, 0x1
		push 0x6B6F6F68
		push 0x3135206F
		push 0x6C6C6568		

		// user32.dll
		mov byte ptr ds : [esp - 1] , 0x0
		sub esp, 0x1
		mov ax, 0x6C6C
		mov word ptr ds : [esp - 2] , ax
		sub esp, 0x2
		push 0x642E3233
		push 0x72657375		

		mov ecx, esp
		push ecx
		call func_payload

		//2. ��ȡģ���ַ
	func_GetModule:
		push ebp
		mov ebp, esp
		sub esp, 0xc
		push esi
		mov esi, dword ptr fs:[0x30] //PEB��ַ
		mov esi, [esi + 0xc]	 //LDR �ṹ���ַ
		mov esi, [esi + 0x1c]	 //list
		mov esi, [esi]			 //list�ĵڶ���洢���� kerne32 kernebase ��Ϣ
		mov esi, [esi + 0x8]	 //dllbase
		mov eax, esi
		pop esi
		mov esp, ebp
		pop ebp
		retn

		//3.��ȡ�����
	func_GetProcAddr:    
		push ebp
		mov ebp, esp
		sub esp, 0x20
		push esi
		push edx
		push edi
		push ecx

		mov edx, [ebp + 0x8]	//dllbase
		mov esi, [edx + 0x3c]	//lf_anew
		lea esi, [edx + esi]	//NTͷ
		mov esi, [esi + 0x78]   // ������ RVA
		lea esi, [edx + esi]	// ������ VA
		mov edi, [esi + 0x1c]	// EAT  RVA  ��ַ�� 
		lea edi, [edx + edi]	// EAT VA
		mov[ebp - 0x4], edi		// eatva
		mov edi, [esi + 0x20]	//ENT RVA ���Ʊ�
		lea edi, [edx + edi]	//ENT VA 
		mov[ebp - 0x8], edi      //entva
		mov edi, [esi + 0x24]	//EOT RVA ���Ʊ�
		lea edi, [edx + edi]	//EOT VA 
		mov[ebp - 0xc], edi      //eotva

		//�Ƚ��ַ�����ȡAPI
		xor eax, eax
		xor ebx, ebx
		cld
		jmp tag_cmpfirest
	tag_cmpLoop:
		inc ebx
	tag_cmpfirest:
		mov esi, [ebp - 0x8]	//�������Ʊ�
		mov esi, [esi+ ebx *4]	//��һ������
		lea esi, [edx + esi]	//��������
		mov edi, [ebp + 0xc]	//�ڶ������� Ҫ�ҵĺ������Ƶ�ַ

		push esi				//����
		call func_HashCode		//��ENT�������ƽ��б���
		cmp edi, eax			//��ϣֵ�Ƚ�
		jne tag_cmpLoop

		mov esi, [ebp - 0xc]
		xor edi, edi				//Ϊ�˲�ӳ�������edi
		mov di,  [esi + ebx *2]		//eat������
		mov edx, [ebp - 0x4]		//eat
		mov esi, [edx + edi*4]		//������ַrva
		mov edx, [ebp + 0x8]		//dllbase
		lea eax, [edx + esi]	    //funaddr vr
		pop ecx
		pop edi
		pop edx
		pop esi
		mov esp, ebp
		pop ebp
		retn 0xC

	func_payload:
		
		push ebp
		mov ebp, esp
		sub esp, 0x30
		push ebx
		push ecx
	
		//1.���õ�dllbase
		call func_GetModule
		mov[ebp - 0x4], eax     //ģ���ַ
		//2.��ȡLoadLibraryA
		push 0XC917432		  // LoadLibraryA ��ϣֵ		
		push eax				
		call func_GetProcAddr   
		mov [ebp - 0x8], eax   // LoadLibraryA ��ַ

		//3.��ȡGetProcAddress
		push 0XBBAFDF85			// GetProcAddress ��ϣֵ	
		push [ebp -0x4]			// kerne32/kerneBase ��ַ
		call func_GetProcAddr
		mov [ebp - 0xc], eax  //GetProcAddress 

		//4.����LoadLibraryA ����user32.dll
		mov ecx, [ebp + 0x8]
		push ecx
		call [ebp - 0x8]	   //����LoadLibraryA
		mov [ebp - 0x10], eax  // user32Base

		//5.����func_GetProcAddr  ��ȡMessageBoxA 
		push 0x1E380A6A			//MessageBoxA  ��ϣֵ
		push [ebp - 0x10]		
		call func_GetProcAddr
		mov[ebp - 0x14], eax	 //MessageBoxA

		//6.���hello 51hook
		push 0
		push 0
		mov ebx, [ebp + 0x8]
		lea ebx, [ebx +0xB]
		push ebx
		push 0
		call [ebp - 0x14]
		
		//����LoadLibraryA ����kerne32
		mov ecx, [ebp + 0x8]
		lea ecx, [ecx + 0x18]
		push ecx
		call [ebp - 0x8]
		mov [ebp - 0x18], eax 

		//����func_GetProcAddr ��ȡ ExitProcess     0x4FD18963
		push 0x4FD18963
		push[ebp - 0x18]
		call func_GetProcAddr
		mov[ebp - 0x1c], eax
		
		//���� ExitProcess �˳�
		push 0
		call [ebp - 0x1c]

		pop ecx
		pop ebx
		mov esp, ebp
		pop ebp
		retn 0x4


	func_HashCode:
		push ebp
		mov ebp, esp
		sub esp, 0X4
		push ecx
		push edx
		push ebx
		mov dword ptr[ebp - 0x4], 0
		mov esi, [ebp + 0x8] // str
		xor ecx, ecx

	tag_HashLoop :
		xor eax, eax
		mov al, [esi + ecx]
		test al, al
		jz tag_End
		mov ebx, [ebp - 0x4]
		shl ebx, 0x19
		mov edx, [ebp - 0x4]
		shr edx, 0x7
		or ebx, edx
		add ebx, eax
		mov[ebp - 0x4], ebx
		inc ecx   //ecx++ 
		jmp tag_HashLoop

	tag_End :
		mov eax, [ebp - 0x4]
		pop ebx
		pop edx
		pop ecx
		mov esp, ebp
		pop ebp
		retn 0x4
	}
}

int main()
{

	printf("hell \n");
	ShellCode();
	system("pause");
	return 0;
}