#include"04PE���ع���.h"


DWORD ReadPEFile(IN LPSTR lpszFile, OUT LPVOID* pFileBuffer)
{
	FILE* pfile = NULL;
	DWORD FileSize = 0;
	LPVOID ptempBuffer = NULL;

	pfile = fopen(lpszFile, "rb");
	if (!pfile)
	{
		printf("exe��ʧ�ܣ�\n");
		return 0;
	}

	//��ȡ�ļ���С
	fseek(pfile, 0, SEEK_END);
	FileSize = ftell(pfile);
	fseek(pfile, 0, SEEK_SET); 

	//���ٿռ�
	ptempBuffer = malloc(FileSize);
	if (!ptempBuffer)
	{
		printf("�ڴ����ʧ��\n");
		fclose(pfile);
		return 0;
	}

	size_t n = fread(ptempBuffer, FileSize,1, pfile);
	if (!n)
	{
		printf("ReadPEFile�ļ���ȡʧ��\n");
		fclose(pfile);
		return 0;
	}
	printf("ReadPEFile�ļ���ȡ�ɹ�\n");

	*pFileBuffer = ptempBuffer;
	ptempBuffer = NULL;
	fclose(pfile);

	return FileSize;

}

DWORD CopyFileBufferToImageBuffer(IN LPVOID pFileBuffer, OUT LPVOID* pImageBuffer)
{
	PIMAGE_DOS_HEADER pDosHeader = NULL;
	PIMAGE_NT_HEADERS pNtHeader = NULL;
	PIMAGE_FILE_HEADER pFileHeader = NULL;
	PIMAGE_OPTIONAL_HEADER32 pOptonalHeader = NULL;
	PIMAGE_SECTION_HEADER pSectionHeader = NULL;
	// ��ʱָ��
	LPVOID TempBuffer = NULL;

	if (pFileBuffer == NULL)
	{
		printf("pFileBufferָ����Ч\n");
		return 0;
	}
	//�ж��Ƿ�����ЧMZ���
	pDosHeader = (PIMAGE_DOS_HEADER)(DWORD)pFileBuffer;
	if (pDosHeader->e_magic != IMAGE_DOS_SIGNATURE)
	{
		printf("pFileBuffer������ЧMZ���\n");
		return 0;
	}
	//�ж�PE��־
	if (*((PDWORD)((DWORD)pDosHeader + pDosHeader->e_lfanew)) != IMAGE_NT_SIGNATURE)
	{
		printf("pFileBuffer������ЧPE��־\n");
		return 0;
	}

	pNtHeader = (PIMAGE_NT_HEADERS)((DWORD)pDosHeader + pDosHeader->e_lfanew);
	pFileHeader = (PIMAGE_FILE_HEADER)(((DWORD)pNtHeader) + 4);
	//��ѡPEͷ
	pOptonalHeader = (PIMAGE_OPTIONAL_HEADER32)((DWORD)pFileHeader + IMAGE_SIZEOF_FILE_HEADER);
	//��һ���ڱ�ָ��
	pSectionHeader = (PIMAGE_SECTION_HEADER)((DWORD)pOptonalHeader + pFileHeader->SizeOfOptionalHeader);

	//����SizeOflmage�����¿ռ�
	TempBuffer = malloc(pOptonalHeader->SizeOfImage);
	if (!TempBuffer)
	{
		printf("TempBuffer�ڴ����ʧ��");
		TempBuffer = NULL;
		return 0;
	}
	//��ʼ���µĻ�����
	memset(TempBuffer, 0, pOptonalHeader->SizeOfImage);
	//��������ͷ   SizeOfHeaders
	memcpy(TempBuffer, pDosHeader, pOptonalHeader->SizeOfHeaders); //����1:Ŀ������  ����2:��ʼλ��  ����3:����λ��
	//���ݽڱ� ѭ��cpy
	PIMAGE_SECTION_HEADER pTempSH = pSectionHeader;
	for (int i = 0; i < pFileHeader->NumberOfSections; i++, pTempSH++)
	{
		// �����׵�ַ    dosͷ + PointerToRawDAta = ����ƫ�Ƶ�ַ      pTempSH->SizeOfRawData :�ļ������ĵ�ַ �����λ��
		memcpy((void*)((DWORD)TempBuffer + pTempSH->VirtualAddress),
			(void*)((DWORD)pDosHeader + pTempSH->PointerToRawData), pTempSH->SizeOfRawData);
	}
	printf("CopyFileBufferToImageBuffer�ɹ�\n");

	//��������
	*pImageBuffer = TempBuffer;
	TempBuffer = NULL;

	return pOptonalHeader->SizeOfImage;
}

