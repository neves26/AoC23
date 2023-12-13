#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>

typedef struct mapCode
{
	unsigned long long int dest;
	unsigned long long int source;
	unsigned long long int range;
	struct mapCode* next;
} mapCode;

typedef struct seeds
{
	unsigned long long int num;
} seeds;


typedef struct map
{
	mapCode* stosoil;
	mapCode* stofertelizer;
	mapCode* ftowater;
	mapCode* wtolight;
	mapCode* ltotemperature;
	mapCode* ttohumidity;
	mapCode* htolocation;
} map;


bool isNum(char c)
{
	return (c >= 48 && c <= 57) ? true : false;
}

unsigned long long int getNum(char* buffer, int* i)
{
	int l = *i, r=*i-1, j = *i;
	unsigned long long int num = 0;

	for ( j = *i; isNum(buffer[j]) ; j++)
	{
		r++;
	}
	*i = r;
	for (j = 0; r >= l; j++, r--)
	{
		num += (buffer[r] - 48) * pow(10, j);
	}
	return num;
}

void getSeeds(char* buffer, seeds** seedsList, int* numSeeds)
{
	int i = 0, j = 0;
	unsigned long long int tmp[40];
	seeds* p1 = *seedsList;


	for (i = 0; i < 40; i++)
	{
		tmp[i] = -1;
	}
	 

	for (i = 0; buffer[i] != '\n'; i++)
	{
		if (isNum(buffer[i]))
		{
			tmp[j] = getNum(buffer, &i);
			j++;
		}
	}

	p1 = (seeds*) malloc(sizeof(seeds) * j);
	if(tmp == NULL)
	{
		fprintf(stderr, "Error: Could not allocate memory of size %d\n", j);
		exit(1);
	}

	for (i = 0; tmp[i] != -1; i++)
	{
		p1[i].num = tmp[i];
	}

	*seedsList = p1;
	*numSeeds = j;

	return;
}

void insertList(mapCode* p, mapCode* node)
{
	mapCode* tmp = p;

	for (;tmp->next != NULL;)
	{
		tmp = tmp->next;
	}
	
	tmp->next = node;
	return;
}

mapCode* getMode(map* p, mapCode* node, int mode)
{
	mapCode* tmp = NULL;
	switch (mode)
	{
		case 1:
			(p->stosoil == NULL)? p->stosoil = node : insertList(p->stosoil, node);
			break;
		case 2:
			(p->stofertelizer == NULL)? p->stofertelizer = node : insertList(p->stofertelizer, node);
			break;
		case 3:
			(p->ftowater == NULL)? p->ftowater = node : insertList(p->ftowater, node);
			break;
		case 4:
			(p->wtolight == NULL)? p->wtolight = node : insertList(p->wtolight, node);
			break;
		case 5:
			(p->ltotemperature == NULL)? p->ltotemperature = node : insertList(p->ltotemperature, node);
			break;
		case 6:
			(p->ttohumidity == NULL)? p->ttohumidity = node : insertList(p->ttohumidity, node);
			break;
		case 7:
			(p->htolocation == NULL)? p->htolocation = node : insertList(p->htolocation, node);
			break;
		default:
			break;
	}
	return tmp;
}

void getMap(FILE* fp, map* p, int mode)
{
	int hits = 0;
	mapCode m, *t = NULL;

	for (; (hits = fscanf(fp, "%llu %llu %llu", &m.dest, &m.source, &m.range)) == 3;)
	{
		t = (mapCode*) malloc(sizeof(mapCode) * 1);
		t->dest = m.dest;
		t->source = m.source;
		t->range = m.range;
		t->next = NULL;
		getMode(p, t ,mode);
	}

	return;
}

