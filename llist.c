//#include "heapsort.h"
#include"htbl.h"

#ifdef UNIT_TEST
typedef void (*fnptr) (node **, int, node*);
fnptr fn_arr[] = 
{
	insert_node,
	append_link_node,
	delete_node,
	print_nodes,
	free_link_nodes
};
#endif
/*******************************************************************
	\fn append_link_node(node**, int, node*)
	\brief - Append the node to the end of the list 
	\param head - list head
	\param data - Node data
	\param parent - node parent
	\return void
*******************************************************************/

void append_link_node(node **head, int data, node *parent)
{
	if(NULL == *head)
	{
		*head = new();
		(*head)->link[PREV] = parent;
		(*head)->link[NEXT] = NULL;
		(*head)->data = data;
	}
	else
	{
		append_link_node(&((*head)->link[NEXT]), data, *head);
	}
}

/*******************************************************************
	\fn print_nodes(node**, int, node*)
	\brief - print the nodes
	\param head - list head
	\param data - Node data
	\param parent - node parent
	\return void
*******************************************************************/
void print_nodes(node **head, int data, node *dontcare)
{
	node *iter = *head;
	while(iter != NULL)
	{
		printf("%d->", iter->data);
		iter = iter->link[NEXT];
	}
	printf("\n");
}

/*******************************************************************
	\fn free_link_nodes(node**, int, node*)
	\brief - Free all the nodes
	\param head - list head
	\param data - Node data
	\param parent - node parent
	\return void
*******************************************************************/
void free_link_nodes(node **head, int data, node *dontcare)
{
	node *iter = *head;
	node *mem;
	while(iter)
	{
		mem = iter->link[NEXT];
		free(iter);
		iter = mem;
	}
}

/*******************************************************************
	\fn insert_node(node**, int, node*)
	\brief - Handling inserting node in between, at the start or end of the list
	\param head - list head
	\param data - Node data
	\param parent - node parent
	\return void
*******************************************************************/
void insert_node(node **head, int data, node *dontcare)
{
	printf("Inserting data %d\n", data);
	node *iter = *head;
	node *prev = NULL;

	// trying to insert before list exists, this is
	// the first node.
	if(NULL == *head)
	{
		append_link_node(head, data, NULL);
		return;
	}


	// Check if we need to insert before head
	while(NULL != iter)
	{
		if(data < iter->data)
		{
			prev = iter;
			iter = iter->link[NEXT];
		}
		else
			break;
	}

	// This means we are at the end of the list.. re-acquire the last node
	if(NULL == iter)
	{
		iter = prev;
	}

	node *new_node = new();
	new_node->data = data;

	// Inserting before head, i.e this will be the new head
	if(NULL == iter->link[PREV])
	{
		new_node->link[PREV] = NULL;
		new_node->link[NEXT] = *head;
		(*head) = new_node; 
	}
	else
	{
		new_node->data = data;
		(iter->link[PREV])->link[NEXT] = new_node;
		new_node->link[PREV] = iter->link[PREV];
		new_node->link[NEXT] = iter;
		iter->link[PREV] = new_node;
	}
}

/*******************************************************************
	\fn delete_node(node**, int, node*)
	\brief - Handling deleting node in between, at the start or end of the list
	\param head - list head
	\param data - Node data
	\param parent - node parent
	\return void
*******************************************************************/
void delete_node(node **head, int data, node *dontcare)
{
	node *iter = *head;
	if(NULL == iter)
		return;

	// look for node
	while(iter)
	{
		if(iter->data != data)
			iter = iter->link[NEXT];
		else
			break;
	}

	// Modifying head.. edit *ptr value so caller sees the changed head
	if(NULL == iter->link[PREV])
	{
		// This is the head, make next node the head
		iter = *head;
		*head = (*head)->link[NEXT];
		(*head)->link[PREV] = NULL; //Since this is the new head, make prev=NULL
		free(iter);
		printf("Deleted %d, %d is now head\n", data, (*head)->data);
		return;
	}
	else
	{
		(iter->link[PREV])->link[NEXT] = iter->link[NEXT];
		printf("relaid out prev->next link to %p\n", iter->link[PREV]->link[NEXT]);
		if(NULL != iter->link[NEXT])
		{
			(iter->link[NEXT])->link[PREV] = iter->link[PREV];
		}
		printf("free'ing node %d\n", data);
		free(iter);
	}
}

#ifdef UNIT_TEST
int main()
{
	unsigned int opt = 0;
	int data = 0;

	node *head = NULL;

	while(1)
	{
		printf("Enter option: \
			\n1)Insert \
			\n2)Append \
			\n3)Delete \
			\n4)Print \
			\n5)Quit\n");
		scanf("%d", &opt);

      if(5 == opt)
         break;
		else if((5 < opt))
			continue;
      else if(4 != opt)
		{
			printf("Enter data:\n");
			scanf("%d",&data);
		}

		fn_arr[opt-1](&head, data, head);
	}
	return 0;
}
#endif
