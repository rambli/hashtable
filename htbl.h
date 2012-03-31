#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#ifndef _HTBL_H_
#define _HTBL_H_

#define NUM_LINKS 2

/*! Macros for linked list nodes */
#define NEXT	1
#define PREV	0
typedef enum
{
   FALSE=0,
   TRUE
}bool;

typedef struct node
{
	/** The left and right children links: [Left child of parent x: [2x+1] Right child: [2x+2]
	    The next and previous nodes in the case of a linked list. */
	struct node *link[NUM_LINKS];
	/** When used as a node in a binary tree, parent of node x, one level up: [(x-1)/2] */
	struct node *parent;
	/** Node data */
	int data;
}node;
/*typedef struct node
{
   struct node *link;
   int data;
}node;
*/

typedef struct htbl
{
   node **table;
   unsigned int size;
   void(*freeHash)(struct htbl *hash);
   void(*add)(struct htbl *hash, int val);
   //node* (*get)(struct htbl *hash, int val);
   bool(*isPresent)(struct htbl *hash, int val);
   unsigned int(*getOccupancy)(struct htbl *hash);
}htbl;

htbl* initHash(unsigned int size);
node *new();
void add(htbl *hash, int val);
//node* get(htbl *hash, int val);
bool isPresent(htbl *hash, int val);
void freeHash(htbl *hash);
unsigned int getOccupancy(htbl *hash);

#endif
