#include "sensorsADT.h"
#define QUERIES 3
#define MAX_LEN 256
void close(FILE * files[], size_t cant);

int main(int argc, char *argv[]){
    
    if( argc < 2 || argc > 4 ) {
        fprintf(stderr, "ERROR: cantidad de argumentos invalida\n");
        exit(1);
    }
    errno = 0;
    FILE * readings = fopen(argv[1], "r");     // abrimos las mediciones
    FILE * sensors = fopen(argv[2], "r");       // abrimos el archivo csv de los sensores
    FILE * query1= fopen("query1.csv", "wt"); // creamos los archivos donde vamos a guardar lo que pide cada query
    FILE * query2= fopen("query2.csv", "wt"); 
    FILE * query3= fopen("query3.csv", "wt");
    size_t cant=QUERIES+argc-1;
    FILE * files[]={readings, sensors, query1, query2, query3};
    if(errno == ENOENT) { // Si no se puede abrir un archivo cierro los que si pude abrir y salgo.
        close(files, cant);
        fprintf(stderr, "ERROR: No se pudo abrir un archivo\n"); 
        exit(1);
    }
    
    if ( readings == NULL || sensors == NULL ){ // nos fijamos que tengamos memoria
        fprintf(stderr, "ERROR: archivos especificados no encontrados\n");
        exit(1);
    }
    sensorsADT data = newsensorADT();         // creamos un nuevo ADT y checkeamos de tener memoria
    if(data==NULL){
        fprintf(stderr, "ERROR: memoria insuficiente\n");
        exit(1);
    }

}

void close(FILE * files[], size_t cant_files){
  for(size_t i=0; i<cant_files; i++)
    if (files[i]!=NULL)
      fclose(files[i]);
  return;
}