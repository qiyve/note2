#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<Windows.h>
#include<stdlib.h>

#define FilePath_In "C:\\Windows\\System32\\notepad.exe"
#define debug  0   //����

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
	fread(pTempBuffer, 1, Size, pf);

	*pFileBuffer = pTempBuffer;
	pTempBuffer = NULL;
	fclose(pf);

	return Size;
}


DWORD RvaToOffset(IN LPVOID pFileBuffer, DWORD dwRva)
{
	PIMAGE_DOS_HEADER pDos = NULL;
	PIMAGE_NT_HEADERS pNT = NULL;
	PIMAGE_FILE_HEADER pPE = NULL;
	PIMAGE_OPTIONAL_HEADER32 pOP = NULL;
	PIMAGE_SECTION_HEADER pSect = NULL;
	
	DWORD NumberOfSection = 0;
	DWORD dwFOA = 0;

	//�ж�ָ���Ƿ���Ч
	if (!pFileBuffer)
	{
		printf("pFileBufferָ����Ч\n");
		return 0;
	}

	//�ж�MZ���
	pDos = (PIMAGE_DOS_HEADER)pFileBuffer;
	if (*((PWORD)pDos) != IMAGE_DOS_SIGNATURE)
	{
		printf("������ЧMZ���\n");
		return 0;
	}

	//�ж�PE
	pNT = (PIMAGE_NT_HEADERS)((DWORD)pDos + pDos->e_lfanew);
	if (*((PDWORD)pNT) != IMAGE_NT_SIGNATURE)
	{
		printf("������ЧPE���\n");
		return 0;
	}

	pPE = (PIMAGE_FILE_HEADER)((DWORD)pNT + 0x4);
	pOP = (PIMAGE_OPTIONAL_HEADER32)((DWORD)pPE + IMAGE_SIZEOF_FILE_HEADER);
	pSect = (PIMAGE_SECTION_HEADER)((DWORD)pOP + pPE->SizeOfOptionalHeader);

	//�������ʱ�ڱ�ָ���������ļ������
	NumberOfSection = pPE->NumberOfSections;
	PIMAGE_SECTION_HEADER pTempSect = pSect;

	//�ж�dwRva���ڵĽ�
	if (dwRva <= pOP->SizeOfHeaders)
	{
		return (DWORD)dwRva;
	}
		//�������ж����rva��ַ�����Ľ��ڵ�һ����֮ǰ��ôֱ�ӷ���rva�ĵ�ַ��
		//����������ǿ�ʼ�������ҽڣ�
	else
	{
		for (DWORD i = 0; i < NumberOfSection; i++, pTempSect++)
		{
			if ((dwRva >= pTempSect->VirtualAddress) && (dwRva <= pTempSect->VirtualAddress + pTempSect->Misc.VirtualSize))
			{
				dwFOA = dwRva - pTempSect->VirtualAddress + pTempSect->PointerToRawData;
			}
		}
	}
	return dwFOA;
}

 //����ض�λ��
DWORD GetDataDirectoyOfBaseRelocation(IN PVOID pFileBuffer)
{
	// ��ʼ��PEͷ���ṹ��
	PIMAGE_DOS_HEADER  pDos = NULL;
	PIMAGE_NT_HEADERS  pNT = NULL;
	PIMAGE_FILE_HEADER pPE = NULL;
	PIMAGE_OPTIONAL_HEADER32  pOP = NULL;
	PIMAGE_SECTION_HEADER   pSect = NULL;

	PIMAGE_DATA_DIRECTORY   pDataDirectory = NULL;   //Ŀ¼��Ŀ��  �׵�ַ
	PIMAGE_BASE_RELOCATION  pBaseRelocation = NULL;  //�ض�λ��   �׵�ַ

	DWORD RVA_BaseRelocationTable = 0;            //�ض�λ���λ��  RVA
	DWORD SizeOfBlock_BaseRelocationTable = 0;    // ��Ĵ�С

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
	pDos = (PIMAGE_DOS_HEADER)pFileBuffer;
	if (*((PWORD)((DWORD)pFileBuffer + pDos->e_lfanew)) != IMAGE_NT_SIGNATURE)
	{
		printf("pFileBuffer����һ����Ч��PE��־\r\n");
		return 0;
	}

	// ǿ�ƽṹ������ת��
	pNT = (PIMAGE_NT_HEADERS)((DWORD)pFileBuffer + pDos->e_lfanew);
	pPE = (PIMAGE_FILE_HEADER)((DWORD)pNT + 0x04); // �������ǿ������ת��
	pOP = (PIMAGE_OPTIONAL_HEADER32)((DWORD)pPE + IMAGE_SIZEOF_FILE_HEADER);
	pSect = (PIMAGE_SECTION_HEADER)((DWORD)pOP + pPE->SizeOfOptionalHeader);
	//pSectionHeader = (PIMAGE_SECTION_HEADER)(pNTHeader+0x01);
	//������ʾ�ڱ�ָ��pSectionHeader����һ��д��������ͨ��NTͷ�����һ������Ľṹ���Ƚ����ƶ���
	//��ΪNTͷ����ṹ������4+20+224=248 --> 16����F8��ͨ����0x01��ֱ���ƶ�F8���ֽڣ��պ����ڽڱ�λ�ã�

	pDataDirectory = (PIMAGE_DATA_DIRECTORY)pOP->DataDirectory;

	//��λ�ض�λ��VirtualAddress ��RVA��ַ  | �� IMAGE_DIRECTORY_ENTRY_BASERELOC  [5]  |    ����Ŀ¼��ĵ�6���ṹ�������ض�λ��.
	RVA_BaseRelocationTable = pDataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress;
	//��λ�ض�λ��SizeOfBlock,�� ��Ĵ�С
	SizeOfBlock_BaseRelocationTable = pDataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].Size;

	if (!debug)
	{
		printf("�ض�λ��VirtualAddress��ַ: %#010X\r\n", RVA_BaseRelocationTable);
		printf("�ض�λ��SizeOfBlock��С: %#010X\r\n", SizeOfBlock_BaseRelocationTable);
	}

	if (!RVA_BaseRelocationTable)
	{
		printf("�������û�е�����.\r\n");
		return 0;
	}

	//�ض�λ��FOV��ַ�������FOA��ַ��Ϊ�� ����Ŀ¼����[5]��ȡ��RVA��ת��ΪFOA �� Ŀ����Ϊ������
	//ƫ�Ƶ�FileBuffer��׼ȷ��BaseRelocation �ض�λ����ʼ��ַ
	DWORD FOA_BaseRelocationTable = RvaToOffset(pFileBuffer, RVA_BaseRelocationTable);

	//��λ�ض�λ���ļ�ƫ�Ƶ�λ�ã� ����FileBuffer ���ļ�ƫ��
	pBaseRelocation = (PIMAGE_BASE_RELOCATION)((DWORD)pFileBuffer + FOA_BaseRelocationTable);

	if (!debug)
	{
		printf("�ض�λ��FOA��ַ: %#010X\r\n", FOA_BaseRelocationTable);
		printf("�ض�λ���ļ�ƫ�Ƶ�ַ: %#010X\r\n", pBaseRelocation);
	}

	//���� �� �������Ƶ�����������Ϊ 0    ��Name Ϊ8�ֽ�
	BYTE secName[9] = { 0 };  //�����Ƕ���9����ȵ��ֽ����� ����Ϊ0��Ϊ����Ľڲ�����׼��

	// �ض�λ���ƫ�� �ʹ�С����Ϊ 0 ��ִ��
	for (DWORD i = 0; i < pBaseRelocation->SizeOfBlock && pBaseRelocation->VirtualAddress; i++)
	{
		// ����pVirtualOfFOA_BaseReloc��FOA��ַ�Ǵ��ض�λ����ȡ��VirtualAddress����ת��ΪFOA��ַ��
		DWORD pVirtualOfFOA_BaseReloc = RvaToOffset(pFileBuffer, pBaseRelocation->VirtualAddress);

		// pSizeOfBlock_BaseReloc  �洢�����������
		DWORD pSizeOfBlock_BaseReloc = (pBaseRelocation->SizeOfBlock - 8) / 2;

		/*�����Ǹ���VirtualAddress��SizeOfBlock�ܹ�ռ8���ֽڣ�SizeOfBlock�ǵ�ǰ����д�С
	  ���м��㣬Ϊ����������������������Ȼ���ж���Щ����Ҫ�޸ĵ���;

	  �������ȣ�2�ֽ�
	  Ҳ�����������,�ڴ��е�ҳ��С��1000H Ҳ����˵2��12�η� �Ϳ��Ա�ʾ,һ��ҳ�����е�ƫ�Ƶ�ַ
	  ������Ŀ����16�ֽڸ���λ,�������ͣ�ֵΪ3���������Ҫ�޸ĵ�����ֵΪ0�������,�������ݶ��������
	  ���Բ����޸�.Ҳ����˵ ����ֻ��ע��4λ��ֵΪ3�ľͿ�����.
	  1000H --> 4096D --> 2��12�η�
	  12 + 4 = 16 bit
	  */

	  //��ʼͨ������ȷ���ýṹ�����ĸ�������
		for (DWORD j = 0; j < pPE->NumberOfSections; j++)
		{
			//pLowAddressOfFoa �ڿ���ʼƫ��   pHighAddressOfFoa����ǰƫ��
			DWORD pLowAddressOfFoa = RvaToOffset(pFileBuffer, pSect[i].VirtualAddress);
			DWORD pHighAddressOfFoa = RvaToOffset(pFileBuffer, pSect[i].Misc.VirtualSize);

			//  �ж����Ǹ��ڱ���
			if (pVirtualOfFOA_BaseReloc >= pLowAddressOfFoa && pVirtualOfFOA_BaseReloc <= pHighAddressOfFoa)
			{
				//���� ����
				memcpy(secName, pSect[i].Name, 8);
				break;
			}
		}
		//�����Ǵ�ӡ��ҳ����Ҫ��Ϣ
		printf("��: %X ->�ض�λ��VA: %#010X -> �ڵ�����:%s -> �������С: %#010X\r\n", i, \
			pBaseRelocation->VirtualAddress, secName, pSizeOfBlock_BaseReloc);

		//��ӡһ��ҳ�������ض�λ��Ϣ�͵�ַ

		//������ͨ��ƫ��8���ֽ�ָ����е�һ���������Ϊ�����2���ֽڣ�����ʹ��WORD����ָ������
		WORD* recAddr = (WORD*)((BYTE*)pBaseRelocation + 0x8);

		for (DWORD n = 0; n < pSizeOfBlock_BaseReloc; n++)
		{
			/*�����㷨���ͣ�
		 ��һ�д��룺ͨ����õĵ�һ��������2���ֽڵĵ�ַ��0x0FFF����������������ȥ���˸�4λ;
		 Ȼ��͵õ���׼ȷ�ĺ���12λ��ƫ�ƣ��պ�������Ҫ�ģ�ֱ�Ӱ����㷨��������ʹ�øý�������
		 VirtualAddress�������ƫ�ƣ���Ȼ�����VirtualAddress����Ҫת��ΪFOA�ĵ�ַ֮����м���
		 ��ʱ��õ���׼ȷ��Ҫƫ�Ƶ�ֵoffset������ͨ�������������ƫ�ƿɵõ�׼ȷ����Ҫ�޸ĵ�ƫ��
		 ��ַ��������type������������˵�ĸ�4λ����һ�����ͣ�������Ҫʹ�����Ƶķ�ʽ������Ϊ0x0011
		 Ҳ����3�����Դ����в��������������12λ���ɵõ�0x0011-->3;
		 ����ع������ƣ���Ϊint������з��ŵ�������,����˵�1λ�Ƿ���λ��0��1�������������ǵ���
		 �����0011������λ��0��ʾ������ô���Ƶ�ʱ��ǰ�油0���ɣ������ƶ�12λ��֮��type�����Ľ��
		 ����0x0011->3

		 �����Ǽ�������һ���ڵľ����������ӣ�
		 ��:0 -> �ض�λ��VA:0X00001000 -> �ڵ�����:.text -> �������С:0X00000088
		 recAddr[j]:0X0000315F ---> 0x315F ---> 0011 0001 0101 1111

		 offset:0X0000115F     ---> 0011 0001 0101 1111 & 0000 1111 1111 1111 --->0x015F
		 0x015F + 0x1000 = 0x115F ---> offset:0X0000115F

		 type:0X00000003  ---> 0011 0001 0101 1111 >> 12 ---> 0000 0000 0000 0011 --> 0x0011 --> 3
		 0X0000215F,0X00000003
		 */
			DWORD pRepair_RvaOffset = (recAddr[n] & 0x0FFF) + pVirtualOfFOA_BaseReloc;

			//printf("recAddr[j]:%#010X \r\n",recAddr[j]);
			//printf("offset:%#010X \r\n",offset);
			WORD type = recAddr[n] >> 12;//��λ
			//printf("type:%#010X \r\n",type);

			if (type != 0)
			{
				printf("%#010X,%#010X\r\n", pRepair_RvaOffset, type);
				//	system("pause");
			}
		}
		memset(secName, 0, 9);
		pBaseRelocation = (PIMAGE_BASE_RELOCATION)((BYTE*)pBaseRelocation + pBaseRelocation->SizeOfBlock);
	}
	return 0;
}


//����
void PrintBaseRelocation()
{
	LPVOID pFileBuffer = NULL;
	DWORD FileBufferSize = 0;
	DWORD BaseName_FunctionAddr = 0;
	DWORD BaseOrdinals_FUnctionAddr = 0;

	//File-->FileBuffer
	FileBufferSize = ReadPEFile((char*)FilePath_In, &pFileBuffer);
	if (FileBufferSize == 0 || !pFileBuffer)
	{
		printf("�ļ�-->������ʧ��\r\n");
		return;
	}
	printf("FileBufferSize: %#X \r\n", FileBufferSize);

	GetDataDirectoyOfBaseRelocation(pFileBuffer);

	free(pFileBuffer);
}

int main(int argc, char* argv[])
{
	PrintBaseRelocation();

	return 0;
}