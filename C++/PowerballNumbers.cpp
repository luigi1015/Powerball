#include <iostream>
#include "sqlite/sqlite3.h"
//#include <string>
#include <vector>
#include <set>
#include <stdio.h>
//#include <stdlib.h>
//#include <cstring>
//#include <fstream>
#include <utility>
#include <string>
#include <sstream>

#include "PowerballNumbers.h"

/*
class PowerballNumbers
{
	private:
		sqlite3 *db;//Database variable.
		char *errMsg;//SQLite error message variable.
		int returnCode;//Return code variable for SQLite function.
		sqlite3_stmt *statement;//SQL statement variable.
		unsigned long dateToLong( unsigned int month, unsigned int day, unsigned int year );//Return the date as a long in the format yyyymmdd.
		//std::vector<PBNum> numbers;
		std::set<PBNum> nums;
		
	public:
		enum PowerballTypes{ White, Powerball, PowerPlay };//The types of numbers stored in the database.
		PowerballNumbers();//Constructor
		~PowerballNumbers();//Destructor
		void addNum( unsigned char number, unsigned char month, unsigned char day, unsigned int year, PowerballTypes type );//Add a number with an associated drawing date and type (white ball, Powerball, PowerPlay).
		bool addNumWCheck( unsigned char number, unsigned char month, unsigned char day, unsigned int year, PowerballTypes type );//Same with addNum but checks isSaved first.
		void clear();//Clear the list of stored numbers.
		unsigned long numCount();//Returns how many numbers in memory.
		bool isSaved( unsigned char number, unsigned char month, unsigned char day, unsigned int year, PowerballTypes type );//Checked if a number is in the database. Returns true if yes, false if not.
		std::vector<std::pair<int, int> > topNumsByType( unsigned char count, PowerballTypes type );//Returns the top count numbers in the database of type type in terms of number of occurences as a vector<pair<int, int>>.The first int is the number and the second int is the number of occurences.
		unsigned int getDrawings();//Returns the total number of drawings in the database.
		void load();//Loads the data in the database into the nums object.
		void save();//Saves the data in the nums object to the database.
};
*/

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
		//returnCode = sqlite3_exec( db, "CREATE TABLE PowerballNums ( Number INTEGER NOT NULL, Date NUMERIC NOT NULL, Type TEXT NOT NULL);", 0, 0, &sqlError );//Create the table.
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
	//Probably should save the data in nums to the database before closing the database.

	sqlite3_close( db );//Close the database.
}

unsigned long PowerballNumbers::numCount()
{//Returns how many numbers in memory.
	return nums.size();
/*
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
*/
}

