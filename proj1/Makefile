###
### Makefile for CalcYouLater Project
### CalcYouLater is an RPN calculator
###
### Author:  Emily Gjertsson

CXX      = clang++
CXXFLAGS = -g3  -std=c++11 -Wall -Wextra  -Wpedantic -Wshadow
LDFLAGS  = -g3

main: DatumStack.o Datum.o RPNCalc.o main.o
	${CXX} ${LDFLAGS} -o calcYouLater DatumStack.o Datum.o RPNCalc.o main.o


parser: parser.o DatumStack.o Datum.o
	${CXX} ${LDFLAGS} -o parser parser.o
	
testDatumStack: DatumStack.o Datum.o testDatumStack.o 
	${CXX} ${LDFLAGS} -o testDatumStack DatumStack.o Datum.o testDatumStack.o

	
datum: DatumStack.o Datum.o parser.o main.o
	${CXX} ${LDFLAGS} -o datum DatumStack.o Datum.o parser.o main.o
	
testRPNCalc: DatumStack.o Datum.o RPNCalc.o testRPNCalc.o	
	${CXX} ${LDFLAGS} -o testRPNCalc DatumStack.o Datum.o RPNCalc.o \
	testRPNCalc.o

testRPNCalc.o: testRPNCalc.cpp 	
RPNCalc.o: RPNCalc.cpp RPNCalc.h
main.o: main.cpp 
DatumStack.o: DatumStack.cpp DatumStack.h Datum.h
testDatumStack.o: testDatumStack.cpp Datum.h DatumStack.cpp DatumStack.h
parser.o: parser.cpp

##
## Here is a rule for compiling .cyl files for use in your testing
##
%.cylc:  %.cyl
	./cylc $^
