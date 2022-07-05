#include "sensorsADT.h"

// Year;Month;Mdate;Day;Sensor_ID;Time;Hourly_Counts
int days(char * token);

void addReading(sensorsADT data, char * string){
    char * token;

    token = strtok(string, DELIM); 
    int year = atoi(token);// año

    token = strtok(NULL, DELIM); 
    char * month = token; // mes //hacer funcion que cambie a numero

    token = strtok(NULL, DELIM); 
    int day = atoi(token); // mDate

    token = strtok(NULL, DELIM); 
    int weekDay = days(token); // Day 

    token = strtok(NULL, DELIM); // sensor_id
    int sensor = atoi(token);
    
    token = strtok(NULL, DELIM); 
    int time = atoi(token); // time

    token = strtok(NULL, DELIM); 
    int hCounts = atoi(token); // hourly_counts 

    //FALTA LLAMAR A LAS FUNCIONES QUE AGREGUEN LA INFO AL TAD
}
int days(char * token){
    int n=2; // comparamos los primeros dos caracteres para ver que dia de la semana es 
    if(strncmp(token, "Mo", n)==0) return 0;
    if(strncmp(token, "Tu", n)==0) return 1;
    if(strncmp(token, "We", n)==0) return 2;
    if(strncmp(token, "Th", n)==0) return 3;
    if(strncmp(token, "Fr", n)==0) return 4;
    if(strncmp(token, "Sa", n)==0) return 5;
    if(strncmp(token, "Su", n)==0) return 6;
}

    


