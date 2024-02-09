CC = g++
CFLAGS = -g -std=c++11 -Wall
JFLAGS = -lcurl -ljsoncpp
DEBUG_RUN = gdb -q -ex run ./main.out
TF = o_files/
FD = fetchdata/

OBJ_FILES = ${TF}gwas_obj.o ${TF}compare_double_vector.o ${TF}myCSV.o ${TF}fetchdata_dbsnp.o ${TF}fetchdata_ensembl.o ${TF}fetchdata_shared.o

main: ${OBJ_FILES}
	rm -f main.out
	${CC} ${CFLAGS} main.cpp ${OBJ_FILES} ${JFLAGS} -o main.out 
	${DEBUG_RUN}

${TF}gwas_obj.o: gwas_obj.cpp gwas_obj.h
	rm -f ${TF}gwas_obj.o
	${CC} ${CFLAGS} -c gwas_obj.cpp -o ${TF}gwas_obj.o

${TF}compare_double_vector.o: compare_double_vector.cpp compare_double_vector.h
	rm -f ${TF}compare_double_vector.o
	${CC} ${CFLAGS} -c compare_double_vector.cpp -o ${TF}compare_double_vector.o

${TF}myCSV.o: myCSV.cpp myCSV.h
	rm -f ${TF}myCSV.o
	${CC} ${CFLAGS} -c myCSV.cpp -o ${TF}myCSV.o

${TF}fetchdata_shared.o: ${FD}fetchdata_shared.cpp ${FD}fetchdata_shared.h
	rm -f ${TF}fetchdata_shared.o
	${CC} ${CFLAGS} -c ${FD}fetchdata_shared.cpp -o ${TF}fetchdata_shared.o	

${TF}fetchdata_dbsnp.o: ${FD}fetchdata_dbsnp.cpp ${FD}fetchdata_dbsnp.h
	rm -f ${TF}fetchdata_dbsnp.o
	${CC} ${CFLAGS} -c ${FD}fetchdata_dbsnp.cpp -o ${TF}fetchdata_dbsnp.o

${TF}fetchdata_ensembl.o: ${FD}fetchdata_ensembl.cpp ${FD}fetchdata_ensembl.h
	rm -f ${TF}fetchdata_ensembl.o
	${CC} ${CFLAGS} -c ${FD}fetchdata_ensembl.cpp -o ${TF}fetchdata_ensembl.o

clean: 
	rm -f *.o *.gch main.out
	rm ${TF}*.o ${TF}*.gch

run:
	./main.out

valgrind:
	valgrind --tool=memcheck --leak-check=yes ./main.out