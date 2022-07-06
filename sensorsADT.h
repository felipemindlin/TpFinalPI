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
int isActive(sensorsADT data, int id);  // devuelve 1 si el sensor esta activo o 0 si esta inactivo

void orderQ1(sensorsADT data);
void orderQ4(sensorsADT data);

void freeALL(sensorsADT data);

int addSensor(sensorsADT data, char * string);

int addReading(sensorsADT data, char * string, int min, int max);


char * getName(sensorsADT data, int idx);
size_t getTotal(sensorsADT data, int idx);

size_t getDataByYear(sensorsADT data, int idx);

char * getDayName(sensorsADT data, int idx);

size_t getDataDay(sensorsADT data, int idx);

size_t getDataNight(sensorsADT data, int idx);

size_t getDataTotal(sensorsADT data, int idx);

size_t getMax(sensorsADT data, int idx);

int getHour(sensorsADT data, int idx);

int getDay(sensorsADT data, int idx);

int getMonth(sensorsADT data, int idx);

int getYear(sensorsADT data, int idx);