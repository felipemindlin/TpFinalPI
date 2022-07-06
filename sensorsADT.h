#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#define DELIM ";"
#define MIN_YEAR 2009
#define IDS 85
#define DAYS 7
#define ACTUAL_YEAR 2022
typedef struct sensorsCDT * sensorsADT;


void orderQ1(sensorsADT data); // funcion que ordena de manera eficiente para devolver en el orden pedidio para el Query 1

void orderQ4(sensorsADT data); // funcion que ordena de manera eficiente para devolver en el orden pedidio para el Query 4



sensorsADT newSensorsADT(size_t minYear, size_t maxYear);

void newyear(sensorsADT data, int year, int hCounts);

int newDay(sensorsADT data, char * nameday, int time, int hCounts, int weekDay);

int newReading(sensorsADT data, int year, int numMonth, int monthDay, char * nameday, int weekDay, int id, int time, int hCounts, int * status);

void newID(sensorsADT data, int num_id, int hCounts, int year, int month, int monthDay, int time);

int newSensor(sensorsADT data, size_t id, char * name, char status);


void orderQ1(sensorsADT data);
void orderQ4(sensorsADT data);

void freeALL(sensorsADT data);