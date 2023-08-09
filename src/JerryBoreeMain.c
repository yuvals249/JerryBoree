#include "Jerry.h"
#include "Defs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "HashTable.h"
#include "MultiValueHashTable.h"

void readFromFile(char *, int, LinkedList, LinkedList, hashTable, MultiValueHashTable);
Planet* readPlanetFromLine(char *);
Jerry* readJerryFromLine(char *, LinkedList);
Physicalcharacteristics* readPhysicalcharacteristicsFromLine(char *);
void addNewJerry(LinkedList planets, LinkedList jerries, hashTable jerriesht, MultiValueHashTable PCmvht);
void removePhysicalCharacteristicFromJerry(hashTable, MultiValueHashTable);
void removeJerry(LinkedList, hashTable, MultiValueHashTable);
static float absToValue(float);
void removeSimilarJerry(LinkedList, hashTable, MultiValueHashTable);
void removeSaddestJerry(LinkedList, hashTable, MultiValueHashTable);
void interactWithFakeBeth(LinkedList);
void playGolf(LinkedList);
void adjustPictureSettings(LinkedList);
void goHome(LinkedList, LinkedList, hashTable, MultiValueHashTable);


//Copy function to generic element
Element copyElement(Element elem)
{
	return elem;
}

// The function receives pointer to jerry and destroys it.
// The function return success after it.
status freeJerry(Jerry* jerry)
{
	destroyJerry(jerry);
	return success;
}

// The function receives pointer to planet and destroys it.
// The function return success after it.
status freePlanet(Planet* planet)
{
	destroyPlanet(planet);
	return success;
}

// The function receives pointer to jerry and prints it.
// The function return success after it.
status prJerry(Jerry* jerry)
{
	return printJerry(jerry);
}

// The function receives pointer to planet and prints it.
// The function return success after it.
status prPlanet(Planet* planet)
{
	return printPlanet(planet);
}

// The function receives 2 pointers to jerries and return true if they are equal or false either.
bool equalFuncSEJToJerrylp(Jerry* jerry, Jerry* other)
{
	return strcmp(jerry->id, other->id) == 0;
}

// The function receives 2 pointers to planets and return true if they are equal or false either.
bool equalFuncSEJToPlanetlp(Planet* planet, Planet* other)
{
	return strcmp(planet->name, other->name) == 0;
}

// The function receives pointer to jerry and id and return true if its id is equal to the id the function received or false either.
bool equalFuncDEJToJerrylp(Jerry* jerry, char* id)
{
	return strcmp(jerry->id, id) == 0;
}

// The function receives pointer to planet and name and return true if its name is equal to the name the function received or false either.
bool equalFuncDEJToPlanetlp(Planet* planet, char* name)
{
	return strcmp(planet->name, name) == 0;
}

// Function that receives element and do nothing except return success.
status freeAndPrintKeyFromHash(Element elem)
{
	return success;
}

// Function that receives key and prints its name
status prKeyHash(char* key)
{
	printf("%s : \n", key);
	return success;
}

// Function that receives 2 char* and return true if they are equal or false either.
bool equalKeyHash(char* key, char* other)
{
	return strcmp(key, other) == 0;
}

// Function that receives char* and returns the sum of its char's ascii value.
int transform(char* stri)
{
	int sum = 0;
	for (int i = 0; stri[i] != '\0'; i++)
		sum += (int)stri[i];
	return sum;
}

// Deep copy for pc's name
char* deepCopyPC(char* PCName)
{
	char* coName = malloc(strlen(PCName) + 1);
	strcpy(coName, PCName);
	return coName;
}

// Function that receives pointer to pc name and free it and return success after it.
status freePCName(char *PCName)
{
	free(PCName);
	return success;
}

// Function that receives pc name and prints its name
status prPCName(char* PCName)
{
	printf("%s : \n", PCName);
	return success;
}

