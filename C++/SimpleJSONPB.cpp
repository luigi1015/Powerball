#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "SimpleJSONPB.h"
#include "PBNum.h"

/*
class SimpleJSONPB
{//Simply saves and loads data to and from a JSON file.
	private:
		std::vector<PBNum> pbNumbers;
		
	public:
		SimpleJSONPB( std::string filename );//Constructor with filename
		SimpleJSONPB();//Constructor
		void saveToFile( std::string filename );//Save the numbers data to a file in JSON format.
		void loadFromFile( std::string filename );//Load the JSON file numbers.
		std::vector<PBNum> getNumbers();//Return the numbers as a vector.
		void addNum( PBNum number );//Add a number.
		void addNum(  unsigned int newNum, unsigned char newMonth, unsigned char newDay, unsigned int newYear, unsigned char newType );//Add a number.
		void clear();//Clear the numbers.
};
*/

SimpleJSONPB::SimpleJSONPB()
{//Constructor
}

SimpleJSONPB::SimpleJSONPB( std::string filename )
{//Constructor with filename
	loadFromFile( filename );
}

std::vector<PBNum> SimpleJSONPB::getNumbers()
{//Return the numbers as a vector.
	return pbNumbers;
}

void SimpleJSONPB::addNum( PBNum number )
{//Add a number.
	pbNumbers.push_back( number );
}

void SimpleJSONPB::addNum(  unsigned int newNum, unsigned char newMonth, unsigned char newDay, unsigned int newYear, unsigned char newType )
{//Add a number.
	PBNum newPBNum;
	newPBNum.setNumber( newNum );
	newPBNum.setDate( newMonth, newDay, newYear );
	newPBNum.setType( newType );
	pbNumbers.push_back( newPBNum );
}
void SimpleJSONPB::clear()
{//Clear the numbers.
	pbNumbers.clear();
}

void SimpleJSONPB::saveToFile( std::string filename )
{//Save the numbers data to a file in JSON format.
	std::ofstream JSONFile;
	JSONFile.open( filename.c_str(), std::ios::out | std::ios::trunc );//Open for output and truncate any previous data in the file.
	JSONFile << "{" << std::endl;
	JSONFile << "\"fileFormatVersion\": 0.1," << std::endl;
	JSONFile << "\"numbers\":[" << std::endl;
	for( std::vector<PBNum>::iterator num = pbNumbers.begin(); num != pbNumbers.end(); num++ )
	{//Go through each of the PBNums in the vector and output each individually as JSON data.
		JSONFile << "\t{";
		JSONFile << "\"number\": " << (*num).getNumber() << ", ";
		JSONFile << "\"month\": " << (int)(*num).getMonth() << ", ";
		JSONFile << "\"day\": " << (int)(*num).getDay() << ", ";
		JSONFile << "\"year\": " << (*num).getYear() << ", ";
		JSONFile << "\"type\": \"" << (*num).getType() << "\"";
		if( (num != pbNumbers.end()) && (num + 1 == pbNumbers.end()) )
		{//At the last element since the next element is the end iterator.
			JSONFile << "}" << std::endl;//Don't put a comma at the end.
		}
		else
		{//Not at the last element.
			JSONFile << "}," << std::endl;//Put a comma at the end.
		}
	}
	JSONFile << "]";
	JSONFile << "}";
	JSONFile.close();
}

void SimpleJSONPB::loadFromFile( std::string filename )
{//Load the JSON formatted numbers.
/*
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
		std::cerr << "SimpleJSONPB::loadFromFile - Couldn't open file " << filename << std::endl;
	}
*/
}
