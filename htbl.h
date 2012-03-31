#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#ifndef _HTBL_H_
#define _HTBL_H_

typedef enum{false=0,true}bool;

typedef struct node
{
   struct node *link;
   int data;
}node;

typedef struct htbl
{
   node **table;
   unsigned int size;
   void(*freeHash)(struct htbl *hash);
   void(*add)(struct htbl *hash, int val);
   bool(*isPresent)(struct htbl *hash, int val);
}htbl;

htbl* initHash(unsigned int size);
node *new();
void add(htbl *hash, int val);
bool isPresent(htbl *hash, int val);
void freeHash(htbl *hash);

#endif
