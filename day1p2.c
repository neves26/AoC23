#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int ctoi(char x)
{
	return x-48;
}

bool isNum(char x)
{
	return (x >= 48 && x <= 57)? true : false;
}

void compare(char* s1, char* s2, int n, int* l, int* r)
{
	int x = strncmp(s1, s2, strlen(s2));
	if(x != 0) /*no match*/
		return;

	if (*l == -1)
		*l = n;
	else
		*r = n;
	return;
} 

/*
digits meaning either written or number
while not end of file
	Get Line
	If no digits, continue to next line
	Get digit from left
	If no more digits, right equals left
	Else right equals rightmost digit
	Form the number, and add to variable sum
*/

int main(int argc, char** argv)
{
	int i, sum = 0, l = -1, r = -1;
	char buffer[200];
	FILE* fp = NULL;

	if(argc != 2)
	{
		fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
		return 1;
	}

	fp = fopen(argv[1], "r");
	if(fp == NULL) {
		fprintf(stderr, "Error: File %s not found\n", argv[1]);
		return 1;
	}

	while(feof(fp) == 0) {
		l = -1; r = -1;
		fgets(buffer,200,fp);

		for(i = 0; buffer[i]!='\0';i++)
		{
			switch(buffer[i])
			{	
				case 'o':
					compare(&buffer[i], "one", 1, &l, &r );
					break;

				case 't':
					compare(&buffer[i], "two", 2, &l, &r );
					compare(&buffer[i], "three", 3, &l, &r );
					break;
          
				case 'f':
					compare(&buffer[i], "four", 4, &l, &r );
					compare(&buffer[i], "five", 5, &l, &r );
					break;
  
				case 's':
					compare(&buffer[i], "six", 6, &l, &r );
					compare(&buffer[i], "seven", 7, &l, &r );
					break;

				case 'e':
					compare(&buffer[i], "eight", 8, &l, &r );
					break;
				
				case 'n':
					compare(&buffer[i], "nine", 9, &l, &r );
					break;
			}
			
			if(isNum(buffer[i]))
			{
				if(l == -1)
					l = ctoi(buffer[i]);
				else
					r = ctoi(buffer[i]);
			}
		}

		if(l == -1)
			continue;
		if(r == -1)
			r = l;
		sum += (l*10) + r;
	}

	printf("Final sum: %d\n", sum);
	fclose(fp);
	
	return 0;
}