DWORD CopyImageBufferToNewBuffer(IN LPVOID pImageBuffer, OUT LPVOID* pNewBuffer)
{
	PIMAGE_DOS_HEADER pDosHeader = NULL;
	PIMAGE_NT_HEADERS pNtHeader = NULL;
	PIMAGE_FILE_HEADER pFileHeader = NULL;
	PIMAGE_OPTIONAL_HEADER32 pOptonalHeader = NULL;
	PIMAGE_SECTION_HEADER pSectionHeader = NULL;

	LPVOID Temp_NewBuffer = NULL;

	if (pImageBuffer == NULL)
	{
		printf("pImageBufferָ����Ч\n");
		return 0;
	}
	//�ж��Ƿ�����ЧMZ���
	pDosHeader = (PIMAGE_DOS_HEADER)(DWORD)pImageBuffer;
	if (pDosHeader->e_magic != IMAGE_DOS_SIGNATURE)
	{
		printf("������ЧMZ���\n");
		return 0;
	}
	//�ж�PE��־
	if (*((PDWORD)((DWORD)pDosHeader + pDosHeader->e_lfanew)) != IMAGE_NT_SIGNATURE)
	{
		printf("������ЧPE��־\n");
		return 0;
	}
	pNtHeader = (PIMAGE_NT_HEADERS)((DWORD)pDosHeader + pDosHeader->e_lfanew);
	pFileHeader = (PIMAGE_FILE_HEADER)(((DWORD)pNtHeader) + 4);
	//��ѡPEͷ
	pOptonalHeader = (PIMAGE_OPTIONAL_HEADER32)((DWORD)pFileHeader + IMAGE_SIZEOF_FILE_HEADER);
	//��һ���ڱ�ָ��
	pSectionHeader = (PIMAGE_SECTION_HEADER)((DWORD)pOptonalHeader + pFileHeader->SizeOfOptionalHeader);
	//��ȡ�ļ���С




	DWORD ImageBuff_Size = pOptonalHeader->SizeOfHeaders;
	//�����ڱ�
	for (size_t i = 0; i < pFileHeader->NumberOfSections; i++)
	{
		ImageBuff_Size += pSectionHeader[i].SizeOfRawData;
	}
	//���ٿռ�
	Temp_NewBuffer = malloc(ImageBuff_Size);
	if (!Temp_NewBuffer)
	{
		printf("Temp_NewBuffer����ʧ�� \n");
		Temp_NewBuffer = NULL;
		return 0;
	}

	//��ʼ��ȫΪ0 
	memset(Temp_NewBuffer, 0, ImageBuff_Size);
	//����ͷ
	memcpy(Temp_NewBuffer, pDosHeader, pOptonalHeader->SizeOfHeaders);

	for (size_t i = 0; i < pFileHeader->NumberOfSections; i++ , pSectionHeader++)
	{
		memcpy((void*)((DWORD)Temp_NewBuffer + pSectionHeader->PointerToRawData),
			(void*)((DWORD)pImageBuffer + pSectionHeader->VirtualAddress),
			pSectionHeader->Misc.VirtualSize);
	}

	*pNewBuffer = Temp_NewBuffer;
	Temp_NewBuffer = NULL;

	printf("CopyImageBufferToNewBuffer�ɹ�\n");

	return ImageBuff_Size;

}


BOOL MemeryTOFile(IN LPVOID pMemBuffer, IN size_t size, OUT LPSTR lpszFile)
{
	FILE* pf = NULL;
	pf = fopen(lpszFile, "wb");
	if (!pf)
	{
		printf("MemeryTOFile �ļ���ȡʧ��\n");
		return 0;
	}

	fwrite(pMemBuffer, size, 1, pf);//�����д������
	fclose(pf);
	pf = NULL;
	return 0;
}


DWORD RvaToFileOffset(IN LPVOID pFileBuffer, IN DWORD dwRva)
{

	return 0;
}