// The function received path to text file, the number of the planets, 2 linked list that one for the jerries and one for the planets, hash table for the jerries and multi value hash table to the pc names and jerries.
// The function splits the file to lines and then to words and creates the objects.
void readFromFile(char *pathToRead, int numberOfPlanets, LinkedList jerries, LinkedList planets, hashTable jerriesht, MultiValueHashTable PCmvht)
{
	if (jerries == NULL || planets == NULL || jerriesht == NULL)
	{
		printf("Memory Problem");
		goHome(jerries, planets, jerriesht, PCmvht);
		exit(1);
	}
	FILE *textFile;
	char line[1205];
	int lineNumber = 0;
	textFile = fopen(pathToRead, "r");
	if (textFile == NULL)
	{
		printf("textFile is empty");
		exit(1);
	}
	fgets(line, sizeof(line), textFile);
	while(fgets(line, sizeof(line), textFile) && lineNumber < numberOfPlanets)
	{
		if (appendNode(planets, readPlanetFromLine(line)) == failure)
		{
			printf("Memory Problem");
			goHome(jerries, planets, jerriesht, PCmvht);
			exit(1);
		}
		lineNumber++;
	}
	while(fgets(line, sizeof(line), textFile) != NULL)
	{
		if (line[0] != '\t')
		{
			Jerry* currentJerry = readJerryFromLine(line, planets);
			if (appendNode(jerries, currentJerry) == failure)
			{
				printf("Memory Problem");
				goHome(jerries, planets, jerriesht, PCmvht);
				exit(1);
			}
			if (addToHashTable(jerriesht, currentJerry->id, currentJerry) == failure)
			{
				printf("Memory Problem");
				goHome(jerries, planets, jerriesht, PCmvht);
				exit(1);
			}
			continue;
		}
		else
		{
			Physicalcharacteristics *physicalcharacteristicsPoint = readPhysicalcharacteristicsFromLine(line);
			if (physicalcharacteristicsPoint == NULL)
			{
				printf("Memory Problem");
				goHome(jerries, planets, jerriesht, PCmvht);
				exit(1);
			}
			Jerry* lastJerry = (Jerry *)getDataByIndex(jerries, getlengthlist(jerries));
			addPhysicalcharacteristic(lastJerry, physicalcharacteristicsPoint);
			if (addToMultiValueHashTable(PCmvht, physicalcharacteristicsPoint->name, lastJerry) == failure)
			{
				printf("Memory Problem");
				goHome(jerries, planets, jerriesht, PCmvht);
				exit(1);
			}
		}
	}
	fclose(textFile);
}

// The function that received each line of the planets from text and responsible to creates it.
Planet* readPlanetFromLine(char *line)
{
	char *name;
	float x, y, z;
	char *word = strtok(line, ",");
	name = word;
	word = strtok(NULL, ",");
	x = atof(word);
	word = strtok(NULL, ",");
	y = atof(word);
	word = strtok(NULL, ",");
	z = atof(word);
	return initPlanet(name, x, y, z);
}

// The function that received each line of the jerries from text and responsible to creates it.
Jerry* readJerryFromLine(char *line, LinkedList planets)
{
	char *id;
	char *planetName;
	Planet *planet;
	char *dimension;
	int happiness;
	char *word = strtok(line, ",");
	id = word;
	word = strtok(NULL, ",");
	dimension = word;
	word = strtok(NULL, ",");
	planetName = word;
	planet = searchByKeyInList(planets, planetName);
	word = strtok(NULL, ",");
	happiness = atoi(word);
	return initJerry(id, happiness, planet, dimension);
}

// The function that received each line of the jerry's physical characteristic and creates it.
Physicalcharacteristics* readPhysicalcharacteristicsFromLine(char *line)
{
	line++;
	char *name;
	float value;
	char *word = strtok(line, ":");
	name = word;
	word = strtok(NULL, ":");
	value = atof(word);
	return initPhysicalcharacteristics(name, value);
}

