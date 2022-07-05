#include "sensorsADT.h"

enum days{Mon = 0, Tue, Wed, Thur, Fri, Sat, Sun};
enum months{Jan = 1, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec};

// Year;Month;Mdate;Day;Sensor_ID;Time;Hourly_Counts
int days(char * token); // convierte los dias de la semana a numeros del 0 al 6

int months(char * token); // convierte los meses a numeros del 1 al 12

int isActive(sensorsADT data, int id);  // devuelve 1 si el sensor esta activo o 0 si esta inactivo

// 2018 - 2022
void addReading(sensorsADT data, char * string){
    char * token;
    int month = -1;
    int monthDay = -1;
    int flag = 0;

    token = strtok(string, DELIM); 
    int year = atoi(token); // year
    

    if(year >= data->minYear && year <= data->maxYear){
        flag = 1;
    }  

    token = strtok(NULL, DELIM); 
    if(flag){
        month = months(token); // month
    }
        

    token = strtok(NULL, DELIM); 
    if(flag){
        monthDay = atoi(token); // mDate
    }
    

    token = strtok(NULL, DELIM); 
    
    char * nameday = token; //guardamos el nombre del dia
    int weekDay = days(token); // el dia como numero del 0 al 6

    token = strtok(NULL, DELIM); // sensor_id
    int id = atoi(token);
    
    token = strtok(NULL, DELIM); 
    int time = atoi(token); // time

    token = strtok(NULL, DELIM); 
    int hCounts = atoi(token); // hourly_counts 
    
    int flag = isActive(data, id);
    //FALTA LLAMAR A LAS FUNCIONES QUE AGREGUEN LA INFO AL TAD
    return newReading(data, year, month, monthDay, nameday, weekDay, id, time, hCounts, &flag);
    
}

int days(char * token){
    int n=2; // comparamos los primeros dos caracteres para ver que dia de la semana es 
    if(strncmp(token, "Mo", n)==0) return Mon;
    if(strncmp(token, "Tu", n)==0) return Tue;
    if(strncmp(token, "We", n)==0) return Wed;
    if(strncmp(token, "Th", n)==0) return Thur;
    if(strncmp(token, "Fr", n)==0) return Fri;
    if(strncmp(token, "Sa", n)==0) return Sat;
    if(strncmp(token, "Su", n)==0) return Sun;
    return -1;
}

int months(char * token){
   int n = 3; //para comparar primeros 3 caracteres del mes (diferenciar march-may, june-july)
   if(strncmp(token, "Jan", n)==0) return Jan;
   if(strncmp(token, "Feb", n)==0) return Feb;
   if(strncmp(token, "Mar", n)==0) return Mar;
   if(strncmp(token, "Apr", n)==0) return Apr;
   if(strncmp(token, "May", n)==0) return May;
   if(strncmp(token, "Jun", n)==0) return Jun;
   if(strncmp(token, "Jul", n)==0) return Jul;
   if(strncmp(token, "Aug", n)==0) return Aug;
   if(strncmp(token, "Sep", n)==0) return Sep;
   if(strncmp(token, "Oct", n)==0) return Oct;
   if(strncmp(token, "Nov", n)==0) return Nov;
   if(strncmp(token, "Dec", n)==0) return Dec;
   return -1;
}   

int isActive(sensorsADT data, int id){
    if(data->ids[id-1].status == 'A'){
        return 1;
    }
    return 0;
}

int addSensor(sensorsADT data, const char * string){
    char * token;

    token = strtok(string, DELIM);
    int id = atoi(token); //obtiene id del sensor

    token = strtok(NULL, DELIM);
    char *name = token; //guardamos nombre sensor

    token = strtok(NULL, DELIM);
    char status = token;
    
    return newSensor(data, id, name, status);
}
    


