Para generar el ejecutable, desde la terminal ejecutar el comando "make all" en el directorio actual:

	- En caso de querer debuggear el programa, correr "make debug"
	y se creará el ejecutable, pero habiéndose compilado con los flags:
	"-Wall -fsanitize=address"
	
Para borrar el ejecutable, correr el comando "make clean".

Para borrar las queries, correr el comando "make cleanQueries".

Para borrar ambos archivo ejecutable y las queries, correr el comando "make cleanAll".

El ejecutable tendrá el nombre "pedestrians".

Para correr el programa se debe ejecutar desde la terminal el programa creado anteriormente, con los siguientes
argumentos que se correspondan:

		1) Path al archivo que contiene las mediciones de los sensores. (i.e: readings.csv)
		
		2) Path al archivo que contiene los sensores. (i.e: sensors.csv)
		
	Argumentos opcionales: Si se desea especificar un intervalo de años para el Query 4.
							Por defecto, si se dejan vacíos, el query 4 analizará todos los datos.
	
		- Intervalo de años en formato numérico y siendo el primero menor o igual que el segundo.
		Ejemplos de argumentos válidos: "2003 2022", "2009 2015", etc.
		Ejemplos de argumentos inválidos: "dos mil 2039", "2022 2010", etc.
		
El ejecutable está configurado para que los archivos se encuentren con el formato siguiente:

	- readings.csv :
		Year;Month;Mdate;Day;Sensor_ID;Time;Hourly_Counts
	
	- sensors.csv :
		Sensor_ID;Name;Status
		
