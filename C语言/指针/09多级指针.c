#include <stdio.h>


int main01()
{
	int a[] = { 1,2,3 };
	int b[] = { 4,5,6 };
	int c[] = { 7,8,9 };
	//ָ��������һ������Ķ�ά�����ģ��
	//ָ�������Ӧ����ָ��
	int* arr[] = { a,b,c };

	//ָ������Ͷ���ָ�뽨����ϵ
	int** p = arr;

	//printf("%d\n", **p); //arr[0][0]  a[0]
	//����ָ���ƫ���� �൱��������һ��һά�����С
	//printf("%d\n", **(p + 1)); // arr[1][0]
	
	//һ��ָ���ƫ���� �൱��������һ��Ԫ��
	//printf("%d\n", *(*p + 1));  //arr[0][1]

	//printf("%d\n", *(*(p + 1) + 1)); //*(p+1) b�ĵ�ַ

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			//printf("%d ", p[i][j]); //��ά���鷽ʽ
			//printf("%d ", *(p[i] + j)); //ָ������ jƫ����
			printf("%d ", *(*(p + i) + j));//����ָ��
		}
		//printf("\n");
		puts(""); //Ҳ����������
	}

	system("pause");
	return 0;
}

int main()
{
	int a = 10;
	int b = 20;
	int* p = &a;
	int** pp = &p;

	//*pp = &b;// �ȼ��� p = &d
	**pp = 100;
	//*pp = 100; err

	printf("%d\n", *p);
	printf("%d\n", a);

	system("pause");
	return 0;
}