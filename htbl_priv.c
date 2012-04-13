#include "htbl.h"

/* PRIVATE FUNCTIONS */
static unsigned int hashfn(htbl *hash, int val)
{
   int hashIndex = 0;
   if(hash)
      hashIndex = val % hash->size;
   return hashIndex;
}

static void hinsert(node **head, void *data)
{
   ll_append_link_node(head, data, *head);
}

void * hremove(node **head)
{
   node *n = NULL;
   ll_get_node(head, NULL, &n);
   return(n);
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
   bool ret = TRUE;
   node **table = NULL;
   if(hash)
   {
      table = hash->table;
      if(table)
         if(NULL == table[hashfn(hash, key)])
            ret = FALSE;
   }
   return (ret);
}

node *new()
{
   node *n = (node*)malloc(sizeof(node));
   n->link[NEXT] = NULL;
   n->link[PREV] = NULL;
   n->key = 0;
   n->data = NULL;
   return (n);
}

bool add(htbl *hash, int key, void *data)
{
   bool ret = TRUE;
   if(!hash)
      return;
   node **hashtable = hash->table;
   if(hashtable)
   {
      /* Don't add if collisions are not allowed and slot is 
       * already occupied */
      if(!hash->allowColl && hash->isOccupied(hash, key))
         ret = FALSE;
      else
         hinsert(&hashtable[hashfn(hash, key)], data);
   }
   return (ret);
}

void* get(htbl *hash, int key)
{
   void *ret = NULL;
   if(!hash)
      return;
   node **table = hash->table;
   if(table)
      ret = hremove(&table[hashfn(hash, key)]);
   return (ret);
}

bool isPresent(htbl *hash, int key)
{
   if(!hash)
      return;
   node **hashtable = hash->table;
   node *head = hashtable[hashfn(hash, key)];
   while(head)
   {
      if(head->key == key)
         return TRUE;
      head = head->link[NEXT];
   }
   return (FALSE);
}

void setAllowCollisionValue(htbl *hash, bool allow)
{
   if(!hash)
      return;
   hash->allowColl = allow;
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
         table[i] = NULL;
         table[i] = next;   
      }
   }
   free(hash->table);
   hash->table = NULL;
   free(hash);
   hash = NULL;
}
