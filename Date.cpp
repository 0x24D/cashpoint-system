#include "Date.h"

//---------------------------------------------------------------------------
//Date: class implementation
//---------------------------------------------------------------------------

//____public member functions

//____constructors & destructors
Date::Date() 						//default constructor
: day_(0), month_(0), year_(0)
{}
Date::Date(int d, int m, int y) 	//constructor
: day_(d), month_(m), year_(y)
{}

//____other public member functions
int Date::getDay() const {
	return day_;
}
int Date::getMonth() const {
	return month_;
}
int Date::getYear() const {
	return year_;
}
const Date Date::currentDate() {	//returns the current date
	time_t now(time(0));
	struct tm& t(*localtime(&now));
    return Date(t.tm_mday, t.tm_mon + 1,  t.tm_year + 1900);
}
bool Date::isValid(const Date& date) const{
	if ((date < *this && *this < currentDate()) &&
		((((date.getMonth() == 1) || (date.getMonth() == 3) || (date.getMonth() == 5) || (date.getMonth() == 7) || (date.getMonth() == 8) || (date.getMonth() == 10) || (date.getMonth() == 12) && (date.getDay() <= 31))
		|| ((date.getMonth() == 4) || (date.getMonth() == 6) || (date.getMonth() == 9) || (date.getMonth() == 11) && (date.getDay() <= 30))
		||((date.getMonth() == 2) && (date.getDay() <= 28))) && (date.getDay() > 0)))
		return true;
	return false;
}
void Date::setDate(int d, int m, int y) {
	day_ = d;
	month_ = m;
	year_ = y;
}
string Date::toFormattedString() const {
//return date formatted as string ("DD/MM/YYYY")
	ostringstream os;
	os << setfill('0');
	os << setw(2) << day_ << "/";
	os << setw(2) << month_ << "/";
	os << setw(4) << year_;
	return (os.str());
}

ostream& Date::putDataInStream(ostream& os) const {
//put (unformatted) date (D/M/Y) into an output stream
	os << day_ << "/";
	os << month_ << "/";
	os << year_;
	return os;
}
istream& Date::getDataFromStream(istream& is) {
//read in date from (semi-formatted) input stream (D/M/Y)
	char ch;			//(any) colon field delimiter
	is >> day_ >> ch >> month_ >> ch >> year_;
	return is;
}

//---------------------------------------------------------------------------
//overloaded operator functions
//---------------------------------------------------------------------------

bool Date::operator==(const Date& d) const { //comparison operator
	return
		((day_ == d.day_) &&
		 (month_ == d.month_) &&
		 (year_ == d.year_));
}
bool Date::operator!=(const Date& d) const {
	return (!(*this == d));
}
bool Date::operator<(const Date& d) const { //NEW
//true if (strictly) earlier than d (i.e., *this < d)
	return ((year_ < d.year_)
	     || ((year_ == d.year_) && (month_ < d.month_) )
	     || ((year_ == d.year_) && (month_ == d.month_) && (day_ < d.day_)));
}

//---------------------------------------------------------------------------
//non-member operator functions
//---------------------------------------------------------------------------

ostream& operator<<(ostream& os, const Date& aDate) {
    return (aDate.putDataInStream(os));
}
istream& operator>>(istream& is, Date& aDate) {
	return (aDate.getDataFromStream(is));
}
