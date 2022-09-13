#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <windows.h>
#include <stdlib.h>

//char FILEPATH_IN[] = "D:/ipmsg.exe";
char FILEPATH_IN[] = "C:\\Windows\\System32\\notepad.exe";
char FILEPATH_OUT[] = "C:/copyxx.exe";


//1��File-> FileBuffer
//2����λ�����
DWORD ReadPEFile(IN LPSTR lpszFile, OUT LPVOID* pFileBuffer)
{
	FILE* fp = NULL;
	DWORD fileSize = 0;
	LPVOID pBuffer = NULL;

	fp = fopen(lpszFile, "rb");
	if (!fp)
	{
		printf("lpszFile��ʧ��\n");
		return 0;
	}
	//��ȡ�ļ���С
	fseek(fp, 0, SEEK_END);
	fileSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	//���仺����
	pBuffer = malloc(fileSize);
	if (!pBuffer)
	{
		printf("pBuffer����ռ�ʧ��\n");
		fclose(fp);
		return 0;
	}

	//���ļ����ݶ�ȡ��������
	size_t n = fread(pBuffer, fileSize,1, fp);
	if (!n)
	{
		printf("��ȡ����ʧ��");
		free(pBuffer);		//�ͷ��ڴ�
		fclose(fp);			//�ر��ļ�
		return NULL;
	}


	*pFileBuffer = pBuffer;
	fclose(fp);
	pBuffer = NULL;
	return fileSize;

}


// RVA ->  FOA
DWORD RvaToFoa(DWORD dwRVA, LPVOID pFileBuffer)
{
	DWORD FOA = NULL;

	PIMAGE_DOS_HEADER pDos = NULL;
	PIMAGE_FILE_HEADER pPE = NULL;
	PIMAGE_OPTIONAL_HEADER32 pOP = NULL;
	PIMAGE_SECTION_HEADER  pSect = NULL;


	if (!pFileBuffer)
	{
		printf("pFileBuffer��Чָ��\n");
		return 0;
	}

	pDos = (PIMAGE_DOS_HEADER)pFileBuffer;
	pPE = (PIMAGE_FILE_HEADER)((DWORD)pDos + pDos->e_lfanew + 4);
	pOP = (PIMAGE_OPTIONAL_HEADER32)((DWORD)pPE + IMAGE_SIZEOF_FILE_HEADER);
	pSect = (PIMAGE_SECTION_HEADER)((DWORD)pOP + pPE->SizeOfOptionalHeader);

	if (*(PWORD)pDos != IMAGE_DOS_SIGNATURE)
	{
		printf("������ЧMZ\n");
		return 0;
	}
	if (*(PDWORD)((DWORD)pDos + pDos->e_lfanew )!= IMAGE_NT_SIGNATURE)
	{
		printf("������ЧPE\n");
		return 0;
	}


	if (dwRVA <= pOP->SizeOfHeaders)
	{
		return dwRVA;
	}

	for (DWORD i = 0; i < pPE->NumberOfSections; i++)
	{
		if (dwRVA >= pSect->VirtualAddress && dwRVA <= pSect->VirtualAddress + pSect->Misc.VirtualSize)
		{
			FOA = dwRVA - pSect->VirtualAddress + pSect->PointerToRawData;
			return FOA;
		}
		pSect = (PIMAGE_SECTION_HEADER)((DWORD)pSect + IMAGE_SIZEOF_SECTION_HEADER);
	}
}



// FOA ->  RVA
DWORD FoaToRva(DWORD dwFOA, LPVOID pFileBuffer)
{
	DWORD RVA = NULL;
	PIMAGE_DOS_HEADER pDos = NULL;
	PIMAGE_FILE_HEADER pPE = NULL;
	PIMAGE_OPTIONAL_HEADER32 pOP = NULL;
	PIMAGE_SECTION_HEADER  pSect = NULL;


	if (!pFileBuffer)
	{
		printf("pFileBuffer��Чָ��\n");
		return 0;
	}

	pDos = (PIMAGE_DOS_HEADER)pFileBuffer;
	pPE = (PIMAGE_FILE_HEADER)((DWORD)pDos + pDos->e_lfanew + 0x4);
	pOP = (PIMAGE_OPTIONAL_HEADER32)((DWORD)pPE + IMAGE_SIZEOF_FILE_HEADER);
	pSect = (PIMAGE_SECTION_HEADER)((DWORD)pOP + pPE->SizeOfOptionalHeader);

	if (*(PWORD)pDos != IMAGE_DOS_SIGNATURE)
	{
		printf("������ЧMZ\n");
		return 0;
	}
	if (*(PDWORD)((DWORD)pDos + pDos->e_lfanew) != IMAGE_NT_SIGNATURE)
	{
		printf("������ЧPE\n");
		return 0;
	}

	if (dwFOA <= pOP->SizeOfHeaders)
	{
		return dwFOA;
	}

	for (DWORD i = 0; i < pPE->NumberOfSections; i++, pSect++)
	{
		if (dwFOA >= pSect->PointerToRawData && dwFOA <= pSect->PointerToRawData + pSect->SizeOfRawData)
		{
			RVA = dwFOA - pSect->PointerToRawData + pSect->VirtualAddress;
			return RVA;
		}
	}

}

