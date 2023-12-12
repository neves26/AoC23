#include <stdio.h>

int main(int argc, char** argv)
{
  FILE* fp = NULL;
  char buffer[100];
  int time[4] = {59, 70, 78, 78}, distance[4] = {430, 1218, 1213, 1276};
  int l = 0, sum = 1;

/*
  if(argc != 2)
  {
    fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
    return 1;
  }

  fopen(argv[1], "r");
  if (fp == NULL)
  {
    fprintf(stderr, "Error: File %d not found\n", argv[1]);
    return 1;
  }

  while (feof(fp) != 0)
  {
    fgets(buffer, 100, fp);

  }
  
  
  fclose(fp);
*/

  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; i < time[i]; j++)
    {
      if((j * (time[i] - j)) > distance[i])
      {
        l = j;
        break;
      }
    }
    sum *= (time[i] + 1) - (2 * l);
    printf("Time %d : Distance %d : Sum: %d\n", time[i], distance[i], sum);
  }
  


  return 0;
}