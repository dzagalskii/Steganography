#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>

void tobit(int x, int *byte);
void invert(int *byte);
int onebyte(int *byte);
int todec(int *byte);

int bitext[10000000];

int main()
{
	printf("container: C:/laba/2.bmp\n");
	printf("text: C:/laba/2.txt\n");
	int byte[8];
	//int bitext[100000];
	FILE *f = fopen("C:/laba/2.bmp", "rb"); //контейнер
	FILE *t = fopen("C:/laba/2.txt", "wb"); //текстовый файл
	int x, start = 0, end = 0, a = 0, stepen;
	while((fgetc(f) != EOF))
	{
		if(start < 39) //начало не смотрим
		{
			fseek(f, -1, SEEK_CUR);
			x = fgetc(f);
			start++;
		}
		else if(start == 39)
		{
			fseek(f, -1, SEEK_CUR);
			stepen = fgetc(f);
			printf("the degree of packing: %d\n", stepen);
			start++;
		}
		else //записываем и ищем конец
		{
			fseek(f, -1, SEEK_CUR);
			x = fgetc(f);
			tobit(x, byte);
			if(onebyte(byte) == 1) 
			{
				end++;
			}
			else
			{
				end = 0;
			}
			
			if(end == 8)
			{
				if(stepen == 1)
				{
					printf("COMPLETE!\n");
					a = a - 6;
					break;
				}
				else if(stepen == 4)
				{
					printf("COMPLETE!\n");
					a = a - 24;
					break;
				}
				else if(stepen == 8)
				{
					printf("COMPLETE!\n");
					a = a - 48;
					break;
				}
			}
			else
			{
				if(stepen == 1)
				{
					bitext[a] = byte[7];
					a++;
				}
				else if(stepen == 4)
				{
					for(int i = 0; i < 4; i++)
					{
						bitext[a] = byte[4+i];
						a++;
					}
				}
				else if(stepen == 8)
				{
					for(int i = 0; i < 8; i++)
					{
						bitext[a] = byte[i];
						a++;
					}
				}
			}
		}
	}
	for(int i = 0; i < a - 8; i = i + 8)
	{
		for(int g = 0; g < 8; g++)
		{
			byte[g] = bitext[i+g];
		}
		fputc(todec(byte), t);
	}
	fclose(f);
	fclose(t);
	system("pause");
	return 0;
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

void tobit(int x, int *byte) /*перевести число в строку из 8бит*/
{
	for(int i = 0; i < 8; i++)
	{
		byte[i] = x%2;
		x = x/2;
	}
	invert(byte);
}

int onebyte(int *byte)
{
	int end = 0;
	for(int i = 0; i < 8; i++)
	{
		if(byte[i] == 1)
		{
			end++;
		}
	}
	if(end == 8)
		return 1;
	else
		return 0;
}