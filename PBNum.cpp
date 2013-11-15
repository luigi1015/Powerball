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

#include "PBNum.h"

/*
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
		unsigned int getNumber();//Returns the number.
		void setNumber( unsigned int newNum );//Sets the number.
		unsigned long getDate();//Returns the value of the date in format yyyymmdd.
		void setDate( unsigned char newMonth, unsigned char newDay, unsigned int newYear );//Sets the date.
		unsigned char getMonth();//Returns the month.
		unsigned char getDay();//Returns the day.
		unsigned int getYear();//Returns the year.
		unsigned int getType();//Returns the type.
		void setType( unsigned int newType );//Sets the type.
};
*/

PBNum::PBNum()
{//Constructor
	num = 0;
	month = 0;
	day = 0;
	year = 0;
	type = 0;
}

PBNum::PBNum( unsigned int newNum, unsigned char newMonth, unsigned char newDay, unsigned int newYear, unsigned char newType )
{//Constructor
	num = newNum;
	month = newMonth;
	day = newDay;
	year = newYear;
	type = newType;
}

unsigned int PBNum::getNumber()
{//Returns the number.
	return num;
}

void PBNum::setNumber( unsigned int newNum )
{//Sets the number.
	num = newNum;
}

unsigned long PBNum::getDate()
{//Returns the value of the date in format yyyymmdd.
	return day + month*100 + year*10000;
}

void PBNum::setDate( unsigned char newMonth, unsigned char newDay, unsigned int newYear )
{//Sets the date.
	month = newMonth;
	day = newDay;
	year = newYear;
}

unsigned char PBNum::getMonth()
{//Returns the month.
	return month;
}

unsigned char PBNum::getDay()
{//Returns the day.
	return day;
}

unsigned int PBNum::getYear()
{//Returns the year.
	return year;
}

unsigned int PBNum::getType()
{//Returns the number.
	return type;
}

void PBNum::setType( unsigned int newType )
{//Sets the number.
	type = newType;
}
