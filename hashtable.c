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
      newHash->isPresent = isPresent;
      for(i = 0; i < size; i++)
      {
         newHash->table[i] = new();
         newHash->table[i]->data = i;
         //printf("Added %p\n", (*table)[i]);
      }
   }
   return (newHash);
}

int main()
{
   htbl *hash;
   hash = initHash(13);
   int i = 0;
   for(i = 0; i < 24; i++)
   {
   //   printf("Add %d\n", i+50);
      hash->add(hash, i+50);//rand());
   }
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
