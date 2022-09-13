// gbpeall.h: interface for the gbpeall class.
//
//////////////////////////////////////////////////////////////////////

#define _CRT_SECURE_NO_WARNINGS
#if !defined(AFX_GBPEALL_H__C24C6881_E003_41F7_BE14_24DDA1702CCD__INCLUDED_)
#define AFX_GBPEALL_H__C24C6881_E003_41F7_BE14_24DDA1702CCD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include<stdio.h>
#include <string.h>
#include <windows.h>
#include <stdlib.h>


#define debug 1
//#define FILEPATH_IN         "C:\\WINDOWS\\system32\\kernel32.dll"
//    #define FilePath_In         "C:\\cntflx\\notepad.exe"
#define FilePath_In         "ipmsg.exe"
//#define FilePath_Out        "C:\\cntflx\\notepadnewpes.exe"
//#define FilePath_Out        "C:\\cntflx\\ipmsgnewpeaddcodes.exe"
//#define FilePath_Out        "C:\\cntflx\\ipmsgnewaddsections.exe"
//#define FilePath_Out        "C:\\cntflx\\ipmsgextendsections.exe"
#define FilePath_Out        "ipmsg_cntf_merge.exe"
#define MESSAGEBOXADDR      0x77D5050B
#define SHELLCODELENGTH     0x12 //16���Ƶģ�ת��Ϊʮ���ƾ���18

extern BYTE ShellCode[];

//���ļ� --->FileBuffer
DWORD ReadPEFile(IN const char* lpszFile, OUT LPVOID* pFileBuffer);

//д��ImageBuffer,FileBuffer ---> ImageBuffer
DWORD CopyFileBufferToImageBuffer(IN LPVOID pFileBuffer, OUT LPVOID* pImageBuffer);

//д��NewImageBuffer, FileBuffer ---> NewImageBuffer
DWORD CopyFileBufferToNewImageBuffer(IN LPVOID pFileBuffer, IN size_t fileSize, OUT LPVOID* pNewImageBuffer);

//д��NewImageBuffer, ���﹩�����ʹ�ã�
DWORD FileBufferToModifyImageBuffer(IN LPVOID pFileBuffer, OUT LPVOID* pNewImageBuffer);

//д�뵽NewBuffer��Ŀ���ǽ�������ImageBuffer����������Ϊ����׼��
DWORD CopyImageBufferToNewBuffer(IN LPVOID pImageBuffer, OUT LPVOID* pNewBuffer);

//д�뵽NewImageBuffer�����﹩�ϲ���ʹ��
DWORD ImageBufferMergeSections(IN LPVOID pImageBuffer, OUT LPVOID* pNewBuffer);

//д��pNewBuffer���棬��pNewImageBufferд�� ---> pNewBuffer
//DWORD ModifyImageBufferToNewBuffer(IN LPVOID pNewImageBuffer,OUT LPVOID* pNewBuffer);

//RvaתFoa
DWORD RvaToFileOffset(IN LPVOID pFileBuffer, IN DWORD dwRva);

//FoaתRVA
DWORD FoaToImageOffset(IN LPVOID pFileBuffer, IN DWORD dwFoa);

//�����С
DWORD AlignLength(DWORD Actuall_size, DWORD Align_size);

//��һ�ֶ�����㷽ʽ
DWORD Alignment(DWORD alignment_value, DWORD addend, DWORD address);

//��MemBufferд�뵽Ӳ�̣�������ǽ������޸ĺõ��ڴ��ļ������뵽����Ӳ���У�
BOOL MemeryTOFile(IN LPVOID pMemBuffer, IN size_t size, OUT const char* lpszFile);

//DWORD RvaToFileOffset(IN LPVOID pFileBuffer,IN DWORD dwRva);

//���ú��������ShellCode����
VOID AddCodeInCodeSec();  //������ú����õ������4������
//ReadPEFile CopyFileBufferToImageBuffer CopyImageBufferToNewBuffer MemeryTOFile

//���ú����������ڱ�ͽڲ�����
VOID NewSectionsInCodeSec();  //������ú����õ������3������
//ReadPEFile CopyFileBufferToNewImageBuffer MemeryTOFile

//���ú������������һ����
VOID ExtendLastSectionsInCodeSec(); //������ú����õ������4������
//ReadPEFile FileBufferToModifyImageBuffer CopyImageBufferToNewImageBuffer MemeryTOFile

//���ú������ϲ���
VOID ModifySectionsOneInCodeSec(); //������ú����õ������4������
//ReadPEFile CopyFileBufferToImageBuffer FileBufferToModifyOneImageBuffer MemeryTOFile

//���ú�����Rva��Foa֮����໥ת����
VOID RvaAndFoaConversion(); //������ú����õ������3������
//ReadPEFile RvaToFileOffset FoaToImageOffset

#endif // !defined(AFX_GBPEALL_H__C24C6881_E003_41F7_BE14_24DDA1702CCD__INCLUDED_)