//// ��������
VOID PrintImport()
{
 
	DWORD Size = 0;
	LPVOID pFileBuffer = NULL;

	//FILE   ->  FileBuffer   //���ú�����ȡ�ļ�����
	Size = ReadPEFile(FILEPATH_IN, &pFileBuffer);
	if (!pFileBuffer || !Size)
	{
			printf("File-> FileBufferʧ��\n");
			return;
	}

	PIMAGE_DOS_HEADER  pDos = NULL;
	PIMAGE_FILE_HEADER  pPE = NULL;
	PIMAGE_OPTIONAL_HEADER32 pOP = NULL;
	PIMAGE_IMPORT_DESCRIPTOR  pImportDirectory = NULL; //�����ṹ��

	pDos = (PIMAGE_DOS_HEADER)pFileBuffer;
	pPE = (PIMAGE_FILE_HEADER)((DWORD)pDos + pDos->e_lfanew + 0x4);
	pOP = (PIMAGE_OPTIONAL_HEADER32)((DWORD)pPE + IMAGE_SIZEOF_FILE_HEADER);

	DWORD ImportRVA = pOP->DataDirectory[1].VirtualAddress; //RVA
	DWORD ImportFOA = 0;

	//	�жϵ�����Ƿ����
	if (ImportRVA == 0)
	{
		printf("���������\n");
		return;
	}

	//�����FOA
	ImportFOA = RvaToFoa(ImportRVA, pFileBuffer); 
	if (ImportRVA == 0)
	{
		printf("ImportFOA RVA -> FOA ʧ��\n");
		return;
	}

	//��ȡ������ַ
	pImportDirectory = (PIMAGE_IMPORT_DESCRIPTOR)((DWORD)pFileBuffer + ImportFOA);

	//ѭ����ӡÿһ����������Ϣ  ��Ҫ��ԱΪ0ʱ����ѭ��
	while (pImportDirectory->FirstThunk && pImportDirectory->OriginalFirstThunk)
	{
		//��ӡ������ļ���
		printf("=========================ImportTable %s Start=============================\n", \
			(PBYTE)((DWORD)pFileBuffer + RvaToFoa(pImportDirectory->Name, pFileBuffer)));
		//��ӡINT��RVA
		printf("OriginalFirstThunk RVA:%08X\n", pImportDirectory->OriginalFirstThunk);
		//��ȡINT���ַ
		PDWORD pOriginalFirstThunk = (PDWORD)((DWORD)pFileBuffer + RvaToFoa(pImportDirectory->OriginalFirstThunk, pFileBuffer));
		printf("%x - %x\n", pOriginalFirstThunk, *pOriginalFirstThunk);//��ӡINT��ĵ�ַ�����

		while (*pOriginalFirstThunk)
		{
			//�ж����λ�Ƿ�Ϊ 1  
			if (*pOriginalFirstThunk & 0x80000000)
			{
				//��λΪ1 �� ��ȥ���λ��ֵ���Ǻ����ĵ������
				printf("����ŵ���: %x\n",(*pOriginalFirstThunk)&0xFFF);
			}
			else
			{
				PIMAGE_IMPORT_BY_NAME pImageByName = (PIMAGE_IMPORT_BY_NAME)((DWORD)pFileBuffer + \
					RvaToFoa(*pOriginalFirstThunk, pFileBuffer));

				printf("�����ֵ���HIT/NAME: %x  -  %s\n", pImageByName->Hint, pImageByName->Name);
			}

			// ƫ�� �� ��һ��
			pOriginalFirstThunk = (PDWORD)((DWORD)pOriginalFirstThunk + sizeof(IMAGE_THUNK_DATA32));
		}

		printf("**********************************************************************\n");

		printf("FirstThunk RVA: %08x\n", pImportDirectory->FirstThunk);
		PDWORD	pFirstThunk_FOA = (PDWORD)((DWORD)pFileBuffer + RvaToFoa(pImportDirectory->FirstThunk, pFileBuffer));
		printf("%x - %x\n", pFirstThunk_FOA, *pFirstThunk_FOA); //��ӡIAT��ĵ�ַ�����

		while (*pFirstThunk_FOA)
		{
			if (*pFirstThunk_FOA & 0x80000000)
			{
				printf("����ŵ���: %x\n", (*pFirstThunk_FOA) & 0xFFF);
			}
			else
			{
				PIMAGE_IMPORT_BY_NAME pImageByName = (PIMAGE_IMPORT_BY_NAME)((DWORD)pFileBuffer + \
					RvaToFoa(*pFirstThunk_FOA, pFileBuffer));
				printf("�����ֵ���HIT/NAME: %x  -  %s\n", pImageByName->Hint, pImageByName->Name);
			}
			pFirstThunk_FOA = (PDWORD)((DWORD)pFirstThunk_FOA + sizeof(IMAGE_THUNK_DATA32)); //ƫ�Ƶ� ��һ�� 
		}
		pImportDirectory++;
	}

	//�ͷ��ڴ�
	free(pFileBuffer);
	return;
}

//**********************************************************************
int main(int argc, char* argv[])

{
	PrintImport();
	getchar();
	return 0;
}