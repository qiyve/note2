#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>	


int main()
{
	int score;
	scanf("%d", &score);

	//if(���ʽ){}
	//if(���ʽ){} else{}
	//if(���ʽ1){} else if(���ʽ2){} else{}
	//����Ƕ��
	if (score > 700)
	{
		printf("�����廪");
		if (score > 720)
		{
			printf("��Ҫѧ�����\n");
		}
		else if (score > 710)
		{
			printf("��Ҫѧ��");
		}
	}
	else if(score>650)
	{
		printf("���ϱ���");
	}

	else
	{
		printf("���ϴ�ר");
	}

	system("pause");
	return 0;
}