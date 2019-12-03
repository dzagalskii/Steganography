#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>

void tobit(int x, int *byte);
void invert(int *byte);
int todec(int *byte);

int mas[10000000];
int bitext[10000000];

int main()
{
	int stepen;
	printf("enter the degree of packaging 1/4/8: ");
	scanf("%d", &stepen);
	if((stepen == 1)||(stepen == 4)||(stepen == 8))
	{
		printf("okay! you chose the degree of packing %d\n", stepen);
		printf("text: C:/laba/1.txt\n");
		printf("picture: C:/laba/1.bmp\n");
		printf("container: C:/laba/2.bmp\n");
	}
	else
	{
		printf("ERROR!\n");
		system("pause");
		return 0;
	}
	/*файл секретного сообщения*/
	int byte[8];
	//int bitext[100000];
	FILE *t = fopen("C:/laba/1.txt", "rb");
	//int mas[100000];
	int k = 0; 
	while(fgetc(t)!= -1)
	{
		fseek(t, -1, SEEK_CUR);
		mas[k] = fgetc(t);
		k++;
	}
	int a = 0; //длина бит сообщения
	for(int i = 0; i < k; i++)
	{
		tobit(mas[i], byte);
		for(int g = 0; g < 8; g++)
		{
			bitext[a] = byte[g];
			a++;
		}
	}
	/*файл с картинкой*/
	int x;
	FILE *f = fopen("C:/laba/1.bmp", "rb"); 
	FILE *g = fopen("C:/laba/2.bmp", "w+b");
	int b = 0;
	int start = 0;
	int end = a + 8;
	while(fgetc(f) != EOF)
	{
		if(start < 39) //ничего не трогать
		{
			fseek(f, -1, SEEK_CUR);
			x = fgetc(f);
			fputc(x, g);
			start++;
		}
		else if(start == 39) //39 байт содержит инф о степени упаковки
		{
			fputc(stepen, g);
			start++;
		}
		else //записывать
		{
			fseek(f, -1, SEEK_CUR);
			x = fgetc(f);
			tobit(x, byte);
			/*запись секретного сообщения*/
			if((b >= a)&&(b < end))
			{
				for(int i = 0; i < 8; i++)
				{
					byte[i] = 1;
				}
				b++;
			}
			else if(b < a)
			{
				if(stepen == 4)
				{
					for(int i = 0; i < 4; i++)
					{
						byte[4+i] = bitext[b];
						b++;
					}
				}
				else if(stepen == 8)
				{
					for(int i = 0; i < 8; i++)
					{
						byte[i] = bitext[b];
						b++;
					}
				}
				else if(stepen == 1)
				{
					byte[7] = bitext[b];
					b++;
				}
			}
			fputc(todec(byte), g);
		}
	}
	if(b < a + 8)
	{
		printf("ERROR! TEXT IS VERY LONG!\n");
	}
	else
	{
		printf("COMPLETE!\n");
	}
	fclose(f);
	fclose(g);
	fclose(t);
	system("pause");
	return 0;
}

void tobit(int x, int *byte) /*перевести число в строку из 8бит*/
{
	for(int i = 0; i < 8; i++)
	{
		byte[i] = x%2;
		x = x/2;
	}
	invert(byte);
}

void invert(int *byte)   /*перевернуть строку из 8бит*/
{
	int tmp[8];
	int g = 0;
	for(int i = 7; i > -1; i--)
	{
		tmp[g] = byte[i];
		g++;
	}
	for(int i = 0; i < 8; i++)
	{
		byte[i] = tmp[i];
	}	
}

int todec(int *byte)  /*перевод из 8бит в число*/
{
	int x = 0;
	int st = 7;
	for(int i = 0; i < 8; i++)
	{
		x = x + byte[i]*pow(2, st);
		st--;
	}
	return x;
}