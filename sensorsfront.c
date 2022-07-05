#include "sensorsADT.h"
#define MAX_LEN 64 // reservamos 64 ya que analizando los parametros llegamos a que el maximo son 55 caracaracter rervamos mas por si cambian los id o hay mediciones absurdamente grandes.
void memory(void);

int main(int argc, char *argv[]){
    if( argc < 2 || argc > 4 ) {
        fprintf(stderr, "ERROR: cantidad de argumentos invalida\n");
        exit(1);
    }
    FILE * readings = fopen(argv[1], "r");     // abrimos las mediciones
    FILE * sensors = fopen(argv[2], "r");       // abrimos el archivo csv de los sensores
    if ( readings == NULL || sensors == NULL ){ // nos fijamos que tengamos memoria
        fprintf(stderr, "ERROR: archivos especificados no encontrados\n");
        exit(1);
    }
    sensorsADT data = newsensorADT();         // creamos un nuevo ADT y checkeamos de tener memoria
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
        if(addReading(data, currentLine)){
            memory();
        }
    }
    fclose(readings);
    fclose(sensors);

    FILE * query1= fopen("query1.csv", "w+"); // creamos los archivos donde vamos a guardar lo que pide cada query
    FILE * query2= fopen("query2.csv", "w+"); 
    FILE * query3= fopen("query3.csv", "w+");
    FILE * query4= fopen("query4.csv", "w+");
    if(query1==NULL || query2==NULL || query3==NULL || query4==NULL){
        fprintf(stderr, "ERROR: Fallo en la creacion/escritura de archivos\n");
        exit(1);
    }
    fputs("sensor;counts\n", query1); // pongo el encabezado de todos los queries 
    fputs("year;counts\n", query2);
    fputs("day;day_counts;night_counts;total_counts\n", query3);
    fputs("sensor;max_counts;hour;date\n", query4);
    



    free(currentLine);
    fclose(query1);
    fclose(query2);
    fclose(query3);
    fclose(query4);
}

void memory(){
    fprintf(stderr, "ERROR: memoria insuficiente\n");
    exit(1);
}