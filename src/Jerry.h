#ifndef JERRY_H_
#define JERRY_H_
#include "Defs.h"

// Declare the attributes for the structure planet.
typedef struct Planet_t
{
	char *name;
	float x,y,z;
}Planet;

// Declare the attributes for the structure origin.
typedef struct Origin_t
{
	Planet *planet;
	char *dimension;
}Origin;

// Declare the attributes for the structure physical characteristic.
typedef struct Physicalcharacteristics_t
{
	char *name;
	float value;
}Physicalcharacteristics;

// Declare the attributes for the structure jerry.
typedef struct Jerry_t
{
	char *id;
	int happiness;
	Origin *origin;
	Physicalcharacteristics **physicalcharacteristics;
	int size_of_physicalcharacteristics;
}Jerry;


// All the decelerations of the functions in this module.

// The function receives char* for id, int for happiness, pointer to planet, and char* for dimension and create the structure Jerry and return it.
Jerry* initJerry(char *, int, Planet *, char *);
// The function receives pointer to jerry and destroys it.
void destroyJerry(Jerry *);
// The function receive char* for name, and 3 floats for his location and create the structure Planet and return it.
Planet* initPlanet(char *, float, float, float);
// The function received pointer to planet and destroys it.
void destroyPlanet(Planet *);
// The function receives char* for name, and value for his physical characteristic and create the structure Physicalcharacteristics and return it.
Physicalcharacteristics* initPhysicalcharacteristics(char *, float);
// The function receives pointer to Physicalcharacteristics and destroys it.
void destroyPhysicalcharacteristics(Physicalcharacteristics *);
// The function receives pointer to Planet, and char* for his dimension and create the structure Origin and return it.
Origin* initOrigin(Planet *, char *);
// The function receives pointer to origin and destroys it.
void destroyOrigin(Origin *);
// The function receives pointer to jerry and name of physical characteristic and return if it exists in this jerry.
bool ifPhysicalcharacteristicExist(Jerry *, char *);
// The function receives pointer to jerry and pointer to physical characteristic and adds it to the end of jerry's physical characteristics list.
void addPhysicalcharacteristic(Jerry *, Physicalcharacteristics *);
// The function receives pointer to jerry and name of physical characteristic and removed it from this jerry.
// The function returns success if the action succeed or failure either (this physical characteristic does not exists in this jerry).
status removePhysicalcharacteristicByName(Jerry *, char *);
// The function receives pointer to jerry and prints the information about it.
// The function returns success if the jerry we received is legal ( type of jerry) or failure if null.
status printJerry(Jerry *);
// The function receives pointer to planet and prints the information about it.
// The function returns success if the planet we received is legal ( type of planet) or failure if null.
status printPlanet(Planet *);

#endif /* JERRY_H_ */


