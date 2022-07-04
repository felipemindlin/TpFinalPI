#include "sensorsADT.h"

// Year;Month;Mdate;Day;Sensor_ID;Time;Hourly_Counts

void newData(sensorsADT sens, char * string){
    char * token;

    token = strtok(string, DELIM); 
    int year = atoi(token);// año

    token = strtok(NULL, DELIM); 
    char * month = token; // mes 

    token = strtok(NULL, DELIM); 
    int day = atoi(token); // mDate

    token = strtok(NULL, DELIM); 
    int weekDay = atoi(token); // Day // HAY QUE VER SI LO HACEMOS ENUM O NO, ESO CAMBIARIA EL TIPO DE DATO

    token = strtok(NULL, DELIM); // sensor_id
    int sensor = atoi(token);
    
    token = strtok(NULL, DELIM); 
    int time = atoi(token); // time

    token = strtok(NULL, DELIM); 
    int hCounts = atoi(token); // hourly_counts (no se que es)

    //FALTA LLAMAR A LAS FUNCIONES QUE AGREGUEN LA INFO AL TAD
}

    


