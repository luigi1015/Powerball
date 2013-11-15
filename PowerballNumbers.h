#ifndef PowerballNumbers_H
#define PowerballNumbers_H

/*
#include <iostream>
#include "sqlite/sqlite3.h"
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <fstream>
*/

#include <vector>
#include <utility>
#include "sqlite/sqlite3.h"

class PowerballNumbers
{
	private:
		sqlite3 *db;//Database variable.
		char *errMsg;//SQLite error message variable.
		int returnCode;//Return code variable for SQLite function.
		sqlite3_stmt *statement;//SQL statement variable.
		unsigned long dateToLong( unsigned int month, unsigned int day, unsigned int year );//Return the date as a long in the format yyyymmdd.
		
	public:
		enum PowerballTypes{ White, Powerball, PowerPlay };//The types of numbers stored in the database.
		PowerballNumbers();//Constructor
		~PowerballNumbers();//Destructor
		bool addNum( unsigned char number, unsigned char month, unsigned char day, unsigned int year, PowerballTypes type );//Add a number with an associated drawing date and type (white ball, Powerball, PowerPlay). Returns true if the add succeeded or false if not.
		bool addNumWCheck( unsigned char number, unsigned char month, unsigned char day, unsigned int year, PowerballTypes type );//Same with addNum but checks isSaved first.
		void clear();//Clear the list of stored numbers.
		unsigned long numCount();//Returns how many numbers in the database.
		bool isSaved( unsigned char number, unsigned char month, unsigned char day, unsigned int year, PowerballTypes type );//Checked if a number is in the database. Returns true if yes, false if not.
		std::vector<std::pair<int, int> > topNumsByType( unsigned char count, PowerballTypes type );//Returns the top count numbers in the database of type type in terms of number of occurences as a vector<pair<int, int>>.The first int is the number and the second int is the number of occurences.
		unsigned int getDrawings();//Returns the total number of drawings in the database.
};

#endif /* PowerballNumbers_H */
