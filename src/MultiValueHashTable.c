#include "MultiValueHashTable.h"
#include "HashTable.h"
#include "LinkedList.h"
#include "KeyValuePair.h"

// Declare the attributes for the ADT generic structure multi value hash table.
struct MultiValueHashTable_s
{
	hashTable ht;
	CopyFunction copyKeyFunc;
	CopyFunction copyValFunc;
	FreeFunction freeKeyFunc;
	FreeFunction freeValFunc;
	PrintFunction printKeyFunc;
	PrintFunction printValFunc;
	EqualFunction equalKeyFunc;
	EqualFunction equalValFunc;
	TransformIntoNumberFunction transformIntoNumberFunc;
	int hashNumber;
};


// Function that creates a new multi value hash table and initializes its attribute.
// copyKey is a function that received a key and returns copy of it.
// freeKey is a function that received a key and frees the memory that allocated to it.
// printKey is a function that received a key and prints it.
// copyVal is a function that received a value and returns copy of it.
// freeVal is a function that received a value and frees the memory that allocated to it.
// printValue is a function that received a value and prints it.
// equalVal is a function that received 2 values and returns true if they are equal or false either.
// equalKey is a function that received 2 keys and returns true if they are equal or false either.
// transformIntoNumber is a that received key and returns int's value for it.
// hashNumber is the size for the hash table.
// The function returns a a pointer to the hash table or null if an error occurred.
MultiValueHashTable createMultiValueHashTable(CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey, CopyFunction copyValue, FreeFunction freeValue, PrintFunction printValue, EqualFunction equalVal,EqualFunction equalKey, TransformIntoNumberFunction transformIntoNumber, int hashNumber)
{
	MultiValueHashTable multiValueHashTable = (MultiValueHashTable)malloc(sizeof(struct MultiValueHashTable_s));
	if (multiValueHashTable == NULL)
	{
		return NULL;
	}
	multiValueHashTable->ht = createHashTable(copyKey, freeKey, printKey, copyValue, (FreeFunction)destroyList, (PrintFunction)displayList, equalKey, transformIntoNumber, hashNumber);
	multiValueHashTable->copyKeyFunc = copyKey;
	multiValueHashTable->freeKeyFunc = freeKey;
	multiValueHashTable->printKeyFunc = printKey;
	multiValueHashTable->copyValFunc = copyValue;
	multiValueHashTable->freeValFunc = freeValue;
	multiValueHashTable->printValFunc = printValue;
	multiValueHashTable->equalKeyFunc = equalKey;
	multiValueHashTable->equalValFunc = equalVal;
	multiValueHashTable->transformIntoNumberFunc = transformIntoNumber;
	multiValueHashTable->hashNumber = hashNumber;
	return multiValueHashTable;
}


// The function received pointer to multi value hash table and destroys it.
// The function returns a status if the operation succeed or failed.
status destroyMultiValueHashTable(MultiValueHashTable mvht)
{
	if (mvht == NULL)
	{
		return failure;
	}
	if (destroyHashTable(mvht->ht) == failure)
	{
		return failure;
	}
	free(mvht);
	return success;
}

// Function that adds a new key value pair to the multi value hash table.
// mvht is a pointer to multi value hash table.
// key and value is the key and the value of the key value pair that will add.
// The function returns a status if the operation succeed or failed.
status addToMultiValueHashTable(MultiValueHashTable mvht, Element key,Element value)
{
	if (mvht == NULL || key == NULL || value == NULL)
	{
		return failure;
	}
	LinkedList valuesLinkedList = lookupInHashTable(mvht->ht, key);
	if (valuesLinkedList == NULL)
	{
		valuesLinkedList = createLinkedList((CopyFunction)mvht->copyValFunc, (FreeFunction)mvht->freeValFunc, (PrintFunction)mvht->printValFunc, (EqualFunction)mvht->equalValFunc , (EqualFunction)mvht->equalKeyFunc);
		if (valuesLinkedList == NULL)
		{
			return destroyMultiValueHashTable(mvht);
		}
		if (appendNode(valuesLinkedList, value) == failure)
		{
			return failure;
		}
		return addToHashTable(mvht->ht, key, valuesLinkedList);
	}
	return appendNode(valuesLinkedList, value);
}

// Function that looks up in multi value hash table to the value for the given key.
// mvht is a pointer to multi value hash table.
// key is the key that the function looks up to his value.
//the function returns a pointer to the relevant value or null if the key is not found.
Element lookupInMultiValueHashTable(MultiValueHashTable mvht, Element key)
{
	if (mvht == NULL || key == NULL)
	{
		return NULL;
	}
	return lookupInHashTable(mvht->ht, key);
}

// Function that removed a key value pair for multi value hash table.
// mvhht is a pointer to multi value hash table.
// key is the key of the key value pair that the function will remove.
// The function returns a status if the operation succeed or failed.
status removeFromMultiValueHashTable(MultiValueHashTable mvht, Element key, Element value)
{
	if (mvht == NULL || key == NULL || value == NULL)
	{
		return failure;
	}
	LinkedList valuesLinkedList = lookupInMultiValueHashTable(mvht, key);
	if (valuesLinkedList == NULL)
	{
		return failure;
	}
	if (deleteNode(valuesLinkedList, value) == failure)
	{
		return failure;
	}
	if (getlengthlist(valuesLinkedList) == 0)
	{
		if (removeFromHashTable(mvht->ht, key) == failure)
		{
			return failure;
		}
	}
	return success;
}

// Function that displays the multi value hash table.
// mvht is a pointer to multi value hash table.
// The function returns a status if the operation succeed or failed.
status displayMultiValueHashElements(MultiValueHashTable mvht, Element key)
{
	if (mvht == NULL || key == NULL)
	{
		return failure;
	}
	LinkedList lp = lookupInMultiValueHashTable(mvht, key);
	if (lp == NULL)
	{
		return failure;
	}
	mvht->printKeyFunc(key);
	return displayList(lp);
}



