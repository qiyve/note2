#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#define FILEPATH "C:\\Windows\\System32\\notepad.exe"

//IMAGE_SIZEOF_FILE_HEADER 20   ��׼PE��С
/*
IMAGE_SECTIONAL_HEADER   �ڱ�
Name �ڱ�����
Micsc.VirtualSize �ý��ļ�����ǰ��ʵ�ߴ�   Misc
ViruakAddress ������� ��ʼ�ĵط�
SizeOfRawData �����ļ��ж����Ĵ�С
PointerToRawDate �����ļ��п�ʼ�ĵط�
Characteristice	�ڵ�����
*/
//LPVOID��һ��û�����͵�ָ�룬Ҳ����˵����Խ��������͵�ָ�븳ֵ��LPVOID���͵ı�����һ����Ϊ�������ݣ���
//Ȼ����ʹ�õ�ʱ����ת�������� ���Խ������Ϊlong�͵�ָ�룬ָ��void��
LPVOID fRead01()
{
	FILE* file = NULL;
	errno_t a = fopen_s(&file, FILEPATH, "rb");
	if (a != 0)
	{
		printf("��ʧ��\n");
		return 0;
	}
	fseek(file, 0, SEEK_END);
	size_t b = ftell(file);
	fseek(file, 0, SEEK_SET);
	LPVOID buff = malloc(b);
	if (buff == 0)
	{
		printf("�����ڴ�ʧ��\n");
		fclose(file);
		return 0;
	}
	size_t c = fread(buff, b, 1, file);
	if (c == 0 || c > 1)
	{
		printf("��ȡʧ��\n");
		fclose(file);
		free(buff);
		return 0;
	}
	printf("��ȡ�ɹ�\n");
	fclose(file);
	return buff;
}

void showSectionHeader()
{
	//������ָ��
	LPVOID buff = NULL;
	//DOSͷָ��
	PIMAGE_DOS_HEADER DosHeader = NULL;
	//NTͷ
	PIMAGE_NT_HEADERS ntHeader = NULL;
	//��׼PEͷ
	PIMAGE_FILE_HEADER peHeader = NULL;
	//��ѡPE
	PIMAGE_OPTIONAL_HEADER32 OptionHeader = NULL;
	//�ڱ�
	PIMAGE_SECTION_HEADER SectionHeader = NULL;;

	buff = fRead01();

	//�ж�dosͷ
	DosHeader = (PIMAGE_DOS_HEADER)buff;
	//DWORD e_magicΪ"MZ",����ΪIMAGE_DOS_SIGNATURE
	DosHeader = (PIMAGE_DOS_HEADER)buff;
	if (DosHeader->e_magic != IMAGE_DOS_SIGNATURE)
	{
		printf("����MZ���\n");
		return;
	}
	//�ж�PE���
	ntHeader = (PIMAGE_NT_HEADERS)((DWORD)buff + DosHeader->e_lfanew);
	if (ntHeader->Signature != IMAGE_NT_SIGNATURE)
	{
		printf("����PE���\n");
		free(buff);
		return;
	}
	printf("PE:%x\n", ntHeader->Signature);

	//NumberOfSections ��¼�ڱ��λ��
	peHeader = (PIMAGE_FILE_HEADER)((DWORD)ntHeader + 4);
	printf("�ڵ�����:%x\n", peHeader->NumberOfSections);
	printf("��ѡPEͷ�Ĵ�С:%x\n", peHeader->SizeOfOptionalHeader);

	//��ѡPEͷ   ��׼PE��СΪ20
	OptionHeader = (PIMAGE_OPTIONAL_HEADER32)((DWORD)peHeader + 20);
	printf("�ڴ����Ϊ��%x\n", OptionHeader->SectionAlignment);
	printf("�ļ�����Ϊ��%x\n", OptionHeader->FileAlignment);
	
	//OptionHeader = (PIMAGE_OPTIONAL_HEADER32)((DWORD)peHeader + 20);
	//printf("�ڴ����:%x\n", OptionHeader->SectionAlignment);
	//printf("�ļ�����:%x\n", OptionHeader->FileAlignment);


	//�ڱ�  32λE0  64λ F0
	int Section_number = peHeader->NumberOfSections; 
	SectionHeader = (PIMAGE_SECTION_HEADER)((DWORD)OptionHeader + peHeader->SizeOfOptionalHeader);

	for (int i = 0; i < Section_number; i++)
	{
		printf("------------�ڱ���Ϣ%d------------\n", i + 1);
		printf("�ڱ�����(name):%s\n", SectionHeader->Name);
		printf("�ڱ����ǰ�ߴ磺%x\n", SectionHeader->Misc);
		printf("VirualAddress(�ڴ�ƫ��)%x\n", SectionHeader->VirtualAddress);
		printf("SizeOfRawDate(�ļ�������С:%x\n", SectionHeader->SizeOfRawData);
		printf("PointerToRawDate(�ļ���ƫ��)%x\n", SectionHeader->PointerToRawData);
		printf("Characteristics(�ڵ�����)%x\n", SectionHeader->Characteristics);
		//ƫ�ƶ�ȡ��һ���ڱ�
		SectionHeader = (PIMAGE_SECTION_HEADER)((DWORD)SectionHeader + 40);
		printf("\n\n");
	}

	free(buff);
}

int main()
{

	showSectionHeader();


	return 0;
}
