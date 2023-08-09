#ifndef MULTIVALUEHASHTABLE_H_
#define MULTIVALUEHASHTABLE_H_
#include "Defs.h"

// Struct that represents a multi value hash table.
typedef struct MultiValueHashTable_s *MultiValueHashTable;

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
MultiValueHashTable createMultiValueHashTable(CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey, CopyFunction copyValue, FreeFunction freeValue, PrintFunction printValue,EqualFunction equalVal ,EqualFunction equalKey, TransformIntoNumberFunction transformIntoNumber, int hashNumber);

// The function received pointer to multi value hash table and destroys it.
// The function returns a status if the operation succeed or failed.
status destroyMultiValueHashTable(MultiValueHashTable);

// Function that adds a new key value pair to the multi value hash table.
// mvht is a pointer to multi value hash table.
// key and value is the key and the value of the key value pair that will add.
// The function returns a status if the operation succeed or failed.
status addToMultiValueHashTable(MultiValueHashTable, Element key,Element value);

// Function that looks up in multi value hash table to the value for the given key.
// mvht is a pointer to multi value hash table.
// key is the key that the function looks up to his value.
//the function returns a pointer to the relevant value or null if the key is not found.
Element lookupInMultiValueHashTable(MultiValueHashTable, Element key);

// Function that removed a key value pair for multi value hash table.
// mvhht is a pointer to multi value hash table.
// key is the key of the key value pair that the function will remove.
// The function returns a status if the operation succeed or failed.
status removeFromMultiValueHashTable(MultiValueHashTable, Element key, Element value);

// Function that displays the multi value hash table.
// mvht is a pointer to multi value hash table.
// The function returns a status if the operation succeed or failed.
status displayMultiValueHashElements(MultiValueHashTable, Element);


#endif /* MULTIVALUEHASHTABLE_H_ */
