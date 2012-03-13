#include<stdio.h>
#include<stdlib.h>

#define SIZE 13

typedef enum{false=0,true}bool;

typedef struct node
{
   struct node *link;
   int data;
}node;

node *hashtbl[SIZE];

node *new()
{
   node *n = (node*)malloc(sizeof(node));
   n->link = NULL;
   n->data = 0;
   //printf("new node %p\n", n);
   return n;
}

void inithash(node ***table)
{
   int i = 0;
   *table = (node**)malloc(sizeof(node*) * SIZE);
   for(i = 0; i < SIZE; i++)
   {
      (*table)[i] = new();
      (*table)[i]->data = i;
      //printf("Added %p\n", (*table)[i]);
   }
}

void freehash(node **table)
{
   int i = 0;
   node *next;
   for(i = 0; i < SIZE; i++)
   {
      while(table[i])
      {
         next = table[i]->link;
         free(table[i]);
         table[i] = next;   
      }
   }
   free(table);
}

int hashfn(int val)
{
   return (val % SIZE);
}

void hinsert(node *head, int val)
{
   node *prev = NULL;
   while(NULL != head)
   {
      prev = head;
      printf("%d->", head->data);
      head = head->link;
   }
   printf("\n");
   head = new();
   head->data = val;
   if(NULL != prev)
      prev->link = head;
}

void add(node **table, int val)
{
   hinsert(table[hashfn(val)], val);
}


bool ispresent(node **hashtable, int val)
{
   node *head = hashtable[hashfn(val)];
   while(head)
   {
      //printf("Current %d\n", head->data);
      if(head->data == val)
         return true;
      head = head->link;
   }
   return false;
}

int main()
{
   node **hashtable;
   inithash(&hashtable);
   int i = 0;
   for(i = 0; i < 52; i++)
   {
      add(hashtable, rand());
   }
   for(i = 0; i < 500; i++)
   {
      int j = rand();
      if(ispresent(hashtable, j))
         printf("%d is present\n", j);
//      else
         //printf("%d is not present\n", j);
   }

   freehash(hashtable);
   return 0;
}
