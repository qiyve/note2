#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

DWORD LoadFile(LPVOID* FileBuffer, LPSTR path);
//��ӡ������
DWORD DeriveList(LPVOID FileBuffer);
//ת����ַ
DWORD RvaTurnFoa(LPVOID Buffer, DWORD Rva);
DWORD FoaTurnRva(LPVOID Buffer, DWORD Fov);
//���ݺ�����Ѱ�ҵ���������ַ
DWORD GetFunctionAddrByName(LPVOID Buffer, LPSTR Name);
//�������Ѱ�ҵ���������ַ
DWORD GetFunctionAddrByOrdinals(LPVOID Buffer, int i);
//�ƶ�������
DWORD MoveList(LPVOID* FileBuffer);
//��ӡ�ض�λ��
DWORD PrintfRelocation(LPVOID Buffer);
//�ƶ��ض�λ��
void MoveRelocation(LPVOID* FileBuffer);
//������
DWORD NewList(LPVOID* FileBuffer);
//�����ļ�
DWORD SaveFile(LPVOID FileBuffer);
DWORD size;
int main()
{
	LPVOID FileBuffer = NULL;
	char path[] = "C:\\Users\\Administrator\\Desktop\\1.exe";
	char Name[] = "DllRQSControlChangeProxyMode";
	DWORD Fov = 0;

	LoadFile(&FileBuffer, path);
	NewList(&FileBuffer);
	//MoveRelocation(&FileBuffer);
	//MoveList(&FileBuffer);
	//DeriveList(FileBuffer);
	//PrintfRelocation(FileBuffer);
	//GetFunctionAddrByName(FileBuffer,Name);
	//GetFunctionAddrByOrdinals(FileBuffer,2);
	SaveFile(FileBuffer);
	system("pause");
	return 0;
}