// case 1
// Function that adds a new jerry and saves it to all the relevant structures.
void addNewJerry(LinkedList planets, LinkedList jerries, hashTable jerriesht, MultiValueHashTable PCmvht)
{
	char id[300];
	char name[300];
	char dimension[300];
	char happiness[300];
	printf("What is your Jerry's ID ? \n");
	scanf("%s", id);
	Jerry* jerry = (Jerry *)lookupInHashTable(jerriesht, id);
	if (jerry != NULL)
	{
		printf("Rick did you forgot ? you already left him here ! \n");
		return;
	}
	printf("What planet is your Jerry from ? \n");
	scanf("%s", name);
	Planet* planet = (Planet *)searchByKeyInList(planets, name);
	if (planet == NULL)
	{
		printf("%s is not a known planet ! \n", name);
		return;
	}
	printf("What is your Jerry's dimension ? \n");
	scanf("%s", dimension);
	printf("How happy is your Jerry now ? \n");
	scanf("%s", happiness);
	jerry = (Jerry *)initJerry(id, atoi(happiness), planet, dimension);
	if (jerry == NULL)
	{
		printf("Memory Problem");
		goHome(jerries, planets, jerriesht, PCmvht);
		exit(1);
	}
	if (appendNode(jerries, jerry) == failure)
	{
		printf("Memory Problem");
		goHome(jerries, planets, jerriesht, PCmvht);
		exit(1);
	}
	if (addToHashTable(jerriesht, id, jerry) == failure)
	{
		printf("Memory Problem");
		goHome(jerries, planets, jerriesht, PCmvht);
		exit(1);
	}
	printJerry(jerry);
	return;
}

// case 3
// The function received jerries's hash table and pc names and jerries multi value hash table and removes from him and from all the relevant structures physical characteristic if he known.
void removePhysicalCharacteristicFromJerry(hashTable jerriesht, MultiValueHashTable PCmvht)
{
	char id[300];
	char name[300];
	printf("What is your Jerry's ID ? \n");
	scanf("%s", id);
	Jerry* jerry = (Jerry *)lookupInHashTable(jerriesht, id);
	if (jerry == NULL)
	{
		printf("Rick this Jerry is not in the daycare ! \n");
		return;
	}
	printf("What physical characteristic do you want to remove from Jerry - %s ? \n", id);
	scanf("%s", name);
	if (!ifPhysicalcharacteristicExist(jerry, name))
	{
		printf("The information about his %s not available to the daycare ! \n", name);
		return;
	}
	removePhysicalcharacteristicByName(jerry, name);
	removeFromMultiValueHashTable(PCmvht, name, jerry);
	printJerry(jerry);
	return;
}


// case 4
// Function that removes a jerry and deletes it from all the relevant structures.
void removeJerry(LinkedList jerries, hashTable jerriesht, MultiValueHashTable PCmvht)
{
	char id[300];
	printf("What is your Jerry's ID ? \n");
	scanf("%s", id);
	Jerry* jerry = (Jerry *)lookupInHashTable(jerriesht, id);
	if (jerry == NULL)
	{
		printf("Rick this Jerry is not in the daycare ! \n");
		return;
	}
	removeFromHashTable(jerriesht, id);
	for (int i = 0; i < jerry->size_of_physicalcharacteristics; i++)
	{
		removeFromMultiValueHashTable(PCmvht, jerry->physicalcharacteristics[i]->name, jerry);
	}
	printf("Rick thank you for using our daycare service ! Your Jerry awaits ! \n");
	deleteNode(jerries, jerry);
	return;
}

// Function that receives a number and return its abs.
static float absToValue(float number)
{
	return number < 0 ? -number : number;
}

