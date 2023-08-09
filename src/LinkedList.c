#include "LinkedList.h"
#include "string.h"
#include <stdio.h>
#include <stdlib.h>

// Declare the attributes for the structure node.
typedef struct t_Node
{
	Element data;
	struct t_Node* next;
}Node;

// Declare the attributes for the ADT generic structure linked list that save its data in node structure.
struct t_LinkedList
{
	Node* head;
	Node* tail;
	int size;
	CopyFunction copyFunc;
	FreeFunction freeFunc;
	PrintFunction printFunc;
	EqualFunction equalFuncSE;
	EqualFunction equalFuncDE;
};


// Function that creates a new linked list and initializes its attribute.
// copyf is a function that received a element and returns copy of it.
// freef is a function that received a element and frees the memory that allocated to it.
// printf is a function that received a element and prints it.
// equalFSE is a function that received 2 same type element and returns true if they are equal or false either.
// equalDSE is a function that received 2 different type element and returns true if one of them contained in the second or false either.
// The function return a a pointer to the linked list or null if an error occurred.
LinkedList createLinkedList(CopyFunction copyf, FreeFunction freef, PrintFunction printf, EqualFunction equalFSE, EqualFunction equalFDE)
{
	LinkedList linkedList = (LinkedList)malloc(sizeof(struct t_LinkedList));
	if (linkedList == NULL)
	{
		return NULL;
	}
	linkedList->head = NULL;
	linkedList->tail = NULL;
	linkedList->size = 0;
	linkedList->copyFunc = copyf;
	linkedList->freeFunc = freef;
	linkedList->printFunc = printf;
	linkedList->equalFuncSE = equalFSE;
	linkedList->equalFuncDE = equalFDE;
	return linkedList;
}

// Function that adds a new node to the linked list.
// lp is a pointer to linked list.
// data is the data that should be stored in a new node that is added to the linked list.
// The function returns a status if the operation succeed or failed.
status appendNode(LinkedList lp, Element data)
{
	if (lp == NULL || data == NULL)
	{
		return failure;
	}
	Node* newNode = (Node*)malloc(sizeof(Node));
	if (newNode == NULL)
	{
		return failure;
	}
	newNode->data = lp->copyFunc(data);
	newNode->next = NULL;
	if (lp->head == NULL && lp->tail == NULL)
	{
		lp->head = newNode;
		lp->tail = newNode;
	}
	else
	{
		lp->tail->next = newNode;
		lp->tail = newNode;
	}
	lp->size++;
	return success;
}

// Function that deletes a node from the linked list.
// lp is a pointer to linked list.
// data is the data that should be deleted from the linked list.
// The function returns a status if the operation succeed or failed.
status deleteNode(LinkedList lp, Element data)
{
	if (lp == NULL || data == NULL)
	{
		return failure;
	}
	Node* currentNode = lp->head;
	if (lp->size == 0)
	{
		return failure;
	}
	if (lp->head == lp->tail)
	{
		if (lp->equalFuncSE(currentNode->data, data) == true)
		{
			if (lp->freeFunc(currentNode->data) == success)
			{
				lp->size = 0;
				free(currentNode);
				lp->head = NULL;
				lp->tail = NULL;
				return success;
			}
		}
		return failure;
	}
	if (lp->equalFuncSE(currentNode->data, data) == true)
	{
		if (lp->freeFunc(currentNode->data) == success)
		{
			lp->size--;
			lp->head = currentNode->next;
			free(currentNode);
			return success;
		}
		return failure;
	}
	while (currentNode->next != NULL)
	{
		if (lp->equalFuncSE(currentNode->next->data, data) == true)
		{
			if (lp->freeFunc(currentNode->next->data) == success)
			{
				Node* temp = currentNode->next;
				currentNode->next = temp->next;
				free(temp);
				if (currentNode->next == NULL)
				{
					lp->tail = currentNode;
				}
				lp->size--;
				return success;
			}
			return failure;
		}
		currentNode = currentNode->next;
	}

	return failure;
}

// Function that displays the linked list.
// lp is a pointer to linked list.
// The function returns a status if the operation succeed or failed.
status displayList(LinkedList lp)
{
	if (lp == NULL)
	{
		return failure;
	}
	Node* currentNode = lp->head;
	while (currentNode != NULL)
	{
		if (lp->printFunc(currentNode->data) == success)
		{
			currentNode = currentNode->next;
			continue;
		}
		return failure;
	}
	return success;
}

// Function that returns the data that stored in location index at the linked list.
// lp is a pointer to linked list.
// index is the location in the linked list for the data to be returned..
//the function returns a pointer to the relevant value or null if the key is not found.
Element getDataByIndex(LinkedList lp, int index)
{
	if (lp == NULL || index < 1)
	{
		return NULL;
	}
	int counter = 1;
	Node* currentNode = lp->head;
	while (currentNode != NULL)
	{
		if (index == counter)
		{
			return lp->copyFunc(currentNode->data);
		}
		currentNode = currentNode->next;
		counter++;
	}
	return NULL;
}

// Function that returns the size of the linked list.
int getlengthlist(LinkedList lp)
{
	if (lp == NULL)
	{
		return 0;
	}
	return lp->size;
}


// Function that returns the value of the data that stored where the key of the data is the key that the function received.
// lp is a pointer to linked list.
// key is the data's key in the linked list for the data's value to be returned..
//the function returns a pointer to the relevant value or null if the key is not found.
Element searchByKeyInList(LinkedList lp, Element key)
{
	if (lp == NULL || key == NULL)
	{
		return NULL;
	}
	Node* currentNode = lp->head;
	while (currentNode != NULL)
	{
		if (lp->equalFuncDE(currentNode->data, key))
		{
			return lp->copyFunc(currentNode->data);
		}
		currentNode = currentNode->next;
	}
	return NULL;
}

// The function received pointer to hash table and destroys it.
// The function returns a status if the operation succeed or failed.
status destroyList(LinkedList lp)
{
	if (lp == NULL)
	{
		return failure;
	}
	Node* currentNode = lp->head;
	Node* temp;
	while (currentNode != NULL)
	{
		lp->freeFunc(currentNode->data);
		temp = currentNode->next;
		free(currentNode);
		currentNode = temp;
	}
	free(lp);
	return success;
}
