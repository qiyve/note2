#include<stdio.h>
#include<stdlib.h>

//������ϰ��
//1������һ��unsiged char ���ͣ�ͨ������Ϊ��3��5��7λ��ֵ, ��ֵʱ����
//Ӱ�쵽����λԭ����ֵ.
//(ʹ��λ����ָ����磺& | !^ << >>��)
void func()
{
	unsigned char c = 0;
	char x = 4;

	//     0000 0000 
	//Xor  0000 0100
	c = c ^ x;
	printf("%x\n", c ^ x);

	//  0001 0000
	 c += c << 2;
	printf("%x\n", c ); 
	// 0001 0100

	char y = 0x40;
	//   0100 0000
	// | 0001 0100    1010 1011
	c = c | y;
	printf("%x\n", c);

	char a = 0xab;
	c = c & a;  
	// 0000 0000
	printf("%x\n", c);
}

//2���ж�ĳ��λ��ֵ�Ƿ�Ϊ1.
//(ʹ��λ����ָ����磺 & | !^ << >>��)
void  test(char c, int b)
{
	if ((c >> (8 - b)) % 2 != 0 )
	{
		printf("��%dλ��ֵΪ: 1\n", b);
		
	}   
	else
	{
		printf("��%dλ��ֵΪ: 0\n", b);
	}

}

//3����ȡ��7��6��5λ��ֵ����ʮ������ʾ(unsigned).
//(ʹ��λ����ָ����磺 & | !^ << >>��)

int main()
{
	
	unsigned char c = 0xab;
	int a = 0;
	test(c, 1);


	printf("%x", c >> 1);

	return 0;
}
