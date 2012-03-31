#include "htbl.h"

/* PRIVATE FUNCTIONS */
static int hashfn(htbl *hash, int val)
{
   int hashIndex = 0;
   if(hash)
      hashIndex = val % hash->size;
   return hashIndex;
}

static void hinsert(node *head, int val)
{
   node *prev = NULL;
   while(NULL != head)
   {
      prev = head;
      printf("%d->", head->data);
      head = head->link;
   }
   head = new();
   head->data = val;
   printf("%d->", head->data);
   printf("\n");
   if(NULL != prev)
      prev->link = head;
}

node *new()
{
   node *n = (node*)malloc(sizeof(node));
   n->link = NULL;
   n->data = 0;
   //printf("new node %p\n", n);
   return n;
}

void add(htbl *hash, int val)
{
   if(!hash)
      return;
   node **hashtable = hash->table;
   if(hashtable)
      hinsert(hashtable[hashfn(hash, val)], val);
}

bool isPresent(htbl *hash, int val)
{
   if(!hash)
      return;
   node **hashtable = hash->table;
   node *head = hashtable[hashfn(hash, val)];
   while(head)
   {
      //printf("Current %d\n", head->data);
      if(head->data == val)
         return true;
      head = head->link;
   }
   return false;
}

void freeHash(htbl *hash)
{
   int i = 0;
   node *next;
   node **table;

   if(!hash)
      return;
   table = hash->table;
   for(i = 0; i < hash->size; i++)
   {
      while(table[i])
      {
         next = table[i]->link;
         free(table[i]);
         table[i] = next;   
      }
   }
   free(hash->table);
   free(hash);
}
