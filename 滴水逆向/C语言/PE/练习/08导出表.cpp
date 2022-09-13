#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<Windows.h>
#include<stdlib.h>
#define debug  0

//��ȡ�ļ�
DWORD ReadPEFile(char* Filepath, LPVOID* pFileBuffer)
{
	LPVOID pTempBuffer = NULL;
	FILE* pf = NULL;
	DWORD Size = 0;

	//��ȡ�ļ�
	pf = fopen(Filepath, "rb");
	if (!pf)
	{
		printf("�ļ���ȡʧ��\n");
		return 0;
	}
	fseek(pf, 0, SEEK_END);
	Size = ftell(pf);
	fseek(pf, 0, SEEK_SET);

	pTempBuffer = malloc(Size);
	if (!pTempBuffer)
	{
		printf("����������ʧ��\n");
		fclose(pf);
		return 0;
	}

    memset(pTempBuffer, 0, Size);
    fread(pTempBuffer,1,Size,pf);

	*pFileBuffer = pTempBuffer;
	pTempBuffer = NULL;
	fclose(pf);

	return Size;
}


// dwRva ĳ������Ŀ¼�� ��virtualAddress 
DWORD RvaToOffset(IN LPVOID pFileBuffer, DWORD dwRva)
{
	PIMAGE_DOS_HEADER			 pDos= NULL;
	PIMAGE_FILE_HEADER			 pPE = NULL;
	PIMAGE_OPTIONAL_HEADER32	 pOP = NULL;
	PIMAGE_SECTION_HEADER	   pSect = NULL;
	PIMAGE_SECTION_HEADER	   pTempSect = NULL;


	if(!pFileBuffer)
	{ 
		printf("Rva_Foa pFileBuffer ��Чָ��\n");
		return 0;
	}
	pDos = (PIMAGE_DOS_HEADER)pFileBuffer;
	if (*((PWORD)pDos) != IMAGE_DOS_SIGNATURE)
	{
		printf("����MZ���\n");
		return 0;
	}
	if (*((PDWORD)((DWORD)pDos + pDos->e_lfanew)) != IMAGE_NT_SIGNATURE)
	{
		printf("����PE���\n");
		return 0;
	}
	pPE = (PIMAGE_FILE_HEADER)((DWORD)pDos + pDos->e_lfanew + 0x4);
	pOP = (PIMAGE_OPTIONAL_HEADER32)((DWORD)pPE + IMAGE_SIZEOF_FILE_HEADER);
	pSect = (PIMAGE_SECTION_HEADER)((DWORD)pOP + pPE->SizeOfOptionalHeader);

	pTempSect = pSect;

	if (dwRva <= pOP->SizeOfHeaders)
	{
		printf("FoA:%x\n", dwRva);
		return dwRva;
	}
	for (int i = 0; i < pPE->NumberOfSections; i++, pTempSect++)
	{


		if (dwRva >= pTempSect->VirtualAddress && dwRva <= pTempSect->VirtualAddress + pTempSect->SizeOfRawData)
		{
			// dwRva - pTempSect->VirtualAddress   ������ƫ��
			// pTempSect->PointerToRawData  ���ε�buffer��ʼλ��ƫ��
			
			printf("FoA = %x\n", dwRva);
			return  dwRva - pTempSect->VirtualAddress + pTempSect->PointerToRawData;
		}
	}

	return 0;
}



