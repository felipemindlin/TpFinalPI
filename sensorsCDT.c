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
    size_t years[YEARS]; // suma total por año
}sensorsCDT;


sensorsADT newSensorsADT(){
    sensorsADT new = calloc(1, sizeof(sensorsCDT)); //reservamos memoria para el TAD
    if(setDays(new)){ //si setDays retorna 1, no hay memoria para guardar los dias
        free(new);      //libera memoria reservada para el TAD y retorna NULL;
        return NULL;
    }
    return new; 
}

static int compareTotalPeople(id * sens1, id * sens2); // Funcion de comapre para ordenar para el Q1
static int compareMax(id * sens1, id * sensMax); // idem pero con Q4

void newyear(sensorsADT data, int year, int hCounts){ //suma los count por año
    data->years[year-MIN_YEAR]+=hCounts;
}

int setDays(sensorsADT data){
    char *days[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    int i = 0;
    day * aux = &data->days[i];
    for(i = 0; i < DAYS; i++){
        aux = &data->days[i];
        aux->name = strcpy(malloc(strlen(days[i]) + 1), days[i]);
        if (aux->name == NULL){
            return 1; //no pudo guardar en memoria, retorna 1 para que tire error
            }
    }
    return 0;
}

int newDay(sensorsADT data, int time, int hCounts, int weekDay){
    day * aux = &data->days[weekDay];
    
    aux->total += hCounts; //siempre sumo al total
    if( (time>=18 && time<24) || (time >= 0 && time < 6)){ //sumo si entra en el rango horario del daycount
        aux->night += hCounts;
    } else { //idem pero con nightcount
        aux->day += hCounts;
    }
    return 0;
}

int newReading(sensorsADT data, int year, int min, int max, int numMonth, int monthDay, int weekDay, int id, int time, int hCounts, int * status){
        if(*status){ // si esta activo agrego sino no
            newID(data, id, hCounts, year, min, max, numMonth, monthDay, time); //agregamos los datos en la struct id
            if(newDay(data, time, hCounts, weekDay)){ // agregamos los datos en la estructura day
                return 1; // sino pudo reservar retrono 1 
            }
            newyear(data, year, hCounts); // suma al total por año
        }
        return 0; // indico que no hubo error al reservar memoria 
}

void newID(sensorsADT data, int num_id, int hCounts, int year, int min, int max, int month, int monthDay, int time){
     id * aux=&data->ids[num_id-1]; // hacemos un aux  para no tener que escribir data->ids[num_id-1]. en todos los casos
     aux->total += hCounts; // suma en el total del id la medicion de la lectura actual
 
    if(year >= min && year <= max && aux->cant_max <= hCounts){ // chequeamos que esten entre el intervalo de los args dados
        aux->cant_max = hCounts; // si esta en el intervalo gaurda los datos relevantes para el Q4
        aux->year = year; //guarda el año de la medicion max
        aux->month = month; // idem con el mes
        aux->day = monthDay; // idem con el dia del mes
        aux->hour = time; // idem con la hora
    }
    
}


int newSensor(sensorsADT data, size_t id, char * name, char status){
    data->ids[id-1].name=strcpy(malloc(strlen(name)+1), name); //reservamos memoria y copiamos el nombre del sensor
    if(data->ids[id-1].name == NULL){ //Corroboramos que haya podido reservar memoria
        return 1; // retorna 1 si no pudo reservar memoria
    }
    data->ids[id-1].status=status; // guardamos el status 'A' o 'R'
    return 0;   //retorna 0 si hizo todo sin problema
}

static int compareTotalPeople(id * sens1, id * sens2){
  int resp;
    if((resp=sens2->total - sens1->total)==0){ // comparamos el total si es el mismo comparamos alfabeticamnte los nombres
        if(sens1->name!=NULL && sens2->name!=NULL){ //chequeamos que no estemos comparando con NULL por si hay un sensor vacio
            return strcmp(sens1->name, sens2->name); 
        }
    }
    return resp; // sino eran iguales retorna sens2->total - sens1->total
}

static int compareMax(id * sens1, id * sens2){
    int resp;
    if((resp=sens2->cant_max - sens1->cant_max)==0){ //idem compareTotalPeople pero con cant_max
        if(sens1->name!=NULL && sens2->name!=NULL){
            return strcmp(sens1->name, sens2->name);
        }    
    }
    return resp;
}

void orderQ1(sensorsADT data){ //ordena con el vector de ids con compareTotalPeople como funcion para decidir el orden
    qsort(data->ids, IDS, sizeof(id), (int (*) (const void *, const void *))compareTotalPeople); // ordena para lo pedido en Q1
} 
void orderQ4(sensorsADT data){ // idem anterior pero con compareMax y ordena para Q4
    qsort(data->ids, IDS, sizeof(id), (int (*) (const void *, const void *))compareMax);
}

void freeALL(sensorsADT data){ // libera toda la memoria reservada dentro del TAD luego libera el TAD
    for(int i=0; i<IDS; i++){ //recorre el vec ids y libera el name para cada uno
        free(data->ids[i].name);
    }
    for(int i=0; i<DAYS; i++){ // idem anterior pero con los dias dentro del vec days
         free(data->days[i].name);
    }
    free(data); // libera el TAD
}

 int isActive(sensorsADT data, int id){ 
    if(data->ids[id-1].status == 'A'){ // se fija si el sensor esta activo
        return 1; // si esta activo retorna 1 
    }
    return 0; // sino retorna 0
}

char * getName(sensorsADT data, int idx){
    return data->ids[idx].name; // devuelve el nombre del sensor en la posicion idx
}
size_t getTotal(sensorsADT data, int idx){
    return data->ids[idx].total; // devuelve el total del sensor en la posicion idx
}

size_t getDataByYear(sensorsADT data, int idx){
    return data->years[idx]; // devuelve el total del año en la posicion idx
}

char * getDayName(sensorsADT data, int idx){
    return data->days[idx].name; // devuelve el el dia de la posicion idx
} 

size_t getDataDay(sensorsADT data, int idx){
    return data->days[idx].day; // devuelve el day count del dia en la posicion idx
}

size_t getDataNight(sensorsADT data, int idx){
    return data->days[idx].night; // devuelve el night count del dia en la posicion idx
}

size_t getDataTotal(sensorsADT data, int idx){
    return data->days[idx].total; // devuelve el total count del dia en la posicion idx
} 

size_t getMax(sensorsADT data, int idx){
    return data->ids[idx].cant_max; // devuelve el cant_max del dia en la posicion idx
}

int getHour(sensorsADT data, int idx){
   return data->ids[idx].hour;  // devuelve la hora de la medicion maxima del id en la posicion idx
}

int getDay(sensorsADT data, int idx){
    return data->ids[idx].day; //devuelve el dia de la medicion maxima del id en la posicion idx
}

int getMonth(sensorsADT data, int idx){
    return data->ids[idx].month; // devuelve el mes de la medcion maxima del id en la posicion idx
}

int getYear(sensorsADT data, int idx){
    return data->ids[idx].year; // devuelve el año de la medicion maxima del id en la posicion idx
}
