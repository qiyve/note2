#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

//�����ж�.exe�ļ�����
int file_len(FILE* fp)
{
	int num = 0;
	//��˼�ǰ�fp�ļ���дλ��ָ���SEEK_END��ʼ����0���ֽ�.
	fseek(fp, 0, SEEK_END);

	//���� ftell ���ڵõ��ļ�λ��ָ�뵱ǰλ��������ļ��׵�ƫ���ֽ�����
	num = ftell(fp);
	// ʹ����Ϻ�Ҫ���ļ�ָ��ָ���ļ���ʼ
	fseek(fp, 0, SEEK_SET);

	//SEEK_SET	�ļ��Ŀ�ͷ
	//SEEK_CUR	�ļ�ָ��ĵ�ǰλ��
	//SEEK_END	�ļ���ĩβ

	return num;
}

void func()
{
	//1�������ļ�ָ��
	FILE* fp1 = NULL;
    //2/��ʼ��exe�ļ�����
	int FpSize = 0;
	// ���ļ�������д��
	fp1 = fopen("C:\\Windows\\System32\\notepad.exe", "rb");
	//��ȡexe��С
	FpSize = file_len(fp1);
	//�����ڴ�
	char* FILE_f = (char*)malloc(FpSize);
	// ��.exeд���ڴ���
	if (FILE_f != NULL)
	{
		fread(FILE_f, FpSize, 1, fp1);
	}
	//�����ڴ���
	int s = (int)FILE_f;
	printf("%x\n", s);
	//�ͷŶ���
	free(FILE_f);
	fclose(fp1);
	
}

int main()
{
	func();


	return 0;
}


