#include <iostream>
//#include "sqlite/sqlite3.h"
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <fstream>

#include "SimpleXMLPB.h"

/*
class SimpleXMLPB
{//A single powerball number
	private:
		std::vector<PBNum> pbNumbers;
		
	public:
		SimpleXMLPB( std::string filename );//Constructor
		SimpleXMLPB();//Constructor
		void saveToFile( std::string filename );//Save the numbers data to a file in XML format.
		void loadFromFile( std::string filename );//Load the XML file numbers.
		std::vector<PBNum> getNumbers();//Return the numbers as a vector.
		void addNum( PBNum number );//Add a number.
		void addNum(  unsigned int newNum, unsigned char newMonth, unsigned char newDay, unsigned int newYear, unsigned char newType );//Add a number.
		void clear();//Clear the numbers.
};
*/

SimpleXMLPB::SimpleXMLPB()
{//Constructor
}

SimpleXMLPB::SimpleXMLPB( std::string filename )
{//Constructor
	loadFromFile( filename );
}

std::vector<PBNum> SimpleXMLPB::getNumbers()
{//Return the numbers as a vector.
	return pbNumbers;
}

void SimpleXMLPB::addNum( PBNum number )
{//Add a number.
	pbNumbers.push_back( number );
}

void SimpleXMLPB::addNum(  unsigned int newNum, unsigned char newMonth, unsigned char newDay, unsigned int newYear, unsigned char newType )
{//Add a number.
	PBNum newPBNum;
	newPBNum.setNumber( newNum );
	newPBNum.setDate( newMonth, newDay, newYear );
	newPBNum.setType( newType );
	pbNumbers.push_back( newPBNum );
}
void SimpleXMLPB::clear()
{//Clear the numbers.
	pbNumbers.clear();
}

void SimpleXMLPB::saveToFile( std::string filename )
{//Save the numbers data to a file in XML format.
	std::ofstream XMLFile;
	XMLFile.open( filename.c_str(), std::ios::out | std::ios::trunc );//Open for output and truncate any previous data in the file.
	XMLFile << "<Powerball>" << std::endl;
	XMLFile << "\t<Version>1.0</Version>" << std::endl;
	for( std::vector<PBNum>::iterator num = pbNumbers.begin(); num != pbNumbers.end(); num++ )
	{//Go through each of the PBNums in the vector and output each individually as XML.
		XMLFile << "\t<number>" << std::endl;
		XMLFile << "\t\t<num>" << (*num).getNumber() << "</num>" << std::endl;
		XMLFile << "\t\t<month>" << (int)(*num).getMonth() << "</month>" << std::endl;
		XMLFile << "\t\t<day>" << (int)(*num).getDay() << "</day>" << std::endl;
		XMLFile << "\t\t<year>" << (*num).getYear() << "</year>" << std::endl;
		XMLFile << "\t\t<type>" << (*num).getType() << "</type>" << std::endl;
		XMLFile << "\t</number>" << std::endl;
	}
	XMLFile << "</Powerball>";
	XMLFile.close();
}

void SimpleXMLPB::loadFromFile( std::string filename )
{//Load the XML file numbers.
	std::string line;//To hold a line from the file.
	std::ifstream inXML( filename.c_str() );//Input file stream of the XML file.
	PBNum powerballNumber;//To temporarily represent a powerball number.
	unsigned int num;//The number drawn.
	unsigned int month, day;//The month and day of the date it was drawn.
	unsigned int year;//The year of the date it was drawn.
	unsigned int type;//The type of number drawn.
	double version;//The version of the XML design.
	
	if( inXML.is_open() )
	{//As long as file has been opened.
		std::getline( inXML, line );//Get first line, should just be "<Powerball>", so nothing to see here.
		std::getline( inXML, line );//Get second line, should just be the version number.
		sscanf( line.c_str(), "\t<Version>%lf</Version>", &version );//Get the version number.
		std::cout << "Powerball XML version " << version << std::endl;
		
		while( inXML.good() )
		{//While can still read lines, try to read in the Powerball info
			std::getline( inXML, line );//Should be the first line of the Powerball info of a number.
			if( line.compare("\t<number>") == 0 )
			{//It's the first line of the Powerball info of a number, so go ahead and read the rest of the info.
				std::getline( inXML, line );//Should be the number.
				sscanf( line.c_str(), "\t\t<num>%u</num>", &num );//Get the number
				std::getline( inXML, line );//Should be the month.
				sscanf( line.c_str(), "\t\t<month>%u</month>", &month );//Get the month
				std::getline( inXML, line );//Should be the day.
				sscanf( line.c_str(), "\t\t<day>%u</day>", &day );//Get the day
				std::getline( inXML, line );//Should be the year.
				sscanf( line.c_str(), "\t\t<year>%u</year>", &year );//Get the year
				std::getline( inXML, line );//Should be the type.
				sscanf( line.c_str(), "\t\t<type>%u</type>", &type );//Get the type
				powerballNumber.setNumber( num );
				powerballNumber.setDate( month, day, year );
				powerballNumber.setType( type );
				//std::cout << powerballNumber.getMonth() << "/" << powerballNumber.getDay() << "/" << powerballNumber.getYear() << " Num: " << powerballNumber.getNumber() << " Type: " << powerballNumber.getType() << std::endl;
				//std::cout << month << "/" << day << "/" << year << " Num: " << num << " Type: " << type << std::endl;
			}
		}
	}
	else
	{
		std::cerr << "SimpleXMLPB::loadFromFile - Couldn't open file " << filename << std::endl;
	}
}
