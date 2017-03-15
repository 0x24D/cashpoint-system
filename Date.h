#ifndef DateH
#define DateH

//---------------------------------------------------------------------------
//Date: class declaration
//---------------------------------------------------------------------------

#include <ctime>	// for date functions
#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class Date {
public:
	Date();								//default constructor
	Date(int, int, int);				//constructor
	int getDay() const;					//return a data member value, day_
	int getMonth() const;				//return a data member value, month_
	int getYear() const;				//return a data member value, year_
	void setDate(int, int, int);		//set new values for date
    static const Date currentDate() ;   //return the current date

	string toFormattedString() const ;				//return date as formatted string ("DD/MM/YYYY")

	ostream& putDataInStream(ostream& os) const;	//send Date info into an output stream
	istream& getDataFromStream(istream& is);		//receive Date info from an input stream

	bool operator==(const Date& d) const;  	//true if (*this == d)
	bool operator!=(const Date& d) const;  	//true if (*this != d)
	bool operator<(const Date& d) const;		//true if (*this < d)  (strictly earlier)

private:
	int day_;
	int month_;
	int year_;
};

//---------------------------------------------------------------------------
//non-member operator functions
//---------------------------------------------------------------------------

ostream& operator<<(ostream&, const Date&);	//output operator
istream& operator>>(istream&, Date&);	//input operator

#endif
