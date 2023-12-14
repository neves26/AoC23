#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define CARDNUMBER 13
#define TYPENUMBER 7

// enum cards {A, K, Q, J, T, nine, eight, seven, six, five, four, three, two};

typedef struct node
{
  char hand[6];
  int bid;
  int cardMatchingCount[CARDNUMBER];       // 0 -> A, 1 -> K, 2 -> Q, ...
  int handTypeCount[TYPENUMBER];  // get # of matching cards
  int handType;                       // 0 -> 5 of a kind, 1 -> 4 of a kind, ...
  struct node* next;
} node;

typedef struct type
{
  int nodeCount;
  node* head;
} type;

bool isNum(char character)
{
  return (character >= 48 && character <= 57)? true : false;
}

void getHandType(node* aux)
{
  int i = 0;

  for (i = 0; i < 5; i++)
  {
    switch (aux->hand[i])
    {
    case 'A':
      aux->cardMatchingCount[0]++;
      break;
    case 'K':
      aux->cardMatchingCount[1]++;
      break;
    case 'Q':
      aux->cardMatchingCount[2]++;
      break;
    case 'J':
      aux->cardMatchingCount[3]++;
      break;
    case 'T':
      aux->cardMatchingCount[4]++;
      break;
    case '9':
      aux->cardMatchingCount[5]++;
      break;
    case '8':
      aux->cardMatchingCount[6]++;
      break;
    case '7':
      aux->cardMatchingCount[7]++;
      break;
    case '6':
      aux->cardMatchingCount[8]++;
      break;
    case '5':
      aux->cardMatchingCount[9]++;
      break;
    case '4':
      aux->cardMatchingCount[10]++;
      break;
    case '3':
      aux->cardMatchingCount[11]++;
      break;
    case '2':
      aux->cardMatchingCount[12]++;
      break;
    default:
      break;
    }
  }
  
  for (i = 0; i < CARDNUMBER; i++)
  {
    switch (aux->cardMatchingCount[i])
    {
    case 5:
      aux->handTypeCount[0]++;
      aux->handType = 0;
      return;
    case 4:
      aux->handTypeCount[1]++;
      aux->handType = 1;
      return;
    case 3:
      aux->handTypeCount[3]++;
      break;
    case 2:
      aux->handTypeCount[5]++;
      break;
    default:
      break;
    }
  }
  
  if( (aux->handTypeCount[3] == 1) && (aux->handTypeCount[5] == 1) )
  {
    aux->handType = 2;
  } else if( (aux->handTypeCount[3] == 1) && (aux->handTypeCount[5] == 0) )
  {
    aux->handType = 3;
  } else if(aux->handTypeCount[5] == 2)
  {
    aux->handType = 4;
  } else if( (aux->handTypeCount[3] == 0) && (aux->handTypeCount[5] == 1))
  {
    aux->handType = 5;
  } else
  {
    aux->handType = 6;
  }
}

node* getHandNode(char buffer[30])
{
  node *aux = NULL;
  char hand[6]; 
  int bid = 0;

  sscanf(buffer, "%s %d\n", hand, &bid);
  aux = (node*) malloc(sizeof(node) * 1);
  if(aux == NULL)
  {
    fprintf(stderr, "Error: couldn't allocate memory for node\n");
    exit(1);
  }

  strncpy(aux->hand, hand, 6);
  aux->bid = bid;
  aux->handType = -1;
  aux->next = (node*) NULL;
  for (int i = 0; i < CARDNUMBER; i++)
  {
    aux->cardMatchingCount[i] = 0;
    if (i < TYPENUMBER)
    {
      aux->handTypeCount[i] = 0;
    }
  }
  

  return aux;
}

void insertNode(type arrayTypes[TYPENUMBER], node* aux)
{
  node *tmp = arrayTypes[aux->handType].head;
  if (tmp == (node*) NULL)
  {
    tmp = aux;
    arrayTypes[aux->handType].nodeCount++;
    return;
  }
  
  for ( ; tmp->next != NULL ; tmp = tmp->next);
  tmp->next = aux;
  arrayTypes[aux->handType].nodeCount++;  
  return;
}

