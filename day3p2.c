#include <stdio.h>
#include <math.h>
#include <string.h>
#define COL 140
#define ROW 140

int isNum(char num) 
{
    int flag = 0;

    if(num >= 48 && num <= 57)
        flag = 1;

    return flag;
}

int recNum(char mat[ROW][COL], int i, int j)
{
    int l = 0, r = 0, num = 0, c = 0, k = j;
    while (isNum(mat[i][k]))
    {
        l = k;
        if(k == 0)
            break;
        if(k>0)
            k--;
    }
    k = j;
    while (isNum(mat[i][k]))
    {
        r = k;
        if(k == COL)
            break;
        if(k<COL)
            k++;
    }

    for (; r >= l; r--, c++)
    {
        num += pow(10,c) * (mat[i][r]-48);
    }
    
    return num;
}

int getNum(char mat[ROW][COL], int i, int j, int* num)
{
    int valid = 0;
    int count = 0;

    if(i > 0 && j > 0) {
        if(isNum(mat[i-1][j-1])) {
            count++;
            *num *= recNum(mat, i-1, j-1);
        }
    }

    if (i > 0) {
        if(isNum(mat[i-1][j])) {
            if(j>0) {
                if(!isNum(mat[i-1][j-1])) {
                    count++;
                    *num *= recNum(mat, i-1, j);
                }
            }
        }
    }

    if(i > 0 && j < COL-1) {
        if(isNum(mat[i-1][j+1])) {
            if(!isNum(mat[i-1][j])) {
                count++;
                *num *= recNum(mat, i-1, j+1);
            }
        }
    }

    if(j > 0) {
        if(isNum(mat[i][j-1])) {
            count++;
            *num *= recNum(mat, i, j-1);
        }
    }

    if(j < COL-1) {
        if(isNum(mat[i][j+1])) {
            count++;
            *num *= recNum(mat, i, j+1);
        }
    }

    if(i < ROW-1 && j > 0) {
        if(isNum(mat[i+1][j-1])) {
            count++;
            *num *= recNum(mat, i+1, j-1);
        }
    }

    if(i < ROW-1) {
        if(isNum(mat[i+1][j])) {
            if(j > 0) {
                if(!isNum(mat[i+1][j-1])) {
                    count++;
                    *num *= recNum(mat, i+1, j);
                }
            }
        }
    }

    if(i < ROW-1 && j < COL-1) {
        if(isNum(mat[i+1][j+1])) {
            if(!isNum(mat[i+1][j])) {
                    count++;
                    *num *= recNum(mat, i+1, j+1);
                }
        }
    }

    if(count == 2) {
        valid = 1;
    }

    return valid;
}

int main(int argc, char** argv)
{
    int i = 0, j = 0;
    int num = 1;
    int sum = 0;
    char buffer[COL+2]; /* +2 cause its a string and needs extra for \0 and \n */
    char mat[ROW][COL];
    int valid = 0;
    FILE* fp = NULL;

    if(argc != 2)
    {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    fp = fopen(argv[1], "r");
    if(fp == NULL)
    {
        fprintf(stderr, "Error: File %s not found\n", argv[1]);
        return 1;
    }

    while (j < ROW)
    {   
        fgets(buffer, COL+2, fp); /* +2 cause its a string and needs extra for \0 and \n */
        for (i = 0; i < COL; i++)
            mat[j][i] = buffer[i];
        j++;
        buffer[0] = '\0';
    }


    for (i = 0; i < ROW; i++)
    { 
        for (j = 0; j < COL; j++)
        {
            if(mat[i][j] == '*')
            {
                valid = getNum(mat, i, j, &num);
                if(valid)
                {
                    sum += num;
                    //printf("num: %d     sum: %d\n",num, sum);
                }
            }
            num = 1;
        }
    }

    printf("\nPart 2 sum: %d\n\n", sum);

    fclose(fp);
    return 0;
}