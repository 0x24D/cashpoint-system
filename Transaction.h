#ifndef TransactionH
#define TransactionH

//---------------------------------------------------------------------------
//Transaction: class declaration
//---------------------------------------------------------------------------

#include "Date.h"
#include "Time.h"

#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class Transaction {
public:
	Transaction();	//default constructor
	Transaction(const Date&, const Time&, const string&, double);	//constructor
    Transaction(const string&, double);   //constructor

	const Date getDate() const;		//return transaction date_
	const Time getTime() const;		//return transaction time_
	const string getTitle() const;	//return transaction title_
	double getAmount() const;	//return transaction amount

	const string toFormattedString() const ;				//return transaction as a formatted string
	ostream& putDataInStream(ostream& os) const;	//send Transaction info into an output stream
	istream& getDataFromStream(istream& is);		//receive Transaction info from an input stream

	bool operator==(const Transaction&) const; 	//"equal" operator
	bool operator!=(const Transaction&) const; 	//"not-equal" operator

private:
    Date date_;			//transaction date
	Time time_;			//transaction time
	string title_;		//transaction title
	double amount_;		//transaction amount
};

//---------------------------------------------------------------------------
//non-member operator functions
//---------------------------------------------------------------------------

ostream& operator<<(ostream&, const Transaction&);	//output operator
istream& operator>>(istream&, Transaction&);	//input operator

#endif