// case 5
// Function that removes the most similar jerry by a pc name and a value and deletes it from all the relevant structures.
void removeSimilarJerry(LinkedList jerries, hashTable jerriesht, MultiValueHashTable PCmvht)
{
	char name[300];
	char value[300];
	float valueInFloat;
	printf("What do you remember about your Jerry ? \n");
	scanf("%s", name);
	LinkedList pclp = (LinkedList)lookupInMultiValueHashTable(PCmvht, name);
	if (getlengthlist(pclp) == 0)
	{
		printf("Rick we can not help you - we do not know any Jerry's %s ! \n", name);
		return;
	}
	printf("What do you remember about the value of his %s ? \n", name);
	scanf("%s", value);
	valueInFloat = atof(value);
	Jerry* Similarjerry = (Jerry *)getDataByIndex(pclp, 1);
	float SimilarjerryValue;
	for (int i = 0; i < Similarjerry->size_of_physicalcharacteristics; i++)
	{
		if (strcmp(Similarjerry->physicalcharacteristics[i]->name, name) == 0)
		{
			SimilarjerryValue = absToValue(Similarjerry->physicalcharacteristics[i]->value - valueInFloat);
			break;
		}
	}
	int numOfjerries = getlengthlist(pclp);
	Jerry* currentJerry;
	for (int i = 2; i <= numOfjerries; i++)
	{
		currentJerry = (Jerry *)getDataByIndex(pclp, i);
		for (int j = 0; j < currentJerry->size_of_physicalcharacteristics; j++)
		{
			if (strcmp(currentJerry->physicalcharacteristics[j]->name, name) == 0)
			{
				if (absToValue(currentJerry->physicalcharacteristics[j]->value - valueInFloat) < SimilarjerryValue)
				{
					Similarjerry = currentJerry;
				}
				break;
			}
		}
	}
	printf("Rick this is the most suitable Jerry we found : \n");
	printJerry(Similarjerry);
	removeFromHashTable(jerriesht, Similarjerry->id);
	for (int i = 0; i < Similarjerry->size_of_physicalcharacteristics; i++)
	{
		removeFromMultiValueHashTable(PCmvht, Similarjerry->physicalcharacteristics[i]->name, Similarjerry);
	}
	printf("Rick thank you for using our daycare service ! Your Jerry awaits ! \n");
	deleteNode(jerries, Similarjerry);
	return;
}

// case 6
// Function that removes the saddest jerry and deletes it from all the relevant structures.
void removeSaddestJerry(LinkedList jerries, hashTable jerriesht, MultiValueHashTable PCmvht)
{
	if (getlengthlist(jerries) == 0)
	{
		printf("Rick we can not help you - we currently have no Jerries in the daycare ! \n");
		return;
	}
	Jerry* saddestJerry = (Jerry *)getDataByIndex(jerries, 1);
	Jerry* currentJerry;
	for (int i = 2; i <= getlengthlist(jerries); i++)
	{
		currentJerry = (Jerry *)getDataByIndex(jerries, i);
		if (currentJerry->happiness < saddestJerry->happiness)
		{
			saddestJerry = currentJerry;
		}
	}
	printf("Rick this is the most suitable Jerry we found : \n");
	printJerry(saddestJerry);
	removeFromHashTable(jerriesht, saddestJerry->id);
	for (int i = 0; i < saddestJerry->size_of_physicalcharacteristics;i++)
	{
		removeFromMultiValueHashTable(PCmvht,saddestJerry->physicalcharacteristics[i]->name, saddestJerry);
	}
	printf("Rick thank you for using our daycare service ! Your Jerry awaits ! \n");
	deleteNode(jerries, saddestJerry);
	return;
}


// case 8
//subcase 1
// Function that adds or subtracts the happiness level from all the jerries according to their happiness level.
void interactWithFakeBeth(LinkedList jerries)
{
	Jerry* currentJerry;
	for (int i = 1; i <= getlengthlist(jerries); i++)
	{
		currentJerry = (Jerry *)getDataByIndex(jerries, i);
		if (currentJerry->happiness >= 20)
		{
			currentJerry->happiness += 15;
			if (currentJerry->happiness > 100)
			{
				currentJerry->happiness = 100;
			}
		}
		else
		{
			currentJerry->happiness -= 5;
			if (currentJerry->happiness < 0)
			{
				currentJerry->happiness = 0;
			}
		}
	}
	printf("The activity is now over ! \n");
	displayList(jerries);
	return;
}

// subcase 2
// Function that adds or subtracts the happiness level from all the jerries according to their happiness level.
void playGolf(LinkedList jerries)
{
	Jerry* currentJerry;
	for (int i = 1; i <= getlengthlist(jerries); i++)
	{
		currentJerry = (Jerry *)getDataByIndex(jerries, i);
		if (currentJerry->happiness >= 50)
		{
			currentJerry->happiness += 10;
			if (currentJerry->happiness > 100)
			{
				currentJerry->happiness = 100;
			}
		}
		else
		{
			currentJerry->happiness -= 10;
			if (currentJerry->happiness < 0)
			{
				currentJerry->happiness = 0;
			}
		}
	}
	printf("The activity is now over ! \n");
	displayList(jerries);
	return;
}

