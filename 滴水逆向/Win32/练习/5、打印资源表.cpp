#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<Windows.h>

#define IN_PATH "ipmsg.exe"

DWORD ReadFileBuffer(LPSTR File_pata, LPVOID* pFilebuffer)
{
    FILE* pf = NULL;
    DWORD Size = 0;
    LPVOID pBuffer = NULL;

    pf = fopen(File_pata, "rb");
    if (!pf)
    {
        printf("�ļ���ȡʧ��!\n");
        return 0;
    }

    fseek(pf, 0, SEEK_END);
    Size = ftell(pf);
    fseek(pf, 0, SEEK_SET);
    pBuffer = malloc(Size);
    if (!pBuffer)
    {
        printf("�ڴ����ʧ��\n");
        fclose(pf);
        return 0;
    }

    DWORD n = fread(pBuffer, Size, 1, pf);
    if (!n)
    {
        printf("�ļ���ȡʧ��\n");
        free(pBuffer);
        fclose(pf);
        return 0;

    }

    *pFilebuffer = pBuffer;
    pBuffer = NULL;
    fclose(pf);
    return Size;
}

DWORD RvaToFoa(LPVOID pFileBuff, DWORD dwRVA)
{
    PIMAGE_DOS_HEADER pDosHeader = NULL;
    PIMAGE_NT_HEADERS pNTHeader = NULL;
    PIMAGE_FILE_HEADER pPEHeader = NULL;
    PIMAGE_OPTIONAL_HEADER32 pOptionHeader = NULL;
    PIMAGE_SECTION_HEADER pSectionHeader = NULL;

    if (!pFileBuff)
    {
        printf("(FoaToImageOffset)Can't open file!\n");
        return 0;
    }

    if (*((PWORD)pFileBuff) != IMAGE_DOS_SIGNATURE)
    {
        printf("(FoaToImageOffset)No MZ flag, not exe file!\n");
        return 0;
    }

    pDosHeader = (PIMAGE_DOS_HEADER)pFileBuff;
    if (*((PDWORD)((DWORD)pFileBuff + pDosHeader->e_lfanew)) != IMAGE_NT_SIGNATURE)
    {
        printf("(FoaToImageOffset)Not a valid PE flag!\n");
        return 0;
    }

    pNTHeader = (PIMAGE_NT_HEADERS)((DWORD)pFileBuff + pDosHeader->e_lfanew);
    pPEHeader = (PIMAGE_FILE_HEADER)((DWORD)pNTHeader + 4); // �������ǿ������ת��
    pOptionHeader = (PIMAGE_OPTIONAL_HEADER32)((DWORD)pPEHeader + IMAGE_SIZEOF_FILE_HEADER);
    pSectionHeader = (PIMAGE_SECTION_HEADER)((DWORD)pOptionHeader + pPEHeader->SizeOfOptionalHeader);
    PIMAGE_SECTION_HEADER pSectionTemp = pSectionHeader;

    if (dwRVA <= pOptionHeader->SizeOfHeaders)
    {
        return dwRVA;
    }

    for (DWORD i = 0; i < pPEHeader->NumberOfSections; i++, pSectionTemp++)
    {
        if (dwRVA >= pSectionTemp->VirtualAddress && dwRVA < pSectionTemp->VirtualAddress + pSectionTemp->Misc.VirtualSize)
        {
            return dwRVA - pSectionTemp->VirtualAddress + pSectionTemp->PointerToRawData;
        }
    }

    printf("δ�ҵ���ֵ��FOA\n");
    return 0;
}


