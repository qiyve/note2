#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


//1�����̳��޺�������(��ӡSub������麯����)
struct Base1
{
public:
    virtual void Function_1()
    {
        printf("Base:Function_1...\n");
    }
    virtual void Function_2()
    {
        printf("Base:Function_2...\n");
    }
    virtual void Function_3()
    {
        printf("Base:Function_3...\n");
    }
};
struct Sub1 :Base1
{
public:
    virtual void Function_4()
    {
        printf("Sub:Function_4...\n");
    }
    virtual void Function_5()
    {
        printf("Sub:Function_5...\n");
    }
    virtual void Function_6()
    {
        printf("Sub:Function_6...\n");
    }
};

void test()
{
    //�鿴 Sub ���麯����		
    Sub1 s;
    //�����ǰ�ĸ��ֽھ����麯����				
    printf("Sub ���麯�����ַΪ��%x\n", *(int*)&s);
    //ͨ������ָ����ú�������֤��ȷ��	
    typedef void(*Function)(void);
    Function pfn;
   //����
    for (int i = 0; i < 6; i++)
    {
       // * ((int*)(*(int*)&sub) + i);       (int*)(*(int*)&sub) + i   ����� �麯����ַ���ƫ�� 
       // (*(int*)&sub) ����ַ              * ((int*)(*(int*)&sub) ȡ�����ǰ4�ֽڽ����� Ҳ���ǵ�һ���麯����ַ
        pfn = (Function)*((int*)(*(int*)&s) + i);
        pfn();
    }
 
}

int main01()
{
    test();
    return 0;

}


//2�����̳��к�������(��ӡSub������麯����)
struct Base
{
public:
    virtual void Function_1()
    {
        printf("Base:Function_1...\n");
    }
    virtual void Function_2()
    {
        printf("Base:Function_2...\n");
    }
    virtual void Function_3()
    {
        printf("Base:Function_3...\n");
    }
};
struct Sub :Base
{
public:
    virtual void Function_1()
    {
        printf("Sub:Function_1...\n");
    }
    virtual void Function_2()
    {
        printf("Sub:Function_2...\n");
    }
    virtual void Function_6()
    {
        printf("Sub:Function_6...\n");
    }
};

void test1()
{
    Sub sub;
    typedef void(*Func)(void);
    Func pfnc;

    //Sub �� func1 func2 �Ѹ����� func1  func2 ���¸����� 
    //���Դ�ӡʱ ���ܰ��ո���ǰ������ӡ����ȡ����� ѭ����û�������� �Ƿ�Ѱַ����
    //for (int i = 0; i < 6; i++)  err
    for (int i = 0; i < 4; i++)
    {
        pfnc = (Func) * ((int*)(*(int*)&sub) + i);
        pfnc();
    }
}

int main()
{
  
    test1();
    return 0;
}