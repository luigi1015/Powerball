#include <iostream>
#include "sqlite/sqlite3.h"
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <fstream>

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

PowerballNumbers::PowerballNumbers()
{//Constructor
	unsigned int tableCount;//Used for the return value of a SQL statement.
	char *sqlError = NULL;//To hold the error from sqlite3_exec.
	//Open the database
	returnCode = sqlite3_open( "powerball.db", &db );//Open the database and get the return code.
	if( returnCode != SQLITE_OK )
	{//If return code isn't the OK return code, send error.
		std::cerr << "PowerballNumbers::PowerballNumbers: Error opening the database, powerball.db: " << sqlite3_errmsg(db) << std::endl;
		//sqlite3_close( db );
		return;
	}

	//See if the database has any info in it.
	returnCode = sqlite3_prepare_v2( db, "SELECT count(*) FROM sqlite_master WHERE type='table';", 100, &statement, 0 );//Check to see if there are any tables.
	if( returnCode != SQLITE_OK )
	{//If return code isn't the OK return code, send error.
		fprintf( stderr, "PowerballNumbers::PowerballNumbers: Error checking for tables: %s\n", sqlite3_errmsg(db) );
		//sqlite3_close( db );
		return;
	}
	sqlite3_step( statement );//Step to the first row.
	tableCount = sqlite3_column_int( statement, 0 );//Get the number of tables.
	sqlite3_finalize( statement );//Destroy the prepared statement to free up the database.
	
	if( tableCount < 1 )
	{//Create the table if it isn't there.
		//std::cout << "Didn't find a table, creating one." << std::endl;//Temp status output
		//returnCode = sqlite3_prepare_v2( db, "CREATE TABLE PowerballNums ( Number INTEGER NOT NULL, Date INTEGER NOT NULL, Type TEXT NOT NULL);", 120, &statement, 0 );//Create the table.
		returnCode = sqlite3_exec( db, "CREATE TABLE PowerballNums ( Number INTEGER NOT NULL, Date INTEGER NOT NULL, Type TEXT NOT NULL);", 0, 0, &sqlError );//Create the table.
		//std::cout << "Ran execute." << std::endl;
		if( returnCode != SQLITE_OK )
		{//If return code isn't the OK return code, send error.
			//fprintf( stderr, "Error creating the table: %s\n", sqlite3_errmsg(db) );
			fprintf( stderr, "PowerballNumbers::PowerballNumbers: Error creating the table: %s\n", sqlError );
			//sqlite3_close( db );
			return;
		}
		/*
		else
		{//The table has been created.
			//std::cout << "The table has been created." << std::endl;//Temp check to make sure got ok returncode
		}
		*/
		//std::cout << "Checked error." << std::endl;
		//sqlite3_finalize( statement );//Destroy the prepared statement to free up the database.
	}
	//std::cout << "Add fake numbers with INSERT INTO PowerballNums( Number, Date, Type ) VALUES (1, 1, '1');" << std::endl;
	//returnCode = sqlite3_prepare_v2( db, "INSERT INTO PowerballNums( Number, Date, Type ) VALUES (1, 1, '1');", 120, &statement, 0 );//Create the table.
	/*
	std::cout << "Add fake numbers with INSERT INTO PowerballNums VALUES (1, 1, '1');" << std::endl;
	//returnCode = sqlite3_prepare_v2( db, "INSERT INTO PowerballNums VALUES (1, 1, '1');", 120, &statement, 0 );//Create the table.
	returnCode = sqlite3_exec( db, "INSERT INTO PowerballNums VALUES (1, 1, '1');", 0, 0, &sqlError );//Create the table.
	if( returnCode != SQLITE_OK )
	{//If return code isn't the OK return code, send error.
		//fprintf( stderr, "Error inserting into the table: %s\n", sqlite3_errmsg(db) );
		fprintf( stderr, "Error inserting into the table: %s\n", sqlError );
		//sqlite3_close( db );
		return;
	}
	else
	{//The table has been created.
		std::cout << "The data has been inserted." << std::endl;//Temp check to make sure got ok returncode
	}
	*/
	//sqlite3_finalize( statement );//Destroy the prepared statement to free up the database.
	//sqlite3_close( db );//Close the database.
}

