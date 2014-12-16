#ifndef SimpleJSONPB_H
#define SimpleJSONPB_H

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
#include <string>

#include "PBNum.h"

class SimpleJSONPB
{//Simply saves and loads data to and from a JSON file.
	private:
		std::vector<PBNum> pbNumbers;
		
	public:
		SimpleJSONPB( std::string filename );//Constructor with filename
		SimpleJSONPB();//Constructor
		void saveToFile( std::string filename );//Save the numbers data to a file in JSON format.
		void loadFromFile( std::string filename );//Load the JSON formatted numbers.
		std::vector<PBNum> getNumbers();//Return the numbers as a vector.
		void addNum( PBNum number );//Add a number.
		void addNum(  unsigned int newNum, unsigned char newMonth, unsigned char newDay, unsigned int newYear, unsigned char newType );//Add a number.
		void clear();//Clear the numbers.
};

#endif /* SimpleJSONPB_H */