//��ӡ������
void Printexport(LPVOID pFileBuffer)
{
	PIMAGE_DOS_HEADER		    pDos = NULL; 
	PIMAGE_NT_HEADERS		     pNT = NULL;
	PIMAGE_FILE_HEADER		     pPE = NULL;
	PIMAGE_OPTIONAL_HEADER32     pOp = NULL;
	PIMAGE_SECTION_HEADER	   pSect = NULL;
	PIMAGE_DATA_DIRECTORY	   pData = NULL;  //�洢������λ��
	PIMAGE_EXPORT_DIRECTORY	 pExport = NULL;  //�������׵�ַ

	DWORD		 Foa = 0;

	if (pFileBuffer == NULL)
	{
		printf("FileBuffer ��ȡʧ��!\r\n");
		return;
	}

	//�ж��Ƿ�����Ч��MZ��־
	if (*((PWORD)pFileBuffer) != IMAGE_DOS_SIGNATURE)
	{
		printf("��Ч��MZ��ʶ\r\n");
		return;
	}
	pDos = (PIMAGE_DOS_HEADER)pFileBuffer;

	//�ж��Ƿ�����Ч��PE��־
	if (*((PDWORD)((DWORD)pFileBuffer + pDos->e_lfanew)) != IMAGE_NT_SIGNATURE)
	{
		printf("��Ч��PE���\r\n");
		return;
	}
	//��λNTͷ
	pNT = (PIMAGE_NT_HEADERS)((DWORD)pFileBuffer + pDos->e_lfanew);
	pPE = (PIMAGE_FILE_HEADER)(((DWORD)pNT) + 4);
	pOp = (PIMAGE_OPTIONAL_HEADER32)((DWORD)pPE + IMAGE_SIZEOF_FILE_HEADER);

	//	pData = PIMAGE_DATA_DIRECTORY((&pOptionHeader->NumberOfRvaAndSizes + 1));
	pData = pOp->DataDirectory;
	Foa = RvaToOffset(pFileBuffer, pData->VirtualAddress);
	printf("FoaAddress: %#X \r\n", Foa);
	pExport = (PIMAGE_EXPORT_DIRECTORY)((DWORD)pDos + Foa);

	printf("\t\t RVA\t\t ��С\r\n");

	//��ӡ�����Ϣ����
	//#define IMAGE_NUMBEROF_DIRECTORY_ENTRIES    16

	//������һ�ֲִڵı���д����
	/*
	for (int i = 0; i < IMAGE_NUMBEROF_DIRECTORY_ENTRIES; i++,pDataDirectory++)
	{
		printf("%#08X \r\n",pDataDirectory->VirtualAddress);
		printf("%#08X \r\n",pDataDirectory->Size);
	}
	*/

	//��ʾÿ����Ŀ��λ�� ��С
	for (DWORD i = 0; i < IMAGE_NUMBEROF_DIRECTORY_ENTRIES; i++)
	{
		//DirectoryString(i);
		printf("%08X\t%08X\r\n", pData[i].VirtualAddress, pData[i].Size);
	}

	printf("***********************************************************\r\n");
	printf("����������ַ��(RVA)	: \t\t%#08X \r\n", pExport->AddressOfFunctions);
	printf("�����������Ʊ�(RVA) : \t\t%#08X \r\n", pExport->AddressOfNames);
	printf("����������ű�(RVA) : \t%#08X \r\n", pExport->AddressOfNameOrdinals);
	printf("����������ʼ��� : \t\t\t%#08X \r\n", pExport->Base);
	printf("pExportDirectory->Characteristics : \t\t%#08X \r\n", pExport->Characteristics);
	printf("pExportDirectory->MajorVersion : \t\t%#08X \r\n", pExport->MajorVersion);
	printf("pExportDirectory->MinorVersion : \t\t%#08X \r\n", pExport->MinorVersion);
	printf("ָ��õ������ļ��ļ����ַ��� : \t\t\t%#08X \r\n", pExport->Name);
	printf("���е��������ĸ��� : \t\t%#08X \r\n", pExport->NumberOfFunctions);
	printf("�Ժ������ֵ����ĺ������� : \t\t%#08X \r\n", pExport->NumberOfNames);
	printf("***********************************************************\r\n");


	//���嵼��������ַ��������ţ��������ַ��ţ��������ƶ�Ӧ�ļ��е�FOAλ�ã�
	//Name, AddressOfNames, AddressOfFunctions, AddressOfOrdinals;
	DWORD NameFoa = RvaToOffset(pFileBuffer, pExport->Name);
	DWORD AddressOfNamesFoa = RvaToOffset(pFileBuffer, pExport->AddressOfNames);
	DWORD AddressOfFunctionsFoa = RvaToOffset(pFileBuffer, pExport->AddressOfFunctions);
	DWORD AddressOfOrdinalsFoa = RvaToOffset(pFileBuffer, pExport->AddressOfNameOrdinals);

	//��ȡ���������ƣ�������ַ��������ű��������Ʊ�
	PBYTE pDllOrExeName = (PBYTE)((DWORD)pDos + NameFoa);
	//����֮����ʹ��PBYTE����ΪҪ��ӡÿ���ַ�����Ҫһ��һ���ֽڶ�ȡ��
	printf("�����������: %s \r\n", pDllOrExeName);//�����ӡ�����ľ���exe������ipmsg.exe

	//����������ַ�����ļ��е�λ��
	PDWORD pAddressFunctionTable = (PDWORD)((DWORD)pDos + AddressOfFunctionsFoa);
	printf("������ַ���λ��: %#08X \r\n", pAddressFunctionTable);

	//����������ű����ļ��е�λ��
	PDWORD pOrdinaFunctionTable = (PDWORD)((DWORD)pDos + AddressOfOrdinalsFoa);
	printf("������ű��λ��: %#08X \r\n", pOrdinaFunctionTable);

	//�����������Ʊ����ļ��е�λ��
	PDWORD pNameFunctionTable = (PDWORD)((DWORD)pDos + AddressOfNamesFoa);
	printf("�������Ʊ��λ��: %#08X \r\n", pNameFunctionTable);


	//�ж�������ŵ��������������Ժ������ֵ���
	BOOL indexNumIsExist = FALSE;
	/*indexNumIsExist --> �򵥵���⣬�����������Ҫ��õ������������±����ű��±�����֮��������ҵ���Ӧ
	��ͬ���±꣬��ô�������indexNumIsExist��TRUE��������FAlSE��

	��ϸ���ͣ����Ը��ݵ������������±�ţ���Ӧ��ű��е��±�ţ�����֮����бȶԣ�
	�������ű�͵����������Ʊ������ܹ��ҵ���Ӧ��ͬ���±���룬��ô�Ϳ��Ը�������ű����ҵ����±��
	��Ӧ��ֵ�����������Ӧ��ֵ���Ϳ����ڵ���������ַ�����ű���ȥѰ���±�Ϊ�����Ӧ��ֵ��Ȼ����Ƕ�Ӧ
	���������ĵ�ַ��
	*/
	for (DWORD n = 0; n < pExport->NumberOfFunctions; n++)
		//n �ǵ���������ַ���Ӧ���±꣬����NumberOfFunctions�ĸ�������
	{
		//��ȡ����������ַ�����ʼλ��;
		//printf("����������ַ���λ��: %#08X ",pAddressFunctionTable[n]);

		indexNumIsExist = FALSE;//�������ΪFALSE�ͱ�ʾ������ֱ��ͨ����ŵ��������Һ�����ַ
		//nNameIndex --> �������������±꣬��������Ǹ���NumberOfNames�������������濪ʼ�ж���֤�Ƿ���ԣ�
		DWORD nNameIndex;
		for (nNameIndex = 0; nNameIndex < pExport->NumberOfNames; nNameIndex++)
		{
			/*���ݵ����������Ƶ��±�(����)������������ֱ�ӽ����������±�ŵ�����ű���±꣬Ȼ��ͨ����ű�
			 ����ʼλ�ü��������ű���±�ȥ��λ�ó���ű��ж�Ӧ��ֵ���Ƿ���ڵ���������ַ����±꣬�����
			�±�����������Ƕ���õĲ���n���ǵ���������ַ�ĸ��������±�ţ������ȣ���ôindexNumIsExist
			����TRUE���ó����ۿ���ͨ���������Ƶ���������
			*/
			if (n == pOrdinaFunctionTable[nNameIndex])
			{
				indexNumIsExist = TRUE;
				break;
			}
		}

		if (indexNumIsExist == TRUE)
		{
			//������ȡ�������������Ʊ��ж�Ӧ�±�ĵ�ַ
			DWORD dwNameFoa = pNameFunctionTable[nNameIndex];//���ﻹ��Rva��ַ
			PBYTE pFunctionName = (PBYTE)((DWORD)pDos + RvaToOffset(pFileBuffer, dwNameFoa));

			//�����ǽ������������Ʊ��Ӧ�±�ĵ�ַȡ������Ӧ��RVA��ַ��Ȼ����ת��ΪFOA��ַ
			//��ͨ�����FOA�ĵ�ַ����ƫ�ƣ����ƫ�ƾ��൱����ͨ�������������Ʊ�����ĵ�ַ����λ
			//��׼ȷ�ĺ������ƣ���ȡ�������Ƶ��ַ�����

			printf("������������-->[%s]", pFunctionName);
			printf("����������ַ���λ��: %#08X", pAddressFunctionTable[n]);
			//��ȡ�����������кű�
			printf("�����������кű�: [%d] \r\n", n - pExport->Base);
			//��ű������ֵ+Base��ֵ=����������ַ��������±�ֵ��
			//����n�ǵ���������ַ����±�ֵ������n - pExportDirectory->Base�Ϳ��Եõ���ű��ֵ
		}
		else
		{
			//�����������������ű�����Ͳ����ڣ��ж��Ƿ�����������
			if (pAddressFunctionTable[n] != 0)
			{
				//ȷ��Ϊ�����غ���
				printf("������������-->");
				printf("����������ַ���±�[%d]-->", n + pExport->Base);
				printf("����������ַ���λ��:%#08X ", pAddressFunctionTable[n]);
			}
		}
		printf("\r\n");
	}
	return;
}


