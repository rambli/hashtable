#include "htbl.h"

/* PRIVATE FUNCTIONS */
static unsigned int hashfn(htbl *hash, int val)
{
   int hashIndex = 0;
   if(hash)
      hashIndex = val % hash->size;
   return hashIndex;
}

static void hinsert(node **head, int val)
{
   ll_append_link_node(head, val, *head);
}

static node* hremove(node **head)
{
   return(ll_get_node(head, 0, NULL));
}

unsigned int getOccupancy(htbl *hash)
{
   int i = 0;
   unsigned int count = 0;
   node **table = NULL;

   if(!hash)
      return 0;
   table = hash->table;
   for(i = 0; i < hash->size; i++)
   {
      if(table[i])
         count++;
   }
   return (count);
}

bool isOccupied(htbl *hash, int key)
{
   bool ret = FALSE;
   node **table = NULL;
   if(hash)
   {
      table = hash->table;
      if(table)
         if(table[hashfn(hash->size, key)])
            ret = TRUE;
   }
   return (ret);
}

node *new()
{
   node *n = (node*)malloc(sizeof(node));
   n->link[NEXT] = NULL;
   n->link[PREV] = NULL;
   n->data = 0;
   //printf("new node %p\n", n);
   return n;
}

void add(htbl *hash, int val)
{
   if(!hash)
      return;
   node **hashtable = hash->table;
   //printf("Adding to index %d\n", hashfn(hash, val));
   if(hashtable)
      hinsert(&hashtable[hashfn(hash, val)], val);
}

node* get(htbl *hash, int key)
{
   node *ret = NULL;
   if(!hash)
      return;
   node **table = hash->table;
   //printf("Retriving from index %d\n", hashfn(hash, key));
   if(table)
      ret = hremove(&table[hashfn(hash, key)]);
   return (ret);
}

bool isPresent(htbl *hash, int val)
{
   if(!hash)
      return;
   node **hashtable = hash->table;
   node *head = hashtable[hashfn(hash, val)];
   while(head)
   {
      if(head->data == val)
         return TRUE;
      head = head->link[NEXT];
   }
   return FALSE;
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
         next = table[i]->link[NEXT];
         free(table[i]);
         table[i] = next;   
      }
   }
   free(hash->table);
   free(hash);
   hash = NULL;
}
