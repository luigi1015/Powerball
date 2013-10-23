all: Powerball

sqlite3.o: sqlite/sqlite3.c
	gcc -Wall -c sqlite/sqlite3.c

Powerball: Powerball.cpp sqlite3.o
	g++ -Wall -o Powerball Powerball.cpp sqlite3.o -lpthread -ldl

clean:
	rm Powerball *~
