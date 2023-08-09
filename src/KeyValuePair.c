#include "KeyValuePair.h"
#include "string.h"
#include <stdio.h>
#include <stdlib.h>

// Declare the attributes for the ADT generic structure key value pair.
struct t_KeyValuePair
{
	Element key;
	Element val;
	CopyFunction copyKeyFunc;
	CopyFunction copyValFunc;
	FreeFunction freeKeyFunc;
	FreeFunction freeValFunc;
	PrintFunction printKeyFunc;
	PrintFunction printValFunc;
	EqualFunction equalKeyFunc;
};

// Function that creates a new key value pair and initializes its attribute.
// copyKey is a function that received a key and returns copy of it.
// freeKey is a function that received a key and frees the memory that allocated to it.
// printKey is a function that received a key and prints it.
// copyVal is a function that received a value and returns copy of it.
// freeVal is a function that received a value and frees the memory that allocated to it.
// printValue is a function that received a value and prints it.
// equalKey is a function that received 2 keys and returns true if they are equal or false either.
// key is the element key in key value pair.
// value is the element value in key value pair.
// the function return a a pointer to the key value pair or null if an error occurred.
KeyValuePair createKeyValuePair(CopyFunction copyKeyf, CopyFunction copyValf, FreeFunction freeKeyf, FreeFunction freeValf, PrintFunction printKeyf, PrintFunction printValf, EqualFunction equalKeyf, Element key, Element val)
{
	if (key == NULL || val == NULL)
	{
		return NULL;
	}
	KeyValuePair keyValuePair = (KeyValuePair)malloc(sizeof(struct t_KeyValuePair));
	if (keyValuePair == NULL)
	{
		return NULL;
	}

	keyValuePair->copyKeyFunc = copyKeyf;
	keyValuePair->copyValFunc = copyValf;
	keyValuePair->freeKeyFunc = freeKeyf;
	keyValuePair->freeValFunc = freeValf;
	keyValuePair->printKeyFunc = printKeyf;
	keyValuePair->printValFunc = printValf;
	keyValuePair->equalKeyFunc = equalKeyf;
	keyValuePair->key = keyValuePair->copyKeyFunc(key);
	keyValuePair->val = keyValuePair->copyValFunc(val);
	return keyValuePair;
}

// The function receives pointer to key value pair and destroys it.
// The function returns a status if the operation succeed or failed.
status destroyKeyValuePair(KeyValuePair kvp)
{
	if (kvp == NULL)
	{
		return failure;
	}
	if (kvp->freeKeyFunc(kvp->key) == failure || kvp->freeValFunc(kvp->val) == failure)
	{
		return failure;
	}
	free(kvp);
	return success;
}

// The function receives a pointer to key value pair and display the value of this key value pair.
// The function returns a status if the operation succeed or failed.
status displayValue(KeyValuePair kvp)
{
	if (kvp == NULL)
	{
		return failure;
	}
	return kvp->printValFunc(kvp->val);
}

// The function receives a pointer to key value pair and display the key of this key value pair.
// The function returns a status if the operation succeed or failed.
status displayKey(KeyValuePair kvp)
{
	if (kvp == NULL)
	{
		return failure;
	}
	return kvp->printKeyFunc(kvp->key);
}

// The function receives a pointer to key value pair and returns the value of this key value pair.
Element getValue(KeyValuePair kvp)
{
	if (kvp == NULL)
	{
		return NULL;
	}
	return kvp->val;
}

// The function receives a pointer to key value pair and returns the key of this key value pair.
Element getKey(KeyValuePair kvp)
{
	if (kvp == NULL)
	{
		return NULL;
	}
	return kvp->key;
}

// Function that receives key value pair and a key and returns true if the key is equal to the key in the key value pair or false either.
bool isEqualKey(KeyValuePair kvp, Element key)
{
	if (kvp == NULL || key == NULL)
	{
		return false;
	}
	return kvp->equalKeyFunc(kvp->key, key);
}

