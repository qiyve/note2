#include <stdio.h>
#include <Windows.h>
#include <tchar.h>



extern"C"
{
	#include"ldasm.h"
}

//��ȡ����
uint32_t calc_len(uint8_t* code, uint32_t need_size)
{
	uint32_t size = 0;
	ldasm_data ld;

	//ѭ�� ��ȡ ָ���
	while (size < need_size)
	{
		size += ldasm(code + size, &ld, 0);
	}
	return size;
}

unsigned char ida_chars[] =
{
	0xE8, 0x05, 0x00, 0x00, 0x00,    // ����call ִ���� ������һ�е�ַ
	0xE9, 0x00, 0x00, 0x00, 0x00,    // ���� ԭ����ַ

	0x60, 0x31, 0xD2, 0x52, 0x68, 0x63, 0x61, 0x6C, 0x63, 0x54,
	0x59, 0x52, 0x51, 0x64, 0x8B, 0x72, 0x30, 0x8B, 0x76, 0x0C,
	0x8B, 0x76, 0x0C, 0xAD, 0x8B, 0x30, 0x8B, 0x7E, 0x18, 0x8B,
	0x5F, 0x3C, 0x8B, 0x5C, 0x1F, 0x78, 0x8B, 0x74, 0x1F, 0x20,
	0x01, 0xFE, 0x8B, 0x54, 0x1F, 0x24, 0x0F, 0xB7, 0x2C, 0x17,
	0x42, 0x42, 0xAD, 0x81, 0x3C, 0x07, 0x57, 0x69, 0x6E, 0x45,
	0x75, 0xF0, 0x8B, 0x74, 0x1F, 0x1C, 0x01, 0xFE, 0x03, 0x3C,
	0xAE, 0xFF, 0xD7, 0x58, 0x58, 0x61, 0xC3
};

void InlineHook()
{
	//��ȡģ����
	HMODULE uers32_dll = LoadLibraryA("user32.dll");
	//��ȡ��ҪHOOK�ĺ����ĵ�ַ
	uint8_t* MessageBox_Address = (uint8_t*)GetProcAddress(uers32_dll, "MessageBoxA");
	//��ȡͷ����  JMP
	uint32_t head_size = calc_len(MessageBox_Address, 5);

	//����ռ�
	uint8_t* code = (uint8_t*)VirtualAlloc(NULL, sizeof(ida_chars) + head_size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

	//��ȡҪ��ת�ĵ�ַ
	uint8_t* Jmp_addr = code + head_size + 5;
	//�޸�Ҫ���صĵ�ַ
	*(int32_t*)&ida_chars[5 + 1] = (MessageBox_Address + head_size) - (Jmp_addr + 5);

	memcpy(code, MessageBox_Address, head_size);
	memcpy(code + head_size, ida_chars, sizeof(ida_chars));

	//�޸ķ���Ȩ��
	DWORD Protect = PAGE_EXECUTE_READWRITE;
	VirtualProtect(MessageBox_Address, 5, Protect, &Protect);

	*MessageBox_Address = 0xE9;
	*(int*)(MessageBox_Address + 1) = code - (MessageBox_Address + 5);
}

int main()
{
	InlineHook();
	MessageBoxA(NULL, ("Text"), ("Caption"), MB_OK);


	return 0;
}