// ��ӡ��Դ��
VOID PrintResourceTable(LPVOID pFileBuffer)
{
	//��Դ������
	PCHAR lpszResType[17] = { "δ����", "���", "λͼ", "ͼ��", "�˵�",
		"�Ի���", "�ַ���","����Ŀ¼", "����",
		"���ټ�", "�Ǹ�ʽ����Դ", "��Ϣ�б�", "�����",
		"δ����", "ͼ����","δ����", "�汾��Ϣ" };

	PIMAGE_DOS_HEADER pDosHeader = (PIMAGE_DOS_HEADER)pFileBuffer;
	PIMAGE_FILE_HEADER pPEHeader = (PIMAGE_FILE_HEADER)(pDosHeader->e_lfanew + (DWORD)pDosHeader + 4);
	PIMAGE_OPTIONAL_HEADER32 pOptionHeader = (PIMAGE_OPTIONAL_HEADER32)((DWORD)pPEHeader + sizeof(IMAGE_FILE_HEADER));
	PIMAGE_SECTION_HEADER pSectionHeader = (PIMAGE_SECTION_HEADER)((DWORD)pOptionHeader + pPEHeader->SizeOfOptionalHeader);

	// ��λ��ԴĿ¼   ��һ��
	PIMAGE_RESOURCE_DIRECTORY pResDir1 = (PIMAGE_RESOURCE_DIRECTORY)((DWORD)pFileBuffer + \
		RvaToFoa(pFileBuffer, pOptionHeader->DataDirectory[2].VirtualAddress)); // ��ȡ�ļ��е�ƫ��
	// ��λ��ԴĿ¼��  ��һ��
	PIMAGE_RESOURCE_DIRECTORY_ENTRY pResDirEntry1 = (PIMAGE_RESOURCE_DIRECTORY_ENTRY)((DWORD)pResDir1 + \
		sizeof(IMAGE_RESOURCE_DIRECTORY));

	//��ȡ��һ����Դ��������   ��Դ�������� = NumberOfNamedEntries + NumberOfIdEntries
	int dwNumberOfResDirEntry1 = pResDir1->NumberOfNamedEntries + pResDir1->NumberOfIdEntries;
	//printf("��Դ��������: %d\n", dwNumberOfResDirEntry1);
	// ������һ�㣺����
	for (int i = 0; i < dwNumberOfResDirEntry1; i++)
	{
		// �����λ��1����31λ��ָ�룬ָ��һ��Unicode�ַ���
		if (pResDirEntry1[i].NameIsString == 1)
		{
			PIMAGE_RESOURCE_DIR_STRING_U uString =
				(PIMAGE_RESOURCE_DIR_STRING_U)((DWORD)pResDir1 + (pResDirEntry1[i].NameOffset & 0x7FFFFFFF));

			//  2 * (uString->Length + 1)) ��Ҫ�洢���ַ�    uString->Length + 1 �����ȡ�Ӷ��ж�ȡ�����ַ��� 0 0 ��β
			WCHAR* pName = (WCHAR*)malloc(2 * (uString->Length + 1));
			memset(pName, 0, 2 * (uString->Length + 1));
			memcpy(pName, uString->NameString, 2 * uString->Length);
			wprintf(L"ID:  - ��Դ����: \"%s\"\n", pName);
			free(pName);
		}
		// ������λ��0��������һ����ţ���Ԥ�����16����Դ֮һ
		else
		{
			if (pResDirEntry1[i].Id <= 16)
				printf("ID: %2d ��Դ����: %s\n", pResDirEntry1[i].Id, lpszResType[pResDirEntry1[i].Id]);
			else
				printf("ID: %2d ��Դ����: δ����\n", pResDirEntry1[i].Id);
		}

		// ����ڶ����ָ��		��ԴĿ¼
		PIMAGE_RESOURCE_DIRECTORY pResDir2 = (PIMAGE_RESOURCE_DIRECTORY)((DWORD)pResDir1 + \
			(pResDirEntry1[i].OffsetToData & 0x7FFFFFFF));
		// �ڶ���  ��ԴĿ¼��
		PIMAGE_RESOURCE_DIRECTORY_ENTRY pResDirEntry2 = (PIMAGE_RESOURCE_DIRECTORY_ENTRY)((DWORD)pResDir2 + \
			sizeof(IMAGE_RESOURCE_DIRECTORY));

		//�ڶ������ݸ���
		int dwNumberOfResDirEntry2 = pResDir2->NumberOfNamedEntries + pResDir2->NumberOfIdEntries;
		// �����ڶ��㣺���
		//printf("�ڶ�������: %d\n", dwNumberOfNumber);		
		for (int j = 0; j < dwNumberOfResDirEntry2; j++)
		{
			if (pResDirEntry2[j].NameIsString == 1)
			{
				//��32λ ��ָ��һ��Unicode�ַ��� ָ��
				PIMAGE_RESOURCE_DIR_STRING_U uString =
					(PIMAGE_RESOURCE_DIR_STRING_U)((DWORD)pResDir1 + (pResDirEntry2[j].NameOffset & 0x7FFFFFFF));
				WCHAR* pName = (WCHAR*)malloc(2 * (uString->Length + 1));
				memset(pName, 0, 2 * (uString->Length + 1));
				memcpy(pName, uString->NameString, 2 * uString->Length);
				wprintf(L"\tName: \"%s\"\n", pName);
				free(pName);
			}
			else
			{
				printf("\tID: %d\n", pResDirEntry2[j].Id);
			}
			// ����������ָ��ͳ���		
			PIMAGE_RESOURCE_DIRECTORY pResDir3 = (PIMAGE_RESOURCE_DIRECTORY)((DWORD)pResDir1 + \
				(pResDirEntry2[j].OffsetToData & 0x7FFFFFFF));

			PIMAGE_RESOURCE_DIRECTORY_ENTRY pResDirEntry3 = (PIMAGE_RESOURCE_DIRECTORY_ENTRY)((DWORD)pResDir3 + \
				sizeof(IMAGE_RESOURCE_DIRECTORY));

			int dwNumberOfResDirEntry3 = pResDir3->NumberOfNamedEntries + pResDir3->NumberOfIdEntries;
			// ���������㣺����ҳ
			// ����������һ����Դ�Ĵ���ҳֻ����һ�֣������Ǿ��ԣ���˵�����ҲҪѭ������			
			//printf("\t\t%d\n", dwNumberOfResDirEntry3); // ���в���1��
			for (int k = 0; k < dwNumberOfResDirEntry3; k++)
			{
				if (pResDirEntry3[k].Name & 0x80000000)
				{
					printf("\t�Ǳ�׼����ҳ\n");
				}
				else
				{
					printf("\t����ҳ: %d\n", pResDirEntry3[k].Id & 0x7FFF);
				}
				// ��Դ�����ͨ������ṹ�����ҵ���Դ��RVA���Լ���С
				PIMAGE_RESOURCE_DATA_ENTRY pDataEntry = (PIMAGE_RESOURCE_DATA_ENTRY)((DWORD)pResDir1 + \
					pResDirEntry3[k].OffsetToData);
				printf("\tRVA: %x\tSIZE: %x\n", pDataEntry->OffsetToData, pDataEntry->Size);
			}
			printf("\n");
		}
	}
}

int main()
{
    LPVOID pFileBuffer = NULL;

    ReadFileBuffer((LPSTR)IN_PATH, &pFileBuffer);
	PrintResourceTable(pFileBuffer);

	return 0;
}

