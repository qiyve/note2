﻿#include<stdio.h>

//课后练习：
void func1()
{
	//假设现在有5个班，每个班10个人，设计一个二维数组存储这些人的年龄.
	int arr[5][10] =
	{ {1,2,3,4,5,6,7,8,9,10},
	  {11,12,13,14,15,16,17,18,19,20 },
	  {21,22,23,24,25,26,27,28,29,30 },
	  {31,32,33,34,35,36,37,38,39,40},
	  {41,42,43,44,45,46,47,48,49,50},
	};

	//如果想知道第二个班的第6个人的年龄，应该如何获取？编译器该如何获取？
	int x =  arr[1][5];
	//arr[1*10 + 5]

	/*打印所有班级，所有学生的年龄(每个班级打印一行).
	for (int i = 0; i < 5; i++)
	{
		printf("第%d班学生年龄如下：\n", i + 1);
		for (int j = 0; j < 10; j++)
		{
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}*/
	
	//将第三个班级的超过20岁的学生的年龄修改为21岁.
	for (int i = 2; i < 3; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (arr[i][j] > 20)
			{
				arr[i][j] = 21;
			}
		}
	}

	for (int i = 0; i < 5; i++)
	{
		printf("第%d班学生年龄如下：\n", i + 1);
		for (int j = 0; j < 10; j++)
		{
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}

	//打印出每个班级学生的年龄的和.
	//for (int i = 0; i < 5; i++)
	//{
	//	int sum = 0;
	//	for (int j = 0; j < 10; j++)
	//	{
	//		sum += arr[i][j];
	//	}
	//	printf("第%d班的学生年龄总和为：%d\n", i + 1, sum);
	//}

}

//归并排序

void func2()
{
//数组一：[3, 5, 7, 9, 12, 25, 34, 55]
//数组二：[4, 7, 9, 11, 13, 16]
//将两个数组中所有数据进行从小到大的排序，存储到
//另一个数组中.

	int arr1[] = { 3,5,7,9,12,25,34,55 };
	int arr2[] = { 4,7,9,11,13,16 };
	int arr3[20] = { 0 };

	int i = 0;
	int j = 0;
	int k = 0;

	while (i<8)
	{
		if (arr1[i] > arr2[j])
		{
			arr3[k] = arr2[j];
			j++;
		}
		else
		{
			arr3[k] = arr1[i];
			i++;
		}
		k++;
	}

	for (int  z = 0; z < 14; z++)
	{
		printf("%d ", arr3[z]);
	}
	printf("\n");
}



int main()
{
	func1();

	//func2();

	return 0;
}
