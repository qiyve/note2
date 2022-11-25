#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>

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
LPVOID ReadPEFile()
{
	FILE* pFile = NULL;
	//��¼��С
	//DWORD ���� unsigned long
	DWORD fileSize = 0;
	//�ļ�������
	LPVOID pFileBuffer = NULL;

	//���ļ�	
	int a = fopen_s(&pFile,"D:\\ipmsg.exe ","rb");
	if (!pFile)
	{
		printf(" �޷��� EXE �ļ�! ");
		return NULL;
	}
	//��ȡ�ļ���С		
	fseek(pFile, 0, SEEK_END);
	fileSize = ftell(pFile);
	fseek(pFile, 0, SEEK_SET);
	//���仺����	
	pFileBuffer = malloc(fileSize);

	if (!pFileBuffer)
	{
		printf(" ����ռ�ʧ��! ");
		fclose(pFile);
		return NULL;
	}
	//���ļ����ݶ�ȡ��������	
	size_t n = fread(pFileBuffer, fileSize, 1, pFile);
	if (!n)
	{
		printf(" ��ȡ����ʧ��! ");
		free(pFileBuffer);
		fclose(pFile);
		return NULL;
	}
	//�ر��ļ�	
	fclose(pFile);
	return pFileBuffer;
}

void PrintNTHeaders()
{
	LPVOID pFileBuffer = NULL;
	PIMAGE_DOS_HEADER pDosHeader = NULL;
	PIMAGE_NT_HEADERS pNTHeader = NULL;
	PIMAGE_FILE_HEADER pPEHeader = NULL;
	PIMAGE_OPTIONAL_HEADER32 pOptionHeader = NULL;
	PIMAGE_SECTION_HEADER pSectionHeader = NULL;

	pFileBuffer = ReadPEFile();
	if (!pFileBuffer)
	{
		printf("�ļ���ȡʧ��\n");
		return;
	}

	//�ж��Ƿ�����Ч��MZ��־	
	if (*((PWORD)pFileBuffer) != IMAGE_DOS_SIGNATURE)
	{
		printf("������Ч��MZ��־\n");
		free(pFileBuffer);
		return;
	}
	pDosHeader = (PIMAGE_DOS_HEADER)pFileBuffer;
	//��ӡDOCͷ	
	printf("********************DOCͷ********************\n");
	printf("MZ��־��%x\n", pDosHeader->e_magic);
	printf("PEƫ�ƣ�%x\n", pDosHeader->e_lfanew);
	//�ж��Ƿ�����Ч��PE��־	
	if (*((PDWORD)((DWORD)pFileBuffer + pDosHeader->e_lfanew)) != IMAGE_NT_SIGNATURE)
	{
		printf("������Ч��PE��־\n");
		free(pFileBuffer);
		return;
	}
	pNTHeader = (PIMAGE_NT_HEADERS)((DWORD)pFileBuffer + pDosHeader->e_lfanew);
	//��ӡNTͷ	
	printf("********************NTͷ********************\n");
	printf("NT��%x\n", pNTHeader->Signature);
	pPEHeader = (PIMAGE_FILE_HEADER)(((DWORD)pNTHeader) + 4);
	printf("********************PEͷ********************\n");
	printf("PE��%x\n", pPEHeader->Machine);
	printf("�ڵ�������%x\n", pPEHeader->NumberOfSections);
	printf("SizeOfOptionalHeader��%x\n", pPEHeader->SizeOfOptionalHeader);
	//��ѡPEͷ	
	pOptionHeader = (PIMAGE_OPTIONAL_HEADER32)((DWORD)pPEHeader + IMAGE_SIZEOF_FILE_HEADER);
	printf("********************OPTIOIN_PEͷ********************\n");
	printf("OPTION_PE��%x\n", pOptionHeader->Magic);
	//�ͷ��ڴ�	
	free(pFileBuffer);
}


int main()
{

	//PrintNTHeaders();
	DWORD fileSize = 2;

	return 0;
}
