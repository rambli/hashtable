#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"htbl.h"

/* PUBLIC INTERFACE TO HASHTABLE */
htbl* initHash(unsigned int size)
{
   htbl *newHash = NULL;
   int i = 0;
   if(!size)
      return;
   size = (size > 10000)?10000:size;

   newHash = (htbl*)malloc(sizeof(htbl));
   if(newHash)
   {
      newHash->table = (node**)malloc(sizeof(node*) * size);
      newHash->size = size;
      newHash->freeHash = freeHash;
      newHash->add = add;
      newHash->get = get;
      newHash->isPresent = isPresent;
      newHash->getOccupancy = getOccupancy;
      newHash->isOccupied = isOccupied;
      /* Populate entries when they are added to */
      for(i = 0; i < size; i++)
      {
         newHash->table[i] = NULL;
      }
   }
   return (newHash);
}

int main()
{
   htbl *hash;
   hash = initHash(13);
   int i = 0;
   for(i = 0; i < 4; i++)
   {
      hash->add(hash, 2);//rand());
   }
   printf("Occupancy is %d\n", hash->getOccupancy(hash));
   
#if 1
   node *ret = hash->get(hash, 2);
   printf("Got node %p\n", ret);
   //free(ret);

   ret = hash->get(hash, 2);
   printf("Got node %p\n", ret);
   //free(ret);
   ret = hash->get(hash, 2);
   printf("Occupancy is %d\n", hash->getOccupancy(hash));
   printf("Got node %p\n", ret);
   //free(ret);
   ret = hash->get(hash, 5);
   printf("Got node %p\n", ret);
   printf("Occupancy is %d\n", hash->getOccupancy(hash));
   //free(ret);
#endif   
   /*
   for(i = 0; i < 500; i++)
   {
      int j = rand();
      if(ispresent(hash, j))
         printf("%d is present\n", j);
//      else
         //printf("%d is not present\n", j);
   }*/

   hash->freeHash(hash);
   return 0;
}
