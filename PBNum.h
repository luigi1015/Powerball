#ifndef PBNum_H
#define PBNum_H

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

class PBNum
{//A single powerball number
	private:
		unsigned int num;//The number drawn.
		unsigned char month, day;//The month and day of the date it was drawn.
		unsigned int year;//The year of the date it was drawn.
		unsigned int type;//The type of number drawn.
		
	public:
		enum PowerballTypes{ White, Powerball, PowerPlay };//The types of numbers stored in the database.
		PBNum();//Constructor
		PBNum( unsigned int newNum, unsigned char newMonth, unsigned char newDay, unsigned int newYear, unsigned char newType );//Constructor
		PBNum( unsigned int newNum, unsigned long newDate, unsigned char newType );//Constructor
		unsigned int getNumber();//Returns the number.
		void setNumber( unsigned int newNum );//Sets the number.
		unsigned long getDate();//Returns the value of the date in format yyyymmdd.
		void setDate( unsigned char newMonth, unsigned char newDay, unsigned int newYear );//Sets the date.
		unsigned char getMonth();//Returns the month.
		unsigned char getDay();//Returns the day.
		unsigned int getYear();//Returns the year.
		unsigned int getType();//Returns the type.
		void setType( unsigned int newType );//Sets the type.
		unsigned long dateToLong( unsigned char month, unsigned char day, unsigned int year );//Return the date as a long in the format yyyymmdd.
		void longToDate( unsigned long date, unsigned char &month, unsigned char &day, unsigned int &year );//Return the date as a set of unsigned ints from an input of long in the format yyyymmdd.
};

#endif /* PBNum_H */
