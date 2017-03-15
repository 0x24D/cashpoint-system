#ifndef CashCardH
#define CashCardH

//---------------------------------------------------------------------------
//Card: class declaration
//---------------------------------------------------------------------------

#include "ListT.h"

#include <fstream>
#include <iomanip>
#include <iostream> 
#include <string>
#include <sstream>
using namespace std;

class CashCard {
public:
    //constructors & destructor
	CashCard();
    CashCard(const string& cardNum, const List<string>& accList);

	//getter (assessor) functions
    const string getCardNumber() const;
    const List<string> getAccountsList() const;

	void readInCardFromFile(const string& fileName);
	bool onCard(const string& fileName) const;

	//functions to put data into and get data from streams
	const string toFormattedString() const;
	ostream& putDataInStream(ostream& os) const;
	istream& getDataFromStream(istream& is);

private:
    string cardNumber_;
    List<string> accountsList_;
};

//---------------------------------------------------------------------------
//non-member operator functions
//---------------------------------------------------------------------------

ostream& operator<<(ostream&, const CashCard&);	//output operator
istream& operator>>(istream&, CashCard&);	//input operator

#endif
