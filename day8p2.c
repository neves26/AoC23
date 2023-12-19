#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define LENGTHBUFFER 30
#define LENGTHRULE 400

typedef struct node {
  char entry[4];
  char left[4];
  char right[4];
  int index;
  int leftIndex;
  int rightIndex;
} node;

long int gcd(long int x, long int y)
{
  while (x != y)
  {
    if (x > y)
    {
      x = x - y;
    } 
    else
    {
      y = y - x;
    }
  }

  return x;
}

void assignIndexes(node* map, int count)
{
  int i = 0, j = 0;

  for ( i = 0; i < count; i++)
  {
    for ( j = 0; j < count; j++)
    {
      if (!strncmp(map[j].entry,map[i].left, 3))
      {
        map[i].leftIndex = j;
      }

      if (!strncmp(map[j].entry,map[i].right, 3))
      {
        map[i].rightIndex = j;
      }
      
    }
  }
  return;
}

void countInstructions(node* map, char rule[LENGTHRULE], int* paths, int pathsCount, int* pathsCountCycle)
{
  bool flagAllMissZ = true, flagAllHasZ = true, flagEnoughCycles = false;
  int i = 0, sizeRule = strlen(rule), j = 0, cycle = 0;
  node currentNode;
  long int count = 0;
  
  printf("Number of paths: %d\n", pathsCount);

  for ( j = 0; j < pathsCount; j++)
  {
    i = 0; count = 0; cycle = 0; flagEnoughCycles = false;
  
  while (!flagEnoughCycles)
  {
    currentNode = map[paths[j]];
    //printf("Node %s\n", currentNode.entry);
    i = count % 269;
      
    if (rule[i] == 'L')
    {
      if (currentNode.leftIndex == -1)
      {
        fprintf(stderr, "Error: Wrong index\n");
        free(map);
        exit(3);
      }
      //printf("%c", rule[i]);
      paths[j] = map[currentNode.leftIndex].index;
      
      //printf("%s = (%s, %s)  || left %d right || %d\n", currentNode.entry, currentNode.left, currentNode.right, currentNode.leftIndex, currentNode.rightIndex );
    } else if(rule[i] == 'R')
    {
      if (currentNode.rightIndex == -1)
      {
        fprintf(stderr, "Error: Wrong index\n");
        free(map);
        exit(2);
      }
      //printf("%c", rule[i]);
      paths[j] = map[currentNode.rightIndex].index;

      //printf("%s = (%s, %s)  || left %d right || %d\n", currentNode.entry, currentNode.left, currentNode.right, currentNode.leftIndex, currentNode.rightIndex );
    } else
    {
      fprintf(stderr, "Error: Unintended behaviour\n");
      exit(1);
    }

    count++;
    
    if(map[paths[j]].entry[2] == 'Z' )
    {
      cycle++;
      printf("Count %lld\n", count);
      pathsCountCycle[j] = count;

      if (cycle == 1)
      {
        flagEnoughCycles = true;
      }
    }

    i++;
  }
  }

  return;
}


int main(int argc, char** argv)
{
  int i = 0, pathsCount = 0;
  long int count = 0;
  char buffer[LENGTHBUFFER];
  char rule[LENGTHRULE];
  node networkNode;
  FILE* fp = NULL;
  node* map;
  int* paths, *pathsCountCycle;

  if (argc != 2)
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

  fgets(rule, LENGTHRULE, fp);
  fgets(buffer, LENGTHBUFFER, fp);
  //printf("Rule: %s\n", rule);
  
  while(feof(fp) == 0)
  {
    fgets(buffer, LENGTHBUFFER, fp);
    count++;
    //printf("|||COunt %d|||\n", count);
  }
  fclose(fp);
  
  map = (node*) malloc(sizeof(node) * count);
  paths = (int*) malloc(sizeof(int) * count);
  pathsCountCycle = (int*) malloc(sizeof(int) * count);
  if (map == NULL)
  {
    fprintf(stderr, "Error: Could not allocate memory for map vector\n");
    return 1;
  }

  for (i = 0; i < count; i++)
  {
    paths[i] = -1;
    pathsCountCycle[i] = -1;
  }
  i=0;
  

  fp = fopen(argv[1], "r");

  if(fp == NULL)
  {
    fprintf(stderr, "Error: File %s not found\n", argv[1]);
    return 1;
  }

  fgets(rule, LENGTHRULE, fp);
  fgets(buffer, LENGTHBUFFER, fp);
  //printf("Rule: %s\n", rule);
  
  while(feof(fp) == 0)
  {
    if (i == count)
    {
      break;
    }
    
    fscanf(fp, "%s = (%s %s)", networkNode.entry, networkNode.left, networkNode.right);
    networkNode.left[3] = '\0'; networkNode.right[3] = '\0'; networkNode.entry[3] = '\0';
    strncpy( map[i].entry, networkNode.entry, 4);
    strncpy( map[i].left, networkNode.left, 4);
    strncpy( map[i].right, networkNode.right, 4);
    map[i].leftIndex = -1; map[i].rightIndex = -1;
    map[i].index = i;

    if (map[i].entry[2] == 'A')
    {
      paths[pathsCount] = i;
      pathsCount++;
    }    
    i++;
  }

/*  for (i = 0; i < count; i++)
  {
    printf("%s = (%s, %s)  || left %d right || %d\n", map[i].entry, map[i].left, map[i].right, map[i].leftIndex, map[i].rightIndex );
  } */
  assignIndexes(map, count);

/* for (i = 0; i < count; i++)
{
  printf("[%d]: %s = (%s, %s)  || left %d right || %d\n", map[i].index, map[i].entry, map[i].left, map[i].right, map[i].leftIndex, map[i].rightIndex );
} */

  countInstructions(map, rule, paths, pathsCount, pathsCountCycle);
  
  count = pathsCountCycle[0];
  for (size_t i = 1; i < pathsCount; i++)
  {
    count = (pathsCountCycle[i] * count) / gcd(pathsCountCycle[i],count);
  }
  free(map);
  free(paths);
  free(pathsCountCycle);
  printf("The number of instruction is %ld\n", count);

  fclose(fp);

  return 0;
}