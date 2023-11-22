CC = g++
CFLAGS = -g -std=c++11 -Wall
JFLAGS = -lcurl -ljsoncpp
DEBUG_RUN = gdb -q -ex run ./main.out
OBJ_FILES = gwas_obj.o compare_double_vector.o myCSV.o fetchdata.o


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

fetchdata.o: fetchdata.cpp fetchdata.h
	rm -f fetchdata.o
	${CC} ${CFLAGS} -c fetchdata.cpp

clean: 
	rm -f *.o *.gch main.out

run:
	./main.out

valgrind:
	valgrind --tool=memcheck --leak-check=yes ./main.out