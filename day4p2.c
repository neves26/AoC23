#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#define MYNUM 10 //5 10
#define WINNUM 25 //8 25
#define GAMES 208 //6 208

bool isNum(char n)
{
	return (n >= 48 && n <= 57)? true : false;
}

int cmpfunc(const void* a, const void* b)
{
	return ( *(int*)a - *(int*)b);
}

int getNum(char* buffer, int* i)
{
	int j = 0, num = 0, power = 0, tmp = 0;
	for(j = *i; isNum(buffer[j]); j++);
	tmp = j;

	for (j--; *i <= j; j--, power++)
	{
		num += pow(10,power) * (buffer[j] - 48);
	}
	*i = tmp;
	return num;
}

int main(int argc, char* argv[])
{
	int i = 0, j = 0, k = -2, cards[GAMES][MYNUM+WINNUM];
	bool flag = true;
  int numCards[GAMES];
	int curr = 0;
	int count = 0, sum = 0;
	int num = 0;
	char buffer[400];
	FILE* fp = NULL;

	if(argc != 2)
	{
		fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
		return 1;
	}

	fp = fopen(argv[1], "r");
	if(fp == NULL)
	{
		fprintf(stderr, "Error: File %s could not be open\n", argv[1]);
		return 1;
	}
	
	for (; i < GAMES; i++)
	{
    numCards[i] = 1;
		fgets(buffer, 400, fp);
		k = -2;
		for (j = 0; buffer[j] != '\n'; j++)
		{
			if (isNum(buffer[j]))
			{
				num = getNum(buffer, &j);
				k++;
			}

			if (k >= 0)
			{
				cards[i][k] = num;
			}
		}
	}

	for (i = 0; i < GAMES; i++)
	{
		count = 0;
		flag = true;
		qsort(cards[i], MYNUM+WINNUM, sizeof(int), cmpfunc);
		for(j=1, curr = cards[i][j-1]; j < MYNUM+WINNUM; j++)
		{
			if(cards[i][j] == curr && flag) {
				count++;
				flag = false;
			} else if(cards[i][j] != curr) {
				curr = cards[i][j];
				flag = true;
			} else if(cards[i][j] == curr && !flag) {
				printf("%d repeat number\n", cards[i][j]);
			} else {
				fprintf(stderr, "Undefined error\n");
				return 1;
			}
		}


		for (j = i+1; j < GAMES && j <= i + count; j++)
		{
			numCards[j] += numCards[i];
		}
        
		sum += numCards[i];

	}
	
	printf("Sum: %d\n", sum);

	fclose(fp);
	return 0;
}