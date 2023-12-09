#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int ctoi(char x)
{
	return x-48;
}

bool isNum(char x)
{
	return (x >= 48 && x <= 57 )? true : false;
}

/*
while not end of file
	Get Line
	If no digits, continue to next line
	Get digit from left
	If no more digits, right equals left
	Else right equals rightmost digit
	Form the number, and add to variable sum
*/

int main(int argc, char** argv) {

	int i = 0, sum = 0, l = -1, r = -1;
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
		fscanf(fp, "%s", buffer);
		fgets(buffer, 200, fp);

		for(i = 0; buffer[i]!='\0'; i++) {
			if(isNum(buffer[i])) {
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
		l = -1, r = -1;
	}

	printf("Final sum: %d\n", sum);
	return 0;
}
