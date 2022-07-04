#include "sensorsADT.h"

// Year;Month;Mdate;Day;Sensor_ID;Time;Hourly_Counts

void newData(sensorsADT sens, char * string){
    char * token;
    token = strtok(string, DELIM);

    token = strtok(NULL, DELIM); // año
    int year = atoi(token);

    token = strtok(NULL, DELIM); // mes // REVISAR SI HACEMOS EL QUERY 4 O NO
    char * month = token;

    token = strtok(NULL, DELIM); // mDate
    int day = token;

    token = strtok(NULL, DELIM); // Day // HAY QUE VER SI LO HACEMOS ENUM O NO, ESO CAMBIARIA EL TIPO DE DATO
    int weekDay = token;

    token = strtok(NULL, DELIM); // sensor_id
    int sensor = token;
    
    token = strtok(NULL, DELIM); // time
    int time = token;

    token = strtok(NULL, DELIM); // hourly_counts (no se que es)
    int hCounts = token;


    






}

    


