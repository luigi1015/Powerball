#ifndef SimpleXMLPB_H
#define SimpleXMLPB_H

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

class SimpleXMLPB
{//Simply saves and loads data to and from an XML file.
	private:
		std::vector<PBNum> pbNumbers;
		
	public:
		SimpleXMLPB( std::string filename );//Constructor with filename
		SimpleXMLPB();//Constructor
		void saveToFile( std::string filename );//Save the numbers data to a file in XML format.
		void loadFromFile( std::string filename );//Load the XML file numbers.
		std::vector<PBNum> getNumbers();//Return the numbers as a vector.
		void addNum( PBNum number );//Add a number.
		void addNum(  unsigned int newNum, unsigned char newMonth, unsigned char newDay, unsigned int newYear, unsigned char newType );//Add a number.
		void clear();//Clear the numbers.
};

#endif /* SimpleXMLPB_H */