int assignCardValue(char character)
{
  int cardValue = -1;

  if(isNum(character))
  {
    cardValue = 14 - (character - 48);
  } else
  {
    switch (character)
    {
    case 'A':
      cardValue = 0;
      break;
    case 'K':
      cardValue = 1;
      break;
    case 'Q':
      cardValue = 2;
      break;
    case 'J':
      cardValue = 3;
      break;
    case 'T':
      cardValue = 4;
      break;
    default:
      break;
    }
  }

  return cardValue;
}

bool compareHandSameType(node* current, node* new)
{
  int valueCurrent = 99, valueNew = 99;
  bool newHigher = false;

  for (int i = 0; i < 5 && valueCurrent == valueNew; i++)
  {
    valueCurrent = assignCardValue(current->hand[i]);
    valueNew = assignCardValue(new->hand[i]);
  }

  newHigher = (valueNew < valueCurrent)? true : false;

  return newHigher;
}

void insertNodeOrdered(type arrayTypes[TYPENUMBER], node* aux)
{
  node *tmp = arrayTypes[aux->handType].head;
  node * previous = NULL;
  arrayTypes[aux->handType].nodeCount++;

  if (tmp == (node*) NULL)
  {
    arrayTypes[aux->handType].head = aux;
    return;
  }

  if(compareHandSameType(tmp, aux))
  {
    //printf("Hand %s higher than hand %s\n", aux->hand, tmp->hand);
    arrayTypes[aux->handType].head = aux;
    aux->next = tmp;
    return;
  }
  
  for (previous = tmp, tmp = tmp->next; tmp != NULL; previous = tmp, tmp = tmp->next)
  {
    if(compareHandSameType(tmp, aux)) // true if aux higher
    {
      //printf("Hand %s higher than hand %s\n", aux->hand, tmp->hand);
      aux->next = tmp;
      previous->next = aux;
      return;
    }
  }

  previous->next = aux;

  return;
}

void freeList(node* head) {
  node* current = head, *tmp = NULL;

  if(current == NULL)
  {
    return;
  }

  for ( ; current != NULL; )
  {
    //printf("freeing node %s\n", current->hand);
    tmp = current;
    current = current->next;
    free(tmp);
  }

  return;
}

int main(int argc, char** argv)
{
  int i = 0, j = 0, totalWinnings = 0;
  char buffer[30];
  FILE* fp = NULL;
  node* aux;
  type arrayTypes[TYPENUMBER];

  if (argc != 2)
  {
    fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
    return 1;
  }

  fp = fopen(argv[1], "r");
  if (fp == NULL)
  {
    fprintf(stderr, "Error: File %s not found\n", argv[1]);
    return 1;
  }

  for(i = 0; i < TYPENUMBER; i++)
  {
    arrayTypes[i].nodeCount = 0;
    arrayTypes[i].head = (node*) NULL;
  }

  while (feof(fp) == 0)
  {
    fgets(buffer, 30, fp);
    aux = (node*) getHandNode(buffer);
    getHandType(aux);
    //printf("Hand: %s  ||  Bid: %d   || Hand type: %d\n", aux->hand, aux->bid, aux->handType);
    insertNodeOrdered(arrayTypes, aux);
  }

  for (i = 0; i < TYPENUMBER; i++)
  {
    j += arrayTypes[i].nodeCount;
  }
  
  for(i = 0; i < TYPENUMBER; i++)
  {
    //printf("Type[%d] count: %d\n", i, arrayTypes[i].nodeCount);
    for (aux = arrayTypes[i].head; aux != NULL; aux = aux->next)
    {
      //printf("Hand %s with bid %d\n", aux->hand, aux->bid);
      totalWinnings += aux->bid * j;
      //printf("%d * %d  || Total Winnings: %d\n", aux->bid, j, totalWinnings);
      j--;
    }
    
    freeList(arrayTypes[i].head);
  }

  printf("Total Winnings: %d\n", totalWinnings);

  fclose(fp);
  return 1;
}