
#include "sensorsADT.h"

typedef struct id{
    size_t total; // suma total de todas las mediciones del sensor
    char *name; // nombre del sensor
    char c; // estado del sensor "A", "R",
    size_t cant_max; // cantidad maxima para comparar 
    unsigned int hour; //dia con max cant
    unsigned int day; // hora con max cant
    unsigned int month; //mes con max cant
    unsigned int year; //año con max cant
}id;

typedef struct day{
    size_t day;  // suma total de las 0 a las 6 h
    size_t night; // suma total de las 18 a 0 h
    size_t total; // suma total de las 24h 
}day;

typedef struct SensorsCDT{
    day days[DAYS]; // vector de los dias de la semana.
    id ids[IDS]; // vector de todos los sensores
    size_t * years; // suma total por año
}SensorsCDT;

