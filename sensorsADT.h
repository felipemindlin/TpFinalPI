#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <errno.h>

#define DELIM ";"
#define MIN_YEAR 2009
#define IDS 86
#define DAYS 7
#define ACTUAL_YEAR 2022
typedef struct sensorsCDT * sensorsADT;

/*
* funcion que ordena de manera eficiente para devolver en el orden pedidio para el Query 1
*/
void orderQ1(sensorsADT data);

/*
* funcion que ordena de manera eficiente para devolver en el orden pedidio para el Query 4
*/
void orderQ4(sensorsADT data); 

/*
* Crea un TAD nuevo vacío. Recibe el año míninimo y máximo de mediciones a tener en cuenta. 
* (Útiles para el query 3)
*/
sensorsADT newSensorsADT(size_t minYear, size_t maxYear);

/*
* Recibe el TAD, el año de mediciones y la medición particular.
* Suma en el vector years al total de mediciones por año la medición recibida.
*/
void newyear(sensorsADT data, int year, int hCounts);

/*
* Recibe el TAD, nombre del día, hora y número de día de medición, y
* retorna 1 si no pudo guardar en memoria, 0 en caso contrario.
* Si guarda en memoria, suma al total del día.
* También si time está entre 0 y 6 (horas): suma en day en vector days
* Si time está entre 18 y 23 (horas): suma en night en vector days
*/
int newDay(sensorsADT data, char * nameday, int time, int hCounts, int weekDay);

/*
* Recibe el TAD, año, número y día de mes, nombre y numero del día de semana,
* un id de sensor, una hora, una medición y un flag indicando el estado del sensor.
* Llama a newID.
* Si el flag está prendido, llama a newDay y si pudo guardar en memoria, llama a newyear, si no retorna 1.
* En caso de poder guardar todo, retorna 0, indicando que no hubo problemas en memoria.
*/
int newReading(sensorsADT data, int year, int numMonth, int monthDay, char * nameday, int weekDay, int id, int time, int hCounts, int * status);

/*
* Recibe el TAD, un id de sensor, una medición, un año, un mes, un día del mes y una hora.
* En el vector de sensores, en el sensor particular, suma al total de mediciones.
* Si el año esta dentro del intervalo de año minímo y máximo, agrega datos de fecha en
* la cantidad maxima de mediciones del sensor.
*/
void newID(sensorsADT data, int num_id, int hCounts, int year, int month, int monthDay, int time);

/* 
* Recibe TAD, id, nombre y estado de sensor.
* Copia nombre en estructura, verifica si pudo reservar memoria, si no pudo retorna 1.
* Si pudo, agrega el estado del sensor, luego retorna 0.
*/
int newSensor(sensorsADT data, size_t id, char * name, char status);

/*
* Retorna 1 si el sensor esta activo, 0 si no.
*/
int isActive(sensorsADT data, int id);  

/*
* Recibe TAD y libera la memoria reservada para los nombres
* en vector de días y vector de sensores.
*/
void freeALL(sensorsADT data);

/*
* Recibe el TAD y linea del archivo.
* Interpreta los datos de la linea y llama a la función newSensor.
* Retorna el valor que retorne newSensor. 1 si no pudo reservar memoria, 0 en caso contrario.
*/
int addSensor(sensorsADT data, char * string);

/*
* Recibe el TAD, línea del archivo, minimo y maximo de años.
* Incializa en -1 las variables month, monthDay y en 0 un flag.
* Interpreta la linea y guarda en variables los datos de la medición.
* Si el año que lee de la línea está entre el mínimo y máximo de años, prende el flag.
* Si el flag está prendido guarda en month y monthDay los datos de la medición.
* Siempre guarda en weekDay, id, time, hCounts y status los datos de la medición.
* LLama a newReading y retorna lo que devuelva la misma. 1 si no pudo reservar memoria y 0 si pudo.
*/
int addReading(sensorsADT data, char * string, int min, int max);

/* 
* Recibe el TAD y un idx y retorna el nombre del sensor
*/
char * getName(sensorsADT data, int idx);

/* 
* Recibe el TAD y un idx y retorna la cantidad de mediciones en un año
*/
size_t getTotal(sensorsADT data, int idx);

/*
*Devuelve la suma total de mediciones del año idx+MIN_YEAR.
*/
size_t getDataByYear(sensorsADT data, int idx);

/* 
* Recibe el TAD y un idx y retorna el nombre del dia
*/
char * getDayName(sensorsADT data, int idx);

/* 
* Recibe el TAD y un idx y retorna la cantidad de mediciones que obtuvo entre las 0 y 6(horas)
*/
size_t getDataDay(sensorsADT data, int idx);

/* 
* Recibe el TAD y un idx y retorna la cantidad de mediciones que obtuvo entre las 18 y 23(horas)
*/
size_t getDataNight(sensorsADT data, int idx);

/* 
* Recibe el TAD y un idx y retorna la cantidad de mediones que obtuvo en un dia
*/
size_t getDataTotal(sensorsADT data, int idx);

/* 
* Recibe el TAD y un idx y retorna la maxima medicion que obtuvo un sensor en una hora
*/
size_t getMax(sensorsADT data, int idx);

/* 
* Recibe el TAD y un idx y retorna la hora
*/
int getHour(sensorsADT data, int idx);

/* 
* Recibe el TAD y un idx y retorna el dia
*/
int getDay(sensorsADT data, int idx);

/* 
* Recibe el TAD y un idx y retorna el mes
*/
int getMonth(sensorsADT data, int idx);

/* 
* Recibe el TAD y un idx y retorna el año
*/
int getYear(sensorsADT data, int idx);