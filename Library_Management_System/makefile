CC=g++
CFLAGS=-std=c++11 -Wall
TARGET=program

BUILD_DIR    = ./build
SRC_DIR    = ./src
INCLUDE_DIR  = ./include
TESTS_DIR = tests/

${BUILD_DIR}/${TARGET}: ${BUILD_DIR}/Student.o ${BUILD_DIR}/Book.o ${BUILD_DIR}/User.o ${BUILD_DIR}/Admin.o ${BUILD_DIR}/System.o ${BUILD_DIR}/Exceptions.o ${BUILD_DIR}/main.o
	${CC} ${CFLAGS} -g -o ${BUILD_DIR}/${TARGET} ${BUILD_DIR}/*.o

${BUILD_DIR}/Student.o: ${INCLUDE_DIR}/Student.hpp ${SRC_DIR}/Student.cpp
	${CC} ${CFLAGS} -I ${INCLUDE_DIR}/ -c ${SRC_DIR}/Student.cpp -o ${BUILD_DIR}/Student.o

${BUILD_DIR}/Book.o: ${INCLUDE_DIR}/Book.hpp ${SRC_DIR}/Book.cpp
	${CC} ${CFLAGS} -I ${INCLUDE_DIR}/ -c ${SRC_DIR}/Book.cpp -o ${BUILD_DIR}/Book.o

${BUILD_DIR}/User.o: ${INCLUDE_DIR}/User.hpp ${SRC_DIR}/User.cpp
	${CC} ${CFLAGS} -I ${INCLUDE_DIR}/ -c ${SRC_DIR}/User.cpp -o ${BUILD_DIR}/User.o

${BUILD_DIR}/Admin.o: ${INCLUDE_DIR}/Admin.hpp ${SRC_DIR}/Admin.cpp
	${CC} ${CFLAGS} -I ${INCLUDE_DIR}/ -c ${SRC_DIR}/Admin.cpp -o ${BUILD_DIR}/Admin.o

${BUILD_DIR}/System.o: ${INCLUDE_DIR}/System.hpp ${SRC_DIR}/System.cpp
	${CC} ${CFLAGS} -I ${INCLUDE_DIR}/ -c ${SRC_DIR}/System.cpp -o ${BUILD_DIR}/System.o

${BUILD_DIR}/Exceptions.o: ${INCLUDE_DIR}/Exceptions.hpp ${SRC_DIR}/Exceptions.cpp
	${CC} ${CFLAGS} -I ${INCLUDE_DIR}/ -c ${SRC_DIR}/Exceptions.cpp -o ${BUILD_DIR}/Exceptions.o

${BUILD_DIR}/main.o: ${INCLUDE_DIR}/Student.hpp ${INCLUDE_DIR}/Book.hpp ${INCLUDE_DIR}/User.hpp ${INCLUDE_DIR}/Admin.hpp ${INCLUDE_DIR}/System.hpp ${INCLUDE_DIR}/Exceptions.hpp ${SRC_DIR}/main.cpp
	${CC} ${CFLAGS} -I ${INCLUDE_DIR} -c ${SRC_DIR}/main.cpp -o ${BUILD_DIR}/main.o

# Rule for cleaning files generated during compilation.
# Call 'make clean' to use it
clean:
	rm -f ${BUILD_DIR}/*

# Run
run: run
	${BUILD_DIR}/program

#Clean test files
clean_test:
	rm tests/coverage/*.gcno tests/coverage/*.gcda tests/coverage/*.o

test:
	g++ -I ${INCLUDE_DIR} -c --coverage ${SRC_DIR}/Admin.cpp ${SRC_DIR}/User.cpp ${SRC_DIR}/Book.cpp ${SRC_DIR}/Student.cpp ${SRC_DIR}/System.cpp ${SRC_DIR}/Exceptions.cpp

test_:
	g++ -I ${INCLUDE_DIR} -I third_party/ --coverage Admin.o User.o Book.o Student.o Exceptions.o System.o ${TESTS_DIR}main_test.cpp ${TESTS_DIR}TesteAdmin.cpp ${TESTS_DIR}TesteUser.cpp ${TESTS_DIR}TesteBook.cpp ${TESTS_DIR}TesteStudent.cpp ${TESTS_DIR}TesteSystem.cpp ${TESTS_DIR}TesteExceptions.cpp -o testes.o;

run_test:
	./testes.o;mv *.gcno *.gcda *.o tests/coverage/

coverage_:
	gcovr -r . --exclude=".*h"
