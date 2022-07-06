#include "sensorsADT.h"

enum days{Mon = 0, Tue, Wed, Thur, Fri, Sat, Sun};
enum months{Jan = 1, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec};

// Year;Month;Mdate;Day;Sensor_ID;Time;Hourly_Counts
static int days(char * token); // convierte los dias de la semana a numeros del 0 al 6

static int months(char * token); // convierte los meses a numeros del 1 al 12



int addReading(sensorsADT data, char * string, int min, int max){
    char * token;
    int month = -1;
    int monthDay = -1;
    int flag = 0;

    token = strtok(string, DELIM); 
    int year = atoi(token); // year
    

    if(year >= min && year <= max){
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
    
    int status = isActive(data, id);
    //FALTA LLAMAR A LAS FUNCIONES QUE AGREGUEN LA INFO AL TAD
    return newReading(data, year, month, monthDay, nameday, weekDay, id, time, hCounts, &status);
    
}

static int days(char * token){
    int n=2; // comparamos los primeros dos caracteres para ver que dia de la semana es 
    char *weekDay[] = {"Mo", "Tu", "We", "Th", "Fr", "Sa", "Su"};
    for(int i = 0; i < (sizeof(weekDay)/sizeof(weekDay[0])); i++){
        if(strncmp(token, weekDay[i], n)==0){
            return i;
        }
    }
    return -1;
}

static int months(char * token){
   int n = 3; //para comparar primeros 3 caracteres del mes (diferenciar march-may, june-july)
   char * monthsVec[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
   int i=0; // n letras necesarias para diferenciar los meses
   while(strncmp(token, monthsVec[i], n) != 0){
        i++;
   }
   return i + 1;
}   



int addSensor(sensorsADT data, char * string){
    char * token;

    token = strtok(string, DELIM);
    int id = atoi(token); //obtiene id del sensor

    token = strtok(NULL, DELIM);
    char *name = token; //guardamos nombre sensor

    token = strtok(NULL, DELIM);
    char status = token[0];
    
    return newSensor(data, id, name, status);
}
    


