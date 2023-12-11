#include <stdio.h>
#include <stdbool.h>

bool isNum(char x)
{
	return (x >= 48 && x <= 57)? true : false;
}

int main(int argc, char** argv) {
	int r = 12, g = 13, b = 14;
	int i = 0, idGame = -1, sum = 0, num = 0;
	char buffer[200];
	bool flag = true;
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
		fgets(buffer,200,fp);
		flag = true;

		if(buffer[0] != 'G') {
			break;
		}
		sscanf(buffer, "Game %d:", &idGame);

		for (i = 8; buffer[i] != '\n' ; i++) {
			num = 0;
			if (isNum(buffer[i])) {
				if (isNum(buffer[i+1])) {
					num = (buffer[i] - 48) * 10 + (buffer[i+1]-48);
					i++;
					
					if(buffer[i+2] == 'r') {
						if(num > r) {
							flag = false;
							continue;;
						}
					}
				
					if(buffer[i+2] == 'g') {
						if(num > g) {
							flag = false;
							continue;
						}
					}

					if(buffer[i+2] == 'b') {
						if(num > b) {
							flag = false;
							continue;
						}
					}
				}
				
				if(buffer[i+2] == 'r') {
					if(buffer[i] - 48 > r) {
						flag = false;
						continue;
					}
				}
				if(buffer[i+2] == 'g') {
					if(buffer[i] - 48 > g) {
						flag = false;
						continue;
					}
				}
				if(buffer[i+2] == 'b') {
					if(buffer[i] - 48 > b) {
						flag = false;
						continue;;
					}
				}
			}
		}

		if(flag)
		{
			sum += idGame;
		}
	}

	printf("Soma: %d\n", sum);
	
	fclose(fp);
	return 0;
}
