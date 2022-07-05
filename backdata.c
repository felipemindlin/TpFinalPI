#include "sensorsADT.h"

// Year;Month;Mdate;Day;Sensor_ID;Time;Hourly_Counts
int days(char * token);

void newData(sensorsADT sens, char * string){
    char * token;

    token = strtok(string, DELIM); 
    int year = atoi(token);// año

    token = strtok(NULL, DELIM); 
    char * month = token; // mes 

    token = strtok(NULL, DELIM); 
    int day = atoi(token); // mDate

    token = strtok(NULL, DELIM); 
    int weekDay = days(token); // Day 

    token = strtok(NULL, DELIM); // sensor_id
    int sensor = atoi(token);
    
    token = strtok(NULL, DELIM); 
    int time = atoi(token); // time

    token = strtok(NULL, DELIM); 
    int hCounts = atoi(token); // hourly_counts (no se que es)

    //FALTA LLAMAR A LAS FUNCIONES QUE AGREGUEN LA INFO AL TAD
}
int days(char * token){
    if(strncmp(token, "Mo")==0) return 0;
    if(strncmp(token, "Tu")==0) return 1;
    if(strncmp(token, "We")==0) return 2;
    if(strncmp(token, "Th")==0) return 3;
    if(strncmp(token, "Fr")==0) return 4;
    if(strncmp(token, "Sa")==0) return 5;
    if(strncmp(token, "Su")==0) return 6;
}

    


