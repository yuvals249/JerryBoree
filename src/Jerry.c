#include "Jerry.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// The function creates the structure Jerry.
// The function returns null if there are memory problem with the mallocs
Jerry* initJerry(char *id, int happiness, Planet *planet, char *dimension)
{
	Jerry *jerryPointer;
	jerryPointer = (Jerry *)malloc(sizeof(Jerry));
	if (jerryPointer == NULL)
	{
		return NULL;
	}
	jerryPointer->id = (char *)malloc(strlen(id) + 1);
	if (jerryPointer->id == NULL)
	{
		destroyJerry(jerryPointer);
		return NULL;
	}
	strcpy(jerryPointer->id, id);
	jerryPointer->happiness = happiness;
	jerryPointer->origin = initOrigin(planet, dimension);
	if (jerryPointer->origin == NULL)
	{
		destroyJerry(jerryPointer);
		return NULL;
	}
	jerryPointer->physicalcharacteristics = NULL;
	jerryPointer->size_of_physicalcharacteristics = 0;
	return jerryPointer;
}

// The function received jerry and destroys it.
void destroyJerry(Jerry *jerry)
{
	free(jerry->id);
	destroyOrigin(jerry->origin);
	for(int i = 0; i < jerry->size_of_physicalcharacteristics; i++)
		destroyPhysicalcharacteristics(jerry->physicalcharacteristics[i]);
	free(jerry->physicalcharacteristics);
	free(jerry);
}

// The function creates the structure Planet.
// The function returns null if there are memory problem with the mallocs
Planet* initPlanet(char *name, float x, float y, float z)
{
	Planet *planetPointer;
	planetPointer = (Planet *)malloc(sizeof(Planet));
	if (planetPointer == NULL)
	{
		return NULL;
	}
	planetPointer->name = (char *)malloc(strlen(name) + 1);
	if (planetPointer->name == NULL)
	{
		destroyPlanet(planetPointer);
		return NULL;
	}
	strcpy(planetPointer->name, name);
	planetPointer->x = x;
	planetPointer->y = y;
	planetPointer->z = z;
	return planetPointer;
}

// The function received planet and destroys it.
void destroyPlanet(Planet *planet)
{
	free(planet->name);
	free(planet);
}

// The function creates the structure physical characteristics.
// The function returns null if there are memory problem with the mallocs
Physicalcharacteristics* initPhysicalcharacteristics(char *name, float value)
{
	Physicalcharacteristics *physicalcharacteristicsPoint;
	physicalcharacteristicsPoint = (Physicalcharacteristics *)malloc(sizeof(Physicalcharacteristics));
	if (physicalcharacteristicsPoint == NULL)
	{
		return NULL;
	}
	physicalcharacteristicsPoint->name = (char *)malloc(strlen(name) + 1);
	if (physicalcharacteristicsPoint->name == NULL)
	{
		destroyPhysicalcharacteristics(physicalcharacteristicsPoint);
		return NULL;
	}
	strcpy(physicalcharacteristicsPoint->name, name);
	physicalcharacteristicsPoint->value = value;
	return physicalcharacteristicsPoint;
}

// The function received physical characteristics list and destroys it.
void destroyPhysicalcharacteristics(Physicalcharacteristics *physicalcharacteristics)
{
	free(physicalcharacteristics->name);
	free(physicalcharacteristics);
}

// The function creates the structure origin.
// The function returns null if there are memory problem with the mallocs
Origin* initOrigin(Planet *planet, char *dimension)
{
	Origin *originPointer;
	originPointer = (Origin *)malloc(sizeof(Origin));
	if (originPointer == NULL)
	{
		return NULL;
	}
	originPointer->dimension = (char *)malloc(strlen(dimension) + 1);
	if (originPointer->dimension == NULL)
	{
		destroyOrigin(originPointer);
		return NULL;
	}
	strcpy(originPointer->dimension, dimension);
	originPointer->planet = planet;
	return originPointer;
}

// The function received origin and destroys it.
void destroyOrigin(Origin *origin)
{
	free(origin->dimension);
	free(origin);
}

// The function received jerry and name of physical characteristic and check if it exists in this jerry.
//The function returns true if that founded or false either.
bool ifPhysicalcharacteristicExist(Jerry *jerry, char *name)
{
	for(int i = 0; i < jerry->size_of_physicalcharacteristics; i++)
		if (strcmp(jerry->physicalcharacteristics[i]->name, name) == 0)
			return true;
	return false;
}

