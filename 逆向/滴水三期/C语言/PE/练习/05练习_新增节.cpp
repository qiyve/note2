#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<Windows.h>
#include<stdlib.h>

#define FILEPATH ""

DWORD ReadPEFile(IN LPSTR lpszFile, OUT LPVOID* pFileBuffer)
{
	// �����и�IN��OUT��������˼���ǲ��������ʹ������֮�󲻽��к���չ��
	//ɶҲ���ɣ���ʹ���ɸɣ�Ҳ����չ�ɿհף������C++�﷨������ģ�
	//LPSTR  ---->  typedef CHAR *LPSTR, *PSTR; ��˼����char* ָ�룻��WINNT.Hͷ�ļ�����
	// typedef unsigned long       DWORD;  DWORD���޷���4���ֽڵ�����
	//LPVOID ---->  typedef void far *LPVOID;��WINDEF.Hͷ�ļ����棻������voidָ������

	FILE* pFile = NULL;
	DWORD fileSize = 0;
	LPVOID pTempFileBuffer = NULL;

	//���ļ�
	pFile = fopen(lpszFile, "rb"); 
	if (!pFile)
	{
		printf("�����ļ�ʧ��\n");
		return 0;
	}

	/*
     ������ָ�������н����жϵĲ��������������ֵ�����ʹ�һ������������£�
     1.��Ϊָ���ж϶�Ҫ��NULL�Ƚϣ��൱��0����ֵ�����඼����ֵ
     2.if(!pFile)��if(pFile == NULL), ----> Ϊ�գ���ִ����䣻�������������ںŲ���һ�����ں�
     3.if(pFile)����if(pFile != NULL), ��Ϊ�գ���ִ����䣻
     */

	//��ȡ�ļ����ݺ󣬻�ȡ�ļ���С
	fseek(pFile, 0, SEEK_END);
	fileSize = ftell(pFile);
	fseek(pFile, 0, SEEK_SET);
	/*
	*  fseek ͨ��ʹ�ö����Ƶķ�ʽ���ļ����ƶ��ļ���дָ���λ��,��stdio.hͷ�ļ���
	int fseek(FILE * stream, long offset, int fromwhere);
	������fseek�ĺ���ԭ��
	��һ������stream Ϊ�ļ�ָ��
	�ڶ�������offset Ϊƫ������������ʾ����ƫ�ƣ�������ʾ����ƫ��
	����������fromwhere Ϊָ�����ʼλ��, �趨���ļ������￪ʼƫ��, ����ȡֵΪ��SEEK_CUR��SEEK_END��SEEK_SET
	SEEK_SET 0 �ļ���ͷ
	SEEK_CUR 1 ��ǰ��д��λ��
	SEEK_END 2 �ļ�β��*/

	//����ռ�
	pTempFileBuffer = malloc(fileSize);
	if (!pTempFileBuffer)
	{
		printf("�ڴ����ʧ��\n");
		fclose(pFile);
		return 0;
	}

	//�������뵽���ڴ�ռ䣬��ȡ����
	size_t n = fread(pTempFileBuffer, fileSize, 1, pFile);
	if (!n)
	{
		printf("��ȡ����ʧ��\n");
		free(pTempFileBuffer);  
		fclose(pFile);

		return 0;
    }

	//���ݶ�ȡ�ɹ����ر��ļ�
	*pFileBuffer = pTempFileBuffer;// ����ȡ�ɹ����������ڵ��ڴ�ռ���׵�ַ����ָ������pFileBuffer
	fclose(pFile);                 //�ر��ļ�

	return fileSize;               //���ػ�ȡ�ļ��Ĵ�С
}

