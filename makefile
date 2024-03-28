CC = g++
CFLAGS = -g -std=c++11 -Wall
JFLAGS = -lcurl -ljsoncpp 
DEBUG_RUN = gdb -q -ex run --args ./main.out input/small_test/small_test.csv
OF = o_files/
SC = src/
HD = ${SC}headers
FD = ${SC}fetchdata/

OBJ_FILES = ${OF}gwas_obj.o ${OF}compare_double_vector.o ${OF}myCSV.o ${OF}fetchdata_dbsnp.o ${OF}fetchdata_ensembl.o ${OF}fetchdata_shared.o ${OF}fetchdata_positions.o

main: ${OBJ_FILES}
	rm -f main.out
	${CC} ${CFLAGS} ${SC}main.cpp ${OBJ_FILES} ${JFLAGS} -o main.out 
	${DEBUG_RUN}

${OF}gwas_obj.o: ${SC}gwas_obj.cpp ${SC}gwas_obj.h
	rm -f ${OF}gwas_obj.o
	${CC} ${CFLAGS} -c ${SC}gwas_obj.cpp -o ${OF}gwas_obj.o

${OF}compare_double_vector.o: ${SC}compare_double_vector.cpp ${SC}compare_double_vector.h
	rm -f ${OF}compare_double_vector.o
	${CC} ${CFLAGS} -c ${SC}compare_double_vector.cpp -o ${OF}compare_double_vector.o

${OF}myCSV.o: ${SC}myCSV.cpp ${SC}myCSV.h
	rm -f ${OF}myCSV.o
	${CC} ${CFLAGS} -c ${SC}myCSV.cpp -o ${OF}myCSV.o

${OF}fetchdata_shared.o: ${FD}fetchdata_shared.cpp ${FD}fetchdata_shared.h
	rm -f ${OF}fetchdata_shared.o
	${CC} ${CFLAGS} -c ${FD}fetchdata_shared.cpp -o ${OF}fetchdata_shared.o	

${OF}fetchdata_dbsnp.o: ${FD}fetchdata_dbsnp.cpp ${FD}fetchdata_dbsnp.h
	rm -f ${OF}fetchdata_dbsnp.o
	${CC} ${CFLAGS} -c ${FD}fetchdata_dbsnp.cpp -o ${OF}fetchdata_dbsnp.o

${OF}fetchdata_ensembl.o: ${FD}fetchdata_ensembl.cpp ${FD}fetchdata_ensembl.h
	rm -f ${OF}fetchdata_ensembl.o
	${CC} ${CFLAGS} -c ${FD}fetchdata_ensembl.cpp -o ${OF}fetchdata_ensembl.o

${OF}fetchdata_positions.o: ${FD}fetchdata_positions.cpp ${FD}fetchdata_positions.h
	rm -f ${OF}fetchdata_positions.o
	${CC} ${CFLAGS} -c ${FD}fetchdata_positions.cpp -o ${OF}fetchdata_positions.o

clean: 
	rm -f *.o *.gch main.out
	rm ${OF}*

run:
	./main.out

valgrind:
	valgrind --tool=memcheck --leak-check=yes ./main.out