bool PowerballNumbers::addNum( unsigned char number, unsigned char month, unsigned char day, unsigned int year, PowerballTypes type )
{//Add a number with an associated drawing date and type (white ball, Powerball, PowerPlay).
	//std::pair<std::set<PBNum>::iterator, bool> insertInfo = nums.insert( PBNum(number, month, day, year, type) );
	//return insertInfo.second;
	nums.insert( PBNum(number, month, day, year, type) );

	char sqlStatement[100];//To represent the sql statement
	char *sqlError;//To hold errors from sqlite3_exec
	//snprintf( sqlStatement, 100, "INSERT INTO PowerballNums( Number, Date, Type ) VALUES (%u, %u, '%d');", number, (day+month*100+year*10000), type );
	snprintf( sqlStatement, 100, "INSERT INTO PowerballNums( Number, Date, Type ) VALUES (%u, %lu, '%d');", number, dateToLong(month, day, year), type );
	std::cout << sqlStatement << std::endl;//Temp sanity check on the sql statement.
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

bool PowerballNumbers::addNums( std::set<PBNum> newNums )
{//Add a set of numbers with their associated drawing dates and types (white ball, Powerball, PowerPlay).
	std::stringstream sqlStatement;
	//std::pair<std::set<PBNum>::iterator, bool> insertInfo = nums.insert( PBNum(number, month, day, year, type) );
	//return insertInfo.second;
	nums.insert( newNums.begin(), newNums.end() );

	//std::string sqlStatement = "";//To represent the sql statement
	char *sqlError;//To hold errors from sqlite3_exec
	//snprintf( sqlStatement, 100, "INSERT INTO PowerballNums( Number, Date, Type ) VALUES (%u, %u, '%d');", number, (day+month*100+year*10000), type );
	//snprintf( sqlStatement, 100, "INSERT INTO PowerballNums( Number, Date, Type ) VALUES (%u, %lu, '%d');", number, dateToLong(month, day, year), type );
	
	//for( int i = 0; i < newNums.size(); i++ )
	std::set<PBNum>::iterator newPowerballNumber = newNums.begin();
/*
	sqlStatement << "INSERT INTO PowerballNums( Number, Date, Type ) VALUES (";
	sqlStatement << (*newPowerballNumber).getNumber();
	sqlStatement << ", ";
	sqlStatement << (*newPowerballNumber).getDate();
	sqlStatement << ", ";
	sqlStatement << (*newPowerballNumber).getType();
	sqlStatement << ")";
	newPowerballNumber++;
*/
	//sqlStatement << "BEGIN TRANSACTION\n";

	while( newPowerballNumber != newNums.end() )
	{
		//sqlStatement << ", (";
		sqlStatement << "INSERT INTO PowerballNums ( Number, Date, Type ) VALUES (";
		sqlStatement << (*newPowerballNumber).getNumber();
		sqlStatement << ", ";
		sqlStatement << (*newPowerballNumber).getDate();
		sqlStatement << ", '";
		sqlStatement << (*newPowerballNumber).getType();
		sqlStatement << "');\n";
		newPowerballNumber++;
	}

	//sqlStatement << "END TRANSACTION\n";

	std::cout << sqlStatement.str() << std::endl;//Temp sanity check on the sql statement.

	returnCode = sqlite3_exec( db, sqlStatement.str().c_str(), 0, 0, &sqlError );//Insert the data.
	if( returnCode != SQLITE_OK )
	{//If return code isn't the OK return code, send error.
		//fprintf( stderr, "Error inserting a number into the table: %s\n", sqlite3_errmsg(db) );
		fprintf( stderr, "PowerballNumbers::addNums: Error inserting a number into the table: %s\n", sqlError );
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

bool PowerballNumbers::isSavedToDB( unsigned char number, unsigned char month, unsigned char day, unsigned int year, PowerballTypes type )
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

bool PowerballNumbers::isSaved( unsigned char number, unsigned char month, unsigned char day, unsigned int year, PowerballTypes type )
{//Checked if a number is in memory. Returns true if yes, false if not.
	//bool isSaved = false;
	std::set<PBNum>::iterator powerballNumberIterator = nums.begin();

	//Go through each number and check it until the end or a number equal to the parameter values is found.
	while( (powerballNumberIterator != nums.end()) && !((*powerballNumberIterator).equals(number, month, day, year, type)) )
	{
		powerballNumberIterator++;
	}

	//If it reached the end, it didn't find a number equal to the values, so return the opposite boolean value to whether it reached the end.
	return !(powerballNumberIterator == nums.end());
}

std::vector<std::pair<int, int> > PowerballNumbers::topNumsByType( unsigned char count, PowerballTypes type )
{//Returns the top count numbers in the database of type type in terms of number of occurences as a vector<int, int>. The first int is the number and the second int is the number of occurences.
	std::vector<std::pair<int, int> > topNumbers;//Used for the top numbers.
	char sqlStatement[200];//To represent the sql statement

	//Get the count of the records matching the data given is in the database.
	//snprintf( sqlStatement, 100, "SELECT Number, count(*) FROM PowerballNums WHERE Type='%d' GROUP BY Number ORDER BY NUMBER LIMIT %u;", type, count );
	snprintf( sqlStatement, 200, "SELECT Number, count(*) AS Count FROM PowerballNums WHERE Type='%d' GROUP BY Number ORDER BY Count DESC LIMIT %u;", type, count );
	std::cout << sqlStatement << std::endl;
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
		std::cout << "Processing a row in topNumsByType" << std::endl;
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

void PowerballNumbers::load()
{//Loads the data in the database into the nums object.
	char sqlStatement[200];//To represent the sql statement

	//Get the count of the records matching the data given is in the database.
	snprintf( sqlStatement, 200, "SELECT Number, Date, Type FROM PowerballNums;" );//Create the SQL statement.
	returnCode = sqlite3_prepare_v2( db, sqlStatement, 200, &statement, 0 );//Run the SQL statement.
	if( returnCode != SQLITE_OK )
	{//If return code isn't the OK return code, send error.
		fprintf( stderr, "PowerballNumbers::load: Error getting the numbers from the database: %s\n", sqlite3_errmsg(db) );
	}
	while( sqlite3_step(statement) == SQLITE_ROW )
	{//Step through the rows returned from the SQL statement while there are still rows left.
		//topNumbers.push_back( std::pair<int, int>(sqlite3_column_int(statement, 0), sqlite3_column_int(statement, 1)) );//Get the number of tables.
		//numbers.push_back( PBNum(sqlite3_column_int(statement, 0), sqlite3_column_int(statement, 1), sqlite3_column_int(statement, 2)) );//Get the number of tables.
		nums.insert( PBNum(sqlite3_column_int(statement, 0), sqlite3_column_int(statement, 1), sqlite3_column_int(statement, 2)) );//Put the number in the set.
	}
	sqlite3_finalize( statement );//Destroy the prepared statement to free up the database.
}

void PowerballNumbers::save()
{//Saves the data in the nums object to the database.
	//Probably a good idea to use "OR IGNORE" clause in the SQL Insert statement.
}
