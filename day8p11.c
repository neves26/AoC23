#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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


int assignIndexes(node* map, int count)
{
  int i = 0, j = 0, startIndex = 0;

  for ( i = 0; i < count; i++)
  {
    if (!strncmp(map[i].entry, "AAA", 3))
    {
      startIndex = i;
    }

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

  return startIndex;
}

int countInstructions(node* map, char rule[LENGTHRULE], int startIndex)
{
  int i = 0, sizeRule = strlen(rule);
  node currentNode = map[startIndex];
  int count = 0;
  printf("%d sizeRule\n", sizeRule);

  while (strncmp(currentNode.entry, "ZZZ", 3) != 0)
  {
    i = count % 269;
    
    if (rule[i] == 'L')
    {
      if (currentNode.leftIndex == -1)
      {
        fprintf(stderr, "Error: Wrong index\n");
        free(map);
        exit(3);
      }
      printf("%c", rule[i]);
      currentNode = map[currentNode.leftIndex];
      //printf("%s = (%s, %s)  || left %d right || %d\n", currentNode.entry, currentNode.left, currentNode.right, currentNode.leftIndex, currentNode.rightIndex );
    } else if(rule[i] == 'R')
    {
      if (currentNode.rightIndex == -1)
      {
        fprintf(stderr, "Error: Wrong index\n");
        free(map);
        exit(2);
      }
      printf("%c", rule[i]);
      currentNode = map[currentNode.rightIndex];
      //printf("%s = (%s, %s)  || left %d right || %d\n", currentNode.entry, currentNode.left, currentNode.right, currentNode.leftIndex, currentNode.rightIndex );
    } else
    {
      fprintf(stderr, "Error: Unintended behaviour\n");
      exit(1);
    }
    count++; i++;
    if(count > 22000)
    {
      fprintf(stderr, "Out of bound: %d\n", count);
      exit(11);
    }
  }
  
  return count;
}


int main(int argc, char** argv)
{
  int i = 0, startIndex = 0, count = 0;
  char buffer[LENGTHBUFFER];
  char rule[LENGTHRULE];
  node networkNode;
  FILE* fp = NULL;
  node* map;

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
  
  map = (node*) malloc(sizeof(node)*(count));
  if (map == NULL)
  {
    fprintf(stderr, "Error: Could not allocate memory for map vector\n");
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
    i++;
  }

/*  for (i = 0; i < count; i++)
  {
    printf("%s = (%s, %s)  || left %d right || %d\n", map[i].entry, map[i].left, map[i].right, map[i].leftIndex, map[i].rightIndex );
  } */
  startIndex = assignIndexes(map, count);

/* for (i = 0; i < count; i++)
{
  printf("[%d]: %s = (%s, %s)  || left %d right || %d\n", map[i].index, map[i].entry, map[i].left, map[i].right, map[i].leftIndex, map[i].rightIndex );
} */
  count = 0;

  count = countInstructions(map, rule, startIndex);

  free(map);
  printf("The number of instruction is %d\n", count);

  fclose(fp);

  return 0;
}