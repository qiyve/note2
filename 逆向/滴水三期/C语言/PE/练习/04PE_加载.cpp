#include"04PE���ع���.h"

#define FILEPATH_IN  "D:/ipmsg.exe"
#define FILEPATH_OUT "D:/ipmsg_s.exe"

VOID Test()
{
	DWORD	Size = 0;
	BOOL	isok = FALSE;
	LPVOID	pFileBuffer = NULL;
	LPVOID	pImageBuffer = NULL;
	LPVOID	pNewBuffer = NULL;

	//File-> FileBuffer
	Size = ReadPEFile((LPSTR)FILEPATH_IN, &pFileBuffer);
	if (!pFileBuffer)
	{
		printf("File-> FileBufferʧ��");
		return;
	}


	//FileBuffer->ImageBuffer
	CopyFileBufferToImageBuffer(pFileBuffer, &pImageBuffer);

	if (!pImageBuffer)
	{
		printf("FileBuffer->ImageBufferʧ��");
		free(pFileBuffer);
		return;
	}

	//ImageBuffer->NewBuffer
	Size = CopyImageBufferToNewBuffer(pImageBuffer, &pNewBuffer);
	if (!Size || !pNewBuffer)
	{
		printf("ImageBuffer->NewBufferʧ��");
		free(pFileBuffer);
		free(pImageBuffer);
		return;
	}

	//NewBuffer->�ļ�
	isok = MemeryTOFile(pNewBuffer, Size, (LPSTR)FILEPATH_OUT);
	if (isok)
	{
		printf("���̳ɹ�");
		return;
	}

	//�ͷ��ڴ�
	free(pFileBuffer);
	free(pImageBuffer);
	free(pNewBuffer);
}


int main()
{
	Test();

	return 0;
}