//ͨ������FileBuffer������1000H���µ�ImageBuffer����
DWORD CopyFileBufferToNewImageBuffer(IN LPVOID pFileBuffer, IN size_t fileSize, OUT LPVOID* pNewImageBuffer)
{
	PIMAGE_DOS_HEADER			pDos  = NULL;
	PIMAGE_NT_HEADERS			pNt	  = NULL;
	PIMAGE_FILE_HEADER			pPE = NULL;
	PIMAGE_OPTIONAL_HEADER32	pOp   = NULL;
	PIMAGE_SECTION_HEADER		pSect = NULL;
	PIMAGE_SECTION_HEADER		pLastSect = NULL;
	LPVOID pTempNewImageBuffer	= 0;
	DWORD	sizeOfFile = 0;
	DWORD  numberOfSection = 0;  
	DWORD  okAddSections = 0;

	//�ж϶�ȡpFileBuffer��ȡ�Ƿ�ɹ�
	if (!pFileBuffer)
	{
		printf("pFileBuffer������ָ����Ч\n");
		return 0;
	}

	//�ж��Ƿ�ΪMZ��־
	if ((*(PWORD)pFileBuffer) != IMAGE_DOS_SIGNATURE) // IMAGE_DOS_SIGNATURE --> MZ
	{
		printf("������ЧMZ���\n");
		return 0;
	}

	//�ж��Ƿ���PE���
	pDos = (PIMAGE_DOS_HEADER)pFileBuffer;
	if (*(PWORD)((DWORD)pDos + pDos->e_lfanew) != IMAGE_NT_SIGNATURE) // IMAGE_NT_SIGNATURE --> PE
	{
		printf("������ЧPE���\n");
		return 0;
	}

	//*********************���뿪���ڴ�ռ�*****************************************************************

	sizeOfFile = fileSize + 0x1000;
	pTempNewImageBuffer = malloc(sizeOfFile);

	//�ж��ڴ�ռ��Ƿ񿪱ٳɹ�
	if (!pTempNewImageBuffer)
	{
		printf("pTempNewImageBuffer�����ڴ�ʧ��\n");
		return 0;
	}

	//��ʼ���ڴ�����
	memset(pTempNewImageBuffer, 0, sizeOfFile);

	//��ʼ�����֮���Ȱ�Ϊ�޸ĵ��ڴ�ռ�ȫ���������µ��ڴ�ռ�
	memcpy(pTempNewImageBuffer, pFileBuffer, fileSize);

	//��λDos��ַ
	pDos = (PIMAGE_DOS_HEADER)(pTempNewImageBuffer);
	//NTͷ
	pNt = (PIMAGE_NT_HEADERS)((DWORD)pDos + pDos->e_lfanew);
	//PEͷ
	pPE = (PIMAGE_FILE_HEADER)(((DWORD)pNt) + 0x04);
	//��ѡPEͷ
	pOp = (PIMAGE_OPTIONAL_HEADER32)(((DWORD)pPE) + IMAGE_SIZEOF_FILE_HEADER); //IMAGE_SIZEOF_FILE_HEADER -> 20���ֽ�
	
   //��һ���ڱ��ַ
	pSect = (PIMAGE_SECTION_HEADER)((DWORD)pOp + pPE->SizeOfOptionalHeader);

	//���һ���ڱ��ַ
	pLastSect = &pSect[pPE->NumberOfSections - 1];

	// �ж��Ƿ����㹻�Ŀռ����һ���ڱ�
		//�ж�������
		/*
		SizeOfHeader - (DOS + �������� + PE��� + ��׼PEͷ + ��ѡPEͷ + �Ѵ��ڽڱ�) >= 2���ڱ�Ĵ�С
		SizeOfHeader�ڿ�ѡPEͷ����
		 */

	okAddSections = (DWORD)(pOp->SizeOfHeaders - (pDos->e_lfanew + 0x04 + sizeof(PIMAGE_FILE_HEADER))
		+ pPE->SizeOfOptionalHeader + sizeof(PIMAGE_SECTION_HEADER) * pPE->NumberOfSections);

	if (okAddSections <= 2 * sizeof(PIMAGE_SECTION_HEADER))
	{
		printf("���exe�ļ�ͷ��ʣ��ռ䲻��\n");
		free(pTempNewImageBuffer);
		return 0;
	}

	//����û���⣬�Ϳ�ʼ�޸�������
	//*************************�޸�����*******************************************************************

	 //��ʼ���½ڱ���Ϣ
	PWORD pNumberOfSecton = &pPE->NumberOfSections;
	PDWORD pSizeOfImage = &pOp->SizeOfImage;

	//��ȡ����ÿ�����ݵĵ�ַ
	numberOfSection				= pPE->NumberOfSections;
	PVOID pSecName				= &pSect[numberOfSection].Name;
	PDWORD pSecMisc				= &pSect[numberOfSection].Misc.VirtualSize;
	PDWORD pSecVirtualAddress	= &pSect[numberOfSection].VirtualAddress;;
	PDWORD pSecSizeOfRawData	= &pSect[numberOfSection].SizeOfRawData;
	PDWORD pSecPointToRawData	= &pSect[numberOfSection].PointerToRawData;
	PDWORD pSecCharacteristics	= &pSect[numberOfSection].Characteristics;


	//�޸�PE�ļ�ͷ����Ľ�������Ϣ
	printf("*pNumberOfSection: %x \n", pPE->NumberOfSections);
	*pNumberOfSecton = pPE->NumberOfSections + 1;
	printf("*pNumberOfSection: %x\n", pPE->NumberOfSections);

	//�޸�PE��ѡͷ����SizeOfImage��Ϣ
	printf("*pSizeOfImage:%#X \r\n", pOp->SizeOfImage);
	* pSizeOfImage = pOp->SizeOfImage + 0x1000;
	printf("*pSizeOfImage:%#X \r\n", pOp->SizeOfImage);

	//��ڱ����������
	memcpy(pSecName, ".newSec", 8);
	*pSecMisc = 0x1000;

	//����VirtualAddress�ĵ�ַ��Ҫ�������һ���ڱ��ж���ǰ�ڴ��е�ʵ�ʴ�С?
	//���ļ��ж����Ĵ�С���ֱ�ʹ��VirtualAddress�������ǵ�ֵ���ĸ��󣬾���
    //�ĸ���
    //VirtualAddress+max(VirtualSize,SizeOfRawData)
    //��������Ĺ�ʽ

	//�жϳ�Ҫ��ӵ�ֵ   ��Ŀ����   
	DWORD add_size = pLastSect->Misc.VirtualSize > pLastSect->SizeOfRawData ? pLastSect->Misc.VirtualSize : pLastSect->SizeOfRawData;

	printf("pLastSectionHeader: %x\n", pLastSect);
	printf("add_size: %x\n", add_size);
	printf("numberOfSection: %x\n", pPE->NumberOfSections);
	printf("pLastSect->Misc.VirtualSize: %x\n", pLastSect->Misc.VirtualSize);
	printf("pLastSect->SizeOfRawData: %x\n", pLastSect->SizeOfRawData);
	printf("add_size: %x\n", add_size);

	//�����ڱ�ĵ�ַ
	*pSecVirtualAddress = pLastSect->VirtualAddress + add_size;

	//SectionAlignment ����   �ڴ�
	if (*pSecVirtualAddress % pOp->SectionAlignment)
	{
		*pSecVirtualAddress = *pSecVirtualAddress / pOp->SectionAlignment * pOp->SectionAlignment + pOp->SectionAlignment;
	}

	*pSecSizeOfRawData = 0x1000;
	*pSecPointToRawData = pLastSect->PointerToRawData + pLastSect->SizeOfRawData;

	//FileAlignment ����    �ļ�
	if (*pSecPointToRawData % pOp->FileAlignment)
	{
		*pSecPointToRawData = *pSecPointToRawData / pOp->FileAlignment * \
			pOp->FileAlignment + pOp->FileAlignment;
	}

	*pSecCharacteristics = 0x40000040;

	*pNewImageBuffer = pTempNewImageBuffer;
	pTempNewImageBuffer = NULL;

	return sizeOfFile;
}