// subcase 3
// Function that adds 20 to the happiness level for all the jerries.
void adjustPictureSettings(LinkedList jerries)
{
	Jerry* currentJerry;
	for (int i = 1; i <= getlengthlist(jerries); i++)
	{
		currentJerry = (Jerry *)getDataByIndex(jerries, i);
		currentJerry->happiness += 20;
		if (currentJerry->happiness > 100)
		{
			currentJerry->happiness = 100;
		}
	}
	printf("The activity is now over ! \n");
	displayList(jerries);
	return;
}

// The function destroys all the the objects and structures that saved before.
void goHome(LinkedList jerries, LinkedList planets, hashTable jerriesht, MultiValueHashTable PCmvht)
{
	destroyHashTable(jerriesht);
	destroyMultiValueHashTable(PCmvht);
	destroyList(planets);
	destroyList(jerries);
	printf("The daycare is now clean and close ! \n");
}


int main(int argc, char **argv)
{
	int ch = 0;
	char chInString[300];
	int numOfPlanets = atoi(argv[1]);
	char *path = argv[2];
	LinkedList Jerrylp = createLinkedList((CopyFunction)copyElement, (FreeFunction)freeJerry, (PrintFunction)prJerry, (EqualFunction)equalFuncSEJToJerrylp, (EqualFunction)equalFuncDEJToJerrylp);
	LinkedList Planetlp = createLinkedList((CopyFunction)copyElement, (FreeFunction)freePlanet, (PrintFunction)prPlanet, (EqualFunction)equalFuncSEJToPlanetlp, (EqualFunction)equalFuncDEJToPlanetlp);
	hashTable Jerryht = createHashTable((CopyFunction)deepCopyPC, (FreeFunction)freePCName, (PrintFunction)prKeyHash, (CopyFunction)copyElement, (FreeFunction)freeAndPrintKeyFromHash, (PrintFunction)prJerry, (EqualFunction)equalKeyHash, (TransformIntoNumberFunction)transform, 37);
	MultiValueHashTable PCmvht = createMultiValueHashTable((CopyFunction)deepCopyPC, (FreeFunction)freePCName, (PrintFunction)prPCName, (CopyFunction)copyElement, (FreeFunction)freeAndPrintKeyFromHash, (PrintFunction)prJerry, (EqualFunction)equalFuncSEJToJerrylp, (EqualFunction)equalKeyHash, (TransformIntoNumberFunction)transform, 37);
	readFromFile(path, numOfPlanets, Jerrylp, Planetlp, Jerryht, PCmvht);
	while(ch != 9)
	{
		printf("Welcome Rick, what are your Jerry's needs today ? \n");
		printf("1 : Take this Jerry away from me \n");
		printf("2 : I think I remember something about my Jerry \n");
		printf("3 : Oh wait. That can't be right \n");
		printf("4 : I guess I will take back my Jerry now \n");
		printf("5 : I can't find my Jerry. Just give me a similar one \n");
		printf("6 : I lost a bet. Give me your saddest Jerry \n");
		printf("7 : Show me what you got \n");
		printf("8 : Let the Jerries play \n");
		printf("9 : I had enough. Close this place \n");
		scanf("%s", chInString);
		if (strlen(chInString) != 1)
		{
			printf("Rick this option is not known to the daycare ! \n");
			continue;
		}
		ch = transform(chInString) - 48;
		switch( ch )
		{
			case 1:
			{
				addNewJerry(Planetlp, Jerrylp, Jerryht, PCmvht);
				break;
			}
			case 2:
			{
				char id[300];
				char name[300];
				float valueInFloat;
				Physicalcharacteristics *physicalcharacteristicsPoint;
				printf("What is your Jerry's ID ? \n");
				scanf("%s", id);
				Jerry* jerry = (Jerry *)lookupInHashTable(Jerryht, id);
				if (jerry == NULL)
				{
					printf("Rick this Jerry is not in the daycare ! \n");
					break;
				}
				printf("What physical characteristic can you add to Jerry - %s ? \n", id);
				scanf("%s", name);
				if (ifPhysicalcharacteristicExist(jerry, name))
				{
					printf("The information about his %s already available to the daycare ! \n", name);
					break;
				}
				printf("What is the value of his %s ? \n", name);
				scanf("%f", &valueInFloat);
				physicalcharacteristicsPoint = initPhysicalcharacteristics(name, valueInFloat);
				if (physicalcharacteristicsPoint == NULL)
				{
					printf("Memory Problem");
					goHome(Jerrylp, Planetlp, Jerryht, PCmvht);
					exit(1);
				}
				addPhysicalcharacteristic(jerry, physicalcharacteristicsPoint);
				if (addToMultiValueHashTable(PCmvht, name, jerry) == failure)
				{
					printf("Memory Problem");
					goHome(Jerrylp, Planetlp, Jerryht, PCmvht);
					exit(1);
				}
				displayMultiValueHashElements(PCmvht, name);
				break;
			}
			case 3:
			{
				removePhysicalCharacteristicFromJerry(Jerryht, PCmvht);
				break;
			}
			case 4:
			{
				removeJerry(Jerrylp, Jerryht, PCmvht);
				break;
			}
			case 5:
			{
				removeSimilarJerry(Jerrylp, Jerryht, PCmvht);
				break;
			}
			case 6:
			{
				removeSaddestJerry(Jerrylp, Jerryht, PCmvht);
				break;
			}
			case 7:
			{
				printf("What information do you want to know ? \n");
				printf("1 : All Jerries \n");
				printf("2 : All Jerries by physical characteristics \n");
				printf("3 : All known planets \n");
				scanf("%s", chInString);
				if (strlen(chInString) != 1)
				{
					printf("Rick this option is not known to the daycare ! \n");
					continue;
				}
				ch = transform(chInString) - 48;
				switch ( ch )
				{
					// Displays all the information for jerries in the daycare.
					case 1:
					{
						if (getlengthlist(Jerrylp) == 0)
						{
							printf("Rick we can not help you - we currently have no Jerries in the daycare ! \n");
						}
						displayList(Jerrylp);
						break;
					}
					// Displays all the information for jerries in the daycare with specific attribute.
					case 2:
					{
						char name[300];
						printf("What physical characteristics ? \n");
						scanf("%s", name);
						LinkedList pclp = (LinkedList)lookupInMultiValueHashTable(PCmvht, name);
						if (getlengthlist(pclp) == 0)
						{
							printf("Rick we can not help you - we do not know any Jerry's %s ! \n", name);
							break;
						}
						displayMultiValueHashElements(PCmvht, name);
						break;
					}
					// Displays all the information for jerries in the daycare
					case 3:
					{
						displayList(Planetlp);
						break;
					}
					default:
					{
						printf("Rick this option is not known to the daycare ! \n");
						break;
					}
				}
				break;
			}
			case 8:
			{
				if (getlengthlist(Jerrylp) == 0)
				{
					printf("Rick we can not help you - we currently have no Jerries in the daycare ! \n");
					break;
				}
				printf("What activity do you want the Jerries to partake in ? \n");
				printf("1 : Interact with fake Beth \n");
				printf("2 : Play golf \n");
				printf("3 : Adjust the picture settings on the TV \n");
				scanf("%s", chInString);
				if (strlen(chInString) != 1)
				{
					printf("Rick this option is not known to the daycare ! \n");
					continue;
				}
				ch = transform(chInString) - 48;
				switch ( ch )
				{
					case 1:
					{
						interactWithFakeBeth(Jerrylp);
						break;
					}
					case 2:
					{
						playGolf(Jerrylp);
						break;
					}
					case 3:
					{
						adjustPictureSettings(Jerrylp);
						break;
					}
					default:
					{
						printf("Rick this option is not known to the daycare ! \n");
						break;
					}
				}
				break;
			}
			case 9:
			{
				goHome(Jerrylp, Planetlp, Jerryht, PCmvht);
				break;
			}
			default:
			{
				printf("Rick this option is not known to the daycare ! \n");
				break;
			}
		}
	}
	return 0;
}
























