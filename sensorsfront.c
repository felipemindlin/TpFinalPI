#include "sensorsADT.h"



static void memory(); // Para modularizar los errores de memoria, indica que no hay mas memoria y aborta.

static int check(char *s); //chequea que los años sean validos

static void wrongyear(void); // si check indica que no son validos indica el error y aborta

int main(int argc, char *argv[]){
    if( argc < 2 || argc > 5 ) { //chequea cantidad de argumentos
        fprintf(stderr, "ERROR: cantidad de argumentos invalida\n"); //sino es valida lo avisa y aborta
        exit(1);
    }
    int min=MIN_YEAR; //inicializamos las variables en donde vamos a gaurdar los años para el Q4
    int max=ACTUAL_YEAR;
    if(argc==4){ //si solo pasaron un año chequea que el mismo sea valido
        if(check(argv[3])){
            wrongyear();
        }
        min=atoi(argv[3]);
    }
    else if(argc==5){ //idem anterior pero con los dos 
        if( check(argv[3]) || check(argv[4])){
           wrongyear();
        }
        min=atoi(argv[3]);
        max=atoi(argv[4]);
        if(min>max){ // y chequeamos que el primer año se menor que el segundo asi el intervalo es valido
            wrongyear();
        }
    }
    if(min<MIN_YEAR){ // si algun año esta fuera de los años que se tomaron las mediciones se lo pone en el minimo o maximo depende el caso
        min=MIN_YEAR; 
    }
    if(max>ACTUAL_YEAR){
        max=ACTUAL_YEAR;
    }
    FILE * readings = fopen(argv[1], "r");     // abrimos las mediciones
    FILE * sensors = fopen(argv[2], "r");       // abrimos el archivo csv de los sensores
    if ( readings == NULL || sensors == NULL ){ // Nos fijamos que haya podido abrir los archivos sino avisa el error y aborta
        fprintf(stderr, "ERROR: archivos especificados no encontrados\n");
        exit(1);
    }
    sensorsADT data = newSensorsADT();         // creamos un nuevo ADT y checkeamos de tener memoria
    if(data==NULL){
        memory();
    }
    char * currentLine=malloc(MAX_LEN); 
    fgets(currentLine, MAX_LEN, sensors); // salteo el encabezado
    while(fgets(currentLine, MAX_LEN, sensors)){ //recorro todas las lineas 
        if(addSensor(data, currentLine)){ //agrego los sensores del archivo sensors.csv
            memory();
        }
    }
    fclose(sensors); // al terminar de leer sensors.csv lo cierro
    fgets(currentLine, MAX_LEN, readings); // salteo el encabezado
    while(fgets(currentLine, MAX_LEN, readings)){ //recorro todas las lineas
        if(addReading(data, currentLine, min, max)){ // agrego las mediciones de los sensores dentro del readings.csv
            memory();
        }
    }
    fclose(readings); //al terminar de leer readings.csv lo cierro
  

    FILE * query1= fopen("query1.csv", "wt"); // creamos los archivos donde vamos a guardar lo que pide cada query
    FILE * query2= fopen("query2.csv", "wt"); 
    FILE * query3= fopen("query3.csv", "wt");
    FILE * query4= fopen("query4.csv", "wt");
    if(query1==NULL || query2==NULL || query3==NULL || query4==NULL){ // chequeamos que los archivos se hayan creado
        fprintf(stderr, "ERROR: Fallo en la creacion/escritura de archivos\n"); // sino se avisa el error y aborta
        exit(1);
    }
    fputs("sensor;counts\n", query1); // pongo el encabezado de todos los queries 
    fputs("year;counts\n", query2);
    fputs("day;day_counts;night_counts;total_counts\n", query3);
    fputs("sensor;max_counts;hour;date\n", query4);
    int i=0;
    //-------------------------------QUERY1------------------------------------------------------
    orderQ1(data); //ordenamos con quicksort en el orden que pide el Q1
    while(i<IDS){ //recorre el vector ids y y lo coloca en el archivos query1.csv
        char * aux=getName(data, i);
        if(aux!=NULL){ // si hay alguna poscion vacia no la agrega 
            fprintf(query1,"%s;%ld\n", aux, getTotal(data, i));
        }
        i++;
    }
    //-------------------------------QUERY2------------------------------------------------------
    for(i=ACTUAL_YEAR-MIN_YEAR; i>=0; i--){ //recorremos el vector de años desde el ultimo hasta el primero para dejarlo en el orden pedido
        fprintf(query2, "%d;%ld\n", i+MIN_YEAR, getDataByYear(data, i)); 
    }
    //-------------------------------QUERY3------------------------------------------------------
    for(i=0; i<DAYS; i++){ //recorremos el vector de dias y ponemos las datos en el formato pedido
        fprintf(query3, "%s;%ld;%ld;%ld\n", getDayName(data, i), getDataDay(data, i), getDataNight(data, i), getDataTotal(data, i)); 
    }
    //-------------------------------QUERY4------------------------------------------------------
    orderQ4(data); //ordenamos en el orden pedido para el Q4
    for(i=0; i<IDS; i++){
        char *name = getName(data, i);
        size_t maxCount = getMax(data, i);
        if(name != NULL && maxCount != 0){ // chequeamos que no sea una poscion vacia y que tenga una cantidad maxima
            fprintf(query4, "%s;%ld;%d;%d/%d/%d\n", name, maxCount, getHour(data, i), getDay(data, i), getMonth(data, i), getYear(data, i));
        }
    }
    //-------------------------------------------------------------------------------------------
    //liberamos y cerramos archivos
    free(currentLine);
    freeALL(data);
    fclose(query1);
    fclose(query2);
    fclose(query3);
    fclose(query4);
    return 0;
}

void memory(){ //indicamos que no hay memoria
    fprintf(stderr, "ERROR: memoria insuficiente\n");
    exit(1);
}
void wrongyear(void){ //indicamos que los años no son validos 
    fprintf(stderr, "ERROR: Paramtros de años invalidos\n");
    exit(1);
}

int check (char * s){
    for(int i=0; s[i]; i++){
         if(!isdigit(s[i])){ //chequea que todos caracteres del año sean numeros
            return 1;
        }
    }
    return 0;
}
