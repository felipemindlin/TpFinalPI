#include "sensorsADT.h"

typedef struct id{
    size_t total; // suma total de todas las mediciones del sensor
    char * name; // nombre del sensor
    char status; //estado del sensor "A" o "R"
    size_t cant_max; // cantidad maxima para comparar 
    unsigned int hour;  // hora con max cant
    unsigned int day; //dia con max cant
    unsigned int month; //mes con max cant
    unsigned int year; //año con max cant
}id;


typedef struct day{
    char * name; // nombre del dia 
    size_t day;  // suma total de las 0 a las 6 h
    size_t night; // suma total de las 18 a 0 h
    size_t total; // suma total de las 24h 
}day;

typedef struct sensorsCDT{
    day days[DAYS]; // vector de los dias de la semana.
    id ids[IDS]; // vector de todos los sensores
    size_t years[ACTUAL_YEAR-MIN_YEAR]; // suma total por año
    size_t minYear; 
    size_t maxYear;
}sensorsCDT;


sensorsADT newSensorsADT(size_t minYear, size_t maxYear){
    sensorsADT new=calloc(1, sizeof(sensorsCDT));
    new->minYear=minYear;
    new->maxYear=maxYear;
    return new;
}

static int compareTotalPeople(id sens1, id sens2); // devuelve 1 si el id1 tiene que ir antes cuando lo ordenas o -1 si deberia ir el id2 antes
static int compareMax(id sens1, id sensMax); // compara la siguiente cantidad de personas en una hora dada del sensor con el record maximo. Si lo supera devuelve -1, si no devuelve 1


int newReading(sensorsADT data, int year, int numMonth, int day, char * nameday, int weekDay, int id, int time, int hCounts, int * status){
    if(status){
        newID(&data->ids, id, hCounts, year, numMonth, day, time) // recibe sensor, id
        newday() 
        newyear()
    }
    
}

void newID(id * sensor, int num_id, int hCounts, int year, int month, int day, int time){
     id aux=sensor[num_id-1];
     
     if(aux.cant_max <= hCounts){
        if()
        aux.cant_max = hCounts;
        aux.year = year;
        aux.year = month;
        aux.day = day;
        aux.hour = time;
        
        }
    
}

int newSensor(sensorsADT data, size_t id, char * name, char status){
    id aux=data->ids[id-1];
    aux->name=strcpy(malloc(strlen(name)+1), name);
    if(aux->name == NULL){
        return 1;
    }
    aux->status=status;
    return 0;    
}

static int compareTotalPeople(id * sens1, id * sens2){
  int resp;
    if((resp=sens2->total - sens1->total)==0){
        return strcmp(sens1->name, sens2->name)
    }
    return resp;
}

static int compareMax(id * sens1, id * sens2){
    int resp;
    if((resp=sen2->cant_max - sens1->cant_max)==0){
        return strcmp(sens1->name, sens2->name)
    }
    return resp;
}

void orderQ1(sensorsADT data){
    qsort(data->ids, IDS, sizeof(id), (int (*) (const void *, const void *))compareTotalPeople);
} 
void orderQ4(sensorsADT data){
    qsort(data->ids, IDS, sizeof(id), (int (*) (const void *, const void *))compareMax);
}