DWORD LoadFile(LPVOID* FileBuffer, LPSTR path)
{
	FILE* p;
	p = fopen(path, "rb+");
	if (!p)
	{
		printf("�ļ���ʧ��\n");
		return 0;
	}

	fseek(p, 0, SEEK_END);
	size_t len = ftell(p);
	fseek(p, 0, SEEK_SET);

	*FileBuffer = malloc(len);
	if (!*FileBuffer)
	{
		printf("�ڴ����ʧ��\n");
		fclose(p);
		return 0;
	}
	memset(*FileBuffer, 0, len);

	fread(*FileBuffer, 1, len, p);

	fclose(p);
	return len;
}
DWORD DeriveList(LPVOID Buffer)
{
	PIMAGE_DOS_HEADER	DosHeader;
	PIMAGE_NT_HEADERS	NtHeader;
	PIMAGE_FILE_HEADER	FileHeader;
	PIMAGE_OPTIONAL_HEADER	OpFileHeader;
	PIMAGE_SECTION_HEADER	SectionHeader;
	PIMAGE_EXPORT_DIRECTORY	ExportDirectory;

	DWORD Foa;

	DosHeader = (PIMAGE_DOS_HEADER)Buffer;
	NtHeader = (PIMAGE_NT_HEADERS)((DWORD)Buffer + DosHeader->e_lfanew);
	FileHeader = (PIMAGE_FILE_HEADER)((DWORD)NtHeader + 0x4);
	OpFileHeader = (PIMAGE_OPTIONAL_HEADER)((DWORD)FileHeader + IMAGE_SIZEOF_FILE_HEADER);
	SectionHeader = (PIMAGE_SECTION_HEADER)((DWORD)OpFileHeader + FileHeader->SizeOfOptionalHeader);

	Foa = RvaTurnFoa(Buffer, OpFileHeader->DataDirectory[0].VirtualAddress);
	ExportDirectory = (PIMAGE_EXPORT_DIRECTORY)((DWORD)Buffer + Foa);

	printf("�����������%s\n", (DWORD)Buffer + RvaTurnFoa(Buffer, ExportDirectory->Name));
	printf("��������ʼ���%x\n", ExportDirectory->Base);
	printf("������������%x\n", ExportDirectory->NumberOfFunctions);
	printf("�����Ƶ����ĺ�������%x\n", ExportDirectory->NumberOfNames);
	printf("������ַ��%x\n", (DWORD)Buffer + RvaTurnFoa(Buffer, ExportDirectory->AddressOfFunctions));
	printf("�������Ʊ�%x\n", (DWORD)Buffer + RvaTurnFoa(Buffer, ExportDirectory->AddressOfNames));
	printf("������ű�%x\n", (DWORD)Buffer + RvaTurnFoa(Buffer, ExportDirectory->AddressOfNameOrdinals));
	printf("***********************************************\n");


	PIMAGE_THUNK_DATA		ThunkFunctions;
	ThunkFunctions = (PIMAGE_THUNK_DATA)((DWORD)Buffer + RvaTurnFoa(Buffer, ExportDirectory->AddressOfFunctions));

	PIMAGE_IMPORT_BY_NAME	ImportNameOrdinals;
	ImportNameOrdinals = (PIMAGE_IMPORT_BY_NAME)((DWORD)Buffer + RvaTurnFoa(Buffer, ExportDirectory->AddressOfNameOrdinals));

	PIMAGE_THUNK_DATA		ThunkName;
	ThunkName = (PIMAGE_THUNK_DATA)((DWORD)Buffer + RvaTurnFoa(Buffer, ExportDirectory->AddressOfNames));

	for (int i = 0; i < (int)ExportDirectory->NumberOfNames; i++)
	{
		for (int n = 0; n < ImportNameOrdinals->Hint; n++)
		{
			ThunkFunctions = (PIMAGE_THUNK_DATA)(DWORD)ThunkFunctions + 0x1;
		}
		printf("����������%s	\n", (DWORD)Buffer + RvaTurnFoa(Buffer, ThunkName->u1.ForwarderString));
		printf("���������%x	\n", ImportNameOrdinals->Hint + 1);
		printf("������ַ��%x	\n", ThunkFunctions->u1.Function + OpFileHeader->ImageBase);
		printf("**********************************************\n");

		ThunkFunctions = (PIMAGE_THUNK_DATA)((DWORD)Buffer + RvaTurnFoa(Buffer, ExportDirectory->AddressOfFunctions));

		ImportNameOrdinals = (PIMAGE_IMPORT_BY_NAME)((DWORD)ImportNameOrdinals + 0x2);

		ThunkName = (PIMAGE_THUNK_DATA)(DWORD)ThunkName + 0x1;

	}
	return 1;
}
DWORD RvaTurnFoa(LPVOID Buffer, DWORD Rva)
{
	PIMAGE_DOS_HEADER	DosHeader;
	PIMAGE_NT_HEADERS	NtHeader;
	PIMAGE_FILE_HEADER	FileHeader;
	PIMAGE_OPTIONAL_HEADER	OpFileHeader;
	PIMAGE_SECTION_HEADER	SectionHeader;
	DWORD Foa;

	DosHeader = (PIMAGE_DOS_HEADER)Buffer;
	NtHeader = (PIMAGE_NT_HEADERS)((DWORD)Buffer + DosHeader->e_lfanew);
	FileHeader = (PIMAGE_FILE_HEADER)((DWORD)NtHeader + 0x4);
	OpFileHeader = (PIMAGE_OPTIONAL_HEADER)((DWORD)FileHeader + IMAGE_SIZEOF_FILE_HEADER);
	SectionHeader = (PIMAGE_SECTION_HEADER)((DWORD)OpFileHeader + FileHeader->SizeOfOptionalHeader);

	for (int i = 0; i < FileHeader->NumberOfSections; i++)
	{
		if (Rva >= (DWORD)SectionHeader->VirtualAddress && Rva < (DWORD)(SectionHeader->VirtualAddress + SectionHeader->SizeOfRawData))
		{
			Foa = Rva - SectionHeader->VirtualAddress + SectionHeader->PointerToRawData;
			return Foa;
		}
		SectionHeader = (PIMAGE_SECTION_HEADER)((DWORD)SectionHeader + IMAGE_SIZEOF_SECTION_HEADER);
	}
	printf("��δ�ҵ�FOA\n");
	return 0;
}
DWORD FoaTurnRva(LPVOID Buffer, DWORD Fov)
{
	PIMAGE_DOS_HEADER	DosHeader;
	PIMAGE_NT_HEADERS	NtHeader;
	PIMAGE_FILE_HEADER	FileHeader;
	PIMAGE_OPTIONAL_HEADER	OpFileHeader;
	PIMAGE_SECTION_HEADER	SectionHeader;
	DWORD Rva;

	DosHeader = (PIMAGE_DOS_HEADER)Buffer;
	NtHeader = (PIMAGE_NT_HEADERS)((DWORD)Buffer + DosHeader->e_lfanew);
	FileHeader = (PIMAGE_FILE_HEADER)((DWORD)NtHeader + 0x4);
	OpFileHeader = (PIMAGE_OPTIONAL_HEADER)((DWORD)FileHeader + IMAGE_SIZEOF_FILE_HEADER);
	SectionHeader = (PIMAGE_SECTION_HEADER)((DWORD)OpFileHeader + FileHeader->SizeOfOptionalHeader);

	for (int i = 0; i < FileHeader->NumberOfSections; i++)
	{
		if (Fov >= (DWORD)SectionHeader->PointerToRawData && Fov < (DWORD)(SectionHeader->PointerToRawData + SectionHeader->SizeOfRawData))
		{
			Rva = Fov - SectionHeader->PointerToRawData + SectionHeader->VirtualAddress;
			return Rva;
		}
		SectionHeader = (PIMAGE_SECTION_HEADER)((DWORD)SectionHeader + IMAGE_SIZEOF_SECTION_HEADER);
	}
	printf("��δ�ҵ�Rva\n");
	return 0;
}
DWORD GetFunctionAddrByName(LPVOID Buffer, LPSTR Name)
{
	PIMAGE_DOS_HEADER	DosHeader;
	PIMAGE_NT_HEADERS	NtHeader;
	PIMAGE_FILE_HEADER	FileHeader;
	PIMAGE_OPTIONAL_HEADER	OpFileHeader;
	PIMAGE_SECTION_HEADER	SectionHeader;
	PIMAGE_EXPORT_DIRECTORY	ExportDirectory;

	DWORD Foa;

	DosHeader = (PIMAGE_DOS_HEADER)Buffer;
	NtHeader = (PIMAGE_NT_HEADERS)((DWORD)Buffer + DosHeader->e_lfanew);
	FileHeader = (PIMAGE_FILE_HEADER)((DWORD)NtHeader + 0x4);
	OpFileHeader = (PIMAGE_OPTIONAL_HEADER)((DWORD)FileHeader + IMAGE_SIZEOF_FILE_HEADER);
	SectionHeader = (PIMAGE_SECTION_HEADER)((DWORD)OpFileHeader + FileHeader->SizeOfOptionalHeader);

	Foa = RvaTurnFoa(Buffer, OpFileHeader->DataDirectory->VirtualAddress);
	ExportDirectory = (PIMAGE_EXPORT_DIRECTORY)((DWORD)Buffer + Foa);

	PIMAGE_THUNK_DATA		ThunkFunctions;
	ThunkFunctions = (PIMAGE_THUNK_DATA)((DWORD)Buffer + RvaTurnFoa(Buffer, ExportDirectory->AddressOfFunctions));

	PIMAGE_IMPORT_BY_NAME	ImportNameOrdinals;
	ImportNameOrdinals = (PIMAGE_IMPORT_BY_NAME)((DWORD)Buffer + RvaTurnFoa(Buffer, ExportDirectory->AddressOfNameOrdinals));

	PIMAGE_THUNK_DATA		ThunkName;
	ThunkName = (PIMAGE_THUNK_DATA)((DWORD)Buffer + RvaTurnFoa(Buffer, ExportDirectory->AddressOfNames));


	int Mark = 0;
	BOOL len;
	for (int i = 0; i < (int)ExportDirectory->NumberOfNames + 1; i++)
	{
		len = strcmp(Name, (LPSTR)((DWORD)Buffer + RvaTurnFoa(Buffer, ThunkName->u1.ForwarderString)));
		if (len == 0)
		{
			printf("�ѳɹ��ҵ�������\n");
			break;
		}
		else if (i == ExportDirectory->NumberOfNames)
		{
			printf("δ�ҵ���Ҫ���ҵĺ���\n");
			return 0;
		}
		ThunkName = (PIMAGE_THUNK_DATA)(DWORD)ThunkName + 0x1;
		ImportNameOrdinals = (PIMAGE_IMPORT_BY_NAME)((DWORD)ImportNameOrdinals + 0x2);
		Mark++;
	}

	//ThunkName = (PIMAGE_THUNK_DATA)(DWORD)ThunkName - 0x1;
	//ImportNameOrdinals = (PIMAGE_IMPORT_BY_NAME)((DWORD)ImportNameOrdinals - 0x2);
	printf("����������%s	\n", (DWORD)Buffer + RvaTurnFoa(Buffer, ThunkName->u1.ForwarderString));
	printf("�����������%x	\n", ImportNameOrdinals->Hint + ExportDirectory->Base);
	for (int n = 0; n < ImportNameOrdinals->Hint; n++)
	{
		ThunkFunctions = (PIMAGE_THUNK_DATA)(DWORD)ThunkFunctions + 0x1;
	}
	printf("������ַ��%x	\n", ThunkFunctions->u1.Function + OpFileHeader->ImageBase);

	return 1;
}
DWORD GetFunctionAddrByOrdinals(LPVOID Buffer, int n)
{
	PIMAGE_DOS_HEADER	DosHeader;
	PIMAGE_NT_HEADERS	NtHeader;
	PIMAGE_FILE_HEADER	FileHeader;
	PIMAGE_OPTIONAL_HEADER	OpFileHeader;
	PIMAGE_SECTION_HEADER	SectionHeader;
	PIMAGE_EXPORT_DIRECTORY	ExportDirectory;

	DWORD Foa;

	DosHeader = (PIMAGE_DOS_HEADER)Buffer;
	NtHeader = (PIMAGE_NT_HEADERS)((DWORD)Buffer + DosHeader->e_lfanew);
	FileHeader = (PIMAGE_FILE_HEADER)((DWORD)NtHeader + 0x4);
	OpFileHeader = (PIMAGE_OPTIONAL_HEADER)((DWORD)FileHeader + IMAGE_SIZEOF_FILE_HEADER);
	SectionHeader = (PIMAGE_SECTION_HEADER)((DWORD)OpFileHeader + FileHeader->SizeOfOptionalHeader);

	Foa = RvaTurnFoa(Buffer, OpFileHeader->DataDirectory->VirtualAddress);
	ExportDirectory = (PIMAGE_EXPORT_DIRECTORY)((DWORD)Buffer + Foa);

	PIMAGE_THUNK_DATA		ThunkFunctions;
	ThunkFunctions = (PIMAGE_THUNK_DATA)((DWORD)Buffer + RvaTurnFoa(Buffer, ExportDirectory->AddressOfFunctions));

	PIMAGE_IMPORT_BY_NAME	ImportNameOrdinals;
	ImportNameOrdinals = (PIMAGE_IMPORT_BY_NAME)((DWORD)Buffer + RvaTurnFoa(Buffer, ExportDirectory->AddressOfNameOrdinals));

	PIMAGE_THUNK_DATA		ThunkName;
	ThunkName = (PIMAGE_THUNK_DATA)((DWORD)Buffer + RvaTurnFoa(Buffer, ExportDirectory->AddressOfNames));


	int Mark = 0;
	for (int i = 0; i < (int)ExportDirectory->NumberOfNames + 1; i++)
	{
		if (ImportNameOrdinals->Hint + ExportDirectory->Base == n)
		{
			printf("���ҵ�����\n");
			break;
		}
		else if (i == ExportDirectory->NumberOfNames)
		{
			printf("δ�ҵ���Ҫ���ҵ����\n");
			return 0;
		}
		ThunkName = (PIMAGE_THUNK_DATA)(DWORD)ThunkName + 0x1;
		ImportNameOrdinals = (PIMAGE_IMPORT_BY_NAME)((DWORD)ImportNameOrdinals + 0x2);
		Mark++;
	}

	//ThunkName = (PIMAGE_THUNK_DATA)(DWORD)ThunkName - 0x1;
	//ImportNameOrdinals = (PIMAGE_IMPORT_BY_NAME)((DWORD)ImportNameOrdinals - 0x2);
	printf("����������%s	\n", (DWORD)Buffer + RvaTurnFoa(Buffer, ThunkName->u1.ForwarderString));
	printf("�����������%x	\n", ImportNameOrdinals->Hint + ExportDirectory->Base);
	for (int n = 0; n < ImportNameOrdinals->Hint; n++)
	{
		ThunkFunctions = (PIMAGE_THUNK_DATA)(DWORD)ThunkFunctions + 0x1;
	}
	printf("������ַ��%x	\n", ThunkFunctions->u1.Function + OpFileHeader->ImageBase);

	return 1;

}
DWORD PrintfRelocation(LPVOID Buffer)
{
	PIMAGE_DOS_HEADER	DosHeader;
	PIMAGE_NT_HEADERS	NtHeader;
	PIMAGE_FILE_HEADER	FileHeader;
	PIMAGE_OPTIONAL_HEADER	OpFileHeader;
	PIMAGE_SECTION_HEADER	SectionHeader;

	DWORD Foa;

	DosHeader = (PIMAGE_DOS_HEADER)Buffer;
	NtHeader = (PIMAGE_NT_HEADERS)((DWORD)Buffer + DosHeader->e_lfanew);
	FileHeader = (PIMAGE_FILE_HEADER)((DWORD)NtHeader + 0x4);
	OpFileHeader = (PIMAGE_OPTIONAL_HEADER)((DWORD)FileHeader + IMAGE_SIZEOF_FILE_HEADER);
	SectionHeader = (PIMAGE_SECTION_HEADER)((DWORD)OpFileHeader + FileHeader->SizeOfOptionalHeader);

	PIMAGE_BASE_RELOCATION	Baserelocation;
	Foa = RvaTurnFoa(Buffer, OpFileHeader->DataDirectory[5].VirtualAddress);
	Baserelocation = (PIMAGE_BASE_RELOCATION)((DWORD)Buffer + Foa);
	int len = 1;
	int q = 1;
	while (1)
	{
		if (Baserelocation->VirtualAddress == 0)
		{
			break;
		}
		printf("�ض�λ��ַ%x\n", Baserelocation->VirtualAddress);
		printf("�ض�λ��С%x\n", Baserelocation->SizeOfBlock);
		for (int i = 1; i < FileHeader->NumberOfSections; i++)
		{
			if (Baserelocation->VirtualAddress >= SectionHeader->VirtualAddress  \
				&& Baserelocation->VirtualAddress < (SectionHeader->VirtualAddress + SectionHeader->SizeOfRawData))
			{
				break;
			}
			else
			{
				SectionHeader = (PIMAGE_SECTION_HEADER)((DWORD)SectionHeader + IMAGE_SIZEOF_SECTION_HEADER);
			}
		}
		printf("�ض�λ��ַ��%s����\n", SectionHeader->Name);
		printf("���ض�λ�ĵ�ַ\t�Ƿ���Ҫ�ض�λ�б�\t\n");
		SectionHeader = (PIMAGE_SECTION_HEADER)((DWORD)OpFileHeader + FileHeader->SizeOfOptionalHeader);
		WORD* dizhi = NULL;
		for (int i = 0; i < (int)(Baserelocation->SizeOfBlock - 0x8) / 2; i++)
		{
			dizhi = (WORD*)((DWORD)Baserelocation + 0x8 + (i * 2));
			printf("FOA��ַ��%x\t", RvaTurnFoa(Buffer, (dizhi[0] & 0xFFF) + Baserelocation->VirtualAddress));
			printf("��Ǻ�:%x\t\n", *dizhi >> 12);
			q++;
		}

		printf("**************************\n");
		len++;
		Baserelocation = (PIMAGE_BASE_RELOCATION)((DWORD)Baserelocation + Baserelocation->SizeOfBlock);
	}
	printf("�ض�λ����%d��\n", len);
	printf("�ض�λ����%d��\n", q);
	return 0;
}
DWORD NewList(LPVOID* FileBuffer)
{
	PIMAGE_DOS_HEADER	DosHeader;
	PIMAGE_NT_HEADERS	NtHeader;
	PIMAGE_FILE_HEADER	FileHeader;
	PIMAGE_OPTIONAL_HEADER	OpFileHeader;
	PIMAGE_SECTION_HEADER	SectionHeader;
	PIMAGE_SECTION_HEADER	NewSectionHeader;

	DosHeader = (PIMAGE_DOS_HEADER)*FileBuffer;
	NtHeader = (PIMAGE_NT_HEADERS)((DWORD)*FileBuffer + DosHeader->e_lfanew);
	FileHeader = (PIMAGE_FILE_HEADER)((DWORD)NtHeader + 0x4);
	OpFileHeader = (PIMAGE_OPTIONAL_HEADER)((DWORD)FileHeader + IMAGE_SIZEOF_FILE_HEADER);
	SectionHeader = (PIMAGE_SECTION_HEADER)((DWORD)OpFileHeader + FileHeader->SizeOfOptionalHeader);
	NewSectionHeader = (PIMAGE_SECTION_HEADER)((DWORD)OpFileHeader + FileHeader->SizeOfOptionalHeader);

	DWORD Foa = NULL;
	LPVOID LenList = NULL;
	DWORD len = 0;
	LPVOID NewFileBuffer = NULL;

	//ͨ��ѭ���������ڱ��
	for (int i = 0; i < FileHeader->NumberOfSections; i++)
	{
		NewSectionHeader = (PIMAGE_SECTION_HEADER)((DWORD)NewSectionHeader + IMAGE_SIZEOF_SECTION_HEADER);
	}
	//�ж������ڵĿռ��Ƿ��㹻
	for (int i = 0; i < 0x80; i++)
	{
		if (*(PWORD)((DWORD)NewSectionHeader + i) != 0x00)
		{
			printf("�����ڱ�ռ䲻��\n");
			return 0;
		}
		len++;
	}
	strcpy((char*)NewSectionHeader->Name, ".NewLen");
	NewSectionHeader->Misc.VirtualSize = 0x1000;
	NewSectionHeader->Characteristics = NewSectionHeader->Characteristics | SectionHeader->Characteristics;

	for (int i = 1; i < FileHeader->NumberOfSections; i++)
	{
		SectionHeader = (PIMAGE_SECTION_HEADER)((DWORD)SectionHeader + IMAGE_SIZEOF_SECTION_HEADER);
	}
	NewSectionHeader->SizeOfRawData = 0x1000;
	NewSectionHeader->PointerToRawData = SectionHeader->PointerToRawData + SectionHeader->SizeOfRawData;
	NewSectionHeader->VirtualAddress = SectionHeader->VirtualAddress + SectionHeader->SizeOfRawData;
	if (NewSectionHeader->VirtualAddress % 0x1000 != 0)
	{
		NewSectionHeader->VirtualAddress = NewSectionHeader->VirtualAddress - (NewSectionHeader->VirtualAddress % 0x1000) + 0x1000;
	}
	FileHeader->NumberOfSections += 0x1;
	OpFileHeader->SizeOfImage += 0x1000;

	NewFileBuffer = malloc(NewSectionHeader->PointerToRawData + NewSectionHeader->SizeOfRawData);
	if (!NewFileBuffer)
	{
		printf("�ռ�δ����ɹ�\n");
		free(*FileBuffer);
		return 0;
	}

	memset(NewFileBuffer, 0, NewSectionHeader->PointerToRawData + NewSectionHeader->SizeOfRawData);
	memcpy(NewFileBuffer, *FileBuffer, SectionHeader->PointerToRawData + SectionHeader->SizeOfRawData);

	/*SectionHeader = (PIMAGE_SECTION_HEADER)((DWORD)OpFileHeader + FileHeader->SizeOfOptionalHeader);
	for (int i = 1; i < FileHeader->NumberOfSections-1;i++)
	{
		memcpy((LPVOID)((DWORD)NewFileBuffer + SectionHeader->PointerToRawData), (LPVOID)((DWORD)*FileBuffer + SectionHeader->PointerToRawData), SectionHeader->SizeOfRawData);
		SectionHeader = (PIMAGE_SECTION_HEADER)((DWORD)SectionHeader + IMAGE_SIZEOF_SECTION_HEADER);
	}*/
	Foa = NewSectionHeader->PointerToRawData;
	size = NewSectionHeader->PointerToRawData + NewSectionHeader->SizeOfRawData;
	free(*FileBuffer);
	*FileBuffer = NewFileBuffer;
	return Foa;
}
DWORD MoveList(LPVOID* FileBuffer)
{
	DWORD Fov = 0;
	Fov = NewList(&*FileBuffer);


	PIMAGE_DOS_HEADER	DosHeader;
	PIMAGE_NT_HEADERS	NtHeader;
	PIMAGE_FILE_HEADER	FileHeader;
	PIMAGE_OPTIONAL_HEADER	OpFileHeader;
	PIMAGE_SECTION_HEADER	SectionHeader;

	//������
	PIMAGE_EXPORT_DIRECTORY	ExportDirectory;
	PIMAGE_THUNK_DATA		ThunkFunctions;			//������ַ��
	PIMAGE_IMPORT_BY_NAME	ImportNameOrdinals;		//������ű�
	PIMAGE_THUNK_DATA		ThunkName;				//�������Ʊ�

	DosHeader = (PIMAGE_DOS_HEADER)*FileBuffer;
	NtHeader = (PIMAGE_NT_HEADERS)((DWORD)*FileBuffer + DosHeader->e_lfanew);
	FileHeader = (PIMAGE_FILE_HEADER)((DWORD)NtHeader + 0x4);
	OpFileHeader = (PIMAGE_OPTIONAL_HEADER)((DWORD)FileHeader + IMAGE_SIZEOF_FILE_HEADER);
	SectionHeader = (PIMAGE_SECTION_HEADER)((DWORD)OpFileHeader + FileHeader->SizeOfOptionalHeader);

	//������
	ExportDirectory = (PIMAGE_EXPORT_DIRECTORY)((DWORD)*FileBuffer + RvaTurnFoa(*FileBuffer, OpFileHeader->DataDirectory[0].VirtualAddress));
	ThunkFunctions = (PIMAGE_THUNK_DATA)((DWORD)*FileBuffer + RvaTurnFoa(*FileBuffer, ExportDirectory->AddressOfFunctions));
	ImportNameOrdinals = (PIMAGE_IMPORT_BY_NAME)((DWORD)*FileBuffer + RvaTurnFoa(*FileBuffer, ExportDirectory->AddressOfNameOrdinals));
	ThunkName = (PIMAGE_THUNK_DATA)((DWORD)*FileBuffer + RvaTurnFoa(*FileBuffer, ExportDirectory->AddressOfNames));

	//ѭ����ȡ����
	for (int i = 1; i < FileHeader->NumberOfSections; i++)
	{
		SectionHeader = (PIMAGE_SECTION_HEADER)((DWORD)SectionHeader + IMAGE_SIZEOF_SECTION_HEADER);
	}

	//����ڶ��ռ�
	LPVOID LenBuffer = NULL;
	size = SectionHeader->PointerToRawData + SectionHeader->SizeOfRawData;
	LenBuffer = malloc(SectionHeader->PointerToRawData + SectionHeader->SizeOfRawData);
	if (!LenBuffer)
	{
		printf("������ʱ�ռ�ʧ��");
	}
	memset(LenBuffer, 0, SectionHeader->SizeOfRawData);
	memcpy(LenBuffer, *FileBuffer, SectionHeader->PointerToRawData + SectionHeader->SizeOfRawData);

	//�ƶ�������
	memcpy((LPVOID)((DWORD)*FileBuffer + Fov), (LPVOID)((DWORD)LenBuffer + (DWORD)((DWORD)ExportDirectory - (DWORD)*FileBuffer)), sizeof(IMAGE_EXPORT_DIRECTORY));
	//memset((LPVOID)((DWORD)*FileBuffer + (DWORD)ExportDirectory, 0, sizeof(IMAGE_EXPORT_DIRECTORY));

	//�ƶ�������ַ��
	DWORD len = (DWORD)(ThunkFunctions + ExportDirectory->NumberOfFunctions);
	memcpy((LPVOID)((DWORD)*FileBuffer + (Fov + sizeof(IMAGE_EXPORT_DIRECTORY))),
		(LPVOID)((DWORD)LenBuffer + (DWORD)((DWORD)ThunkFunctions - (DWORD)*FileBuffer)),
		(DWORD)(ThunkFunctions + ExportDirectory->NumberOfFunctions) - (DWORD)ThunkFunctions);

	//�ƶ�������ű�
	DWORD biao = Fov + sizeof(IMAGE_EXPORT_DIRECTORY) + (DWORD)(ThunkFunctions + ExportDirectory->NumberOfFunctions) - (DWORD)ThunkFunctions;
	DWORD Sizezhang[100];
	memcpy((LPVOID)((DWORD)*FileBuffer + biao),
		(LPVOID)((DWORD)LenBuffer + ((DWORD)ImportNameOrdinals - (DWORD)*FileBuffer)),
		(DWORD)(0x2 * ExportDirectory->NumberOfFunctions));

	biao += (0x2 * ExportDirectory->NumberOfFunctions);
	//�ƶ��������Ʊ�
	memcpy((LPVOID)((DWORD)*FileBuffer + biao),
		(LPVOID)((DWORD)LenBuffer + (DWORD)((DWORD)ThunkName - (DWORD)*FileBuffer)),
		(DWORD)(ThunkName + ExportDirectory->NumberOfFunctions) - (DWORD)ThunkName);

	biao += ((DWORD)(ThunkName + ExportDirectory->NumberOfFunctions) - (DWORD)ThunkName);
	DWORD biao2 = biao;
	for (int i = 0; i < (int)ExportDirectory->NumberOfFunctions; i++)
	{
		printf("%s\n", (CHAR*)((DWORD)*FileBuffer + RvaTurnFoa(*FileBuffer, ThunkName->u1.Function)));
		Sizezhang[i] = strlen((CHAR*)((DWORD)*FileBuffer + RvaTurnFoa(*FileBuffer, ThunkName->u1.Function))) + 1;
		memcpy((LPVOID)((DWORD)*FileBuffer + biao), (LPVOID)((DWORD)LenBuffer + RvaTurnFoa(LenBuffer, ThunkName->u1.Function)), Sizezhang[i]);
		biao += Sizezhang[i];
		ThunkName++;
	}
	memset(ExportDirectory, 0, biao - Fov);

	//�޸�ָ��
	OpFileHeader->DataDirectory[0].VirtualAddress = FoaTurnRva(*FileBuffer, Fov);
	ExportDirectory = (PIMAGE_EXPORT_DIRECTORY)((DWORD)*FileBuffer + RvaTurnFoa(*FileBuffer, OpFileHeader->DataDirectory[0].VirtualAddress));
	ExportDirectory->AddressOfFunctions = FoaTurnRva(*FileBuffer, Fov + sizeof(IMAGE_EXPORT_DIRECTORY));
	ExportDirectory->AddressOfNameOrdinals = FoaTurnRva(*FileBuffer, Fov + sizeof(IMAGE_EXPORT_DIRECTORY) + ((DWORD)(ThunkFunctions + ExportDirectory->NumberOfFunctions) - (DWORD)ThunkFunctions));
	ExportDirectory->AddressOfNames = FoaTurnRva(*FileBuffer, Fov + sizeof(IMAGE_EXPORT_DIRECTORY) + ((DWORD)(ThunkFunctions + ExportDirectory->NumberOfFunctions) - (DWORD)ThunkFunctions) + (0x2 * ExportDirectory->NumberOfFunctions));
	ThunkName = (PIMAGE_THUNK_DATA)((DWORD)*FileBuffer + RvaTurnFoa(*FileBuffer, ExportDirectory->AddressOfNames));
	for (int i = 0; i < (int)ExportDirectory->NumberOfNames; i++)
	{
		ThunkName->u1.ForwarderString = FoaTurnRva(*FileBuffer, biao2);
		biao2 += Sizezhang[i];
		ThunkName++;
	}
	return 0;
}
DWORD SaveFile(LPVOID FileBuffer)
{
	FILE* p = NULL;
	p = fopen("C:\\Users\\Administrator\\Desktop\\4.exe", "wb+");
	if (!p)
	{
		printf("�ļ�����ʧ��\n");
		free(FileBuffer);
		return 0;
	}
	fwrite(FileBuffer, size, 1, p);
	fclose(p);
	free(FileBuffer);
	return 1;
}


