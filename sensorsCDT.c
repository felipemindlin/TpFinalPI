#include "sensorsADT.h"

typedef struct id{
    size_t total; // suma total de todas las mediciones del sensor
    char *name; // nombre del sensor
    char status; //estado del sensor "A" o "R"
    size_t cant_max; // cantidad maxima para comparar 
    unsigned int hour;  // hora con max cant
    unsigned int day; //dia con max cant
    unsigned int month; //mes con max cant
    unsigned int year; //año con max cant
}id;


typedef struct day{
    char *name; // nombre del dia 
    size_t day;  // suma total de las 0 a las 6 h
    size_t night; // suma total de las 18 a 0 h
    size_t total; // suma total de las 24h 
}day;

typedef struct sensorsCDT{
    day days[DAYS]; // vector de los dias de la semana.
    id ids[IDS]; // vector de todos los sensores
    size_t years[ACTUAL_YEAR-MIN_YEAR]; // suma total por año
    size_t minYear; //cant de años      // preguntar a Pipe si en vez de tener un dim, guardamos el max y min de los years.
    size_t maxYear;
}sensorsCDT;


sensorsADT newSensorsADT(){
    return calloc(1, sizeof(sensorsCDT));
}
// ./pedestrians data1 data2 año1 año2

int compare(int id1, char * sens1, int id2, char * sens2); // devuelve 1 si el id1 tiene que ir antes cuando lo ordenas o -1 si deberia ir el id2 antes


int newReading(sensorsADT data, int year, int numMonth, int day, char * nameday, int weekDay, int id, int time, int hCounts, int * flag){

     
    
}

static int compareTotalPeople(id sens1, id sens2){
    if(sens1->total > sens2->total)
        return 1;
    else if(sens1->total < sens2->total)
        return -1;
    else{   // son iguales
        if(strcmp(sens1->name, sens2->name) < 0)
            return 1;
        return -1;
    }
    return 0;
}

// preguntarle a Pipe si tengo que hacer otra o con esta funcion puedo hacer el Q4