// The function received jerry and physical characteristic and adds it to the end of jerry's physical characteristics list.
void addPhysicalcharacteristic(Jerry *jerry, Physicalcharacteristics *physicalcharacteristic)
{
	jerry->physicalcharacteristics = (Physicalcharacteristics **)realloc(jerry->physicalcharacteristics, sizeof(Physicalcharacteristics) * (jerry->size_of_physicalcharacteristics + 1));
	jerry->physicalcharacteristics[jerry->size_of_physicalcharacteristics] = physicalcharacteristic;
	jerry->size_of_physicalcharacteristics++;
}


// The function received jerry and name of physical characteristic and removed it from this jerry.
// The function returns success if the action succeed or failure either (this physical characteristic does not exists in this jerry).
status removePhysicalcharacteristicByName(Jerry *jerry, char *name)
{
	Physicalcharacteristics *pointerToRemove;
	if (!ifPhysicalcharacteristicExist(jerry, name))
		return failure;
	if (strcmp(jerry->physicalcharacteristics[jerry->size_of_physicalcharacteristics - 1]->name, name) == 0)
	{
		destroyPhysicalcharacteristics(jerry->physicalcharacteristics[jerry->size_of_physicalcharacteristics - 1]);
		jerry->size_of_physicalcharacteristics--;
		jerry->physicalcharacteristics = (Physicalcharacteristics **)realloc(jerry->physicalcharacteristics, jerry->size_of_physicalcharacteristics * sizeof(Physicalcharacteristics));
		return success;
	}

	for(int i = 0; i < jerry->size_of_physicalcharacteristics - 1; i++)
	{
		if (jerry->size_of_physicalcharacteristics == 2)
		{
			pointerToRemove = jerry->physicalcharacteristics[i];
			jerry->physicalcharacteristics[i] = jerry->physicalcharacteristics[i + 1];
			break;
		}
		else
		{
			if ((strcmp(jerry->physicalcharacteristics[i]->name, name) == 0) && (jerry->size_of_physicalcharacteristics != 2))
			{
				pointerToRemove = jerry->physicalcharacteristics[i];
				jerry->physicalcharacteristics[i] = jerry->physicalcharacteristics[i + 1];
			}
			if (i != 0 && jerry->physicalcharacteristics[i]->name == jerry->physicalcharacteristics[i - 1]->name)
				jerry->physicalcharacteristics[i] = jerry->physicalcharacteristics[i + 1];
		}
	}
	destroyPhysicalcharacteristics(pointerToRemove);
	jerry->size_of_physicalcharacteristics--;
	jerry->physicalcharacteristics = (Physicalcharacteristics **)realloc(jerry->physicalcharacteristics, jerry->size_of_physicalcharacteristics * sizeof(Physicalcharacteristics));
	return success;
}

// The function received jerry and prints the information about it.
// The function returns success if the jerry we received is legal ( type of jerry) or failure if null.
status printJerry(Jerry *jerry)
{
	if (jerry == NULL)
	{
		printf("jerry is null");
		return failure;
	}
	printf("Jerry , ID - %s : \n",jerry->id);
	printf("Happiness level : %d \n",jerry->happiness);
	printf("Origin : %s \n",jerry->origin->dimension);
	printPlanet(jerry->origin->planet);
	if (jerry->size_of_physicalcharacteristics > 0)
	{
		printf("Jerry's physical Characteristics available : \n\t");
		for (int i = 0; i < jerry->size_of_physicalcharacteristics; i++)
		{
			if (i == 0)
				printf("%s : %.2f",jerry->physicalcharacteristics[i]->name,jerry->physicalcharacteristics[i]->value);
			else
				printf(" , %s : %.2f",jerry->physicalcharacteristics[i]->name,jerry->physicalcharacteristics[i]->value);
		}
		printf(" \n");
	}
	return success;
}

// The function received planet and prints the information about it.
// The function returns success if the planet we received is legal ( type of planet) or failure if null.
status printPlanet(Planet *planet)
{
	if (planet == NULL)
	{
		printf("planet is null");
		return failure;
	}
	printf("Planet : %s (%.2f,%.2f,%.2f) \n",planet->name,planet->x,planet->y,planet->z);
	return success;
}

