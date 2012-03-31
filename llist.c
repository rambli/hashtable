//#include "heapsort.h"
#include"htbl.h"

#ifdef UNIT_TEST
typedef void (*fnptr) (node **, int, node*);
fnptr fn_arr[] = 
{
	ll_insert_node,
	ll_append_link_node,
	ll_delete_node,
	ll_print_nodes,
	ll_free_link_nodes
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

void ll_append_link_node(node **head, int data, node *parent)
{
	if(NULL == *head)
	{
		*head = new();
      //printf("Appending new node %p <next:%p prev:%p>\n", *head, NULL, parent);
      (*head)->link[PREV] = parent;
		(*head)->link[NEXT] = NULL;
		(*head)->data = data;
	}
	else
	{
		ll_append_link_node(&((*head)->link[NEXT]), data, *head);
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
void ll_print_nodes(node **head, int data, node *dontcare)
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
void ll_free_link_nodes(node **head, int data, node *dontcare)
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
void ll_insert_node(node **head, int data, node *dontcare)
{
	printf("Inserting data %d\n", data);
	node *iter = *head;
	node *prev = NULL;

	// trying to insert before list exists, this is
	// the first node.
	if(NULL == *head)
	{
		ll_append_link_node(head, data, NULL);
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
	\fn get_node(node**, int, node*)
	\brief - Remove and return node from the end of the list, user should free 
            returned node
	\param head - list head
	\param data - Node data
	\param parent - node parent
	\return node * - returned node
*******************************************************************/
node* ll_get_node(node **head, int data, node *dontcare)
{
   node *ret =  NULL;
   node *curr = NULL;

	node *iter = *head;
	if(NULL == iter)
   {
      //printf("List is NULL, nothing to return\n");
		return ret;
   }

	// Traverse to the end of the list
	while(iter)
	{
      curr = iter;
		iter = iter->link[NEXT];
	}
   // Reached last node, return it
   ret = curr;

	if(NULL == curr->link[PREV])
	{
      //printf("This is the head node, setting it to NULL\n");
      // If last node is head, set *head to NULL so caller knows about it
      *head = NULL;
	}
	else
	{
      // Not the last node, set prev's next to NULL so curr is no longer accessible
      // from current list. Caller should free curr
		(curr->link[PREV])->link[NEXT] = NULL;
		//printf("relaid out prev(%p)->next link to %p\n", curr->link[PREV],curr->link[PREV]->link[NEXT]);
   }
   return (ret);
}

/*******************************************************************
	\fn delete_node(node**, int, node*)
	\brief - Handling deleting node in between, at the start or end of the list
	\param head - list head
	\param data - Node data
	\param parent - node parent
	\return void
*******************************************************************/
void ll_delete_node(node **head, int data, node *dontcare)
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
