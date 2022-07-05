#include "sensorsADT.h"
#define MAX_LEN 64 // reservamos 64 ya que analizando los parametros llegamos a que el maximo son 55 caracaracter rervamos mas por si cambian los id o hay mediciones absurdamente grandes.
void memory(void);
void wrongyear(void);
int check(char *s);
int main(int argc, char *argv[]){
    if( argc < 2 || argc > 4 ) {
        fprintf(stderr, "ERROR: cantidad de argumentos invalida\n");
        exit(1);
    }
    if(argc==3){
        if(check(argv[3])){
            wrongyear();
        }
    }
    else if(argc==4){
        if( check(argv[3]) || check(argv[4])){
           wrongyear();
        }
    }
    FILE * readings = fopen(argv[1], "r");     // abrimos las mediciones
    FILE * sensors = fopen(argv[2], "r");       // abrimos el archivo csv de los sensores
    if ( readings == NULL || sensors == NULL ){ // nos fijamos que tengamos memoria
        fprintf(stderr, "ERROR: archivos especificados no encontrados\n");
        exit(1);
    }
    if(argc >=3){
        int min=atoi(argv[3]);
        
        if(argc==4){
            int max=atoi(argv[4]);
            
            sensorsADT data = newsensorADT(min, max);
        }
        else{
            sensorsADT data = newsensorADT(min, ACTUAL_YEAR);
        }
    }
    else {
        sensorsADT data = newsensorADT(MIN_YEAR, ACTUAL_YEAR);         // creamos un nuevo ADT y checkeamos de tener memoria
    }
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
    //Llamar a funcion que ordena
    while(i<IDS){
        id aux=data->ids[i];
        fprintf(query1,"%s;%d\n", aux.name, aux.total);
        i++;
    }
    for(i=data->dim; i>=0; i--){
        fprintf(query2, "%d;%d\n", i+MIN_YEAR, data->years[i]);
    }
    for(i=0; i<DAYS; i++){
        day aux=data->days[i];
        fprintf(query3, "%s;%d;%d;%d\n", aux.name, aux.day, aux.night, aux.total);
    }
    //Llamar a funcion que ordena vol 2
    for(i=data->minYear-MIN_YEAR; i<data->maxYear-MIN_YEAR; i++){
        id aux=data->ids[i];
        fprintf(query3, "%s;%d;%d;%d/%d/%d\n",aux.name, aux.cant_max, aux.hour, aux.day, aux.month, aux.year);
    }
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

