#ifndef TimeH
#define TimeH

//---------------------------------------------------------------------------
//Time: class declaration
//---------------------------------------------------------------------------

#include <ctime>	// for time functions

#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class Time {
public:
	Time();						//default constructor
	Time(const Time&);   		//copy constructor
	Time(int h, int m, int s);
	Time(long);				//conversion constructor
	~Time();					//destructor

	static const Time currentTime();    			//return system time

	int getHours() const;
	int getMinutes() const;
	int getSeconds() const;

	void setTime(int h, int m, int s);
	void setTime(long secs);
	void increment(long secs);				//add secs to *this

	const string toFormattedString() const ;		//return time as formatted string ("HH:MM:SS")
	ostream& putDataInStream(ostream& os) const;	//send Time info into an output stream
	istream& getDataFromStream(istream& is);		//receive Time info from an input stream

	bool operator==(const Time& t) const;  //true if (*this == t)
	bool operator!=(const Time& t) const;  //true if (*this != t)
	bool operator <(const Time& t) const;	//true if (*this < t)
	const Time operator +(const Time& t) const;

private:
   long inSeconds_;
};

//---------------------------------------------------------------------------
//non-member operator functions
//---------------------------------------------------------------------------

ostream& operator<<(ostream&, const Time&);	//output operator
istream& operator>>(istream&, Time&);			//input operator

#endif