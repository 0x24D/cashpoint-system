#include "Time.h"			//header file

//---------------------------------------------------------------------------
//Time: class implementation
//---------------------------------------------------------------------------

//____public member functions

//____constructors & destructors
Time::Time()						//default constructor
: inSeconds_(0)
{}
Time::Time(const Time& t) 			//copy constructor
: inSeconds_(t.inSeconds_)
{}
Time::Time(int h, int m, int s)	//basic constructor
: inSeconds_((h * 3600) + (m * 60 ) + s)
{}
Time::Time(long timeInSec)			//conversion constructor
: inSeconds_(timeInSec)
{}
Time::~Time() {
}

//____other public member functions
const Time Time::currentTime() {  		// return system time
	time_t now(time(0));
	struct tm& t(*localtime(&now));
	return Time(t.tm_hour, t.tm_min, t.tm_sec);
}
int Time::getHours() const {
	return(inSeconds_ / 3600);
}
int Time::getMinutes() const {
	return((inSeconds_ % 3600) / 60) ;
}
int Time::getSeconds() const {
	return(inSeconds_ % 60);
}

void Time::setTime(int h, int m, int s) {
   inSeconds_ = (h * 3600) + (m * 60 ) + s;
}
void Time::setTime(long secs) {
   inSeconds_ = secs;
}
void Time::increment(long secs) {//add secs to *this
   inSeconds_ += secs;
}

const string Time::toFormattedString() const {
//return time formatted output ("HH:MM:SS")
	ostringstream os;
	os << setfill('0');
	os << setw(2) << getHours()   << ":";
	os << setw(2) << getMinutes() << ":";
	os << setw(2) << getSeconds();
	return (os.str());
}
ostream& Time::putDataInStream(ostream& os) const {
//put (semi-formatted) time (H:M:S) into an output stream
	os << getHours() << ":";
	os << getMinutes() << ":";
	os << getSeconds();
	return os;
}
istream& Time::getDataFromStream(istream& is) {
//read in time from digital clock (semi-formatted) input stream (H:M:S)
	char ch;			//(any) colon field delimiter
	int h, m, s;
	is >> h >> ch >> m >> ch >> s;
	setTime(h, m, s);
	return is;
}

//---------------------------------------------------------------------------
//overloaded operator functions
//---------------------------------------------------------------------------

bool Time::operator ==(const Time& t) const {	//true if (*this == t)
   return(inSeconds_ == t.inSeconds_);
}
bool Time::operator!=(const Time& t) const {	//true if (*this != t)
	return (! (*this == t));
}
bool Time::operator <(const Time& t) const {	//true if (*this < t)
   return(inSeconds_ < t.inSeconds_);
}
const Time Time::operator +(const Time& t) const {
   return Time(inSeconds_ + t.inSeconds_);
}

//---------------------------------------------------------------------------
//non-member operator functions
//---------------------------------------------------------------------------

ostream& operator<<(ostream& os, const Time& aTime) {
	return (aTime.putDataInStream(os));
}
istream& operator>>(istream& is, Time& aTime) {
	return (aTime.getDataFromStream(is));
}