//	2��GetFunctionAddrByName(FileBufferָ�룬������ָ��)
DWORD	GetFunctionAddrByName(LPVOID pFileBuffer, LPSTR Name)
{
	printf("Function Name: %s\n", Name);

	PIMAGE_DOS_HEADER		 pDos = NULL;;
	PIMAGE_OPTIONAL_HEADER32  pOP = NULL;
	PIMAGE_DATA_DIRECTORY   pData = NULL;	   //�洢�������ƫ��λ�� �ʹ�С
	PIMAGE_EXPORT_DIRECTORY  pExport = NULL;   //��������׵�ַ


	pDos = (PIMAGE_DOS_HEADER)pFileBuffer;
	pOP = (PIMAGE_OPTIONAL_HEADER32)((DWORD)pDos + pDos->e_lfanew + 0x4 + IMAGE_SIZEOF_FILE_HEADER);

	if (!pFileBuffer)
	{
		printf("FileBuffer ��ȡʧ��!\r\n");
		return NULL;
	}

	//�ж��Ƿ�����Ч��MZ��־
	if (*((PWORD)pFileBuffer) != IMAGE_DOS_SIGNATURE)
	{
		printf("��Ч��MZ��ʶ\r\n");
		return NULL;;
	}

	//�ж��Ƿ�����Ч��PE��־
	if (*((PDWORD)((DWORD)pFileBuffer + pDos->e_lfanew)) != IMAGE_NT_SIGNATURE)
	{
		printf("��Ч��PE���\r\n");
		return NULL;;
	}

	//��ȡ ������λ��
	pData = (PIMAGE_DATA_DIRECTORY)pOP->DataDirectory;
	if (!pData->VirtualAddress)
	{
		printf("�������û�е�����.\n");
		return NULL;
	}

	printf("������ RVA:%x\n", pData->VirtualAddress);
	DWORD pExport_FOA = RvaToOffset(pFileBuffer, pData->VirtualAddress);
	printf("������ FOA:%x\n", pExport_FOA);

	pExport = (PIMAGE_EXPORT_DIRECTORY)((DWORD)pOP + pExport_FOA);
	//����������֮�󣬾���ͨ��RVAת��ΪFOA��ַ����λ���˵��������ʼλ�ã�

	if (!debug)
	{
		printf("Characteristics: %#X\r\n", pExport->Characteristics);
		printf("TimeDateStamp: %#X\r\n", pExport->TimeDateStamp);
		printf("MajorVersion: %#X\r\n", pExport->MajorVersion);
		printf("MinorVersion: %#X\r\n", pExport->MinorVersion);
		printf("Name: %s\r\n", (PVOID)((DWORD)pFileBuffer + RvaToOffset(pFileBuffer, pExport->Name)));
		printf("Base: %#X\r\n", pExport->Base);
		printf("NumberOfFunctions: %#X\r\n", pExport->NumberOfFunctions);
		printf("NumberOfNames: %#X\r\n", pExport->NumberOfNames);
		printf("AddressOfFunctions: %#X\r\n", pExport->AddressOfFunctions);
		printf("AddressOfNames: %#X\r\n", pExport->AddressOfNames);
		printf("AddressOfNameOrdinals: %#X\r\n", pExport->AddressOfNameOrdinals);
	}

	//ͬ���ǽ������������Ʊ���ű�������ַ���Ӧ��ʼλ�õ�RVAת��ΪFOA
	DWORD Foa_AddressOfNames = RvaToOffset(pFileBuffer, pExport->AddressOfNames);
	DWORD Foa_AddressOfFunctions = RvaToOffset(pFileBuffer, pExport->AddressOfFunctions);
	DWORD Foa_AddressOfNameOrdinals = RvaToOffset(pFileBuffer, pExport->AddressOfNameOrdinals);

	if (!debug)
	{
		DWORD Foa_Address_Names = (DWORD)pFileBuffer + Foa_AddressOfNames;
		printf("AddressOfNames Offset Value: %#X\r\n", Foa_Address_Names);//ƫ�ƿ�����û������
		printf("Foa_AddressOfNames: %#X\r\n", Foa_AddressOfNames);//����ת����ĵ�ַ
		printf("Foa_AddressOfNameOrdinals: %#X\r\n", Foa_AddressOfNameOrdinals);
		printf("Foa_AddressOfFunctions: %#X\r\n", Foa_AddressOfFunctions);
	}

	//1.ͨ��ѭ��ȷ�ϴӵ����������Ʊ�������Ŀ�꺯�����Ƿ���ͬ������ͬ���򷵻ظ������ڱ��е�����
	DWORD ordIndex = -1;
	for (DWORD i = 0; i < pExport->NumberOfNames; i++)
	{
		DWORD nameOffset = *(PDWORD)((DWORD)pFileBuffer + (DWORD)((LPDWORD)Foa_AddressOfNames + i));
		/*����õ���nameOffset�Ĳ���ֵ����⣺
		Foa_AddressOfNames��ֵ��0X5223C�������FileBuffer�¶�Ӧ��FOA�ڴ�ƫ�Ƶ�ַ��ͨ��FileBuffer
		ֱ���ƶ������Ƶ�ַ��(AddressOfNames)���׵�ַλ��;������һ���ص������󣬾������ǿ�������Щ
		AddressOfNames��AddressOfNameOrdinals��AddressOfFunctionsȫ��RVA��ַ��Ȼ��ת��֮���FOA��ַ
		���Ƕ�Ӧ���Ϊ��ʹ��Winhex��16������ʽ��ipmsg.exe�ļ���Ȼ���������ʾ����һ���ڴ��ַ��
		����������˵��RVA��ַ��FOA��ַ�����������Ͳ�������������(LPDWORD)Foa_AddressOfNames + i)��
		�����Լ����ʵ������ʹ��Winhex��16������ʽ��ipmsg.exe�ļ�������ڴ��ַ����ƫ�������ҵ���Ӧ
		���Ƶ�ַ��AddressOfNames��ÿ��ƫ�Ƶ�ַ��Ȼ��ʹ��ָ��ķ�ʽͨ��* ȡ�������Ӧ��ÿ��ֵ������ÿ��
		ֵҲ��RVA��ַ�����Եõ���nameOffset��ֵ��Ҫ�ٴ�ת��ΪFOA��ַ����ʹ���ļ�FileBufferƫ�Ƶķ�ʽ
		�ҵ������ĺ������Ƶ�ַ;
		*/

		LPSTR nameAddr = (LPSTR)((DWORD)pFileBuffer + RvaToOffset(pFileBuffer, nameOffset));
		if (!strcmp(nameAddr, Name))
		{
			ordIndex = i;
			break;
		}
	}

	if (ordIndex == -1)
	{
		printf("��������û�иú�������\n");
		return 0;
	}
	//2.ͨ����õ������ڵ�������ű����ҵ���Ӧ���������
	WORD ord = *(PWORD)((DWORD)pFileBuffer + (DWORD)((LPWORD)Foa_AddressOfNameOrdinals + ordIndex));
	if (!debug)
	{
		DWORD Foa_AddressNameOrdinals = (DWORD)pFileBuffer + Foa_AddressOfNameOrdinals;
		printf("AddressOfNameOrdinals Offset Value: %#X\r\n", Foa_AddressNameOrdinals);
		printf("Foa_AddressOfNameOrdinals: %#X\r\n", Foa_AddressOfNameOrdinals);
		printf("ordInex in AddressOfNames: %#X\r\n", ordIndex);
		printf("ordInex in AddressOfNameOrdinals: %#X\r\n", ord);
	}

	//3.ͨ����ű��в������ֵ�������±������ӵ���������ַ�����Һ�����ַ
	DWORD addr = *(PDWORD)((DWORD)pFileBuffer + (DWORD)((LPDWORD)Foa_AddressOfFunctions + ord));
	//DWORD Foa_AddrFun = RvaToFileOffset(pFileBuffer, addr);

	return addr;
}