PowerballNumbers::~PowerballNumbers()
{//Destructor
	sqlite3_close( db );//Close the database.
}

unsigned long PowerballNumbers::numCount()
{//Returns how many numbers in the database.
	unsigned long numberCount;//Used for the number count.

	//Get the number count.
	returnCode = sqlite3_prepare_v2( db, "SELECT count(*) FROM PowerballNums;", 70, &statement, 0 );//Check to see if there are any tables.
	if( returnCode != SQLITE_OK )
	{//If return code isn't the OK return code, send error.
		fprintf( stderr, "PowerballNumbers::numCount: Error getting the number count: %s\n", sqlite3_errmsg(db) );
		//sqlite3_close( db );
		return 0;
	}
	sqlite3_step( statement );//Step to the first row.
	numberCount = sqlite3_column_int( statement, 0 );//Get the number of tables.
	sqlite3_finalize( statement );//Destroy the prepared statement to free up the database.
	
	return numberCount;
}

bool PowerballNumbers::addNum( unsigned char number, unsigned char month, unsigned char day, unsigned int year, PowerballTypes type )
{//Add a number with an associated drawing date and type (white ball, Powerball, PowerPlay). Returns true if the add succeeded or false if not.
	char sqlStatement[100];//To represent the sql statement
	char *sqlError;//To hold errors from sqlite3_exec
	//snprintf( sqlStatement, 100, "INSERT INTO PowerballNums( Number, Date, Type ) VALUES (%u, %u, '%d');", number, (day+month*100+year*10000), type );
	snprintf( sqlStatement, 100, "INSERT INTO PowerballNums( Number, Date, Type ) VALUES (%u, %lu, '%d');", number, dateToLong(month, day, year), type );
	//std::cout << sqlStatement << std::endl;//Temp sanity check on the sql statement.
	returnCode = sqlite3_exec( db, sqlStatement, 0, 0, &sqlError );//Create the table.
	if( returnCode != SQLITE_OK )
	{//If return code isn't the OK return code, send error.
		//fprintf( stderr, "Error inserting a number into the table: %s\n", sqlite3_errmsg(db) );
		fprintf( stderr, "PowerballNumbers::addNum: Error inserting a number into the table: %s\n", sqlError );
		//sqlite3_close( db );
		return false;
	}
	//sqlite3_finalize( statement );//Destroy the prepared statement to free up the database.
	return true;
}

bool PowerballNumbers::addNumWCheck( unsigned char number, unsigned char month, unsigned char day, unsigned int year, PowerballTypes type )
{//Same with addNum but checks isSaved first.
	if( isSaved(number, month, day, year, type) == false )
	{//Isn't in the database, add it.
		return addNum(number, month, day, year, type);
	}
	else
	{//Is in the database, return false.
		return false;
	}
}

unsigned long PowerballNumbers::dateToLong( unsigned int month, unsigned int day, unsigned int year )
{//Return the date as a long in the format yyyymmdd.
	return day + month*100 + year*10000;
}

void PowerballNumbers::clear()
{//Clear the list of stored numbers.
	char *sqlError;//To hold errors from sqlite3_exec
	//returnCode = sqlite3_prepare_v2( db, "DELETE FROM PowerballNums;", 70, &statement, 0 );//SQL to delete all rows from PowerballNums.
	returnCode = sqlite3_exec( db, "DELETE FROM PowerballNums;", 0, 0, &sqlError );//SQL to delete all rows from PowerballNums.
	if( returnCode != SQLITE_OK )
	{//If return code isn't the OK return code, send error.
		fprintf( stderr, "PowerballNumbers::clear: Error clearing PowerballNums: %s\n", sqlError );
		//sqlite3_close( db );
		return;
	}
	//sqlite3_finalize( statement );//Destroy the prepared statement to free up the database.
}

