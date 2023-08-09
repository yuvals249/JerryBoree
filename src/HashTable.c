#include "HashTable.h"
#include "LinkedList.h"
#include "KeyValuePair.h"

// Declare the attributes for the ADT generic structure hash table.
struct hashTable_s
{
	LinkedList* table;
	CopyFunction copyKeyFunc;
	CopyFunction copyValFunc;
	FreeFunction freeKeyFunc;
	FreeFunction freeValFunc;
	PrintFunction printKeyFunc;
	PrintFunction printValFunc;
	EqualFunction equalKeyFunc;
	TransformIntoNumberFunction transformIntoNumberFunc;
	int hashNumber;
};
// Function that receives key value pair and returns it.
KeyValuePair copyKeyValuePair(KeyValuePair kvp)
{
	return kvp;
}

// Static function that received key value pair and prints the information about them.
static status printFunc(KeyValuePair kvp)
{
	if (displayKey(kvp) == success && displayValue(kvp) == success)
	{
		return success;
	}
	return failure;
}

// Static function that received 2 key value pair and return if they are equal
static bool equalFSE(KeyValuePair kvp1, KeyValuePair kvp2)
{
	return isEqualKey(kvp1, getKey(kvp2));
}

// Function that creates a new hash table and initializes its attribute.
// copyKey is a function that received a key and returns copy of it.
// freeKey is a function that received a key and frees the memory that allocated to it.
// printKey is a function that received a key and prints it.
// copyVal is a function that received a value and returns copy of it.
// freeVal is a function that received a value and frees the memory that allocated to it.
// printValue is a function that received a value and prints it.
// equalKey is a function that received 2 keys and returns true if they are equal or false either.
// transformIntoNumber is a function that received key and returns int's value for it.
// hashNumber is the size for the hash table.
// The function returns a a pointer to the hash table or null if an error occurred.
hashTable createHashTable(CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey, CopyFunction copyValue, FreeFunction freeValue, PrintFunction printValue, EqualFunction equalKey, TransformIntoNumberFunction transformIntoNumber, int hashNumber)
{
	if (hashNumber < 1)
	{
		return NULL;
	}
	hashTable hashtable = (hashTable)malloc(sizeof(struct hashTable_s));
	if (hashtable == NULL)
	{
		return NULL;
	}
	hashtable->table = (LinkedList *)malloc(sizeof(LinkedList) * hashNumber);
	if (hashtable->table == NULL)
	{
		destroyHashTable(hashtable);
		return NULL;
	}

	for (int i = 0; i < hashNumber; i++)
	{
		hashtable->table[i] = createLinkedList((CopyFunction)copyKeyValuePair, (FreeFunction)destroyKeyValuePair, (PrintFunction)printFunc, (EqualFunction)equalFSE, (EqualFunction)isEqualKey);
		if (hashtable->table[i] == NULL)
		{
			destroyHashTable(hashtable);
			return NULL;
		}
	}

	hashtable->copyKeyFunc = copyKey;
	hashtable->freeKeyFunc = freeKey;
	hashtable->printKeyFunc = printKey;
	hashtable->copyValFunc = copyValue;
	hashtable->freeValFunc = freeValue;
	hashtable->printValFunc = printValue;
	hashtable->equalKeyFunc = equalKey;
	hashtable->transformIntoNumberFunc = transformIntoNumber;
	hashtable->hashNumber = hashNumber;
	return hashtable;
}

// The function receives pointer to hash table and destroys it.
// The function returns a status if the operation succeed or failed.
status destroyHashTable(hashTable ht)
{
	if (ht == NULL)
	{
		return failure;
	}
	for (int i = 0; i < ht->hashNumber; i++)
	{
		LinkedList currentLp = ht->table[i];
		if (currentLp == NULL)
		{
			break;
		}
		if (destroyList(currentLp) == failure)
		{
			return failure;
		}
	}
	free(ht->table);
	free(ht);
	return success;
}

// Function that adds a new key value pair to the hash table.
// ht is a pointer to hash table.
// key and value is the key and the value of the key value pair that will add.
// The function returns a status if the operation succeed or failed.
status addToHashTable(hashTable ht, Element key, Element value)
{
	if (ht == NULL || key == NULL || value == NULL)
	{
		return failure;
	}
	KeyValuePair kvp = createKeyValuePair((CopyFunction)ht->copyKeyFunc, (CopyFunction)ht->copyValFunc, (FreeFunction)ht->freeKeyFunc, (FreeFunction)ht->freeValFunc, (PrintFunction)ht->printKeyFunc, (PrintFunction)ht->printValFunc, (EqualFunction)ht->equalKeyFunc, key, value);
	if (kvp == NULL)
	{
		destroyHashTable(ht);
		return failure;
	}
	int loc = ht->transformIntoNumberFunc(key) % ht->hashNumber;
	return appendNode(ht->table[loc], kvp);
}

// Function that looks up in hash table to the value for the given key.
// ht is a pointer to hash table.
// key is the key that the function looks up to his value.
//the function returns a pointer to the relevant value or null if the key is not found.
Element lookupInHashTable(hashTable ht, Element key)
{
	if (ht == NULL || key == NULL)
	{
		return NULL;
	}
	int loc = ht->transformIntoNumberFunc(key) % ht->hashNumber;
	KeyValuePair kvp = searchByKeyInList(ht->table[loc], key);
	if (kvp ==  NULL)
	{
		return NULL;
	}
	return getValue(kvp);

}

// Function that removed a key value pair for hash table.
// ht is a pointer to hash table.
// key is the key of the key value pair that the function will remove.
// The function returns a status if the operation succeed or failed.
status removeFromHashTable(hashTable ht, Element key)
{
	if (ht == NULL || key == NULL)
	{
		return failure;
	}
	int loc = ht->transformIntoNumberFunc(key) % ht->hashNumber;
	KeyValuePair kvp = searchByKeyInList(ht->table[loc], key);
	if (kvp == NULL)
	{
		return failure;
	}
	return deleteNode(ht->table[loc], kvp);
}

// Function that displays the hash table.
// ht is a pointer to hash table.
// The function returns a status if the operation succeed or failed.
status displayHashElements(hashTable ht)
{
	if (ht == NULL)
	{
		return failure;
	}
	for (int i = 0; i < ht->hashNumber; i++)
	{
		LinkedList currentLp = ht->table[i];
		if (displayList(currentLp) == failure)
		{
			return failure;
		}
	}
	return success;
}




