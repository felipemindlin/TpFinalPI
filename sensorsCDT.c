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

static int compareTotalPeople(id * sens1, id * sens2); // devuelve 1 si el id1 tiene que ir antes cuando lo ordenas o -1 si deberia ir el id2 antes
static int compareMax(id * sens1, id * sensMax); // compara la siguiente cantidad de personas en una hora dada del sensor con el record maximo. Si lo supera devuelve -1, si no devuelve 1

void newyear(sensorsADT data, int year, int hCounts){
    data->years[year-MIN_YEAR]+=hCounts;
}

int newDay(sensorsADT data, char * nameday, int time, int hCounts, int weekDay){
    day aux = data->days[weekDay];
    aux.name = strcpy(malloc(strlen(nameday) + 1), nameday);
    if (aux.name == NULL){
        return 1; //no pudo guardar en memoria, 1 para que tire error
    }
    
    aux.total += hCounts; //siempre sumo al total
    if( time >= 0 && time <= 6){ //sumo si entra en el rango horario del daycount
        aux.day += hCounts;
    } else if( time>=18 && time<24){ //idem pero con nightcount
        aux.night += hCounts;
    }
    return 0;
}

int newReading(sensorsADT data, int year, int numMonth, int monthDay, char * nameday, int weekDay, int id, int time, int hCounts, int * status){
        newID(data, id, hCounts, year, numMonth, monthDay, time); 
        if(*status){
            if(newDay(data, nameday, time, hCounts, weekDay)){
                return 1;
            }
            newyear(data, year, hCounts);
        }
        return 0;
}

void newID(sensorsADT data, int num_id, int hCounts, int year, int month, int monthDay, int time){
     id aux=data->ids[num_id-1];
     aux.total += hCounts;
     
     if(year >= data->minYear && year <= data->maxYear){
        if(aux.cant_max <= hCounts){
            //if() definir si al ser iguales tomo otro criterio o no
            aux.cant_max = hCounts;
            aux.year = year;
            aux.year = month;
            aux.day = monthDay;
            aux.hour = time;
        }
    }
    
}

int newSensor(sensorsADT data, size_t id, char * name, char status){
    data->ids[id-1].name=strcpy(malloc(strlen(name)+1), name);
    if(data->ids[id-1].name == NULL){
        return 1;
    }
    data->ids[id-1].status=status;
    return 0;    
}

static int compareTotalPeople(id * sens1, id * sens2){
  int resp;
    if((resp=sens2->total - sens1->total)==0){
        return strcmp(sens1->name, sens2->name);
    }
    return resp;
}

static int compareMax(id * sens1, id * sens2){
    int resp;
    if((resp=sens2->cant_max - sens1->cant_max)==0){
        return strcmp(sens1->name, sens2->name);
    }
    return resp;
}

void orderQ1(sensorsADT data){
    qsort(data->ids, IDS, sizeof(id), (int (*) (const void *, const void *))compareTotalPeople);
} 
void orderQ4(sensorsADT data){
    qsort(data->ids, IDS, sizeof(id), (int (*) (const void *, const void *))compareMax);
}

void freeALL(sensorsADT data){
    for(int i=0; i<IDS; i++){
        free(data->ids[i].name);
    }
    for(int i=0; i<DAYS; i++){
        free(data->days[i].name);
    }
    free(data);
}

 int isActive(sensorsADT data, int id){
    if(data->ids[id-1].status == 'A'){
        return 1;
    }
    return 0;
}

char * getName(sensorsADT data, int idx){
    return data->ids[idx].name;
}
size_t getTotal(sensorsADT data, int idx){
    return data->ids[idx].total;
}

size_t getDataByYear(sensorsADT data, int idx){
    return data->years[idx];
}

char * getDayName(sensorsADT data, int idx){
    return data->days[idx].name;
} 

size_t getDataDay(sensorsADT data, int idx){
    return data->days[idx].day;
}

size_t getDataNight(sensorsADT data, int idx){
    return data->days[idx].night;
}

size_t getDataTotal(sensorsADT data, int idx){
    return data->days[idx].total;
} 

size_t getMax(sensorsADT data, int idx){
    return data->ids[idx].cant_max;
}

int getHour(sensorsADT data, int idx){
   return data->ids[idx].hour;
}

int getDay(sensorsADT data, int idx){
    return data->ids[idx].day;
}

int getMonth(sensorsADT data, int idx){
    return data->ids[idx].month;
}

int getYear(sensorsADT data, int idx){
    return data->ids[idx].year;
}
