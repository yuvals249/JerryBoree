#ifndef DEFS_H_
#define DEFS_H_
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// enum for boolean
typedef enum e_bool { false, true } bool;
// enum for success / failure status
typedef enum e_status { success, failure } status;

// use Element as a void*
typedef void * Element;

// copy function that received Element and returns Element
typedef Element(*CopyFunction) (Element);
// free function that received Element and returns status if the free succeed or failure either
typedef status(*FreeFunction) (Element);
// print function that received Element and returns status if the print succeed or failure either
typedef status(*PrintFunction) (Element);
// transform function that received Element and returns int's value for the Element
typedef int(*TransformIntoNumberFunction) (Element);
// equal function that received 2 Elements and returns true if the are equal or false either
typedef bool(*EqualFunction) (Element, Element);

#endif /* DEFS_H_ */