void MoveRelocation(LPVOID* FileBuffer)
{
	DWORD isOk;
	DWORD NewLength = 0;
	PVOID LastSection = NULL;
	PVOID CodeSection = NULL;
	PVOID AddressOfSectionTable = NULL;

	PWORD Location = NULL;
	DWORD RVA_Data;
	WORD reloData;



	DWORD NodeFov = 0;
	DWORD Fov = 0;
	NodeFov = NewList(&*FileBuffer);


	PIMAGE_DOS_HEADER	DosHeader;
	PIMAGE_NT_HEADERS	NtHeader;
	PIMAGE_FILE_HEADER	FileHeader;
	PIMAGE_OPTIONAL_HEADER	OpFileHeader;
	PIMAGE_SECTION_HEADER	SectionHeader;

	//������
	PIMAGE_EXPORT_DIRECTORY	ExportDirectory;
	PIMAGE_THUNK_DATA		ThunkFunctions;			//������ַ��
	PIMAGE_IMPORT_BY_NAME	ImportNameOrdinals;		//������ű�
	PIMAGE_THUNK_DATA		ThunkName;				//�������Ʊ�

	DosHeader = (PIMAGE_DOS_HEADER)*FileBuffer;
	NtHeader = (PIMAGE_NT_HEADERS)((DWORD)*FileBuffer + DosHeader->e_lfanew);
	FileHeader = (PIMAGE_FILE_HEADER)((DWORD)NtHeader + 0x4);
	OpFileHeader = (PIMAGE_OPTIONAL_HEADER)((DWORD)FileHeader + IMAGE_SIZEOF_FILE_HEADER);
	SectionHeader = (PIMAGE_SECTION_HEADER)((DWORD)OpFileHeader + FileHeader->SizeOfOptionalHeader);

	PIMAGE_BASE_RELOCATION RelocationDirectory;

	//��ȡ�ṹ
	Fov = RvaTurnFoa(*FileBuffer, OpFileHeader->DataDirectory[5].VirtualAddress);
	RelocationDirectory = (PIMAGE_BASE_RELOCATION)((DWORD)*FileBuffer + Fov);
	DWORD AllSizeOfBlock = 0;
	DWORD pRelocationDirectory;
	//printf("%x",pRelocationDirectory->VirtualAddress);

	//��ȡ�ض�λ���С
	while (1)
	{
		if (RelocationDirectory->VirtualAddress != 0)
		{
			AllSizeOfBlock += RelocationDirectory->SizeOfBlock;
			RelocationDirectory = (PIMAGE_BASE_RELOCATION)((DWORD)RelocationDirectory + (DWORD)RelocationDirectory->SizeOfBlock);
		}
		if (RelocationDirectory->VirtualAddress == 0)
		{
			break;
		}
	}
	for (int i = 1; i < FileHeader->NumberOfSections;i++)
	{
		SectionHeader = (PIMAGE_SECTION_HEADER)((DWORD)SectionHeader + IMAGE_SIZEOF_SECTION_HEADER);
	}

	//����ڶ��ռ�
	LPVOID LenBuffer = NULL;
	LenBuffer = malloc(SectionHeader->PointerToRawData + SectionHeader->SizeOfRawData);
	if (!LenBuffer)
	{
		printf("������ʱ�ռ�ʧ��");
	}
	memset(LenBuffer, 0, SectionHeader->PointerToRawData + SectionHeader->SizeOfRawData);
	memcpy(LenBuffer, *FileBuffer, SectionHeader->PointerToRawData + SectionHeader->SizeOfRawData);


	//�����ض�λ�������Ľ�������
	memcpy((LPVOID)((DWORD)*FileBuffer + Fov), (LPVOID)((DWORD)LenBuffer + RvaTurnFoa(LenBuffer,OpFileHeader->DataDirectory[5].VirtualAddress)), AllSizeOfBlock);

	OpFileHeader->DataDirectory[5].VirtualAddress = FoaTurnRva(*FileBuffer,Fov);
	free(LenBuffer);

	//�޸�DLL��ImageBase
	//pImageOptionalHeader->ImageBase += 1000;

	//=============================================================
	//=============================================================
	//=============================================================
	//=============================================================
	RelocationDirectory = (PIMAGE_BASE_RELOCATION)((DWORD)*FileBuffer + (DWORD)Fov); //��λ��һ���ض�λ�� �ļ��еĵ�ַ

	while (RelocationDirectory->SizeOfBlock && RelocationDirectory->VirtualAddress){
		printf("VirtualAddress    :%08X\n", RelocationDirectory->VirtualAddress);
		printf("SizeOfBlock       :%08X\n", RelocationDirectory->SizeOfBlock);
		printf("================= BlockData Start ======================\n");


		DWORD NumberOfRelocation = (RelocationDirectory->SizeOfBlock - 8) / 2;// ÿ���ض�λ���е������������

		PWORD LocaTion = (PWORD)((DWORD)RelocationDirectory + 8); // ����8���ֽ�

		for (int i = 0; i < (int)NumberOfRelocation; i++){
			if (LocaTion[i] >> 12 != 0){ //�ж��Ƿ�����������
				// WORD���͵ı������н���
				reloData = (Location[i] & 0xFFF); //������������ ֻȡ4�ֽ� �����Ƶĺ�12λ
				RVA_Data = RelocationDirectory->VirtualAddress + reloData; //�����RVA�ĵ�ַ
				Fov = RvaTurnFoa(*FileBuffer, RVA_Data);
				printf("��[%04X]��  �����������Ϊ:[%04X]  ��������Ϊ:[%X]  RVA�ĵ�ַΪ:[%08X]  �ض�λ������:[%08X]\n"
					, i + 1
					, reloData
					, (Location[i] >> 12)
					, RVA_Data
					, *(PDWORD)((DWORD)*FileBuffer + (DWORD)Fov));

				//������������ �����޸��ض�λ�������imagebase����������1000����ôҪ�޸��ĵ�ַ����Ҫ����1000
				*(PDWORD)((DWORD)*FileBuffer + (DWORD)Fov) = *(PDWORD)((DWORD)*FileBuffer + (DWORD)Fov) + 1000;
			}
		}
		RelocationDirectory = (PIMAGE_BASE_RELOCATION)((DWORD)RelocationDirectory + (DWORD)RelocationDirectory->SizeOfBlock); //�����forѭ�����֮����ת���¸��ض�λ�� �������ϵĲ���
	}

}