bool PowerballNumbers::isSaved( unsigned char number, unsigned char month, unsigned char day, unsigned int year, PowerballTypes type )
{//Checked if a number is in the database. Returns true if yes, false if not.
	unsigned long numberCount;//Used for how many records matching the data given is in the database.
	char sqlStatement[100];//To represent the sql statement

	//Get the count of the records matching the data given is in the database.
	snprintf( sqlStatement, 100, "SELECT count(*) FROM PowerballNums WHERE Number=%u AND Date=%lu AND Type='%d';", number, dateToLong(month, day, year), type );
	//std::cout << sqlStatement << std::endl;//Temp check of sqlStatement.
	returnCode = sqlite3_prepare_v2( db, sqlStatement, 100, &statement, 0 );//Check to see if there are any tables.
	if( returnCode != SQLITE_OK )
	{//If return code isn't the OK return code, send error.
		fprintf( stderr, "PowerballNumbers::isSaved: Error getting the number of matches: %s\n", sqlite3_errmsg(db) );
		//sqlite3_close( db );
		return 0;
	}
	sqlite3_step( statement );//Step to the first row.
	numberCount = sqlite3_column_int( statement, 0 );//Get the number of tables.
	sqlite3_finalize( statement );//Destroy the prepared statement to free up the database.
	
	return (numberCount > 0);
}

std::vector<std::pair<int, int> > PowerballNumbers::topNumsByType( unsigned char count, PowerballTypes type )
{//Returns the top count numbers in the database of type type in terms of number of occurences as a vector<int, int>. The first int is the number and the second int is the number of occurences.
	std::vector<std::pair<int, int> > topNumbers;//Used for the top numbers.
	char sqlStatement[200];//To represent the sql statement

	//Get the count of the records matching the data given is in the database.
	//snprintf( sqlStatement, 100, "SELECT Number, count(*) FROM PowerballNums WHERE Type='%d' GROUP BY Number ORDER BY NUMBER LIMIT %u;", type, count );
	snprintf( sqlStatement, 200, "SELECT Number, count(*) AS Count FROM PowerballNums WHERE Type='%d' GROUP BY Number ORDER BY Count DESC LIMIT %u;", type, count );
	//std::cout << sqlStatement << std::endl;//Temp check of sqlStatement.
	returnCode = sqlite3_prepare_v2( db, sqlStatement, 200, &statement, 0 );//Check to see if there are any tables.
	if( returnCode != SQLITE_OK )
	{//If return code isn't the OK return code, send error.
		fprintf( stderr, "PowerballNumbers::topNumsByType: Error getting the top numbers: %s\n", sqlite3_errmsg(db) );
		//sqlite3_close( db );
		return topNumbers;
	}
	while( sqlite3_step(statement) == SQLITE_ROW )
	{//Step through the rows while there are still rows left.
		topNumbers.push_back( std::pair<int, int>(sqlite3_column_int(statement, 0), sqlite3_column_int(statement, 1)) );//Get the number of tables.
	}
	sqlite3_finalize( statement );//Destroy the prepared statement to free up the database.
	
	return topNumbers;
}

unsigned int PowerballNumbers::getDrawings()
{//Returns the total number of drawings in the database.
	unsigned int numDrawings;
	returnCode = sqlite3_prepare_v2( db, "SELECT count(DISTINCT Date) FROM PowerballNums;", 100, &statement, 0 );//Get the number of drawings by getting the count of dates.
	if( returnCode != SQLITE_OK )
	{//If return code isn't the OK return code, send error.
		fprintf( stderr, "PowerballNumbers::getDrawings: Error getting the number of drawings: %s\n", sqlite3_errmsg(db) );
		//sqlite3_close( db );
		return 0;
	}
	sqlite3_step( statement );//Step to the first row.
	numDrawings = sqlite3_column_int( statement, 0 );//Get the number of drawings.
	sqlite3_finalize( statement );//Destroy the prepared statement to free up the database.
	
	return numDrawings;
}

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

Powerball::Powerball()
{//Constructor
}
/*
unsigned long Powerball::dateToLong( unsigned int month, unsigned int day, unsigned int year )
{//Return the date as a long in the format yyyymmdd.
	return day + month*100 + year*10000;
}
*/

