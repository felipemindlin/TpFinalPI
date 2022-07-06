#include "sensorsADT.h"
#define MAX_LEN 64 // reservamos 64 ya que analizando los parametros llegamos a que el maximo son 55 caracaracter rervamos mas por si cambian los id o hay mediciones absurdamente grandes.
void memory();
void wrongyear(void);
int check(char *s);
int main(int argc, char *argv[]){
    if( argc < 2 || argc > 5 ) {
        fprintf(stderr, "ERROR: cantidad de argumentos invalida\n");
        exit(1);
    }
    int min=MIN_YEAR;
    int max=ACTUAL_YEAR;
    if(argc==4){
        if(check(argv[3])){
            wrongyear();
        }
        min=atoi(argv[3]);
    }
    else if(argc==5){
        if( check(argv[3]) || check(argv[4])){
           wrongyear();
        }
        min=atoi(argv[3]);
        max=atoi(argv[4]);
        if(min>max){
            wrongyear();
        }
    }
    if(min<MIN_YEAR){
        min=MIN_YEAR;
    }
    if(max>ACTUAL_YEAR){
        max=ACTUAL_YEAR;
    }
    FILE * readings = fopen(argv[1], "r");     // abrimos las mediciones
    FILE * sensors = fopen(argv[2], "r");       // abrimos el archivo csv de los sensores
    if ( readings == NULL || sensors == NULL ){ // nos fijamos que tengamos memoria
        fprintf(stderr, "ERROR: archivos especificados no encontrados\n");
        exit(1);
    }
    sensorsADT data = newSensorsADT(min, max);         // creamos un nuevo ADT y checkeamos de tener memoria
    if(data==NULL){
        memory();
    }
    char * currentLine=malloc(MAX_LEN); 
    fgets(currentLine, MAX_LEN, sensors); // salteo el encabezado
    while(fgets(currentLine, MAX_LEN, sensors)){ //recorro todas las lineas 
        if(addSensor(data, currentLine)){
            memory();
        }
    }
    fgets(currentLine, MAX_LEN, readings); // salteo el encabezado
    while(fgets(currentLine, MAX_LEN, readings)){
        if(addReading(data, currentLine, min, max)){
            memory();
        }
    }
    fclose(readings);
    fclose(sensors);

    FILE * query1= fopen("query1.csv", "wt"); // creamos los archivos donde vamos a guardar lo que pide cada query
    FILE * query2= fopen("query2.csv", "wt"); 
    FILE * query3= fopen("query3.csv", "wt");
    FILE * query4= fopen("query4.csv", "wt");
    if(query1==NULL || query2==NULL || query3==NULL || query4==NULL){
        fprintf(stderr, "ERROR: Fallo en la creacion/escritura de archivos\n");
        exit(1);
    }
    fputs("sensor;counts\n", query1); // pongo el encabezado de todos los queries 
    fputs("year;counts\n", query2);
    fputs("day;day_counts;night_counts;total_counts\n", query3);
    fputs("sensor;max_counts;hour;date\n", query4);
    int i=0;
    orderQ1(data);
    while(i<IDS){
        char * aux=getName(data, i);
        if(aux!=NULL){
            fprintf(query1,"%s;%ld\n", aux, getTotal(data, i));
        }
        i++;
    }
    for(i=ACTUAL_YEAR-MIN_YEAR; i>=0; i--){
        fprintf(query2, "%d;%ld\n", i+MIN_YEAR, getDataByYear(data, i)); 
    }
    for(i=0; i<DAYS; i++){
        fprintf(query3, "%s;%ld;%ld;%ld\n", getDayName(data, i), getDataDay(data, i), getDataNight(data, i), getDataTotal(data, i)); 
    }
    orderQ4(data);
    for(i=min-MIN_YEAR; i<max-MIN_YEAR; i++){
        fprintf(query4, "%s;%ld;%d;%d/%d/%d\n",getName(data, i), getMax(data, i), getHour(data, i), getDay(data, i), getMonth(data, i), getYear(data, i));
    }
    free(currentLine);
    freeALL(data);
    fclose(query1);
    fclose(query2);
    fclose(query3);
    fclose(query4);
    return 0;
}

void memory(){
    fprintf(stderr, "ERROR: memoria insuficiente\n");
    exit(1);
}
void wrongyear(void){
    fprintf(stderr, "ERROR: Paramtros de años invalidos\n");
    exit(1);
}

int check (char * s){
    for(int i=0; s[i]; i++){
         if(!isdigit(s[i])){
            return 1;
        }
    }
    return 0;
}


