all: main.o conditions.o DNA.o solver.o
	g++ -o TSP main.o conditions.o DNA.o solver.o
main.o: main.cpp conditions.h DNA.h solver.h
	g++ -c -g main.cpp

conditions.o: conditions.cpp conditions.h
	g++ -c -g conditions.cpp

DNA.o: DNA.cpp DNA.h
	g++ -c -g DNA.cpp

solver.o: solver.cpp solver.h
	g++ -c -g solver.cpp

clean: cleanobj cleanmain 

cleanobj:
	rm -f *.o

cleanmain:
	rm TSP

.PHONY: clean cleanobj cleanmain