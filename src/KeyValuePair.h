#ifndef KEYVALUEPAIR_H_
#define KEYVALUEPAIR_H_

#include "Defs.h"

// Struct that represents a key value pair.
typedef struct t_KeyValuePair *KeyValuePair;


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
KeyValuePair createKeyValuePair(CopyFunction copyKey, CopyFunction copyVal, FreeFunction freeKey, FreeFunction freeVal, PrintFunction printKey, PrintFunction printVal, EqualFunction equalKey, Element key, Element val);

// Function that receives pointer to key value pair and destroys it.
// The function returns a status if the operation succeed or failed.
status destroyKeyValuePair(KeyValuePair kvp);

// Function that receives a pointer to key value pair and displays the value of this key value pair.
// The function returns a status if the operation succeed or failed.
status displayValue(KeyValuePair kvp);

// Function that receives a pointer to key value pair and displays the key of this key value pair.
// The function returns a status if the operation succeed or failed.
status displayKey(KeyValuePair kvp);

// Function that receives a pointer to key value pair and returns the value of this key value pair.
Element getValue(KeyValuePair kvp);

// Function that receives a pointer to key value pair and returns the key of this key value pair.
Element getKey(KeyValuePair kvp);

// Function that receives key value pair and a key and returns true if the key is equal to the key in the key value pair or false either.
bool isEqualKey(KeyValuePair kvp, Element key);


#endif /* KEYVALUEPAIR_H_ */
