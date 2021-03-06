#include <iostream>
//#include "sqlite/sqlite3.h"
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <fstream>
#include <set>

#include "Powerball.h"

/*
class Powerball
{
	private:
		PowerballNumbers nums;
		SimpleXMLPB xmlNums;
		SimpleJSONPB jsonNums;
		//unsigned long dateToLong( unsigned int month, unsigned int day, unsigned int year );//Return the date as a long in the format yyyymmdd.
		
	public:
		Powerball();//Constructor
		void readFile( std::string filename );//Read from file filename line by line and parse the lines for the Powerball data.
		void top5wb();//Print the top 5 white ball numbers.toppb
		void toppb();//Print the top 5 white ball numbers.
		void getNums();//Get the numbers from the web and send them to the database.
};
*/

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
	PBNum pbNum;//To represent a Powerball number
	//unsigned long dateNum;//A date in the format yyyymmdd.
	std::set<PBNum> numsToSave;

	std::cout << "Processing " << filename << std::endl;
	while( getline(pbFile, pbLine) )
	{//While there are still lines to read in the file, read lines into pbLine.
		//if( sscanf( pbLine.c_str(), "%ud/%ud/%ud  %ud  %ud  %ud  %ud  %ud  %ud  %ud", &month, &day, &year, &wb1, &wb2, &wb3, &wb4, &wb5, &pb, &pp) != 0)
		pp = 0;
		if( sscanf( pbLine.c_str(), "%d/%d/%d  %d  %d  %d  %d  %d  %d  %d", &month, &day, &year, &wb1, &wb2, &wb3, &wb4, &wb5, &pb, &pp) != 0)
		{//As long as got something.
			//printf("Date: %ud/%ud/%ud\nwb1: '%ud'\nwb2: '%ud'\nwb3: '%ud'\nwb4: '%ud'\nwb5: '%ud'\npb: '%ud'\npp: '%ud'\n", month, day, year, wb1, wb2, wb3, wb4, wb5, pb, pp);
			//printf("Date: %u/%u/%u\nwb1: '%u'\nwb2: '%u'\nwb3: '%u'\nwb4: '%u'\nwb5: '%u'\npb: '%u'\npp: '%u'\n", month, day, year, wb1, wb2, wb3, wb4, wb5, pb, pp);
			//printf("Date: %u/%u/%u\twb1: '%u'\twb2: '%u'\twb3: '%u'\twb4: '%u'\twb5: '%u'\tpb: '%u'\tpp: '%u'\n", month, day, year, wb1, wb2, wb3, wb4, wb5, pb, pp);

			//Set the date of the Powerball Number for the set so it doesn't have to be set for every single Powerball number scanned in above.
			pbNum.setDate( month, day, year );

			if( nums.isSaved(wb1, month, day, year, nums.White) == false )
			{//If the number isn't in the database. save it to the database.
				//std::cout << "Adding number " << wb1 << " " << month << "/" << day << "/" << year << " White ball." << std::endl;
				pbNum.setNumber( wb1 );
				pbNum.setType( nums.White );
				numsToSave.insert( pbNum );
				//nums.addNum( wb1, month, day, year, nums.White );
				xmlNums.addNum( wb1, month, day, year, nums.White );
				jsonNums.addNum( wb1, month, day, year, nums.White );
			}
			else
			{
				//std::cout << "Already in the database." << std::endl;
				xmlNums.addNum( wb1, month, day, year, nums.White );
				jsonNums.addNum( wb1, month, day, year, nums.White );
			}
			if( nums.isSaved(wb2, month, day, year, nums.White) == false )
			{//If the number isn't in the database. save it to the database.
				//std::cout << "Adding number " << wb2 << " " << month << "/" << day << "/" << year << " White ball." << std::endl;
				pbNum.setNumber( wb2 );
				pbNum.setType( nums.White );
				numsToSave.insert( pbNum );
				//nums.addNum( wb2, month, day, year, nums.White );
				xmlNums.addNum( wb2, month, day, year, nums.White );
				jsonNums.addNum( wb2, month, day, year, nums.White );
			}
			else
			{
				//std::cout << "Already in the database." << std::endl;
				xmlNums.addNum( wb2, month, day, year, nums.White );
				jsonNums.addNum( wb2, month, day, year, nums.White );
			}
			if( nums.isSaved(wb3, month, day, year, nums.White) == false )
			{//If the number isn't in the database. save it to the database.
				//std::cout << "Adding number " << wb3 << " " << month << "/" << day << "/" << year << " White ball." << std::endl;
				pbNum.setNumber( wb3 );
				pbNum.setType( nums.White );
				numsToSave.insert( pbNum );
				//nums.addNum( wb3, month, day, year, nums.White );
				xmlNums.addNum( wb3, month, day, year, nums.White );
				jsonNums.addNum( wb3, month, day, year, nums.White );
			}
			else
			{
				//std::cout << "Already in the database." << std::endl;
				xmlNums.addNum( wb3, month, day, year, nums.White );
				jsonNums.addNum( wb3, month, day, year, nums.White );
			}
			if( nums.isSaved(wb4, month, day, year, nums.White) == false )
			{//If the number isn't in the database. save it to the database.
				//std::cout << "Adding number " << wb4 << " " << month << "/" << day << "/" << year << " White ball." << std::endl;
				pbNum.setNumber( wb4 );
				pbNum.setType( nums.White );
				numsToSave.insert( pbNum );
				//nums.addNum( wb4, month, day, year, nums.White );
				xmlNums.addNum( wb4, month, day, year, nums.White );
				jsonNums.addNum( wb4, month, day, year, nums.White );
			}
			else
			{
				//std::cout << "Already in the database." << std::endl;
				xmlNums.addNum( wb4, month, day, year, nums.White );
				jsonNums.addNum( wb4, month, day, year, nums.White );
			}
			if( nums.isSaved(wb5, month, day, year, nums.White) == false )
			{//If the number isn't in the database. save it to the database.
				//std::cout << "Adding number " << wb5 << " " << month << "/" << day << "/" << year << " White ball." << std::endl;
				pbNum.setNumber( wb5 );
				pbNum.setType( nums.White );
				numsToSave.insert( pbNum );
				//nums.addNum( wb5, month, day, year, nums.White );
				xmlNums.addNum( wb5, month, day, year, nums.White );
				jsonNums.addNum( wb5, month, day, year, nums.White );
			}
			else
			{
				//std::cout << "Already in the database." << std::endl;
				xmlNums.addNum( wb5, month, day, year, nums.White );
				jsonNums.addNum( wb5, month, day, year, nums.White );
			}
			if( nums.isSaved(pb, month, day, year, nums.Powerball) == false )
			{//If the number isn't in the database. save it to the database.
				//std::cout << "Adding number " << pb << " " << month << "/" << day << "/" << year << " Powerball." << std::endl;
				pbNum.setNumber( pb );
				pbNum.setType( nums.Powerball );
				numsToSave.insert( pbNum );
				//nums.addNum( pb, month, day, year, nums.Powerball );
				xmlNums.addNum( pb, month, day, year, nums.Powerball );
				jsonNums.addNum( pb, month, day, year, nums.Powerball );
			}
			else
			{
				//std::cout << "Already in the database." << std::endl;
				xmlNums.addNum( pb, month, day, year, nums.Powerball );
				jsonNums.addNum( pb, month, day, year, nums.Powerball );
			}
			numLines++;
		}
		if( pp != 0 )
		{//If pp was scanned in from sscanf above.
			if( nums.isSaved(pp, month, day, year, nums.PowerPlay) == false )
			{//If the number isn't in the database. save it to the database.
				//std::cout << "Adding number " << pp << " " << month << "/" << day << "/" << year << " Power Play." << std::endl;
				pbNum.setNumber( pp );
				pbNum.setType( nums.PowerPlay );
				numsToSave.insert( pbNum );
				//nums.addNum( pp, month, day, year, nums.PowerPlay );
				xmlNums.addNum( pp, month, day, year, nums.PowerPlay );
				jsonNums.addNum( pp, month, day, year, nums.PowerPlay );
			}
			else
			{
				//std::cout << "Already in the database." << std::endl;
				xmlNums.addNum( pp, month, day, year, nums.PowerPlay );
				jsonNums.addNum( pp, month, day, year, nums.PowerPlay );
			}
		}
	}
	//Add the numbers to the database and memory with the nums object.
	std::cout << "Finished pocessing the file, saving new data to the database." << std::endl;
	nums.addNums( numsToSave );
	std::cout << "Finished saving new data to the database." << std::endl;

	//Save the XML file.
	xmlNums.saveToFile( "Powerball.xml" );
	xmlNums.loadFromFile( "Powerball.xml" );

	//Save the JSON file.
	jsonNums.saveToFile( "Powerball.json" );
	jsonNums.loadFromFile( "Powerball.json" );

	//Output to the user how many lines processed
	printf( "Number lines processed: %u\n", numLines );
	//printf( "Number count in the database: %lu\n", nums.numCount() );
	printf( "Number count in the database: %lu\n", nums.numCountDatabase() );
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
