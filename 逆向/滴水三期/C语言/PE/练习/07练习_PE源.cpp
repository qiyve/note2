#include"Դ.h"

//����һ��ȫ�ֱ���
BYTE ShellCode[] =
{
    0x6A,00,0x6A,00,0x6A,00,0x6A,00, //MessageBox push 0��Ӳ����
    0xE8,00,00,00,00,  // call���ָ��E8�ͺ��������Ӳ����
    0xE9,00,00,00,00   // jmp���ָ��E9�ͺ��������Ӳ����
};

// allpelx.cpp : Defines the entry point for the console application.
//


int main()
{
    //Fun();
    //AddCodeInCodeSec();
    //NewSectionsInCodeSec();
    //ExtendLastSectionsInCodeSec();
    ModifySectionsOneInCodeSec();
    //RvaAndFoaConversion();

    system("pause");
    return 0;
}