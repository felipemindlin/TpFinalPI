COMPILER=gcc
OUTPUT_FILE=pedestrians
FILES=sensorsCDT.c backdata.c sensorsfront.c
FLAGS=-pedantic -std=c99
DEBUG_COMPILER=-Wall -fsanitize=address

QUERYS=query1.csv query2.csv query3.csv query4.csv

debug: COMPILER+=$(DEBUG_COMPILER)
debug: all


all:
	$(COMPILER) -o $(OUTPUT_FILE) $(FILES) $(FLAGS)

clean:
	rm $(OUTPUT_FILE)
	
cleanQueries:
	rm -f $(QUERYS)

cleanAll:
	rm -f $(OUTPUT_FILE) $(QUERYS)