all: Powerball

sqlite3.o: sqlite/sqlite3.c
	gcc -Wall -c sqlite/sqlite3.c

PBNum.o: PBNum.h PBNum.cpp
	gcc -Wall -c PBNum.cpp

PowerballNumbers.o: PowerballNumbers.h PowerballNumbers.cpp
	gcc -Wall -c PowerballNumbers.cpp

SimpleXMLPB.o: SimpleXMLPB.h SimpleXMLPB.cpp
	gcc -Wall -c SimpleXMLPB.cpp

Powerball: Powerball.cpp Powerball.h sqlite3.o SimpleXMLPB.o PowerballNumbers.o PBNum.o
	g++ -Wall -o Powerball Powerball.cpp sqlite3.o SimpleXMLPB.o PowerballNumbers.o PBNum.o -lpthread -ldl

clean:
	rm Powerball *~ *.o *.gch
