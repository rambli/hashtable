// Author: Rohan Ambli

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"htbl.h"
#include<stdint.h>

#define UNIT_TEST

/* PUBLIC INTERFACE TO HASHTABLE */
htbl* initHash(unsigned int size)
{
   htbl *newHash = NULL;
   int i = 0;
   if(!size)
      return;
   size = (size > 10000)?10000:size;

   newHash = (htbl*)calloc(1,sizeof(htbl));
   if(newHash)
   {
      /* Populate entries when they are added to */
      newHash->table = (node**)calloc(size, sizeof(node*));
      newHash->size = size;
      newHash->freeHash = freeHash;
      newHash->add = add;
      newHash->get = get;
      newHash->isPresent = isPresent;
      newHash->getOccupancy = getOccupancy;
      newHash->isOccupied = isOccupied;
   }
   return (newHash);
}

#ifdef UNIT_TEST
typedef struct _a
{
   int b;
   int c;
}st_a;

int main()
{
   htbl *hash;
   hash = initHash(13);
   int i = 0;
   st_a *a1 = (st_a*)malloc(sizeof(st_a));
   a1->b = 5;
   a1->c = 32;

   for(i = 0; i < 4; i++)
   {
      a1->c++;
      hash->add(hash, i, (void*)a1);
   }
   hash->add(hash, 0, (void*)a1);
   hash->add(hash, 0, (void*)a1);
   hash->add(hash, 0, (void*)a1);
   hash->add(hash, 0, (void*)a1);
   printf("Population done, occupancy is %d\n", hash->getOccupancy(hash));
   
   void *v_ret = NULL;

   for(i = 0; i < 4; i++)
   {
      v_ret = hash->get(hash,i);
      while(v_ret)
      {
         printf("Got data %d\n----\n", ((st_a*)v_ret)->c);
         v_ret = hash->get(hash,i);
      }
      printf("Occupancy is %d\n", hash->getOccupancy(hash));
   }

   hash->freeHash(hash);
   hash = NULL;
   free(a1);
   return 0;
}
#endif // UNIT_TEST