BOOL MemeryTOFile(IN LPVOID pMemBuffer, IN size_t size, OUT LPSTR lpszFile)
{
	FILE* fp = NULL;
	fp = fopen(lpszFile, "wb+");
	if (!fp)
	{
		printf("��ȡʧ��\n");
		fclose(fp);
		return FALSE;
	}
	fwrite(pMemBuffer, size, 1, fp);
	fclose(fp);
	fp = NULL;
	return TRUE;
}

VOID NewSectionsInCodeSec()
{
	LPVOID pFileBuffer		 = NULL;
	LPVOID pNewImageBuffer	 = NULL;
	BOOL isOK = FALSE;

	char FilePath1[] = "D:/ipmsg.exe";
	char FilePath2[] = "ipmsg_S.exe";

	DWORD size1 = 0;
	DWORD size2 = 0;

	//File->FileBuffer 

	size1 = ReadPEFile(FilePath1, &pFileBuffer);
	if (size1 == 0 || !pFileBuffer)
	{
		printf("�ļ�-->������ʧ��\r\n");
		return;
	}
	printf("�ļ�-->�������ɹ�\n");


	//FileBuffer ->NewImageBuffer

	size2 = CopyFileBufferToNewImageBuffer(pFileBuffer, size1, &pNewImageBuffer);
	if (size2 == 0 || !pNewImageBuffer)
	{
		printf("FileBuffer-->NewImageBufferʧ��\r\n");
		free(pFileBuffer);
		return;
	}
	printf("FileBuffer-->NewImageBuffer�ɹ�\r\n");


	//NewImageBuffer -> �ļ�

	isOK = MemeryTOFile(pNewImageBuffer, size2, FilePath2);
	if (!isOK)
	{
		printf("�����ڱ�ͽڴ���ʧ��\r\n");
	}
	printf("�����ڱ�ͽڴ��̳ɹ�\r\n");

}

int main()
{
	NewSectionsInCodeSec();

	return 0;
}