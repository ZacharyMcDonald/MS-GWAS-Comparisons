CC = g++
CFLAGS = -g -std=c++11 -Wall
JFLAGS = -lcurl -ljsoncpp
DEBUG_RUN = gdb -q -ex run ./main.out
OBJ_FILES = gwas_obj.o compare_double_vector.o myCSV.o fetchdata_dbsnp.o fetchdata_ensembl.o


main: ${OBJ_FILES}
	rm -f main.out
	${CC} ${CFLAGS} main.cpp ${OBJ_FILES} ${JFLAGS} -o main.out 
	${DEBUG_RUN}

gwas_obj.o:
	rm -f driver.o
	${CC} ${CFLAGS} -c gwas_obj.cpp

compare_double_vector.o: compare_double_vector.cpp compare_double_vector.h
	rm -f compare_double_vector.o
	${CC} ${CFLAGS} -c compare_double_vector.cpp

myCSV.o: myCSV.cpp myCSV.h
	rm -f myCSV.o
	${CC} ${CFLAGS} -c myCSV.cpp

fetchdata_dbsnp.o: fetchdata_dbsnp.cpp fetchdata_dbsnp.h
	rm -f fetchdata_dbsnp.o
	${CC} ${CFLAGS} -c fetchdata_dbsnp.cpp

fetchdata_ensembl.o: fetchdata_ensembl.cpp fetchdata_ensembl.h
	rm -f fetchdata_ensembl.o
	${CC} ${CFLAGS} -c fetchdata_ensembl.cpp

clean: 
	rm -f *.o *.gch main.out

run:
	./main.out

valgrind:
	valgrind --tool=memcheck --leak-check=yes ./main.out