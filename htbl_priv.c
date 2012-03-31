#include "htbl.h"

/* PRIVATE FUNCTIONS */
static int hashfn(htbl *hash, int val)
{
   int hashIndex = 0;
   if(hash)
      hashIndex = val % hash->size;
   return hashIndex;
}

static void hinsert(node **head, int val)
{
   node *prev = NULL;
   if(!head)
      return;
   if(!(*head))
   {
      *head = new();
      printf("Occupying new cell with %p\n", *head);
      (*head)->data = val;
      (*head)->link  = NULL;
   }
   else
   {
      /* This is a collision, traverse and add to the end */
      node *tmp = *head;
      while(NULL != tmp)
      {
         prev = tmp;
         printf("%d->", tmp->data);
         tmp = tmp->link;
      }
      tmp = new();
      tmp->data = val;
      printf("%d->", tmp->data);
      printf("\n");
      if(NULL != prev)
         prev->link = tmp;
   }
}
#if 0
static node* hremove(node **head)
{
   node *ret = NULL;
   node *prev = NULL;

   if(!head)
      return;
   
   if(!(*head))
   {
      printf("Nothing to return\n");
   }
   else
   {
      if(!((*head)->link))
      {
         /* Removing first node, set it to NULL after getting the value */
         ret = *head;
         *head = NULL;
      }
      else
      {
         /* Traverse to the end and return the last one */
         node *tmp = *head;
         node *prev = tmp;
         while(NULL != tmp)
         {
            ret = tmp;
            tmp = tmp->link;
         }
         printf("Returning %d\n", ret->data);
         if(prev)
         /* We are returning this node, set the previous
          * node's link ptr to NULL. Caller should free returned node.
          */
      }
   }
   return (ret);
}
#endif
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
   printf("Adding to index %d\n", hashfn(hash, val));
   if(hashtable)
      hinsert(&hashtable[hashfn(hash, val)], val);
}

#if 0
node* get(htbl *hash, int key)
{
   node *ret = NULL;
   if(!hash)
      return;
   node **table = hash->table;
   printf("Retriving from index %d\n", hashfn(hash, key));
   if(table)
      ret = hremove(&table[hashfn(hash, key)]);
   return (ret);
}
#endif

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
   hash = NULL;
}