void Powerball::readFile( std::string filename )
{//Read from file filename line by line and parse the lines for the Powerball data.
	std::string pbLine;//To represent a line of the Powerball file.
	std::ifstream pbFile( filename.c_str() );//Open the powerball file for reading.
	unsigned int year;//Year of the Powerball drawing date.
	unsigned int month, day, wb1, wb2, wb3, wb4, wb5, pb, pp;//The month and day of the drawing date along with the white ball numbers, powerball and power play numbers.
	unsigned int numLines = 0;//Number of lines processed.
	//PBNum pbNum;//To represent a Powerball number
	//unsigned long dateNum;//A date in the format yyyymmdd.
	
	while( getline(pbFile, pbLine) )
	{//While there are still lines to read in the file, read lines into pbLine.
		//if( sscanf( pbLine.c_str(), "%ud/%ud/%ud  %ud  %ud  %ud  %ud  %ud  %ud  %ud", &month, &day, &year, &wb1, &wb2, &wb3, &wb4, &wb5, &pb, &pp) != 0)
		pp = 0;
		if( sscanf( pbLine.c_str(), "%d/%d/%d  %d  %d  %d  %d  %d  %d  %d", &month, &day, &year, &wb1, &wb2, &wb3, &wb4, &wb5, &pb, &pp) != 0)
		{//As long as got something.
			//printf("Date: %ud/%ud/%ud\nwb1: '%ud'\nwb2: '%ud'\nwb3: '%ud'\nwb4: '%ud'\nwb5: '%ud'\npb: '%ud'\npp: '%ud'\n", month, day, year, wb1, wb2, wb3, wb4, wb5, pb, pp);
			//printf("Date: %u/%u/%u\nwb1: '%u'\nwb2: '%u'\nwb3: '%u'\nwb4: '%u'\nwb5: '%u'\npb: '%u'\npp: '%u'\n", month, day, year, wb1, wb2, wb3, wb4, wb5, pb, pp);
			//printf("Date: %u/%u/%u\twb1: '%u'\twb2: '%u'\twb3: '%u'\twb4: '%u'\twb5: '%u'\tpb: '%u'\tpp: '%u'\n", month, day, year, wb1, wb2, wb3, wb4, wb5, pb, pp);
			if( nums.isSaved(wb1, month, day, year, nums.White) == false )
			{//If the number isn't in the database. save it to the database.
				std::cout << "Adding number " << wb1 << " " << month << "/" << day << "/" << year << "White ball." << std::endl;
				nums.addNum( wb1, month, day, year, nums.White );
				xmlNums.addNum( wb1, month, day, year, nums.White );
			}
			else
			{
				//std::cout << "Already in the database." << std::endl;
				xmlNums.addNum( wb1, month, day, year, nums.White );
			}
			if( nums.isSaved(wb2, month, day, year, nums.White) == false )
			{//If the number isn't in the database. save it to the database.
				std::cout << "Adding number " << wb2 << " " << month << "/" << day << "/" << year << " White ball." << std::endl;
				nums.addNum( wb2, month, day, year, nums.White );
				xmlNums.addNum( wb2, month, day, year, nums.White );
			}
			else
			{
				//std::cout << "Already in the database." << std::endl;
				xmlNums.addNum( wb2, month, day, year, nums.White );
			}
			if( nums.isSaved(wb3, month, day, year, nums.White) == false )
			{//If the number isn't in the database. save it to the database.
				std::cout << "Adding number " << wb3 << " " << month << "/" << day << "/" << year << " White ball." << std::endl;
				nums.addNum( wb3, month, day, year, nums.White );
				xmlNums.addNum( wb3, month, day, year, nums.White );
			}
			else
			{
				//std::cout << "Already in the database." << std::endl;
				xmlNums.addNum( wb3, month, day, year, nums.White );
			}
			if( nums.isSaved(wb4, month, day, year, nums.White) == false )
			{//If the number isn't in the database. save it to the database.
				std::cout << "Adding number " << wb4 << " " << month << "/" << day << "/" << year << " White ball." << std::endl;
				nums.addNum( wb4, month, day, year, nums.White );
				xmlNums.addNum( wb4, month, day, year, nums.White );
			}
			else
			{
				//std::cout << "Already in the database." << std::endl;
				xmlNums.addNum( wb4, month, day, year, nums.White );
			}
			if( nums.isSaved(wb5, month, day, year, nums.White) == false )
			{//If the number isn't in the database. save it to the database.
				std::cout << "Adding number " << wb5 << " " << month << "/" << day << "/" << year << " White ball." << std::endl;
				nums.addNum( wb5, month, day, year, nums.White );
				xmlNums.addNum( wb5, month, day, year, nums.White );
			}
			else
			{
				//std::cout << "Already in the database." << std::endl;
				xmlNums.addNum( wb5, month, day, year, nums.White );
			}
			if( nums.isSaved(pb, month, day, year, nums.Powerball) == false )
			{//If the number isn't in the database. save it to the database.
				std::cout << "Adding number " << pb << " " << month << "/" << day << "/" << year << " Powerball." << std::endl;
				nums.addNum( pb, month, day, year, nums.Powerball );
				xmlNums.addNum( pb, month, day, year, nums.Powerball );
			}
			else
			{
				//std::cout << "Already in the database." << std::endl;
				xmlNums.addNum( pb, month, day, year, nums.Powerball );
			}
			numLines++;
		}
		if( pp != 0 )
		{//If pp was scanned in from sscanf above.
			if( nums.isSaved(pp, month, day, year, nums.PowerPlay) == false )
			{//If the number isn't in the database. save it to the database.
				std::cout << "Adding number " << pp << " " << month << "/" << day << "/" << year << " Power Play." << std::endl;
				nums.addNum( pp, month, day, year, nums.PowerPlay );
				xmlNums.addNum( pp, month, day, year, nums.PowerPlay );
			}
			else
			{
				//std::cout << "Already in the database." << std::endl;
				xmlNums.addNum( pp, month, day, year, nums.PowerPlay );
			}
		}
	}
	xmlNums.saveToFile( "Powerball.xml" );
	xmlNums.loadFromFile( "Powerball.xml" );
	printf( "Number lines processed: %u\n", numLines );
	printf( "Number count in the database: %lu\n", nums.numCount() );
}

