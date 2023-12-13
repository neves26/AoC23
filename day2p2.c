#include <stdio.h>
#include <stdbool.h>

bool isNum(char x)
{
	return (x >= 48 && x <= 57)? true : false;
}

int main(int argc, char** argv) {
	int r = 0, g = 0, b = 0;
	int i = 0;
	int idGame = -1;
	int sum = 0;
	char buffer[200];
	int num = 0;
	int power = 1;
	FILE* fp = NULL;


	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
		return 1;
	}
	
	fp = fopen(argv[1], "r");
	if(fp == NULL) {
		fprintf(stderr, "Error: File %s not found\n", argv[1]);
		return 1;
	}

	while(feof(fp) ==	 0) {
		r = 0; g = 0; b = 0;
		fgets(buffer,200,fp);
		if(buffer[0] != 'G') {
			break;
		}
		sscanf(buffer, "Game %d:", &idGame);

		for (i = 0; buffer[i] != '\n' ; i++) {
			if ( isNum(buffer[i]) ) {
				if ( isNum(buffer[i+1]) ) {
					num = (buffer[i] - 48) * 10 + (buffer[i+1]-48);
					i++;
					
					if(buffer[i+2] == 'r') {
						if(num > r) {
							r = num;
							continue;
						}
					}
				
					if(buffer[i+2] == 'g') {
						if(num > g) {
							g = num;
							continue;
						}
					}

					if(buffer[i+2] == 'b') {
						if(num > b) {
							b = num;
							continue;
						}
					}
				}
				
				if(buffer[i+2] == 'r') {
					if(buffer[i] - 48 > r) {
						r = buffer[i] - 48;
						continue;
					}
				}
				if(buffer[i+2] == 'g') {
					if(buffer[i] - 48 > g) {
						g = buffer[i] - 48;
						continue;
					}
				}
				if(buffer[i+2] == 'b') {
					if(buffer[i] - 48 > b) {
						b = buffer[i] - 48;
						continue;
					}
				}
			}
		}

		power = r * g * b;
		sum += power;
	}

	printf("Soma: %d\n", sum);

	return 0;
}
