#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>

int ctoi(char x) {
	return x-48;
}

void compare(char* s1, char* s2, int n, int* l, int* r) {
	int x = strncmp(s1, s2, strlen(s2));
	if(x != 0) /*no match*/
		return;

	if (*l == -1)
		*l = n;
	else
		*r = n;
	return;
} 


int main(void) {

	/*
	 *	1. get var to hold sum
	 *	2. get var to hold 1st and last digit
	 *	3. read line
	 *	4. read digit values
	 *	5. add to sum var
	 *	6. return sum value
	 *
	 */

	int i, sum = 0, l = -1, r = -1;
	char str[200];
	FILE* fp = NULL;

	fp = fopen("day1.txt", "r");
	if(fp == NULL) {
		printf("no file\n");
		return 1;
	}

	while(feof(fp) == 0) {
		l = -1; r = -1;
		fgets(str,200,fp);
		for(i = 0; str[i]!='\0';i++) {
		
			switch(str[i]) {	
				case 'o':
					compare(&str[i], "one", 1, &l, &r );
					break;

				case 't':
					compare(&str[i], "two", 2, &l, &r );
					compare(&str[i], "three", 3, &l, &r );
					break;
          
				case 'f':
					compare(&str[i], "four", 4, &l, &r );
					compare(&str[i], "five", 5, &l, &r );
					break;
  
				case 's':
					compare(&str[i], "six", 6, &l, &r );
					compare(&str[i], "seven", 7, &l, &r );
					break;

				case 'e':
					compare(&str[i], "eight", 8, &l, &r );
					break;
				
				case 'n':
					compare(&str[i], "nine", 9, &l, &r );
					break;
			}
			
			if(str[i]>= 48 && str[i] <= 57) {
				if(l == -1)
					l = ctoi(str[i]);
				else
					r = ctoi(str[i]);
			}

		}
		
		if(r == -1)
			r = l;
		printf("number: %d%d\n", l, r);
		sum += (l*10) + r;
	}

	printf("final sum: %d\n", sum);
	return 0;
}