void Powerball::getNums()
{//Get the numbers from the web and send them to the database.
	system( "rm winnums-text.txt" );
	system( "wget http://www.powerball.com/powerball/winnums-text.txt" );
	readFile( "winnums-text.txt" );
}

void Powerball::top5wb()
{//Print the top 5 white ball numbers.
	std::vector<std::pair<int, int> > top5wbnums = nums.topNumsByType( 5, nums.White );
	unsigned int numDrawings = nums.getDrawings();
	for( size_t i = 0; i < top5wbnums.size(); i++ )
	{//Go through the elements in the vector and print them.
		std::cout << top5wbnums[i].first << ": " << top5wbnums[i].second << " out of " << numDrawings << " drawings (" << (100.0*top5wbnums[i].second)/numDrawings << "%)" << std::endl;
	}
}

void Powerball::toppb()
{//Print the top powerball numbers.
	std::vector<std::pair<int, int> > toppbnums = nums.topNumsByType( 1, nums.Powerball );
	unsigned int numDrawings = nums.getDrawings();
	for( size_t i = 0; i < toppbnums.size(); i++ )
	{//Go through the elements in the vector and print them.
		std::cout << toppbnums[i].first << ": " << toppbnums[i].second << " out of " << numDrawings << " drawings (" << (100.0*toppbnums[i].second)/numDrawings << "%)" << std::endl;
	}
}

int main()
{
	Powerball pb;
	//pb.readFile( "winnums-text.txt" );
	pb.getNums();
	std::cout << "Top White balls:" << std::endl;
	std::cout << "Number: Count" << std::endl;
	pb.top5wb();
	std::cout << std::endl << "Top Powerball:" << std::endl;
	std::cout << "Number: Count" << std::endl;
	pb.toppb();
	return 0;
}