int main(int argc, char** argv)
{
	FILE* fp = NULL;
	char buffer[250] = "\0";
	seeds* seedsArray = NULL;
	map p;
	int i = 0, numSeeds = 0;
	unsigned long long int least = 18446744073709551610	 , num = 0;

	p.stosoil = NULL;
	p.stofertelizer = NULL;
	p.ftowater = NULL;
	p.wtolight = NULL;
	p.ltotemperature = NULL;
	p.ttohumidity = NULL;
	p.htolocation = NULL;

	if(argc != 2)
	{
		fprintf(stderr,"Usage: %s <filename>\n", argv[0]);
		return 1;
	}

	fp = fopen(argv[1], "r");
	if(fp == NULL)
	{
		fprintf(stderr, "Error: file %s not found\n", argv[1]);
		return 1;
	}

	while (feof(fp) == 0)
	{
		printf("\nI: %d\n", i);
		i++;
		fgets(buffer,250,fp);

		if(!strncmp("seeds", buffer, 5))
		{
			printf("seeds\n");
			getSeeds(buffer, &seedsArray, &numSeeds);
		}

		if(!strncmp("seed-", buffer, 5))
		{
			printf("seed to soil \n");
			getMap(fp,&p,1);
		}

		if(!strncmp("soil", buffer, 4))
		{
			printf("soil to fert\n");
			getMap(fp,&p,2);
		}

		if(!strncmp("fert", buffer, 4))
		{
			printf("fert to water\n");
			getMap(fp,&p,3);
			continue;
		}

		if(!strncmp("wate", buffer, 4))
		{
			printf("water to light\n");
			getMap(fp,&p,4);
			continue;
		}

		if(!strncmp("ligh", buffer, 4))
		{
			printf("light to temp\n");
			getMap(fp,&p,5);
			continue;
		}

		if(!strncmp("temp", buffer, 4))
		{
			printf("temp to humid\n");
			getMap(fp,&p,6);
			continue;
		}

		if(!strncmp("humi", buffer, 4))
		{
			printf("humi to location\n");
			getMap(fp,&p,7);
			continue;
		}
		buffer[0] = '\0';
	}

	for ( i = 0; i < numSeeds; i++)
	{
		num = seedsArray[i].num;
		mapCode* tmp = p.stosoil;

		for (;tmp != NULL; tmp = tmp->next)
		{
			if(num >= tmp->source && num <= (tmp->source + tmp->range))
			{
				num = tmp->dest + (num - tmp->source);
				seedsArray[i].num = num;
				break;
			}
		}
		tmp = p.stofertelizer;
		for (;tmp != NULL; tmp = tmp->next)
		{
			if(num >= tmp->source && num <= (tmp->source + tmp->range))
			{
				num = tmp->dest + (num - tmp->source);
				seedsArray[i].num = num;
				break;
			}
		}
		tmp = p.ftowater;
				for (;tmp != NULL; tmp = tmp->next)
		{
			if(num >= tmp->source && num <= (tmp->source + tmp->range))
			{
				num = tmp->dest + (num - tmp->source);
				seedsArray[i].num = num;
				break;
			}
		}
		tmp = p.wtolight;
				for (;tmp != NULL; tmp = tmp->next)
		{
			if(num >= tmp->source && num <= (tmp->source + tmp->range))
			{
				num = tmp->dest + (num - tmp->source);
				seedsArray[i].num = num;
				break;
			}
		}
		tmp = p.ltotemperature;
				for (;tmp != NULL; tmp = tmp->next)
		{
			if(num >= tmp->source && num <= (tmp->source + tmp->range))
			{
				num = tmp->dest + (num - tmp->source);
				seedsArray[i].num = num;
				break;
			}
		}
		tmp = p.ttohumidity;
				for (;tmp != NULL; tmp = tmp->next)
		{
			if(num >= tmp->source && num <= (tmp->source + tmp->range))
			{
				num = tmp->dest + (num - tmp->source);
				seedsArray[i].num = num;
				break;
			}
		}
		tmp = p.htolocation;
				for (;tmp != NULL; tmp = tmp->next)
		{
			if(num >= tmp->source && num <= (tmp->source + tmp->range))
			{
				num = tmp->dest + (num - tmp->source);
				seedsArray[i].num = num;
				break;
			}
		}
		printf("Seed [%i]: num %llu\n", i, seedsArray[i].num);
		if(least > seedsArray[i].num)
			least = seedsArray[i].num;	
	}
	
	printf("Minimum location: %llu\n",least);
	free(seedsArray);
	fclose(fp);
}