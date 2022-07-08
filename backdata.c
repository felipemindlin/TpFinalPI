#include "sensorsADT.h"

enum days{Mon = 0, Tue, Wed, Thur, Fri, Sat, Sun}; // enum de los dias de la semana
enum months{Jan = 1, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec}; // enum de meses en el año


static int days(char * token); // convierte los dias de la semana a numeros del 0 al 6

static int months(char * token); // convierte los meses a numeros del 1 al 12



int addReading(sensorsADT data, char * string, int min, int max){
    char * token;  // inicializamos el string token con el que vamos a leer la linea 
    int month = -1; // inicializamos el month por si no hay guardarlo para poder llamar a la funcion con los paramteros correctos
    int monthDay = -1; // idem con el dia del mes
    int flag = 0; // inicializamos el flag con el que vamos corroborar si hay que guardar los datos para el Q4

    token = strtok(string, DELIM); // leo la linea hasta el;
    int year = atoi(token); // convertimos el año que es un string a int

    if(year >= min && year <= max){ // si el año de la medicion actual esta dentro del intervalo dado en los args
        flag = 1; // pongo el flag en 1 para indicar que si tengo que guardar los datos del Q4
    }  

    token = strtok(NULL, DELIM); // leo la lina hasta el proximo ;
    if(flag){ // si flag=1
        month = months(token); // agrego el mes llamando a la funcion month que convierte el string del mes a int 
    }

    token = strtok(NULL, DELIM);  // leo la linea hasta el proximo ;
    if(flag){ // si flag=1
        monthDay = atoi(token); // paso el dia del mes de string a int si flag=1
    }

    token = strtok(NULL, DELIM); // leo la linea hasta el proximo ;
    int weekDay = days(token); // guardamos el dia como numero del 0 al 6 mediante la funcion days

    token = strtok(NULL, DELIM); // leo la linea hasta el proximo ;
    int id = atoi(token); // guardo el sensor como int 
    
    token = strtok(NULL, DELIM); // leo la linea hasta el proximo ;
    int time = atoi(token); // guardo la hora como int

    token = strtok(NULL, DELIM); // leo la linea hasta el proximo ;
    int hCounts = atoi(token); // guardo hCounts como int 
    
    int status = isActive(data, id); // me guardo 1 si el sensor esta activo
    // llamo a newReading para que agregue los datos en sus respectivos lugares
    return newReading(data, year, min, max, month, monthDay, weekDay, id, time, hCounts, &status);
    
}

static int days(char * token){
    // comparamos los primeros dos caracteres para ver que dia de la semana es y lo devolvemos como un int 
    char *weekDay[] = {"Mo", "Tu", "We", "Th", "Fr", "Sa", "Su"}; // sendo Mo=0, Tu=1 ... Su=6
    for(int i = 0; i < (sizeof(weekDay)/sizeof(weekDay[0])); i++){
        if(strncmp(token, weekDay[i], 2)==0){
            return i; //retorna que dia es como int
        }
    }
    return -1; // retrona -1 si es un dia invalido (no deberia entrar aca ya que los datos son validos)
}

static int months(char * token){
   //para comparar primeros 3 caracteres del mes (diferenciar march-may, june-july)
   char * monthsVec[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
   int i=0; // comparo con los primeros 3 caracteres ya que con esos diferencio todos 
   while(strncmp(token, monthsVec[i], 3) != 0){ // busca que mes es comparando los primeros tres caracteres
        i++; // incremento el i para seguir recorriendo el vector de strings
   }
   return i + 1; // devuelve i+1 ya que el vetor arranca en 0 y los meses arrancan en 1
}   



int addSensor(sensorsADT data, char * string){
    char * token; // inicializamos el string token con el que vamos a leer la linea 

    token = strtok(string, DELIM);// leo la linea hasta el proximo ;
    int id = atoi(token); //guarda el id como int 

    token = strtok(NULL, DELIM);// leo la linea hasta el proximo ;
    char *name = token; //guardamos el nombre del sensor

    token = strtok(NULL, DELIM);// leo la linea hasta el proximo ;
    char status = token[0]; // guarda el status 

    if(status == 'A'){
        return newSensor(data, id, name, status); // agrega los datos si el sensor esta activo 
    }
    return 0; // retona 0 sino se agrego (no hubo error de memoria)
}
