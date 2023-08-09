#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include "Defs.h"

// Struct that represents a key value pair.
typedef struct t_LinkedList *LinkedList;

// Function that creates a new linked list and initializes its attribute.
// copyf is a function that received a element and returns copy of it.
// freef is a function that received a element and frees the memory that allocated to it.
// printf is a function that received a element and prints it.
// equalFSE is a function that received 2 same type element and returns true if they are equal or false either.
// equalDSE is a function that received 2 different type element and returns true if one of them contained in the second or false either.
// The function return a a pointer to the linked list or null if an error occurred.
LinkedList createLinkedList(CopyFunction copyf, FreeFunction freef, PrintFunction printf,EqualFunction equalFSE, EqualFunction equalFDE);

// The function received pointer to hash table and destroys it.
// The function returns a status if the operation succeed or failed.
status destroyList(LinkedList lp);


// Function that adds a new node to the linked list.
// lp is a pointer to linked list.
// data is the data that should be stored in a new node that is added to the linked list.
// The function returns a status if the operation succeed or failed.
status appendNode(LinkedList lp, Element data);

// Function that deletes a node from the linked list.
// lp is a pointer to linked list.
// data is the data that should be deleted from the linked list.
// The function returns a status if the operation succeed or failed.
status deleteNode(LinkedList lp, Element data);

// Function that displays the linked list.
// lp is a pointer to linked list.
// The function returns a status if the operation succeed or failed.
status displayList(LinkedList lp);

// Function that returns the data that stored in location index at the linked list.
// lp is a pointer to linked list.
// index is the location in the linked list for the data to be returned..
//the function returns a pointer to the relevant value or null if the key is not found.
Element getDataByIndex(LinkedList lp, int index);

// Function that returns the size of the linked list.
int getlengthlist(LinkedList lp);

// Function that returns the value of the data that stored where the key of the data is the key that the function received.
// lp is a pointer to linked list.
// key is the data's key in the linked list for the data's value to be returned..
//the function returns a pointer to the relevant value or null if the key is not found.
Element searchByKeyInList(LinkedList lp, Element val);

#endif /* LINKEDLIST_H_ */
