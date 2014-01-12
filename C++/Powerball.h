#ifndef Powerball_H
#define Powerball_H

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

#include "SimpleXMLPB.h"
#include "PowerballNumbers.h"

class Powerball
{
	private:
		PowerballNumbers nums;
		SimpleXMLPB xmlNums;
		//unsigned long dateToLong( unsigned int month, unsigned int day, unsigned int year );//Return the date as a long in the format yyyymmdd.
		
	public:
		Powerball();//Constructor
		void readFile( std::string filename );//Read from file filename line by line and parse the lines for the Powerball data.
		void top5wb();//Print the top 5 white ball numbers.toppb
		void toppb();//Print the top 5 white ball numbers.
		void getNums();//Get the numbers from the web and send them to the database.
};

#endif /* Powerball_H */
