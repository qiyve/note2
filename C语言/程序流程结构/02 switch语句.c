#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

int main()
{
	int score;
	scanf("%d", &score);
	switch (score/10)
	{
	case 10:
		printf("����\n");
		break;
	case 9:
		printf("����\n");
		break;
	case 8:
		printf("����\n");
		break;
	case 7:
		printf("����\n");
		break;
	case 6:
		printf("����\n");
		break;
	case 5:
		printf("������\n");
		break;
	default:
		printf("������\n");
		break;
	}

	return 0;
}