//������Ż�ȡ����������ַ
DWORD GetFunctionAddrByOrdinals(PVOID pFileBuffer, DWORD pFunctionOfOrdinal)
{
	printf("Function Ordinal: %#x\n", pFunctionOfOrdinal);
	// ��ʼ��PEͷ���ṹ��
	PIMAGE_DOS_HEADER pDosHeader = NULL;
	PIMAGE_NT_HEADERS pNTHeader = NULL;
	PIMAGE_FILE_HEADER pPEHeader = NULL;
	PIMAGE_OPTIONAL_HEADER32 pOptionHeader = NULL;
	PIMAGE_SECTION_HEADER pSectionHeader = NULL;
	PIMAGE_DATA_DIRECTORY pDataDirectory = NULL;     //�������ƫ�� RVA ��ת��FOA
	PIMAGE_EXPORT_DIRECTORY pExportDirectory = NULL;

	// �ж�ָ���Ƿ���Ч
	if (!pFileBuffer)
	{
		printf("pFileBuffer������Ч��ָ��\r\n");
		return 0;
	}
	//�ж��Ƿ�����Ч��MZ��־
	if (*((PWORD)pFileBuffer) != IMAGE_DOS_SIGNATURE)
	{
		printf("pFileBuffer������Ч��MZ�ļ�\r\n");
		return 0;
	}
	//�ж��Ƿ���һ����Ч��PE��־
	pDosHeader = (PIMAGE_DOS_HEADER)pFileBuffer;
	if (*((PWORD)((DWORD)pFileBuffer + pDosHeader->e_lfanew)) != IMAGE_NT_SIGNATURE)
	{
		printf("pFileBuffer����һ����Ч��PE��־\r\n");
		return 0;
	}

	// ǿ�ƽṹ������ת��
	pNTHeader = (PIMAGE_NT_HEADERS)((DWORD)pFileBuffer + pDosHeader->e_lfanew);
	pPEHeader = (PIMAGE_FILE_HEADER)((DWORD)pNTHeader + 0x04); // �������ǿ������ת��
	pOptionHeader = (PIMAGE_OPTIONAL_HEADER32)((DWORD)pPEHeader + IMAGE_SIZEOF_FILE_HEADER);
	pSectionHeader = (PIMAGE_SECTION_HEADER)((DWORD)pOptionHeader + pPEHeader->SizeOfOptionalHeader);
	pDataDirectory = (PIMAGE_DATA_DIRECTORY)pOptionHeader->DataDirectory;


	if (!pDataDirectory->VirtualAddress)
	{
		printf("�������û�е�����.\r\n");
		return 0;
	}

	printf("������RVA��ַ: %#X\r\n", pDataDirectory->VirtualAddress);
	DWORD Foa_ExportTable = RvaToOffset(pFileBuffer, pDataDirectory->VirtualAddress);
	printf("������FOA��ַ: %#X\r\n", Foa_ExportTable);
	pExportDirectory = (PIMAGE_EXPORT_DIRECTORY)((DWORD)pFileBuffer + Foa_ExportTable);

	if (!debug)
	{
		printf("Characteristics: %#X\r\n", pExportDirectory->Characteristics);
		printf("TimeDateStamp:%#X\r\n", pExportDirectory->TimeDateStamp);
		printf("MajorVersion: %#X\r\n", pExportDirectory->MajorVersion);
		printf("MinorVersion: %#X\r\n", pExportDirectory->MinorVersion);
		printf("Name: %s\r\n", (PVOID)((DWORD)pFileBuffer + RvaToOffset(pFileBuffer, pExportDirectory->Name)));
		printf("Base: %#X\r\n", pExportDirectory->Base);
		printf("NumberOfFunctions: %#X\r\n", pExportDirectory->NumberOfFunctions);
		printf("NumberOfNames: %#X\r\n", pExportDirectory->NumberOfNames);
		printf("AddressOfFunctions: %#X\r\n", pExportDirectory->AddressOfFunctions);
		printf("AddressOfNames: %#X\r\n", pExportDirectory->AddressOfNames);
		printf("AddressOfNameOrdinals: %#X\r\n", pExportDirectory->AddressOfNameOrdinals);
	}

	//��������㷨���������ͨ�����ֱ�ӵó�����������ַ���еĵ�ַ����ôֻҪ���-Baseֵ����
	DWORD Sequence = pFunctionOfOrdinal - pExportDirectory->Base;
	DWORD Foa_AddressOfFunctions = RvaToOffset(pFileBuffer, pExportDirectory->AddressOfFunctions);

	if (!debug)
	{
		DWORD Foa_AddressFunctions = Foa_AddressOfFunctions + (DWORD)pFileBuffer;
		printf("AddressOfFunctions��������: %#X\r\n", Foa_AddressFunctions);
		printf("Foa_AddressOfFunctions: %#X\r\n", Foa_AddressOfFunctions);
	}

	PDWORD pFoa_AddressOfFunctions = (PDWORD)((DWORD)pFileBuffer + Foa_AddressOfFunctions);
	for (DWORD n = 0; n < Sequence; n++)
	{
		pFoa_AddressOfFunctions++;
	}
	//DWORD Foa_AddrFun = RvaToFileOffset(pFileBuffer, *pFoa_AddressOfFunctions);
	return *pFoa_AddressOfFunctions;
}

}

int main()
{
	LPVOID FileBuffer = NULL;
	char path[] = "D:/ipmsg.exe";
	//LPSTR Name = "";

	ReadPEFile( path, &FileBuffer );
	//Printexport(FileBuffer);
	//GetFunctionAddrByName(FileBuffer,Name);
	//GetFunctionAddrByOrdinals(FileBuffer, 2);

	system("pause");
	return 0;
}



