The project splited to 11 files: Defs.h, Jerry.h, Jerry.c, JerryBoreeMain.c.
Defs.h inclouds enum bool that allowing the option to use bool and enum status that allowing to know if action success of failure. Moreover, there are all the declarations of the functions that all the ADT's structs need to receive.
Jerry.h inclouds all the functions and structure's settings for module Jerry.
Jerry.c inclouds the implementation for all the functions that setted in Jerry.h.
JerryBoree.c inclouds the main of the project and all the functions that needed for implement the interface of the project. Moreover, the informations that got from the textFile are readed in the function readFromFile and are saved with calling the right function according to the information in each line.
LinkedList.h inclouds all the functions that setted in generic adt module linked list.
LinkedList.c inclouds the implementation for all the functions that setted in LinkedList.h and all the generic settings for the module.
HashTable.c inclouds the implementation for all the functions that setted in HashTable.h and all the generic settings for the module.This generic ADT realized with LinkedList to support chaining and to give the option to find each key in the table at O(1) in avarage. I set the size of the hash table to 37 because its a prime number and it big enough to reduce the number of collisions and make the table more effective but not too big for dont use in too much memory that dont needs.
keyValuePair.h inclouds all the functions that setted in generic adt module KeyValuePair.
keyValuePair.c inclouds the implementation for all the functions that setted in keyValuePair.h and all the generic settings for the module. all the data that save in hash table and multi value hash table store into key value pair to find it the fastest way.
MultiValueHashTable.h inclouds all the functions that setted in generic adt module MultiValueHashTable.
MultiValueHashTable.c inclouds the implementation for all the functions that setted in MultiValueHashTable.h and all the generic settings for the module.This generic ADT use the methods in hash table and bases on it. the difference is that here the value of each key is a linked list to support chaining. the size here is the same as the hash table for the same reasons.
