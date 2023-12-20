#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#define COL 140
#define ROW 140

bool isNum(char character)
{
    return (character >= 48 && character <= 57)? true : false;
}

int getNum(char* str, int* i, int* n, int row, int map[ROW][COL])
{
    int c = *i;
    int tmp = 0;
    int d = 0;
    int sum = 0;
    int valid = 0;

    while (isNum(str[c]) && c < COL)
    {
        if(map[row][c] != 0)
            valid = 1;
        c++;
    }

    tmp = c;
    c--;
    d = c;

    for (; c >= *i; c--)
    {
        sum += pow(10,(d-c)) * (str[c] - 48);
    }
    
    *n = sum;
    *i = tmp;

    return valid;
}

void constructMap(int map[ROW][COL])
{
    int i = 0;
    int j = 0;

    for (i = 0; i < ROW; i++)
    {
        for (j = 0; j < COL; j++)
        {
            if(map[i][j] == 1) {
                if (i > 0) {
                    if(map[i-1][j] == 0)
                        map[i-1][j] = 2;
                }
                if(i < ROW-1) {
                    if(map[i+1][j] == 0)
                        map[i+1][j] = 2;
                }
                if(j > 0) {
                    if(map[i][j-1] == 0)
                        map[i][j-1] = 2;
                }
                if(j < COL-1) {
                    if(map[i][j+1] == 0)
                        map[i][j+1] = 2;
                }
                if(i > 0 && j > 0) {
                    if(map[i-1][j-1] == 0) 
                        map[i-1][j-1] = 2;
                }
                if(i > 0 && j < COL-1) {
                    if(map[i-1][j+1] == 0)
                        map[i-1][j+1] = 2;
                }
                if(i < ROW-1 && j > 0) {
                    if(map[i+1][j-1] == 0)
                        map[i+1][j-1] = 2;
                }
                if(i < ROW-1 && j < COL-1) {
                    if(map[i+1][j+1] == 0)
                        map[i+1][j+1] = 2;
                }
            }
            else {
                continue;
            }
        }
    }
}

/*
    Creates a kind of bitmap where special characters are 1, and around the
    characters constructMap puts a 2 on there are dots only. When rereading
    the file if the number is on top of a 2, thats a number to add to the sum.
    Otherwise skip it.

*/

int main(void)
{
    int i = 0, j = 0;
    int num = 0;
    int sum = 0;
    char buffer[COL+2]; /* +2 cause its a string and needs extra for \0 and \n */
    int map[ROW][COL];
    int valid = 0;
    FILE* fp = NULL;
    fp = fopen("day3.txt", "r");

    while (j < ROW)
    {   
        fgets(buffer, COL+2, fp); /* +2 cause its a string and needs extra for \0 and \n */

        for (i = 0; i < COL; i++)
        {
            if(!isNum(buffer[i]) && buffer[i] != '.')
                map[j][i] = 1;
            else
                map[j][i] = 0;
        }
        j++;
    }

    constructMap(map);
    fclose(fp);
    fp = fopen("day3.txt", "r");
    j = 0;

    while (j < ROW)
    {
        fgets(buffer,COL+2,fp); /* +2 cause its a string and needs extra for \0 and \n */ 

        for (i = 0; i < COL; i++)
        {
            if(isNum(buffer[i])) 
            {
                valid = getNum(buffer, &i, &num, j, map);
                if(valid)
                {
                    sum += num;
                }
            }
        }
        j++;
    }

    printf("Sum of all the part numbers: %d\n", sum);

    fclose(fp);
    return 0;
}