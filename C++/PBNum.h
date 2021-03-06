#ifndef PBNum_H
#define PBNum_H

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
		unsigned int getNumber() const;//Returns the number.
		void setNumber( unsigned int newNum );//Sets the number.
		unsigned long getDate() const;//Returns the value of the date in format yyyymmdd.
		void setDate( unsigned char newMonth, unsigned char newDay, unsigned int newYear );//Sets the date.
		unsigned char getMonth() const;//Returns the month.
		void setMonth( unsigned char newMonth );//Sets the month.
		unsigned char getDay() const;//Returns the day.
		void setDay( unsigned char newDay );//Sets the day.
		unsigned int getYear() const;//Returns the year.
		void setYear( unsigned int newYear );//Sets the year.
		unsigned int getType() const;//Returns the type.
		void setType( unsigned int newType );//Sets the type.
		unsigned long dateToLong( unsigned char month, unsigned char day, unsigned int year );//Return the date as a long in the format yyyymmdd.
		void longToDate( unsigned long date, unsigned char &month, unsigned char &day, unsigned int &year );//Return the date as a set of unsigned ints from an input of long in the format yyyymmdd.
		bool equals( unsigned int newNum, unsigned char newMonth, unsigned char newDay, unsigned int newYear, unsigned char newType ) const;//Checks if this number equals the values specified in the parameters.
		friend bool operator <(const PBNum& lhs, const PBNum& rhs);//Less than operator, written mostly to put into set and whatever else might need to sort PBNums.
		friend bool operator >(const PBNum& lhs, const PBNum& rhs);//Greater than operator, written mostly for what might need to sort/compare PBNums.
		friend bool operator ==(const PBNum& lhs, const PBNum& rhs);//Equality operator, written mostly for what might need to sort/compare PBNums.
		friend bool operator !=(const PBNum& lhs, const PBNum& rhs);//Inequality operator, written mostly for what might need to sort/compare PBNums.
};

#endif /* PBNum_H */
